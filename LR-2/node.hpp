#pragma once

template <typename T> 
struct Node {
    Node(const T& d) : data(new T(d)), next(NULL) {}
    Node(const T& d, Node<T>* n) : data(new T(d)), next(n) {}
    ~Node() {
        delete data;
        delete next;
    }
    T* data;
    Node<T> *next;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Node<T> &t) {
    out << *t.data;
    return out;
};