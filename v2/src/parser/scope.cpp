#include <iostream>

#include "errors.hpp"
#include "scope.hpp"

std::string scopeTypeToString(enum ScopeType scope_type){
    switch(scope_type){
        case SCOPE_NORMAL:
            return "scope";
        case SCOPE_IF:
            return "if";
        case SCOPE_ELSIF:
            return "elsif";
        case SCOPE_ELSE:
            return "else";
        case SCOPE_FUNCTION:
            return "function";
        case SCOPE_CLASS:
            return "class";
        default:
            return "invalid";
    }
}

Scope::Scope() : Object("unnamed_scope", TYPE_SCOPE){
    last_scope_index = 0;
    this->scope_type = SCOPE_NORMAL;
    parent=nullptr;
    next_scope=nullptr;
    truthiness=true;
    is_main_scope = false;
}

Scope::Scope(enum ScopeType scope_type) : Object("unnamed_scope", TYPE_SCOPE){
    last_scope_index = 0;
    this->scope_type = scope_type;
    parent=nullptr;
    next_scope=nullptr;
    truthiness=true;
    is_main_scope = false;
}

Scope::Scope(std::string name) : Object(name, TYPE_SCOPE){
    last_scope_index = 0;
    this->scope_type = SCOPE_NORMAL;
    parent=nullptr;
    next_scope=nullptr;
    truthiness=true;
    is_main_scope = false;
}

Scope::Scope(std::string name, enum ScopeType scope_type) : Object(name, TYPE_SCOPE){
    last_scope_index = 0;
    this->scope_type = scope_type;
    parent=nullptr;
    next_scope=nullptr;
    truthiness=true;
    is_main_scope = false;
}

Scope::~Scope(){
    // we don't want to DELETE or FREE parent because it might have other children
    // as such, we just want to set our local parent to a nullptr just in case.
    parent=nullptr;
    if(next_scope != nullptr){
        delete next_scope;
        next_scope=nullptr;
    }

    for(auto pair : scopes){
        Scope* temp = pair.second;
        if(temp != nullptr){
            delete temp; // here we actually want to delete the scopes because they only exist locally
            temp=nullptr; // and here is some extra cleanup, which might not be necessary
        }
    }
    scopes.clear(); // dump the vector
}

void Scope::setMainScope(){
    is_main_scope = true;
}

void Scope::setScopeType(enum ScopeType scope_type){
    this->scope_type = scope_type;
}
enum ScopeType Scope::getScopeType(){
    return scope_type;
}

// void Scope::evaluate(){

// }

void Scope::setParent(Scope* parent){
    if(this->parent == nullptr)
        this->parent = new Scope();
    this->parent = parent;
}
Scope* Scope::getParent(){
    return parent;
}
bool Scope::hasParent(){
    return (parent!=nullptr);
}

ObjectTable<Variable>& Scope::getVariables(){
    return variables;
}

void Scope::addVariable(Variable var){
    var.setAccess(PRIVATE);
    variables.add(var);
}

void Scope::addVariable(std::string name, Variable var){
    var.setAccess(PRIVATE);
    var.setName(name);
    variables.add(var);
}

void Scope::addVariable(enum AccessSpecifier access, Variable var){
    var.setAccess(access);
    variables.add(var);
}

void Scope::addVariable(std::string name, enum AccessSpecifier access, Variable var){
    var.setAccess(access);
    var.setName(name);
    variables.add(var);
}

void Scope::updateVariable(Variable var){
    variables.update(var);
}

void Scope::updateVariable(std::string name, Variable var){
    variables.update(name, var);
}

void Scope::updateVariableRecursive(std::string name, Variable var){
    if(variables.isKnown(name)){
        variables.update(name, var);
        return;
    }

    if(hasParent()){
        parent->updateVariableRecursive(name, var);
    }
}

void Scope::updateVariableRecursive(Variable var){
    updateVariableRecursive(var.getName(), var);
}

bool Scope::getTruthiness(){
    return truthiness;
}

void Scope::setTruthiness(bool truthiness){
    this->truthiness = truthiness;
}

Variable Scope::updateVariableAndGetRecursive(std::string name, Variable var){
    if(variables.isKnown(name)){
        Variable v = variables.updateAndGet(name, var);
        return v;
    }

    if(hasParent()){
        Variable v = parent->updateVariableAndGetRecursive(name, var);
        return v;
    }

    return var;
}

Variable Scope::updateVariableAndGetRecursive(Variable var){
    return updateVariableAndGetRecursive(var.getName(), var);
}


Variable Scope::updateVariableAndGet(Variable var){
    variables.update(var);
    return var;
}

Variable Scope::getVariable(std::string name){
    Variable var = variables.get(name);
    return var; //variables.get(name);
}

bool Scope::getVariableRecursive(std::string name, Variable& var){
    if(variables.isKnown(name)){
        var = variables.get(name);
        return true;
    }

    if(hasParent()){
        return parent->getVariableRecursive(name, var);
    }

    return false;
}

/*****************************************/

void Scope::addScope(Scope scope){
    scope.setAccess(PRIVATE);
    Scope* temp = new Scope(scope);
    scopes[scope.getName()] = temp;
    last_scope_index++;
}

void Scope::addScope(enum AccessSpecifier access, Scope scope){
    scope.setAccess(access);
    Scope* temp = new Scope(scope);
    scopes[scope.getName()] = temp;
    last_scope_index++;
}

