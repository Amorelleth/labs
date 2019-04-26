#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "functions.h"
#include "matrix.h"
#include "complex.h"

#define COMPARE_FLOATS_PRECISION 0.01f
#define NUMBER_OF_TESTS 14

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

int testIntsSumMatrix() {
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

    Matrix* mx1 = makeIntMatrixFromArray(mSize, x1);
    Matrix* mx2 = makeIntMatrixFromArray(mSize, x2);
    Matrix* resSum = SumMatrix(mx1, mx2, &SumInts);

    printf("START int sum test\n----------\n");
    printf("FIRST matrix:\n");
    PrintMatrix(mx1, &PrintInts);
    printf("\nSECOND matrix:\n");
    PrintMatrix(mx2, &PrintInts);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(makeIntMatrixFromArray(mSize, sum), &PrintInts);
    printf("\nGOT matrix:\n");
    PrintMatrix(resSum, &PrintInts);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize * i + j;
            if (*(int*)resSum->elems[i][j] != sum[idx]) {
                printf("----- elem[%d][%d]: EXPECTED %d, GOT %d\n", i, j, sum[idx], *(int*)resSum->elems[i][j]);
                res = false;
            }
        }
    }
    if (res) {
        printf("\nPASSED int sum test\n----------\n");
    } else {
        printf("\nFAILED int sum test\n----------\n");
    }

    FreeMatrix(resSum);
    free(mx1->elems);
    free(mx2->elems);
    free(mx1);
    free(mx2);
    free(resSum);

    return res ? 1 : 0;
}

int testIntsMulMatrix() {
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
    int mul[9] = {
        2, 6, -2,
        5, 15, -5,
        8, 24, -8,
    };

    Matrix* mx1 = makeIntMatrixFromArray(3, x1);
    Matrix* mx2 = makeIntMatrixFromArray(3, x2);
    Matrix* resMul = MulMatrix(mx1, mx2, &SumInts, &MulInts);

    printf("START int multiplication test\n----------\n");
    printf("FIRST matrix:\n");
    PrintMatrix(mx1, &PrintInts);
    printf("\nSECOND matrix:\n");
    PrintMatrix(mx2, &PrintInts);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(makeIntMatrixFromArray(mSize, mul), &PrintInts);
    printf("\nGOT matrix:\n");
    PrintMatrix(resMul, &PrintInts);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize * i + j;
            if (*(int*)resMul->elems[i][j] != mul[idx]) {
                printf("----- elem[%d][%d]: EXPECTED %d, GOT %d\n", i, j, mul[idx], *(int*)resMul->elems[i][j]);
                res = false;
            }
        }
    }
    if (res) {
        printf("\nPASSED int multiplication test\n----------\n");
    } else {
        printf("\nFAILED int multiplication test\n----------\n");
    }

    FreeMatrix(resMul);
    free(mx1->elems);
    free(mx2->elems);
    free(mx1);
    free(mx2);
    free(resMul);

    return res ? 1 : 0;
}

int testIntsMulByCMatrix() {
    bool res = true;
    const int mSize = 3;
    int x1[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
    };
    int mulByC[9] = {
        5, 10, 15,
        20, 25, 30,
        35, 40, 45,
    };
    int c = 5;

    Matrix* mx1 = makeIntMatrixFromArray(mSize, x1);
    Matrix* resMulByC = MulByConst(mx1, &c, &MulInts);

    printf("START int multiplication by const test\n----------\n");
    printf("MATRIX:\n");
    PrintMatrix(mx1, &PrintInts);
    printf("\nCONST: %d\n", c);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(makeIntMatrixFromArray(mSize, mulByC), &PrintInts);
    printf("\nGOT matrix:\n");
    PrintMatrix(resMulByC, &PrintInts);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize * i + j;
            if (*(int*)resMulByC->elems[i][j] != mulByC[idx]) {
                printf("----- elem[%d][%d]: EXPECTED %d, GOT %d\n", i, j, mulByC[idx], *(int*)resMulByC->elems[i][j]);
                res = false;
            }
        }
    }
    if (res) {
        printf("\nPASSED int multiplication by const test\n----------\n");
    } else {
        printf("\nFAILED int multiplication by const test\n----------\n");
    }

    FreeMatrix(resMulByC);
    free(mx1->elems);
    free(mx1);
    free(resMulByC);

    return res ? 1 : 0;
}

