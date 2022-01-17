#pragma once

#include <string>

#include "primtypes.hpp"

class Variable{
    protected:
        std::string name;
        enum PrimType type;
    
    public:
        Variable();
        Variable(std::string);
        Variable(enum PrimType);
        Variable(std::string, enum PrimType);

        enum PrimType getType() const;
        void setName(std::string);
        std::string getName() const;

        virtual std::string toString();
        virtual void dumpString();
        virtual std::string stringValue(); // the actual value held in the variable as a string
};