#include <iostream>

#include "utils.hpp"

std::string removeBracketing(std::string str_in, char bracket){
    if(str_in.length() < 2) return str_in;

    if(str_in.at(0) == bracket && str_in.at(str_in.length()-1) == bracket){
        return str_in.substr(1, str_in.length()-2);
    }
    return str_in;
}
std::string removeSingleQuotes(std::string str_in){
    if(str_in.length()==0) return "\0";
    return removeBracketing(str_in, '\'');
}
std::string removeDoubleQuotes(std::string str_in){
    return removeBracketing(str_in, '\"');
}

bool endsInJollyExtension(std::string str_in){
    std::string extension = ".jolly";
    int extension_length = (int)extension.length();
    if((int)str_in.length() < (extension_length + 1)) return false;

    int start_index = str_in.length() - extension_length;
    int end_index = str_in.length();
    std::string str_in_substr = str_in.substr(start_index, end_index);
    if(str_in_substr == extension) return true;
    return false;
}

std::string dropExtension(std::string str_in){
    int dot_index = -1;

    if(str_in.length() == 0) return str_in;

    for(int i = 0; i<(int)str_in.length(); i++){
        if(str_in.at(i) == '.'){
            dot_index = i;
            break;
        }
    }

    if(dot_index >= 0){
        return str_in.substr(0, dot_index);
    }
    return str_in;
}