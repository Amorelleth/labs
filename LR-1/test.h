#include <stdbool.h>
#include "matrix.h"

#ifndef TEST
#define TEST

Matrix* makeIntMatrixFromArray(int size, int* array);
Matrix* makeFloatMatrixFromArray(int size, float* array);
Matrix* makeComplexMatrixFromArray(int size, float* re, float* im);
bool CompareFloats(float a, float b);
int testIntsSumMatrix();
int testIntsMulMatrix();
int testIntsMulByCMatrix();
int testIntsMulByZMatrix();
int testIntsMulByEMatrix();
int testComplexSumMatrix();
int testComplexMulMatrix();
int testComplexMulByCMatrix();
int testComplexMulByZMatrix();
int testFloatsSumMatrix();
int testFloatsMulMatrix();
int testFloatsMulByCMatrix();
int testFloatsMulByZMatrix();
int testFloatsMulByEMatrix();
void runTests();

#endif