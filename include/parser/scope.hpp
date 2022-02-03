#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "variable.hpp"
#include "tokens_lines.hpp"

enum ScopeType{
    ScopeInvalid,

    ScopeConstant,
    ScopeClass,
    ScopeFunction,

    ScopeWhile,
    ScopeDowhile,
    ScopeFor,
    ScopeForeach,
    ScopeCount,

    ScopeIf,
    ScopeElsif,
    ScopeElse,
};

bool isScopeType(const std::string& s);
enum ScopeType stringToScopeType(const std::string& s);
std::string scopeTypeToString(const enum ScopeType& type);

bool isScopeHeader(const std::string& s);
bool tokensAreValidFunctionCall(const Tokens& tokens);
#define VerifyTokensForFunctionCall(X) {if(!tokensAreValidFunctionCall(X)){ERROR(SyntaxErrorIncompleteStatement);}}

/********************************/

class Scope : public std::enable_shared_from_this<Scope>{

protected:
    bool truthiness;
    std::string name;
    enum ScopeType type;
    std::vector<Line> lines;

    std::shared_ptr<Scope> parent;
    std::unordered_map<std::string, std::shared_ptr<Scope>> children;
    std::unordered_map<std::string, Variable> variables;

public:

    Scope();
    Scope(std::string name, enum ScopeType type);

    std::shared_ptr<Scope> getptr();
    [[nodiscard]] static std::shared_ptr<Scope> create();
    [[nodiscard]] static std::shared_ptr<Scope> create(std::string name, enum ScopeType type);

    std::string getName() const;
    enum ScopeType getScopeType() const;

    bool getTruthiness() const;
    void setTruthiness(bool truthiness);

    void addLine(Line line);
    std::vector<Line> getLines() const;

    void dump() const;
    void dumpRecursive() const;
    void tree();
    void tree(int level);
    void treeLines();
    void treeLines(int level);

    void setParent(std::shared_ptr<Scope> parent);
    std::shared_ptr<Scope> getParent() const;

    void addChild(std::shared_ptr<Scope> child);
    bool hasChild(std::string name);
    std::shared_ptr<Scope> getChild(std::string name);

    bool hasVariable(std::string name) const;
    void addVariable(std::string name, Variable var);
    void addVariable(Variable var);
    void updateVariable(std::string name, const Variable& right);
    void updateVariableRecursive(const Variable& right);
    Variable getVariable(const std::string name);

    bool hasVariableRecursive(std::string name) const;
    void updateVariableRecursive(std::string name, const Variable& right);
    Variable getVariableRecursive(const std::string name);
};

typedef std::shared_ptr<Scope> ScopePtr;