#pragma once
#include "any.hpp"
#include "complex.hpp"

class Int;
class Complex;

class Float : public Any {
    public: 
        float data;

        Float(float d) : Any(d) {
            data = d;
        }
        ~Float() {}
        virtual void serialize(std::ostream& out) const {
            std::cout << "j";
            out << data;
        }
        bool equal(Any* any);
        bool less(Any* any);
        bool operator<=(const Int* any_2) const;
        bool operator<=(const Float* any_2) const;
        bool operator<(const Int* any_2) const;
        bool operator<(const Float* any_2) const;
        bool operator==(const Int* any_2) const;
        bool operator==(const Float* any_2) const;
        friend std::ostream& operator<<(std::ostream& out, const Float some) {
            out << some.data;
            return out;
        };
};

class Int : public Any {
    public: 
        int data;
        Int(int d) : Any(d) {
            data = d;
        }
        ~Int() {}

        virtual void serialize(std::ostream& out) const {
            std::cout << "j";

            out << data;
        }
        bool equal(Any* any);
        bool less(Any* any);
        bool operator<=(const Int* any_2) const;
        bool operator<=(const Float* any_2) const;
        bool operator<(const Float* any_2) const;
        friend std::ostream& operator<<(std::ostream& out, const Int some) {
            out << some.data;
            return out;
        };
};

class Complex : public Any {
    public:
        complex data;
        Complex(complex d) : Any(d) {
            data = d;
        }
        ~Complex() {}

        virtual void serialize(std::ostream& out) const {
            std::cout << "j";

            out << data;
        }
        friend std::ostream& operator<<(std::ostream& out, const Complex some) {
            out << some.data;
            return out;
        };
        bool equal(Any* any);
        bool less(Any* any);
};

bool Int::equal(Any* any) {
    if (Float* a = dynamic_cast<Float*>(any)) {
        return a->data == data;
    }
    if (Int* a = dynamic_cast<Int*>(any)) {
        return a->data == data;
    }
    if (Complex* a = dynamic_cast<Complex*>(any)) {
        // return a->data == data;
        return false;
    }
    return false;
}

bool Float::equal(Any* any) {
    if (Float* a = dynamic_cast<Float*>(any)) {
        return a->data == data;
    }
    if (Int* a = dynamic_cast<Int*>(any)) {
        return a->data == data;
    }
    if (Complex* a = dynamic_cast<Complex*>(any)) {
        // return a->data == data;
        return false;
    }
    return false;
}

bool Complex::equal(Any* any) {
    if (Float* a = dynamic_cast<Float*>(any)) {
        // return a->data == data;
        return false;
    }
    if (Int* a = dynamic_cast<Int*>(any)) {
        // return a->data == data;
        return false;
    }
    if (Complex* a = dynamic_cast<Complex*>(any)) {
        return a->data == data;
    }
    return false;
}

bool Int::less(Any* any) {
    if (Float* a = dynamic_cast<Float*>(any)) {
        return data < a->data;
    }
    if (Int* a = dynamic_cast<Int*>(any)) {
        return data < a->data;
    }
    if (Complex* a = dynamic_cast<Complex*>(any)) {
        // return a->data == data;
        return false;
    }
    return false;
}

bool Float::less(Any* any) {
    if (Float* a = dynamic_cast<Float*>(any)) {
        return data < a->data;
    }
    if (Int* a = dynamic_cast<Int*>(any)) {
        return data < a->data;
    }
    if (Complex* a = dynamic_cast<Complex*>(any)) {
        // return a->data == data;
        return false;
    }
    return false;
}

bool Complex::less(Any* any) {
    if (Float* a = dynamic_cast<Float*>(any)) {
        // return a->data == data;
        return false;
    }
    if (Int* a = dynamic_cast<Int*>(any)) {
        // return a->data == data;
        return false;
    }
    if (Complex* a = dynamic_cast<Complex*>(any)) {
        return data < a->data;
    }
    return false;
}

bool operator==(Any& left, Any& right) {
    std::cout << left << right;
    if (Float* a = dynamic_cast<Float*>(&right)) {
        std::cout << "downcast to float successful\n";
        return a->equal(&left);
    }
    if (Int* a = dynamic_cast<Int*>(&right)) {
        std::cout << "downcast to int successful\n";
        return a->equal(&left);
    }
    if (Complex* a = dynamic_cast<Complex*>(&right)) {
        std::cout << "downcast to complex successful\n";
        return a->equal(&left);
    }
    return false;
}

bool operator<(Any& left, Any& right) {
    std::cout << left << right;
    if (Float* a = dynamic_cast<Float*>(&right)) {
        std::cout << "downcast to float successful\n";
        return a->less(&left);
    }
    if (Int* a = dynamic_cast<Int*>(&right)) {
        std::cout << "downcast to int successful\n";
        return a->less(&left);
    }
    if (Complex* a = dynamic_cast<Complex*>(&right)) {
        std::cout << "downcast to complex successful\n";
        return a->less(&left);
    }
    return false;
}

bool operator<=(Any& left, Any& right) {
    return left < right || left == right;
}

std::ostream& operator<<(std::ostream& out, Any& any) {
    if (Float* a = dynamic_cast<Float*>(&any)) {
        std::cout << "downcast to float successful\n";
        out << a->data;
    }
    if (Int* a = dynamic_cast<Int*>(&any)) {
        std::cout << "downcast to int successful\n";
        out << a->data;
    }
    if (Complex* a = dynamic_cast<Complex*>(&any)) {
        std::cout << "downcast to complex successful\n";
        out << a->data;
    }
    return out;
};