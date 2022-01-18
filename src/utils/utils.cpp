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