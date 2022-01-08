#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct readLinesStruct{
    bool is_function;
    std::string function_name;
    std::vector<std::string> lines;
};

void removeNewLine(std::string& in);
std::vector<std::string> readFileAsLines(std::string filename);
std::vector<struct readLinesStruct> readLinesAsLinesAndFunctions(std::vector<std::string> lines);