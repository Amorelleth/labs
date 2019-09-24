#pragma once
#include <iostream>
#include "sequence.hpp"

template<class T>
class ArraySequence : public Sequence<T> {
    private:
        T* items;

    protected:
        virtual void Serialize(std::ostream& os) const override {
            for (int i = 0; i < this->length; i++) {
                os << items[i] << (i == this->length - 1 ? "" : ",");
            }
        }

    public:
        ArraySequence() : Sequence<T>() {};
        ArraySequence(T d) : Sequence<T>() { Append(d); };
        ~ArraySequence() { delete items; }

        ArraySequence<T>* GetSubsequence(int left, int right) override {
            this->GettingOutOfRangeCheck(left, right);
            auto newSeq = new ArraySequence<T>;

            for (int i = left; i <= right; i++) {
                newSeq->Append(items[i]);
            }

            return newSeq;
        }

        void InsertAt(int index, T item) override {
            this->InsertionOutOfRangeCheck(index);
            items = this->GetIsEmpty() ? new T[1] : (T*)realloc(items, (this->length + 1)*sizeof(T));
            
            for (int j = this->length - 1; j >= index; j--) {
                items[j + 1] = items[j];
            }
            
            this->length++;
            items[index] = item;
        }

        void Remove(T item) override {
            for (int i = 0; i < this->length; i++) {
                if (items[i] == item) {
                    for (int j = i; j < this->length; j++) {
                        items[j] = items[j + 1];
                    }
                    this->length--;
                    items = (T*)realloc(items, this->length * sizeof(T));
                    break;
                }
            }
        }

        T Get(int index) override {
            this->GettingOutOfRangeCheck(index);
            return items[index];
        }
};
