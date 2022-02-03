#pragma once

#include <string>
#include <memory>

#include "variable_type.hpp"

class Scope; // prototype

class Variable{
protected:
    std::string name;
    VarType type;

    struct {
        bool boolean;
        char character;
        std::string string;
        double number;
        VarType type;
    } value;

    std::shared_ptr<Scope> parent;

public:

    Variable();
    Variable(bool boolean);
    Variable(std::string name, std::string type);
    Variable(std::string name, VarType type);

    void setValue(const bool& value);
    void setValue(const char& value);
    void setValue(const std::string& value);
    void setValue(const double& value);
    void setValue(const VarType& value);
    
    bool getBoolean() const;
    char getCharacter() const;
    std::string getString() const;
    double getNumber() const;
    VarType getType() const;

    void setName(std::string name);
    std::string getName() const;
    void setType(std::string type);
    VarType getValueType() const;

    void setParent(std::shared_ptr<Scope> parent);
    std::shared_ptr<Scope> getParent() const;

    std::string valueString() const;
    std::string dump() const;

    /* Operators */

    virtual void _set(const Variable& right);
    virtual bool _eq(const Variable& right);
    virtual bool _notEq(const Variable& right);

    virtual Variable _add(const Variable& right); // +
    virtual Variable _sub(const Variable& right); // -
    virtual Variable _mul(const Variable& right); // *
    virtual Variable _div(const Variable& right); // /
    virtual Variable _pow(const Variable& right); // ^
    virtual Variable _mod(const Variable& right); // %

    virtual Variable _and(const Variable& right); // and
    virtual Variable _or(const Variable& right); // or
    virtual Variable _xor(const Variable& right); // xor

    virtual Variable _cat(const Variable& right); // ~
    virtual Variable _type(const Variable& right); // $
};