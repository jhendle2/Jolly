#include <string>
#include <stack>

#include "operators.hpp"
#include "errors.hpp"
#include "logging.hpp"
#include "type_handler.hpp"
#include "expressions.hpp"
#include "function.hpp"

template <typename T>
static Variable applyOpType(Scope*& current_scope, Variable a, Variable b, std::string op){
    if(!compatibleTypes(a.getPrimType(), b.getPrimType())){
        ERROR(ArithmeticErrorIncompatibleTypes);
    }

    T a_n = T(a), b_n = T(b);

    bool has_operation = a_n.hasOperation(op);
    if(!has_operation) ERROR(ArithmeticErrorBadOperation);

    if(op == OP_ADD) return a_n._add(b_n);
    else if(op == OP_SUB) return a_n._sub(b_n);
    else if(op == OP_MUL) return a_n._mul(b_n);
    else if(op == OP_DIV) return a_n._div(b_n);
    else if(op == OP_MOD) return a_n._mod(b_n);
    else if(op == OP_EXP) return a_n._exp(b_n);
    else if(op == OP_CAT) return a_n._cat(b_n);
    else if(op == OP_EQ) {
        a_n.set(b_n);
        current_scope->updateVariableRecursive(a_n);
        return a_n;
    }
    else if(op == OP_EQUALITY) return Boolean(a_n.eq(b_n));
    else if(op == OP_INEQUALITY) return Boolean(a_n.notEq(b_n));
    else if(op == OP_LESS) return Boolean(a_n._less(b_n));
    else if(op == OP_GREATER) return Boolean(a_n._greater(b_n));

    ERROR(ArithmeticErrorBadOperation);
    return T();
}

static Variable applyOp(Scope*& current_scope, Variable a, Variable b, std::string op){
    // Strings have priority, regardless
    if(b.getPrimType() == Prim_String && a.getPrimType() != Prim_String){
        a = String(a);
    }
    enum PrimType a_type = a.getPrimType();
    enum PrimType b_type = b.getPrimType();

    // We can only trivially perform these operations if types are the same
    // otherwise, we need to use a type specific equals operator
    if(a_type == b_type){
        if(op == OP_EQ){
            a.set(b);
            current_scope->updateVariableRecursive(a);
            return a;
        }

        if(op == OP_EQUALITY) return Boolean(a.eq(b));
        if(op == OP_INEQUALITY) return Boolean(a.notEq(b));
    }

    // Otherwise, they're guaranteed to be false and true respectively
    // TODO: Change this because [True == "True"] should also be allowed
    if(op == OP_EQUALITY) return Boolean(false);
    if(op == OP_INEQUALITY) return Boolean(true);

    // If this operator is an EQUALS+OPERATOR,
    // we perform the operation first,
    // then set variable
    if(op.length() > 1 && op.substr(1,2) == OP_EQ){
        Variable result = applyOp(current_scope, a, b, op.substr(0, 1));
        a.set(result);
        current_scope->updateVariableRecursive(a);
        return a;
    }

    // If we couldn't perform the previous operations,
    // cast the types accordingly and perform the needed operation.
    switch(a_type){
        default:
        case Prim_Nothing: return Variable();

        case Prim_Number: return applyOpType<Number>(current_scope, a, b, op);
        case Prim_Boolean: return applyOpType<Boolean>(current_scope, a, b, op);
        case Prim_Char: return applyOpType<Character>(current_scope, a, b, op);
        case Prim_String: return applyOpType<String>(current_scope, a, b, op);
        case Prim_Type: return applyOpType<Type>(current_scope, a, b, op);
    }
}


