#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "tokens_lines.hpp"
#include "parser.hpp"

void parseTreeButIgnoreFunctionsAndClasses(ScopePtr& current_scope);
void evaluateTakes(ScopePtr& current_scope, Tokens tokens, const Variable& param_value);

Variable parseFunctionCall(ScopePtr& current_scope, std::vector<Variable> params, size_t last_parameter_index);
Variable parseFunctionCall(ScopePtr& current_scope, std::vector<Variable> params);
Variable parseFunctionCall(ScopePtr& current_scope, Tokens params_tokens);

std::vector<Variable> tokensToListOfVariables(ScopePtr& current_scope, Tokens tokens);
