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
