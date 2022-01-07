#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "variable.hpp"
#include "object_table.hpp"
#include "function.hpp"

Scope* buildVariableAndEvaluateExpressions(Scope* parent, std::vector<std::string> tokens);