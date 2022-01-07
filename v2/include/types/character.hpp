#pragma once

#include "variable.hpp"

class Character : public Variable{
    public:
        Character();
        Character(const char);
        Character(const int);
        Character(const Variable&);

        Character add(const Character& right);
        Character addEq(const Character& right);
        Character sub(const Character& right);
        Character subEq(const Character& right);
};