#pragma once

#include <string>

class VarType{
protected:
    std::string name;
    std::string keyword;
public:
    VarType();
    VarType(std::string name, std::string keyword);

    std::string getName() const;
    std::string getKeyword() const;

    // VarType& operator=(const VarType& right);
    bool operator==(const std::string& keyword) const;
    bool operator!=(const std::string& keyword) const;
    bool operator==(VarType right) const;
    bool operator!=(VarType right) const;
};

bool isVarType(std::string key);
VarType getVarType(std::string key);
void addVarType(VarType type);