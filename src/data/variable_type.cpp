#include <iostream>
#include <unordered_map>

#include "keywords.hpp"
#include "variable_type.hpp"
#include "errors.hpp"

std::unordered_map<std::string, VarType> VarTypeTable = {
    {KW_CHARACTER, VarType(KW_CHARACTER, KW_CHARACTER)},
    {KW_STRING, VarType(KW_STRING, KW_STRING)},
    {KW_NUMBER, VarType(KW_NUMBER, KW_NUMBER)},
    {KW_TYPE, VarType(KW_TYPE, KW_TYPE)},
    {KW_BOOLEAN, VarType(KW_BOOLEAN, KW_BOOLEAN)},
    {KW_NOTHING, VarType(KW_NOTHING, KW_NOTHING)},
    {KW_VARIABLE, VarType(KW_VARIABLE, KW_VARIABLE)},
    {KW_OBJECT, VarType(KW_OBJECT, KW_OBJECT)},
    {KW_LIST, VarType(KW_LIST, KW_LIST)},
    {KW_MAP, VarType(KW_MAP, KW_MAP)},
    {KW_ENUM, VarType(KW_ENUM, KW_ENUM)}
};

VarType::VarType(){
    this->name = KW_NOTHING;
    this->keyword = KW_NOTHING;
}

VarType::VarType(std::string name, std::string keyword){
    this->name = name;
    this->keyword = keyword;
}

std::string VarType::getName() const{
    return name;
}
std::string VarType::getKeyword() const{
    return keyword;
}

// VarType& VarType::operator=(const VarType& right){
//     this->name = right.getName();
//     this->keyword = right.getKeyword();
//     return *this;
// }

bool VarType::operator==(const std::string& keyword) const{
    return this->keyword == keyword;
}
bool VarType::operator!=(const std::string& keyword) const{
    return !this->operator==(keyword);
}

bool VarType::operator==(VarType right) const{
    return this->keyword == right.getKeyword();
}
bool VarType::operator!=(VarType right) const{
    return !this->operator==(right);
}

bool isVarType(std::string key){
    return VarTypeTable.count(key) > 0;
}

VarType getVarType(std::string key){
    if(isVarType(key)){
        return VarTypeTable[key];
    }

    ERROR(SyntaxErrorUnrecognizedType);
    return VarTypeTable[KW_NOTHING];
}

void addVarType(VarType type){
    VarTypeTable[type.getName()] = type;
}
