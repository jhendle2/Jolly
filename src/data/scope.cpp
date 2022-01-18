#include <iostream>

#include "scope.hpp"

Scope::Scope(std::string name){
    this->name = name;
    this->type = SCOPE_NORMAL;
    this->truthiness = true;
}

Scope::Scope(std::string name, enum ScopeType type){
    this->name = name;
    this->type = type;
    this->truthiness = true;
}

void Scope::setTruthiness(bool truthiness){
    this->truthiness = truthiness;
}

bool Scope::getTruthiness() const{
    return truthiness;
}


void Scope::setName(std::string name){
    this->name = name;
}

std::string Scope::getName() const{
    return name;
}
