#pragma once

#include <string>

#include "constants.hpp"

enum AccessSpecifier{
    PUBLIC, // PUBLIC
    PRIVATE, // MY / LOCAL
    PROTECTED,
};

std::string accessToString(enum AccessSpecifier);

class Object{
    protected:
        bool is_initialized;
        enum AccessSpecifier access;
        enum ObjectType type;
        std::string name;

    public:
        Object();
        Object(std::string);
        Object(enum ObjectType);
        Object(std::string, enum ObjectType);

        void initialize();
        bool isInitialized();

        void setAccess(enum AccessSpecifier);
        void setPublic();
        void setPrivate();
        void setProtecte();

        enum AccessSpecifier getAccess();
        enum ObjectType getType();

        void setName(const char*);
        void setName(std::string);
        std::string getName();

        virtual std::string toString();
        virtual void dump();
};