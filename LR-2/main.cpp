#include <any>
#include <iostream>
#include <vector>
#include "set.hpp"
#include "any.hpp"
// #include "int.hpp"

// - map, where
// + объединение
// + пересечение
// + вычитание
// + проверка на включение подмножества
// + проверка на вхождение элемента
// + сравнение (равенство) двух

int main() {
    Set<Any*> set;

    Int* some1 = new Int(2);
    Float* some2 = new Float(2);
    Float* some3 = new Float(5);
    Float* some31 = new Float(5);
    Float* some32 = new Float(5);
    Float* some33 = new Float(5);
    Float* some4 = new Float(-667);
    Float* some5 = new Float(9.0);

    set.insert(some1);
    set.insert(some2);
    set.insert(some3);
    set.insert(some31);
    set.insert(some32);
    set.insert(some33);
    set.insert(some4);
    // set.insert(some5);

    // вроде работает 
    //
    // set.delete_elem(some3);
    // set.clear();

    std::cout << set.includes(some3) << " " << set.includes(some5) << "\n";

    // any_set.insert(any_int_1);
    // Any* any_int_2_ptr = &any_int_2;
    // Any* any_int_1_ptr = &any_int_1;

    // Float any_float_1 = Float(5);

    std::cout << set;
    // std::cout << (any_int_2 == any_int_1);
    // std::cout << any_int_1_ptr->equal(any_int_2_ptr);

    // Set<int> set;
    // set.insert(4);
    // set.insert(5);
    // set.insert(6);
    // set.insert(7);
    // set.insert(8);
    // std::cout << set;

    return 0;

}
