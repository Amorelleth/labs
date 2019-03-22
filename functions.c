#include <stdlib.h>
#include <stdio.h>
#include "complex.h"
#include "matrix.h"

void* SumInts(const void* num1, const void* num2) {
    int* sum = (int*)malloc(sizeof(int));
    *sum = *((int*)num1) + *((int*)num2);

    return (void*)sum;
}

void* MulInts(const void* num1, const void* num2) {
    int* mul = (int*)malloc(sizeof(int));
    *mul = *((int*)num1) * *((int*)num2);

    return (void*)mul;
}

void* SumFloats(const void* num1, const void* num2) {
    float* sum = (float*)malloc(sizeof(float));
    *sum = *((float*)num1) + *((float*)num2);

    return (void*)sum;
}

void* MulFloats(const void* num1, const void* num2) {
    float* mul = (float*)malloc(sizeof(float));
    *mul = *((float*)num1) * *((float*)num2);

    return (void*)mul;
}

void* SumCmplx(const void* num1, const void* num2) {
    struct Complex* sum = (struct Complex*)malloc(sizeof(Complex));
    *sum = SumComplex(*((Complex*)num1), *((Complex*)num2));

    return (void*)sum;
}

void* MulCmplx(const void* num1, const void* num2) {
    struct Complex* mul = (struct Complex*)malloc(sizeof(struct Complex));
    *mul = MulComplex(*((struct Complex*)num1), *((struct Complex*)num2));

    return (void*)mul;
}

void PrintInts(const void* val) {
    printf("%d", *(int*)val);
}

void PrintFloats(const void* val) {
    printf("%.2f", *(float*)val);
}

void PrintComplex(const void* val) {
    struct Complex* cmplx = (struct Complex*)val;
    printf("%.2f%s%.2fi", cmplx->re, cmplx->im >= 0.0 ? "+" : "" , cmplx->im);
}
