#include <iostream>
#include "array-sequence.hpp"
#include "list-sequence.hpp"
#include "out-of-range.hpp"

bool MainTest() {
    ArraySequence<int> seq;
    if (seq.GetLength() != 0) {
        return false;
    }
    seq.Append(23);
    if (seq.GetLength() != 1) {
        return false;
    }
    if (seq.GetFirst() != 23) {
        return false;
    }
    if (seq.GetLast() != 23) {
        return false;
    }

}


int main() {
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


    return 0;
}
