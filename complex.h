#ifndef COMPLEX
#define COMPLEX

typedef struct Complex {
    float re;
    float im;
} Complex;

Complex* NewComplex(float re, float im) { 
    Complex* cmpl = (Complex*)malloc(sizeof(Complex));
    cmpl->re = re;
    cmpl->im = im;

    return cmpl;
}

Complex SumComplex(const Complex cmpl1, const Complex cmpl2) {
    return *NewComplex(cmpl1.re + cmpl2.re, cmpl1.im + cmpl2.im);
}

Complex MulComplex(const Complex cmpl1, const Complex cmpl2) {
    return *NewComplex(cmpl1.re*cmpl2.re - cmpl1.im*cmpl2.im, cmpl1.re*cmpl2.im + cmpl1.im*cmpl2.re);
}

#endif