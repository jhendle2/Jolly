#include "type.hpp"
#include "primtypes.hpp"

Type::Type() : Variable(Prim_Type){
    value = Prim_Nothing;
}

Type::Type(std::string name) : Variable(name, Prim_Type){
    value = Prim_Nothing;
}

Type::Type(enum PrimType value) : Variable(Prim_Type){
    this->value = value;
}

Type::Type(std::string name, enum PrimType value) : Variable(name, Prim_Type){
    this->value = value;
}


void Type::setValue(enum PrimType value){
    this->value = value;
}

enum PrimType Type::getValue() const{
    return value;
}


std::string Type::stringValue() const{
    return primType2Keyword(value);
}


void Type::set(const Type& t){
    this->value = t.getValue();
}

bool Type::eq(const Type& t){
    return (this->value == t.getValue());
}

bool Type::notEq(const Type& t){
    return !eq(t);
}
