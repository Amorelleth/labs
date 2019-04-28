#pragma once
#include "types.hpp"

template <typename T> 
struct Node {
    Node(const T& d) : data(d), next(NULL) {}
    Node(const T& d, Node<T>* n) : data(d), next(n) {}
    ~Node() {
        delete next;
    }
    T data;
    Node<T> *next;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, Node<T> &t) {
    if (Float* a = dynamic_cast<Float*>(t.data)) {
        out << a->data;
    }
    if (Int* a = dynamic_cast<Int*>(t.data)) {
        out << a->data;
    }
    // if (Complex* a = dynamic_cast<Complex*>(t.data)) {
    //     out << a->data;
    // }
    out << t.data;
    return out;
};
