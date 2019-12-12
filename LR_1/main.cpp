#include <iostream>
#include <exception>
#include <string>
#include <ctime>
#include <functional>
#include "fill-random.hpp"
#include "node.hpp"
#include "sequence.hpp"
#include "list-sequence.hpp"
#include "array-sequence.hpp"


// Length	        Длина последовательности (количество элементов)
// IsEmpty	        Признак того, является ли последовательность пустой
// Get	            Получение элемента по индексу.
// GetFirst         Получить первый элемент последовательности
// GetLast          Получить последний элемент последовательности
// GetSubsequence	Получить подпоследовательность: начиная с элемента с индексом startIndex и заканчивая элементом с индексом endIndex
// Append	        Добавить элемент в конец последовательности
// Prepend	        Добавить элемент в начало последовательности
// InsertAt	        Вставить элемент в позицию index (существующие элементы сдвигаются вперед на 1).
// Remove	        Удаляет элемент из последовательности. Если элемента не было, ничего не происходит.

// example:

// create array (list)
// create random array(list) 100
// exit 
// get 4
// getfirst
// getlast
// append 6
// prepend 8
// remove 999
// getsub 1 3
// insertAt 0 999
// testSorts
// qsort
// shellSort

void CheckInput() {
    if (std::cin.fail()) {
        std::cin.clear();
        throw std::invalid_argument("Input must be integer!");
    }
}

bool InOrder(int a, int b) { return a < b; };

void testSorts(Sequence<int>* seq) {
    Sequence<int>* testQSortSeq = nullptr;
    Sequence<int>* testShellSeq = nullptr;

    if (ListSequence<int>* l = dynamic_cast<ListSequence<int>*>(seq)) {
        testQSortSeq = new ListSequence<int>(*l);
        testShellSeq = new ListSequence<int>(*l);
    } else if (ArraySequence<int>* a = dynamic_cast<ArraySequence<int>*>(seq)) {
        testShellSeq = new ArraySequence<int>(*a);
        testQSortSeq = new ArraySequence<int>(*a);
    }
    std::cout << "qsort time: " << testQSortSeq->QSort(InOrder) << std::endl;
    std::cout << "shell time: " << testShellSeq->ShellSort(InOrder) << std::endl;
}

void CheckSeq(Sequence<int>* seq) {
    if (seq == nullptr) throw std::invalid_argument("Create your sequence first!");
}

void ResolveAction(Sequence<int>* seq, std::string action) {
    int number;

    CheckSeq(seq);
    if (action == "print") {
        std::cout << *seq << std::endl;
    } else if (action == "append") {
        std::cin >> number;
        CheckInput();
        seq->Append(number);
    } else if (action == "prepend") {
        std::cin >> number;
        CheckInput();
        seq->Prepend(number);
    } else if (action == "remove") {
        std::cin >> number;
        CheckInput();
        seq->Remove(number);
    } else if (action == "get") {
        std::cin >> number;
        CheckInput();
        std::cout << seq->Get(number) << std::endl;
    } else if (action == "getSub") {
        int left, right;
        std::cin >> left >> right;
        std::cout << seq->GetSubsequence(left, right) << std::endl;
    } else if (action == "insertAt") {
        int idx;
        std::cin >> idx >> number;
        CheckInput();
        seq->InsertAt(idx, number);
    } else if (action == "getFirst") {
        std::cout << seq->GetFirst() << std::endl;
    } else if (action == "getLast") {
        std::cout << seq->GetLast() << std::endl;
    } else if (action == "testSorts") {
        testSorts(seq);
    } else if (action == "qsort") {
        seq->QSort(InOrder);
    } else if (action == "shellSort") {
        seq->ShellSort(InOrder);
    } else throw std::invalid_argument("Invalid Command!");
}

int main () {
    srand(time(nullptr));
    std::string action;
    std::string object;
    Sequence<int>* seq = nullptr;

    while(true) {
        try {
            std::cin >> action;
            if (action == "exit") {
                return 0;
            } else if (action == "create") {
                std::cin >> object;
                if (object == "array") {
                    seq = new ArraySequence<int>;
                } else if (object == "list") {
                    seq = new ListSequence<int>;
                } else if (object == "random") {
                    int number;
                    std::cin >> object;
                    std::cin >> number;
                    CheckInput();
                    int arr[number];
                    FillWithRandom(arr, number);
                    if (object == "array") {
                        seq = new ArraySequence<int>(arr, number);
                    } else if (object == "list") {
                        seq = new ListSequence<int>(arr, number);
                    } else throw std::invalid_argument("Invalid Command!");
                } else throw std::invalid_argument("Invalid Command!");
            } else {
                ResolveAction(seq, action);
            }
        } catch (std::invalid_argument err) {
            std::cout << err.what() << std::endl;
            std::string str;
            std::getline(std::cin, str);
        } catch (std::out_of_range err) {
            std::cout << err.what() << std::endl;
            std::string str;
            std::getline(std::cin, str);
        }
    }
    
    return 0;
}
