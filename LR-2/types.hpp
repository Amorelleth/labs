#pragma once
#include <cmath>

class Complex;
class Float;
class Int;

class Number {
    public:
        float length;

        Number() {};
        virtual ~Number() {};
        virtual void serialize (std::ostream&) const {};
        virtual Complex* to_complex() const;

        friend std::ostream& operator<<(std::ostream& out, Number& num);        
        friend bool operator<(const Number&, const Number&);
        friend bool operator<=(const Number&, const Number&);
        friend bool operator>=(const Number&, const Number&);
        friend bool operator>(const Number&, const Number&);
        friend Number* operator+(const Number&, const Number&);
        friend Number* operator-(const Number&, const Number&);
        friend Number* operator*(const Number&, const Number&);
        friend Number* operator/(const Number&, const Number&);
};

class Complex : public Number {
    public:
        float im;
        float re;

        Complex(): im(0), re(0) { length = 0; };
        Complex(float _re, float _im = 0) {
            re = _re;
            im = _im;
            length = float(sqrt(_re * _re + _im * _im));
        };
        ~Complex() {};

        Complex* to_complex() const {
            return new Complex(*this);
        };

        friend Complex operator+(const Complex& left, const Complex& right) {
            return Complex(left.re + right.re, left.im + right.im);
        };
        friend Complex operator-(const Complex& left, const Complex& right) {
            return Complex(left.re - right.re, left.im - right.im);
        };
        friend Complex operator*(const Complex& left, const Complex& right) {
            return Complex(left.re*right.re - left.im*right.im, left.re*right.im + left.im*right.re);
        };
        friend Complex operator/(const Complex& left, const Complex& right) {
            return Complex((left.re*right.re + left.im*right.im)/(right.re*right.re + right.im*right.im), (left.im*right.re - left.re*right.im)/(right.re*right.re + right.im*right.im));
        };
        friend bool operator==(const Complex& left, const Complex& right) {
            return left.re == right.re && left.im == right.im;
        };
        friend bool operator!=(const Complex& left, const Complex& right) {
            return left.re != right.re && left.im == right.im;
        };
        friend bool operator<(const Complex& left, const Complex& right) {
            return left.length < right.length;
        };
        friend bool operator<=(const Complex& left, const Complex& right) {
            return left.length <= right.length;
        };
        friend bool operator>=(const Complex& left, const Complex& right) {
            return left.length >= right.length;
        };
        friend bool operator>(const Complex& left, const Complex& right) {
            return left.length > right.length;
        };
        Complex& operator=(const Complex& cmplx) {
            im = cmplx.im;
            re = cmplx.re;
            return *this;
        }
        void serialize(std::ostream& out) const {
            out << re << (im >= 0 ? "+" : "") << im << "i"; 
        };
        friend std::ostream& operator<<(std::ostream& out, const Complex& cmplx) {
            out << cmplx.re << (cmplx.im >= 0 ? "+" : "") << cmplx.im << "i"; 
            return out;
        };
        friend std::istream& operator>>(std::istream &in, Complex &some) {
            in >> some.re;
            in >> some.im;
            return in;
        }
};

class Float : public Number {
    public:
        float data;
        Float(float d) {
            data = d;
            length = d;
        };
        ~Float() {}
        Complex* to_complex() const {
            return new Complex(data);
        };
        void serialize(std::ostream& out) const {
            out << data;
        };
        friend std::ostream& operator<<(std::ostream& out, const Float& some) {
            out << some.data;
            return out;
        };
        friend std::istream& operator>>(std::istream &in, Float &some) {
            in >> some.data;
            return in;
        }
};

class Int : public Number {
    public: 
        int data;

        Int(int d) {
            length = d;
            data = d;
        }
        ~Int() {}
        Complex* to_complex() const {
            return new Complex(data);
        };
        virtual void serialize(std::ostream& out) const {
            out << data;
        };
        friend std::ostream& operator<<(std::ostream& out, const Int& some) {
            out << some.data;
            return out;
        };
        friend std::istream& operator<<(std::istream &in, Int &some) {
            in >> some.data;
            return in;
        }
};

Complex* Number::to_complex() const { return NULL; };

bool operator==(const Number& left, const Number& right) {
    return *left.to_complex() == *right.to_complex();
};
bool operator!=(const Number& left, const Number& right) {
    return *left.to_complex() != *right.to_complex();
};
bool operator<(const Number& left, const Number& right) {
    return *left.to_complex() < *right.to_complex();
};
bool operator<=(const Number& left, const Number& right) {
    return *left.to_complex() <= *right.to_complex();
};
bool operator>(const Number& left, const Number& right) {
    return *left.to_complex() > *right.to_complex();
};
bool operator>=(const Number& left, const Number& right) {
    return *left.to_complex() >= *right.to_complex();
};
Number* operator+(const Number& left, const Number& right) {
    return new Complex(*left.to_complex() + *right.to_complex());
};
Number* operator-(const Number& left, const Number& right) {
    return new Complex(*left.to_complex() - *right.to_complex());
};
Number* operator*(const Number& left, const Number& right) {
    return new Complex(*left.to_complex() * *right.to_complex());
};
Number* operator/(const Number& left, const Number& right) {
    return new Complex(*left.to_complex() / *right.to_complex());
};
std::ostream& operator<<(std::ostream& out, Number& num) {
    num.serialize(out);
    return out;
};
