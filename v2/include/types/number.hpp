#pragma once

#include "variable.hpp"

class Number : public Variable{
    private:

    public:
        Number();
        Number(const int);
        Number(const Variable&);
        Number(std::string);

        Number add(const Number& right);
        Number addEq(const Number& right);
};