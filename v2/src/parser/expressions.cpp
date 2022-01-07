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
    {"xor", 3},
    {"or", 3},
    {"+=", 2},
    {"-=", 2},
    {"*=", 2},
    {"/=", 2},
    {"%=", 2},
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

int precendence(std::string op){
    if(prio.count(op) > 0)
        return prio.at(op);
    else
        ERROROUT(SyntaxErrorBadOperator, op);
}

Variable applyOp(Function* scope, Variable a, Variable b, std::string op){
    std::cout<<"Applying Op ["<<op<<"] to "<<a.toString()<<" and "<<b.toString()<<" => ";

    enum ObjectType a_type = a.getType(), b_type = b.getType();
    std::cout<<"a_type="<<typeToString(a.getType())<<" b_type="<<typeToString(b.getType())<<"\n";
    bool same_types = (a_type==b_type);

    if(same_types && op == "="){
        a.eq(b);
        scope->updateVariable(a);
        return a;
    }

    if(a_type == TYPE_NUMBER){
        Number an = Number(a);
        if(b_type == TYPE_NUMBER || b_type == TYPE_CHAR){
            Number bn = Number(b);
            if(op=="+=") return scope->updateVariableAndGet(an.addEq(bn));
            else if(op=="+") return scope->updateVariableAndGet(an.add(bn));
        }
        return an;
    }

    else if(a_type == TYPE_CHAR){
        Character an = Character(a);
        if(b_type == TYPE_CHAR || b_type == TYPE_NUMBER){
            Character bn = Character(b);
            if(op=="+=") return scope->updateVariableAndGet(an.addEq(bn));
            else if(op=="+") return scope->updateVariableAndGet(an.add(bn));
        }
        return an;
    }

    else if(a_type == TYPE_STRING){
        String an = String(a);
        if(op=="+=") return scope->updateVariableAndGet(an.addEq(b));
        else if(op=="+") return scope->updateVariableAndGet(an.add(b));
        return an;
    }

    else if(a_type == TYPE_BOOL){
        Boolean an = Boolean(a);
        if(b_type == TYPE_BOOL){
            Boolean bn = Boolean(b);
            if(op=="+=") return scope->updateVariableAndGet(an.addEq(bn));
            else if(op=="+") return scope->updateVariableAndGet(an.add(bn));
        }
        return an;
    }

    return Variable();
}

Variable evaluateExpression(Function* scope, std::vector<std::string> tokens){
    std::stack<Variable> values;
    std::stack<std::string> operators;

    for(int i = 0; i<(int)tokens.size(); i++){
        std::cout<<"Token=<"<<tokens[i]<<">\n";

        if(tokens[i] ==  "") continue;

        else if(tokens[i] == "("){
            operators.push(tokens[i]);
        }

        else if(isNumber(tokens[i])){
            std::cout<<tokens[i]<<" is number\n";
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
                if(has_variable) values.push(looked_up_variable);
                else ERROROUT(SyntaxErrorUnrecognizedVariable, tokens[i]);
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