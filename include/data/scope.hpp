#pragma once

#include <string>
#include <unordered_map>

#include "variable.hpp"

enum ScopeType{
    SCOPE_NORMAL,
    SCOPE_CONDITIONAL,
    SCOPE_FUNCTION
};

class Scope{
    protected:
        std::string name;
        enum ScopeType type;

        std::unordered_map<std::string, Variable> variables; // Variables DIRECTLY within this scope
        std::unordered_map<std::string, Scope*> scopes; // Scopes DIRECTLY within this scope

        bool truthiness; // If we should actually run this scope

    public:
        Scope(std::string name);
        Scope(std::string name, enum ScopeType type);

        void setTruthiness(bool truthiness);
        bool getTruthiness() const;

        void setName(std::string name);
        std::string getName() const;
    
};