#include <iostream>

#include "function.hpp"

Function::Function() : BaseFunction("invalid_function", TYPE_NOTHING){
    parent=nullptr;
}

Function::~Function(){
    // we don't want to DELETE or FREE parent because it might have other children
    // as such, we just want to set our local parent to a nullptr just in case.
    parent=nullptr;

    for(auto pair : functions){
        Function* temp = pair.second;
        if(temp != nullptr){
            delete temp; // here we actually want to delete the functions because they only exist locally
            temp=nullptr; // and here is some extra cleanup, which might not be necessary
        }
    }
    functions.clear(); // dump the vector
}

Function::Function(std::string name) : BaseFunction(name, TYPE_NOTHING){
    parent=nullptr;
}

Function::Function(std::string name, enum ObjectType return_type) : BaseFunction(name, return_type){
    parent=nullptr;
}

Function::Function(std::string name, std::vector<Object> params) : BaseFunction(name, TYPE_NOTHING){
    parent=nullptr;
}

Function::Function(std::string name, enum ObjectType return_type, std::vector<Object> params) : BaseFunction(name, return_type){
    parent=nullptr;
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

void Function::setParent(Function* parent){
    if(this->parent == nullptr)
        this->parent = new Function();
    this->parent = parent;
}
Function* Function::getParent(){
    return parent;
}
bool Function::hasParent(){
    return (parent!=nullptr);
}

ObjectTable<Variable>& Function::getVariables(){
    return variables;
}

void Function::addVariable(Variable var){
    var.setAccess(PRIVATE);
    variables.add(var);
}

void Function::addVariable(std::string name, Variable var){
    var.setAccess(PRIVATE);
    var.setName(name);
    variables.add(var);
}

void Function::addVariable(enum AccessSpecifier access, Variable var){
    var.setAccess(access);
    variables.add(var);
}

void Function::addVariable(std::string name, enum AccessSpecifier access, Variable var){
    var.setAccess(access);
    var.setName(name);
    variables.add(var);
}

void Function::updateVariable(Variable var){
    variables.update(var);
}

void Function::updateVariable(std::string name, Variable var){
    variables.update(name, var);
}

Variable Function::updateVariableAndGet(Variable var){
    variables.update(var);
    return var;
}

Variable Function::getVariable(std::string name){
    Variable var = variables.get(name);
    return var; //variables.get(name);
}

bool Function::getVariableRecursive(std::string name, Variable& var){
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

void Function::addFunction(Function func){
    func.setAccess(PRIVATE);
    Function* temp = new Function(func);
    functions[func.getName()] = temp;
}

void Function::addFunction(enum AccessSpecifier access, Function func){
    func.setAccess(access);
    Function* temp = new Function(func);
    functions[func.getName()] = temp;
}

void Function::addFunction(Function* func){
    func->setAccess(PRIVATE);
    functions[func->getName()] = func;
}

void Function::addFunction(enum AccessSpecifier access, Function* func){
    func->setAccess(access);
    functions[func->getName()] = func;
}

void Function::updateFunction(std::string name, Function func){
    *(functions[name]) = func;
}

bool Function::hasFunction(std::string name){
    return (functions.count(name) > 0);
}

Function* Function::getFunction(std::string name){
    return functions[name];
}

Function* Function::updateAndGetFunction(std::string name, Function func){
    updateFunction(name, func);
    return getFunction(name);
}

/*****************************************/

void Function::dump(){
    std::cout<<"\n===========FUNCTION("<<name<<")===========\n";
    if(parent != nullptr) std::cout<<"PARENT FUNCTION: "<<parent->getName()<<"\n";
    else std::cout<<"NO PARENT!\n";
    std::cout<<"##VARIABLES##:\n";
    variables.dump(); std::cout<<"\n\n";
    std::cout<<"##FUNCTIONS##:\n";
    std::cout<<"\n------------------------------------------\n";
    for(auto pair : functions){
        std::cout<<"* "<<pair.second->getName()<<"\n";
    }
    std::cout<<"\n==========================================\n";
}

void Function::dumpRecursive(){
    std::cout<<"{{{{{{{{{{{{{{{{{{{{{{{{\n";
    dump();

    for(auto pair : functions){
        std::cout<<"\n";
        pair.second->dumpRecursive();
    }

    std::cout<<"}}}}}}}}}}}}}}}}}}}}}}}}\n";
}

 // Do I have this variable or function?
bool Function::isKnown(std::string name){
    return variables.isKnown(name) || hasFunction(name);
}

bool Function::isKnownVariable(std::string name){
    return variables.isKnown(name);
}

// Do I have this variable or function? If yes --> return TYPE_VARIABLE or TYPE_FUNCTION. If not, TYPE_INVALID
enum ObjectType Function::isKnownAndType(std::string name){
    if(variables.isKnown(name)) return TYPE_VARIABLE;
    else if(hasFunction(name)) return TYPE_FUNCTION;
    else return TYPE_INVALID;
}

void addFunctionToFunction(Function& parent, Function& child){
    child.setParent(&parent);
    parent.addFunction(child);
}

void addFunctionToFunction(Function* parent, Function* child){
    child->setParent(parent);
    parent->addFunction(child);
}