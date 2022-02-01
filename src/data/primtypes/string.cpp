#include <iostream>

#include "string.hpp"
#include "utils.hpp"
#include "operators.hpp"

String::String() : Variable(Prim_String){
    value_string = "";
}

String::String(const Variable& var) : Variable(var.getName(), Prim_String){
    value_string = var.stringValue();
}

String::String(std::string name) : Variable(name, Prim_String){
    value_string = "";
}

String::String(std::string name, char value_string) : Variable(name, Prim_String){
    std::string str_char{value_string};
    this->value_string = str_char;
}

String::String(std::string name, std::string value_string) : Variable(name, Prim_String){
    this->value_string = removeDoubleQuotes(value_string);
}

void String::setValue(char value_string){
    std::string str_value_string{value_string};
    this->value_string = str_value_string;
}
void String::setValue(std::string value_string){
    this->value_string = removeDoubleQuotes(value_string);
}
std::string String::getValue() const{
    return value_string;
}

/* Operations */

bool String::hasOperation(std::string op) const{
    return(
        op == OP_EQ ||
        op == OP_EQUALITY ||
        op == OP_INEQUALITY ||
        op == OP_ADD ||
        op == OP_CAT
    );
}

Variable String::set(const Variable& var){
    this->value_string = var.stringValue();
    String out = String(name, value_string);
    return out;
}
bool String::eq(const Variable& var){
    return (value_string == var.stringValue());
}
bool String::notEq(const Variable& var){
    return !eq(var);
}
Number String::_len(){
    int length = (int)value_string.length();
    return Number(length);
}

bool String::_less(const String& string){
    return (value_string.length() < string.getValueString().length());
}

bool String::_greater(const String& string){
    return (value_string.length() > string.getValueString().length());
}
bool String::_lessEq(const String& string){
    return (value_string.length() <= string.getValueString().length());
}

bool String::_greaterEq(const String& string){
    return (value_string.length() >= string.getValueString().length());
}

String String::_add(const String& string){
    String out = String("constant", "");
    out.setValue(value_string + string.getValue());
    return out;
}
String String::_mul(const Number& number){
    String out = String("constant", "");
    std::string mul_string = value_string;
    for(int i = 0; i<number.getValueNumber(); i++){
        mul_string += value_string;
    }
    out.setValue(mul_string);
    return out;
}
String String::cat(const String& string){
    return _add(string);
}
String String::cat(const Character& character){
    return _add(String("constant", character.stringValue()));
}
String String::cat(const Boolean& boolean){
    return _add(String("constant", boolean.stringValue()));
}
String String::cat(const Number& number){
    return _add(String("constant", number.stringValue()));
}
String String::cat(const Type& t){
    return _add(String("constant", t.stringValue()));
}