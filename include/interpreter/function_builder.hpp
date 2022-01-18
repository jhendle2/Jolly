#pragma once

#include "tokens.hpp"

struct FunctionBlock{
    std::string name;
    std::vector<Tokens> lines;
};

bool tokensIsFunctionHeader(Tokens tokens, std::string& function_name);
bool tokensIsFunctionCloser(Tokens tokens, std::string function_name);