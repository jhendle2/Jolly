#pragma once

#include <vector>
#include <unordered_map>

#include "function_builder.hpp"
#include "scope.hpp"
#include "tokens.hpp"

class Function : public Scope{
protected:
    std::vector<std::string> params_order;
    struct FunctionBlock lines;
public:

    Function(std::string name);
    ~Function();

    void setLines(struct FunctionBlock lines);
    struct FunctionBlock getLines();

    void dump();

    void addParam(Variable param_variable);
    std::vector<std::string> getParamsOrder();
    void setReturnVariable(Variable return_variable);
};

Variable returnFunction(Function*& func);
Variable returnFunction(Function*& func, std::vector<Variable> args);