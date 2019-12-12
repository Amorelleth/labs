#pragma once
#include <iostream>
#include "node.hpp"
#include "sequence.hpp"

template<class T> class ListSequence : public Sequence<T> {
    private:
        Node<T>* _head;

        Node<T>* GetNode(int index) {
            this->GettingOutOfRangeCheck(index);
            auto tmp = _head;
            for (int counter = 0; counter != index; counter++) {
                tmp = tmp->next;
            }
            return tmp;
        }

        void RemoveNode(Node<T>* node) {
            auto tmp = node->next->next;
            node->next->next = nullptr;
            delete node->next;
            node->next = tmp;
            this->length--;
        }

        void RemoveHead() {
            _head->next = nullptr;
            delete _head->next;
            _head = nullptr;
            delete _head;
            this->length--;
        }

        T* GetPointer(int index) override {
            this->GettingOutOfRangeCheck(index);
            return &GetNode(index)->data;
        };

    protected:
        void Serialize(std::ostream& os) const override {
            auto node = _head;
            for (int i = 0; i < this->length; i++) {
                os << *node << (i == this->length - 1 ? "" : ",");
                if (node->next != nullptr) node = node -> next;
            }
        }

    public:
        ListSequence() : Sequence<T>() { _head = nullptr; };
        ListSequence(ListSequence& seq) : Sequence<T>(seq) {
            auto newSeq = new ListSequence<T>;
            auto node = seq._head;
            for (int i = 0; i < seq.length; i++) {
                this->Append(node->data);
                if (node->next != nullptr) node = node->next;
            }
        };
        ListSequence(T d) : Sequence<T>(d) { this->Append(d); };
        ListSequence(T d[], int size) : Sequence<T>(d, size) { 
            for (int i = 0; i < size; i++) this->Append(d[i]);
        };
        ~ListSequence() {
            auto current = _head;
            if (current == nullptr) return;
            while (current->next != nullptr) RemoveNode(current);
            RemoveHead();
        }

        T Get(int index) override { return GetNode(index)->data; };

        Sequence<T>* GetSubsequence(int left, int right) override {
            this->GettingOutOfRangeCheck(left, right);
            auto newSeq = new ListSequence();
            auto item = GetNode(left);

            for (int counter = left; counter <= right; counter++) {
                newSeq->Append(item->data);
                item = item->next;
            }

            return newSeq;
        }

        void InsertAt(int index, T d) override {
            this->InsertionOutOfRangeCheck(index);
            auto node = new Node<T>(d, nullptr);

            if (index == 0) {
                node->next = _head;
                _head = node;
            } else {
                auto tmp = GetNode(index - 1);
                node->next = tmp->next;
                tmp->next = node;
            }

            this->length++;
        }

        void Remove(T data) override {
            if (!this->GetIsEmpty()) {
                if (_head->data == data) {
                    if (_head->next == nullptr) {
                        RemoveHead();
                    } else {
                        auto tmp = _head->next;
                        _head->next = nullptr;
                        delete _head->next;
                        _head = tmp;
                        this->length--;
                    }
                } else {
                    for (auto current = _head; current->next != nullptr; current = current->next) {
                        if (current->next->data == data) {
                            RemoveNode(current);
                            break;
                        }
                    }
                }
            }
        }
};
