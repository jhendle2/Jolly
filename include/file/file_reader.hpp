#pragma once

#include <string>
#include <vector>

struct Line{
    int line_number;
    std::string line;
};

std::string lineToString(struct Line line);

std::vector<struct Line> readFileAsLines(std::string filename);