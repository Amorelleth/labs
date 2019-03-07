#include <stdio.h>
#include <stdbool.h>
// #include "matrix.h"
#include "functions.h"

#ifndef TESTS
#define TESTS

Matrix* makeMatrixFromArray(int size, int* array) {
    int*** mx = (int***)malloc(size * sizeof(int**));
    for (uint16 i = 0; i < size; i++) {
        mx[i] = (int**)malloc(size * sizeof(int*));
        for (uint16 j = 0; j < size; j++) {
            mx[i][j] = (int*)&array[size*i + j];
        }
    }

    return NewMatrix(size, (void***)mx);
}

void testIntsMatrix() {
    bool res = true;
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
    int mulBy5[9] = {
        5, 10, 15,
        20, 25, 30,
        35, 40, 45,
    };
    int c = 5;

    Matrix* mx1 = makeMatrixFromArray(3, x1);
    Matrix* mx2 = makeMatrixFromArray(3, x2);
    Matrix* resSum = SumMatrix(mx1, mx2, &SumInts);
    Matrix* resMul = MulMatrix(mx1, mx2, &SumInts, &MulInts);
    Matrix* resMulByC = MulByConst(mx1, &c, &MulInts);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (*(int*)resSum->elems[i][j] != sum[3*i + j]) {
                printf("test sum ints failed\n");
                res = false;
                break;
            }
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (*(int*)resMul->elems[i][j] != mul[3*i + j]) {
                printf("test mul ints failed\n");
                res = false;
                break;
            }
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (*(int*)resMulByC->elems[i][j] != mulBy5[3*i + j]) {
                printf("test mul ints by const failed\n");
                res = false;
                break;
            }
        }
    }
    if (res) {
        printf("int tests passed OK\n");
    }


    free(mx1->elems);
    free(mx2->elems);
    free(resSum->elems);
    free(resMul->elems);
    free(resMulByC->elems);
    free(mx1);
    free(mx2);
    free(resSum); 
    free(resMul);
    free(resMulByC);
}

#endif