void Scope::addScope(Scope* scope){
    scope->setAccess(PRIVATE);
    scopes[scope->getName()] = scope;
    last_scope_index++;
}

void Scope::addScope(enum AccessSpecifier access, Scope* scope){
    scope->setAccess(access);
    scopes[scope->getName()] = scope;
    last_scope_index++;
}

void Scope::updateScope(std::string name, Scope scope){
    *(scopes[name]) = scope;
}

void Scope::updateScopeRecursive(std::string name, Scope scope){
    if(hasScope(name)){
        *(scopes[name]) = scope;
        return;
    }

    if(hasParent()){
        parent->updateScopeRecursive(name, scope);
    }
}

bool Scope::hasScope(std::string name){
    bool out = (scopes.count(name) > 0);
    return out;
}

bool Scope::hasScopeRecursive(std::string name){
    if(hasScope(name)) return true;

    if(parent != nullptr){
        if(hasScope(name)) return true;
        else return hasScopeRecursive(name);
    }
    return false;
}

Scope* Scope::getScope(std::string name){
    if(hasScope(name)){
        Scope* out = scopes[name];
        return out; 
    }
    else{
        return nullptr;
    }
    return new Scope();
}

Scope* Scope::getScopeRecursive(std::string name){

    // if(variables.isKnown(name)){
    // if(variables.isKnown(name)){
    //     var = variables.get(name);
    //     return true;
    // }

    // if(hasParent()){
    //     return parent->getVariableRecursive(name, var);
    // }

    // return false;

    // dumpRecursive();
    std::string local_name = this->name + "." + name;

    if(hasScope(local_name)){
        Scope* temp = getScope(local_name);
        return temp;
    }

    if(hasParent()){
        Scope* temp = parent->getScopeRecursive(name);
        return temp;
    }

    std::cout<<"!!something went hella wrong\n";
    return nullptr;
}

Scope* Scope::updateAndGetScope(std::string name, Scope scope){
    if(hasScope(name)){
        updateScope(name, scope);
        return getScope(name);
    }

    ERROROUT(ParseErrorUnknownWithinScope, name);
    return new Scope();
}

Scope* Scope::updateAndGetScopeRecursive(std::string name, Scope scope){
    if(hasScope(name)){
        updateScope(name, scope);
        return getScope(name);
    }

    if(hasParent()){
        return parent->updateAndGetScopeRecursive(name, scope);
    }
    
    ERROROUT(ParseErrorUnknownWithinScope, name);
    return new Scope();
}

int Scope::lastScopeIndex(){
    return last_scope_index;
}

/*****************************************/

void Scope::dump(){
    std::cout<<"\n===========SCOPE("<<name<<")===========\n";
    std::cout<<"##SCOPE_TYPE: "<<scopeTypeToString(getScopeType())<<"\n";

    if(parent != nullptr) std::cout<<"PARENT SCOPE: "<<parent->getName()<<"\n";
    else std::cout<<"NO PARENT!\n";

    std::cout<<"##VARIABLES##:\n";
    variables.dump(); std::cout<<"\n\n";
    
    std::cout<<"##SCOPES##:\n";
    std::cout<<"\n------------------------------------------\n";
    for(auto pair : scopes){
        std::cout<<"* "<<pair.second->getName()<<" <"<<scopeTypeToString(pair.second->getScopeType())<<">\n";
    }
    std::cout<<"\n==========================================\n";
}

void Scope::dumpRecursive(){
    std::cout<<"{{{{{{{{{{{{{{{{{{{{{{{{\n";
    dump();

    for(auto pair : scopes){
        std::cout<<"\n";
        pair.second->dumpRecursive();
    }

    std::cout<<"}}}}}}}}}}}}}}}}}}}}}}}}\n";
}

 // Do I have this variable or scopetion?
bool Scope::isKnown(std::string name){
    return variables.isKnown(name) || hasScope(name);
}

bool Scope::isKnownVariable(std::string name){
    return variables.isKnown(name);
}

void Scope::addNextScope(Scope* next_scope){
    if(this->next_scope == nullptr){
        this->next_scope = next_scope;
    }
}

bool Scope::getNextScope(Scope* next_scope){
    if(this->next_scope != nullptr){
        next_scope = this->next_scope;
        return true;
    }
    return false;
}

bool Scope::hasNextScope(){
    return (next_scope != nullptr);
}

// Do I have this variable or scopetion? If yes --> return TYPE_VARIABLE or TYPE_FUNCTION. If not, TYPE_INVALID
enum ObjectType Scope::isKnownAndType(std::string name){
    if(variables.isKnown(name)) return TYPE_VARIABLE;
    else if(hasScope(name)) return TYPE_FUNCTION;
    else return TYPE_INVALID;
}

void addScopeToScope(Scope& parent, Scope& child){
    child.setName(parent.getName()+"."+child.getName());
    child.setParent(&parent);
    parent.addScope(child);
}

void addScopeToScope(Scope* parent, Scope* child){
    ///std::cout<<"Adding "<<child->getName()<<" to "<<parent->getName()<<"\n";
    std::string adding_name = parent->getName()+"."+child->getName();
    child->setName(adding_name);
    child->setParent(parent);
    parent->addScope(child);
}