#include "variable_utils.hpp"
#include "variable.hpp"
#include "keywords.hpp"

bool VarUtils::isDigit(const char& c){
    return (
        c >= '0' && c <= '9'
    );
}

bool VarUtils::isNumber(const std::string& token){
    for(size_t i = 0; i<token.length(); i++){
        if(!isDigit(token.at(i))) return false;
    } return true;
}

bool VarUtils::isDecimal(const std::string& token){
    int dot_count = 0;
    for(const char& c : token){
        if(c == '.') dot_count++;
        else if(!isDigit(c)) return false;
    }
    return (dot_count <= 1);
}

bool VarUtils::isCharacter(const std::string& token){
    if(token.length() != 3) return false;

    if(token.at(0)=='\'' && token.at(2)=='\'') return true;
    return false;
}

bool VarUtils::isString(const std::string& token){
    if(token.length() < 2) return false;

    if(token.at(0)=='\"' && token.at(token.length()-1)=='\"') return true;
    return false;
}

bool VarUtils::isType(const std::string& token){
    return isVarType(token);
}

bool VarUtils::isBoolean(const std::string& token){
    return (
        token == KW_TRUE ||
        token == KW_TRUE_ALT ||
        token == KW_FALSE ||
        token == KW_FALSE_ALT
    );
}

char VarUtils::dropSingleQuotes(const std::string& token){
    if(VarUtils::isCharacter(token)){
        return token.substr(1).at(0);
    }
    return '\0';
}
std::string VarUtils::dropDoubleQuotes(const std::string& token){
    if(VarUtils::isString(token)){
        return token.substr(1, token.length()-2);
    }
    return "";
}

bool VarUtils::stringToBool(const std::string& token){
    return (
        token == KW_TRUE ||
        token == KW_TRUE_ALT
    );
}

VarType VarUtils::stringToVarType(const std::string& token){
    return getVarType(token);
}