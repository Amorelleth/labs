#include <iostream>
#include "types.hpp"
#include "tree.hpp"
#include "helpers.hpp"

#define TESTS_COUNTER 18

TTree<Number*>* init_small_tree() {
    auto tree = new TTree<Number*>;
    tree->insert(new Int(5));
    tree->insert(new Float(4.4));
    tree->insert(new Complex(3, 9));
    tree->insert(new Complex(3, -9));
    return tree;
}

TTree<Number*>* init_big_tree() {
    auto tree = new TTree<Number*>;
    tree->insert(new Int(10));
	tree->insert(new Complex(6, -5));
	tree->insert(new Int(14));
	tree->insert(new Int(5));
	tree->insert(new Int(8));
	tree->insert(new Int(11));
	tree->insert(new Int(18));
	tree->insert(new Int(18));
	tree->insert(new Int(18));
	tree->insert(new Int(5));
	tree->insert(new Float(8));
	tree->insert(new Float(1.1));
	tree->insert(new Float(1.5));
	tree->insert(new Float(1.8));
	tree->insert(new Float(-1.8));
    return tree;
}

bool test_search() {
	auto *tree = init_big_tree();
    bool res = false;

    if (tree->search(new Int(18)) != nullptr) {
        cout << "PASS test_search" << endl;
        res = true;
    } else {
        cout << "FAIL test_search" << endl;
        cout << "---Node Int(18) was not found in " << tree->to_string() << endl;
    }

    delete tree;
    return res;
}

bool test_map() {
    auto tree = init_small_tree();
    auto mapped_tree = tree->map(mapfunc);
    auto expected = new TTree<Number*>;
    bool res = false;

    expected->insert(new Complex(10, 0));
    expected->insert(new Complex(9.4, 0));
    expected->insert(new Complex(8, 9));
    expected->insert(new Complex(8, -9));

    if (
        mapped_tree->to_string() == "( 10+0i )[ 8+9i ]{ 9.4+0i }{ 8-9i }" &&
        *mapped_tree == *expected
    ) {
        cout << "PASS test_map" << endl;
        res = true;
    } else {
        cout << "FAIL test_map" << endl;
        cout << "---EXPECTED " << expected->to_string() << endl;
        cout << "---GOT " << mapped_tree->to_string() << endl;
    }

    delete mapped_tree;
    delete expected;
    delete tree;
    return res;
}

bool test_where() {
    auto tree = init_big_tree();
    auto whered_tree = tree->where(wherefunc);
    auto expected = new TTree<Number*>;
    bool res = false;

	expected->insert(new Complex(6, -5));
	expected->insert(new Int(8));
    expected->insert(new Float(1.8));
	expected->insert(new Float(-1.8));
	expected->insert(new Int(5));
	expected->insert(new Int(5));
	expected->insert(new Float(8));
	expected->insert(new Float(1.1));
	expected->insert(new Float(1.5));

    if (
        whered_tree->to_string() == expected->to_string() &&
        *whered_tree == *expected
    ) {
        cout << "PASS test_where" << endl;
        res = true;
    } else {
        cout << "FAIL test_where" << endl;
        cout << "---EXPECTED " << expected->to_string() << endl;
        cout << "---GOT " << whered_tree->to_string() << endl;
    }

    delete tree;
    delete whered_tree;
    delete expected;
    return res;
}

bool test_destroy_tree() {
    auto tree = new TTree<Number*>;
    bool res = false;

    tree->insert(new Int(5));
    tree->insert(new Float(4.4));
    tree->insert(new Complex(3, 9));
    tree->insert(new Complex(3, -9));
    tree->~TTree();

    if (
        tree->to_string() == "" &&
        tree->_get_root() == nullptr
    ) {
        cout << "PASS test_destroy_tree" << endl;
        res = true;
    } else {
        cout << "FAIL test_destroy_tree" << endl;
        cout << "---TREE IS NOT EMPTY" << endl;
    }
    return res;
}

bool test_insert() {
    auto tree = init_small_tree();
    bool res = false;
    string expected_str = "( 5 )[ 3+9i ]{ 4.4 }{ 3-9i }";

    if (
        tree->to_string() == expected_str &&
        *tree->_get_root()->value == Int(5) &&
        *tree->_get_root()->left->value == Float(4.4) &&
        *tree->_get_root()->mid->value == Complex(3, 9) &&
        *tree->_get_root()->right->value == Complex(3, -9)
    ) {
        cout << "PASS test_insert" << endl;
        res = true;
    } else {
        cout << "FAIL test_insert" << endl;
        cout << "---EXPECTED " << expected_str << endl;
        cout << "---GOT " << tree->to_string() << endl;
    }

    delete tree;
    return res;
}

