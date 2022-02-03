#pragma once

#include "scope.hpp"
#include "variable.hpp"

Variable evaluateExpression(ScopePtr& current_scope, Tokens tokens);