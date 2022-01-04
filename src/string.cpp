#include "string.hpp"

String::String() : Variable(""){

}
String::String(std::string str) : Variable(""){
    string = str;
}
String::String(const Variable& var){
    Variable v = var;
    string = v.getString();
}

String String::eq(const String& right){
    string=right.string;
    return right;
}

String String::equality(const String& right){
    return Variable(string==right.string);
}
String String::inequality(const String& right){
    return Variable(string!=right.string);
}

String String::add(const String& b){
    string+=b.string;
    return string;
}

void String::addEq(const String& b){
    string+=b.string;
}