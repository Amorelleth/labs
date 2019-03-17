#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "functions.h"

#define COMPARE_FLOATS_PRECISION 0.01f

#ifndef TESTS
#define TESTS

Matrix* makeIntMatrixFromArray(int size, int* array) {
    int*** mx = (int***)malloc(size * sizeof(int**));
    for (int i = 0; i < size; i++) {
        mx[i] = (int**)malloc(size * sizeof(int*));
        for (int j = 0; j < size; j++) {
            mx[i][j] = (int*)&array[size*i + j];
        }
    }

    return NewMatrix(size, (void***)mx);
}

Matrix* makeFloatMatrixFromArray(int size, float* array) {
    float*** mx = (float***)malloc(size * sizeof(float**));
    for (int i = 0; i < size; i++) {
        mx[i] = (float**)malloc(size * sizeof(float*));
        for (int j = 0; j < size; j++) {
            mx[i][j] = (float*)&array[size*i + j];
        }
    }

    return NewMatrix(size, (void***)mx);
}

Matrix* makeComplexMatrixFromArray(int size, float* re, float* im) {
    Complex*** mx = (Complex***)malloc(size * sizeof(Complex**));
    for (int i = 0; i < size; i++) {
        mx[i] = (Complex**)malloc(size * sizeof(Complex*));
        for (int j = 0; j < size; j++) {
            mx[i][j] = NewComplex(re[size*i + j], im[size*i + j]);
        }
    }

    return NewMatrix(size, (void***)mx);
}

bool CompareFloats(float a, float b) {
  return fabs(a - b) < COMPARE_FLOATS_PRECISION;
}

void testIntsMatrix() {
    bool res = true;
    const int mSize = 3;
    int x1[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
    };
    int x2[9] = {
        1, 1, -1,
        -1, 1, 1,
        1, 1, -1,
    };
    int sum[9] = {
        2, 3, 2,
        3, 6, 7,
        8, 9, 8
    };
    int mul[9] = {
        2, 6, -2,
        5, 15, -5,
        8, 24, -8,
    };
    int mulByC[9] = {
        5, 10, 15,
        20, 25, 30,
        35, 40, 45,
    };
    int c = 5;

    Matrix* mx1 = makeIntMatrixFromArray(3, x1);
    Matrix* mx2 = makeIntMatrixFromArray(3, x2);
    Matrix* resSum = SumMatrix(mx1, mx2, &SumInts);
    Matrix* resMul = MulMatrix(mx1, mx2, &SumInts, &MulInts);
    Matrix* resMulByC = MulByConst(mx1, &c, &MulInts);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int idx = mSize * i + j;
            if (*(int*)resSum->elems[i][j] != sum[idx]) {
                printf("test sum ints failed, elem[%d][%d]: EXPECTED %d, GOT %d\n", i, j, sum[idx], *(int*)resSum->elems[i][j]);
                res = false;
            }
            if (*(int*)resMul->elems[i][j] != mul[idx]) {
                printf("test mul ints failed, elem[%d][%d]: EXPECTED %d, GOT %d\n", i, j, mul[idx], *(int*)resMul->elems[i][j]);
                res = false;
            }
            if (*(int*)resMulByC->elems[i][j] != mulByC[idx]) {
                printf("test mul ints by const failed, elem[%d][%d]: EXPECTED %d, GOT %d\n", i, j, mulByC[idx], *(int*)resMulByC->elems[i][j]);
                res = false;
            }
        }
    }
    if (res) {
        printf("int tests passed OK\n");
    }

    FreeMatrix(resSum);
    FreeMatrix(resMul);
    FreeMatrix(resMulByC);
    free(mx1->elems);
    free(mx2->elems);
    free(mx1);
    free(mx2);
    free(resSum); 
    free(resMul);
    free(resMulByC);
}

