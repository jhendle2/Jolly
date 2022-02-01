#pragma once

#include <string>

std::string removeBracketing(std::string str_in, char bracket);
std::string removeSingleQuotes(std::string str_in);
std::string removeDoubleQuotes(std::string str_in);

bool endsInJollyExtension(std::string str_in);
std::string dropExtension(std::string str_in);