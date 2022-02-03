#include <iostream>
#include <string>
#include <stack>

#include "variable_utils.hpp"
#include "expressions.hpp"
#include "keywords.hpp"
#include "operators_delimiters.hpp"
#include "logging.hpp"

Variable applyOp(ScopePtr& current_scope, Variable left, std::string op, const Variable& right){
    if(op == OP_EQ){
        left._set(right);
        current_scope->updateVariableRecursive(left);
        return left;
    }

    if(op == OP_EQUALITY){ return Variable(left._eq(right));}
    if(op == OP_INEQUALITY){ return Variable(left._notEq(right));}
    return Variable();
}

Variable evaluateExpression(ScopePtr& current_scope, Tokens tokens){
    LOGDEBUG("EE " + tokensToLine(tokens));
    std::stack<Variable> values;
    std::stack<std::string> operators;

    for(int i = 0; i<(int)tokens.size(); i++){
        // if(LOGLEVEL == LOGLEVELDEBUG){
        //     std::cout<<"ee-tok ["<<i<<"] = "<<tokens[i]<<"\n";
        // }

        if(tokens[i] ==  "") continue;

        else if(tokens[i] == "("){
            operators.push(tokens[i]);
        }

        else if(VarUtils::isNumber(tokens[i])){
            Variable var("constant", KW_NUMBER);
            double value = (double)atoi(tokens[i].c_str());
            var.setValue(value);
            values.push(var);
        }

        else if(VarUtils::isDecimal(tokens[i])){
            Variable var("constant", KW_NUMBER);
            double value = (double)atoi(tokens[i].c_str());
            var.setValue(value);
            values.push(var);
        }

        else if(VarUtils::isString(tokens[i])){
            Variable var("constant", KW_STRING);
            std::string value = VarUtils::dropDoubleQuotes(tokens[i]);
            var.setValue(value);
            values.push(var);
        }

        else if(VarUtils::isBoolean(tokens[i])){
            Variable var("constant", KW_BOOLEAN);
            bool value = VarUtils::stringToBool(tokens[i]);
            var.setValue(value);
            values.push(var);
        }

        else if(VarUtils::isCharacter(tokens[i])){
            Variable var("constant", KW_CHARACTER);
            char value = VarUtils::dropSingleQuotes(tokens[i]);
            var.setValue(value);
            values.push(var);
        }

        else if(VarUtils::isType(tokens[i])){
            Variable var("constant", KW_CHARACTER);
            VarType value = VarUtils::stringToVarType(tokens[i]);
            var.setValue(value);
            values.push(var);
        }

        else if(tokens[i] == ")"){
            while(!operators.empty() && operators.top() != "("){
                Variable val2 = values.top();
                values.pop();
                
                Variable val1 = values.top();
                values.pop();

                std::string op = operators.top();
                operators.pop();

                Variable result = applyOp(current_scope, val1, op, val2);

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

                    Variable result = applyOp(current_scope, val1, op, val2);

                    values.push(result);

                }

                operators.push(tokens[i]);
            }

            else{
                Variable looked_up_variable = Variable();
                if(current_scope->hasVariableRecursive(tokens[i])){
                    looked_up_variable = current_scope->getVariableRecursive(tokens[i]);
                }
                else{
                    std::cout << "!! Error: " << tokens[i] << " not a known variable!\n";
                }
                values.push(looked_up_variable);

                // std::cout << "!! Error evaluating expression!\n";
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

        Variable result = applyOp(current_scope, val1, op, val2);

        values.push(result);
    }

    // LOGDEBUG("values_top = " + values.top().toString());
    return values.top();
}