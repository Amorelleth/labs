#pragma once
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include "node.hpp"

// + map (построить новое дерево поэлементным преобразованием)
// + where (построить новое дерево, в которое входят лишь те узлы исходного, которые удовлетворяют заданному условию)
// - Извлечение поддерева (по заданному элементу)
// - Поиск на вхождение поддерева
// - Поиск элемента на вхождение

using namespace std;

template <class T>
class TTree {
	private:
		Node<T> *search(T, Node<T>*);
		void map(Node<T>*, T (*func)(T));
		void print_node(Node<T>*, ofstream&);
		void copy(Node<T>*);
		void merge(TTree<T>*, Node<T>*);
		void where(TTree<T>*, Node<T>*, bool (*func)(T));
		void destroy_tree(Node<T>*);
		void insert(T, Node<T>*);
		void inorder_print(Node<T>*, ostringstream&, string prefix = "", string postfix = "") const;
		void preorder_print(Node<T>*, ostringstream&, string prefix = "", string postfix = "") const;
		bool are_identical(Node<T>*, Node<T>*);
		bool is_subtree(Node<T>*, TTree<T>*);

		Node<T>* _root;
		TTree(Node<T>* root) : _root(root) {}

	protected:
		Node<T>* _get_root() {
			return _root;
		}
	public:
		friend bool test_insert();
		friend bool test_destroy_tree();
		friend bool _empty_test_destroy_tree();

		TTree() : _root(nullptr) {}
		TTree(TTree<T>* tree) { tree->copy(); }
		~TTree() { destroy_tree(_root); _root = nullptr; }

		Node<T>* search(T key);
		TTree<T>* sub_tree(T key);
		TTree<T>* map(T (*func)(T));
		TTree<T>* copy();
		TTree<T>* merge(TTree<T>*);
        TTree<T>* where(bool (*func)(T));
		bool is_subtree(TTree<T>*);
		void insert(T);
		void inorder_print(ostringstream&) const;
		void preorder_print(ostringstream&) const;
		void make_graph(string);

		friend bool operator==(TTree<T>& left, TTree<T>& right) {
			return left.are_identical(left._root, right._root);
		};
		friend ostream& operator<<(ostream& out, const TTree<T>& tree) {
			std::ostringstream ss;
            tree.preorder_print(ss);
			out << ss.str();
            return out;
        }
		string to_string() {
			std::ostringstream ss;
            preorder_print(ss);
			return ss.str();
		}
};

template <class T>
void TTree<T>::make_graph(string file) {
	ofstream outfile(file + ".dot");
	outfile << "digraph d {" << endl;

	print_node(_root, outfile);	
	outfile.close();

	ofstream outfile_2(file + ".dot", ios::app);
	outfile_2 << "}" << endl;
	outfile_2.close();

	string command = "dot " + file + ".dot -Tpng -o" + file + ".png";
	system(command.c_str());
}

template <class T>
void TTree<T>::insert(T key, Node<T> *node){
	queue<Node<T>*> q; 
    q.push(node);
  
    while (!q.empty()) { 
        Node<T>* node = q.front(); 
        q.pop(); 
  
        if (!node->left) { 
            node->left = new Node(key); 
            break; 
        } else q.push(node->left);
		if (!node->mid) {
            node->mid = new Node(key); 
            break; 
        } else q.push(node->mid);
        if (!node->right) {
            node->right = new Node(key); 
            break; 
        } else q.push(node->right);
    } 
}

template <class T>
void TTree<T>::insert (T key) {
	if (_root != nullptr){
		insert(key, _root);
	} else {
		_root = new Node<T>;
		_root->value = key;
		_root->left = nullptr;
		_root->mid = nullptr;
		_root->right = nullptr;
	}
}

template <class T>
Node<T>* TTree<T>::search(T key, Node<T> *node){
	if (node == nullptr) return nullptr;
	if (*key == *node->value) return node;

	Node<T>* res = search(key, node->left);
	if (res == nullptr) {
		res = search(key, node->mid);
	}
	if (res == nullptr) {
		res = search(key, node->right);
	}
	return res;
}

template <class T>
Node<T> *TTree<T>::search(T key){
	return search(key, _root);
}

template <class T>
bool TTree<T>::are_identical(Node<T>* node1, Node<T>* node2) {
    if (node1 == nullptr && node2 == nullptr) {
        return true;
	}
    if (node1 == nullptr || node2 == nullptr) {
        return false;
	}
    return (*node1->value == *node2->value &&
		are_identical(node1->left, node2->left) &&
		are_identical(node1->mid, node2->mid) &&
		are_identical(node1->right, node2->right));
}
 
template <class T>
bool TTree<T>::is_subtree(TTree<T>* tree) {
    if (tree->_root == nullptr) return true;
    return is_subtree(_root, tree);
}

template <class T>
bool TTree<T>::is_subtree(Node<T>* node, TTree<T>* tree) {
    if (node == nullptr) return false;
    if (are_identical(node, tree->_root)) return true;  

    return is_subtree(node->left, tree)
		|| is_subtree(node->mid, tree)
		|| is_subtree(node->right, tree);  
}

