#pragma once

#include <string>
#include <unordered_map>

#include "variable.hpp"

enum ScopeType{
    SCOPE_NORMAL,
    SCOPE_CONDITIONAL,
    SCOPE_FUNCTION,
    SCOPE_LOOP,
};

std::string scopeTypeToString(enum ScopeType type);

class Scope{
    protected:
        std::string name;
        enum ScopeType type;
        Scope* parent;

        std::unordered_map<std::string, Variable> variables; // Variables DIRECTLY within this scope
        std::unordered_map<std::string, Scope*> scopes; // Scopes DIRECTLY within this scope

        bool truthiness; // If we should actually run this scope

    public:
        Scope(std::string name);
        Scope(std::string name, enum ScopeType type);
        virtual ~Scope();

        void setTruthiness(bool truthiness);
        bool getTruthiness() const;

        void setScopeType(enum ScopeType type);
        enum ScopeType getScopeType();

        void setName(std::string name);
        std::string getName() const;

        void setParent(Scope* parent);
        Scope* getParent() const;

        virtual void dump();
        void dumpRecursive();
    
        /************************************/

        void addVariable(std::string name, Variable var);
        void addVariable(Variable var);
        bool hasVariable(std::string name) const;
        bool hasVariableRecursive(std::string name) const;
        bool hasVariableExact(std::string name) const;
        bool hasVariableRecursiveExact(std::string name) const;
        bool getVariable(std::string name, Variable& var);
        bool getVariableRecursive(std::string name, Variable& var);
        void updateVariable(std::string name, Variable var);
        void updateVariable(Variable var);
        void updateVariableRecursive(std::string name, Variable var);
        void updateVariableRecursive(Variable var);

        Variable& getVariableRef(std::string name); // Gets a reference to the exact variable

        /************************************/

        void addScope(std::string name, Scope* scope);
        void addScope(Scope* scope);
        bool hasScope(std::string name) const;
        bool hasScopeRecursive(std::string name) const;
        bool getScope(std::string name, Scope*& scope);
        bool getScopeRecursive(std::string name, Scope*& scope);
        void updateScope(std::string name, Scope* scope);
        void updateScope(Scope* scope);
        void updateScopeRecursive(std::string name, Scope* scope);
        void updateScopeRecursive(Scope* scope);

        /************************************/
};

void checkNullScope(Scope* scope);
void addScopeToScope(Scope*& parent, Scope* child); // This assigns parenthood, which we cannot do inside the normal class addScope method