#pragma once

#include <string>

#define KW_CLASS "class"
#define KW_FUNCTION "function"
#define KW_TAKES "takes"
#define KW_YIELD "yield"
    #define KW_YIELD_ALT "return"
#define KW_YIELDS "yields"
    #define KW_YIELDS_ALT "returns"
#define KW_ENTRYPOINT "entrypoint"

#define KW_WHILE "while"
#define KW_DOWHILE "dowhile"
#define KW_FOR "for"
#define KW_FOREACH "foreach"
#define KW_COUNT "count"

#define KW_CONTINUE "continue"
#define KW_BREAK "break"

#define KW_IF "if"
#define KW_ELSIF "elsif"
#define KW_ELSE "else"

#define KW_WITH "with"
#define KW_AS "as"
#define KW_FROM "from"

#define KW_MY "my"
#define KW_PUBLIC "public"
#define KW_PRIVATE "private"
#define KW_STATIC "static"
#define KW_CONST "const"

#define KW_DEFINE "define"
#define KW_ALIAS "alias"

#define KW_END "end"
#define KW_EXIT "exit"
#define KW_PASS "pass"

/********************************/

#define KW_NOTHING "Nothing"
    #define KW_NOTHING_ALT "Void"
#define KW_VARIABLE "Auto"
    #define KW_VARIABLE_ALT "Variable"
#define KW_STRING "String"
    #define KW_STRING_ALT "Str"
#define KW_NUMBER "Number"
    #define KW_NUMBER_ALT "Num"
#define KW_BOOLEAN "Boolean"
    #define KW_BOOLEAN_ALT "Bool"
#define KW_CHARACTER "Character"
    #define KW_CHARACTER_ALT "Char"
#define KW_TYPE "Type"
    #define KW_TYPE_ALT "Type"
#define KW_OBJECT "Object"
    #define KW_OBJECT_ALT "Obj"
#define KW_LIST "List"
    #define KW_LIST_ALT "List"
#define KW_MAP "Map"
    #define KW_MAP_ALT "Dict"
#define KW_ENUM "Enum"
    #define KW_ENUM_ALT "Enumeration"

#define KW_TRUE "True"
    #define KW_TRUE_ALT "true"
#define KW_FALSE "False"
    #define KW_FALSE_ALT "false"

/********************************/

#define KW_PRINT "Print"
#define KW_PRINTLN "Println"
#define KW_TYPEOF "Typeof"

bool isKeyword(const std::string& keyword);