template <class T>
void TTree<T>::destroy_tree(Node<T>* node) {
	if (node != nullptr) {
        if (node->left != nullptr) destroy_tree(node->left);
        if (node->mid != nullptr) destroy_tree(node->mid);
        if (node->right != nullptr) destroy_tree(node->right);
        delete node;
    }
}

template <class T>
void TTree<T>::print_node(Node<T>* node, ofstream& outfile) {
    outfile << "    \"" << node->value << "\"[label=\"" << *node->value << "\"];\n";
    if (node->left != nullptr) {
		outfile << "    \"" << node->value << "\"->\"" << node->left->value << "\";" << endl;
		print_node(node->left, outfile);
	}
    if (node->mid != nullptr) {
		outfile << "    \"" << node->value << "\"->\"" << node->mid->value << "\";" << endl;
		print_node(node->mid, outfile);
	}
    if (node->right != nullptr) {
		outfile << "    \"" << node->value << "\"->\"" << node->right->value << "\";" << endl;
		print_node(node->right, outfile);
	}
}

template <class T>
void TTree<T>::inorder_print(ostringstream& out) const {
	inorder_print(_root, out, "", "");
}

template <class T>
void TTree<T>::inorder_print(Node<T>* node, ostringstream& out, string prefix, string postfix) const {
	if (node != nullptr) {
        out << prefix;
        out << " " << *node->value << " ";
        inorder_print(node->mid, out, "[", "]");
		inorder_print(node->left, out, "{", "}");
		inorder_print(node->right, out, "{", "}");
        out << postfix;
    }
}

template <class T>
void TTree<T>::preorder_print(ostringstream& out) const {
    preorder_print(_root, out, "(", ")");
}

template <class T>
void TTree<T>::preorder_print(Node<T> *node, ostringstream& out, string prefix, string postfix) const {
	if (node != nullptr) {
        out << prefix << " " << *node->value << " " << postfix;
        inorder_print(node->mid, out, "[", "]");
        inorder_print(node->left, out, "{", "}");
        inorder_print(node->right, out, "{", "}");
	}
}

template <class T>
TTree<T>* TTree<T>::sub_tree(T key) {
	return new TTree(search(key));
}

template <class T>
TTree<T>* TTree<T>::map(T (*func)(T)) {
	if (_root == nullptr) return new TTree<T>;
	auto new_root = new Node<T>(_root);
	map(new_root, func);
	return new TTree<T>(new_root);
}

template <class T>
void TTree<T>::map(Node<T>* node, T (*func)(T)) {
	if (node != nullptr) {
		node->value = func(node->value);
		if (node->left != nullptr) {
			node->left = new Node<T>(node->left);
			map(node->left, func);
		}
		if (node->mid != nullptr) {
			node->mid = new Node<T>(node->mid);
			map(node->mid, func);
		}
		if (node->right != nullptr) {
			node->right = new Node<T>(node->right);
			map(node->right, func);
		}
	}
}

template <class T>
TTree<T>* TTree<T>::copy() {
	auto new_root = new Node<T>(_root);
	copy(new_root);
	return new TTree<T>(new_root);
}

template <class T>
void TTree<T>::copy(Node<T>* node) {
	if (node != nullptr) {
		if (node->left != nullptr) {
			node->left = new Node<T>(node->left);
			copy(node->left);
		}
		if (node->mid != nullptr) {
			node->mid = new Node<T>(node->mid);
			copy(node->mid);
		}
		if (node->right != nullptr) {
			node->right = new Node<T>(node->right);
			copy(node->right);
		}
	}
}

template <class T>
TTree<T>* TTree<T>::where(bool (*func)(T)) {
	auto tree = new TTree<T>;
	where(tree, _root, func);
	return tree;
}

template <class T>
void TTree<T>::where(TTree<T>* tree, Node<T>* node, bool (*func)(T)) {
	if (node != nullptr) {
		if (func(node->value)) tree->insert(node->value);
		if (node->left != nullptr) where(tree, node->left, func);
		if (node->mid != nullptr) where(tree, node->mid, func);
		if (node->right != nullptr) where(tree, node->right, func);
	}
}

template <class T>
TTree<T>* TTree<T>::merge(TTree<T>* inserting_tree) {
	if (_root == nullptr && inserting_tree->_root == nullptr) {
		return new TTree<T>;
	}
	if (_root == nullptr) {
		auto tree = inserting_tree->copy();
		return tree;
	}
	auto tree = this->copy();
	merge(tree, inserting_tree->_root);
	return tree;
}

template <class T>
void TTree<T>::merge(TTree<T>* tree, Node<T>* node) {
	if (node != nullptr) {
		tree->insert(node->value);
		if (node->left != nullptr) merge(tree, node->left);
		if (node->mid != nullptr) merge(tree, node->mid);
		if (node->right != nullptr) merge(tree, node->right);
	}
}


