#include <iostream>

#include "function.hpp"

Function::Function() : BaseFunction("invalid_function", TYPE_NOTHING){
    
}

Function::~Function(){

}

Function::Function(std::string name) : BaseFunction(name, TYPE_NOTHING){
    
}

Function::Function(std::string name, enum ObjectType return_type) : BaseFunction(name, return_type){
    
}

Function::Function(std::string name, std::vector<Object> params) : BaseFunction(name, TYPE_NOTHING){

}

Function::Function(std::string name, enum ObjectType return_type, std::vector<Object> params) : BaseFunction(name, return_type){

}

// Function::Function(const BaseFunction& bf) : BaseFunction(bf.getReturnType()){

// }

void Function::addParameter(Object param){
    params[param.getName()] = param;
}

void Function::addParameter(std::string name, Object value){
    params[name] = value;
}

Object Function::getParameter(std::string name){
    return params[name];
}

void Function::setParameter(std::string name, Object value){
    params[name] = value;
}

void Function::evaluateInner(){

}


void Function::dump(){
    std::cout<<"\n===========FUNCTION("<<name<<")===========\n";
    variables.dump(); std::cout<<"\n\n";
    std::cout<<"\n==========================================\n";
}

void Function::addVariable(Variable var){
    var.setAccess(PRIVATE);
    variables.add(var);
}

void Function::addVariable(enum AccessSpecifier access, Variable var){
    var.setAccess(access);
    variables.add(var);
}

Variable Function::getVariable(std::string name){
    Variable var = variables.get(name);
    return var; //variables.get(name);
}