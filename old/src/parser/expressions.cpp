#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <deque>

#include "constants.hpp"
#include "expressions.hpp"
#include "types.hpp"
#include "errors.hpp"

#include "object_table.hpp"

// This code was adapted from a tutorial by Nikhil Jindal.

std::unordered_map<std::string, int> prio = {
    {"++", 10},
    {"--", 10},
    {"^", 9},
    {"%", 8},
    {"*", 8},
    {"/", 8},
    {"+", 7},
    {"-", 7},
    {"<", 6},
    {">", 6},
    {"<=", 6},
    {">=", 6},
    {"==", 5},
    {"!=", 5},
    {"and", 4},
    {"&&", 4},
    {"xor", 3},
    {"^^", 3},
    {"or", 3},
    {"||", 3},
    {"+=", 2},
    {"-=", 2},
    {"*=", 2},
    {"/=", 2},
    {"%=", 2},
    {"|=", 2},
    {"or=", 2},
    {"^=", 2},
    {"xor=", 2},
    {"&=", 2},
    {"and=", 2},
    {"=", 2},
    {":", 2},
    {"(", 0},
    {")", 0},
};

bool isOperator(std::string op){
    return prio.count(op) > 0;
}

bool isDelimiter(char c){
    return (
        c=='(' ||
        c==')' ||
        c=='[' ||
        c==']' ||
        c=='{' ||
        c=='}' ||
        c=='+' ||
        c=='-' ||
        c=='*' ||
        c=='/' ||
        c=='%' ||
        c=='^' ||
        c=='=' ||
        c=='!' ||
        c==':' ||
        c=='?' ||
        c=='<' ||
        c=='>'
    );
}

// Yields the precendence an operation has
int precendence(std::string op){
    if(prio.count(op) > 0)
        return prio.at(op);
    else
        return prio.at("+");
        // ERROROUT(SyntaxErrorBadOperator, op);
}

// Applies an operation between two variables a and b
// and updates the definition of the left operand
// within the scope's variable lookup table
// (OR)
// generates a new variable from the operation
// and adds it to the scope's variable lookup table
Variable applyOp(Scope* scope, Variable a, Variable b, std::string op){
    // std::cout<<"Applying Op ["<<op<<"] to "<<a.toString()<<" and "<<b.toString()<<" => ";

    enum ObjectType a_type = a.getType(), b_type = b.getType();
    // std::cout<<"a_type="<<typeToString(a.getType())<<" b_type="<<typeToString(b.getType())<<"\n";
    bool same_types = (a_type==b_type);

    if(same_types && op == "="){
        a.eq(b);
        scope->updateVariableRecursive(a);
        return a;
    }
    else if(same_types && op == "=="){
        Boolean equality = a.equality(b);
        return equality;
    }
    else if(same_types && op == "!="){
        Boolean inequality = a.inequality(b);
        return inequality;
    }

    if(a_type == TYPE_NUMBER){
        Number an = Number(a);
        if(b_type == TYPE_NUMBER || b_type == TYPE_CHAR){
            Number bn = Number(b);
            if(op=="+=") return scope->updateVariableAndGetRecursive(an.addEq(bn));
            else if(op=="+") return scope->updateVariableAndGetRecursive(an.add(bn));
            else if(op=="-=") return scope->updateVariableAndGetRecursive(an.subEq(bn));
            else if(op=="-") return scope->updateVariableAndGetRecursive(an.sub(bn));
            else if(op=="*=") return scope->updateVariableAndGetRecursive(an.mulEq(bn));
            else if(op=="*") return scope->updateVariableAndGetRecursive(an.mul(bn));
            else if(op=="/=") return scope->updateVariableAndGetRecursive(an.divEq(bn));
            else if(op=="/") return scope->updateVariableAndGetRecursive(an.div(bn));
            else if(op=="^=") return scope->updateVariableAndGetRecursive(an.expEq(bn));
            else if(op=="^") return scope->updateVariableAndGetRecursive(an.exp(bn));
            else if(op=="%=") return scope->updateVariableAndGetRecursive(an.modEq(bn));
            else if(op=="%") return scope->updateVariableAndGetRecursive(an.mod(bn));
        }
        return an;
    }

    else if(a_type == TYPE_CHAR){
        Character an = Character(a);
        if(b_type == TYPE_CHAR || b_type == TYPE_NUMBER){
            Character bn = Character(b);
            if(op=="+=") return scope->updateVariableAndGetRecursive(an.addEq(bn));
            else if(op=="+") return scope->updateVariableAndGetRecursive(an.add(bn));
        }
        return an;
    }

    else if(a_type == TYPE_STRING){
        String an = String(a);
        if(op=="+=") return scope->updateVariableAndGetRecursive(an.addEq(b));
        else if(op=="+") return scope->updateVariableAndGetRecursive(an.add(b));
        else if(op=="*=") return scope->updateVariableAndGetRecursive(an.mulEq(b));
        else if(op=="*") return scope->updateVariableAndGetRecursive(an.mul(b));
        return an;
    }

    else if(a_type == TYPE_BOOL){
        Boolean an = Boolean(a);
        if(b_type == TYPE_BOOL){
            Boolean bn = Boolean(b);
            if(op=="+=") return scope->updateVariableAndGetRecursive(an.addEq(bn));
            else if(op=="+") return scope->updateVariableAndGetRecursive(an.add(bn));
            else if(op=="|=") return scope->updateVariableAndGetRecursive(an._orEq(bn));
            else if(op=="or=") return scope->updateVariableAndGetRecursive(an._orEq(bn));
            else if(op=="or") return scope->updateVariableAndGetRecursive(an._or(bn));
            else if(op=="||") return scope->updateVariableAndGetRecursive(an._or(bn));
            else if(op=="&=") return scope->updateVariableAndGetRecursive(an._andEq(bn));
            else if(op=="and=") return scope->updateVariableAndGetRecursive(an._andEq(bn));
            else if(op=="and") return scope->updateVariableAndGetRecursive(an._and(bn));
            else if(op=="&&") return scope->updateVariableAndGetRecursive(an._and(bn));
            else if(op=="^=") return scope->updateVariableAndGetRecursive(an._xorEq(bn));
            else if(op=="xor=") return scope->updateVariableAndGetRecursive(an._xorEq(bn));
            else if(op=="xor") return scope->updateVariableAndGetRecursive(an._xor(bn));
            else if(op=="^^") return scope->updateVariableAndGetRecursive(an._xor(bn));
        }
        return an;
    }

    else{
        SAFEERROROUT(scope, ArithmeticErrorIncompatibleTypes, a.getName() + op + b.getName());
    }

    return Variable();
}

