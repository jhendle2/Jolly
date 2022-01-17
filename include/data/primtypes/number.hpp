#pragma once

#include "variable.hpp"

class Number : public Variable{
    protected:
        bool show_decimal;
        float value;
    
    public:
        Number(float value);
        Number(int value);
        Number(std::string name);
        Number(std::string name, float value);
        Number(std::string name, int value);

        void setShowDecimal(bool show_decimal);
        bool showDecimal() const;

        void setValue(float value);
        void setValue(int value);
        float getValue() const;

        std::string toString();
        std::string stringValue();
        
        /* Operations */

        void set(const Number& number);
        bool eq(const Number& number);
        bool notEq(const Number& number);

        bool less(const Number& number);
        bool greater(const Number& number);
        bool lessEq(const Number& number);
        bool greaterEq(const Number& number);

        Number add(const Number& number);
        Number sub(const Number& number);
        Number mul(const Number& number);
        Number div(const Number& number);
        Number mod(const Number& number);
        Number exp(const Number& number);
};