Variable evaluateExpression(Scope*& current_scope, Tokens tokens){
    std::stack<Variable> values;
    std::stack<std::string> operators;

    for(int i = 0; i<(int)tokens.size(); i++){
        if(LOGLEVEL == LOGLEVELDEBUG){
            std::cout<<"ee-tok ["<<i<<"] = "<<tokens[i]<<"\n";
        }

        if(tokens[i] ==  "") continue;

        else if(tokens[i] == "("){
            operators.push(tokens[i]);
        }

        else if(isNumber(tokens[i])){
            Number number("constant", atoi(tokens[i].c_str()));
            values.push(number);
        }

        else if(isDecimal(tokens[i])){
            Number number("constant", atof(tokens[i].c_str()));
            values.push(number);
        }

        else if(isString(tokens[i])){
            String str("constant", tokens[i]);
            values.push(str);
        }

        else if(isBoolean(tokens[i])){
            Boolean b("constant", tokens[i]);
            values.push(b);
        }

        else if(isCharacter(tokens[i])){
            Character c("constant", tokens[i]);
            values.push(c);
        }

        else if(isPrimType(tokens[i])){
            Type t("constant", keyword2PrimType(tokens[i]));
            values.push(t);
        }

        else if(tokens[i] == ")"){
            while(!operators.empty() && operators.top() != "("){
                Variable val2 = values.top();
                values.pop();
                
                Variable val1 = values.top();
                values.pop();

                std::string op = operators.top();
                operators.pop();

                Variable result = applyOp(current_scope, val1, val2, op);

                values.push(result);
            }

            if(!operators.empty())
                operators.pop();
        }

        else{
            if(isOperator(tokens[i])){

                while(!operators.empty() && precedence(operators.top()) >= precedence(tokens[i])){
                    Variable val2 = values.top();
                    values.pop();

                    Variable val1 = values.top();
                    values.pop();

                    std::string op = operators.top();
                    operators.pop();

                    Variable result = applyOp(current_scope, val1, val2, op);

                    values.push(result);

                }

                operators.push(tokens[i]);
            }

            else{
                Variable looked_up_variable = Variable();
                bool has_variable = current_scope->getVariableRecursive(tokens[i], looked_up_variable);
                if(has_variable){
                    values.push(looked_up_variable);
                    continue;
                }

                Scope* function_as_scope = nullptr;
                bool has_func = current_scope->getScopeRecursive(tokens[i], function_as_scope);
                if(has_func){
                    if(function_as_scope->getScopeType() != SCOPE_FUNCTION){
                        ERROR(ParseErrorScopeNotFunction);
                    }

                    Function* function = (Function*)function_as_scope;

                    if( i < ((int)tokens.size() - 3) ){
                        if( tokens[i + 1] == "("){
                            Tokens param_expression;
                            int j;
                            int param_index = 0;
                            for(j = i + 2; j<(int)tokens.size(); j++){
                                if(LOGLEVEL == LOGLEVELDEBUG) std::cout<<"pe-tok ["<<j<<"] = "<<tokens[j]<<"\n";
                                
                                if(tokens[j] == ")"){
                                    break;
                                }

                                if(tokens[j] == ","){
                                    if(LOGLEVEL == LOGLEVELDEBUG) std::cout<<"pe-pi = "<<param_index<<"\n";
                                    
                                    std::string param_name = std::to_string(param_index);
                                    Variable param = evaluateExpression(current_scope, param_expression);
                                    function->addVariable(param_name, param);

                                    param_expression.clear();
                                    param_index++;
                                    continue;
                                }

                                param_expression.push_back(tokens[j]);
                            }
                            
                            if(param_expression.size() > 0){
                                std::string param_name = std::to_string(param_index);
                                Variable param = evaluateExpression(current_scope, param_expression);
                                function->addVariable(param_name, param);
                            }
                            i = j;
                        }
                    }

                    Variable return_variable = returnFunction(function);

                    values.push(return_variable);
                    continue;
                }

                ERROR(SyntaxErrorUnrecognizedObject);
            }
            
        }
    }

    while(!operators.empty()){
        Variable val2 = values.top();
        values.pop();

        Variable val1 = values.top();
        values.pop();

        std::string op = operators.top();
        operators.pop();

        Variable result = applyOp(current_scope, val1, val2, op);

        values.push(result);
    }

    LOGDEBUG("values_top = " + values.top().toString());
    return values.top();
}