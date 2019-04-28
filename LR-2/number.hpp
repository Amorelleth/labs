#pragma once
#include <iostream>
#include <cmath>
#include "complex.hpp"
#include "types.hpp"

class Complex;

class Number {
    public:
        float length;

        Number() {};
        virtual ~Number() {};
        virtual void serialize (std::ostream&) const {};

        // friend Number operator+(const Number& left, const Number& right) {
            // Complex* lc = dynamic_cast<Complex*>(left));
 
            // return Complex(left) + Number(right);
        // };
        // friend Complex operator-(const Complex& left, const Complex& right) {
        //     return;
        // // };
        // friend Complex operator*(const Complex& left, const Complex& right) {
        //     return;
        // };
        // friend Complex operator/(const Number& left, const Number& right) {
        //     return;
        // };
        friend bool operator==(const Number& left, const Number& right) {
            return left.length == right.length;
        };
        friend bool operator<(const Number& left, const Number& right) {
            return left.length < right.length;
        };
        friend bool operator<=(const Number& left, const Number& right) {
            return left.length <= right.length;
        };
        friend bool operator>=(const Number& left, const Number& right) {
            return left.length >= right.length;
        };
        friend bool operator>(const Number& left, const Number& right) {
            return left.length > right.length;
        };



        bool operator<=(const Number* right) {
            std::cout << "f";
            return false;
        };
        // Number& operator=(const Number& num) {
        //     Complex(num)
        //     return *this;
        // }
        // friend std::ostream& operator<<(std::ostream& out, Number& num) {};
};
