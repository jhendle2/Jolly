#include "constants.hpp"

bool isObjectType(std::string s){
    return (s=="String" ||
        s=="Number" ||
        s=="Boolean" ||
        s=="Bool" ||
        s=="Character" ||
        s=="Nothing"
        );
}

bool isDigit(char d){
    switch(d){
        default:
            return false;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
    }
}

bool isChar(std::string s){
    if(s.length() > 2){
        if(s.at(0) == '\'' && s.at(s.length()-1) == '\''){
            return true;
        }
    }
    return false;
}

bool isString(std::string s){
    if(s.length() > 2){
        if(s.at(0) == '\"' && s.at(s.length()-1) == '\"'){
            return true;
        }
    }
    return false;
}

bool isNumber(std::string s){
    int length = s.length();
    for(int i = 0; i<length; i++){
        if(!isDigit(s.at(i))) return false;
    }
    return true;
}

bool isBool(std::string s){
    return s=="true" || s=="false" || s=="True" || s=="False";
}

bool isNothing(std::string s){
    return s=="Nothing";
}

enum ObjectType getTypeFromConstant(std::string str){

    if(isNumber(str))
        return TYPE_NUMBER;
    else if(isString(str))
        return TYPE_STRING;
    else if(isChar(str))
        return TYPE_CHAR;
    else if(isBool(str))
        return TYPE_BOOL;
    else if(isNothing(str))
        return TYPE_NOTHING;
    
    return TYPE_INVALID;
}

enum ObjectType getTypeFromString(std::string str){
    
    if(str == "Number")
        return TYPE_NUMBER;
    else if(str == "String")
        return TYPE_STRING;
    else if(str == "Char")
        return TYPE_CHAR;
    else if(str == "Bool" || str == "Boolean")
        return TYPE_BOOL;
    else if(str == "Nothing")
        return TYPE_NOTHING;
    
    return TYPE_INVALID;
}

std::string typeToString(enum ObjectType type){
    switch(type){
        case TYPE_NOTHING:
            return "Nothing";
        case TYPE_BOOL:
            return "Boolean";
        case TYPE_CHAR:
            return "Character";
        case TYPE_STRING:
            return "String";
        case TYPE_NUMBER:
            return "Number";
        case TYPE_OBJECT:
            return "Object";
        default:
        case TYPE_INVALID:
            return "Invalid";
    }
}