#pragma once

#include <string>

#ifndef KEYWORDS

    #define KW_FUNCTION "function"
    #define KW_END      "end"

    #define KW_IF       "if"
    #define KW_ELSIF    "elsif"
    #define KW_ELSE     "else"

    #define KW_YIELD    "yield"
    #define KW_YIELD_ALT "return"

    #define KW_TAKES    "takes"
    #define KW_TAKES_ALT    "input"

    #define KW_YIELDS   "yields"
    #define KW_YIELDS_ALT   "outputs"

    #define KW_WHILE    "while"

#endif /* KEYWORDS */

bool isKeyword(std::string str);