#pragma once

#include <vector>

#include "tokens_lines.hpp"

bool endsInJollyExtension(const std::string& str_in);

std::string lineToString(Line line);
std::string fileName(std::string file_path);
std::vector<Line> readFileAsLines(std::string file_path);