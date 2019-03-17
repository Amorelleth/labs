#include <stdlib.h>
#include <stdio.h>
#include "complex.h"

#ifndef MATH_FUNCTIONS
#define MATH_FUNCTIONS 

void* SumInts(const void* num1, const void* num2) {
    int int1 = *((int*)num1);
    int int2 = *((int*)num2);
    int* sum = (int*)malloc(sizeof(int));
    *sum = int1 + int2;

    return (void*)sum;
}

void* MulInts(const void* num1, const void* num2) {
    int int1 = *((int*)num1);
    int int2 = *((int*)num2);
    int* mul = (int*)malloc(sizeof(int));
    *mul = int1 * int2;

    return (void*)mul;
}

void* SumFloats(const void* num1, const void* num2) {
    float float1 = *((float*)num1);
    float float2 = *((float*)num2);
    float* sum = (float*)malloc(sizeof(float));
    *sum = float1 + float2;

    return (void*)sum;
}

void* MulFloats(const void* num1, const void* num2) {
    float float1 = *((float*)num1);
    float float2 = *((float*)num2);
    float* mul = (float*)malloc(sizeof(float));
    *mul = float1 * float2;

    return (void*)mul;
}

void* SumCmplx(const void* num1, const void* num2) {
    Complex cmplx1 = *((Complex*)num1);
    Complex cmplx2 = *((Complex*)num2);
    Complex* sum = (Complex*)malloc(sizeof(Complex));
    *sum = SumComplex(cmplx1, cmplx2);

    return (void*)sum;
}

void* MulCmplx(const void* num1, const void* num2) {
    Complex cx1 = *((Complex*)num1);
    Complex cx2 = *((Complex*)num2);
    Complex* mul = (Complex*)malloc(sizeof(Complex));
    *mul = MulComplex(cx1, cx2);

    return (void*)mul;
}

void PrintInts(const void* val) {
    printf("%d", *(int*)val);
}

void PrintFloats(const void* val) {
    printf("%.2f", *(float*)val);
}

void PrintComplex(const void* val) {
    Complex* cmplx = (Complex*)val;
    printf("%.2f%s%.2fi", cmplx->re, cmplx->im >= 0.0 ? "+" : "" , cmplx->im);
}

#endif