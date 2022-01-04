#include "general_utils.hpp"

std::string stripQuotes(std::string s){
    if(s.length() < 3) return s;
    else{
        return s.substr(1,s.length()-2);
    }
}
