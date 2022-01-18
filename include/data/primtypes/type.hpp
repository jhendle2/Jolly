#pragma once

#include "variable.hpp"

class Type : public Variable{
    protected:
        enum PrimType value;
        
    public:
        Type();
        Type(std::string name);
        Type(enum PrimType value);
        Type(std::string name, enum PrimType value);

        void setValue(enum PrimType value);
        enum PrimType getValue() const;

        std::string stringValue() const;

        void set(const Type& t);
        bool eq(const Type& t);
        bool notEq(const Type& t);
};