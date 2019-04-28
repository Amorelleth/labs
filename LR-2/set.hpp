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
        Set() : head(nullptr), size(0) {};
        Set(Set &set) : size(set.size) {
            Node<T>* current = set.get_head();
            while (current != nullptr) {
                insert(current->data);//ok
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
        bool equal(const Set<T>&); // перегрузить ==
        Set<T>* map(T* (*func)(size_t, T));
        Set<T>* merge(Set<T>&);
        Set<T>* intersection(Set<T>&);
        Set<T>* subtract(Set<T>&);
        Node<T>* get_head() const;
        T delete_elem(T);

        Set<T>& operator=(const Set<T>&);

        friend std::ostream& operator<<(std::ostream& out, const Set<T>& set) {
            Node<T>* current = set.head;
            while (current != nullptr) {
                out << *current->data << " ";
                current = current->next;
            }
            out << "\n";
            return out;
        }
};

template <class T>
Node<T>* Set<T>::get_node(T data) {
    if (head == nullptr) {
        return nullptr;
    }
    int idx = 0;
    Node<T>* current = head;
    while (current != nullptr) {
        if (*current->data == *data) {
            return current;
        }
        current = current->next;
        idx++;
    }
    return nullptr;
}

template <class T>
void Set<T>::delete_node(Node<T>* node) {
    Node<T>* tmp = node->next->next;
    node->next->next = nullptr;
    delete node->next;
    node->next = tmp;
    size--;
}

template <class T>
void Set<T>::delete_head() {
    head->next = nullptr;
    delete head->next;
    head = nullptr;
    delete head;
    size--;
}

template <class T>
void Set<T>::insert_node(Node<T>* node) {
    if (Set<T>::get_node(node->data) != nullptr) {
        return;
    }
    size++;
    if (head == nullptr || *node->data <= *head->data)  {
        node->next = head; 
        head = node;
    } else {
        Node<T>* current = head;
        while (current->next != nullptr && *current->next->data < *node->data) {
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }
    return;
}

// template <class T>
// Set<T>* Set<T>::map(T* (*func)(size_t, T)) {
//     Node<T>* current = head;
//     while (current->next != nullptr && *current->next->data < *node->data) {
//         *func()
//         current = current->next;
//     }
// };

// template <class T>
// Set<T>::Set(Set &set) : size(set.size) {
//     Node<T>* current = set.get_head();
//     while (current != nullptr) {
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
    return Set<T>::get_node(data) != nullptr;
}

template <class T>
bool Set<T>::includes_set(Set<T>& set) {
    if (size < set.size) {
        return false;
    }
    Node<T>* current_first = head;
    Node<T>* current_second = set.get_head();
    while (current_second != nullptr) {
        if (Set<T>::get_node(current_second->data) == nullptr) {//ok
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
    return;
}

template <class T>
bool Set<T>::equal(const Set<T>& set) {
    if (size != set.size) {
        return false;
    }
    Node<T>* current_first = head;
    Node<T>* current_second = set.get_head();
    while (current_first != nullptr) {
        if (!(*current_first->data == *current_second->data)) {
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
    while (current_first != nullptr) {
        new_set->insert(current_first->data);
        current_first = current_first->next;
    }
    while (current_second != nullptr) {
        new_set->insert(current_second->data);
        current_second = current_second->next;
    }
    return new_set;
}

template <class T>
Set<T>* Set<T>::intersection(Set<T>& set) {
    Set<T>* new_set = new Set<T>;
    Node<T>* current_first = head;
    Node<T>* current_second = set.get_head();
    while (current_first != nullptr) {
        if (set.get_node(current_first->data) != nullptr) {
            new_set->insert(current_first->data);
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
    while (current_first != nullptr) {
        if (!set.includes(current_first->data)) {
            new_set->insert(current_first->data);
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
    while (current->next->data != data) {
        current = current->next;
    }
    Node<T>* tmp = current;
    delete_node(current);

    return data;
}

template <class T>
void Set<T>::clear() {
    Node<T>* current = head;
    if (current == nullptr) {
        return;
    }
    while (current->next != nullptr) {
        delete_node(current);
    }
    delete_head();
}

template <class T>
Set<T>& Set<T>::operator=(const Set<T>& set) {
    Node<T>* current = set.get_head();
    size = set.size;
    while (current != nullptr) {
        insert(current->data);//ok
        current = current->next;
    }
    return *this;
}