int testIntsMulByEMatrix() {
    bool res = true;
    const int mSize = 3;
    int x1[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
    };
    int x2[9] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    };

    Matrix* mx1 = makeIntMatrixFromArray(mSize, x1);
    Matrix* mx2 = makeIntMatrixFromArray(mSize, x2);
    Matrix* resMul = MulMatrix(mx1, mx2, &SumInts, &MulInts);

    printf("START int multiplication by E-matrix test\n----------\n");
    printf("FIRST matrix:\n");
    PrintMatrix(mx1, &PrintInts);
    printf("\nSECOND matrix:\n");
    PrintMatrix(mx2, &PrintInts);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(makeIntMatrixFromArray(mSize, x1), &PrintInts);
    printf("\nGOT matrix:\n");
    PrintMatrix(resMul, &PrintInts);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize * i + j;
            if (*(int*)resMul->elems[i][j] != x1[idx]) {
                printf("----- elem[%d][%d]: EXPECTED %d, GOT %d\n", i, j, x1[idx], *(int*)resMul->elems[i][j]);
                res = false;
            }
        }
    }
    if (res) {
        printf("\nPASSED int multiplication by E-matrix test\n----------\n");
    } else {
        printf("\nFAILED int multiplication by E-matrix test\n----------\n");
    }

    FreeMatrix(resMul);
    free(mx1->elems);
    free(mx2->elems);
    free(mx1);
    free(mx2);
    free(resMul);

    return res ? 1 : 0;
}

int testIntsMulByZMatrix() {
    bool res = true;
    const int mSize = 3;
    int x1[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
    };
    int mulByZ[9] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
    };
    int c = 0;

    Matrix* mx1 = makeIntMatrixFromArray(mSize, x1);
    Matrix* resMulByC = MulByConst(mx1, &c, &MulInts);

    printf("START int multiplication by zero test\n----------\n");
    printf("MATRIX:\n");
    PrintMatrix(mx1, &PrintInts);
    printf("\nCONST: %d\n", c);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(makeIntMatrixFromArray(mSize, mulByZ), &PrintInts);
    printf("\nGOT matrix:\n");
    PrintMatrix(resMulByC, &PrintInts);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize * i + j;
            if (*(int*)resMulByC->elems[i][j] != mulByZ[idx]) {
                printf("----- elem[%d][%d]: EXPECTED %d, GOT %d\n", i, j, mulByZ[idx], *(int*)resMulByC->elems[i][j]);
                res = false;
            }
        }
    }
    if (res) {
        printf("\nPASSED int multiplication by zero test\n----------\n");
    } else {
        printf("\nFAILED int multiplication by zero test\n----------\n");
    }

    FreeMatrix(resMulByC);
    free(mx1->elems);
    free(mx1);
    free(resMulByC);

    return res ? 1 : 0;
}

