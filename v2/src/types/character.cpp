#include "character.hpp"

Character::Character() : Variable(TYPE_CHAR){

}

Character::Character(const char character) : Variable(character){

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