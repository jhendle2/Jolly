#include <iostream>

#include "variable.hpp"
#include "keywords.hpp"
#include "scope.hpp"
#include "logging.hpp"

std::string scopeTypeToString(const enum ScopeType& type){
    switch(type){
        case ScopeConstant: return "constant";
        case ScopeClass: return "class";
        case ScopeFunction: return "function";
        case ScopeWhile: return "while";
        case ScopeDowhile: return "dowhile";
        case ScopeFor: return "for";
        case ScopeForeach: return "foreach";
        case ScopeCount: return "count";
        case ScopeIf: return "if";
        case ScopeElsif: return "elsif";
        case ScopeElse: return "else";
        default: return "invalid";
    }
}

bool isScopeType(const std::string& s){
    return (
        s == KW_FUNCTION ||
        s == KW_CLASS ||
        s == KW_WHILE ||
        s == KW_DOWHILE ||
        s == KW_FOR ||
        s == KW_FOREACH ||
        s == KW_COUNT ||
        s == KW_IF ||
        s == KW_ELSIF ||
        s == KW_ELSE
    );
}
enum ScopeType stringToScopeType(const std::string& s){
    if      (s == KW_FUNCTION)  return ScopeFunction;
    else if (s == KW_CLASS)     return ScopeClass;
    else if (s == KW_WHILE)     return ScopeWhile;
    else if (s == KW_DOWHILE)   return ScopeDowhile;
    else if (s == KW_FOR)       return ScopeFor;
    else if (s == KW_FOREACH)   return ScopeForeach;
    else if (s == KW_COUNT)     return ScopeCount;
    else if (s == KW_IF)        return ScopeIf;
    else if (s == KW_ELSIF)     return ScopeElsif;
    else if (s == KW_ELSE)      return ScopeElse;

    return ScopeInvalid;
}

bool isScopeHeader(const std::string& s){
    return (
        s.length() > 2 &&
        s.at(0) == '<'
    );
}

bool tokensAreValidFunctionCall(const Tokens& tokens){
    return tokens.size() >= 3; // A ( ) = 3 characters
}

Scope::Scope() : std::enable_shared_from_this<Scope>(){
    this->name = "<no_name>";
    this->type = ScopeInvalid;
    this->truthiness = true;
    this->parent = nullptr;
}

Scope::Scope(std::string name, enum ScopeType type) : std::enable_shared_from_this<Scope>(){
    this->name = "<" + name + ">";
    this->type = type;
    this->truthiness = true;
    this->parent = nullptr;
}

void Scope::addLine(Line line){this->lines.push_back(line);}
std::vector<Line> Scope::getLines() const{return this->lines;}

ScopePtr Scope::getptr(){return shared_from_this();}

std::string Scope::getName() const{return this->name;}
enum ScopeType Scope::getScopeType() const{return this->type;}

bool Scope::getTruthiness() const{return truthiness;}
void Scope::setTruthiness(bool truthiness){this->truthiness=truthiness;}

void Scope::setParent(ScopePtr parent){this->parent = parent;}

ScopePtr Scope::getParent() const{return this->parent;}

[[nodiscard]] ScopePtr Scope::create() {return ScopePtr(new Scope());}

[[nodiscard]] ScopePtr Scope::create(std::string name, enum ScopeType type) {
    return ScopePtr(new Scope(name, type));
}

void Scope::addChild(ScopePtr child){
    child->setParent(this->getptr());
    this->children[child->getName()] = child;
}

bool Scope::hasChild(std::string name){
    return (children.count("<" + name + ">") > 0);
}

std::shared_ptr<Scope> Scope::getChild(std::string name){
    if(name.length() == 0) return nullptr;

    if(name.at(0) != '<') name = "<" + name + ">";

    for(auto pair : this->children){
        ScopePtr scope = pair.second;
        if(scope->getName() == name) return scope;
    }

    return nullptr;
}

