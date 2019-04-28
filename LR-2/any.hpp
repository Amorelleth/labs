#pragma once
#include <iostream>
#include "complex.hpp"

class Int;
class Float;
class Complex;

class Any {
    public:
        Any(int) {};
        Any(float) {};
        Any(complex) {};
        virtual ~Any() {};
       
        virtual bool equal(Any*) const { return false; };
        virtual bool less(Any*) const { return false; };
        virtual void serialize (std::ostream&) const {};
        friend bool operator==(Any&, Any&);
        friend bool operator<=(const Any&, const Any&);
        friend bool operator<(const Any&, const Any&);
        friend std::ostream& operator<<(std::ostream&, Any&);
};
