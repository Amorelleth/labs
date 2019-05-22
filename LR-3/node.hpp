#pragma once
#include "types.hpp"

using namespace std;

template <class T>
class Node {
	public:
		T value;
        unsigned char height;
		Node<T> *left;
		Node<T> *mid;
		Node<T> *right;
		Node<T>() : left(nullptr), mid(nullptr), right(nullptr), value(T()) {};
		Node<T>(T _value) : left(nullptr), mid(nullptr), right(nullptr), value(_value) {};
		Node<T>(Node<T>* node) : left(node->left), mid(node->mid), right(node->right), value(node->value) {};
};