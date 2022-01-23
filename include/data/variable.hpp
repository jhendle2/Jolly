#pragma once

#include <string>

#include "primtypes.hpp"

class Type;

class Variable{
    protected:
        std::string name;
        enum PrimType type;

        bool value_boolean;
        char value_character;
        double value_number;
        bool value_number_show_decimal;
        std::string value_string;
        enum PrimType value_type;
    
    public:
        Variable();
        Variable(std::string);
        Variable(enum PrimType);
        Variable(std::string, enum PrimType);

        enum PrimType getPrimType() const;
        Type getType() const;
        void setName(std::string);
        std::string getName() const;

        bool getValueBoolean() const;
        char getValueCharacter() const;
        double getValueNumber() const;
        bool getValueNumberShowDecimal() const;
        std::string getValueString() const;
        enum PrimType getValueType() const;

        virtual std::string toString() const;
        virtual void dumpString() const;
        virtual std::string stringValue() const; // the actual value held in the variable as a string

        virtual Variable set(const Variable& var);
        virtual bool eq(const Variable& var);
        virtual bool notEq(const Variable& var);

        virtual bool hasOperation(std::string op) const;

        virtual Variable _add(const Variable& var){return Variable();}
        virtual Variable _sub(const Variable& var){return Variable();}
        virtual Variable _mul(const Variable& var){return Variable();}
        virtual Variable _div(const Variable& var){return Variable();}
        virtual Variable _mod(const Variable& var){return Variable();}
        virtual Variable _exp(const Variable& var){return Variable();}
        virtual Variable _addEq(const Variable& var){return Variable();}
        virtual Variable _subEq(const Variable& var){return Variable();}
        virtual Variable _mulEq(const Variable& var){return Variable();}
        virtual Variable _divEq(const Variable& var){return Variable();}
        virtual Variable _modEq(const Variable& var){return Variable();}
        virtual Variable _cat(const Variable& var){return Variable();}
        virtual Variable _not(const Variable& var){return Variable();}
        virtual Variable _or(const Variable& var){return Variable();}
        virtual Variable _xor(const Variable& var){return Variable();}
        virtual Variable _and(const Variable& var){return Variable();}
        virtual Variable _orEq(const Variable& var){return Variable();}
        virtual Variable _xorEq(const Variable& var){return Variable();}
        virtual Variable _andEq(const Variable& var){return Variable();}
        virtual Variable _less(const Variable& var){return Variable();}
        virtual Variable _lessEq(const Variable& var){return Variable();}
        virtual Variable _greater(const Variable& var){return Variable();}
        virtual Variable _greaterEq(const Variable& var){return Variable();}
};

bool isDigit(char c);
bool isCharacter(std::string s);
bool isNumber(std::string s);
bool isDecimal(std::string s);
bool isString(std::string s);
bool isBoolean(std::string s);