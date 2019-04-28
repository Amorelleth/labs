#include <any>
#include <iostream>
#include <vector>
#include "set.hpp"
#include "types.hpp"
#include "node.hpp"
#include "complex.hpp"
#include "number.hpp"

// - map, where
// + объединение
// + пересечение
// + вычитание
// + проверка на включение подмножества
// + проверка на вхождение элемента
// + сравнение (равенство) двух множеств

int main() {
    Set<Number*> set;

    set.insert(new Float(5));
    set.insert(new Int(5));
    set.insert(new Complex(4, 5));
    set.insert(new Int(20));
    set.insert(new Float(5));
    set.insert(new Float(5));
    set.insert(new Float(999));
    set.insert(new Float(-5454));


    Set<Number*> set_;

    set_.insert(new Float(5));
    set_.insert(new Float(999));
    set_.insert(new Float(99));
    set_.insert(new Float(33));
    set_.insert(new Float(34));

    auto set__ = set.intersection(set_);

    std::cout << set;
    std::cout << set.size << "\n";

    std::cout << set_;
    std::cout << set_.size << "\n";

    std::cout << *set__;
    std::cout << set__->size;


    return 0;
}