int testComplexSumMatrix() {
    bool res = true;
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

    Matrix* mx1 = makeComplexMatrixFromArray(mSize, re1, im1);
    Matrix* mx2 = makeComplexMatrixFromArray(mSize, re2, im2);
    Matrix* resSum = SumMatrix(mx1, mx2, &SumCmplx);

    printf("START complex sum test\n----------\n");
    printf("FIRST matrix:\n");
    PrintMatrix(mx1, &PrintComplex);
    printf("\nSECOND matrix:\n");
    PrintMatrix(mx2, &PrintComplex);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(makeComplexMatrixFromArray(mSize, sumRe, sumIm), &PrintComplex);
    printf("\nGOT matrix:\n");
    PrintMatrix(resSum, &PrintComplex);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize*i + j;
            Complex* sum = (Complex*)resSum->elems[i][j];
            if (!(CompareFloats(sum->re, sumRe[idx]) && CompareFloats(sum->im, sumIm[idx]))) {
                printf(
                    "----- elem[%d][%d]: EXPECTED %.2f%s%.2f, GOT %.2f\n",
                    i, j, sumRe[idx], sumIm[idx] >= 0.0 ? "+" : "", 
                    sumIm[idx], *(float*)resSum->elems[i][j]
                );
                res = false;
            }
        }
    }

    if (res) {
        printf("\nPASSED complex sum test\n----------\n");
    } else {
        printf("\nFAILED complex sum test\n----------\n");
    }

    FreeMatrix(resSum);
    free(mx1->elems);
    free(mx2->elems);
    free(mx1);
    free(mx2);
    free(resSum); 

    return res ? 1 : 0;
}

int testComplexMulMatrix() {
    bool res = true;
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
    float mulRe[4] = {
        -2, -6,
        -2, -6,
    };
    float mulIm[4] = {
        0, 12,
        0, 24,
    };

    Matrix* mx1 = makeComplexMatrixFromArray(mSize, re1, im1);
    Matrix* mx2 = makeComplexMatrixFromArray(mSize, re2, im2);
    Matrix* resMul = MulMatrix(mx1, mx2, &SumCmplx, &MulCmplx);

    printf("START complex multiplication test\n----------\n");
    printf("FIRST matrix:\n");
    PrintMatrix(mx1, &PrintComplex);
    printf("\nSECOND matrix:\n");
    PrintMatrix(mx2, &PrintComplex);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(makeComplexMatrixFromArray(mSize, mulRe, mulIm), &PrintComplex);
    printf("\nGOT matrix:\n");
    PrintMatrix(resMul, &PrintComplex);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize*i + j;
            Complex* mul = (Complex*)resMul->elems[i][j];
            if (!(CompareFloats(mul->re, mulRe[idx]) && CompareFloats(mul->im, mulIm[idx]))) {
                printf(
                    "----- elem[%d][%d]: EXPECTED %.2f%s%.2f, GOT %.2f\n",
                    i, j, mulRe[idx], mulIm[idx] >= 0.0 ? "+" : "", 
                    mulIm[idx], *(float*)resMul->elems[i][j]
                );
                res = false;
            }
        }
    }

    if (res) {
        printf("\nPASSED complex multiplication test\n----------\n");
    } else {
        printf("\nFAILED complex multiplication test\n----------\n");
    }

    FreeMatrix(resMul);
    free(mx1->elems);
    free(mx2->elems);
    free(mx1);
    free(mx2);
    free(resMul);

    return res ? 1 : 0;
}

int testComplexMulByCMatrix() {
    bool res = true;
    const int mSize = 2;
    float re1[4] = {
        1, 2,
        4, 5,
    };
    float im1[4] = {
        4, 5,
        7, 8,
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
    Matrix* resMulByC = MulByConst(mx1, c, &MulCmplx);

    printf("START complex multiplication by const test\n----------\n");
    printf("MATRIX:\n");
    PrintMatrix(mx1, &PrintComplex);
    printf("\nCONST matrix: ");
    PrintComplex(c);
    printf("\n\nEXPECTED matrix:\n");
    PrintMatrix(makeComplexMatrixFromArray(mSize, mulByCRe, mulByCIm), &PrintComplex);
    printf("\nGOT matrix:\n");
    PrintMatrix(resMulByC, &PrintComplex);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize*i + j;
            Complex* mulByC = (Complex*)resMulByC->elems[i][j];
            if (!(CompareFloats(mulByC->re, mulByCRe[idx]) && CompareFloats(mulByC->im, mulByCIm[idx]))) {
                printf(
                    "----- elem[%d][%d]: EXPECTED %.2f%s%.2f, GOT %.2f\n",
                    i, j, mulByCRe[idx], mulByCIm[idx] >= 0.0 ? "+" : "", 
                    mulByCIm[idx], *(float*)resMulByC->elems[i][j]
                );
                res = false;
            }
        }
    }

    if (res) {
        printf("\nPASSED complex multiplication by const test\n----------\n");
    } else {
        printf("\nFAILED complex multiplication by const test\n----------\n");
    }

    FreeMatrix(resMulByC);
    free(mx1->elems);
    free(mx1);
    free(resMulByC);

    return res ? 1 : 0;
}