bool Scope::hasVariable(std::string name) const{
    return (variables.count(name) > 0);
}
void Scope::addVariable(std::string name, Variable var){
    if(LOGLEVEL == LOGLEVELDEBUG) std::cout<<"Adding variable: "<<name<<"\n";
    if(hasVariable(name)){
        updateVariable(name, var);
        return;
    }

    variables[name] = var;
}
void Scope::addVariable(Variable var){
    addVariable(var.getName(), var);
}
void Scope::updateVariable(std::string name, const Variable& right){
    if(!hasVariable(name)){
        addVariable(right);
        return;
    }

    variables[name]._set(right);
}
Variable Scope::getVariable(const std::string name){
    if(hasVariable(name)){
        return variables[name];
    }
    std::cout<<"!! Error: Variable \"" << name << "\" doesn\'t exist in scope \"" << this->getName() << "\"\n";
    return Variable();
}

/******************************************/

bool Scope::hasVariableRecursive(std::string name) const{
    if(hasVariable(name)){
        return true;
    }

    if(parent != nullptr){
        return parent->hasVariableRecursive(name);
    }

    return false;
}
void Scope::updateVariableRecursive(std::string name, const Variable& right){
    if(hasVariable(name)){
        updateVariable(name, right);
        return;
    }

    if(hasVariableRecursive(name)){
        // we don't need to check if the parent is nullptr
        // because hasVariableRecursive already does :)
        parent->updateVariableRecursive(name, right);
        return;
    }

    addVariable(name, right);
}
void Scope::updateVariableRecursive(const Variable& right){
    this->updateVariableRecursive(right.getName(), right);
}
Variable Scope::getVariableRecursive(const std::string name){
    if(hasVariable(name)){
        return getVariable(name);
    }

    if(hasVariableRecursive(name)){
        // we don't need to check if the parent is nullptr
        // because hasVariableRecursive already does :)
        return parent->getVariableRecursive(name);
    }

    std::cout<<"!! Error: Variable \"" << name << "\" doesn\'t exist in scope \"" << this->getName() << "\"\n";
    return Variable();
}

/******************************************/

void Scope::dump() const{
    std::cout << "----" << name << "----\n";
    std::cout << "ScopeType: " << scopeTypeToString(type) << "\n";
    std::cout << "Parent: " << (getParent()!=nullptr ? getParent()->getName() : "None") << "\n";
    std::cout << "Truthiness: " << (truthiness?"True\n":"False\n");

    std::cout << "\nLines:\n";
    for(auto line : lines){
        std::cout << "(" << line.line_number << ") - " << line.line << "\n";
    }

    std::cout << "\nVariables:\n";
    for(auto pair : variables){
        Variable var = pair.second;
        std::cout << "* " << var.dump() << "\n";
    }

    std::cout << "\nChildren:\n";
    for(auto pair : children){
        ScopePtr child = pair.second;
        std::cout << "* " << child->getName() << "\n";
    }
    std::cout << "----------------------\n";
}

void Scope::dumpRecursive() const {
    dump();

    for(auto pair : children){
        std::cout << "\n";
        ScopePtr child = pair.second;
        child->dumpRecursive();
    }
}

static void tree_helper(int level, const ScopePtr& scope){
    for(int i = 0; i<level; i++) std::cout<<"* ";
    std::cout<<scope->getName()<<"\n";
}
void Scope::tree(int level){
    tree_helper(level, this->getptr());

    for(auto pair : children){
        ScopePtr child = pair.second;
        child->tree(level + 1);
    }
}
void Scope::tree(){
    this->tree(0);
}

void Scope::treeLines(int level){
    tree_helper(level, this->getptr());
    for(auto line : lines){
        if(line.line.at(0) == '<'){
            ScopePtr child = this->getChild(line.line);
            if(child == nullptr) continue;
            child->treeLines(level+1);
        }
        else{
            for(int i = 0; i<level+1; i++){
                std::cout << "* ";
            }
            std::cout<<line.line<<"\n";
        }
    }
}
void Scope::treeLines(){
    this->treeLines(0);
}