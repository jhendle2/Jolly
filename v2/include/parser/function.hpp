#pragma once

#include "scope.hpp"

class Function : public Scope{
    protected:
        enum ObjectType return_type;
        Variable return_variable;
        bool has_been_evaluated;

        std::vector<std::string> lines; // lines of text within me to be evaluated later
        std::unordered_map<std::string, Object> params;

        Scope* function_scope;

    public:
        Function();
        Function(std::string name);
        Function(std::string name, enum ObjectType return_type);
        ~Function();
        
        enum ObjectType getReturnType();
        Variable getReturnVariable();

        // Variable returnMe();
        void dump();
        void dumpRecursive();

        void setHasBeenEvaluated();
        void clearHasBeenEvaluated();
        bool hasBeenEvaluated();

        void setFunctionScope(Scope* function_scope);
        Scope* getFunctionScope();

        int numLines();
        void addLine(std::string line);
        void popLine(int index);
        std::string getLine(int index);
        std::vector<std::string> getLineAsTokens(int index);
        std::vector<std::string> getLines();

        void addParameter(Object param);
        void addParameter(std::string name, Object value);
        Object getParameter(std::string name);
        void setParameter(std::string name, Object value);
};

// Function* initializeFunction(Scope* parent, std::string name);
Variable returnFunction(Function* function);
void buildFunctionFromItsLines(Function* function);