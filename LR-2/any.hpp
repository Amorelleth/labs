#pragma once
#include <iostream>
// #include "int.hpp"
class Int;
class Float;

class Any {
    public:
        virtual ~Any() {};        
        virtual bool equal(const Any*) const = 0;
        virtual bool less(const Any*) const = 0;
        // virtual bool less(const Any*) const = 0;
        virtual void serialize (std::ostream& out) const {};
        friend bool operator==(const Any& any_1, const Any& any_2);
        friend bool operator<=(const Any& any_1, const Any& any_2);
        friend bool operator<(const Any& any_1, const Any& any_2);
        friend std::ostream& operator<<(std::ostream&, const Any*);
};

bool operator==(const Any& any_1, const Any& any_2) {
    return (&any_1)->equal(&any_2);
}
bool operator<=(const Any& any_1, const Any& any_2)  {
    return (&any_1)->equal(&any_2) || (&any_1)->less(&any_2);
    return false;
}
bool operator<(const Any& any_1, const Any& any_2)  {
    return (&any_1)->less(&any_2);
    return false;
}
std::ostream& operator<<(std::ostream& out, const Any* any) {
    any->serialize(out);
    return out;
};

// friend bool operator==(const Any& one, const Any& two) {
//     return (&one)->equal(&two);
// }
// friend bool operator<=(const Any& any_1, const Any& any_2)  {
//     return (&one)->equal(&two) || (&one)->less(&two);
// }
// friend bool operator<(const Any&, const Any&)  {
//     return (&one)->less(&two);
// }

class Float : public Any {
    public: 
        float data;
        Float(float d) {
            data = d;
        }
        ~Float() {}
        virtual void serialize (std::ostream& out) const {
            out << data;
        }
        bool equal(const Any* any) const {
            return any->equal(this);
        }
        bool equal(const Int* some_int) const {
            return data == some_int->data;
        }
        // bool equal(const Complex* some_complex) const {
        //     return false;
        // }
        bool equal(const Float* some_float) const {
            return data == some_float->data;
        }
        bool less(const Any* any) const {
            return any->less(this);
        }
        bool less(const Int* some_int) const {
            return data < some_int->data;
        }
        bool less(const Float* some_float) const {
            return data < some_float->data;
        }
        // bool less(const Complex* some_complex) const {
        //     return false;
        // }
};

class Int : public Any {
    public: 
        int data;
        Int(int some_data) {
            data = some_data;
        }
        ~Int() {}

        virtual void serialize (std::ostream& out) const {
            out << data;
        }

        bool equal(const Any* any) const {
            return any->equal(this);
        }
        bool equal(const Int* some_int) const {
            return data == some_int->data;
        }
        bool equal(const Float* some_float) const {
            return data == some_float->data;
        }
        // bool equal(const Complex* some_complex) const {
        //     return false;
        // }
        bool less(const Any* any) const {
            return any->less(this);
        }
        bool less(const Int* some_int) const {
            return data < some_int->data;
        }
        bool less(const Float* some_float) const {
            return data < some_float->data;
        }
        // bool less(const Complex* some_complex) const {
        //     return false;
        // }
};

// TODO добавить комплексные

// class Complex : public Any {
//     public:
//         complex data;
//         Complex(complex some_data) {
//             data = some_data;
//         }
//         ~Complex() {}

//         virtual void serialize (std::ostream& out) const {
//             out << data;
//         }

//         bool equal(const Any* any) const {
//             return any->equal(this);
//         }
//         bool equal(const Int* some_int) const {
//             return false;
//         }
//         bool equal(const Float* some_float) const {
//             return false;
//         }
//         // bool equal(const Complex* some_complex) const {
//         //     return data == some_complex;
//         // }
//         bool less(const Any* any) const {
//             return any->less(this);
//         }
//         bool less(const Int* some_int) const {
//             return data < some_int->data;
//         }
//         bool less(const Float* some_float) const {
//             return data < some_float->data;
//         }
//         // bool less(const Complex* some_complex) const {
//         //     return data < some_complex
//         // }
// };
