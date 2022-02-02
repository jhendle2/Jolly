#include <iostream>

#include "keywords.hpp"
#include "scope.hpp"

std::string scopeTypeToString(const enum ScopeType& type){
    switch(type){
        case ScopeConstant: return "constant";
        case ScopeClass: return "scope";
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

Scope::Scope() : std::enable_shared_from_this<Scope>(){
    this->name = "no_name";
    this->type = ScopeInvalid;

    this->parent = nullptr;
}

Scope::Scope(std::string name, enum ScopeType type) : std::enable_shared_from_this<Scope>(){
    this->name = name;
    this->type = type;

    this->parent = nullptr;
}

void Scope::addLine(Line line){
    this->lines.push_back(line);
}
std::vector<Line> Scope::getLines() const{
    return this->lines;
}

ScopePtr Scope::getptr(){
    return shared_from_this();
}

std::string Scope::getName() const{
    return this->name;
}
enum ScopeType Scope::getScopeType() const{
    return this->type;
}


void Scope::setParent(ScopePtr parent){
    this->parent = parent;
}

ScopePtr Scope::getParent() const{
    return this->parent;
}

[[nodiscard]] ScopePtr Scope::create() {
    return ScopePtr(new Scope());
}

[[nodiscard]] ScopePtr Scope::create(std::string name, enum ScopeType type) {
    return ScopePtr(new Scope(name, type));
}

void Scope::addChild(ScopePtr child){
    child->setParent(this->getptr());
    this->children.push_back(child);
}

void Scope::dump() const{
    std::cout << "----" << name << "----\n";
    std::cout << "ScopeType: " << scopeTypeToString(type) << "\n";
    std::cout << "Parent: " << (getParent()!=nullptr ? getParent()->getName() : "None") << "\n";
    
    std::cout << "\nLines:\n";
    for(auto line : lines){
        std::cout << "(" << line.line_number << ") - " << line.line << "\n";
    }

    std::cout << "\nChildren:\n";
    for(auto child : children){
        std::cout << "* " << child->name << "\n";
    }
    std::cout << "----------------------\n";
}

void Scope::dumpRecursive() const {
    dump();

    for(auto child : children){
        std::cout << "\n";
        child->dumpRecursive();
    }
}

static void tree_helper(int level, const ScopePtr& scope){
    for(int i = 0; i<level; i++) std::cout<<"* ";
    std::cout<<scope->getName()<<"\n";
}
void Scope::tree(int level){
    tree_helper(level, this->getptr());

    for(ScopePtr child : children){
        child->tree(level + 1);
    }
}
void Scope::tree(){
    this->tree(0);
}