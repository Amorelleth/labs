#include <any>
#include <iostream>
#include <vector>
#include "set.hpp"
#include "any.hpp"
#include "types.hpp"
#include "node.hpp"
#include "complex.hpp"



// - map, where
// + объединение
// + пересечение
// + вычитание
// + проверка на включение подмножества
// + проверка на вхождение элемента
// + сравнение (равенство) двух

int main() {
    Set<Any> set;

    Int some1 = Int(2);
    Float some2 = Float(2);
    Float some3 = Float(5);
    Float some31 = Float(5);
    Float some32 = Float(5);
    Float some33 = Float(5);
    Float some4 = Float(-667);
    Float some5 = Float(9.0);

    set.insert(some1);
    set.insert(some2);
    set.insert(some3);
    set.insert(some31);
    set.insert(some32);
    set.insert(some33);
    set.insert(some4);
    set.insert(some5);

    // вроде работает 
    //
    // set.delete_elem(some3);
    // set.clear();

    // Any *some = new Float(6);
    // Float* a = dynamic_cast<Float*>(some);
    // Node<Any*>* node = new Node(some);

    // if (Float* a = dynamic_cast<Float*>(*node->data)) {
    //     std::cout << "downcast from b1 to d successful\n";
    //     // d->name(); // safe to call
    // }

    Int any = Int(5);
    auto s = set.get_head()->data;
    std::cout << *set.get_head()->data;

    // any_set.insert(any_int_1);
    // Any* any_int_2_ptr = &any_int_2;
    // Any* any_int_1_ptr = &any_int_1;

    // Float any_float_1 = Float(5);

    // std::cout << set;
    // std::cout << (any_int_2 == any_int_1);
    // std::cout << any_int_1_ptr->equal(any_int_2_ptr);

    // Set<int> set;
    // set.insert(4);
    // set.insert(5);
    // set.insert(6);
    // set.insert(7);
    // set.insert(8);
    // std::cout << set;


    // if (Float* a = dynamic_cast<Float*>(some_)) {
    //     std::cout << "downcast to float successful\n";
    // }
    // if (Int* a = dynamic_cast<Int*>(some_)) {
    //     std::cout << "downcast to int successful\n";
    // }
    // if (Complex* a = dynamic_cast<Complex*>(some_)) {
    //     std::cout << "downcast to complex successful\n";
    // }

    

    // std::cout << (some == some_);

    return 0;

}
