#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void removeNewLine(std::string& in);
std::vector<std::string> readFileAsLines(std::string filename);