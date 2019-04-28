#pragma once
#include <iostream>
#include <cmath>

class complex {
    public:
        float im;
        float re;
        float length;
        complex(): im(0), re(0), length(0) {};
        complex(float _re, float _im) {
            im = _im;
            re = _re;
            length = sqrt(_re * _re * _im * _im);
        };
        friend complex operator+(const complex& left, const complex& right) {
            return complex(left.re + right.re, left.im + right.im);
        };
        friend complex operator-(const complex& left, const complex& right) {
            return complex(left.re - right.re, left.im - right.im);
        };
        friend complex operator*(const complex& left, const complex& right) {
            return complex(left.re*right.re - left.im*right.im, left.re*right.im + left.im*right.re);
        };
        friend complex operator/(const complex& left, const complex& right) {
            return complex((left.re*right.re + left.im*right.im)/(right.re*right.re + right.im*right.im), (left.im*right.re - left.re*right.im)/(right.re*right.re + right.im*right.im));
        };
        friend bool operator==(const complex& left, const complex& right) {
            return left.re == right.re && left.im == right.im;
        };
        friend bool operator<(const complex& left, const complex& right) {
            return left.length < right.length;
        };
        friend bool operator<=(const complex& left, const complex& right) {
            return left.length <= right.length;
        };
        friend bool operator>=(const complex& left, const complex& right) {
            return left.length >= right.length;
        };
        friend bool operator>(const complex& left, const complex& right);
        complex& operator=(const complex& cmplx) {
            im = cmplx.im;
            re = cmplx.re;
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& out, const complex& cmplx) {
            out << cmplx.re << (cmplx.im >= 0 ? "+" : "") << cmplx.im << "i ";
            return out;
        }
};
