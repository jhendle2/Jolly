#pragma once

#include <string>
#include <vector>

#include "constants.hpp"

bool isVariableType(std::string str);

class Variable{
    protected:
        enum Type type = TYPE_NOTHING;
        int number = 0;
        char character = 0;
        bool boolean = false;
        std::string string = "";

        bool initialized = false;

    public:
        Variable();
        Variable(enum Type);
        Variable(const int);
        Variable(const char);
        Variable(const bool);
        Variable(const char*);
 
        void set(const int);
        void set(const char);
        void set(const bool);
        void set(const char*);
        void set(const Variable& right);

        virtual void addEq(const Variable& right); // +=
        virtual void subtractEq(const Variable& right); // -=
        virtual void multiplyEq(const Variable& right); // *=
        virtual void divideEq(const Variable& right); // /=
        virtual void modEq(const Variable& right); // %=
        virtual void powerEq(const Variable& right); // ^=

        virtual Variable add(const Variable& right); // +
        virtual Variable subtract(const Variable& right); // -
        virtual Variable multiply(const Variable& right); // *
        virtual Variable divide(const Variable& right); // /
        virtual Variable mod(const Variable& right); // %
        virtual Variable power(const Variable& right); // ^

        virtual void increment(); // ++
        virtual void decrement(); // --
        virtual Variable eq(const Variable& right); // =

        virtual Variable equality(const Variable& right); // ==
        virtual Variable inequality(const Variable& right); // !=
        virtual Variable less(const Variable& right); // <
        virtual Variable greater(const Variable& right); // >
        virtual Variable lessEq(const Variable& right); // <=
        virtual Variable greaterEq(const Variable& right); // >=

        bool isInitialized();

        void setFromString(std::string);

        std::string toString();
        enum Type getType();
        int getNumber();
        bool getBoolean();
        char getCharacter();
        std::string getString();
        std::string dump();

        bool canMergeWith(const Variable& right);
        void merge(const Variable& right);

};
