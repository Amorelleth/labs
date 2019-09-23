#pragma once
#include <iostream>
#include "sequence.hpp"
#include "node.hpp"

template<class T>
class ArraySequence : public Sequence<T> {
    private:
        T* items;
        void Scale() {
            this->length++;
            if (this->GetIsEmpty()) {
                items = new T[1];
            } else {
                items = (T*)realloc(items, this->length * sizeof(T));
            }
        }
    protected:
        virtual void Serialize(std::ostream& os) const override {
            for (int i = 0; i < this->length; i++) {
                os << items[i] << (i == this->length - 1 ? "" : ",");
            }
        }

    public:
        ArraySequence() : Sequence<T>() {};
        ArraySequence(T d) : Sequence<T>() { Append(d); };

        ArraySequence<T>* GetSubsequence(int left, int right) override {
            this->GettingOutOfRangeCheck(left, right);
            auto *newSeq = new ArraySequence<T>;

            for (int i = left; left <= right; i++) {
                newSeq->Append(items[i]);
            }

            return newSeq;
        }

        void InsertAt(int index, T item) override {
            // this->InsertionOutOfRangeCheck(index);
            if (index < 0 || index >= this->length) {
                throw std::out_of_range("Invalid parameter");
            }

            this->length++;

            items = (T*) realloc(items, this->length * sizeof(T));

            for (int j = this->length - 2; j >= index; j--) {
                items[j + 1] = items[j];
            }

            items[index] = item;
        }

        void Append (T item) override {
            if (this->GetIsEmpty()) {
                items = new T[1];
                items[0] = item;
            } else {
                items = (T*)realloc(items, this->length*sizeof(T));
                items[this->length - 1] = item;
                // std::cout << *this << std::endl;
            }
            // std::cout << *this << std::endl;
            this->length++;
            std::cout << "---" << items[0] << items[2] << std::endl;
        }

        void Prepend(T item) override {
            Scale();
            items[0] = item;
        }

        void Remove(T item) override {
            for (int i = 0; i < this->length - 1; i++) {
                if (items[i] == item) {
                    for (int j = i; j < this->length - 1; j++) {
                        items[j] = items[j + 1];
                    }
                    this->length--;
                    items = (T *) realloc(items, this->length * sizeof(T));
                    break;
                }
            }
        }

        T Get(int index) override {
            this->GettingOutOfRangeCheck(index);
            return items[index];
        }
};
