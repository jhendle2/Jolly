#pragma once

#include <vector>

#include "variable.hpp"

class List : public Variable{
    // protected:
    public:
        std::vector<Variable> list;
        List();
        // List(const Variable& var);

        void push_back(Variable var);
        int length();

        Variable add(const Variable& var);
        Variable addEq(const Variable& var);

        std::string toStringValue();
        void dump();
};