#pragma once

#include "variable.hpp"

class Character : public Variable{
    public:
        Character();
        Character(const char);
        Character(const Variable&);
};