#include <iostream>
#include <vector>

bool isDigit(char& c){
    return (c >= '0' && c <= '9');
}

bool isNumber(std::string s){
    for(char& c : s){
        if(!isDigit(c)) return false;
    }
    return true;
}
bool isDecimal(std::string s){
    int dot_count = 0;
    for(char& c : s){
        if(c == '.') dot_count++;
        else if(!isDigit(c)) return false;
    }
    return (dot_count <= 1);
}

int main () {
    
    std::string s1 = "1.00";
    std::string s2 = "4.0.2";
    std::string s3 = "12";
    std::cout<<isDecimal(s1)<<"\n";
    std::cout<<isNumber(s1)<<"\n";
    std::cout<<isDecimal(s2)<<"\n";
    std::cout<<isNumber(s2)<<"\n";
    std::cout<<isDecimal(s3)<<"\n";
    std::cout<<isNumber(s3)<<"\n";

    return 0;
}