#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "complex.h"

// Матричное сложение и умножение, умножение на скаляр, прибавление к строке линейной комбинации других строк

void printIntMatrix(Matrix* m) {
    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            printf("%d ", *(int*)m->elems[i][j]);
        }
        printf("\n");
    }
}

void* SumInts(const void* num1, const void* num2) {
    const int* sumPtr = NULL;
    int int1 = *((int*)num1);
    int int2 = *((int*)num2);
    int* sum = (int*)malloc(sizeof(int));
    *sum = int1 + int2;
    sumPtr = sum;

    return (void*)sumPtr;
}

void* MulInts(const void* num1, const void* num2) {
    const int* mulPtr = NULL;
    int int1 = *((int*)num1);
    int int2 = *((int*)num2);
    int* mul = (int*)malloc(sizeof(int));
    *mul = int1 * int2;
    mulPtr = mul;

    return (void*)mulPtr;
}

void* SumCmplx(const void* num1, const void* num2) {
    const int* sumPtr = NULL;
    int int1 = *((int*)num1);
    int int2 = *((int*)num2);
    int* sum = (int*)malloc(sizeof(int));
    *sum = int1 + int2;
    sumPtr = sum;

    return (void*)sumPtr;
}

void* MulCmplx(const void* num1, const void* num2) {
    const Complex* mulPtr = NULL;
    Complex cx1 = *((Complex*)num1);
    Complex cx2 = *((Complex*)num2);
    Complex* mul = (Complex*)malloc(sizeof(Complex));
    *mul = MulComplex(cx1, cx2);
    mulPtr = mul;

    return (void*)mulPtr;
}

Matrix* initIntsMatrix() {
    int n;
    printf("Size of matrix: ");
    scanf("%d", &n);

    int*** m = (int***)malloc(n * sizeof(int**));
    for (int i = 0; i < n; i++) {
        m[i] = (int**)malloc(n * sizeof(int*));
        for (int j = 0; j < n; j++) {
            m[i][j] = (int*)malloc(sizeof(int));
            printf("element[%d][%d]: ", i, j);
            scanf("%d", m[i][j]);
        }
    }
    return NewMatrix(n, (void***)m);
}

int main(void) {
    Matrix* Neo = initIntsMatrix();
    Matrix* Morpheus = initIntsMatrix();

    Matrix* Sum = SumMatrix(Neo, Morpheus, &SumInts);
    Matrix* Mul = MulMatrix(Neo, Morpheus, &SumInts, &MulInts);

    int const c = 5;
    Matrix* MulByC = MulByConst(Neo, (void*)&c, &MulInts);

    printIntMatrix(Neo);
    printf("\n");
    printIntMatrix(Morpheus);
    printf("\n");
    printIntMatrix(Sum);
    printf("\n");
    printIntMatrix(Mul);
    printf("\n");
    printIntMatrix(MulByC);

    FreeMatrix(Neo);
    FreeMatrix(Morpheus);
    free(Neo);
    free(Morpheus);

    return 0;
}
