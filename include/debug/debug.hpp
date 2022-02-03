#pragma once

#include "file_reader.hpp"
#include "scope.hpp"

typedef bool Flag; // for convenience

extern Line DEBUG_last_line; // so we can keep track of lines & their numbers
extern ScopePtr DEBUG_last_scope; // so we can clean up all dangling scopes

extern Flag DEBUG_show_tokens; // show tokens when we interpret them
extern Flag DEBUG_show_lines; // show lines when we interpret them
extern Flag DEBUG_dump_scopes; // dump scopes when we modify them
extern Flag DEBUG_dump_scopes_recursively; // dump scopes recursively when we modify them