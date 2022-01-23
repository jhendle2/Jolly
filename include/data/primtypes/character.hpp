#pragma once

#include "variable.hpp"
#include "number.hpp"
#include "string.hpp"

class String; // Forward declared so the 'cat' function works

class Character : public Variable{
    public:
        Character();
        Character(char value_character);
        Character(const Variable& var);
        Character(std::string name);
        Character(std::string name, char value_character);
        Character(std::string name, std::string value_character);
        Character(std::string name, int value_character);
        Character(std::string name, float value_character);

        void setValue(char value_character);
        void setValue(std::string value_character);
        char getValue() const;

        /* Operations */

        bool hasOperation(std::string op) const;

        Variable set(const Variable& var);
        bool eq(const Character& character);
        bool notEq(const Character& character);

        bool less(const Character& character);
        bool greater(const Character& character);
        bool lessEq(const Character& character);
        bool greaterEq(const Character& character);

        Character _add(const Character& character);
        Character _sub(const Character& character);
        Character _add(const Number& number);
        Character _sub(const Number& number);

        String cat(const Character& character);
        String cat(const String& string);
};