#pragma once

#include "variable.hpp"
#include "character.hpp"
#include "boolean.hpp"
#include "number.hpp"
#include "type.hpp"

class Character;

class String : public Variable{
    protected:
        std::string value;

    public:
        String();
        String(std::string value);
        String(std::string name, char value);
        String(std::string name, std::string value);
            
        void setValue(char value);
        void setValue(std::string value);
        std::string getValue() const;

        std::string stringValue() const;

        /* Operations */

        void set(const String& string);
        bool eq(const String& string);
        bool notEq(const String& string);
        Number _len();

        String _add(const String& string);
        String cat(const String& string);
        String cat(const Character& character);
        String cat(const Boolean& boolean);
        String cat(const Number& number);
        String cat(const Type& t);
};