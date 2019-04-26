#ifndef MATRIX
#define MATRIX

typedef struct Matrix {
    void*** elems;
    int size;
} Matrix;
Matrix* NewMatrix(int size, void*** elems);
Matrix* SumMatrix(Matrix *mtrx1, Matrix *mtrx2, void*(*sum)(const void*, const void*));
Matrix* MulMatrix(Matrix *mtrx1, Matrix *mtrx2, void*(*sum)(const void*, const void*), void*(*mul)(const void*, const void*));
Matrix* MulByConst(Matrix *mtrx1, const void* c, void*(*mul)(const void*, const void*));
void PrintMatrix(Matrix* m, void(*print)(const void*));
void FreeMatrix(Matrix* m);

#endif
