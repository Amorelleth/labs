#pragma once
#include <iostream>
#include "node.hpp"

// - map, where
// + объединение
// + пересечение
// + вычитание
// + проверка на включение подмножества
// + проверка на вхождение элемента
// + сравнение (равенство) двух

template <class T> class Set {
    private:
        Node<T>* head;
        Node<T>* get_node(T);

        void delete_node(Node<T>*);
        void delete_head();
        void insert_node(Node<T>*);
    public:
        size_t size;
        Set() : head(NULL), size(0) {};
        Set(Set &set) : size(set.size) {
            Node<T>* current = set.get_head();
            while (current != NULL) {
                insert(*current->data);//ok
                current = current->next;
            }
        };

        ~Set() {
            clear();
            delete head;
        }

        void insert(T);
        void clear();
        bool includes(T);
        bool includes_set(Set<T>&);
        bool equal(const Set<T>&); // TODO перегрузить ==
        Set<T>* merge(Set<T>&);
        Set<T>* intersection(Set<T>&);
        Set<T>* subtract(Set<T>&);
        Node<T>* get_head() const;
        T delete_elem(T);

        Set<T>& operator=(const Set<T>&);

        friend std::ostream& operator<<(std::ostream& out, const Set<T>& set) {
            Node<T>* current = set.head;
            while (current != NULL) {
                out << *current << " ";
                current = current->next;
            }
            out << "\n";
            return out;
        }
};

template <class T>
Node<T>* Set<T>::get_node(T data) {
    if (head == NULL) {
        return NULL;
    }
    int idx = 0;
    Node<T>* current = head;
    while (current != NULL) {
        if (*current->data == data) {
            return current;
        }
        current = current->next;
        idx++;
    }
    return NULL;
}

template <class T>
void Set<T>::delete_node(Node<T>* node) {
    Node<T>* tmp = node->next->next;
    node->next->next = NULL;
    delete node->next;
    node->next = tmp;
    size--;
}

template <class T>
void Set<T>::delete_head() {
    head->next = NULL;
    delete head->next;
    head = NULL;
    delete head;
    size--;
}

template <class T>
void Set<T>::insert_node(Node<T>* node) {
    if (Set<T>::get_node(*node->data) != NULL) {//ok
        return;
    }
    if (head == NULL || *node->data <= *head->data)  { //ok
        node->next = head; 
        head = node;
    } else {
        Node<T>* current = head;
        while (current->next != NULL && *current->next->data < *node->data) {//ok
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }
    return;
}

// template <class T>
// Set<T>::Set(Set &set) : size(set.size) {
//     Node<T>* current = set.get_head();
//     while (current != NULL) {
//         insert(current->data);
//         current = current->next;
//     }
// };

// template <class T>
// Set<T>::~Set() {
//     Set<T>::clear();
//     delete head;
// }

template <class T>
bool Set<T>::includes(T data) {
    return Set<T>::get_node(data) != NULL;
}

template <class T>
bool Set<T>::includes_set(Set<T>& set) {
    if (size < set.size) {
        return false;
    }
    Node<T>* current_first = head;
    Node<T>* current_second = set.get_head();
    while (current_second != NULL) {
        if (Set<T>::get_node(*current_second->data) == NULL) {//ok
            return false;
        }
        current_second = current_second->next;
    }
    return true;
}

template <class T>
void Set<T>::insert(T data) {
    Node<T>* node = new Node<T>(data);
    Set<T>::insert_node(node);
    size++;
    return;
}

template <class T>
bool Set<T>::equal(const Set<T>& set) {
    if (size != set.size) {
        return false;
    }
    Node<T>* current_first = head;
    Node<T>* current_second = set.get_head();
    while (current_first != NULL) {
        if (*current_first->data != *current_second->data) {//ok
            return false;
        }
        current_first = current_first->next;
        current_second = current_second->next;
    }
    return true;
}

template <class T>
Set<T>* Set<T>::merge(Set<T>& set) {
    Set<T>* new_set = new Set<T>;
    Node<T>* current_first = head;
    Node<T>* current_second = set.get_head();
    while (current_first != NULL) {
        new_set->insert(*current_first->data);
        current_first = current_first->next;
    }
    while (current_second != NULL) {
        new_set->insert(*current_second->data);
        current_second = current_second->next;
    }
    return new_set;
}

template <class T>
Set<T>* Set<T>::intersection(Set<T>& set) {
    Set<T>* new_set = new Set<T>;
    Node<T>* current_first = head;
    Node<T>* current_second = set.get_head();
    while (current_first != NULL) {
        if (set.get_node(*current_first->data) != NULL) {
            new_set->insert(*current_first->data);
        }
        current_first = current_first->next;
    }
    return new_set;
}

template <class T>
Set<T>* Set<T>::subtract(Set<T>& set) {
    Set<T>* new_set = new Set<T>;
    Node<T>* current_first = head;
    Node<T>* current_second = set.get_head();
    while (current_first != NULL) {
        if (!set.includes(*current_first->data)) {
            new_set->insert(*current_first->data);
        }
        current_first = current_first->next;
    }
    return new_set;
}

template <class T>
Node<T>* Set<T>::get_head() const {
    return head;
}

template <class T>
T Set<T>::delete_elem(T data) {
    Node<T>* current = head;
    while (*current->next->data != data) {
        current = current->next;
    }
    Node<T>* tmp = current;
    delete_node(current);

    return data;
}

template <class T>
void Set<T>::clear() {
    Node<T>* current = head;
    if (current == NULL) {
        return;
    }
    while (current->next != NULL) {
        delete_node(current);
    }
    delete_head();
}


// TODO переписать

// template <class T>
// std::ostream& Set<T>::operator<<(std::ostream& out, const Set<T>& set) {
//     Node<T>* current = set.head;
//     while (current != NULL) {
//         out << *current << " ";
//         current = current->next;
//     }
//     out << "\n";
//     return out;
// }

template <class T>
Set<T>& Set<T>::operator=(const Set<T>& set) {
    Node<T>* current = set.get_head();
    size = set.size;
    while (current != NULL) {
        insert(*current->data);//ok
        current = current->next;
    }
    return *this;
}