int testComplexMulByZMatrix() {
    bool res = true;
    const int mSize = 2;
    float re1[4] = {
        1, 2,
        4, 5,
    };
    float im1[4] = {
        4, 5,
        7, 8,
    };
    float mulByZRe[4] = {
        0, 0,
        0, 0,
    };
    float mulByZIm[4] = {
        0, 0,
        0, 0,
    };

    Complex* c = NewComplex(0, 0);
    Matrix* mx1 = makeComplexMatrixFromArray(mSize, re1, im1);
    Matrix* resMulByZ = MulByConst(mx1, c, &MulCmplx);

    printf("START complex multiplication by zero test\n----------\n");
    printf("MATRIX:\n");
    PrintMatrix(mx1, &PrintComplex);
    printf("\nCONST: ");
    PrintComplex(c);
    printf("\n\nEXPECTED matrix:\n");
    PrintMatrix(makeComplexMatrixFromArray(mSize, mulByZRe, mulByZIm), &PrintComplex);
    printf("\nGOT matrix:\n");
    PrintMatrix(resMulByZ, &PrintComplex);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize*i + j;
            Complex* mulByC = (Complex*)resMulByZ->elems[i][j];
            if (!(CompareFloats(mulByC->re, mulByZRe[idx]) && CompareFloats(mulByC->im, mulByZIm[idx]))) {
                printf(
                    "----- elem[%d][%d]: EXPECTED %.2f%s%.2f, GOT %.2f\n",
                    i, j, mulByZRe[idx], mulByZIm[idx] >= 0.0 ? "+" : "", 
                    mulByZIm[idx], *(float*)resMulByZ->elems[i][j]
                );
                res = false;
            }
        }
    }

    if (res) {
        printf("\nPASSED complex multiplication by zero test\n----------\n");
    } else {
        printf("\nFAILED complex multiplication by zero test\n----------\n");
    }

    FreeMatrix(resMulByZ);
    free(mx1->elems);
    free(mx1);
    free(resMulByZ);

    return res ? 1 : 0;
}

int testFloatsMulMatrix() {
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
    float mul[9] = {
        1.1, 6.6, -4.4,
        2.75, 16.5, -11,
        4.4, 26.4, -17.6,
    };

    Matrix* mx1 = makeFloatMatrixFromArray(mSize, x1);
    Matrix* mx2 = makeFloatMatrixFromArray(mSize, x2);
    Matrix* resMul = MulMatrix(mx1, mx2, &SumFloats, &MulFloats);

    printf("START float multiplication test\n----------\n");
    printf("FIRST matrix:\n");
    PrintMatrix(mx1, &PrintFloats);
    printf("\nSECOND matrix:\n");
    PrintMatrix(mx2, &PrintFloats);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(makeFloatMatrixFromArray(mSize, mul), &PrintFloats);
    printf("\nGOT matrix:\n");
    PrintMatrix(resMul, &PrintFloats);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize * i + j;
            if (!CompareFloats(*(float*)resMul->elems[i][j], mul[idx])) {
                printf("----- elem[%d][%d]: EXPECTED %.2f, GOT %.2f\n", i, j, mul[idx], *(float*)resMul->elems[i][j]);
                res = false;
            }
        }
    }
    
    if (res) {
        printf("\nPASSED float multiplication test\n----------\n");
    } else {
        printf("\nFAILED float multiplication test\n----------\n");
    }

    FreeMatrix(resMul);
    free(mx1->elems);
    free(mx2->elems);
    free(mx1);
    free(mx2);
    free(resMul);

    return res ? 1 : 0;
}

