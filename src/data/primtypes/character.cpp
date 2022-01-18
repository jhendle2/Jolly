#include <iostream>
#include <math.h>

#include "utils.hpp"
#include "character.hpp"
#include "errors.hpp"

Character::Character(char value) : Variable(Prim_Char){
    this->value=value;
}
Character::Character(std::string name) : Variable(name, Prim_Char){
    value = '\0';
}
Character::Character(std::string name, char value) : Variable(name, Prim_Char){
    this->value = value;
}
Character::Character(std::string name, std::string value) : Variable(name, Prim_Char){
    this->value = removeSingleQuotes(value).at(0);
}

void Character::setValue(char value){
    this->value = value;
}
void Character::setValue(std::string value){
    this->value = removeSingleQuotes(value).at(0);
}
char Character::getValue() const{
    return value;
}

std::string Character::stringValue() const{
    std::string str_value{value};
    return str_value;
}

/* Operations */
void Character::set(const Character& character){
    this->value = character.getValue();
}
bool Character::eq(const Character& character){
    return (this->value == character.getValue());
}
bool Character::notEq(const Character& character){
    return !eq(character);
}

bool Character::less(const Character& character){
    return (this->value < character.getValue());
}
bool Character::greater(const Character& character){
    return (this->value > character.getValue());
}
bool Character::lessEq(const Character& character){
    return !greater(character);
}
bool Character::greaterEq(const Character& character){
    return !less(character);
}

Character Character::_add(const Character& character){
    Character temp = Character(value);
    temp.setValue(temp.getValue() + character.getValue());
    return temp;
}
Character Character::_sub(const Character& character){
    Character temp = Character(value);
    temp.setValue(temp.getValue() - character.getValue());
    return temp;
}
Character Character::_add(const Number& number){
    Character temp = Character(value);
    temp.setValue(temp.getValue() + number.getValue());
    return temp;
}
Character Character::_sub(const Number& number){
    Character temp = Character(value);
    temp.setValue(temp.getValue() - number.getValue());
    return temp;
}

String Character::cat(const Character& character){
    String out = String("contant", value);
    out = out.cat(character);
    return out;
}
