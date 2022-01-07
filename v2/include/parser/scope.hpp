#pragma once

#include <vector>
#include <unordered_map>

#include "object.hpp"
#include "variable.hpp"
#include "object_table.hpp"

enum ScopeType{
    SCOPE_NORMAL,

    SCOPE_IF,
    SCOPE_ELSE,
    SCOPE_ELSIF,

    SCOPE_FUNCTION,
    SCOPE_CLASS,

    SCOPE_INVALID
};

std::string scopeTypeToString(enum ScopeType);

class Scope : public Object{
    protected:
        int last_scope_index;
        enum ScopeType scope_type;

        Scope* parent;
        Scope* next_scope;
        ObjectTable<Variable> variables;
        std::unordered_map<std::string, Scope*> scopes;

    public:
        Scope();
        Scope(std::string);
        Scope(enum ScopeType);
        Scope(std::string, enum ScopeType);
        virtual ~Scope();

        void setScopeType(enum ScopeType);
        enum ScopeType getScopeType();

        void addParameter(Object param);
        void addParameter(std::string name, Object param);
        // Object getParameter(int index);
        Object getParameter(std::string name);

        void setParameter(std::string name, Object value);

        void evaluateInner();

        virtual void dump();
        void dumpRecursive();

        void setParent(Scope* parent); // TODO: Copy child type from parent type
        Scope* getParent();
        bool hasParent();

        virtual void addNextScope(Scope* next_scope);
        virtual bool getNextScope(Scope* next_scope);
        virtual bool hasNextScope();

        /*****************************************/
        ObjectTable<Variable>& getVariables();

        void addVariable(Variable var);
        void addVariable(std::string name, Variable var);
        void addVariable(enum AccessSpecifier access_specifier, Variable var);
        void addVariable(std::string name, enum AccessSpecifier access_specifier, Variable var);

        // void updateVariable(Variable var, const Variable& value);
        void updateVariable(Variable var);
        void updateVariable(std::string name, Variable value);
        Variable updateVariableAndGet(Variable var);

        void updateVariableRecursive(std::string name, Variable var);
        void updateVariableRecursive(Variable var);
        Variable updateVariableAndGetRecursive(std::string name, Variable var);
        Variable updateVariableAndGetRecursive(Variable var);

        Variable getVariable(std::string name);
        bool getVariableRecursive(std::string name, Variable& var);

        /*****************************************/
        void addScope(Scope scope);
        void addScope(Scope* scope);
        void addScope(enum AccessSpecifier access_specifier, Scope scope);
        void addScope(enum AccessSpecifier access_specifier, Scope* scope);

        Scope* getScope(std::string name);
        bool hasScope(std::string name);

        void updateScope(std::string name, Scope scope);
        Scope* updateAndGetScope(std::string name, Scope scope);

        int lastScopeIndex();

        /*****************************************/
        bool isKnown(std::string name); // Do I have this variable or scopetion?
        bool isKnownVariable(std::string name);
        enum ObjectType isKnownAndType(std::string name); // Do I have this variable or scopetion? If yes --> return TYPE_VARIABLE or TYPE_FUNCTION. If not, TYPE_INVALID
};

void addScopeToScope(Scope& parent, Scope& child);
void addScopeToScope(Scope* parent, Scope* child);