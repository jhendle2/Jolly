#pragma once

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

bool isDelimiter(char c);
bool isOperator(char c);