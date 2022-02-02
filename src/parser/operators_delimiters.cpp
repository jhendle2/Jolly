#include "operators_delimiters.hpp"

std::unordered_map<std::string, int> op_priority = {
    {OP_PLUSPLUS, 10},
    {OP_MINUSMINUS, 10},
    {OP_EXP, 9},
    {OP_MOD, 8},
    {OP_MUL, 8},
    {OP_DIV, 8},
    {OP_ADD, 7},
    {OP_CAT, 7},
    {OP_SUB, 7},
    {OP_LESS, 6},
    {OP_GREATER, 6},
    {OP_LESSEQ, 6},
    {OP_GREATEREQ, 6},
    {OP_EQUALITY, 5},
    {OP_INEQUALITY, 5},
    {OP_AND, 4},
    {OP_XOR, 3},
    {OP_OR, 3},
    {OP_ADDEQ, 2},
    {OP_SUBEQ, 2},
    {OP_MULEQ, 2},
    {OP_DIVEQ, 2},
    {OP_MODEQ, 2},
    {OP_OREQ, 2},
    {OP_ANDEQ, 2},
    {OP_EQ, 2},
    {OP_COLON, 2},
    {OP_PAREN_OPEN, 0},
    {OP_PAREN_CLOSE, 0},
};

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

    // c == DELIM_DOT || // TODO: REIMPLEMENT THIS FOR DECIMALS
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

    c == DELIM_COMMA ||

    c == DELIM_QUESTION);
}

bool isOperator(std::string op){
    return (op_priority.count(op) > 0);
}

int precedence(std::string op){
    if(op_priority.count(op) > 0)
        return op_priority.at(op);
    else
        return op_priority.at("+");
        // ERROROUT(SyntaxErrorBadOperator, op);
}

bool isSetOperation(std::string op){
    return(
        op == OP_EQ ||
        op == OP_ADDEQ ||
        op == OP_SUBEQ ||
        op == OP_MULEQ ||
        op == OP_DIVEQ ||
        op == OP_MODEQ ||
        op == OP_XOREQ ||
        op == OP_OREQ ||
        op == OP_ANDEQ
    );
}

bool isDigit(char c){
    return(
        c >= '0' && c <= '9'
    );
}