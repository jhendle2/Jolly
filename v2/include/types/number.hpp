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
};