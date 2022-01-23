#pragma once

#include "variable.hpp"

class Boolean : public Variable{
    public:
        Boolean();
        Boolean(bool value_boolean);
        Boolean(const Variable& var);
        Boolean(std::string name);
        Boolean(std::string name, bool value_boolean);
        Boolean(std::string name, std::string value_boolean);

        void setValue(bool value_boolean);
        bool getValue() const;

        /* Operations */

        bool hasOperation(std::string op) const;

        Variable set(const Boolean& boolean);
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