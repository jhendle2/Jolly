#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "general_utils.hpp"

enum TokensBlockType{
    BLOCK_FUNCTION,
    BLOCK_LINES,
    BLOCK_INCLUDE,
};

struct TokensBlock{
    enum TokensBlockType type;
    std::string block_name;
    std::vector<std::string> lines;
};

void removeNewLine(std::string& in);
std::vector<std::string> readFileAsLines(std::string filename);
std::vector<struct TokensBlock> readLinesAsLinesAndFunctions(Tokens lines);