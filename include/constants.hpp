#pragma once

#include <string>

enum Type{
    TYPE_NOTHING,

    TYPE_NUMBER,
    TYPE_CHAR,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_OBJECT,

    TYPE_INVALID,
};

bool isDigit(char d);
bool isString(std::string s);
bool isChar(std::string s);
bool isNumber(std::string s);
bool isBool(std::string s);
bool isNothing(std::string s);

enum Type getTypeFromConstant(std::string str);
enum Type getTypeFromString(std::string str);

std::string typeToString(enum Type type);