#pragma once

#include "tokens.hpp"
#include "scope.hpp"

void interpret_tokens(Scope*& current_scope, Tokens tokens);