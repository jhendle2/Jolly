#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "tokens_lines.hpp"
#include "scope.hpp"

void emptyConditionalStack();

void evaluateOpenScopeLine(ScopePtr& current_scope, Tokens tokens);