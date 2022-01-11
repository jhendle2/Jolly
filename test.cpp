#include <iostream>
#include <set>

int main () {
    std::set<std::string> set_test;
    set_test.insert("hello");
    set_test.insert("goodbye");
    set_test.insert("peace");
    set_test.insert("shalom");
    set_test.insert("sionara");

    for(std::string s : set_test){
        std::cout<<s<<"\n";
    }

    return 0;
}