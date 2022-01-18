#pragma once

#include <iostream>

#include "color_text.hpp"

#define BaseError(COLOR_CODE, ERROR_TYPE, ERROR_NAME, DESC) "\n" COLOR_CODE "[" ERROR_TYPE " - " ERROR_NAME "] " _reset DESC ":\t"
#define BaseWarning(WARNING_NAME, DESC) BaseError(_fgBrightMagenta, "Warning", WARNING_NAME, DESC)
#define BaseNote(DESC) "\n" _fgBrightMagenta "[ SMILE-PARSER :> ] " _reset DESC

#define SyntaxError(ERROR_NAME, DESC)  BaseError(_fgBrightRed, "SyntaxError", ERROR_NAME, DESC)
#define ParseError(ERROR_NAME, DESC)  BaseError(_fgBrightGreen, "ParseError", ERROR_NAME, DESC)
#define ArithmeticError(ERROR_NAME, DESC)  BaseError(_fgBrightMagenta, "ArithmeticError", ERROR_NAME, DESC)


/* Syntax Errors */
#define SyntaxErrorBadOperator SyntaxError("Bad Operator", "Operator does not exist")
#define SyntaxErrorBadOperation SyntaxError("Bad Operation", "Cannot combine two elements")
#define SyntaxErrorIncompleteStatement SyntaxError("Incomplete Statement", "Statement is incomplete")
#define SyntaxErrorUnrecognizedType SyntaxError("Unrecognized Type", "Not a valid type")
#define SyntaxErrorUnrecognizedVariable SyntaxError("Unrecognized Variable", "Not a known variable. Did you initialize it?")
#define SyntaxErrorUnrecognizedFunction SyntaxError("Unrecognized Function", "Not a known function. Did you define it?")
#define SyntaxErrorUnrecognizedObject SyntaxError("Unrecognized Object", "Not a known object (function, variable). Did you define it?")
#define SyntaxErrorUnrecognizedKeyword SyntaxError("Unrecognized Keyword", "Not a recognized keyword")
#define SyntaxErrorReinitializedVariable SyntaxError("Reinitialized Variable", "Variable was reinitialized twice!")
#define SyntaxErrorConditionalScopeWithNoCondition SyntaxError("Conditional Scope Lacking Condition", "This conditional scope lacks any sort of boolean value")
#define SyntaxErrorElseWithoutIf SyntaxError("Else without If or Elsif", "This else lacks a friend :(")

/* Syntax Warnings */
#define SyntaxWarningUnknownVariable BaseWarning("Unknown Variable", "This variable is unknown and will be initialized to Nothing")

/* Arithmetic Errors */
#define ArithmeticErrorDivideByZero ArithmeticError("Divide By Zero", "Cannot divide by zero")
#define ArithmeticErrorIncompatibleTypes SyntaxError("Incompatible Types", "Cannot perform specified arithmetic operation between types")

/* Parse Errors */
#define ParseErrorUnrecognizedVariable ParseError("Unrecognized Variable", "Parser encountered an empty variable name")
#define ParseErrorUnmatchedEnd ParseError("Unmatched \"end\"", "\"end\" with no matching open keyword")
#define ParseErrorUnknownWithinScope ParseError("Unknown Within Scope", "The following is unknown within this scope")
#define ParseErrorUnexpectedToken ParseError("Unexpected Token", "The following is an unexpected token within this scope")
#define ParseErrorIncompleteFunctionHeader ParseError("Incomplete Function Header", "Function header is missing integral tokens")
#define ParseErrorOrphanYield ParseError("Orphan Yield", "This yield is an orphan and lacks a parent function")
#define ParseErrorOrphanConditionalScope ParseError("Orphan Conditional Scope", "This conditional scope lacks a parent to leave")
#define ParseErrorCriticalScopeError ParseError("Critical Scope Error", "This scope lacked a parent and urgently needed to exit")

#define RECURSIONDEPTHLIMIT 100
#define ParseErrorRecursionLimitReached ParseError("Recursion Limit Reached", "Recursion depth has reached its max of 100")

#define ParseDebugNoTokens "\n[Parse Debug - No Tokens]\t"
#define ParseDebugOneToken "\n[Parse Debug - One Token]\t"
#define ParseDebugTwoTokens "\n[Parse Debug - Two Tokens]\t"
#define ParseDebugSeveralTokens "\n[Parse Debug - Several Tokens]\t"
#define ParseDebugNoReturnVariableSet "\n[Parse Debug - No Variable Set]\t"

/* Parse Warnings (My fault usually) */
#define ParseWarningNestedFunctions BaseWarning("Nested Functions", "This feature is not supported yet")

#define WarningsEnabled true

#define ERROROUT(X,Y) {std::cout<<X<<Y<<"\n\n"; exit(EXIT_FAILURE);}

#define CLEANUPEVERYTHING(PARENT) cleanup_everything(PARENT)
#define SAFEERROROUT(PARENT,X,Y) {std::cout<<X<<Y<<"\n\n"; CLEANUPEVERYTHING(PARENT); exit(EXIT_FAILURE);} // Exits but also frees all remaining scopes, vars, etc.
#define WARNING(X,Y) {if(WarningsEnabled){std::cout<<X<<Y<<"\n\n";}} // Warning and doesn't cleanup or quit
#define NOTE(DESC) std::cout<<BaseNote(DESC)<<"\n";

#include "debug.hpp"
#define ERROR(X) {std::cout<<X<<lineToString(DEBUG_last_line)<<"\n\n"; exit(EXIT_FAILURE);}
// #include "scope.hpp"
// void cleanup_everything(Scope* scope);