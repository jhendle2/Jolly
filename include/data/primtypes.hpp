#pragma once

#ifndef PRIMTYPES

    #define KW_NOTHING  "Nothing"   // Nothing m
    #define KW_TYPE     "Type"      // Type t = Bool
    #define KW_BOOLEAN  "Bool"      // Bool b = True
    #define KW_STRING   "String"    // String s = "Hello"
    #define KW_CHAR     "Char"      // Char c = 'x'
    #define KW_NUMBER   "Number"    // Number n = 10

    #define KW_LIST     "List"      // List(String) ls = ["Hello", "Goodbye"]
    #define KW_MAP      "Map"       // Map(String, Number) msn = {"First":1, "Second":2, "Third":3}

#endif /* PRIMTYPES */


#ifndef RESERVEDVALS

    #define KW_TRUE     "True"
    #define KW_FALSE    "False"

#endif /* RESERVEDVALS */

enum PrimType{
    Prim_Invalid,
    Prim_Nothing,
    Prim_Type,
    Prim_Boolean,
    Prim_String,
    Prim_Char,
    Prim_Number,
    Prim_List,
    Prim_Map,
};

#include <string>
bool isPrimType(std::string keyword);
enum PrimType keyword2PrimType(std::string keyword);
std::string primType2Keyword(enum PrimType type);