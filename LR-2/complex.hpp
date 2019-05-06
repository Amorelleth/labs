#pragma once
#include <iostream>
#include <cmath>
#include "number.hpp"

class Complex : public Number {
    public:
        float im;
        float re;

        Complex(): im(0), re(0) { length = 0; };
        Complex(float _re, float _im) {
            re = _re;
            im = _im;
            length = float(sqrt(_re * _re + _im * _im));
        };
        ~Complex() {};

        Complex operator=(const Complex& right) {
            re == right.re;
            im == right.im;
            return *this;
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
};
