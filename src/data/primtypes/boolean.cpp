#include "boolean.hpp"

Boolean::Boolean(bool value) : Variable(Prim_Boolean){
    this->value = value;
}

Boolean::Boolean(std::string name) : Variable(name, Prim_Boolean){
    this->value = false;
}

Boolean::Boolean(std::string name, bool value) : Variable(name, Prim_Boolean){
    this->value = value;
}


void Boolean::setValue(bool value){
    this->value = value;
}

bool Boolean::getValue() const{
    return value;
}

std::string Boolean::stringValue() const{
    return value?KW_TRUE:KW_FALSE;
}

/* Operations */

void Boolean::set(const Boolean& boolean){
    value = boolean.getValue();
}

bool Boolean::eq(const Boolean& boolean){
    return (value == boolean.getValue());
}

bool Boolean::notEq(const Boolean& boolean){
    return !eq(boolean);
}


Boolean Boolean::_not(){
    return Boolean(!value);
}

Boolean Boolean::_and(const Boolean& boolean){
    bool operation = value && boolean.getValue();
    return Boolean(operation);
}

Boolean Boolean::_or(const Boolean& boolean){
    bool operation = value || boolean.getValue();
    return Boolean(operation);
}

Boolean Boolean::_xor(const Boolean& boolean){
    bool operation = (!value != !boolean.getValue());
    return Boolean(operation);
}

Boolean Boolean::_nand(const Boolean& boolean){
    return _and(boolean)._not();
}

Boolean Boolean::_nor(const Boolean& boolean){
    return _or(boolean)._not();
}

Boolean Boolean::_xnor(const Boolean& boolean){
    return _xor(boolean)._not();
}
