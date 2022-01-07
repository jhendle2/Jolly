#include "general_utils.hpp"
#include "conditional_scope.hpp"

ConditionalScope::ConditionalScope(enum ScopeType scope_type, int id) : Scope(scope_type){
    next_conditional_scope = nullptr;
    name = scopeTypeToString(scope_type) + "." + std::to_string(id);
}

ConditionalScope::~ConditionalScope(){
    if(next_conditional_scope != nullptr){
        delete next_conditional_scope;
        next_conditional_scope = nullptr;
    }
}

Boolean ConditionalScope::evaluateCondition(){
    return Boolean(false);
}

void ConditionalScope::addNextScope(ConditionalScope* next_conditional_scope){
    if(this->next_conditional_scope == nullptr){
        this->next_conditional_scope = next_conditional_scope;
    }
}

bool ConditionalScope::getNextScope(ConditionalScope* next_conditional_scope){
    if(this->next_conditional_scope != nullptr){
        next_conditional_scope = this->next_conditional_scope;
        return true;
    }
    return false;
}

bool ConditionalScope::hasNextScope(){
    return (next_conditional_scope != nullptr);
}

void ConditionalScope::dump(){
    std::cout<<"\n===========CONDITIONAL_SCOPE("<<name<<")===========\n";

    if(parent != nullptr) std::cout<<"PARENT SCOPE: "<<parent->getName()<<"\n";
    else std::cout<<"NO PARENT!\n";
    std::cout<<"##CONDITION: "<<tokensToString(condition_tokens)<<"\n";
    
    std::cout<<"##VARIABLES##:\n";
    variables.dump(); std::cout<<"\n\n";

    if(hasNextScope()) std::cout<<"##NEXT CONDITIONAL SCOPE: "<<next_conditional_scope->getName()<<"\n";
    else std::cout<<"##NO NEXT CONDITIONAL SCOPE!\n";

    std::cout<<"##SCOPES##:\n";
    std::cout<<"\n------------------------------------------\n";
    for(auto pair : scopes){
        std::cout<<"* "<<pair.second->getName()<<"\n";
    }
    std::cout<<"\n==========================================\n";
}

bool isConditionalScope(Scope& scope){
    return (
        scope.getScopeType() == SCOPE_IF ||
        scope.getScopeType() == SCOPE_ELSE ||
        scope.getScopeType() == SCOPE_ELSIF
    );
}

bool isConditionalScope(Scope* scope){
    return (
        scope->getScopeType() == SCOPE_IF ||
        scope->getScopeType() == SCOPE_ELSE ||
        scope->getScopeType() == SCOPE_ELSIF
    );
}