bool test_is_subtree() {
	TTree<Number*> *tree = init_big_tree();
	TTree<Number*> *sub_tree = new TTree<Number*>();

	sub_tree->insert(new Int(14));
	sub_tree->insert(new Int(18));
	sub_tree->insert(new Int(18));
	sub_tree->insert(new Int(5));

    bool res = tree->is_subtree(sub_tree);

    if (res) {
        cout << "PASS test_is_subtree" << endl;
    } else {
        cout << "FAIL test_is_subtree" << endl;
        cout << "---EXPECTED TRUE" << endl;
        cout << "---GOT FALSE" << endl;
        cout << "---TREE " << tree->to_string() << endl;
        cout << "---SUB_TREE " << sub_tree->to_string() << endl;
    }
    return res;
}

bool test_merge() {
    TTree<Number*> *big_tree = init_big_tree();
    TTree<Number*> *small_tree = init_small_tree();
    string expected_str = "( 10 )[ 14 [ 18 ]{ 18 }{ 5 }]{ 6-5i [ 11 [ 3+9i ]{ 4.4 }{ 3-9i }]{ 8 [ -1.8 ]{ 1.8 }{ 5 }}{ 18 }}{ 5 [ 1.1 ]{ 8 }{ 1.5 }}";

    auto tree = big_tree->merge(small_tree);
    bool res = false;

    if (tree->to_string() == expected_str) {
        cout << "PASS test_merge" << endl;
        res = true;
    } else {
        cout << "FAIL test_merge" << endl;
        cout << "---FIRST TREE " << big_tree->to_string() << endl;
        cout << "---SECOND TREE " << small_tree->to_string() << endl;
        cout << "---EXPECTED " << expected_str << endl;
        cout << "---GOT " << tree->to_string() << endl;
    }

    return res;
}

bool _empty_test_search() {
	auto *tree = new TTree<Number*>;
    bool res = false;

    if (tree->search(new Int(18)) == nullptr) {
        cout << "PASS _empty_test_search" << endl;
        res = true;
    } else {
        cout << "FAIL _empty_test_search" << endl;
    }

    delete tree;
    return res;
}

bool _empty_test_map() {
    auto *tree = new TTree<Number*>;
    auto mapped_tree = tree->map(mapfunc);
    bool res = false;

    if (
        mapped_tree->to_string() == "" &&
        *mapped_tree == *tree
    ) {
        cout << "PASS _empty_test_map" << endl;
        res = true;
    } else cout << "FAIL _empty_test_map" << endl;

    delete mapped_tree;
    delete tree;
    return res;
}

bool _empty_test_where() {
    auto *tree = new TTree<Number*>;
    auto whered_tree = tree->where(wherefunc);
    bool res = false;

    if (
        whered_tree->to_string() == tree->to_string() &&
        *whered_tree == *tree
    ) {
        cout << "PASS _empty_test_where" << endl;
        res = true;
    } else cout << "FAIL _empty_test_where" << endl;

    delete tree;
    delete whered_tree;
    return res;
}

bool _empty_test_destroy_tree() {
    auto tree = new TTree<Number*>;
    bool res = false;
    tree->~TTree();

    if (
        tree->to_string() == "" &&
        tree->_get_root() == nullptr
    ) {
        cout << "PASS _empty_test_destroy_tree" << endl;
        res = true;
    } else cout << "FAIL _empty_test_destroy_tree" << endl;
    return res;
}

bool _empty_test_is_subtree() {
	auto tree = new TTree<Number*>;
	auto sub_tree = new TTree<Number*>();

	sub_tree->insert(new Int(14));
	sub_tree->insert(new Int(18));
	sub_tree->insert(new Int(18));
	sub_tree->insert(new Int(5));

    bool res = tree->is_subtree(sub_tree);

    if (!res) {
        cout << "PASS _empty_test_is_subtree" << endl;
    } else {
        cout << "FAIL _empty_test_is_subtree" << endl;
        cout << "---EXPECTED FALSE" << endl;
        cout << "---GOT TRUE" << endl;
        cout << "---TREE " << tree->to_string() << endl;
        cout << "---SUB_TREE " << sub_tree->to_string() << endl;
    }
    return res;
}

