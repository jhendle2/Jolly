#include "operators.hpp"

bool isDelimiter(char c){
    return (
    // c == DELIM_ADD ||
    // c == DELIM_SUB ||
    // c == DELIM_MULT ||
    // c == DELIM_DIV ||
    // c == DELIM_MOD ||
    // c == DELIM_EXP ||
    // c == DELIM_CAT ||

    c == DELIM_PAREN_OPEN ||
    c == DELIM_PAREN_CLOSE ||
    c == DELIM_BRACKET_OPEN ||
    c == DELIM_BRACKET_CLOSE ||
    c == DELIM_BRACE_OPEN ||
    c == DELIM_BRACE_CLOSE ||

    // c == DELIM_LESS ||
    // c == DELIM_GREATER ||
    // c == DELIM_EQ ||
    // c == DELIM_NOT ||

    // c == DELIM_AND ||
    // c == DELIM_OR ||
    // c == DELIM_XOR ||

    c == DELIM_DOT ||
    c == DELIM_COMMA ||
    c == DELIM_COLON ||
    c == DELIM_SEMICOLON ||

    // c == DELIM_QUESTION ||
    // c == DELIM_BACKSLASH ||
    c == DELIM_AT);
}

bool isOperator(char c){
    return (
    c == DELIM_ADD ||
    c == DELIM_SUB ||
    c == DELIM_MULT ||
    c == DELIM_DIV ||
    c == DELIM_MOD ||
    c == DELIM_EXP ||
    c == DELIM_CAT ||

    c == DELIM_LESS ||
    c == DELIM_GREATER ||
    c == DELIM_EQ ||
    c == DELIM_NOT ||

    c == DELIM_AND ||
    c == DELIM_OR ||
    c == DELIM_XOR ||

    c == DELIM_QUESTION);
}