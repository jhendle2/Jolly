#pragma once

#include <vector>
#include <unordered_set>

#include "scope.hpp"
#include "variable.hpp"

// struct ParameterList{
//     std::vector<std::string> names;
//     std::vector<Variable> variables;
// };

class Function : public Scope{
    protected:
        enum ObjectType return_type;
        // struct ParameterList params;

    public:
        Function(std::string function_name);
        Function(std::string function_name, enum ObjectType return_type);
        // ~Function();

        void addParam(std::string name, Variable param); // initializes a variable with name function_name.variable_name & adds to variables list
        void setParam(std::string name, Variable param);
        
        std::vector<std::string> unprocessed_lines;
        void addLine(std::string line); // lines to be processed later

        enum ObjectType getReturnType();
        void setReturnVariable(Variable return_variable);
        Variable getReturnVariable(); // doesn't re-evaluate me

        void dump();
        void dumpRecursive();
};

Variable returnFunction(Function* func); // re-evaluates return variable