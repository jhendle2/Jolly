#pragma once

#include "scope.hpp"
#include "tokens_lines.hpp"

namespace StandardJolly{

    bool isBuiltin(const std::string& keyword);
    Variable runBuiltin(ScopePtr& current_scope, const Tokens& tokens);

    void Print(ScopePtr& current_scope, const Tokens& tokens);
    void Println(ScopePtr& current_scope, const Tokens& tokens);
    Variable Typeof(ScopePtr& current_scope, const Tokens& tokens);

};