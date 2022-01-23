#include <iostream>
#include <math.h>

#include "operators.hpp"
#include "number.hpp"
#include "errors.hpp"

Number::Number() : Variable(Prim_Number){
    value_number_show_decimal = true;
    this->value_number=0;
}
// Number::Number(float value_number) : Variable(Prim_Number){
//     value_number_show_decimal = true;
//     this->value_number=(double)value_number;
// }
Number::Number(int value_number) : Variable(Prim_Number){
    value_number_show_decimal = false;
    this->value_number=value_number;
}
Number::Number(double value_number) : Variable(Prim_Number){
    value_number_show_decimal = true;
    this->value_number=value_number;
}
Number::Number(char value_number) : Variable(Prim_Number){
    value_number_show_decimal = false;
    this->value_number=(int)value_number;
}
Number::Number(const Variable& var) : Variable(var.getName(), Prim_Number){
    if(var.getPrimType() == Prim_Char){
        value_number = (int)(var.getValueCharacter());
        value_number_show_decimal = false;
    }
    else if(var.getPrimType() == Prim_String){
        if(isDecimal(var.stringValue())){
            value_number = atof(var.getValueString().c_str());
            value_number_show_decimal = false;
        }
        else if(isNumber(var.stringValue())){
            value_number = atoi(var.getValueString().c_str());
            value_number_show_decimal = true;
        }
        else{
            ERROR(ArithmeticErrorIncompatibleTypes);
        }
    }
    else{
        value_number = var.getValueNumber();
        value_number_show_decimal = var.getValueNumberShowDecimal();
    }
}

Number::Number(std::string name) : Variable(name, Prim_Number){
    value_number_show_decimal = false;
    value_number = 0.0;
}
Number::Number(std::string name, double value_number) : Variable(name, Prim_Number){
    value_number_show_decimal = true;
    this->value_number = value_number;
}
Number::Number(std::string name, int value_number) : Variable(name, Prim_Number){
    value_number_show_decimal = false;
    this->value_number = (float)value_number;
}
Number::Number(std::string name, char value_number) : Variable(name, Prim_Number){
    value_number_show_decimal = false;
    this->value_number = (int)value_number;
}

void Number::setShowDecimal(bool value_number_show_decimal){
    this->value_number_show_decimal = value_number_show_decimal;
}
bool Number::showDecimal() const{
    return value_number_show_decimal;
}

// void Number::setValue(float value_number){
//     this->value_number = value_number;
// }
void Number::setValue(int value_number){
    this->value_number = (float)value_number;
}
void Number::setValue(double value_number){
    this->value_number = (float)value_number;
}
double Number::getValue() const{
    return value_number;
}

/* Operations */
bool Number::hasOperation(std::string op) const{
    return(
        op == OP_EQ ||
        op == OP_EQUALITY ||
        op == OP_INEQUALITY ||
        op == OP_ADD ||
        op == OP_SUB ||
        op == OP_MUL ||
        op == OP_DIV ||
        op == OP_MOD ||
        op == OP_EXP ||
        op == OP_ADDEQ ||
        op == OP_SUBEQ ||
        op == OP_MULEQ ||
        op == OP_DIVEQ ||
        op == OP_LESS ||
        op == OP_LESSEQ ||
        op == OP_GREATER ||
        op == OP_GREATEREQ
    );
}

Variable Number::set(const Number& number){
    this->value_number = number.getValue();
    this->value_number_show_decimal = number.showDecimal();
    Number out = Number(name, 0);
    out.setValue(value_number);
    out.setShowDecimal(value_number_show_decimal);
    return out;
}
bool Number::eq(const Number& number){
    return (this->value_number == number.getValue());
}
bool Number::notEq(const Number& number){
    return !eq(number);
}

bool Number::_less(const Number& number){
    return (this->value_number < number.getValue());
}
bool Number::_greater(const Number& number){
    return (this->value_number > number.getValue());
}
bool Number::_lessEq(const Number& number){
    return !_greater(number);
}
bool Number::_greaterEq(const Number& number){
    return !_less(number);
}

Number Number::_add(const Number& number){
    Number temp = Number(value_number);
    temp.setShowDecimal(value_number_show_decimal || number.getValueNumberShowDecimal());
    temp.setValue(temp.getValue() + number.getValue());
    return temp;
}
Number Number::_sub(const Number& number){
    Number temp = Number(value_number);
    temp.setShowDecimal(value_number_show_decimal || number.getValueNumberShowDecimal());
    temp.setValue(temp.getValue() - number.getValue());
    return temp;
}
Number Number::_mul(const Number& number){
    Number temp = Number(value_number);
    temp.setShowDecimal(value_number_show_decimal || number.getValueNumberShowDecimal());
    temp.setValue(temp.getValue() * number.getValue());
    return temp;
}
Number Number::_div(const Number& number){
    if(number.getValue() == 0){
        ERROROUT(ArithmeticErrorDivideByZero, name + "/" + number.getName());
    }
    Number temp = Number(value_number);
    temp.setValue(temp.getValue() / number.getValue());
    bool divides_cleanly = ((int)temp.getValue() % (int)number.getValue() == 0);
    temp.setShowDecimal(!divides_cleanly || value_number_show_decimal || number.getValueNumberShowDecimal());
    return temp;
}
Number Number::_mod(const Number& number){
    if(number.getValue() == 0){
        ERROROUT(ArithmeticErrorDivideByZero, name + "%" + number.getName());
    }
    Number temp = Number(value_number);
    temp.setShowDecimal(value_number_show_decimal);
    int mod = (int)temp.getValue() % (int)number.getValue();
    temp.setValue(mod);
    return temp;
}
Number Number::_exp(const Number& number){
    if(value_number == 0 && number.getValue() == 0){
        ERROROUT(ArithmeticErrorDivideByZero, name + "^" + number.getName());
    }
    Number temp = Number(value_number);
    temp.setShowDecimal(value_number_show_decimal);
    int exp_value_number = pow((int)temp.getValue(), (int)number.getValue());
    temp.setValue(exp_value_number);
    return temp;
}