#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "errors.hpp"
#include "number.hpp"

Number::Number() : Variable(0){

}

Number::Number(std::string str) : Variable(atoi(str.c_str())){

}

Number::Number(int number) : Variable(number){

}

Number::Number(const Variable& var){
    Variable v = var;
    number = v.getNumber();
}

void Number::increment(){
    number++;
}

void Number::decrement(){
    number--;
}

Number Number::add(const Number& b){
    Number out(number);
    out.addEq(b);
    return out;
}


Number Number::subtract(const Number& b){
    Number out(number);
    out.subtractEq(b);
    return out;
}


Number Number::multiply(const Number& b){
    Number out(number);
    out.multiplyEq(b);
    return out;
}


Number Number::divide(const Number& b){
    Number out(number);
    out.divideEq(b);
    return out;
}

Number Number::power(const Number& b){
    Number out(number);
    out.powerEq(b);
    return out;
}

Number Number::mod(const Number& b){
    Number out(number);
    out.modEq(b);
    return out;
}

void Number::addEq(const Number& b){
    number+=b.number;
}


void Number::subtractEq(const Number& b){
    number-=b.number;
}


void Number::multiplyEq(const Number& b){
    number*=b.number;
}

void Number::divideEq(const Number& b){
    if(b.number == 0){
        std::cout<<ArithmeticErrorDivideByZero<<"\n";
        exit(EXIT_FAILURE);
    }
    else number/=b.number;
}

void Number::powerEq(const Number& b){
    float af = (float)number;
    float bf = (float)b.number;
    number = (int)pow(af, bf);
}

void Number::modEq(const Number& b){
    number %= b.number;
}

Number Number::eq(const Number& right){
    number=right.number;
    return right;
}

Variable Number::equality(const Number& right){
    return Variable(number==right.number);
}
Variable Number::inequality(const Number& right){
    return Variable(!equality(right).getBoolean());
}
Variable Number::less(const Number& right){
    return Variable(number<right.number);
}
Variable Number::greater(const Number& right){
    return Variable(number>right.number);
}
Variable Number::lessEq(const Number& right){
    return Variable(!greater(right).getBoolean());
}
Variable Number::greaterEq(const Number& right){
    return Variable(!less(right).getBoolean());
}