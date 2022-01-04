#pragma once

#include <unordered_map>
#include <string>

#include "function.hpp"

void setFunction(std::string name, Function var);
Function getFunction(std::string name);
bool isKnownFunction(std::string name);

bool isPrint(std::string token);

void dumpVariables();