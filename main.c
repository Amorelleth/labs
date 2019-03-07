#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "matrix.h"
#include "complex.h"
#include "test.h"
#include "functions.h"

#ifndef UINT16
#define UINT16
typedef unsigned short int uint16;
#endif

// Матричное сложение и умножение, умножение на скаляр, прибавление к строке линейной комбинации других строк

Matrix* initMatrix(uint16 size, int type) {
    void*** mtrx;
    switch(type) {
        case 1: {
            int*** m = (int***)malloc(size * sizeof(int**));
            for (uint16 i = 0; i < size; i++) {
                m[i] = (int**)malloc(size * sizeof(int*));
                for (uint16 j = 0; j < size; j++) {
                    m[i][j] = (int*)malloc(sizeof(int));
                    printf("element[%d][%d]: ", i, j);
                    scanf("%d", m[i][j]);
                }
            }
            mtrx = (void***)m;
            break;
        }
        case 2: {
            float*** m = (float***)malloc(size * sizeof(float**));
            for (uint16 i = 0; i < size; i++) {
                m[i] = (float**)malloc(size * sizeof(float*));
                for (uint16 j = 0; j < size; j++) {
                    m[i][j] = (float*)malloc(sizeof(float));
                    printf("element[%d][%d]: ", i, j);
                    scanf("%f", m[i][j]);
                }
            }
            mtrx = (void***)m;
            break;
        }
        case 3: {
            Complex*** m = (Complex***)malloc(size * sizeof(Complex**));
            for (uint16 i = 0; i < size; i++) {
                m[i] = (Complex**)malloc(size * sizeof(Complex*));
                for (uint16 j = 0; j < size; j++) {
                    m[i][j] = (Complex*)malloc(sizeof(Complex));
                    int re, im;
                    printf("Re(element[%d][%d]): ", i, j);
                    scanf("%d", &re);
                    printf("Im(element[%d][%d]): ", i, j);
                    scanf("%d", &im);
                    m[i][j] = NewComplex(re, im);
                }
            }
            mtrx = (void***)m;
            break;
        }
    }

    return NewMatrix(size, mtrx);
}

void* Print(int type) {
    switch (type) {
        case 1: return &PrintInts;
        case 2: return &PrintFloats;
        case 3: return &PrintComplex;
    }
    return NULL;
}

void* GetSumFunction(int type) {
    switch (type) {
        case 1: return &SumInts;
        case 2: return &SumFloats;
        case 3: return &SumCmplx;
    }
    return NULL;
}

void* GetMulFunction(int type) {
    switch (type) {
        case 1: return &MulInts;
        case 2: return &MulFloats;
        case 3: return &MulCmplx;
    }
    return NULL;
}

void runTests() {
    testIntsMatrix();
}

int main(void) {
    runTests();

    int type;
    Matrix* Neo;
    Matrix* Morpheus;

    printf("Выберите тип данных (int - '1', float - '2', complex - '3'): ");
    while (true) {
        if (scanf("%d", &type) == 1) {
            if (type == 1 || type == 2 || type == 3) {
                uint16 size;
                printf("Введите размер матрицы: ");
                scanf("%hu", &size);

                printf("Введите элементы первой матрицы:\n\n");
                Neo = initMatrix(size, type);
                printf("\nВведите элементы второй матрицы:\n\n");
                Morpheus = initMatrix(size, type);
                
                // printf("\nВведите коэффициент умножения первой матрицы:\n\n");
                // scanf(c);

                const void* PrintType = Print(type);
                const void* SumType = GetSumFunction(type);
                const void* MulType = GetMulFunction(type);
                Matrix* Sum = SumMatrix(Neo, Morpheus, SumType);
                Matrix* Mul = MulMatrix(Neo, Morpheus, SumType, MulType);
                // Matrix* MulByC = MulByConst(Neo, MulType, (void*)&c);

                printf("\nМатрица 1:\n");
                PrintMatrix(Neo, PrintType);
                printf("\n\nМатрица 2:\n");
                PrintMatrix(Morpheus, PrintType);
                printf("\n\nСумма матриц:\n");
                PrintMatrix(Sum, PrintType);
                printf("\n\nПроизведение матриц:\n");
                PrintMatrix(Mul, PrintType);
                // printf("\n\nУмножение на константу %s: ", (char)c);
                // PrintMatrix(MulByC, PrintType);

                break;
            }
        }
        while (getchar() != '\n') {
            continue;
        }
        printf("Неверный тип, попробуйте еще раз\n");
    }

    FreeMatrix(Neo);
    FreeMatrix(Morpheus);
    free(Neo);
    free(Morpheus);

    return 0;
}
