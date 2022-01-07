#pragma once

#include <iostream>

#include "color_text.hpp"

#define BaseError(COLOR_CODE, ERROR_TYPE, ERROR_NAME, DESC) "\n" COLOR_CODE "[" ERROR_TYPE " - " ERROR_NAME "] " _reset DESC ":\t"

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

/* Arithmetic Errors */
#define ArithmeticErrorDivideByZero ArithmeticError("Divide By Zero", "Cannot divide by zero")

/* Parse Errors (My fault usually) */
#define ParseErrorUnrecognizedVariable ParseError("Unrecognized Variable", "Parser encountered an empty variable name")
#define ParseErrorUnmatchedEnd ParseError("Unmatched \"end\"", "\"end\" with no matching open keyword")

#define ParseDebugNoTokens "\n[Parse Debug - No Tokens]\t"
#define ParseDebugOneToken "\n[Parse Debug - One Token]\t"
#define ParseDebugTwoTokens "\n[Parse Debug - Two Tokens]\t"
#define ParseDebugSeveralTokens "\n[Parse Debug - Several Tokens]\t"

#define ERROROUT(X,Y) {std::cout<<X<<Y<<"\n\n";exit(EXIT_FAILURE);}