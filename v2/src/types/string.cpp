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
    String out = String(number);
    out.string += var.toStringValue();
    return out;
}

Variable String::addEq(const Variable& right){
    Variable var = right;
    string += var.toStringValue();
    return String(string);    
}