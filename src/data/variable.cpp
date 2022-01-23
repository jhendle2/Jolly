#include <iostream>

#include "primtypes.hpp"
#include "variable.hpp"
#include "type.hpp"

Variable::Variable(){
    name = "constant";
    type = Prim_Nothing;

    value_boolean = false;
    value_character = 0;
    value_string = "null";
    value_number = 0.0;
    value_number_show_decimal = false;
    value_type = Prim_Nothing;
}

Variable::Variable(std::string name){
    this->name = name;
    type = Prim_Nothing;

    value_boolean = false;
    value_character = 0;
    value_string = "";
    value_number = 0.0;
    value_number_show_decimal = false;
    value_type = Prim_Nothing;
}

Variable::Variable(enum PrimType type){
    this->name = "constant";
    this->type = type;

    value_boolean = false;
    value_character = 0;
    value_string = "";
    value_number = 0.0;
    value_number_show_decimal = false;
    value_type = Prim_Nothing;
}

Variable::Variable(std::string name, enum PrimType type){
    this->name = name;
    this->type = type;

    value_boolean = false;
    value_character = 0;
    value_string = "";
    value_number = 0.0;
    value_number_show_decimal = false;
    value_type = Prim_Nothing;
}

bool Variable::getValueBoolean() const{
    return value_boolean;
}
char Variable::getValueCharacter() const{
    return value_character;
}
double Variable::getValueNumber() const{
    return value_number;
}
bool Variable::getValueNumberShowDecimal() const{
    return value_number_show_decimal;
}
std::string Variable::getValueString() const{
    return value_string;
}
enum PrimType Variable::getValueType() const{
    return value_type;
}

enum PrimType Variable::getPrimType() const{
    return type;
}

Type Variable::getType() const{
    return Type(type);
}

void Variable::setName(std::string name){
    this->name = name;
}

std::string Variable::getName() const{
    return name;
}


std::string Variable::toString() const{
    return "["+primType2Keyword(type)+"] "+name+" = "+stringValue();
}

void Variable::dumpString() const{
    std::cout<<toString()<<"\n";
}

std::string Variable::stringValue() const{
    std::string char_as_string{value_character};
    int int_value_number = 0;
    switch(type){
        default:
        case Prim_Nothing:
            return "novalue";
        case Prim_Boolean:
            return value_boolean?KW_TRUE:KW_FALSE;
        case Prim_String:
            return value_string;
        case Prim_Char:
            return char_as_string;
        case Prim_Number:
            if(!value_number_show_decimal){
                int_value_number = (int)value_number;
                return std::to_string(int_value_number);
            }
            return std::to_string(value_number);
        case Prim_Type:
            return primType2Keyword(value_type);
    }
}

Variable Variable::set(const Variable& var){
    if(type == var.getPrimType()){
        switch(type){
            default:
            case Prim_Nothing: return Variable();
            case Prim_Boolean: value_boolean = var.getValueBoolean(); break;
            case Prim_Char: value_character = var.getValueCharacter(); break;
            case Prim_Number:
                value_number = var.getValueNumber();
                value_number_show_decimal = var.getValueNumberShowDecimal();
                break;
            case Prim_String: value_string = var.getValueString(); break;
            case Prim_Type: value_type = var.getValueType(); break;
        }
    }
    return var;
}
bool Variable::eq(const Variable& var){
    if(type == var.getPrimType()){
        switch(type){
            default:
            case Prim_Nothing: return false;
            case Prim_Boolean: return value_boolean == var.getValueBoolean();
            case Prim_Char: return value_character == var.getValueCharacter();
            case Prim_Number: return value_number == var.getValueNumber();
            case Prim_String: return value_string == var.getValueString();
            case Prim_Type: return value_type == var.getValueType();
        }
    }
    return false;
}
bool Variable::notEq(const Variable& var){
    return !eq(var);
}

bool Variable::hasOperation(std::string op) const{
    return false;
}

/*************************************************/

bool isDigit(char c){
    return (c >= '0' && c <= '9');
}
bool isCharacter(std::string s){
    return ((s.length() > 2) && (s.at(0) == '\'' && s.at(s.length()-1) == '\''));
}
bool isNumber(std::string s){
    for(char& c : s){
        if(!isDigit(c)) return false;
    }
    return true;
}
bool isDecimal(std::string s){
    int dot_count = 0;
    for(char& c : s){
        if(c == '.') dot_count++;
        else if(!isDigit(c)) return false;
    }
    return (dot_count <= 1);
}
bool isString(std::string s){
    return ((s.length() >= 2) && (s.at(0) == '\"' && s.at(s.length()-1) == '\"'));
}
bool isBoolean(std::string s){
    return (s=="true" || s=="True" || s=="false" || s=="False");
}