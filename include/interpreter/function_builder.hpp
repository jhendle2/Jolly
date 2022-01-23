#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "file_reader.hpp"
#include "tokens.hpp"

struct FunctionBlock{
    std::string name;
    std::vector<Tokens> lines;
};

struct FunctionsLinesPair{
    std::vector<Tokens> lines_as_tokens;
    std::vector<struct Line> file_as_lines;
    std::unordered_map<std::string, struct FunctionBlock> functions;
};

bool tokensIsFunctionHeader(Tokens tokens, std::string& function_name);
bool tokensIsFunctionCloser(Tokens tokens, std::string function_name);

struct FunctionsLinesPair LocateFunctionsAndLines(std::string filename);