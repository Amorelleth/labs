#ifndef COMPLEX
#define COMPLEX

typedef struct Complex {
    int re;
    int im;
} Complex;

Complex* NewComplex(int re, int im) { 
    Complex* c = (Complex*)malloc(sizeof(Complex));
    c->re = re;
    c->im = im;

    return c;
}

Complex SumComplex(const Complex c1, const Complex c2) {
    return *NewComplex(c1.re + c2.re, c1.im + c2.im);
}

Complex MulComplex(const Complex c1, const Complex c2) {
    return *NewComplex(c1.re*c2.re - c1.im*c2.im, c1.re*c2.im + c1.im*c2.re);
}

#endif