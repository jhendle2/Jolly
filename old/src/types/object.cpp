#include <iostream>

#include "object.hpp"

std::string accessToString(enum AccessSpecifier access){
    switch(access){
        case PUBLIC:
            return "public";
        case PRIVATE:
            return "private";
        case PROTECTED:
            return "protected";
        default:
            return "invalidaccess";
    }
}

Object::Object(){
    is_initialized = false;
    access = PRIVATE;
    type = TYPE_NOTHING;
    name = "none";
}

Object::Object(enum ObjectType type){
    is_initialized = false;
    access = PRIVATE;
    this->type = type;
    name = "none";
}

Object::Object(std::string name){
    is_initialized = false;
    access = PRIVATE;
    type = TYPE_NOTHING;
    this->name = name;
}

Object::Object(std::string name, enum ObjectType type){
    is_initialized = false;
    access = PRIVATE;
    this->type = type;
    this->name = name;
}

void Object::initialize(){
    is_initialized = true;
}

bool Object::isInitialized(){
    return is_initialized;
}

void Object::setAccess(enum AccessSpecifier access){
    this->access = access;
}

void Object::setPublic(){
    access = PUBLIC;
}

void Object::setPrivate(){
    access = PRIVATE;
}

void Object::setProtecte(){
    access = PROTECTED;
}


enum AccessSpecifier Object::getAccess(){
    return access;
}

enum ObjectType Object::getType(){
    return type;
}

void Object::setName(const char* name){
    this->name = name;
}
void Object::setName(std::string name){
    this->name = name;
}
std::string Object::getName(){
    return name;
}

std::string Object::toString(){
    std::string str = "<" + accessToString(access) + "> " + name +" ["+typeToString(type)+"]";
    return str;
}
void Object::dump(){
    std::cout<<toString();
}