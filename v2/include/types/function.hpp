#pragma once

#include <vector>

#include "object.hpp"
#include "variable.hpp"
#include "object_table.hpp"

class BaseFunction : public Object{
    private:
        
    protected:
        enum ObjectType return_type;
        std::unordered_map<std::string, Object> params;
        Variable return_variable;

    public:
        BaseFunction() : Object("invalid_function", TYPE_FUNCTION){

        }
        BaseFunction(std::string name) : Object(name, TYPE_FUNCTION){
            return_variable = Variable(TYPE_NOTHING);
        }
        BaseFunction(std::string name, enum ObjectType return_type) : Object(name, TYPE_FUNCTION){
            this->return_type = return_type;
            return_variable = Variable(return_type);
        }
        
        enum ObjectType getReturnType(){
            return return_type;
        }
        Object getReturn(){
            return return_variable;
        }
};

class Function : public BaseFunction{
    private:
        ObjectTable<Variable> variables;

    public:
        Function();
        ~Function();

        Function(std::string name);
        Function(std::string name, enum ObjectType return_type);
        // Function(const BaseFunction& bf);
        
        Function(std::string name, std::vector<Object> params);
        Function(std::string name, enum ObjectType, std::vector<Object> params);

        void addParameter(Object param);
        void addParameter(std::string name, Object param);
        // Object getParameter(int index);
        Object getParameter(std::string name);

        void setParameter(std::string name, Object value);

        void evaluateInner();

        void dump();
        void dumpVariables();

    //protected:
        void addVariable(Variable var);
        void addVariable(enum AccessSpecifier access_specifier, Variable var);

        // void updateVariable(Variable var, const Variable& value);
        void updateVariable(std::string name, Variable value);

        Variable getVariable(std::string name);
};