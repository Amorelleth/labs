#include <iostream>
#include <exception>
#include <string>
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
// exit 
// get 4
// getfirst
// getlast
// append 6
// prepend 8
// remove 999
// getsub 1 3
// insertAt 0 999

void CheckInput() {
    if (std::cin.fail()) {
        std::cin.clear();
        throw std::invalid_argument("Input must be integer!");
    }
}

void CheckSeq(Sequence<int>* seq) {
    if (seq == nullptr) throw std::invalid_argument("Create your sequence first!");
}

int main () {
    std::string action;
    std::string object;
    
    int number;

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
                } else throw std::invalid_argument("Invalid Command!");
            } else if (action == "print") {
                std::cout << *seq << std::endl;
            } else if (action == "append") {
                CheckSeq(seq);
                std::cin >> number;
                CheckInput();
                seq->Append(number);
            } else if (action == "prepend") {
                CheckSeq(seq);
                std::cin >> number;
                CheckInput();
                seq->Prepend(number);
            } else if (action == "remove") {
                CheckSeq(seq);
                std::cin >> number;
                CheckInput();
                seq->Remove(number);
            } else if (action == "get") {
                CheckSeq(seq);
                std::cin >> number;
                CheckInput();
                std::cout << seq->Get(number) << std::endl;
            } else if (action == "getSub") {
                CheckSeq(seq);
                int left, right;
                std::cin >> left >> right;
                std::cout << seq->GetSubsequence(left, right) << std::endl;
            } else if (action == "insertAt") {
                CheckSeq(seq);
                int idx;
                std::cin >> idx >> number;
                CheckInput();
                seq->InsertAt(idx, number);
            } else if (action == "getFirst") {
                CheckSeq(seq);
                std::cout << seq->GetFirst() << std::endl;
            } else if (action == "getLast") {
                CheckSeq(seq);
                std::cout << seq->GetLast() << std::endl;
            } else throw std::invalid_argument("Invalid Command!");
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
