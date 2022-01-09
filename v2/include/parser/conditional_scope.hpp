#pragma once

#include "scope.hpp"
#include "boolean.hpp"

class ConditionalScope : public Scope{
    private:
        bool truthiness;
        std::vector<std::string> condition_tokens;
        ConditionalScope* next_conditional_scope;
    
    public:
        ConditionalScope(enum ScopeType scope_type, int id, bool truthiness);
        ~ConditionalScope();

        void addNextScope(ConditionalScope* next_conditional_scope);
        bool getNextScope(ConditionalScope* next_conditional_scope);
        bool hasNextScope();

        Boolean evaluateCondition();

        void dump();
};

bool isConditionalScope(Scope& scope);
bool isConditionalScope(Scope* scope);