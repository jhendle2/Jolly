#pragma once

#include <iostream>

/* Syntax Errors */
#define SyntaxErrorBadOperation "\n[SyntaxError - Bad Operation] Cannot combine two elements:\t"
#define SyntaxErrorBadOperator "\n[SyntaxError - Bad Operator] Operator does not exist:\t"
#define SyntaxErrorIncompleteStatement "\n[SyntaxError - Incomplete Statement] Statement is incomplete:\t"
#define SyntaxErrorUnrecognizedType "\n[SyntaxError - Unrecognized Type] Not a valid type:\t"
#define SyntaxErrorUnrecognizedVariable "\n[SyntaxError - Unrecognized Variable] Not a known variable. Did you initialize it?:\t"

/* Arithmetic Errors */
#define ArithmeticErrorDivideByZero "\n[Arithmetic Error - Divide By Zero] Cannot divide by zero:\t"

#define ERROROUT(X,Y) {std::cout<<X<<Y<<"\n";exit(EXIT_FAILURE);}