#include <iostream>

#include "errors.hpp"
#include "scope.hpp"
#include "function.hpp"

std::string scopeTypeToString(enum ScopeType type){
    switch(type){
        case SCOPE_CONDITIONAL:
            return "conditional";
        
        case SCOPE_FUNCTION:
            return "function";

        case SCOPE_NORMAL:
            return "scope";

        default:
            break;
    }
    return "invalid_scope";
}

Scope::Scope(std::string name){
    this->name = name;
    this->type = SCOPE_NORMAL;
    this->truthiness = true;
    this->parent = nullptr;
}

Scope::Scope(std::string name, enum ScopeType type){
    this->name = name;
    this->type = type;
    this->truthiness = true;
    this->parent = nullptr;
}

Scope::~Scope(){
    parent = nullptr;    

    for(auto pair : scopes){
        Scope* scope = pair.second;
        delete scope;
    }
}

void Scope::setScopeType(enum ScopeType type){
    this->type = type;
}
enum ScopeType Scope::getScopeType(){
    return this->type;
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

void Scope::setParent(Scope* parent){
    this->parent = parent;
}

Scope* Scope::getParent() const{
    return parent;
}

/************************************/
void Scope::dump(){
    std::cout<<"-----SCOPE ("<<name<<")-----\n";
    std::cout<<"\tparent=";
    if(parent == nullptr) std::cout<<"Null\n";
    else std::cout<<parent->getName()<<"\n";
    std::cout<<"\ttruthiness="<<(truthiness?"TRUE":"FALSE")<<"\n";
    
    std::cout<<"\n--VARIABLES ("<<variables.size()<<")--\n";
    for(auto pair : variables){
        Variable var = pair.second;
        std::cout<<"\t* ";
        pair.second.dumpString();
    }
    
    std::cout<<"\n--SUBSCOPES ("<<scopes.size()<<")--\n";
    for(auto pair : scopes){
        std::cout<<"\t* ["<<scopeTypeToString(
            pair.second->getScopeType())<<"] "<<pair.second->getName()<<"\n";
    }

    std::cout<<"\n-----END SCOPE ("<<name<<")-----\n";
}
void Scope::dumpRecursive(){
    dump();
    std::cout<<"\n";

    for(auto pair : scopes){
        enum ScopeType type = pair.second->getScopeType();
        if(type == SCOPE_FUNCTION){
            Function* func = (Function*)pair.second;
            func->dumpRecursive();
        }
        else{
            pair.second->dumpRecursive();
        }
        std::cout<<"\n";
    }
}

/************************************/

void Scope::addVariable(std::string name, Variable var){
    if(hasVariableRecursive(name)){
        updateVariableRecursive(name, var);
    }
    else{
        std::string local_name = this->name + "." + name;
        var.setName(local_name);
        variables.insert({local_name, var});
    }
}
void Scope::addVariable(Variable var){
    addVariable(var.getName(), var);
}
bool Scope::hasVariable(std::string name) const{
    std::string local_name = this->name + "." + name;
    return (variables.count(local_name) > 0);
}
bool Scope::hasVariableRecursive(std::string name) const{
    if(hasVariable(name)){
        return true;
    }
    else{
        if(parent == nullptr) return false;
        return parent->hasVariableRecursive(name);
    }
}
bool Scope::hasVariableExact(std::string name) const{
    return (variables.count(name) > 0);
}
bool Scope::hasVariableRecursiveExact(std::string name) const{
    if(hasVariableExact(name)){
        return true;
    }
    else{
        if(parent == nullptr) return false;
        return parent->hasVariableRecursiveExact(name);
    }
}
bool Scope::getVariable(std::string name, Variable& var){
    if(hasVariable(name)){
        std::string local_name = this->name + "." + name;
        var = variables[local_name]; // this operation means getVariable cannot be const
        return true;
    }
    return false;
}
bool Scope::getVariableRecursive(std::string name, Variable& var){
    if(hasVariable(name)){
        return getVariable(name, var);
    }

    if(parent != nullptr){
        return parent->getVariableRecursive(name, var);
    }
    return false;
}
void Scope::updateVariable(std::string name, Variable var){
    if(hasVariableExact(name)){
        var.setName(name);
        variables[name] = var;
    }
    else if(hasVariable(name)){
        std::string local_name = this->name + "." + name;
        var.setName(local_name);
        variables[local_name] = var; // this operation means getVariable cannot be const
    }
    else{
        addVariable(name, var);
    }
}
void Scope::updateVariable(Variable var){
    updateVariable(var.getName(), var);
}
void Scope::updateVariableRecursive(std::string name, Variable var){
    if(hasVariableExact(name) || hasVariable(name)){
        updateVariable(name, var);
    }
    else if(hasVariableRecursiveExact(name) || hasVariableRecursive(name)){
        parent->updateVariableRecursive(name, var);
    }
    else{
        addVariable(name, var);
    }
}
void Scope::updateVariableRecursive(Variable var){
    updateVariableRecursive(var.getName(), var);
}

Variable& Scope::getVariableRef(std::string name){
    if(hasVariable(name)){
        std::string local_name = this->name + "." + name;
        Variable& ref = variables[local_name];
        return ref;
    }
    if(hasVariableRecursive(name)){
        return parent->getVariableRef(name);
    }
    ERROR(SyntaxErrorUnrecognizedObject);
    static Variable out = Variable();
    return out;
}

/************************************/

void Scope::addScope(std::string name, Scope* scope){
    if(hasScopeRecursive(name)){
        updateScopeRecursive(name, scope);
    }
    else{
        std::string local_name = this->name + "." + name;
        scope->setName(local_name);
        scopes.insert({local_name, scope});
    }
}

void Scope::addScope(Scope* scope){
    addScope(scope->getName(), scope);
}

bool Scope::hasScope(std::string name) const{
    std::string local_name = this->name + "." + name;
    return (scopes.count(local_name) > 0);
}

bool Scope::hasScopeRecursive(std::string name) const{
    if(hasScope(name)){
        return true;
    }
    else{
        if(parent == nullptr) return false;
        return parent->hasScopeRecursive(name);
    }
}

bool Scope::getScope(std::string name, Scope*& scope){
    if(hasScope(name)){
        std::string local_name = this->name + "." + name;
        scope = scopes[local_name];
        return true;
    }
    return false;
}

bool Scope::getScopeRecursive(std::string name, Scope*& scope){
    if(hasScope(name)){
        return getScope(name, scope);
    }

    if(parent != nullptr){
        return parent->getScopeRecursive(name, scope);
    }
    return false;
}

void Scope::updateScope(std::string name, Scope* scope){
    if(hasVariable(name)){
        std::string local_name = this->name + "." + name;
        scopes[local_name] = scope;
    }
    else{
        addScope(name, scope);
    }
}

void Scope::updateScope(Scope* scope){
    updateScope(scope->getName(), scope);
}

void Scope::updateScopeRecursive(std::string name, Scope* scope){
    if(hasScope(name)){
        updateScope(name, scope);
    }
    else if(hasScopeRecursive(name)){
        parent->updateScopeRecursive(name, scope);
    }
    else{
        addScope(name, scope);
    }
}

void Scope::updateScopeRecursive(Scope* scope){
    updateScopeRecursive(scope->getName(), scope);
}

/************************************/

void checkNullScope(Scope* scope){
    if(scope == nullptr){
        ERROR(ParseErrorScopeDoesNotExist);
    }
}

void addScopeToScope(Scope*& parent, Scope* child){
    child->setParent(parent);
    parent->addScope(child);
}