#include <iostream>

#include "primtypes.hpp"
#include "variable.hpp"

Variable::Variable(){
    name = "null";
    type = Prim_Nothing;
}

Variable::Variable(std::string name){
    this->name = name;
    type = Prim_Nothing;
}

Variable::Variable(enum PrimType type){
    this->name = "null";
    this->type = type;
}

Variable::Variable(std::string name, enum PrimType type){
    this->name = name;
    this->type = type;
}

enum PrimType Variable::getType() const{
    return type;
}

void Variable::setName(std::string name){
    this->name = name;
}

std::string Variable::getName() const{
    return name;
}


std::string Variable::toString(){
    return "["+primType2Keyword(type)+"] "+name;
}

void Variable::dumpString(){
    std::cout<<toString()<<"\n";
}

std::string Variable::stringValue(){
    return "novalue";
}