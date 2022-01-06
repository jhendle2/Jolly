#include "character.hpp"

Character::Character() : Variable(TYPE_CHAR){

}

Character::Character(const char character) : Variable(character){

}

Character::Character(const Variable& var) : Variable(TYPE_CHAR){
    Variable temp = var;
    character = temp.getCharacter();
}
