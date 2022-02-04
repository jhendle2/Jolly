#pragma once

#include "variable.hpp"
#include "scope.hpp"
#include "scope_builder.hpp"

ScopePtr buildTreeFromFile(std::string file_path);

void parseTree(ScopePtr& current_scope);

void evaluateLine(ScopePtr& current_scope, Tokens tokens);
void evaluateKeyword(ScopePtr& current_scope, Tokens tokens);
void evaluateOpenScopeLine(ScopePtr& current_scope, Tokens tokens);

#define ifScopeCanRun(X) if(current_scope->getTruthiness() == true)
#define ifScopeCannotRun(X) if(current_scope->getTruthiness() == false)