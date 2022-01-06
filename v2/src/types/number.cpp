#include "number.hpp"

Number::Number() : Variable(TYPE_NUMBER){

}

Number::Number(const int number) : Variable(number){

}

Number::Number(std::string string) : Variable(TYPE_NUMBER){
    number = atoi(string.c_str());
}

Number::Number(const Variable& var) : Variable(TYPE_NUMBER){
    Variable v = var;
    this->number = v.getNumber();
}

Number Number::add(const Number& right){
    Number out = Number(number);
    out.number += right.number;
    return out;
}

Number Number::addEq(const Number& right){
    Number out = Number(number);
    out.number += right.number;
    number = out.number;
    return out;
}