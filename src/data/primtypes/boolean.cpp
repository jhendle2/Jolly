#include "boolean.hpp"
#include "operators.hpp"

Boolean::Boolean() : Variable(Prim_Boolean){
    this->value_boolean = false;
}

Boolean::Boolean(bool value_boolean) : Variable(Prim_Boolean){
    this->value_boolean = value_boolean;
}

Boolean::Boolean(const Variable& var) : Variable(var.getName(), Prim_Boolean){
    switch(var.getPrimType()){
        default:
            this->value_boolean = false;
            break;

        case Prim_Number:
            this->value_boolean = (bool)var.getValueNumber();
            break;
        
        case Prim_Boolean:
            this->value_boolean = var.getValueBoolean();
            break;

        case Prim_Char:
            this->value_boolean = (bool)var.getValueCharacter();
            break;

        case Prim_String:
            this->value_boolean = (var.getValueString() == "True" || var.getValueString() == "true") ? true : false;
            break;
    }
}

Boolean::Boolean(std::string name) : Variable(name, Prim_Boolean){
    this->value_boolean = false;
}

Boolean::Boolean(std::string name, bool value_boolean) : Variable(name, Prim_Boolean){
    this->value_boolean = value_boolean;
}

Boolean::Boolean(std::string name, std::string value_boolean) : Variable(name, Prim_Boolean){
    this->value_boolean = (value_boolean=="True" || value_boolean=="true")?true:false;
}


void Boolean::setValue(bool value_boolean){
    this->value_boolean = value_boolean;
}

bool Boolean::getValue() const{
    return value_boolean;
}

/* Operations */

bool Boolean::hasOperation(std::string op) const{
    return(
        op == OP_EQ ||
        op == OP_EQUALITY ||
        op == OP_INEQUALITY ||
        op == OP_AND ||
        op == OP_OR ||
        op == OP_XOR ||
        op == OP_ANDEQ ||
        op == OP_XOREQ ||
        op == OP_OREQ ||
        op == OP_NOT
    );
}

Variable Boolean::set(const Boolean& boolean){
    value_boolean = boolean.getValue();
    Boolean out = Boolean(name, value_boolean);
    return out;
}

bool Boolean::eq(const Boolean& boolean){
    return (value_boolean == boolean.getValue());
}

bool Boolean::notEq(const Boolean& boolean){
    return !eq(boolean);
}


Boolean Boolean::_not(){
    return Boolean(!value_boolean);
}

Boolean Boolean::_and(const Boolean& boolean){
    bool operation = value_boolean && boolean.getValue();
    return Boolean(operation);
}

Boolean Boolean::_or(const Boolean& boolean){
    bool operation = value_boolean || boolean.getValue();
    return Boolean(operation);
}

Boolean Boolean::_xor(const Boolean& boolean){
    bool operation = (!value_boolean != !boolean.getValue());
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
