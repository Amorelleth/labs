#pragma once
#include <cmath>
#include "complex.hpp"

class Float : public Number {
    public:
        float data;
        Float(float d) {
            data = d;
            length = d;
        };
        ~Float() {}
        void serialize(std::ostream& out) const {
            out << data;
        };
        friend std::ostream& operator<<(std::ostream& out, const Float& some) {
            out << some.data;
            return out;
        };
};

class Int : public Number {
    public: 
        int data;

        Int(int d) {
            length = d;
            data = d;
        }
        ~Int() {}
        virtual void serialize(std::ostream& out) const {
            out << data;
        };
        friend std::ostream& operator<<(std::ostream& out, const Int& some) {
            out << some.data;
            return out;
        };
};

std::ostream& operator<<(std::ostream& out, Number& num) {
    num.serialize(out);
    return out;
};
