#include "general_utils.hpp"

bool hasQuotes(std::string s){
    return (
        s.length() > 2 &&
        s.at(0) == '\"' &&
        s.at(s.length()-1) == '\"'
    );
}

std::string stripQuotes(std::string s){
    if(s.length() >= 3){
        if(s.at(0)=='\"' && s.at(s.length()-1)=='\"')
            return s.substr(1,s.length()-2);
    }
    return s;
}
