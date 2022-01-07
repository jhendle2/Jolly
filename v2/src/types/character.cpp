#include "character.hpp"
#include "general_utils.hpp"

#include <iostream>

Character::Character() : Variable(TYPE_CHAR){

}

Character::Character(const char character) : Variable(character){

}

Character::Character(const char* character) : Variable(TYPE_CHAR){
    std::string character_as_string = character;
    if(hasQuotes(character_as_string))
        character_as_string = stripQuotes(this->string);
    std::cout<<"cas="<<character_as_string<<"\n";
    this->character = character_as_string.at(0);
}

Character::Character(std::string character_as_string) : Variable(TYPE_CHAR){
    if(hasQuotes(character_as_string))
        character_as_string = stripQuotes(this->string);
    std::cout<<"cas="<<character_as_string<<"\n";
    this->character = character_as_string.at(0);
}

Character::Character(const int character) : Variable((char)character){

}

Character::Character(const Variable& var) : Variable(TYPE_CHAR){
    Variable temp = var;
    character = temp.getCharacter();
}

Character Character::add(const Character& right){
    Character out = Character(character);
    out.character += right.character;
    return out;
}

Character Character::addEq(const Character& right){
    Character out = Character(character);
    out.character += right.character;
    character = out.character;
    return out;
}

Character Character::sub(const Character& right){
    Character out = Character(character);
    out.character -= right.character;
    return out;
}

Character Character::subEq(const Character& right){
    Character out = Character(character);
    out.character -= right.character;
    character = out.character;
    return out;
}