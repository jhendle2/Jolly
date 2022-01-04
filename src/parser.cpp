#include <iostream>
#include <iterator>
#include <vector>
#include <string>

#include "errors.hpp"
#include "parser.hpp"
#include "variable.hpp"
#include "variable_table.hpp"
#include "operators.hpp"

#include "print.hpp"

std::vector<std::string> shiftTokens(std::vector<std::string> tokens, int shift){
    std::vector<std::string> shifted;
    int count = 0;
    for(std::string token : tokens){
        if(count>=shift) shifted.push_back(token);
        count++;
    }
    return shifted;
}

std::string tokensToString(std::vector<std::string> tokens){
    std::string tokensAsString = "";
    for(std::string token : tokens) tokensAsString += token + " ";
    return tokensAsString;
}

std::vector<std::string> tokenizeLine(std::string line){
    std::vector<std::string> tokens;
    std::string temp = "";
    int line_length = line.length();
    bool inside_a_string = false;

    for(int i = 0; i<line_length; i++){
        char c = line.at(i);

        if(c == '\"'){
            if(inside_a_string){
                inside_a_string = false;
                temp+=c;
                if(temp!="\"")
                    tokens.push_back(temp);
                temp = "";
            }
            else{
                temp += c;
                inside_a_string = true;
            }
        }
        else if(c == ' '){
            if(!inside_a_string){
                if(temp.length() > 0 && temp!="\"")
                    tokens.push_back(temp);
                temp = "";
            }
            else{
                temp += c;
            }
        }
        else if(isDelimiter(c)){
            // if we're inside a string, operators do nothing
            if(inside_a_string){
                temp += c;
            }
            else{

                // check the next char to see if we're a double char operator
                if(i<line_length-1){
                    char next_char = line.at(i+1);

                    std::string op_string{c};
                    op_string += next_char;
                    if(isOperator(op_string)){
                        if(temp!="")
                            tokens.push_back(temp);
                        tokens.push_back(op_string);
                        i++;
                        temp="";
                    }
                    else{
                        std::string delim_string{c};
                        if(temp!="")
                            tokens.push_back(temp);
                        tokens.push_back(delim_string);
                        temp="";
                    }
                }

                // If we end a line with a delimiter
                else{
                    std::string delim_string{c};
                    if(temp!="")
                        tokens.push_back(temp);
                    tokens.push_back(delim_string);
                    temp="";
                }

            }
        }
        else{
            temp += c;
        }
    }
    if(temp.length() > 0 && temp!="\"")
        tokens.push_back(temp);

    return tokens;
}

Variable buildVariableFromTokens(std::vector<std::string> tokens){
    // if(tokens.size() < 2) return Variable();
    if(tokens.size() < 2) ERROROUT(SyntaxErrorIncompleteStatement, tokensToString(tokens));

    std::string type_string = tokens[0]; // Type
    if(isVariableType(type_string)){
        std::string variable_name = tokens[1]; // Variable Name
        
        enum Type type = getTypeFromString(type_string);
        Variable var = Variable(type);

        if(tokens.size() > 3){
            std::string equals_sign = tokens[2]; // Equals Sign
            std::string value_string = tokens[3]; // Value

            if(isKnownVariable(value_string))
                setVariableFromOtherVariable(variable_name, value_string);
            else
                var.setFromString(value_string);
        }

        return var;
    }
    return Variable();
}

Variable reassignVariableFromTokens(std::vector<std::string> tokens){
    // if(tokens.size() < 2) return Variable();
    if(tokens.size() < 2) ERROROUT(SyntaxErrorIncompleteStatement, tokensToString(tokens));

    std::string variable_name = tokens[1]; // Variable Name
    std::string equals_sign = tokens[2]; // =
    std::string value_string = tokens[3]; // Value

    updateVariable(variable_name, value_string);

    return getVariable(variable_name);
}

void buildVariableFromTokensAndAdd(std::vector<std::string> tokens){
    if(tokens.size() < 2) ERROROUT(SyntaxErrorIncompleteStatement, tokensToString(tokens));

    std::string variable_name = tokens[1];
    Variable var = buildVariableFromTokens(tokens);
    setVariable(variable_name, var);
}

void buildVariableAndEvaluateExpressions(std::vector<std::string> tokens){

    // Syntax error
    if(tokens.size() < 2) ERROROUT(SyntaxErrorIncompleteStatement, tokensToString(tokens));

    // Type name
    if(tokens.size() == 2){

        std::string type_string = tokens.at(0);
        if(isVariableType(type_string)){
            enum Type type = getTypeFromString(type_string);
            Variable var = Variable(type);

            std::string variable_name = tokens.at(1);
            setVariable(variable_name, var);
        }

        else{
            ERROROUT(SyntaxErrorUnrecognizedType, tokensToString(tokens));
        }
    }

    // name = value
    else if(tokens.size() == 3){

        std::string variable_name = tokens.at(0);
        if(isKnownVariable(variable_name)){
            std::string equals_sign = tokens.at(1);
            std::string value_string = tokens.at(2);

            if(isKnownVariable(value_string)){
                updateVariableFromOtherVariable(variable_name, value_string);
            }

            else{
                updateVariable(variable_name, value_string);
            }
        }

        else{
            ERROROUT(SyntaxErrorUnrecognizedVariable, tokensToString(tokens));
        }
    }

    // Type name = value (OR) Type name = expression... (OR) name = expression...
    else if(tokens.size() > 3){

        if(tokens.at(0)=="Print"){
            // string in Print
            if(tokens.at(2).at(0)=='\"'){
                Print(tokens.at(2));
            }
            else{
                Variable var_within_print = getVariable(tokens.at(2));
                Print(var_within_print);
            }
            return;
        }
        else if(tokens.at(0)=="Println"){
            if(tokens.at(2).at(0)=='\"'){
                Println(tokens.at(2));
            }
            else{
                Variable var_within_print = getVariable(tokens.at(2));
                Println(var_within_print);
            }
            return;
        }

        // Type name = value (OR) Type name = expression...
        if(isVariableType(tokens.at(0))){
            
            // Type name = value
            if(tokens.size() == 4){
                buildVariableFromTokensAndAdd(tokens);
            }

            // Type name = expression...
            else{
                std::vector<std::string> expression_tokens = shiftTokens(tokens, 3);
                Variable expression_result = evaluateExpression(expression_tokens);
                std::string variable_name = tokens.at(1);
                setVariable(variable_name, expression_result);
            }
        }

        // name = expression...
        else{
            std::vector<std::string> expression_tokens = shiftTokens(tokens, 2);
            Variable expression_result = evaluateExpression(expression_tokens);
            std::string variable_name = tokens.at(1);
            updateVariable(variable_name, expression_result);
        }
    }
}