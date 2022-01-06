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
    // std::cout<<"precendence\n";
    if(prio.count(op) > 0)
        return prio.at(op);
    else
        ERROROUT(SyntaxErrorBadOperator, op);
}

Variable applyOp(ObjectTable<Variable>& vt, Variable a, Variable b, std::string op){
    std::cout<<"Applying Op ["<<op<<"] to "<<a.toString()<<" and "<<b.toString()<<" => ";
    // std::cout<<"Types are equal: "<<((a.getType()==b.getType())?"True":"False")<<"\n";

    enum ObjectType a_type = a.getType(), b_type = b.getType();
    std::cout<<"a_type="<<typeToString(a.getType())<<"b_type="<<typeToString(b.getType())<<"\n";
    bool same_types = (a_type==b_type);

    if(same_types && op == "="){
        a.eq(b);
        vt.update(a);
        return a;
    }

    if(a_type == TYPE_NUMBER){
        Number an = Number(a);
        if(b_type == TYPE_NUMBER){
            Number bn = Number(b);
            if(op=="+=") return vt.updateAndGet(an.addEq(bn));
            else if(op=="+") return vt.updateAndGet(an.add(bn));
        }
        return an;
    }

    else if(a_type == TYPE_STRING){
        String an = String(a);
        if(op=="+=") return vt.updateAndGet(an.addEq(b));
        else if(op=="+") return vt.updateAndGet(an.add(b));
        return an;
    }

    else if(a_type == TYPE_BOOL){
        Boolean an = Boolean(a);
        if(b_type == TYPE_BOOL){
            Boolean bn = Boolean(b);
            if(op=="+=") return vt.updateAndGet(an.addEq(bn));
            else if(op=="+") return vt.updateAndGet(an.add(bn));
        }
        return an;
    }

    // if(same_types){
    //     std::cout<<"Same Types\n";
    //     if(op == "="){
    //         a.eq(b);
    //         vt.update(a);
    //         return a;
    //     }
    //     else if(op == "+=") return vt.updateAndGet(a.addEq(b));
    //     else if(op == "+") return vt.updateAndGet(a.add(b));
    // }

    // else{
    //     std::cout<<"Different Types\n";
    // }

    // if(a.getType() == b.getType()){
    //     if(op=="==") return a.equality(b);
    //     else if(op=="!=") return a.inequality(b);

    //     else if(op=="="){
    //         a.eq(b);
    //         vt.updateVariable(a.getName(), a);
    //         return a;
    //     }

    //     if(a.getType() == TYPE_NUMBER){
    //         Number an(a);
    //         Number bn(b);
    //         if(op=="+") return an.add(bn);
    //         else if(op=="-") return an.subtract(bn);
    //         else if(op=="*") return an.multiply(bn);
    //         else if(op=="/") return an.divide(bn);
    //         else if(op=="%") return an.mod(bn);
    //         else if(op=="^") return an.power(bn);

    //         else if(op=="+=") return vt.updateVariableAndGet(an.addEq(bn));
    //         else if(op=="-=") return vt.updateVariableAndGet(an.subtractEq(bn));
    //         else if(op=="*=") return vt.updateVariableAndGet(an.multiplyEq(bn));
    //         else if(op=="/=") return vt.updateVariableAndGet(an.divideEq(bn));
    //         else if(op=="%=") return vt.updateVariableAndGet(an.modEq(bn));
    //         else if(op=="^=") return vt.updateVariableAndGet(an.powerEq(bn));

    //         else if(op=="<") return an.less(bn);
    //         else if(op==">") return an.greater(bn);
    //         else if(op=="<=") return an.lessEq(bn);
    //         else if(op==">=") return an.greaterEq(bn);

    //         else return an;
    //     }
    // }

    // if(a.getType() == TYPE_STRING){
    //     std::cout<<"herrreee\n";
    //     String as(a);
    //     String bs(b.toString());
    //     // std::cout<<"TYPE_STRING WITH "<<as.toString()<<" AND "<<bs.toString()<<"\n";
    //     if(op=="+") return as.add(bs);

    //     else if(op=="+=") return vt.updateVariableAndGet(as.addEq(bs));
    // }

    // else{
    //     std::cout<<"there\n";
    //     std::string error_msg = a.toStringWithQuotes() + " " + op + " " + b.toStringWithQuotes(); 
    //     ERROROUT(SyntaxErrorBadOperation,error_msg);
    // }
    // return a;
    return Variable();
}

Variable evaluateExpression(ObjectTable<Variable>& vt, std::vector<std::string> tokens){
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
            // std::cout<<"Found number: "<<tokens[i]<<"\n";
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

                Variable result = applyOp(vt, val1, val2, op);
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

                    Variable result = applyOp(vt, val1, val2, op);
                    // std::cout<<"Result="<<result.toString()<<"\n";
                    values.push(result);

                }

                // std::cout<<"Pushed: "<<tokens[i]<<"\n";
                operators.push(tokens[i]);
            }

            else{
                Variable lookedUpVariable = vt.get(tokens[i]);
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

        Variable result = applyOp(vt, val1, val2, op);
        // std::cout<<"Result="<<result.toString()<<"\n";
        values.push(result);
    }

    return values.top();
}