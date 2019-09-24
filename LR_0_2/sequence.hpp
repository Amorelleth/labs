#pragma once

template<class T> class Sequence {
    protected:
        int length;
        Sequence(T) : length(1) {};
        Sequence() : length(0) {};
        void InsertionOutOfRangeCheck(int index) {
            if (index < 0 || index > this->length) {
                throw std::out_of_range("Out of range!");
            }
        }
        void GettingOutOfRangeCheck(int index) {
            if (index < 0 || index >= this->length) {
                throw std::out_of_range("Out of range!");
            }
        }
        void GettingOutOfRangeCheck(int left, int right) {
            GettingOutOfRangeCheck(left);
            GettingOutOfRangeCheck(right);
            if (left > right) {
                throw std::out_of_range("Out of range!");
            }
        }
    public:
	    int GetLength() {
            return length;
        };
        int GetIsEmpty() {
            return length == 0 ? true : false;
        };
        T GetFirst() { return Get(0); };
        T GetLast() { return Get(length - 1); };
    	void Append(T item) { InsertAt(length, item); };
    	void Prepend(T item) { InsertAt(0, item); };

        friend std::ostream& operator<<(std::ostream& os, const Sequence<T>& seq) {
            seq.Serialize(os);
            return os;
        }
        T operator[](int index) { return Get(index); };

        virtual void Serialize (std::ostream&) const = 0;
        virtual T Get(int) = 0;
        virtual Sequence<T>* GetSubsequence(int, int) = 0;
    	virtual void InsertAt(int, T) = 0;
    	virtual void Remove(T) = 0;
};
