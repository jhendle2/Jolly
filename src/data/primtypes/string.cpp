#include "string.hpp"
#include "utils.hpp"

#include <iostream>

String::String() : Variable(Prim_String){
    value = "";
}

String::String(std::string name) : Variable(name, Prim_String){
    value = "";
}

String::String(std::string name, char value) : Variable(name, Prim_String){
    std::string str_char{value};
    this->value = str_char;
}

String::String(std::string name, std::string value) : Variable(name, Prim_String){
    this->value = removeDoubleQuotes(value);
}

void String::setValue(char value){
    std::string str_value{value};
    this->value = str_value;
}
void String::setValue(std::string value){
    this->value = removeDoubleQuotes(value);
}
std::string String::getValue() const{
    return value;
}

std::string String::stringValue() const{
    return value;
}

/* Operations */

void String::set(const String& string){
    this->value = string.getValue();
}
bool String::eq(const String& string){
    return (value == string.getValue());
}
bool String::notEq(const String& string){
    return !eq(string);
}
Number String::_len(){
    int length = (int)value.length();
    return Number(length);
}

String String::_add(const String& string){
    String out = String("constant");
    out.setValue(value + string.getValue());
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