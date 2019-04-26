#include "matrix.h"

#ifndef MATH_FUNCTIONS
#define MATH_FUNCTIONS 

void FreeMatrix(Matrix* m);
void* SumInts(const void* num1, const void* num2);
void* MulInts(const void* num1, const void* num2);
void* SumFloats(const void* num1, const void* num2);
void* MulFloats(const void* num1, const void* num2);
void* SumCmplx(const void* num1, const void* num2);
void* MulCmplx(const void* num1, const void* num2);
void PrintInts(const void* val);
void PrintFloats(const void* val);
void PrintComplex(const void* val);

#endif