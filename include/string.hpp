#pragma once

#include "variable.hpp"

class String : public Variable{
    public:
        String();
        String(std::string str);
        String(const Variable& var);

        String eq(const String& right); // =

        String equality(const String& right); // ==
        String inequality(const String& right); // !=

        String add(const String& b);

        void addEq(const String& b);
};