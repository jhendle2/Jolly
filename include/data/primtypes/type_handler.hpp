#pragma once

#include "types.hpp"

bool compatibleTypes(enum PrimType in, enum PrimType out);
bool compatibleTypes(Variable in, enum PrimType out);
bool compatibleTypes(Variable in, Variable out);


template <typename T>
bool changeType(Variable in, T& out){
    bool can_change_type = compatibleTypes(in, out.getPrimType());
    if(!can_change_type) return false;
    out = T(in);
    return true;
}