void testComplexMatrix() {
    bool sumPassed = true;
    bool mulPassed = true;
    bool mulByCPassed = true;
    const int mSize = 2;
    float re1[4] = {
        1, 2,
        4, 5,
    };
    float re2[4] = {
        1, 1,
        -1, 1,
    };
    float im1[4] = {
        4, 5,
        7, 8,
    };
    float im2[4] = {
        -1, 1,
        1, 1,
    };
    float sumRe[4] = {
        2, 3,
        3, 6,
    };
    float sumIm[4] = {
        3, 6,
        8, 9,
    };
    float mulRe[4] = {
        -2, -6,
        -2, -6,
    };
    float mulIm[4] = {
        0, 12,
        0, 24,
    };
    float mulByCRe[4] = {
        -7, -8,
        -10, -11,
    };
    float mulByCIm[4] = {
        6, 9,
        15, 18,
    };

    Complex* c = NewComplex(1, 2);

    Matrix* mx1 = makeComplexMatrixFromArray(mSize, re1, im1);
    Matrix* mx2 = makeComplexMatrixFromArray(mSize, re2, im2);
    Matrix* resSum = SumMatrix(mx1, mx2, &SumCmplx);
    Matrix* resMul = MulMatrix(mx1, mx2, &SumCmplx, &MulCmplx);
    Matrix* resMulByC = MulByConst(mx1, c, &MulCmplx);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize*i + j;
            Complex* sum = (Complex*)resSum->elems[i][j];
            Complex* mul = (Complex*)resMul->elems[i][j];
            Complex* mulByC = (Complex*)resMulByC->elems[i][j];
            if (sumPassed && !(CompareFloats(sum->re, sumRe[idx]) && CompareFloats(sum->im, sumIm[idx]))) {
                sumPassed = false;
            }
            if (mulPassed && !(CompareFloats(mul->re, mulRe[idx]) && CompareFloats(mul->im, mulIm[idx]))) {
                mulPassed = false;
            }
            if (mulByCPassed && !(CompareFloats(mulByC->re, mulByCRe[idx]) && CompareFloats(mulByC->im, mulByCIm[idx]))) {
                mulByCPassed = false;
            }
        }
    }
    if (sumPassed && mulPassed && mulByCPassed) {
        printf("complex tests passed OK\n");
    } else {
        if (!sumPassed) {    
            printf("\ntest sum complex failed:\nEXPECTED:\n");
            PrintMatrix(makeComplexMatrixFromArray(mSize, sumRe, sumIm), PrintComplex);
            printf("GOT:\n");
            PrintMatrix(resSum, PrintComplex);
        }
        if (!mulPassed) {
            printf("\ntest mul complex failed:\nEXPECTED:\n");
            PrintMatrix(makeComplexMatrixFromArray(mSize, mulRe, mulIm), PrintComplex);
            printf("GOT:\n");
            PrintMatrix(resMul, PrintComplex);
        }
        if (!mulByCPassed) {
            printf("\ntest mul complex by const failed:\nEXPECTED:\n");
            PrintMatrix(makeComplexMatrixFromArray(mSize, mulByCRe, mulByCIm), PrintComplex);
            printf("GOT:\n");
            PrintMatrix(resMulByC, PrintComplex);
        }
    }

    FreeMatrix(resSum);
    FreeMatrix(resMul);
    FreeMatrix(resMulByC);
    free(mx1->elems);
    free(mx2->elems);
    free(mx1);
    free(mx2);
    free(resSum); 
    free(resMul);
    free(resMulByC);
}

void testFloatsMatrix() {
    bool res = true;
    const int mSize = 3;
    float x1[9] = {
        1.1, 2.2, 3.3,
        4.4, 5.5, 6.6,
        7.7, 8.8, 9.9,
    };
    float x2[9] = {
        1, 1, -1.5,
        -1.5, 1, 1,
        1, 1, -1.5,
    };
    float sum[9] = {
        2.1, 3.2, 1.8,
        2.9, 6.5, 7.6,
        8.7, 9.8, 8.4
    };
    float mul[9] = {
        1.1, 6.6, -4.4,
        2.75, 16.5, -11,
        4.4, 26.4, -17.6,
    };
    float mulByC[9] = {
        5.72, 11.44, 17.16,
        22.88, 28.6, 34.32,
        40.04, 45.76, 51.48,
    };
    float c = 5.2;

    Matrix* mx1 = makeFloatMatrixFromArray(3, x1);
    Matrix* mx2 = makeFloatMatrixFromArray(3, x2);
    Matrix* resSum = SumMatrix(mx1, mx2, &SumFloats);
    Matrix* resMul = MulMatrix(mx1, mx2, &SumFloats, &MulFloats);
    Matrix* resMulByC = MulByConst(mx1, &c, &MulFloats);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize * i + j;
            if (!CompareFloats(*(float*)resSum->elems[i][j], sum[idx])) {
                printf("test sum floats failed, elem[%d][%d]: EXPECTED %.2f, GOT %.2f\n", i, j, sum[idx], *(float*)resSum->elems[i][j]);
                res = false;
                break;
            }
            if (!CompareFloats(*(float*)resMul->elems[i][j], mul[idx])) {
                printf("test mul floats failed, elem[%d][%d]: EXPECTED %.2f, GOT %.2f\n", i, j, mul[idx], *(float*)resMul->elems[i][j]);
                res = false;
                break;
            }
            if (!CompareFloats(*(float*)resMulByC->elems[i][j], (mulByC[idx]))) {
                printf("test mul floats by const failed, elem[%d][%d]: EXPECTED %.2f, GOT %.2f\n", i, j, mulByC[idx], *(float*)resMulByC->elems[i][j]);
                res = false;
                break;
            }
        }
    }
    if (res) {
        printf("float tests passed OK\n");
    }

    FreeMatrix(resSum);
    FreeMatrix(resMul);
    FreeMatrix(resMulByC);
    free(mx1->elems);
    free(mx2->elems);
    free(mx1);
    free(mx2);
    free(resSum); 
    free(resMul);
    free(resMulByC);
}

#endif