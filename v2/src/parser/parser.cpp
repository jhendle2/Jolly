#include <iostream>
#include <iterator>
#include <vector>
#include <string>

#include "errors.hpp"
#include "parser.hpp"
#include "variable.hpp"
#include "object_table.hpp"
#include "expressions.hpp"

static std::vector<std::string> shiftTokens(std::vector<std::string> tokens, int shift){
    std::vector<std::string> shifted;
    int count = 0;
    for(std::string token : tokens){
        if(count>=shift) shifted.push_back(token);
        count++;
    }
    return shifted;
}

static std::string tokensToString(std::vector<std::string> tokens){
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


void initializeVariable(ObjectTable<Variable>& vt, std::string type_string, std::string variable_name){
    enum ObjectType type = getTypeFromString(type_string);
    Variable var = Variable(type);
    var.setName(variable_name);
    std::cout<<"~Initialized Var="<<variable_name<<"\n";
    vt.add(variable_name, var);
    std::cout<<"~"<<vt.get(variable_name).toString()<<"\n";
}


void buildVariableAndEvaluateExpressions(ObjectTable<Variable>& vt, std::vector<std::string> tokens){
    // Obvious error
    if(tokens.size() == 0)
        ERROROUT(ParseDebugNoTokens, tokensToString(tokens));
    
    // Single word keywords
    if(tokens.size() == 1){
        ERROROUT(ParseDebugOneToken, tokensToString(tokens));
    }

    // Expressions, function calls, variables initialization, etc.
    else{

        bool first_token_is_type = isObjectType(tokens[0]);
        if(first_token_is_type){
            std::cout<<"######################\n";
            bool second_token_is_known_variable = vt.isKnown(tokens[1]);
            std::cout<<"stikv="<<second_token_is_known_variable<<"\n";
            if(second_token_is_known_variable){
                ERROROUT(SyntaxErrorReinitializedVariable, tokensToString(tokens));
            }

            std::string type_string = tokens[0];
            std::string variable_name = tokens[1];
            initializeVariable(vt, type_string, variable_name);
            vt.dump();

            // if there are still tokens left
            if(tokens.size() > 2){
                std::vector<std::string> shifted_tokens = shiftTokens(tokens, 1);
                buildVariableAndEvaluateExpressions(vt, shifted_tokens); // recurse and do it again now with var initialized
            }
        }

        bool first_token_is_known_variable = vt.isKnown(tokens[0]);
        if(first_token_is_known_variable){
            std::string variable_name = tokens[0];
            Variable expression_result = evaluateExpression(vt, tokens);
            vt.update(variable_name, expression_result);
        }

        else{
            // ERROROUT(SyntaxErrorUnrecognizedVariable, tokensToString(tokens));
        }

    }
}