#pragma once

#include <string>
#include <unordered_map>

#ifndef DELIMITER

    #define DELIM_ADD '+'
    #define DELIM_SUB '-'
    #define DELIM_MULT '*'
    #define DELIM_DIV '/'
    #define DELIM_MOD '%'
    #define DELIM_EXP '^'
    #define DELIM_CAT '~'

    #define DELIM_PAREN_OPEN '('
    #define DELIM_PAREN_CLOSE ')'
    #define DELIM_BRACKET_OPEN '['
    #define DELIM_BRACKET_CLOSE ']'
    #define DELIM_BRACE_OPEN '{'
    #define DELIM_BRACE_CLOSE '}'

    #define DELIM_LESS '<'
    #define DELIM_GREATER '>'
    #define DELIM_EQ '='
    #define DELIM_NOT '!'

    #define DELIM_AND '&'
    #define DELIM_OR '|'
    #define DELIM_XOR '^'

    #define DELIM_DOT '.'
    #define DELIM_COMMA ','
    #define DELIM_COLON ':'
    #define DELIM_SEMICOLON ';'

    #define DELIM_QUESTION '?'
    #define DELIM_BACKSLASH '\\'
    #define DELIM_AT '@'

#endif /* DELIMITER */

#ifndef OPERATORS

    #define OP_PLUSPLUS "++"
    #define OP_MINUSMINUS "--"
    #define OP_EXP "^"
    #define OP_MOD "%"
    #define OP_MUL "*"
    #define OP_DIV "/"
    #define OP_ADD "+"
    #define OP_SUB "-"
    #define OP_LESS "<"
    #define OP_GREATER ">"
    #define OP_LESSEQ "<="
    #define OP_GREATEREQ ">="
    #define OP_EQUALITY "=="
    #define OP_INEQUALITY "!="
    #define OP_AND "and"
    // #define OP_MINUSMINUS "&&"
    #define OP_XOR "xor"
    // #define OP_MINUSMINUS "^^"
    #define OP_OR "or"
    // #define OP_MINUSMINUS "||"
    #define OP_ADDEQ "+="
    #define OP_SUBEQ "-="
    #define OP_MULEQ "*="
    #define OP_DIVEQ "/="
    #define OP_MODEQ "%="
    #define OP_OREQ "|="
    // #define OP_MINUSMINUS "or="
    #define OP_XOREQ "^="
    // #define OP_MINUSMINUS "xor="
    #define OP_ANDEQ "&="
    // #define OP_MINUSMINUS "and="
    #define OP_EQ "="
    #define OP_COLON ":"
    #define OP_COMMA ","
    #define OP_SEMICOLON ";"
    #define OP_CAT "~"
    #define OP_DOT "~"
    #define OP_QUESTION "?"
    #define OP_NOT "!"
    #define OP_AT "!"
    #define OP_PAREN_OPEN "("
    #define OP_PAREN_CLOSE ")"

#endif /* OPERATORS */

extern std::unordered_map<std::string, int> op_priority;

bool isDelimiter(char c);
bool isOperator(char c);
bool isOperator(std::string s);
int precedence(std::string op);
bool isSetOperation(std::string op);
bool isDigit(char c);