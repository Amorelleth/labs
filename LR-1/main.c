#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "matrix.h"
#include "complex.h"
#include "functions.h"
#include "test.h"

#define MAX_RAND 100

void getInt(int* num) {
    int res;
    do {
        res = scanf("%d", num);
        while(getchar() != '\n') continue;
        if(res != 1) printf("%s","Введите целое число\n");
    } while(res != 1);
}

void getFloat(float* num) {
    int res;
    do {
        res = scanf("%f", num);
        while(getchar() != '\n') continue;
        if(res != 1) printf("%s","Введите число\n");
    } while(res != 1);
}

Matrix* initMatrix(int size, int type, bool random) {
    srand(time(NULL));
    void*** mtrx;

    switch(type) {
        case 1: {
            int*** m = (int***)malloc(size * sizeof(int**));
            for (int i = 0; i < size; i++) {
                m[i] = (int**)malloc(size * sizeof(int*));
                for (int j = 0; j < size; j++) {
                    m[i][j] = (int*)malloc(sizeof(int));
                    if (random) {
                        *m[i][j] = rand() % 2 == 1 ? rand() % MAX_RAND : -rand() % MAX_RAND;
                        continue;
                    }
                    printf("element[%d][%d]: ", i, j);
                    getInt(m[i][j]);
                }
            }
            mtrx = (void***)m;
            break;
        }
        case 2: {
            float*** m = (float***)malloc(size * sizeof(float**));
            for (int i = 0; i < size; i++) {
                m[i] = (float**)malloc(size * sizeof(float*));
                for (int j = 0; j < size; j++) {
                    m[i][j] = (float*)malloc(sizeof(float));
                    if (random) {
                        *m[i][j] = (float)(rand() % 2 == 1 ? rand() % MAX_RAND : -rand() % MAX_RAND);
                        continue;
                    }
                    printf("element[%d][%d]: ", i, j);
                    getFloat(m[i][j]);
                }
            }
            mtrx = (void***)m;
            break;
        }
        case 3: {
            Complex*** m = (Complex***)malloc(size * sizeof(Complex**));
            for (int i = 0; i < size; i++) {
                m[i] = (Complex**)malloc(size * sizeof(Complex*));
                for (int j = 0; j < size; j++) {
                    m[i][j] = (Complex*)malloc(sizeof(Complex));
                    float re, im;
                    if (random) {
                        re = (float)(rand() % 2 == 1 ? rand() % MAX_RAND : -rand() % MAX_RAND);
                        im = (float)(rand() % 2 == 1 ? rand() % MAX_RAND : -rand() % MAX_RAND);
                    } else {
                        printf("Re(element[%d][%d]): ", i, j);
                        getFloat(&re);
                        printf("Im(element[%d][%d]): ", i, j);
                        getFloat(&im);
                    }
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

int main(int argc, char * argv[]) {
    if (argc > 1 && strcmp(argv[1], "-t") == 0) {
        runTests();
    }
    int type, size, start, action;
    Matrix* Neo;
    Matrix* Morpheus;

    do {
        printf("Выберите тип данных (int - 1, float - 2, complex - 3): ");
        getInt(&type);
    } while (type < 1 || type > 3);
    do {
        printf("Введите размер матрицы (>0): ");
        getInt(&size);
    } while (size <= 0);
    do {
        printf("1 - ввести значения, 2 - случайная матрица: \n");
        getInt(&start);
    } while (start != 1 && start != 2);

    if (start == 1) printf("Введите элементы первой матрицы:\n\n");
    Neo = initMatrix(size, type, start == 2);
    if (start == 1) printf("\nВведите элементы второй матрицы:\n\n");
    Morpheus = initMatrix(size, type, start == 2);
   
    do {
        printf("\n1 - сложить, 2 - умножить, 3 - умножить на число, 0 - завершить программу\n");
        getInt(&action);
    } while (!(action == 1 || action == 2 || action == 3 || action == 0));

    const void* PrintType = Print(type);
    const void* SumType = GetSumFunction(type);
    const void* MulType = GetMulFunction(type);

    printf("\nМатрица 1:\n");
    PrintMatrix(Neo, PrintType);
    printf("\n\nМатрица 2:\n");
    PrintMatrix(Morpheus, PrintType);

    switch (action) {
        case 1: {
            Matrix* Sum = SumMatrix(Neo, Morpheus, SumType);
            printf("\n\nСумма матриц:\n");
            PrintMatrix(Sum, PrintType);
            FreeMatrix(Sum);
            free(Sum);

            break;
        }
        case 2: {
            Matrix* Mul = MulMatrix(Neo, Morpheus, SumType, MulType);
            printf("\n\nПроизведение матриц:\n");
            PrintMatrix(Mul, PrintType);
            FreeMatrix(Mul);
            free(Mul);

            break;
        }
        case 3: {
            void* constant;

            printf("\nВведите константу\n");
            switch(type) {
                case 1: {
                    int c;
                    getInt(&c);
                    constant = (void*)&c;
                    break;
                }
                case 2: {
                    float c;
                    getFloat(&c);
                    constant = (void*)&c;
                    break;
                }
                case 3: {
                    Complex* c;
                    float re, im;
                    printf("Re: ");
                    getFloat(&re);
                    printf("Im: ");
                    getFloat(&im);
                    c = NewComplex(re, im);
                    constant = (void*)c;
                    break;
                }
            }

            Matrix* MulByC1 = MulByConst(Neo, constant, MulType);
            Matrix* MulByC2 = MulByConst(Neo, constant, MulType);
            printf("\n\nУмножение на константу матрицы 1: \n");
            PrintMatrix(MulByC1, PrintType);
            printf("\n\nУмножение на константу матрицы 2: \n");
            PrintMatrix(MulByC2, PrintType);
            
            FreeMatrix(MulByC1);
            FreeMatrix(MulByC2);
            free(MulByC1);
            free(MulByC2);
            break;
        }
        case 0: break;
    }

    FreeMatrix(Neo);
    FreeMatrix(Morpheus);
    free(Neo);
    free(Morpheus);

    return 0;
}
