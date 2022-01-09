#pragma once

#include "variable.hpp"

class String : public Variable{
    public:
        String();
        String(const char*);
        String(const std::string);
        String(const Variable&);

        Variable add(const Variable& right);
        Variable addEq(const Variable& right);
        Variable mul(const Variable& right);
        Variable mulEq(const Variable& right);
};