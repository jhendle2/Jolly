#pragma once

#include "variable.hpp"

class Boolean : public Variable{
    protected:
        bool value;
    
    public:
        Boolean(bool value);
        Boolean(std::string name);
        Boolean(std::string name, bool value);

        void setValue(bool value);
        bool getValue() const;
        
        std::string stringValue() const;

        /* Operations */

        void set(const Boolean& boolean);
        bool eq(const Boolean& boolean);
        bool notEq(const Boolean& boolean);

        Boolean _not();
        Boolean _and(const Boolean& boolean);
        Boolean _or(const Boolean& boolean);
        Boolean _xor(const Boolean& boolean);
        Boolean _nand(const Boolean& boolean);
        Boolean _nor(const Boolean& boolean);
        Boolean _xnor(const Boolean& boolean);
};