int testFloatsMulByEMatrix() {
    bool res = true;
    const int mSize = 3;
    float x1[9] = {
        1.1, 2.2, 3.3,
        4.4, 5.5, 6.6,
        7.7, 8.8, 9.9,
    };
    float x2[9] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    };

    Matrix* mx1 = makeFloatMatrixFromArray(mSize, x1);
    Matrix* mx2 = makeFloatMatrixFromArray(mSize, x2);
    Matrix* resMul = MulMatrix(mx1, mx2, &SumFloats, &MulFloats);

    printf("START float multiplication by E-matrix test\n----------\n");
    printf("FIRST matrix:\n");
    PrintMatrix(mx1, &PrintFloats);
    printf("\nSECOND matrix:\n");
    PrintMatrix(mx2, &PrintFloats);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(mx1, &PrintFloats);
    printf("\nGOT matrix:\n");
    PrintMatrix(resMul, &PrintFloats);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize * i + j;
            if (!CompareFloats(*(float*)resMul->elems[i][j], x1[idx])) {
                printf("----- elem[%d][%d]: EXPECTED %.2f, GOT %.2f\n", i, j, x1[idx], *(float*)resMul->elems[i][j]);
                res = false;
            }
        }
    }
    
    if (res) {
        printf("\nPASSED float multiplication by E-matrix test\n----------\n");
    } else {
        printf("\nFAILED float multiplication by E-matrix test\n----------\n");
    }

    FreeMatrix(resMul);
    free(mx1->elems);
    free(mx2->elems);
    free(mx1);
    free(mx2);
    free(resMul);

    return res ? 1 : 0;
}

int testFloatsSumMatrix() {
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

    Matrix* mx1 = makeFloatMatrixFromArray(mSize, x1);
    Matrix* mx2 = makeFloatMatrixFromArray(mSize, x2);
    Matrix* resSum = SumMatrix(mx1, mx2, &SumFloats);

    printf("START float sum test\n----------\n");
    printf("FIRST matrix:\n");
    PrintMatrix(mx1, &PrintFloats);
    printf("\nSECOND matrix:\n");
    PrintMatrix(mx2, &PrintFloats);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(makeFloatMatrixFromArray(mSize, sum), &PrintFloats);
    printf("\nGOT matrix:\n");
    PrintMatrix(resSum, &PrintFloats);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize * i + j;
            if (!CompareFloats(*(float*)resSum->elems[i][j], sum[idx])) {
                printf("----- elem[%d][%d]: EXPECTED %.2f, GOT %.2f\n", i, j, sum[idx], *(float*)resSum->elems[i][j]);
                res = false;
            }
        }
    }
    
    if (res) {
        printf("\nPASSED float sum test\n----------\n");
    } else {
        printf("\nFAILED float sum test\n----------\n");
    }

    FreeMatrix(resSum);
    free(mx1->elems);
    free(mx2->elems);
    free(mx1);
    free(mx2);
    free(resSum); 

    return res ? 1 : 0;
}

