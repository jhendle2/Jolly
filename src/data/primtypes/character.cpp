#include <iostream>
#include <math.h>

#include "operators.hpp"
#include "utils.hpp"
#include "character.hpp"
#include "errors.hpp"

Character::Character() : Variable(Prim_Char){
    this->value_character = 0;
}
Character::Character(char value_character) : Variable(Prim_Char){
    this->value_character=value_character;
}
Character::Character(const Variable& var) : Variable(var.getName(),Prim_Char){
    if(var.getPrimType() == Prim_Number){
        this->value_character = (char)(var.getValueNumber());
    }
    else{
        this->value_character=var.getValueCharacter();
    }
}
Character::Character(std::string name) : Variable(name, Prim_Char){
    value_character = '\0';
}
Character::Character(std::string name, char value_character) : Variable(name, Prim_Char){
    this->value_character = value_character;
}
Character::Character(std::string name, std::string value_character) : Variable(name, Prim_Char){
    this->value_character = removeSingleQuotes(value_character).at(0);
}
Character::Character(std::string name, int value_character) : Variable(name, Prim_Char){
    this->value_character = (char)value_character;
}
Character::Character(std::string name, float value_character) : Variable(name, Prim_Char){
    this->value_character = (char)value_character;
}

void Character::setValue(char value_character){
    this->value_character = value_character;
}
void Character::setValue(std::string value_character){
    this->value_character = removeSingleQuotes(value_character).at(0);
}
char Character::getValue() const{
    return value_character;
}

/* Operations */
bool Character::hasOperation(std::string op) const{
    return(
        op == OP_EQ ||
        op == OP_EQUALITY ||
        op == OP_INEQUALITY ||
        op == OP_ADD ||
        op == OP_SUB ||
        op == OP_CAT ||
        op == OP_LESS ||
        op == OP_LESSEQ ||
        op == OP_GREATER ||
        op == OP_GREATEREQ
    );
}

Variable Character::set(const Variable& var){
    switch(var.getPrimType()){
        default:
            break;
        
        case Prim_Char:
            this->value_character = var.getValueCharacter();
            return Character(name, value_character);

        case Prim_String:
            if(var.getValueString().length() > 1){
                this->value_character = var.getValueString().at(0);
                return Character(name, value_character);
            }
            else{
                this->value_character = 0;
                return Character(name, value_character);
            }
        
        case Prim_Boolean:
            this->value_character = (var.getValueBoolean()?'1':'0');
            return Character(name, value_character);
        
        case Prim_Number:
            this->value_character = (char)(var.getValueNumber());
    }
    return Variable();
}
bool Character::eq(const Character& character){
    return (this->value_character == character.getValue());
}
bool Character::notEq(const Character& character){
    return !eq(character);
}

bool Character::less(const Character& character){
    return (this->value_character < character.getValue());
}
bool Character::greater(const Character& character){
    return (this->value_character > character.getValue());
}
bool Character::lessEq(const Character& character){
    return !greater(character);
}
bool Character::greaterEq(const Character& character){
    return !less(character);
}

Character Character::_add(const Character& character){
    Character temp = Character(value_character);
    temp.setValue(temp.getValue() + character.getValue());
    return temp;
}
Character Character::_sub(const Character& character){
    Character temp = Character(value_character);
    temp.setValue(temp.getValue() - character.getValue());
    return temp;
}
Character Character::_add(const Number& number){
    Character temp = Character(value_character);
    temp.setValue(temp.getValue() + number.getValue());
    return temp;
}
Character Character::_sub(const Number& number){
    Character temp = Character(value_character);
    temp.setValue(temp.getValue() - number.getValue());
    return temp;
}

String Character::cat(const Character& character){
    String out = String("contant", value_character);
    out = out.cat(character);
    return out;
}

String Character::cat(const String& string){
    String out = String("contant", value_character);
    out = out.cat(string);
    return out;
}
