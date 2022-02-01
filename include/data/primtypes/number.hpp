#pragma once

#include "variable.hpp"

class Number : public Variable{
    public:
        Number();
        // Number(float value_number);
        Number(double value_number);
        Number(int value_number);
        Number(char value_number);
        Number(const Variable& var);
        Number(std::string name);
        Number(std::string name, double value_number);
        Number(std::string name, int value_number);
        Number(std::string name, char value_number);

        void setShowDecimal(bool show_decimal);
        bool showDecimal() const;

        // void setValue(float value_number);
        void setValue(int value_number);
        void setValue(double value_number);
        double getValue() const;

        /* Operations */

        bool hasOperation(std::string op) const;

        Variable set(const Number& number);
        bool eq(const Number& number);
        bool notEq(const Number& number);

        bool _less(const Number& number);
        bool _greater(const Number& number);
        bool _lessEq(const Number& number);
        bool _greaterEq(const Number& number);

        Number _add(const Number& number);
        Number _sub(const Number& number);
        Number _mul(const Number& number);
        Number _div(const Number& number);
        Number _mod(const Number& number);
        Number _exp(const Number& number);
};