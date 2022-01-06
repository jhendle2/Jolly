#include "boolean.hpp"

Boolean::Boolean() : Variable(TYPE_BOOL){

}

Boolean::Boolean(const bool boolean) : Variable(boolean){
    
}

Boolean::Boolean(const char* string) : Variable(TYPE_BOOL){
    std::string bool_as_str = string;
    boolean = (bool_as_str=="true" || bool_as_str=="True") ? true : false;
}

Boolean::Boolean(const std::string string) : Variable(TYPE_BOOL){
    boolean = (string=="true" || string=="True") ? true : false;
}

Boolean::Boolean(const Variable& var) : Variable(TYPE_BOOL){
    Variable temp = var;
    boolean = temp.getBoolean();
}

Boolean Boolean::add(const Boolean& right){
    Boolean out = Boolean(boolean);
    out.boolean |= right.boolean;
    return out;
}

Boolean Boolean::addEq(const Boolean& right){
    Boolean out = Boolean(boolean);
    out.boolean |= right.boolean;
    boolean = out.boolean;
    return out;
}