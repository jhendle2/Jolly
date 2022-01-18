#include "primtypes.hpp"

enum PrimType keyword2PrimType(std::string keyword){
    if (keyword==KW_NOTHING) return Prim_Nothing;
    else if (keyword==KW_TYPE) return Prim_Type;
    else if (keyword==KW_BOOLEAN) return Prim_Boolean;
    else if (keyword==KW_STRING) return Prim_String;
    else if (keyword==KW_CHAR) return Prim_Char;
    else if (keyword==KW_NUMBER) return Prim_Number;
    else if (keyword==KW_LIST) return Prim_List;
    else if (keyword==KW_MAP) return Prim_Map;
    else return Prim_Invalid;
}

bool isPrimType(std::string keyword){
    return (keyword2PrimType(keyword)!=Prim_Invalid);
}

std::string primType2Keyword(enum PrimType type){
    switch(type){
        case Prim_Nothing: return KW_NOTHING;
        case Prim_Type: return KW_TYPE;
        case Prim_Boolean: return KW_BOOLEAN;
        case Prim_String: return KW_STRING;
        case Prim_Char: return KW_CHAR;
        case Prim_Number: return KW_NUMBER;
        case Prim_List: return KW_LIST;
        case Prim_Map: return KW_MAP;
        default: return "invalid";
    }
}