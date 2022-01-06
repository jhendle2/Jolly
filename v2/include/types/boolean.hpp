#pragma once

#include "variable.hpp"

class Boolean : public Variable{
    public:
        Boolean();
        Boolean(const bool boolean);
        Boolean(const Variable& var);
        Boolean(const char* string);
        Boolean(const std::string string);

        // Boolean not(const Boolean& right);
        Boolean add(const Boolean& right);
        Boolean addEq(const Boolean& right);
};