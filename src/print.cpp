#include <iostream>

#include "general_utils.hpp"
#include "print.hpp"

void Print(Variable var){
    std::cout << var.toString();
}
void Print(std::string string){
    if(string.at(0)=='\"')
        string = stripQuotes(string);
    std::cout << string;
}

void Println(Variable var){
    std::cout << var.toString() << "\n";
}

void Println(std::string string){
    if(string.at(0)=='\"')
        string = stripQuotes(string);
    std::cout << string << "\n";
}