#pragma once
#include "any.hpp"
// #include "complex.hpp"

class Int;
// class Complex;

class Float : public Any {
    public: 
        float data;

        Float(float d)  {
            data = d;
        }
        ~Float() {}
        virtual void serialize(std::ostream& out) const {
            out << data;
        }
        bool equal(const Any* any) const {
            return any->equal(this);
        }
        bool equal(const Int* some_int) const;
        // bool equal(const Complex* some_complex) const;
        bool equal(const Float* some_float) const;
        bool less(const Any* any) const { return false; };
        bool less(const Int* some_int) const;
        bool less(const Float* some_float) const;
        // bool less(const Complex* some_complex);
        bool operator<=(const Int* any_2) const {
            std::cout << "==";
            return this->equal(any_2) || this->less(any_2);
        }
        bool operator<=(const Float* any_2) const {
            std::cout << "==";
            return this->equal(any_2) || this->less(any_2);
        }
        bool operator<(const Int* any_2) const {
            std::cout << "less";
            return this->less(any_2);
        }
        bool operator<(const Float* any_2) const {
            std::cout << "less";
            return this->less(any_2);;
        }
        bool operator==(const Int* any_2) const {
            std::cout << "less";
            return this->less(any_2);
        }
        bool operator==(const Float* any_2) const {
            std::cout << "less";
            return this->less(any_2);
        }
};

class Int : public Any {
    public: 
        int data;
        Int(int d) {
            data = d;
        }
        ~Int() {}

        virtual void serialize(std::ostream& out) const {
            out << data;
        }
        bool equal(const Any* any) const {
            return any->equal(this);
        }
        bool equal(const Int* some_int) const;
        bool equal(const Float* some_float) const;
        // bool equal(const Complex* some_complex) const;
        bool less(const Any* any) const { return false; };
        bool less(const Int* some_int) const;
        bool less(const Float* some_float) const;
        // bool less(const Complex* some_complex) const;
        bool operator<=(const Int* any_2) const {
            std::cout << "==";
            return this->equal(any_2);
        }
        bool operator<=(const Float* any_2) const {
            std::cout << "==";
            return this->equal(any_2);
        }
        bool operator<(const Float* any_2) const {
            std::cout << "==";
            return this->less(any_2);
        }
};

// class Complex : public Any {
//     public:
//         complex data;
//         Complex(complex some_data) {
//             data = some_data;
//         }
//         ~Complex() {}

//         virtual void serialize (std::ostream& out) {};
//         bool equal(const Any* any) const;
//         bool equal(const Int* some_int) const;
//         bool equal(const Float* some_float) const;
//         // bool equal(const Complex* some_complex) const;
//         bool less(const Any* any) const;
//         bool less(const Int* some_int) const;
//         bool less(const Float* some_float) const;
//         // bool less(const Complex* some_complex) const;
// };
