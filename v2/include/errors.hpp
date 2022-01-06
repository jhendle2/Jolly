#pragma once

#include <iostream>

/* Syntax Errors */
#define SyntaxErrorBadOperation "\n[SyntaxError - Bad Operation] Cannot combine two elements:\t"
#define SyntaxErrorBadOperator "\n[SyntaxError - Bad Operator] Operator does not exist:\t"
#define SyntaxErrorIncompleteStatement "\n[SyntaxError - Incomplete Statement] Statement is incomplete:\t"
#define SyntaxErrorUnrecognizedType "\n[SyntaxError - Unrecognized Type] Not a valid type:\t"
#define SyntaxErrorUnrecognizedVariable "\n[SyntaxError - Unrecognized Variable] Not a known variable. Did you initialize it?:\t"
#define SyntaxErrorUnrecognizedFunction "\n[SyntaxError - Unrecognized Function] Not a known function. Did you define it?:\t"
#define SyntaxErrorUnrecognizedObject "\n[SyntaxError - Unrecognized Object] Not a known object (function, variable). Did you define it?:\t"
#define SyntaxErrorReinitializedVariable "\n[SyntaxError - Reinitialized Variable] Variable was reinitialized twice!:\t"

/* Arithmetic Errors */
#define ArithmeticErrorDivideByZero "\n[Arithmetic Error - Divide By Zero] Cannot divide by zero:\t"

/* Parse Errors (My fault usually) */
#define ParseErrorUnrecognizedVariable "\n[Parse Error - Unrecognized Variable] Parser encountered an empty variable name:\t"

#define ParseDebugNoTokens "\n[Parse Debug - No Tokens]\t"
#define ParseDebugOneToken "\n[Parse Debug - One Token]\t"
#define ParseDebugTwoTokens "\n[Parse Debug - Two Tokens]\t"
#define ParseDebugSeveralTokens "\n[Parse Debug - Several Tokens]\t"

#define ERROROUT(X,Y) {std::cout<<X<<Y<<"\n";exit(EXIT_FAILURE);}