#pragma once

#include <vector>

#include "scope.hpp"
#include "tokens.hpp"

enum LoopType{
    LOOP_WHILE,
    LOOP_FOR,
    LOOP_FOREACH,
    LOOP_DOWHILE,
    LOOP_COUNT,
    LOOP_INVALID,
};

bool isLoopType(std::string token);
std::string loopTypeToString(enum LoopType loop_type);
enum LoopType tokenToLoopType(std::string token);

class Loop : public Scope{
protected:
    std::vector<Tokens> lines;
    Tokens loop_condition;
    enum LoopType loop_type;

public:
    Loop(enum LoopType);

    void setLoopCondition(Tokens condition);
    Tokens getLoopCondition();

    void dump();

    void addLine(Tokens tokens);
    std::vector<Tokens> getLines();

    enum LoopType getLoopType();

};

bool evaluateLoopCondition(Loop*& loop);
void evaluateLoop(Loop*& loop);