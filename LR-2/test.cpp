#include <iostream>
#include <array>
#include "set.hpp"
#include "types.hpp"

// - map, where
// + объединение
// + пересечение
// + вычитание
// + проверка на включение подмножества
// + проверка на вхождение элемента
// + сравнение (равенство) двух

template <class T>
void clear_initial_array(T arr[], int size) {
    for (int i = 0; i < size; i++) {
        delete arr[i];
    }
}

bool test_insert() {
    Number* initial[5] = { new Float(4.5), new Int(4), new Float(-999), new Complex(4, -6), new Int(4) };
    Number* expected[4] = { new Float(-999), new Complex(4, -6), new Int(4), new Float(4.5) };
    Set<Number*> set(initial, 5);
    Set<Number*> expected_set(expected, 4);
    
    if (expected_set != set) {
        std::cout << "FAIL test-insert\n";
        return false;
    }

    std::cout << "PASS test-insert\n";
    return true;
}

bool test_clear() {
    Number* init[2] = { new Int(54), new Float(-54) };
    Set<Number*> set(init, 2);
    set.clear();

    std::cout << set;

    if (set.size != 0 || set.get_head() != nullptr) {
        std::cout << "FAIL test-clear\n";
        return false;
    }

    std::cout << "PASS test-clear\n";
    return true;
}

bool test_merge() {
    Number* first[3] = { new Float(4.5), new Int(4), new Complex(0, 0) };
    Number* second[3] = { new Float(4.5), new Int(1), new Float(3.3) };
    Number* expected[5] = { new Complex(0, 0), new Int(1), new Float(3.3), new Int(4), new Float(4.5) };
    Set<Number*> first_set(first, 3);
    Set<Number*> second_set(second, 3);
    Set<Number*> expected_set(expected, 5);
    
    const Set<Number*>* sum = first_set + second_set;
    if (*sum != expected_set) {
        std::cout << "FAIL test-merge\n";
        return false;
    }

    std::cout << "PASS test-merge\n";
    return true;
}

bool test_intersection() {
    Number* first[3] = { new Float(4.5), new Int(4), new Complex(0, 0) };
    Number* second[3] = { new Float(4.5), new Int(1), new Float(3.3) };
    Number* expected[1] = { new Float(4.5) };
    Set<Number*> first_set(first, 3);
    Set<Number*> second_set(second, 3);
    Set<Number*> expected_set(expected, 1);
    
    const Set<Number*>* multuplication = first_set * second_set;
    if (*multuplication != expected_set) {
        std::cout << "FAIL test-intersection\n";
        return false;
    }

    std::cout << "PASS test-intersection\n";
    return true;
}

bool test_subtract() {
    Number* first[3] = { new Float(4.5), new Int(4), new Complex(0, 0) };
    Number* second[3] = { new Float(4.5), new Int(1), new Float(3.3) };
    Number* expected[2] = { new Int(4), new Complex(0, 0) };
    Set<Number*> first_set(first, 3);
    Set<Number*> second_set(second, 3);
    Set<Number*> expected_set(expected, 2);
    
    const Set<Number*>* sub = first_set - second_set;
    if (*sub != expected_set) {
        std::cout << "FAIL test-subtract\n";
        return false;
    }

    std::cout << "PASS test-subtract\n";
    return true;
}

bool test_includes() {
    Number* arr[3] = { new Float(4.5), new Int(4), new Complex(0, 0) };
    Set<Number*> set(arr, 3);

    if (set.includes(new Float(3.3)) == true || set.includes(new Complex(0, 0)) == false) {
        std::cout << "FAIL test-includes\n";
        return false;
    }

    std::cout << "PASS test-includes\n";
    return true;
}

bool test_includes_set() {
    Number* first[4] = { new Float(4.5), new Int(4), new Complex(0, 0), new Int(1) };
    Number* second[2] = { new Int(1), new Complex(0, 0) };
    Set<Number*> first_set(first, 4);
    Set<Number*> second_set(second, 2);
    
    if (first_set.includes_set(second_set) == false || second_set.includes_set(first_set) == true) {
        std::cout << "FAIL test-includes-set\n";
        return false;
    }

    std::cout << "PASS test-includes-set\n";
    return true;
}

bool test_equality() {
    Number* first[2] = { new Int(1), new Complex(0, 0) };
    Number* second[2] = { new Int(1), new Complex(0, 0) };
    Set<Number*> first_set(first, 2);
    Set<Number*> second_set(second, 2);
    
    if (first_set != second_set) {
        std::cout << "FAIL test-equality\n";
        return false;
    }

    std::cout << "PASS test-equality\n";
    return true;
}

bool test_deletion() {
    const int size = 5;
    bool res = true;
    Number* arr[size] = { new Int(1), new Int(2), new Int(3), new Int(4), new Int(5) };
    Number* delete_last[size - 1] = { new Int(1), new Int(2), new Int(3), new Int(4) };
    Number* delete_first[size - 2] = { new Int(2), new Int(3), new Int(4) };
    Number* delete_middle[size - 3] = { new Int(2), new Int(4) };

    Set<Number*> set(arr, size);
    Set<Number*> last_deleted(delete_last, size - 1);
    Set<Number*> first_deleted(delete_first, size - 2);
    Set<Number*> middle_deleted(delete_middle, size - 3);
    
    auto deleted = set.delete_elem(new Int(5));
    if (set != last_deleted || *deleted != Int(5) || set.size != size - 1) {
        std::cout << "FAIL test-delete-last-elem\n";
        res = false;
    }
    deleted = set.delete_elem(new Int(1));
    if (set != first_deleted || *deleted != Int(1) || set.size != size - 2) {
        std::cout << "FAIL test-delete-first-elem\n";
        res = false;
    }
    deleted = set.delete_elem(new Int(3));
    if (set != middle_deleted || *deleted != Int(3) || set.size != size - 3) {
        std::cout << "FAIL test-delete-middle-elem\n";
        res = false;
    }

    if (res == true) {
        std::cout << "PASS test-deletion\n";
    }

    return res;
}

bool test_similar_objects() {

}

bool test_equality() {

}

bool test_map() {

}

bool test_where() {
    
}

int main() {
    // Number* arr[5] = { new Complex(3, 4), new Float(54), new Complex(9, 0) };
    // Set<int*> set(arr, 3);
    // std::cout << set;
    test_clear();
    test_insert();
    test_merge();
    test_intersection();
    test_subtract();
    test_includes();
    test_includes_set();
    test_equality();
    test_deletion();



    // Set<Number*> set(arr, 3);

    // Float c(5);
    // Complex b(6, 5);

    // std::cout << c << " " << *set.get_head()->data << " " << (c == *set.get_head()->data);
}
