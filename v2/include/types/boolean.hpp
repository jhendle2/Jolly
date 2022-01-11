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
        Boolean _and(const Boolean& right);
        Boolean _andEq(const Boolean& right);
        Boolean _or(const Boolean& right);
        Boolean _orEq(const Boolean& right);
        Boolean _xor(const Boolean& right);
        Boolean _xorEq(const Boolean& right);       
};