#pragma once

#include "object.hpp"

class Variable : public Object{
    protected:
        int number;
        bool boolean;
        char character;
        std::string string;

    public:
        Variable();
        ~Variable();
        
        Variable(enum ObjectType type);

        Variable(const int number);
        Variable(const bool boolean);
        Variable(const char character);
        Variable(const char* string);
        Variable(const std::string string);

        int getNumber();
        bool getBoolean();
        char getCharacter();
        std::string getString();

        std::string toString();
        std::string toStringValue(); // gets just the value as a string
        void dump();

        virtual Variable eq(const Variable& right);
        virtual Variable equality(const Variable& right);
        virtual Variable inequality(const Variable& right);

        virtual Variable add(const Variable& right);
        virtual Variable addEq(const Variable& right);
};