#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <deque>

#include "operators.hpp"
#include "variable.hpp"
#include "errors.hpp"
#include "number.hpp"
#include "string.hpp"

#include "variable_table.hpp"

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
    // std::cout<<"precendence\n";
    if(prio.count(op) > 0)
        return prio.at(op);
    else
        ERROROUT(SyntaxErrorBadOperator, op);
}

Variable applyOp(Variable a, Variable b, std::string op){
    // std::cout<<"Applying Op ["<<op<<"] to "<<a.toString()<<" and "<<b.toString()<<" => ";

    if(a.getType() == b.getType()){
        if(op=="==") return a.equality(b);
        else if(op=="!=") return a.inequality(b);

        if(a.getType() == TYPE_NUMBER){
            Number an(a);
            Number bn(b);
            if(op=="+") return an.add(bn);
            else if(op=="-") return an.subtract(bn);
            else if(op=="*") return an.multiply(bn);
            else if(op=="/") return an.divide(bn);
            else if(op=="%") return an.mod(bn);
            else if(op=="^") return an.power(bn);
            else if(op=="<") return an.less(bn);
            else if(op==">") return an.greater(bn);
            else if(op=="<=") return an.lessEq(bn);
            else if(op==">=") return an.greaterEq(bn);

            else return an;
        }

        else if(a.getType() == TYPE_STRING){
            String as(a);
            String bs(b);
            // std::cout<<"TYPE_STRING WITH "<<as.toString()<<" AND "<<bs.toString()<<"\n";
            if(op=="+") return as.add(bs);
            else if(op=="=") return as.eq(bs);
        }
    }
    return a;
}

Variable evaluateExpression(std::vector<std::string> tokens){
    std::stack<Variable> values;
    std::stack<std::string> operators;

    for(int i = 0; i<(int)tokens.size(); i++){
        // std::cout<<"Token=<"<<tokens[i]<<">\n";

        if(tokens[i] ==  "") continue;

        else if(tokens[i] == "("){
            operators.push(tokens[i]);
        }

        else if(isNumber(tokens[i])){
            Number number(tokens[i]);
            // std::cout<<"Found number: "<<tokens[i]<<"\n";
            values.push(number);
        }

        else if(isString(tokens[i])){
            String str(tokens[i]);
            values.push(str);
        }

        else if(tokens[i] == ")"){
            while(!operators.empty() && operators.top() != "("){
                Variable val2 = values.top();
                values.pop();
                
                Variable val1 = values.top();
                values.pop();

                std::string op = operators.top();
                operators.pop();

                Variable result = applyOp(val1, val2, op);
                // std::cout<<"Result="<<result.toString()<<"\n";
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

                    Variable result = applyOp(val1, val2, op);
                    // std::cout<<"Result="<<result.toString()<<"\n";
                    values.push(result);

                }

                // std::cout<<"Pushed: "<<tokens[i]<<"\n";
                operators.push(tokens[i]);
            }

            else{
                Variable lookedUpVariable = getVariable(tokens[i]);
                values.push(lookedUpVariable);
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

        Variable result = applyOp(val1, val2, op);
        // std::cout<<"Result="<<result.toString()<<"\n";
        values.push(result);
    }

    return values.top();
}