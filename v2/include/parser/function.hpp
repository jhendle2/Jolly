#pragma once

#include "scope.hpp"

class Function : public Scope{
    protected:
        enum ObjectType return_type;
        std::unordered_map<std::string, Object> params;
        Variable return_variable;

    public:
        Function();
        Function(std::string name);
        Function(std::string name, enum ObjectType return_type);
        
        enum ObjectType getReturnType();
        Object getReturn();

        void dump();

        void addParameter(Object param);
        void addParameter(std::string name, Object value);
        Object getParameter(std::string name);
        void setParameter(std::string name, Object value);
};