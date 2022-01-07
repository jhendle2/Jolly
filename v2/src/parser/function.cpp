#include "function.hpp"

Function::Function() : Scope("unnamed_function", SCOPE_FUNCTION){
    this->return_type = TYPE_NOTHING;
    this->return_variable = Variable(TYPE_NOTHING);
}

Function::Function(std::string name) : Scope(name, SCOPE_FUNCTION){
    this->return_type = TYPE_NOTHING;
    this->return_variable = Variable(TYPE_NOTHING);
}

Function::Function(std::string name, enum ObjectType return_type) : Scope(name, SCOPE_FUNCTION){
    this->name = name;
    this->return_type = return_type;
    this->return_variable = Variable(return_type);
}

enum ObjectType Function::getReturnType(){
    return return_type;
}
Object Function::getReturn(){
    return return_variable;
}

void Function::dump(){
    std::cout<<"\n===========FUNCTION("<<name<<")===========\n";
    if(parent != nullptr) std::cout<<"PARENT FUNCTION: "<<parent->getName()<<"\n";
    else std::cout<<"NO PARENT!\n";
    std::cout<<"##RETURNS: "<<typeToString(return_type)<<"\n";
    std::cout<<"##VARIABLES##:\n";
    variables.dump(); std::cout<<"\n\n";
    std::cout<<"##SCOPES##:\n";
    std::cout<<"\n------------------------------------------\n";
    for(auto pair : scopes){
        std::cout<<"* "<<pair.second->getName()<<"\n";
    }
    std::cout<<"\n==========================================\n";
}

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
