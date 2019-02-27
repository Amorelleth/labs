#ifndef MATRIX
#define MATRIX

typedef struct Matrix {
    void*** elems;
    int size;
} Matrix;

Matrix* NewMatrix(int size, void*** elems) { 
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->size = size;
    m->elems = elems;
    return m;
}

Matrix* SumMatrix(Matrix *m1, Matrix *m2, void*(*sum)(const void*, const void*)) {
    int n = m1->size;

    void*** m = (void***)malloc(n * sizeof(void**));
    for (int i = 0; i < n; i++) {
        m[i] = (void**)malloc(n * sizeof(void*));
        for (int j = 0; j < n; j++) {
            m[i][j] = (*sum)(m1->elems[i][j], m2->elems[i][j]);
        }
    }
    Matrix* mx = NewMatrix(n, m);
    return mx;
}

Matrix* MulMatrix(Matrix *m1, Matrix *m2, void*(*sum)(const void*, const void*), void*(*mul)(const void*, const void*)) {
    int n = m1->size;

    void*** m = (void***)malloc(n * sizeof(void**));
    for (int i = 0; i < n; i++) {
        m[i] = (void**)malloc(n * sizeof(void*));
        for (int j = 0; j < n; j++) {
            m[i][j] = (*mul)(m1->elems[i][0], m2->elems[0][j]);
            for(int k = 1; k < n; k++) {
                m[i][j] = (*sum)(m[i][j], (*mul)(m1->elems[i][k], m2->elems[k][j]));
            }
        }
    }

    Matrix* mx = NewMatrix(n, m);
    return mx;
}

Matrix* MulByConst(Matrix *m1, const void* c, void*(*mul)(const void*, const void*)) {
    int n = m1->size;

    void*** m = (void***)malloc(n * sizeof(void**));
    for (int i = 0; i < n; i++) {
        m[i] = (void**)malloc(n * sizeof(void*));
        for (int j = 0; j < n; j++) {
            m[i][j] = (*mul)(c, m1->elems[i][j]);
        }
    }

    Matrix* mx = NewMatrix(n, m);
    return mx;
}

void FreeMatrix(Matrix* m) { 
    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            free(m->elems[i][j]);
        }
    }
    free(m->elems);

    return;
}

#endif