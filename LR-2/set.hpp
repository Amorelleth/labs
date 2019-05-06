#pragma once
#include <iostream>
#include <string>
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
        Node<T>* get_node(T) const;

        void delete_node(Node<T>*);
        void delete_head();
        void insert_node(Node<T>*);
    protected:
        Node<T>* get_head() const;
    public:
        friend bool test_clear();
        friend bool test_insert();
        friend bool test_merge();
        size_t size;
        Set() : head(nullptr), size(0) {};
        Set(Set &set) : size(set.size) {
            Node<T>* current = set.get_head();
            while (current != nullptr) {
                insert(current->data);
                current = current->next;
            }
        };
        Set(T arr[], int _size) : head(nullptr), size(0) {
            for (int i = 0; i < _size; i++) {
                insert(arr[i]);
            }
        }


        ~Set() {
            clear();
            delete head;
        }

        void insert(T);
        void clear();
        bool includes(T) const;
        bool includes_set(Set<T>&);
        bool equal(const Set<T>&) const;
        Set<T>* map(T (*func)(T));
        Set<T>* merge(const Set<T>&) const;
        Set<T>* intersection(const Set<T>&) const;
        Set<T>* subtract(const Set<T>&) const;
        T delete_elem(T);

        Set<T>& operator=(const Set<T>&);

        friend std::ostream& operator<<(std::ostream& out, const Set<T>& set) {
            auto current = set.head;
            while (current != nullptr) {
                out << *current->data << " ";
                current = current->next;
            }
            out << "\n";
            return out;
        }
        friend bool operator==(const Set<T>& left, const Set<T>& right) {
            return left.equal(right);
        };
        friend bool operator!=(const Set<T>& left, const Set<T>& right) {
            return !left.equal(right);
        };
        friend Set<T>* operator+(const Set<T>& left, const Set<T>& right) {
            return left.merge(right);
        };
        friend Set<T>* operator-(const Set<T>& left, const Set<T>& right) {
            return left.subtract(right);
        };
        friend Set<T>* operator*(const Set<T>& left, const Set<T>& right) {
            return left.intersection(right);
        };
};

template <class T>
Node<T>* Set<T>::get_node(T data) const {
    if (head == nullptr) {
        return nullptr;
    }
    int idx = 0;
    auto current = head;
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
    auto tmp = node->next->next;
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
        auto current = head;
        while (current->next != nullptr && *current->next->data < *node->data) {
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }
    return;
}

template <class T>
Set<T>* Set<T>::map(T (*func)(T)) {
    Node<T>* current = head;
    Set<T>* set = new Set<T>();
    while (current != nullptr) {
        set->insert(func(current->data));
        current = current->next;
    }
    return set;
};

template <class T>
bool Set<T>::includes(T data) const {
    return Set<T>::get_node(data) != nullptr;
}

template <class T>
bool Set<T>::includes_set(Set<T>& set) {
    if (size < set.size) {
        return false;
    }
    auto current_first = head;
    auto current_second = set.get_head();
    while (current_second != nullptr) {
        if (Set<T>::get_node(current_second->data) == nullptr) {
            return false;
        }
        current_second = current_second->next;
    }
    return true;
}

template <class T>
void Set<T>::insert(T data) {
    auto node = new Node<T>(data);
    Set<T>::insert_node(node);
    return;
}

template <class T>
bool Set<T>::equal(const Set<T>& set) const {
    if (size != set.size) {
        return false;
    }
    auto current_first = head;
    auto current_second = set.get_head();
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
Set<T>* Set<T>::merge(const Set<T>& set) const {
    auto new_set = new Set<T>;
    auto current_first = head;
    auto current_second = set.get_head();
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
Set<T>* Set<T>::intersection(const Set<T>& set) const {
    auto new_set = new Set<T>;
    auto current_first = head;
    auto current_second = set.get_head();
    while (current_first != nullptr) {
        if (set.get_node(current_first->data) != nullptr) {
            new_set->insert(current_first->data);
        }
        current_first = current_first->next;
    }
    return new_set;
}

template <class T>
Set<T>* Set<T>::subtract(const Set<T>& set) const {
    auto new_set = new Set<T>;
    auto current_first = head;
    auto current_second = set.get_head();
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
    if (*head->data == *data) {
        auto tmp = head->next;
        head->next = nullptr;
        delete head->next;
        head = tmp;
        size--;
        return data;
    }

    auto current = head;
    while (current->next->next != nullptr && *current->next->data != *data) {
        current = current->next;
    }
    if (*current->next->data == *data) {
        delete_node(current);
    }

    return data;
}

template <class T>
void Set<T>::clear() {
    auto current = head;
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
    auto current = set.get_head();
    size = set.size;
    while (current != nullptr) {
        insert(current->data);
        current = current->next;
    }
    return *this;
}
