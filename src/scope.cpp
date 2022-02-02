#include <iostream>

#include "scope.hpp"

std::string scopeTypeToString(const enum ScopeType& type){
    switch(type){
        case ScopeFunction:
            return "function";
        
        case ScopeWhile:
            return "while";

        default:
            return "invalid";
    }
}

Scope::Scope() : std::enable_shared_from_this<Scope>(){
    this->name = "noname";
    this->type = ScopeInvalid;

    this->parent = nullptr;
}

Scope::Scope(std::string name, enum ScopeType type) : std::enable_shared_from_this<Scope>(){
    this->name = name;
    this->type = type;

    this->parent = nullptr;
}

std::shared_ptr<Scope> Scope::getptr(){
    return shared_from_this();
}

std::string Scope::getName() const{
    return this->name;
}
enum ScopeType Scope::getScopeType() const{
    return this->type;
}


void Scope::setParent(std::shared_ptr<Scope> parent){
    this->parent = parent;
}

std::shared_ptr<Scope> Scope::getParent() const{
    return this->parent;
}

[[nodiscard]] std::shared_ptr<Scope> Scope::create() {
    return std::shared_ptr<Scope>(new Scope());
}

[[nodiscard]] std::shared_ptr<Scope> Scope::create(std::string name, enum ScopeType type) {
    return std::shared_ptr<Scope>(new Scope(name, type));
}

void Scope::addChild(std::shared_ptr<Scope> child){
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
        child->dump();
    }
}

static void tree_helper(int level, const std::shared_ptr<Scope>& scope){
    for(int i = 0; i<level; i++) std::cout<<"* ";
    std::cout<<scope->getName()<<"\n";
}

void Scope::tree(int level){
    tree_helper(level, this->getptr());

    for(std::shared_ptr<Scope> child : children){
        child->tree(level + 1);
    }
}