#include <iostream>
#include <math.h>

#include "number.hpp"
#include "errors.hpp"

Number::Number(float value) : Variable(Prim_Number){
    show_decimal = true;
    this->value=value;
}
Number::Number(int value) : Variable(Prim_Number){
    show_decimal = false;
    this->value=value;
}
Number::Number(double value) : Variable(Prim_Number){
    show_decimal = true;
    this->value=(float)value;
}
Number::Number(std::string name) : Variable(name, Prim_Number){
    show_decimal = false;
    value = 0.0;
}
Number::Number(std::string name, float value) : Variable(name, Prim_Number){
    show_decimal = true;
    this->value = value;
}
Number::Number(std::string name, int value) : Variable(name, Prim_Number){
    show_decimal = false;
    this->value = (float)value;
}

void Number::setShowDecimal(bool show_decimal){
    this->show_decimal = show_decimal;
}
bool Number::showDecimal() const{
    return show_decimal;
}

void Number::setValue(float value){
    this->value = value;
}
void Number::setValue(int value){
    this->value = (float)value;
}
void Number::setValue(double value){
    this->value = (float)value;
}
float Number::getValue() const{
    return value;
}

std::string Number::stringValue() const{
    if(!show_decimal){
        int int_value = (int)value;
        return std::to_string(int_value);
    }
    return std::to_string(value);
}

/* Operations */
void Number::set(const Number& number){
    this->value = number.getValue();
    this->show_decimal = number.showDecimal();
}
bool Number::eq(const Number& number){
    return (this->value == number.getValue());
}
bool Number::notEq(const Number& number){
    return !eq(number);
}

bool Number::less(const Number& number){
    return (this->value < number.getValue());
}
bool Number::greater(const Number& number){
    return (this->value > number.getValue());
}
bool Number::lessEq(const Number& number){
    return !greater(number);
}
bool Number::greaterEq(const Number& number){
    return !less(number);
}

Number Number::_add(const Number& number){
    Number temp = Number(value);
    temp.setShowDecimal(show_decimal);
    temp.setValue(temp.getValue() + number.getValue());
    return temp;
}
Number Number::_sub(const Number& number){
    Number temp = Number(value);
    temp.setShowDecimal(show_decimal);
    temp.setValue(temp.getValue() - number.getValue());
    return temp;
}
Number Number::_mul(const Number& number){
    Number temp = Number(value);
    temp.setShowDecimal(show_decimal);
    temp.setValue(temp.getValue() * number.getValue());
    return temp;
}
Number Number::_div(const Number& number){
    if(number.getValue() == 0){
        ERROROUT(ArithmeticErrorDivideByZero, name + "/" + number.getName());
    }
    Number temp = Number(value);
    temp.setValue(temp.getValue() / number.getValue());
    bool divides_cleanly = ((int)temp.getValue() % (int)number.getValue() == 0);
    temp.setShowDecimal(!divides_cleanly || show_decimal);
    return temp;
}
Number Number::_mod(const Number& number){
    if(number.getValue() == 0){
        ERROROUT(ArithmeticErrorDivideByZero, name + "%" + number.getName());
    }
    Number temp = Number(value);
    temp.setShowDecimal(show_decimal);
    int mod = (int)temp.getValue() % (int)number.getValue();
    temp.setValue(mod);
    return temp;
}
Number Number::_exp(const Number& number){
    if(value == 0 && number.getValue() == 0){
        ERROROUT(ArithmeticErrorDivideByZero, name + "^" + number.getName());
    }
    Number temp = Number(value);
    temp.setShowDecimal(show_decimal);
    int exp_value = pow((int)temp.getValue(), (int)number.getValue());
    temp.setValue(exp_value);
    return temp;
}