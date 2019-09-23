#include <iostream>
#include "node.hpp"
#include "sequence.hpp"
#include "list-sequence.hpp"
#include "array-sequence.hpp"

// Написать, по крайней мере, один тест, реализующий следующий сценарий:
// Создать пустую последовательность (TElement = int).
// Проверить, что длина = 0
// Добавить (Append) элемент «23».
// Проверить, что длина = 1
// Проверить, что GetFisrt возвращает «23»
// Проверить, что GetLast возвращает «23»
// Проверить, что Get(0) возвращает «23», а Get(-1) и Get(1) – выбрасывают исключение.

// Добавить (Append) элемент «43»
// Проверить, что длина = 2
// Проверить, что GetFisrt возвращает «23»
// Проверить, что GetLast возвращает «43»
// Проверить, что Get(0) возвращает «23», Get(1) – «43», а Get(-1) и Get(2) – выбрасывают исключение.
// Добавить (Prepend) элемент «53»
// Проверить, что длина = 3
// Проверить, что GetFisrt возвращает «53»
// Проверить, что GetLast возвращает «43»
// Проверить, что Get(0) возвращает «53», Get(1) – «23», а Get(-1) и Get(3) – выбрасывают исключение.
// Проверить, что GetSubsequence(1,1) возвращает последовательность, у которой:
// длина =1
// первый и последний элемент – 23


// g++ -std=c++17 -g main.cpp -o main && ./main

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

int main () {
    // ListSequence<int> seq;
    // seq.Append(0);
    // seq.Append(1);
    // seq.Append(2);
    // seq.Append(3);
    // seq.Prepend(-1);
    // seq.InsertAt(0, 999);
    // seq.InsertAt(2, -999);
    // std::cout << seq << "\nlen: " << seq.GetLength() << "\n\n" << *seq.GetSubsequence(2, 4) << "\nlen: " << seq.GetSubsequence(2, 4)->GetLength() << "\n" <<std::endl;
    // seq.Remove(999);

    ArraySequence<int> seq;
    // if (seq.GetLength() != 0) {
    //     // return false;
    //     std::cout << "1";
    // }
    // seq.Append(23);
    // if (seq.GetLength() != 1) {
    //     // return false;
    //     std::cout << "1";
    // }
    // if (seq.GetFirst() != 23) {
    //     // return false;
    //     std::cout << "1";
    // }
    // if (seq.GetLast() != 23) {
    //     // return false;
    //     std::cout << "1";
    // }
    // if (seq.Get(0) != 23) {
    //     // return false;
    //     std::cout << "1";
    // }
    // try {
    //     int a = seq.Get(1);
    //     std::cout << "1" << a << std::endl;
    // } catch(std::out_of_range exc) {
    //     // std::cout << exc.what() << std::endl;
    // }
    // try {
    //     int a = seq.Get(-1);
    //     std::cout << "1" << a << std::endl;
    // } catch(std::out_of_range exc) {
    //     // std::cout << exc.what() << std::endl;
    // }
    // seq.Append(43);
    // if (seq.GetLength() != 2) {
    //     // return false;
    //     std::cout << "1" << std::endl;
    // }
    // if (seq.GetFirst() != 23) {
    //     // return false;
    //     std::cout << "1" << std::endl;
    // }

// Добавить (Append) элемент «43»
// Проверить, что длина = 2
// Проверить, что GetFisrt возвращает «23»
// Проверить, что GetLast возвращает «43»
// Проверить, что Get(0) возвращает «23», Get(1) – «43», а Get(-1) и Get(2) – выбрасывают исключение.
// Добавить (Prepend) элемент «53»
// Проверить, что длина = 3
// Проверить, что GetFisrt возвращает «53»
// Проверить, что GetLast возвращает «43»
// Проверить, что Get(0) возвращает «53», Get(1) – «23», а Get(-1) и Get(3) – выбрасывают исключение.
// Проверить, что GetSubsequence(1,1) возвращает последовательность, у которой:
// длина =1
// первый и последний элемент – 23

    seq.Append(1);
    seq.Append(2);
    // seq.Append(3);
    // seq.Append(4);
    // seq.Append(5);
    // seq.InsertAt(1, 999);
    // std::cout << seq[0] << " " << seq[1];
    std::cout << seq;


    return 0;
}
