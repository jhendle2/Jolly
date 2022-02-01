#pragma once

#include "variable.hpp"
#include "character.hpp"
#include "boolean.hpp"
#include "number.hpp"
#include "type.hpp"

class Character;

class String : public Variable{
    public:
        String();
        String(const Variable& var);
        String(std::string value_string);
        String(std::string name, char value_string);
        String(std::string name, std::string value_string);
            
        void setValue(char value_string);
        void setValue(std::string value_string);
        std::string getValue() const;

        /* Operations */

        bool hasOperation(std::string op) const;

        Variable set(const Variable& var);
        bool eq(const Variable& var);
        bool notEq(const Variable& var);
        Number _len();

        bool _less(const String& string);
        bool _lessEq(const String& string);
        bool _greater(const String& string);
        bool _greaterEq(const String& string);

        String _add(const String& string);
        String _mul(const Number& number);
        String cat(const String& string);
        String cat(const Character& character);
        String cat(const Boolean& boolean);
        String cat(const Number& number);
        String cat(const Type& t);
};