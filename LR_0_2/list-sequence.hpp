#pragma once
#include <iostream>
#include "node.hpp"
#include "sequence.hpp"

template<class T> class ListSequence : public Sequence<T> {
    private:
        Node<T>* _head;
        Node<T>* GetNode(int);
        Node<T>* GetNodeByData(T);
        Node<T>* GetFirstNode() { return _head; };
        Node<T>* GetLastNode() { return GetNode(this->length - 1); };
    protected:
        void Serialize(std::ostream&) const override;

    public:
        ListSequence() : Sequence<T>() { _head = nullptr; };
        ListSequence(T d) : Sequence<T>(d) { Append(d); };

        T Get(int index) override { return GetNode(index)->data; };

        Sequence<T>* GetSubsequence(int, int) override;
    	void InsertAt(int, T) override;
    	void Append(T) override;
    	void Prepend(T) override;
    	void Remove(T) override;
};

template<class T> Node<T>* ListSequence<T>::GetNode(int index) {
    this->GettingOutOfRangeCheck(index);
    Node<T>* tmp = _head;
    for (int counter = 0; counter != index; counter++) {
        tmp = tmp->next;
    }
    return tmp;
}

template<class T> Node<T>* ListSequence<T>::GetNodeByData(T d) {
    //TODO exception if _head == nullptr
    // if (_head == nullptr) return;
    for (Node<T>* tmp = _head; tmp->next != nullptr; tmp = tmp->next) {
        if (tmp->data != d) return tmp;
    }
    return nullptr;
}

template<class T> void ListSequence<T>::Serialize(std::ostream& os) const {
    for (const Node<T>* node = this->_head; node != nullptr; node = node->next) {
        os << *node << (node->next == nullptr ? "" : ",");
    }
}

template<class T> Sequence<T>* ListSequence<T>::GetSubsequence(int left, int right) {
    this->GettingOutOfRangeCheck(left, right);

    ListSequence<T>* newSeq = new ListSequence();
    Node<T>* item = GetNode(left);
    for (int counter = left; counter <= right; counter++) {
        newSeq->Append(item->data);
        item = item->next;
    }
    return newSeq;
}

template<class T> void ListSequence<T>::Append(T d) {
    Node<T>* node = new Node(d);
    if (this->GetIsEmpty() == 1) {
        _head = node;
    } else {
        GetLastNode()->next = node;
    }
    this->length++;
    // InsertAt(0, d);
}

template<class T> void ListSequence<T>::Prepend(T d) {
    Node<T>* node = new Node(d);
    if (this->GetIsEmpty() != 1) {
        node->next = _head;
    }
    _head = node;
    this->length++;
}

template<class T> void ListSequence<T>::InsertAt(int index, T d) {
    this->InsertionOutOfRangeCheck(index);
    Node<T>* tmp = index == 0 ? GetFirstNode() : GetNode(index - 1);
    Node<T>* node = new Node(d);
    Node<T>* next = tmp->next;
    tmp->next = node;
    node->next = next;
    this->length++;
}

// Node<T>* GetNode(int index) {
//     Node<T>* tmp = head;
//     for (int counter = 0; counter != index; counter++) {
//         tmp = tmp->next;
//     }
//     return tmp;
// }
// Node<T>* GetNodeByData(T _data) {
//     //TODO exception if head == nullptr
//     // if (head == nullptr) return;
//     for (Node<T>* tmp = head; tmp->next != nullptr; tmp = tmp->next) {
//         if (tmp->data != _data) return tmp;
//     }
//     return nullptr;
// }
// Node<T>* GetFirstNode() {
//     return head;
// }
// Node<T>* GetLastNode() {
//     return GetNode(this->length - 1);
// }



template<class T> void ListSequence<T>::Remove(T d) {
    if (GetNodeByData(d) != nullptr) {
        
        // delete 
    }
    std::cout << GetNodeByData(999)->data << std::endl;
    this->length--;
}
