#include <iostream>

#include "primtypes.hpp"
#include "variable.hpp"
#include "type.hpp"

Variable::Variable(){
    name = "constant";
    type = Prim_Nothing;
}

Variable::Variable(std::string name){
    this->name = name;
    type = Prim_Nothing;
}

Variable::Variable(enum PrimType type){
    this->name = "constant";
    this->type = type;
}

Variable::Variable(std::string name, enum PrimType type){
    this->name = name;
    this->type = type;
}

enum PrimType Variable::getPrimType() const{
    return type;
}

Type Variable::getType() const{
    return Type(type);
}

void Variable::setName(std::string name){
    this->name = name;
}

std::string Variable::getName() const{
    return name;
}


std::string Variable::toString(){
    return "["+primType2Keyword(type)+"] "+name+" = "+stringValue();
}

void Variable::dumpString(){
    std::cout<<toString()<<"\n";
}

std::string Variable::stringValue() const{
    return "novalue";
}