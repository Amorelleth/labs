#ifndef COMPLEX
#define COMPLEX

typedef struct Complex {
    float re;
    float im;
} Complex;
Complex* NewComplex(float, float);
Complex SumComplex(const Complex, const Complex);
Complex MulComplex(const Complex, const Complex);

#endif