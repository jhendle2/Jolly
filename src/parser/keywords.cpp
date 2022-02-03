#include "keywords.hpp"

bool isKeyword(const std::string& keyword){
    return (
        // keyword == KW_CLASS || // these might have to come back
        // keyword == KW_FUNCTION ||

        // keyword == KW_WHILE || // concerned this might cause a lot of harm
        // keyword == KW_DOWHILE ||
        // keyword == KW_FOR ||
        // keyword == KW_FOREACH ||
        // keyword == KW_COUNT ||

        keyword == KW_CONTINUE ||
        keyword == KW_BREAK ||

        // keyword == KW_IF || // concerned this might cause a lot of harm
        // keyword == KW_ELSIF ||
        // keyword == KW_ELSE ||

        keyword == KW_WITH ||
        keyword == KW_AS ||
        keyword == KW_FROM ||

        keyword == KW_MY ||
        keyword == KW_PUBLIC ||
        keyword == KW_PRIVATE ||
        keyword == KW_STATIC ||
        keyword == KW_CONST ||

        keyword == KW_DEFINE ||
        keyword == KW_ALIAS ||

        // keyword == KW_END || // concerned this might cause a lot of harm
        keyword == KW_EXIT ||
        keyword == KW_PASS ||
        keyword == KW_ENTRYPOINT
    );
}