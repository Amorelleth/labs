#pragma once

template <typename T>
struct Node {
    Node(const T& d) : data(d), next(nullptr) {}
    Node(const T& d, Node<T>* n) : data(d), next(n) {}
    ~Node() {
        delete next;
    }
    T data;
    Node<T> *next;
    friend std::ostream& operator <<(std::ostream &os, const Node<T>& node){
        return os << node.data;
    }
};
