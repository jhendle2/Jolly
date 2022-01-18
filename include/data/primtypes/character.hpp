#pragma once

#include "variable.hpp"
#include "number.hpp"
#include "string.hpp"

class String; // Forward declared so the 'cat' function works

class Character : public Variable{
    protected:
        char value;
    
    public:
        Character(char value);
        Character(std::string name);
        Character(std::string name, char value);
        Character(std::string name, std::string value);

        void setValue(char value);
        void setValue(std::string value);
        char getValue() const;

        std::string stringValue() const;

        /* Operations */

        void set(const Character& character);
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
};