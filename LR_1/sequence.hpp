#pragma once
#include <functional>


// void output(const function<string(int)>& f) {
//     cout << f(0) << endl;
// }

// string text = "text";
// output([&](int i){ return text; });


template<class T> class Sequence {
    protected:
        int length;

        virtual T* GetPointer(int) = 0;
        
        Sequence(T) : length(0) {};

        Sequence(T d[], int size) : length(0) {};

        Sequence(Sequence&) : length(0) {};
        
        Sequence() : length(0) {};

        void InsertionOutOfRangeCheck(int index) {
            if (index < 0 || index > length) {
                throw std::out_of_range("Out of range!");
            }
        }

        void GettingOutOfRangeCheck(int index) {
            if (index < 0 || index >= length) {
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

        void Swap (T* first, T* second) {
            T tmp = *first;
            *first = *second;
            *second = tmp;
        }

        int Partition (int low, int high, const std::function<bool(int, int)>& comp) {
            int pivot = (*this)[high];
            int i = (low - 1);
        
            for (int j = low; j <= high - 1; j++) {
                auto cur = GetPointer(j);
                if (comp(*cur, pivot)) {
                    i++;
                    Swap(GetPointer(i), cur);  
                }
            }
            Swap(GetPointer(i + 1), GetPointer(high));
            return (i + 1);
        }

        void QuickSort(int low, int high, const std::function<bool(int, int)>& comp) {  
            if (low < high) {
                int pi = Partition(low, high, comp);  
                QuickSort(low, pi - 1, comp);
                QuickSort(pi + 1, high, comp);
            }  
        } 

    public:
	    int GetLength() { return length; };
        
        bool GetIsEmpty() { return length == 0 ? true : false; };
        
        T GetFirst() { return Get(0); };
        
        T GetLast() { return Get(length - 1); };
        
        T operator[](int index) { return Get(index); };
    	
        void Append(T item) { InsertAt(length, item); };
    	
        void Prepend(T item) { InsertAt(0, item); };
        
        float QSort(const std::function<bool(int, int)>& comp) {
            auto start = clock();
            QuickSort(0, length - 1, comp);
            auto end = clock();
            return (float)(end - start) / CLOCKS_PER_SEC;
        }

        float ShellSort (const std::function<bool(int, int)>& comp) {
            auto start = clock();
            int step, i, j, tmp;
            for (step = length / 2; step > 0; step /= 2) {
                for (i = step; i < length; i++) {
                    for (j = i - step; j >= 0; j -= step) {
                        auto fst = GetPointer(j);                        
                        auto snd = GetPointer(j + step);
                        if (!comp(*fst, *snd)) {
                            Swap(fst, snd);
                       }
                    }
                }
            }
            auto end = clock();
            return (float)(end - start) / CLOCKS_PER_SEC;
        }

        virtual void Serialize (std::ostream&) const = 0;
        virtual T Get(int) = 0;
        virtual Sequence<T>* GetSubsequence(int, int) = 0;
    	virtual void InsertAt(int, T) = 0;
    	virtual void Remove(T) = 0;

        friend std::ostream& operator<<(std::ostream& os, const Sequence<T>& seq) {
            seq.Serialize(os);
            return os;
        }
};
