#include "errors.hpp"

void cleanup_everything(Scope* scope){
    while(scope->hasParent())
        scope = scope->getParent();
    
    delete scope;
}