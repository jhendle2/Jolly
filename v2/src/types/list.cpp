#include <iostream>

#include "list.hpp"

List::List() : Variable(TYPE_LIST){

}

// List::List(const Variable& var) : Variable(TYPE_LIST){
//     Variable temp = var;
//     boolean = temp.getBoolean();
// }

void List::push_back(Variable var){
    list.push_back(var);
}

Variable List::add(const Variable& var){
    List new_list = List();
    new_list.list = list;
    new_list.push_back(var);
    return new_list;
}
Variable List::addEq(const Variable& var){
    List new_list = List();
    push_back(var);
    new_list.list = list;
    return new_list;
}

int List::length(){
    return (int)list.size();
}

std::string List::toStringValue(){
    std::string out = "";
    out += " [";
    for(Variable v : list){
        out += v.toString() + ",\n";
    }
    return out;
}

void List::dump(){
    std::cout<<toString()<<"\n";
    std::cout<<" [";
    for(Variable v : list){
        std::cout<<v.toString()<<",\n";
    }
    std::cout<<"]\n";
}