#include <iostream>
#include <stdlib.h>

#include "variable.hpp"

Variable::Variable() : Object(){
    number = 0;
    character = '\0';
    boolean = false;
    string = "";
}

Variable::~Variable(){
    
}

Variable::Variable(enum ObjectType type) : Object(type){
    number = 0;
    character = '\0';
    boolean = false;
    string = "";
}


Variable::Variable(const int number) : Object(TYPE_NUMBER){
    this->number = number;
    character = '\0';
    boolean = false;
    string = "";
}

Variable::Variable(const bool boolean) : Object(TYPE_BOOL){
    number = 0;
    character = '\0';
    this->boolean = boolean;
    string = "";
}

Variable::Variable(const char character) : Object(TYPE_CHAR){
    number = 0;
    this->character = character;
    boolean = false;
    string = "";
}

Variable::Variable(const char* string) : Object(TYPE_STRING){
    number = 0;
    character = '\0';
    boolean = false;
    this->string = string;
}

Variable::Variable(const std::string string) : Object(TYPE_STRING){
    number = 0;
    character = '\0';
    boolean = false;
    this->string = string;
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

std::string Variable::toStringValue(){
    std::string char_as_str{character};
    switch(type){
        case TYPE_BOOL:
            return (boolean?"True":"False");
        case TYPE_STRING:
            return string;
        case TYPE_CHAR:
            return char_as_str;
        case TYPE_NUMBER:
            return std::to_string(number);
        default:
            return "nothing";
    }
}

std::string Variable::toString(){
    std::string value_str = "";
    std::string char_as_str{character};
    switch(type){
        case TYPE_BOOL:
            value_str = (boolean?"True":"False");
            break;
        case TYPE_STRING:
            value_str = "\"" + string + "\"";
            break;
        case TYPE_CHAR:
            value_str = "\'" + char_as_str + "\'";
            break;
        case TYPE_NUMBER:
            value_str = std::to_string(number);
            break;
        default:
            value_str = "nothing";
            break;
    }
    std::string str = "<" + accessToString(access) + "> " + name+" ["+typeToString(type)+"]" + " = " + value_str;
    return str;
}
void Variable::dump(){
    std::cout<<toString();
}

Variable Variable::eq(const Variable& right){
    //DO NOT SET NAME
    this->number = right.number;
    this->boolean = right.boolean;
    this->string = right.string;
    this->character = right.character;

    return right;
}

Variable Variable::equality(const Variable& right){
    if(type == right.type){
        switch(type){
            case TYPE_BOOL: return Variable(boolean == right.boolean);
            case TYPE_CHAR: return Variable(character == right.character);
            case TYPE_NUMBER: return Variable(number == right.number);
            case TYPE_STRING: return Variable(string == right.string);
            default: break;
        }
    }
    return Variable(false);
}

Variable Variable::inequality(const Variable& right){
    if(type == right.type){
        switch(type){
            case TYPE_BOOL: return Variable(boolean != right.boolean);
            case TYPE_CHAR: return Variable(character != right.character);
            case TYPE_NUMBER: return Variable(number != right.number);
            case TYPE_STRING: return Variable(string != right.string);
            default: break;
        }
    }
    // Lol, should this be true or false?
    return Variable(false);
}

Variable Variable::add(const Variable& right){
    return right;
}

Variable Variable::addEq(const Variable& right){

    return right;
}