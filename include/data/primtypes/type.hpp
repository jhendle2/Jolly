#pragma once

#include "variable.hpp"

class Type : public Variable{
    public:
        Type();
        Type(const Variable& var);
        Type(std::string name);
        Type(enum PrimType value_type);
        Type(std::string name, enum PrimType value_type);

        void setValue(enum PrimType value_type);
        enum PrimType getValue() const;

        bool hasOperation(std::string op) const;

        Variable set(const Variable& t);
        bool eq(const Type& t);
        bool notEq(const Type& t);
};