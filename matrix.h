#include <stdlib.h>

#ifndef UINT16
#define UINT16
typedef unsigned short int uint16;
#endif

#ifndef MATRIX
#define MATRIX

typedef struct Matrix {
    void*** elems;
    uint16 size;
} Matrix;

Matrix* NewMatrix(uint16 size, void*** elems) { 
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->size = size;
    m->elems = elems;
    return m;
}

Matrix* SumMatrix(Matrix *mtrx1, Matrix *mtrx2, void*(*sum)(const void*, const void*)) {
    uint16 n = mtrx1->size;

    void*** m = (void***)malloc(n * sizeof(void**));
    for (uint16 i = 0; i < n; i++) {
        m[i] = (void**)malloc(n * sizeof(void*));
        for (uint16 j = 0; j < n; j++) {
            m[i][j] = (*sum)(mtrx1->elems[i][j], mtrx2->elems[i][j]);
        }
    }
    Matrix* mx = NewMatrix(n, m);
    return mx;
}

Matrix* MulMatrix(Matrix *mtrx1, Matrix *mtrx2, void*(*sum)(const void*, const void*), void*(*mul)(const void*, const void*)) {
    uint16 n = mtrx1->size;

    void*** m = (void***)malloc(n * sizeof(void**));
    for (uint16 i = 0; i < n; i++) {
        m[i] = (void**)malloc(n * sizeof(void*));
        for (uint16 j = 0; j < n; j++) {
            m[i][j] = (*mul)(mtrx1->elems[i][0], mtrx2->elems[0][j]);
            for(uint16 k = 1; k < n; k++) {
                m[i][j] = (*sum)(m[i][j], (*mul)(mtrx1->elems[i][k], mtrx2->elems[k][j]));
            }
        }
    }

    Matrix* mx = NewMatrix(n, m);
    return mx;
}

Matrix* MulByConst(Matrix *mtrx1, const void* c, void*(*mul)(const void*, const void*)) {
    uint16 n = mtrx1->size;

    void*** m = (void***)malloc(n * sizeof(void**));
    for (uint16 i = 0; i < n; i++) {
        m[i] = (void**)malloc(n * sizeof(void*));
        for (uint16 j = 0; j < n; j++) {
            m[i][j] = (*mul)(c, mtrx1->elems[i][j]);
        }
    }

    Matrix* mx = NewMatrix(n, m);
    return mx;
}

void PrintMatrix(Matrix* m, void(*print)(const void*)) {
    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            (*print)(m->elems[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

void FreeMatrix(Matrix* m) { 
    for (uint16 i = 0; i < m->size; i++) {
        for (uint16 j = 0; j < m->size; j++) {
            free(m->elems[i][j]);
        }
    }
    free(m->elems);

    return;
}

#endif
