#pragma once
#include <iostream>
#include "node.hpp"
#include "any.hpp"

class AnySet {
    private:
        Node<Any*>* head;
        Node<Any*>* get_node(Any*);

        void delete_node(Node<Any*>*);
        void delete_head();
        void insert_node(Node<Any*>*);
    public:
        size_t size;
        AnySet() : head(NULL), size(0) {};
        AnySet(AnySet &set) : size(set.size) {
            Node<Any*>* current = set.get_head();
            while (current != NULL) {
                insert(current->data);//ok
                current = current->next;
            }
        };

        ~AnySet() {
            clear();
            delete head;
        }

        void insert(Any*);
        void clear();
        bool includes(Any*);
        bool includes_set(AnySet&);
        bool equal(const AnySet&); // TODO перегрузить ==
        AnySet* merge(AnySet&);
        AnySet* intersection(AnySet&);
        AnySet* subtract(AnySet&);
        Node<Any*>* get_head() const;
        Any* delete_elem(Any*);

        AnySet& operator=(const AnySet&);

        friend std::ostream& operator<<(std::ostream& out, const AnySet& set) {
            Node<Any*>* current = set.head;
            while (current != NULL) {
                out << *current << " ";
                current = current->next;
            }
            out << "\n";
            return out;
        }
};

Node<Any*>* AnySet::get_node(Any* data) {
    if (head == NULL) {
        return NULL;
    }
    int idx = 0;
    Node<Any*>* current = head;
    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
        idx++;
    }
    return NULL;
}

void AnySet::delete_node(Node<Any*>* node) {
    Node<Any*>* tmp = node->next->next;
    node->next->next = NULL;
    delete node->next;
    node->next = tmp;
    size--;
}

void AnySet::delete_head() {
    head->next = NULL;
    delete head->next;
    head = NULL;
    delete head;
    size--;
}

void AnySet::insert_node(Node<Any*>* node) {
    if (AnySet::get_node(node->data) != NULL) {//ok
        return;
    }
    if (head != NULL) {
        std::cout << node->data << " " << (node->data <= head->data) << " " << head->data << "\n";
    }
    if (head == NULL || node->data <= head->data) { //ok
        node->next = head;
        head = node;
    } else {
        Node<Any*>* current = head;
        while (current->next != NULL && current->next->data < node->data) {//ok
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }
    return;
}

// AnySet::AnySet(AnySet &set) : size(set.size) {
//     Node<Any*>* current = set.get_head();
//     while (current != NULL) {
//         insert(current->data);
//         current = current->next;
//     }
// };

// AnySet::~AnySet() {
//     AnySet::clear();
//     delete head;
// }

bool AnySet::includes(Any* data) {
    return AnySet::get_node(data) != NULL;
}

bool AnySet::includes_set(AnySet& set) {
    if (size < set.size) {
        return false;
    }
    Node<Any*>* current_first = head;
    Node<Any*>* current_second = set.get_head();
    while (current_second != NULL) {
        if (AnySet::get_node(current_second->data) == NULL) {//ok
            return false;
        }
        current_second = current_second->next;
    }
    return true;
}

void AnySet::insert(Any* data) {
    Node<Any*>* node = new Node<Any*>(data);
    AnySet::insert_node(node);
    size++;
    return;
}

bool AnySet::equal(const AnySet& set) {
    if (size != set.size) {
        return false;
    }
    Node<Any*>* current_first = head;
    Node<Any*>* current_second = set.get_head();
    while (current_first != NULL) {
        if (current_first->data != current_second->data) {//ok
            return false;
        }
        current_first = current_first->next;
        current_second = current_second->next;
    }
    return true;
}

AnySet* AnySet::merge(AnySet& set) {
    AnySet* new_set = new AnySet;
    Node<Any*>* current_first = head;
    Node<Any*>* current_second = set.get_head();
    while (current_first != NULL) {
        new_set->insert(current_first->data);
        current_first = current_first->next;
    }
    while (current_second != NULL) {
        new_set->insert(current_second->data);
        current_second = current_second->next;
    }
    return new_set;
}

AnySet* AnySet::intersection(AnySet& set) {
    AnySet* new_set = new AnySet;
    Node<Any*>* current_first = head;
    Node<Any*>* current_second = set.get_head();
    while (current_first != NULL) {
        if (set.get_node(current_first->data) != NULL) {
            new_set->insert(current_first->data);
        }
        current_first = current_first->next;
    }
    return new_set;
}

AnySet* AnySet::subtract(AnySet& set) {
    AnySet* new_set = new AnySet;
    Node<Any*>* current_first = head;
    Node<Any*>* current_second = set.get_head();
    while (current_first != NULL) {
        if (!set.includes(current_first->data)) {
            new_set->insert(current_first->data);
        }
        current_first = current_first->next;
    }
    return new_set;
}

Node<Any*>* AnySet::get_head() const {
    return head;
}

Any* AnySet::delete_elem(Any* data) {
    Node<Any*>* current = head;
    while (current->next->data != data) {
        current = current->next;
    }
    Node<Any*>* tmp = current;
    delete_node(current);

    return data;
}

void AnySet::clear() {
    Node<Any*>* current = head;
    if (current == NULL) {
        return;
    }
    while (current->next != NULL) {
        delete_node(current);
    }
    delete_head();
}


// TODO переписать

// std::ostream& AnySet::operator<<(std::ostream& out, const AnySet& set) {
//     Node<Any*>* current = set.head;
//     while (current != NULL) {
//         out << *current << " ";
//         current = current->next;
//     }
//     out << "\n";
//     return out;
// }

AnySet& AnySet::operator=(const AnySet& set) {
    Node<Any*>* current = set.get_head();
    size = set.size;
    while (current != NULL) {
        insert(current->data);//ok
        current = current->next;
    }
    return *this;
}
