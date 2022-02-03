#pragma once

#include "scope.hpp"
#include "scope_builder.hpp"

ScopePtr buildTreeFromFile(std::string file_path);

void parseTree(ScopePtr& current_scope);
void parseTreeButIgnoreFunctionsAndClasses(ScopePtr& current_scope);

void evaluateLine(ScopePtr& current_scope, Tokens tokens);
void evaluateKeyword(ScopePtr& current_scope, Tokens tokens);
void evaluateOpenScopeLine(ScopePtr& current_scope, Tokens tokens);
void evaluateCloseScopeLine(ScopePtr& current_scope, Tokens tokens);