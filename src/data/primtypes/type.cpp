#include "type.hpp"
#include "primtypes.hpp"
#include "operators.hpp"

Type::Type() : Variable(Prim_Type){
    value_type = Prim_Nothing;
}

Type::Type(const Variable& var) : Variable(var.getName(), Prim_Type){
    if(var.getPrimType() == Prim_Type){
        value_type = var.getValueType();
    }
    else{
        value_type = var.getPrimType();
    }
}

Type::Type(std::string name) : Variable(name, Prim_Type){
    value_type = Prim_Nothing;
}

Type::Type(enum PrimType value_type) : Variable(Prim_Type){
    this->value_type = value_type;
}

Type::Type(std::string name, enum PrimType value_type) : Variable(name, Prim_Type){
    this->value_type = value_type;
}


void Type::setValue(enum PrimType value_type){
    this->value_type = value_type;
}

enum PrimType Type::getValue() const{
    return value_type;
}

bool Type::hasOperation(std::string op) const{
    return(
        op == OP_EQ ||
        op == OP_EQUALITY ||
        op == OP_INEQUALITY
    );
}

Variable Type::set(const Variable& t){
    if(t.getPrimType() == Prim_Type){
        this->value_type = t.getValueType();
        Type out = Type(name, value_type);
        return out;
    }
    
    this->value_type = t.getPrimType();
    Type out = Type(name, value_type);
    return out;
}

bool Type::eq(const Type& t){
    return (this->value_type == t.getValue());
}

bool Type::notEq(const Type& t){
    return !eq(t);
}
