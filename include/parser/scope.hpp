#pragma once

#include <string>
#include <vector>
#include <memory>

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

/********************************/

class Scope : public std::enable_shared_from_this<Scope>{

protected:
    std::string name;
    enum ScopeType type;
    std::vector<Line> lines;

    std::shared_ptr<Scope> parent;
    std::vector<std::shared_ptr<Scope>> children;

public:

    Scope();
    Scope(std::string name, enum ScopeType type);

    std::shared_ptr<Scope> getptr();
    [[nodiscard]] static std::shared_ptr<Scope> create();
    [[nodiscard]] static std::shared_ptr<Scope> create(std::string name, enum ScopeType type);

    std::string getName() const;
    enum ScopeType getScopeType() const;

    void addLine(Line line);
    std::vector<Line> getLines() const;

    void dump() const;
    void dumpRecursive() const;
    void tree();
    void tree(int level);

    void setParent(std::shared_ptr<Scope> parent);
    std::shared_ptr<Scope> getParent() const;

    void addChild(std::shared_ptr<Scope> child);
};

typedef std::shared_ptr<Scope> ScopePtr;