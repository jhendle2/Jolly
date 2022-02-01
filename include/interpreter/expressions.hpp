#pragma once

#include "types.hpp"
#include "scope.hpp"
#include "tokens.hpp"

Variable evaluateExpression(Scope*& current_scope, Tokens tokens);