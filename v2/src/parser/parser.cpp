#include <iostream>
#include <iterator>
#include <vector>
#include <string>

#include "errors.hpp"
#include "parser.hpp"
#include "variable.hpp"
#include "object_table.hpp"
#include "expressions.hpp"

#include "parser_keywords.hpp"

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
    bool inside_a_char = false;

    for(int i = 0; i<line_length; i++){
        char c = line.at(i);

        if(c == '\"'){
            if(inside_a_char){
                temp += c;
            }
            else if(inside_a_string){
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
        else if(c == '\''){
            if(inside_a_string){
                temp += c;
            }
            else if(inside_a_char){
                inside_a_char = false;
                temp+=c;
                if(temp!="\'")
                    tokens.push_back(temp);
                temp = "";
            }
            else{
                temp += c;
                inside_a_char = true;
            }
        }
        else if(c == ' '){
            if(!inside_a_string && !inside_a_char){
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
            if(inside_a_string || inside_a_char){
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


void initializeVariable(Function* scope, std::string type_string, std::string variable_name){
    enum ObjectType type = getTypeFromString(type_string);
    Variable var = Variable(type);
    std::cout<<"~Initialized Var="<<variable_name<<"\n";
    scope->addVariable(variable_name, var);
    std::cout<<"~"<<scope->getVariable(variable_name).toString()<<"\n";
}


Function* buildVariableAndEvaluateExpressions(Function* scope, std::vector<std::string> tokens){
    std::cout<<"#################CURRENTLY IN = "<<scope->getName()<<"\n";
    // Obvious error
    if(tokens.size() == 0)
        ERROROUT(ParseDebugNoTokens, tokensToString(tokens));
    
    // Single word keywords
    if(tokens.size() == 1){
        std::string first_token = tokens[0];
        if(isReservedKeyword(first_token)){

            return scope;
        }
        
        ERROROUT(ParseDebugOneToken, tokensToString(tokens));
    }

    // Expressions, function calls, variables initialization, etc.
    bool first_token_is_type = isObjectType(tokens[0]);
    if(first_token_is_type){
        std::cout<<"######################\n";
        bool second_token_is_known_variable = scope->isKnownVariable(tokens[1]);
        std::cout<<"stikv="<<second_token_is_known_variable<<"\n";
        if(second_token_is_known_variable){
            ERROROUT(SyntaxErrorReinitializedVariable, tokensToString(tokens));
        }

        std::string type_string = tokens[0];
        std::string variable_name = tokens[1];
        initializeVariable(scope, type_string, variable_name);

        // if there are still tokens left
        if(tokens.size() > 2){
            std::vector<std::string> shifted_tokens = shiftTokens(tokens, 1);
            scope = buildVariableAndEvaluateExpressions(scope, shifted_tokens); // recurse and do it again now with var initialized
        }

        return scope;
    }

    bool first_token_is_keyword = isReservedKeyword(tokens[0]);
    if(first_token_is_keyword){
        enum ReservedKeyword keyword_type = getReservedKeyword(tokens[0]);

        if(keyword_type == RESERVED_FUNCTION){
            std::cout<<"<<<<GOING DOWN>>>>\n";

            std::string function_name = tokens[1];
            Function* new_function = new Function(function_name);  
            addFunctionToFunction(scope, new_function);
            std::cout<<"SCOPE WAS: "<<scope->getName()<<"\n";
            scope = new_function;
            std::cout<<"SCOPE IS NOW: "<<scope->getName()<<"\n";
            std::cout<<"WITH PARENT: "<<scope->getParent()->getName()<<"\n";
            std::cout<<"HAS PARENT: "<<scope->hasParent()<<"\n";

            return new_function;
        }

        if(keyword_type == RESERVED_END){
            bool has_parent = scope->hasParent();
            std::cout<<"&&&&&&&&has_parent="<<has_parent<<"\n";
            if(has_parent){
                scope = scope->getParent();
                std::cout<<"<<<<GOING UP>>>>\n";
            }
            else{
                ERROROUT(ParseErrorUnmatchedEnd, tokensToString(tokens));
            }

            return scope;
        }
        

        return scope;
    }

    Variable temp = Variable();
    bool first_token_is_known_variable = scope->getVariableRecursive(tokens[0], temp);
    if(first_token_is_known_variable){
        std::string variable_name = tokens[0];
        Variable expression_result = evaluateExpression(scope, tokens);
        scope->updateVariable(variable_name, expression_result);
        return scope;
    }

    return scope;
}