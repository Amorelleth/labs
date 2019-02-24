#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Матричное сложение и умножение, умножение на скаляр, прибавление к строке линейной комбинации других строк

struct Complex {
    int re;
    int im;
};

typedef struct Matrix {
    void*** elems;
    int size;
} Matrix;

Matrix* NewMatrix(int size, void*** elems) { 
    Matrix* m = malloc(sizeof(Matrix));
    m->size = size;
    m->elems = elems;
    return m;
}

void FreeMatrix(Matrix* m) { 
    int i, j;

    for (i = 0; i < m->size; i++) {
        for (j = 0; j < m->size; j++) {
            free(m->elems[i][j]);
        }
    }
    //free m.elems
}

void printIntMatrix(Matrix* m) {
    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            printf("%d ", *(int*)m->elems[i][j]);
        }
        printf("\n");
    }
}

Matrix* SumMatrix(Matrix *m1, Matrix *m2, void*(*sum)(const void*, const void*)) {
    int i, j;
    int n = m1->size;

    void*** m = (void***)malloc(n * sizeof(void**));
    for (i = 0; i < n; i++) {
        m[i] = (void**)malloc(n * sizeof(void*));
        for (j = 0; j < n; j++) {
            // m[i][j] = (void*)malloc(sizeof(void));

            m[i][j] = (*sum)(m1->elems[i][j], m2->elems[i][j]);

            // printf("\n(%d)\n", *((int*)m[i][j]));
            //memcpy(m[i][j], vp, sizeof(void));
            // m[i][j] = vp;
            // printf("\n(%d)\n", *(int*)m[i][j]);

        }
    }

    Matrix* mx = NewMatrix(n, m);

    // printIntMatrix(mx);
    // printf("\n");

    return mx;
}

void* SumInts(const void* num1, const void* num2) {
    const int* sumPtr = NULL;
    int int1 = *((int*)num1);
    int int2 = *((int*)num2);
    int* sum = (int*)malloc(sizeof(int));
    *sum = int1 + int2;

    sumPtr = sum;

    // printf("%d func", *(int*)(const void*)sumPtr);

    return (void*)sumPtr;
}

Matrix* initIntsMatrix() {
    int n, i, j;
    printf("Size of matrix: ");
    scanf("%d", &n);

    int*** m = (int***)malloc(n * sizeof(int**));
    for (i = 0; i < n; i++) {
        m[i] = (int**)malloc(n * sizeof(int*));
        for (j = 0; j < n; j++) {
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

    // printf("%d", ((int**)Neo.elems)[0][1]);

    printIntMatrix(Neo);
    printf("\n");
    printIntMatrix(Morpheus);
    printf("\n");
    printIntMatrix(Sum);


    FreeMatrix(Neo);
    FreeMatrix(Morpheus);

    free(Neo);
    free(Morpheus);

    // printf("------\n%d-------\n\n\n", *(int*)(Sum->elems[0][0]));

    return 0;
}
