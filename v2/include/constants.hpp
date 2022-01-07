#pragma once

#include <string>

enum ObjectType{
    TYPE_NOTHING,

    TYPE_NUMBER,
    TYPE_CHAR,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_OBJECT,
    TYPE_VARIABLE,
    TYPE_FUNCTION,

    TYPE_INVALID,
};

bool isObjectType(std::string s);

bool isDigit(char d);
bool isString(std::string s);
bool isChar(std::string s);
bool isNumber(std::string s);
bool isBool(std::string s);
bool isNothing(std::string s);

enum ObjectType getTypeFromConstant(std::string str);
enum ObjectType getTypeFromString(std::string str);

std::string typeToString(enum ObjectType type);