int testFloatsMulByCMatrix() {
    bool res = true;
    const int mSize = 3;
    float x1[9] = {
        1.1, 2.2, 3.3,
        4.4, 5.5, 6.6,
        7.7, 8.8, 9.9,
    };
    float mulByC[9] = {
        5.72, 11.44, 17.16,
        22.88, 28.6, 34.32,
        40.04, 45.76, 51.48,
    };
    float c = 5.2;

    Matrix* mx1 = makeFloatMatrixFromArray(mSize, x1);
    Matrix* resMulByC = MulByConst(mx1, &c, &MulFloats);

    printf("START float multiplication by const test\n----------\n");
    printf("MATRIX:\n");
    PrintMatrix(mx1, &PrintFloats);
    printf("\nCONST: %.2f\n", c);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(makeFloatMatrixFromArray(mSize, mulByC), &PrintFloats);
    printf("\nGOT matrix:\n");
    PrintMatrix(resMulByC, &PrintFloats);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize * i + j;
            if (!CompareFloats(*(float*)resMulByC->elems[i][j], (mulByC[idx]))) {
                printf("----- elem[%d][%d]: EXPECTED %.2f, GOT %.2f\n", i, j, mulByC[idx], *(float*)resMulByC->elems[i][j]);
                res = false;
            }
        }
    }
    
    if (res) {
        printf("\nPASSED float multiplication by const test\n----------\n");
    } else {
        printf("\nFAILED float multiplication by const test\n----------\n");
    }

    FreeMatrix(resMulByC);
    free(mx1->elems);
    free(mx1);
    free(resMulByC);

    return res ? 1 : 0;
}

int testFloatsMulByZMatrix() {
    bool res = true;
    const int mSize = 3;
    float x1[9] = {
        1.1, 2.2, 3.3,
        4.4, 5.5, 6.6,
        7.7, 8.8, 9.9,
    };
    float mulByZ[9] = {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
    };
    float c = 0.0;

    Matrix* mx1 = makeFloatMatrixFromArray(mSize, x1);
    Matrix* resMulByZ = MulByConst(mx1, &c, &MulFloats);

    printf("START float multiplication by zero test\n----------\n");
    printf("MATRIX:\n");
    PrintMatrix(mx1, &PrintFloats);
    printf("\nCONST: %.2f\n", c);
    printf("\nEXPECTED matrix:\n");
    PrintMatrix(makeFloatMatrixFromArray(mSize, mulByZ), &PrintFloats);
    printf("\nGOT matrix:\n");
    PrintMatrix(resMulByZ, &PrintFloats);

    for (int i = 0; i < mSize; ++i) {
        for (int j = 0; j < mSize; ++j) {
            int idx = mSize * i + j;
            if (!CompareFloats(*(float*)resMulByZ->elems[i][j], (mulByZ[idx]))) {
                printf("----- elem[%d][%d]: EXPECTED %.2f, GOT %.2f\n", i, j, mulByZ[idx], *(float*)resMulByZ->elems[i][j]);
                res = false;
            }
        }
    }
    
    if (res) {
        printf("\nPASSED float multiplication by zero test\n----------\n");
    } else {
        printf("\nFAILED float multiplication by zero test\n----------\n");
    }

    FreeMatrix(resMulByZ);
    free(mx1->elems);
    free(mx1);
    free(resMulByZ);

    return res ? 1 : 0;
}

void runTests() {
    int testCounter = 0;

    testCounter += testIntsSumMatrix();
    testCounter += testIntsMulMatrix();
    testCounter += testIntsMulByCMatrix();
    testCounter += testIntsMulByEMatrix();
    testCounter += testIntsMulByZMatrix();
    testCounter += testComplexSumMatrix();
    testCounter += testComplexMulMatrix();
    testCounter += testComplexMulByCMatrix();
    testCounter += testComplexMulByZMatrix();
    testCounter += testFloatsSumMatrix();
    testCounter += testFloatsMulMatrix();
    testCounter += testFloatsMulByCMatrix();
    testCounter += testFloatsMulByEMatrix();
    testCounter += testFloatsMulByZMatrix();

    printf("TESTS PASSED: %d/%d", testCounter, NUMBER_OF_TESTS);
    printf("\n%s", testCounter == NUMBER_OF_TESTS ? "OK" : "NOT OK");
}
