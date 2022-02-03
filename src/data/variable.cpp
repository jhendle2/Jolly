#include <iostream>

#include "keywords.hpp"
#include "variable.hpp"

Variable::Variable(){
    name = "constant";
    type = VarType();

    value.boolean = false;
    value.character = 0;
    value.string = "";
    value.number = 0.0;
    value.type = VarType();

    parent = nullptr;
}

Variable::Variable(bool boolean){
    name = "constant";
    type = getVarType(KW_BOOLEAN);

    value.boolean = boolean;
    value.character = 0;
    value.string = "";
    value.number = 0.0;
    value.type = VarType();

    parent = nullptr;
}

Variable::Variable(std::string name, std::string type){
    this->name = name;
    this->type = getVarType(type);

    value.boolean = false;
    value.character = 0;
    value.string = "";
    value.number = 0.0;
    value.type = VarType();

    parent = nullptr;
}

Variable::Variable(std::string name, VarType type){
    this->name = name;
    this->type = type;

    value.boolean = false;
    value.character = 0;
    value.string = "";
    value.number = 0.0;
    value.type = VarType();

    parent = nullptr;
}

void Variable::setValue(const bool& value){this->type = getVarType(KW_BOOLEAN); this->value.boolean=value;}
void Variable::setValue(const char& value){this->type = getVarType(KW_CHARACTER); this->value.character=value;}
void Variable::setValue(const std::string& value){this->type = getVarType(KW_STRING); this->value.string=value;}
void Variable::setValue(const double& value){this->type = getVarType(KW_NUMBER); this->value.number=value;}
void Variable::setValue(const VarType& value){this->type = getVarType(KW_TYPE); this->value.type=value;}

void Variable::setName(std::string name){this->name=name;}
std::string Variable::getName() const{return name;}

void Variable::setType(std::string type){this->type=getVarType(type);}
VarType Variable::getType() const{return type;}

void Variable::setParent(std::shared_ptr<Scope> parent){this->parent=parent;}
std::shared_ptr<Scope> Variable::getParent() const{return parent;}


std::string Variable::valueString() const{
    if(type.getName()=="String") return value.string;
    if(type.getName()=="Character") return std::to_string(value.character);
    if(type.getName()=="Number") return std::to_string(value.number);
    if(type.getName()=="Boolean") return value.boolean?"True":"False";
    if(type.getName()=="Type") return value.type.getName();
    return "";
}

std::string Variable::dump() const{
    return "[" + type.getName() + "] " + name + " = " + valueString();
}

bool Variable::getBoolean() const{
    return value.boolean;
}
char Variable::getCharacter() const{
    return value.character;
}
std::string Variable::getString() const{
    return value.string;
}
double Variable::getNumber() const{
    return value.number;
}
VarType Variable::getValueType() const{
    return value.type;
}


void Variable::_set(const Variable& right){
    type = right.getType();
    
    value.boolean = right.getBoolean();
    value.character = right.getCharacter();
    value.string = right.getString();
    value.number = right.getNumber();
    value.type = right.getValueType();

    parent = right.getParent();
}

bool Variable::_eq(const Variable& right){
    if(type == right.getType()){
        if(type.getName() == KW_BOOLEAN) return value.boolean==right.getBoolean();
        if(type.getName() == KW_STRING) return value.string==right.getString();
        if(type.getName() == KW_CHARACTER) return value.character==right.getCharacter();
        if(type.getName() == KW_TYPE) return value.type==right.getValueType();
        if(type.getName() == KW_NUMBER) return value.number==right.getNumber();
    }
    return false;
}

bool Variable::_notEq(const Variable& right){
    return !_eq(right);
}


Variable Variable::_add(const Variable& right){
    return Variable();
}

Variable Variable::_sub(const Variable& right){
    return Variable();
}

Variable Variable::_mul(const Variable& right){
    return Variable();
}

Variable Variable::_div(const Variable& right){
    return Variable();
}

Variable Variable::_pow(const Variable& right){
    return Variable();
}

Variable Variable::_mod(const Variable& right){
    return Variable();
}


Variable Variable::_and(const Variable& right){
    return Variable();
}

Variable Variable::_or(const Variable& right){
    return Variable();
}

Variable Variable::_xor(const Variable& right){
    return Variable();
}


Variable Variable::_cat(const Variable& right){
    return Variable();
}

Variable Variable::_type(const Variable& right){
    return Variable();
}
