#include "string.hpp"
#include "general_utils.hpp"

String::String() : Variable(TYPE_STRING){

}

String::String(const char* string) : Variable(TYPE_STRING){
    this->string = string;
    if(hasQuotes(string))
        this->string = stripQuotes(this->string);
}

String::String(const std::string string) : Variable(TYPE_STRING){
    this->string = string;
    if(hasQuotes(string))
        this->string = stripQuotes(this->string);
}

String::String(const Variable& var) : Variable(TYPE_STRING){
    Variable temp = var;
    string = temp.getString();
}

Variable String::add(const Variable& right){
    Variable var = right;
    String out = String(string);
    out.string += var.toStringValue();
    return out;
}

Variable String::addEq(const Variable& right){
    Variable var = right;
    string += var.toStringValue();
    return String(string);    
}

Variable String::mul(const Variable& right){
    Variable var = right;
    String out = String(string);
    std::string string_temp = out.string;
    for(int i = 1; i<var.getNumber(); i++){
        out.string += string_temp; 
    }
    return out;
}

Variable String::mulEq(const Variable& right){
    Variable var = right;
    std::string string_temp = string;
    for(int i = 1; i<var.getNumber(); i++){
        string += string_temp; 
    }
    return String(string);   
}