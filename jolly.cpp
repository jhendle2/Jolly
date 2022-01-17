#include <iostream>
#include <string>
#include <vector>

#include "errors.hpp"

#include "types.hpp"

void Interpret(std::string filename){

}

int main(int argc, char** argv){
    NOTE("Starting Smile-Parser");

    // std::string filename = std::string(argv[1]);
    // Interpret(filename);

    Number n = Number("n", 6);
    Number m = Number("m", 5);
    n.dumpString();
    m.dumpString();
    bool n_less_m = n.less(m);
    std::cout<<"n+m="<<(n.add(m).stringValue())<<"\n";
    std::cout<<"n-m="<<(n.sub(m).stringValue())<<"\n";
    std::cout<<"n*m="<<(n.mul(m).stringValue())<<"\n";
    std::cout<<"n/m="<<(n.div(m).stringValue())<<"\n";
    std::cout<<"n%m="<<(n.mod(m).stringValue())<<"\n";
    std::cout<<"n^m="<<(n.exp(m).stringValue())<<"\n";

    std::cout<<"\n";
    return 0;
}