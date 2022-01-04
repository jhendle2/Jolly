#include <iostream>
#include <stdlib.h>

#include "general_utils.hpp"
#include "variable.hpp"

bool isVariableType(std::string str){
    return (
        str=="Number" ||
        str=="String" ||
        str=="Bool"   ||
        str=="Char"
    );
}

int Variable::getNumber(){
    return number;
}
bool Variable::getBoolean(){
    return boolean;
}
char Variable::getCharacter(){
    return character;
}
std::string Variable::getString(){
    return string;
}

Variable::Variable(){
    this->initialized = false;
    this->type = TYPE_NOTHING;
}

Variable::Variable(enum Type type){
    this->initialized = false;
    this->type = type;
}

Variable::Variable(const int number){
    this->initialized = true;
    this->type = TYPE_NUMBER;
    this->number = number;
}

Variable::Variable(const char character){
    this->initialized = true;
    this->type = TYPE_CHAR;
    this->character = character;
}

Variable::Variable(const bool boolean){
    this->initialized = true;
    this->type = TYPE_BOOL;
    this->boolean = boolean;
}

Variable::Variable(const char* string){
    this->initialized = true;
    this->type = TYPE_STRING;
    this->string = string;
}

void Variable::set(const int number){
    this->initialized = true;
    this->number = number; 
}

void Variable::set(const char character){
    this->initialized = true;
    this->character = character;
}

void Variable::set(const bool boolean){
    this->initialized = true;
    this->boolean = boolean;
}

void Variable::set(const char* string){
    this->initialized = true;
    this->string = string;
}

void Variable::set(const Variable& right){
    this->initialized = right.initialized;
    this->type = right.type;
    this->number = right.number;
    this->boolean = right.boolean;
    this->character = right.character;
    this->string = right.string;
}

void Variable::setFromString(std::string value){
    if(isString(value)){
        this->string = stripQuotes(value);
    }
    else if(isChar(value)){
        this->character = value[1];
    }
    else if(isNumber(value)){
        this->number = atoi(value.c_str());
    }
    else if(isBool(value)){
        this->boolean = value=="true" || value=="True" ? true : false;
    }
    this->initialized = true;
}

bool Variable::isInitialized(){
    return initialized;
}

enum Type Variable::getType(){
    return this->type;
}

std::string Variable::toString(){
    enum Type type = this->type;

    if(type==TYPE_NOTHING){
        return "\\0";
    }
    else if(type==TYPE_BOOL){
        return boolean?"true":"false";
    }
    else if(type==TYPE_CHAR){
        std::string out{character};
        return out;
    }
    else if(type==TYPE_NUMBER){
        return std::to_string(number);
    }
    else if(type==TYPE_STRING){
        return string;
    }

    return "ERROR";
}

std::string Variable::dump(){
    if(type==TYPE_STRING)
        return "[" + typeToString(type) + "]" + " = \"" + toString() + "\"";
    else if(type==TYPE_CHAR)
        return "[" + typeToString(type) + "]" + " = \'" + toString() + "\'";    
    else
        return "[" + typeToString(type) + "]" + " = " + toString();
}

bool Variable::canMergeWith(const Variable& right){
    return this->type == right.type;
}

#include "errors.hpp"
void Variable::merge(const Variable& right){
    if(canMergeWith(right)){
        if(this->type == TYPE_NUMBER){
            int temp = number + right.number;
            number = temp;
        }
        else if(this->type == TYPE_STRING){
            std::string temp = string + right.string;
            string = temp;
        }
    }
    else{
        Variable v = right;
        std::cout << "\n" << SyntaxErrorBadOperation << toString() << " + " << v.toString() << "\n";
        exit(EXIT_FAILURE);
    }
}

void Variable::addEq(const Variable& right){
    return;
}
void Variable::subtractEq(const Variable& right){
    return;
}
void Variable::multiplyEq(const Variable& right){
    return;
}
void Variable::divideEq(const Variable& right){
    return;    
}
void Variable::modEq(const Variable& right){
    return;
}
void Variable::powerEq(const Variable& right){
    return;
}
Variable Variable::add(const Variable& right){
    return Variable();
}
Variable Variable::subtract(const Variable& right){
    return Variable();
}
Variable Variable::multiply(const Variable& right){
    return Variable();
}
Variable Variable::divide(const Variable& right){
    return Variable(); 
}
Variable Variable::mod(const Variable& right){
    return Variable();
}
Variable Variable::power(const Variable& right){
    return Variable();
}
void Variable::increment(){
    return;    
}
void Variable::decrement(){
    return;
}
Variable Variable::eq(const Variable& right){
    set(right);
    return right;
}

Variable Variable::equality(const Variable& right){
    if(type != right.type) return Variable(false);

    switch(type){
        case TYPE_NOTHING:
            return true;
        case TYPE_BOOL:
            return Variable(boolean==right.boolean);
        case TYPE_CHAR:
            return Variable(character==right.character);
        case TYPE_NUMBER:
            return Variable(number==right.number);
        case TYPE_STRING:
            return Variable(string==right.string);
        default:
        case TYPE_INVALID:
            return Variable(false);
    }
}
Variable Variable::inequality(const Variable& right){
    return Variable(!equality(right).boolean);
}
Variable Variable::less(const Variable& right){
    if(type != right.type) return false;

    switch(type){
        case TYPE_BOOL:
            return Variable(boolean<right.boolean);
        case TYPE_CHAR:
            return Variable(character<right.character);
        case TYPE_NUMBER:
            return Variable(number<right.number);
        default:
        case TYPE_STRING:
        case TYPE_NOTHING:
        case TYPE_INVALID:
            return Variable(false);
    }
}
Variable Variable::greater(const Variable& right){
    if(type != right.type) return false;

    switch(type){
        case TYPE_BOOL:
            return Variable(boolean>right.boolean);
        case TYPE_CHAR:
            return Variable(character>right.character);
        case TYPE_NUMBER:
            return Variable(number>right.number);
        default:
        case TYPE_STRING:
        case TYPE_NOTHING:
        case TYPE_INVALID:
            return Variable(false);
    }
}
Variable Variable::lessEq(const Variable& right){
    return Variable(!greater(right).boolean);    
}

Variable Variable::greaterEq(const Variable& right){
    return Variable(!less(right).boolean);  
}