// Evaluates an expression of tokens by
// setting variables in the scope's variable lookup table to constants
// or applying operations between known variables and/or constants
// Uses a stack to keep track of operators and operands
// Allows for support of parenthesis to enforce order of operations
Variable evaluateExpression(Scope* scope, std::vector<std::string> tokens){
    std::stack<Variable> values;
    std::stack<std::string> operators;

    for(int i = 0; i<(int)tokens.size(); i++){

        if(tokens[i] ==  "") continue;

        else if(tokens[i] == "("){
            operators.push(tokens[i]);
        }

        else if(isNumber(tokens[i])){
            Number number(tokens[i]);
            number.setName("constant");
            values.push(number);
        }

        else if(isString(tokens[i])){
            String str(tokens[i]);
            str.setName("constant");
            values.push(str);
        }

        else if(isBool(tokens[i])){
            Boolean b(tokens[i]);
            b.setName("constant");
            values.push(b);
        }

        else if(isChar(tokens[i])){
            Character c(tokens[i]);
            c.setName("constant");
            values.push(c);
        }

        else if(tokens[i] == ")"){
            while(!operators.empty() && operators.top() != "("){
                Variable val2 = values.top();
                values.pop();
                
                Variable val1 = values.top();
                values.pop();

                std::string op = operators.top();
                operators.pop();

                Variable result = applyOp(scope, val1, val2, op);

                values.push(result);
            }

            if(!operators.empty())
                operators.pop();
        }

        else{
            if(isOperator(tokens[i])){

                while(!operators.empty() && precendence(operators.top()) >= precendence(tokens[i])){
                    Variable val2 = values.top();
                    values.pop();

                    Variable val1 = values.top();
                    values.pop();

                    std::string op = operators.top();
                    operators.pop();

                    Variable result = applyOp(scope, val1, val2, op);

                    values.push(result);

                }

                operators.push(tokens[i]);
            }

            else{
                Variable looked_up_variable = Variable();
                bool has_variable = scope->getVariableRecursive(tokens[i], looked_up_variable);
                if(has_variable){
                    values.push(looked_up_variable);
                    continue;
                }

                Scope* func_as_scope = scope->getScopeRecursive(tokens[i]);
                bool first_token_is_known_func = (func_as_scope != nullptr);
                if(first_token_is_known_func){
                    Function* func = (Function*)func_as_scope;
                    Variable function_return = returnFunction(func); // Evaluates the function if it hasn't already been. Then pushes this variable to the expression stack
                    values.push(function_return);
                    continue;
                }

                SAFEERROROUT(scope, SyntaxErrorUnrecognizedObject, tokens[i]);
                // else SAFEERROROUT(scope, SyntaxErrorUnrecognizedVariable, tokens[i]);
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

        Variable result = applyOp(scope, val1, val2, op);

        values.push(result);
    }

    return values.top();
}