bool __empty_test_is_subtree() {
	auto tree = init_big_tree();
	auto sub_tree = new TTree<Number*>();
    bool res = tree->is_subtree(sub_tree);

    if (res) {
        cout << "PASS __empty_test_is_subtree" << endl;
    } else {
        cout << "FAIL __empty_test_is_subtree" << endl;
        cout << "---EXPECTED TRUE" << endl;
        cout << "---GOT FALSE" << endl;
    }
    return res;
}

bool ___empty_test_is_subtree() {
	auto tree = new TTree<Number*>;
	auto sub_tree = new TTree<Number*>;
    bool res = tree->is_subtree(sub_tree);

    if (res) {
        cout << "PASS ___empty_empty_test_is_subtree" << endl;
    } else {
        cout << "FAIL ___empty_empty_test_is_subtree" << endl;
        cout << "---EXPECTED TRUE" << endl;
        cout << "---GOT FALSE" << endl;
    }
    return res;
}

bool _empty_test_merge() {
	auto null_tree = new TTree<Number*>;
    auto *small_tree = init_small_tree();
    auto tree = null_tree->merge(small_tree);
    bool res = false;

    if (tree->to_string() == small_tree->to_string()) {
        cout << "PASS _empty_test_merge" << endl;
        res = true;
    } else {
        cout << "FAIL _empty_test_merge" << endl;
        cout << "---FIRST TREE " << null_tree->to_string() << endl;
        cout << "---SECOND TREE " << small_tree->to_string() << endl;
        cout << "---EXPECTED " << small_tree->to_string() << endl;
        cout << "---GOT " << tree->to_string() << endl;
    }
    return res;
}

bool __empty_test_merge() {
	auto null_tree = new TTree<Number*>;
    auto *big_tree = init_big_tree();
    auto tree = big_tree->merge(null_tree);
    bool res = false;

    if (tree->to_string() == big_tree->to_string()) {
        cout << "PASS __empty_test_merge" << endl;
        res = true;
    } else {
        cout << "FAIL __empty_test_merge" << endl;
        cout << "---FIRST TREE " << null_tree->to_string() << endl;
        cout << "---SECOND TREE " << big_tree->to_string() << endl;
        cout << "---EXPECTED " << big_tree->to_string() << endl;
        cout << "---GOT " << tree->to_string() << endl;
    }
    return res;
}

bool ___empty_test_merge() {
	auto null_tree = new TTree<Number*>;
	auto _null_tree = new TTree<Number*>;
    auto tree = null_tree->merge(_null_tree);
    bool res = false;

    if (tree->to_string() == "") {
        cout << "PASS ___empty_test_merge" << endl;
        res = true;
    } else {
        cout << "FAIL ___empty_test_merge" << endl;
        cout << "---EXPECTED EMPTY TREE" << endl;
    }
    return res;
}

bool test_subtree() {
	auto big_tree = init_big_tree();
	auto expected = new TTree<Number*>;
    auto tree = big_tree->sub_tree(new Int(8));
    bool res = false;
    
    expected->insert(new Int(8));
    expected->insert(new Float(1.8));
    expected->insert(new Float(-1.8));

    if (
        tree->to_string() == expected->to_string() &&
        *tree == *expected
    ) {
        cout << "PASS test_subtree" << endl;
        res = true;
    } else {
        cout << "FAIL test_subtree" << endl;
        cout << "---EXPECTED " << expected->to_string() << endl;
        cout << "---GOT " << tree->to_string() << endl;
    }

    delete expected;
    delete tree;
    return res;
}

bool _empty_test_subtree() {
	auto null_tree = new TTree<Number*>;
    auto tree = null_tree->sub_tree(new Int(8));
    bool res = false;
    
    if (tree->to_string() == "") {
        cout << "PASS _empty_test_subtree" << endl;
        res = true;
    } else {
        cout << "FAIL _empty_test_subtree" << endl;
        cout << "---EXPECTED EMPTY TREE" << endl;
    }

    delete null_tree;
    delete tree;
    return res;
}

int main() {
    int res = 0;

    res += test_merge();
    res += test_map();
    res += test_where();
    res += test_insert();
    res += test_destroy_tree();
    res += test_is_subtree();
    res += test_subtree();
    res += test_search();
    res += _empty_test_merge();
    res += __empty_test_merge();
    res += ___empty_test_merge();
    res += _empty_test_map();
    res += _empty_test_subtree();
    res += _empty_test_where();
    res += _empty_test_destroy_tree();
    res += _empty_test_is_subtree();
    res += __empty_test_is_subtree();
    res += ___empty_test_is_subtree();
    res += _empty_test_search();

    std::cout << "TESTS PASSED: " << res << "/" << TESTS_COUNTER << '\n';

    return 0;
}