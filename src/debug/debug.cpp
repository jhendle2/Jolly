#include "debug.hpp"

struct Line DEBUG_last_line;
Scope* DEBUG_last_scope = nullptr;

Flag DEBUG_show_tokens = false;
Flag DEBUG_show_lines = true;
Flag DEBUG_dump_scopes = true;
Flag DEBUG_dump_scopes_recursively = false;