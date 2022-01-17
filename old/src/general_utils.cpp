#include "general_utils.hpp"
#include "expressions.hpp"

std::string dropFileExtension(std::string filename){
    int dot_index = (int)filename.find('.');
    if(dot_index >= 0){
        return filename.substr(0,dot_index); // I think this is more correct
        // return filename.substr(0,dot_index-1);
    }
    return filename;
}

bool hasQuotes(std::string s){
    return (
        s.length() > 2 &&
        ((s.at(0) == '\"' &&
        s.at(s.length()-1) == '\"') ||
        (s.at(0) == '\'' &&
        s.at(s.length()-1) == '\''))
    );
}

std::string stripQuotes(std::string s){
    if(s.length() >= 3){
        if(s.at(0)=='\"' && s.at(s.length()-1)=='\"'){
            return s.substr(1,s.length()-2);
        }
        else if(s.at(0)=='\'' && s.at(s.length()-1)=='\''){
            return s.substr(1,s.length()-2);
        }
    }
    return s;
}

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

std::string tokensToLine(std::vector<std::string> tokens){
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

bool tokensIsList(std::vector<std::string> tokens){
    for(std::string token : tokens){
        if(token == ",")
            return true;
    }
    return false;
}

std::vector<std::vector<std::string>> listToListOfTokens(std::vector<std::string> tokens){
    std::vector<std::vector<std::string>> list_of_token_lists;
    std::vector<std::string> temp_tokens;

    for(std::string token : tokens){
        if(token == ","){
            list_of_token_lists.push_back(temp_tokens);
            temp_tokens.clear();
        }
        else{
            temp_tokens.push_back(token);
        }
    }
    list_of_token_lists.push_back(temp_tokens);
    return list_of_token_lists;
}