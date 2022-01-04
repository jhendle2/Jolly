#pragma once

#include <unordered_map>
#include <string>

#include "variable.hpp"

void setVariable(std::string name, Variable var);
Variable getVariable(std::string name);
bool isKnownVariable(std::string name);

void updateVariable(std::string name, Variable value);
void updateVariable(std::string name, std::string value_expression);
void updateVariableFromOtherVariable(std::string name, std::string other_name);
void setVariableFromOtherVariable(std::string name, std::string other_name);

void dumpVariables();