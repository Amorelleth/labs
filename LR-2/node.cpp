#include <iostream>
#include "node.hpp"

template <typename T>   
std::ostream& operator<<(std::ostream& out, const Node<T> &t) {
    out << t.data;
    return out;
};