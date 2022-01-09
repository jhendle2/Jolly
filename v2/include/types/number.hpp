#pragma once

#include "variable.hpp"

class Number : public Variable{
    private:

    public:
        Number();
        Number(const int);
        Number(const char);
        Number(const Variable&);
        Number(std::string);

        Number add(const Number& right);
        Number addEq(const Number& right);
        Number sub(const Number& right);
        Number subEq(const Number& right);
        Number mul(const Number& right);
        Number mulEq(const Number& right);
        Number div(const Number& right);
        Number divEq(const Number& right);
        Number exp(const Number& right);
        Number expEq(const Number& right);
        Number mod(const Number& right);
        Number modEq(const Number& right);
};