#include "type_handler.hpp"

bool compatibleTypes(enum PrimType in, enum PrimType out){
    if(in == out) return true;
    if(in == Prim_Nothing || out == Prim_Nothing) return false;

    switch(in){
        default:
        case Prim_Nothing: break;

        case Prim_Boolean:
            if(out == Prim_Number) return true;
            if(out == Prim_Char) return true;
            if(out == Prim_String) return true;
            if(out == Prim_Type) return false;
        
        case Prim_Number:
            if(out == Prim_Boolean) return true;
            if(out == Prim_Char) return true;
            if(out == Prim_String) return true;
            if(out == Prim_Type) return true;
        
        case Prim_Type:
            if(out == Prim_Boolean) return false;
            if(out == Prim_Char) return false;
            if(out == Prim_String) return false;
            if(out == Prim_Number) return false;
        
        case Prim_Char:
            if(out == Prim_Boolean) return true;
            if(out == Prim_Type) return false;
            if(out == Prim_String) return true;
            if(out == Prim_Number) return true;
        
        case Prim_String:
            if(out == Prim_Boolean) return true;
            if(out == Prim_Type) return true;
            if(out == Prim_Number) return true;
            if(out == Prim_Char) return true;
    }
    return false;
}
bool compatibleTypes(Variable in, enum PrimType out){
    return compatibleTypes(in.getPrimType(), out);
}
bool compatibleTypes(Variable in, Variable out){
    return compatibleTypes(in.getPrimType(), out.getPrimType());
}

