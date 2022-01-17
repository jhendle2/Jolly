#include <math.h>

#include "number.hpp"
#include "errors.hpp"

Number::Number() : Variable(TYPE_NUMBER){

}

Number::Number(const int number) : Variable(number){

}

Number::Number(const char number) : Variable((int)number){

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

Number Number::sub(const Number& right){
    Number out = Number(number);
    out.number -= right.number;
    return out;
}

Number Number::subEq(const Number& right){
    Number out = Number(number);
    out.number -= right.number;
    number = out.number;
    return out;
}

Number Number::mul(const Number& right){
    Number out = Number(number);
    out.number *= right.number;
    return out;
}

Number Number::mulEq(const Number& right){
    Number out = Number(number);
    out.number *= right.number;
    number = out.number;
    return out;
}

Number Number::div(const Number& right){
    Number out = Number(number);
    if(right.number == 0){
        ERROROUT(ArithmeticErrorDivideByZero, right.name);
    }
    out.number /= right.number;
    return out;
}

Number Number::divEq(const Number& right){
    Number out = Number(number);
    if(right.number == 0){
        ERROROUT(ArithmeticErrorDivideByZero, right.name);
    }
    out.number /= right.number;
    number = out.number;
    return out;
}

Number Number::exp(const Number& right){
    Number out = Number(number);
    double base = (double)(out.number);
    double power = (double)(right.number);
    double pow_out = pow(base,power);
    out.number = pow_out;
    return out;
}

Number Number::expEq(const Number& right){
    Number out = Number(number);
    double base = (double)(out.number);
    double power = (double)(right.number);
    double pow_out = pow(base,power);
    out.number = pow_out;
    number = out.number;
    return out;
}

Number Number::mod(const Number& right){
    Number out = Number(number);
    out.number %= right.number;
    return out;
}

Number Number::modEq(const Number& right){
    Number out = Number(number);
    out.number %= right.number;
    number = out.number;
    return out;
}