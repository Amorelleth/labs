#include <iostream>
#include "set.hpp"
#include "types.hpp"

#define TESTS 11

template <class T>
void clear_array(T arr[], int size) {
    for (int i = 0; i < size; i++) {
        delete arr[i];
    }
}

bool compare_results(Number* expected[], int size, Set<Number*>* set, std::string test_name) {
    Set<Number*> expected_set(expected, size);
    auto tmp = set->get_head();
    int i = 0;
    bool res = true;
    while (tmp != nullptr) {
        if (*tmp->data != *expected[i]) {
            res = false;
        }
        tmp = tmp->next;
        i++;
    }

    if (res == true) {
        std::cout << "PASS " << test_name << "\n";
    } else {
        std::cout << "FAIL " << test_name << "\n";
        std::cout << "---EXPECTED " << expected_set;
        std::cout << "---GOT " << *set;
    }

    clear_array(expected, size);
    return res;
}

bool test_insert() {
    Number* expected[4] = { new Int(4), new Float(4.5), new Complex(4, -6), new Float(-999) };
    Set<Number*> set;
    set.insert(new Float(4.5));
    set.insert(new Int(4));
    set.insert(new Float(-999));
    set.insert(new Complex(4, -6));
    set.insert(new Int(4));
    return compare_results(expected, 4, &set, std::string("test-insert"));
}

bool test_clear() {
    Number* initial[2] = { new Int(54), new Float(-54) };
    Set<Number*> set(initial, 2);
    set.clear();

    if (set.size != 0 || set.get_head() != nullptr) {
        std::cout << "FAIL test-clear\n";
        return false;
    }

    clear_array(initial, 2);
    std::cout << "PASS test-clear\n";
    return true;
}

bool test_merge() {
    Number* first[3] = { new Float(4.5), new Int(4), new Complex(0, 0) };
    Number* second[3] = { new Float(4.5), new Int(1), new Float(3.3) };
    Number* expected[5] = { new Complex(0, 0), new Int(1), new Float(3.3), new Int(4), new Float(4.5) };
    Set<Number*>* set = Set<Number*>(first, 3) + Set<Number*>(second, 3);
    bool res = compare_results(expected, 5, set, std::string("test-merge"));
    clear_array(first, 3);
    clear_array(second, 3);
    return res;
}

bool test_intersection() {
    Number* first[3] = { new Float(4.5), new Int(4), new Complex(0, 0) };
    Number* second[3] = { new Float(4.5), new Int(1), new Float(3.3) };
    Number* expected[1] = { new Float(4.5) };
    Set<Number*>* set = Set<Number*>(first, 3) * Set<Number*>(second, 3);
    bool res = compare_results(expected, 1, set, std::string("test-intersection"));
    clear_array(first, 3);
    clear_array(second, 3);
    return res;
}

bool test_subtract() {
    Number* first[3] = { new Float(4.5), new Int(4), new Complex(0, 0) };
    Number* second[3] = { new Float(4.5), new Int(1), new Float(3.3) };
    Number* expected[2] = { new Complex(0, 0), new Int(4) };
    Set<Number*>* set = Set<Number*>(first, 3) - Set<Number*>(second, 3);
    bool res = compare_results(expected, 2, set, std::string("test-subtract"));
    clear_array(first, 3);
    clear_array(second, 3);
    return true;
}

bool test_includes() {
    Number* initial[3] = { new Float(4.5), new Int(4), new Complex(0, 0) };
    Set<Number*> set(initial, 3);

    bool res = true;
    if (set.includes(new Float(3.3)) == true || set.includes(new Complex(0, 0)) == false) {
        res = false;
    }

    clear_array(initial, 3);
    res ? std::cout << "PASS test-includes\n" : std::cout << "FAIL test-includes\n";
    return res;
}

bool test_includes_set() {
    Number* first[4] = { new Float(4.5), new Int(4), new Complex(0, 0), new Int(1) };
    Number* second[2] = { new Int(1), new Complex(0, 0) };
    Set<Number*> first_set(first, 4);
    Set<Number*> second_set(second, 2);
    bool res = first_set.includes_set(second_set) == true || second_set.includes_set(first_set) == false;
    clear_array(first, 4);
    clear_array(second, 2);

    res ? std::cout << "PASS test-includes-set\n" : std::cout << "FAIL test-includes-set\n";
    return res;
}

bool test_equality() {
    Number* first[2] = { new Int(1), new Complex(0, 0) };
    Number* second[3] = { new Complex(0, 0), new Int(1), new Int(1) };
    Set<Number*> first_set(first, 2);
    Set<Number*> second_set(second, 3);
    bool res = first_set == second_set;
    clear_array(first, 2);
    clear_array(second, 3);

    res ? std::cout << "PASS test-equality\n" : std::cout << "FAIL test-equality\n";
    return true;
}

bool test_deletion() {
    const int size = 5;
    bool res = true;
    Number* initial[size] = { new Int(1), new Int(2), new Int(3), new Int(4), new Int(5) };
    Number* delete_last[size - 1] = { new Int(1), new Int(2), new Int(3), new Int(4) };
    Number* delete_first[size - 2] = { new Int(2), new Int(3), new Int(4) };
    Number* delete_middle[size - 3] = { new Int(2), new Int(4) };

    Set<Number*> set(initial, size);
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
    clear_array(initial, size);
    clear_array(delete_last, size - 1);
    clear_array(delete_first, size - 2);
    clear_array(delete_middle, size - 3);

    return res;
}

Number* mapfunc(Number* v) {
    return *v + Int(5);
}

bool test_map() {
    Number* initial[3] = { new Complex(3, 4), new Float(54), new Complex(9, 0) };
    Number* expected[3] = { new Complex(8, 4), new Complex(14, 0), new Float(59), };
    Set<Number*> set(initial, 3);
    Set<Number*>* map_set = set.map(mapfunc);
    bool res = compare_results(expected, 3, map_set, "test-map");
    clear_array(initial, 3);
    return res;
}

bool wherefunc(Number* v) {
    return *v < Int(50);
}

bool test_where() {
    Number* initial[3] = { new Complex(3, 4), new Float(54), new Complex(9, 0) };
    Number* expected[2] = { new Complex(3, 4), new Complex(9, 0) };
    Set<Number*> set(initial, 3);
    bool res = compare_results(expected, 2, &set, "test-where");
    clear_array(initial, 3);
    return res;
}

int main() {
    int counter = 0;
    counter += test_clear();
    counter += test_insert();
    counter += test_merge();
    counter += test_intersection();
    counter += test_subtract();
    counter += test_includes();
    counter += test_includes_set();
    counter += test_equality();
    counter += test_deletion();
    counter += test_map();
    counter += test_where();

    std::cout << "TESTS PASSED: " << counter << "/" << TESTS << '\n';
}
