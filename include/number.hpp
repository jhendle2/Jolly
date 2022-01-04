#pragma once

#include "variable.hpp"

class Number : public Variable{
    public:
        Number();
        Number(int number);
        Number(std::string str);
        Number(const Variable& var);

        void increment(); // ++
        void decrement(); // --
        Number eq(const Number& right); // =

        Variable equality(const Number& right); // ==
        Variable inequality(const Number& right); // !=
        Variable less(const Number& right); // <
        Variable greater(const Number& right); // >
        Variable lessEq(const Number& right); // <=
        Variable greaterEq(const Number& right); // >=

        Number add(const Number& b);
        Number subtract(const Number& b);
        Number multiply(const Number& b);
        Number divide(const Number& b);
        Number power(const Number& b);
        Number mod(const Number& b);

        void addEq(const Number& b);
        void subtractEq(const Number& b);
        void multiplyEq(const Number& b);
        void divideEq(const Number& b);
        void powerEq(const Number& b);
        void modEq(const Number& b);
};