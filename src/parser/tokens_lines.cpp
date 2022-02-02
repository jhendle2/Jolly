#include "tokens_lines.hpp"
#include "operators_delimiters.hpp"

bool validTokensLength(const Tokens& tokens){
    return (tokens.size() > 0);
}

Tokens tokenizeLine(const std::string& line){
    Tokens tokens;
    std::string temp = "";

    bool inside_string = false;
    bool inside_character = false;
    for(int i = 0; i<(int)line.length(); i++){
        char c = line[i];

        if(c == '\"'){
            if(!inside_character){
                temp += "\"";
                if(inside_string){
                    inside_string = false;
                    goto ADD_TOKEN;
                }
                else{
                    inside_string = true;
                }
            } 
        }
        else if(c == '\''){
            if(!inside_string){
                temp += "\'";
                if(inside_character){
                    inside_character = false;
                    goto ADD_TOKEN;
                }
                else{
                    inside_character = true;
                }
            } 
        }

        else if(c == ' ' || c == '\t'){
            if(inside_character || inside_string){
                temp += c;
            }
            else goto ADD_TOKEN;
        }

        else if(isOperator(c)){
            if(inside_character || inside_string){
                temp += c;
            }
            else{
                if(temp != ""){
                    tokens.push_back(temp);
                    temp = "";
                }
                temp += c;

                if(i < (int)line.length()-1){
                    if(isOperator(line[i+1])){
                        temp += line[i+1];
                        i++;
                    }
                }

                goto ADD_TOKEN;
            } 
        }

        else if(c == DELIM_DOT){
            if(inside_character || inside_string){
                temp += c;
            }
            else{
                if(i > 1){
                    if(isDigit(line[i+1])){
                        temp += c;
                    }
                }
                else if(i < (int)line.length()-1){
                    if(isDigit(line[i+1])){
                        temp += c;
                    }
                }
                else{
                    if(temp != ""){
                        tokens.push_back(temp);
                        temp = "";
                    }
                    temp += c;
                    goto ADD_TOKEN;
                }
            }
        }

        else if(isDelimiter(c)){
            if(inside_character || inside_string){
                temp += c;
            }
            else{
                if(temp != ""){
                    tokens.push_back(temp);
                    temp = "";
                }
                temp += c;
                goto ADD_TOKEN;
            } 
        }

        else{
            temp += c;
        }
    continue;

    ADD_TOKEN:
        if(temp!=""){
            tokens.push_back(temp);
            temp = "";
        }
    }

    if(temp != ""){
        tokens.push_back(temp);
    }
    return tokens;
}

std::string tokensToString(const Tokens& tokens){
    std::string out = "";
    for(std::string token : tokens){
        out += "[" + token + "] ";
    }
    return out;
}

std::string tokensToLine(const Tokens& tokens){
    std::string out = "";
    for(std::string token : tokens){
        // out += token + " ";
        out += token + "_";
    }
    if(out.length() > 1) out = out.substr(0, out.length() - 1);
    return out;
}

Tokens shiftTokens(const Tokens& tokens, const int& shift){
    Tokens shifted;
    int count = 0;
    for(std::string token : tokens){
        if(count>=shift) shifted.push_back(token);
        count++;
    }
    return shifted;
}