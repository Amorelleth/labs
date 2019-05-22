#include <iostream>
#include <fstream>
#include <map>
#include "types.hpp"
#include "tree.hpp"

using namespace std;

// Обходы1): (К)[2]{1}{3}

enum Type { IntType, FloatType, ComplexType };
enum Exception {
    InvalidType, InvalidAction,
    TreeDoesNotExist, TreesDoNotExist,
};
enum Action {
    Insert, Delete, Clear, Print, Exit,
	Includes, Merge, Graph, Create,
	ShowTrees, IncludesNode, GetTree
};

void clear_stream() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void does_key_exist(map<string, TTree<Number*>*> &m, string &key) {
    if (m.find(key) == m.end()) {
        clear_stream();
        throw TreeDoesNotExist;
    }
}

string resolve_exception(Exception exc) {
    switch (exc) {
        case InvalidType: return "invalid type\n";
        case InvalidAction: return "invalid action\n";
        case TreeDoesNotExist: return "no such tree\n";
        case TreesDoNotExist: return "you do not have any trees yet\n";
    }
}

Type resolve_type(string &type) {
    if (type == "int") return IntType;
    else if (type == "complex") return ComplexType;
    else if (type == "float") return FloatType;
    else {
        clear_stream();
        throw InvalidType;
    }
}

Action resolve_action(string &action) {
	if (action == "create") return Create;
    else if (action == "trees") return ShowTrees;
    else if (action == "exit") return Exit;
    else if (action == "insert") return Insert;
    else if (action == "delete") return Delete;
    else if (action == "clear") return Clear;
    else if (action == "print") return Print;
    else if (action == "graph") return Graph;
    else if (action == "includes") return Includes;
    else if (action == "includes-node") return IncludesNode;
    else if (action == "get-tree") return GetTree;
    else if (action == "+" || action == "merge") return Merge;
    else throw InvalidAction;
}

int main() {
	map<string, TTree<Number*>*> m;
    string action, name;

    while (true) {
		cin >> action;
        try {
            Action act = resolve_action(action);
            switch (act) {
                case Insert: {
					cin >> name;
                    does_key_exist(m, name);
					string type;
					cin >> type;
					switch(resolve_type(type)) {
						case IntType: {
							int some;
							cin >> some;
							m[name]->insert(new Int(some));
							break;
						}
						case FloatType: {
							float some;
							cin >> some;
							m[name]->insert(new Float(some));
							break;
						}
						case ComplexType: {
							float re, im;
							cin >> re >> im;
							m[name]->insert(new Complex(re, im));
							break;
						}
					}
                    continue;
                }
				case Delete: {
					cin >> name;
                    does_key_exist(m, name);
					m[name]->~TTree();
					m.erase(name);
                    continue;
                }
                case Clear: {
					cin >> name;
                    does_key_exist(m, name);
                    m[name]->~TTree();
                    continue;
                }
				case Print: {
					cin >> name;
					does_key_exist(m, name);
                    cout << *m[name] << endl;
                    continue;
				}
				case Includes: {
					cin >> name;
					does_key_exist(m, name);
					string second_name;
					cin >> second_name;
					does_key_exist(m, second_name);
                    cout << m[name]->is_subtree(m[second_name]) << endl;
					continue;
				}
				case GetTree: {
					cin >> name;
                    does_key_exist(m, name);
					string type;
					cin >> type;
					switch(resolve_type(type)) {
						case IntType: {
							int some;
							cin >> some;
							cout << *m[name]->sub_tree(new Int(some)) << endl;
							break;
						}
						case FloatType: {
							float some;
							cin >> some;
							cout << *m[name]->sub_tree(new Float(some)) << endl;
							break;
						}
						case ComplexType: {
							float re, im;
							cin >> re >> im;
							cout << *m[name]->sub_tree(new Complex(re, im)) << endl;
							break;
						}
					}
                    continue;
				}
				case Merge: {
					cin >> name;
					does_key_exist(m, name);
					string second_name;
					cin >> second_name;
					does_key_exist(m, second_name);
                    cout << *m[name]->merge(m[second_name]) << endl;
					continue;
				}
				case Graph: {
					cin >> name;
					does_key_exist(m, name);
					string file;
					cin >> file;
					m[name]->make_graph(file);
					continue;
				}
				case Create: {
					cin >> name;
					m.insert(pair<string, TTree<Number*>*>(name, new TTree<Number*>));
				}
				case ShowTrees: {
					if (m.size() == 0) {
						clear_stream();
						throw TreesDoNotExist;
					}
					std::cout << "your trees: ";
					for (auto const& [key, val] : m) {
						std::cout << key << " ";
					}
					std::cout << "\n";
					continue;
				}
				case IncludesNode: {
					cin >> name;
                    does_key_exist(m, name);
					string type;
					cin >> type;
					switch(resolve_type(type)) {
						case IntType: {
							int some;
							cin >> some;
							cout << m[name]->search(new Int(some))->value << endl;
							break;
						}
						case FloatType: {
							float some;
							cin >> some;
							cout << m[name]->search(new Float(some))->value << endl;
							break;
						}
						case ComplexType: {
							float re, im;
							cin >> re >> im;
							cout << m[name]->search(new Complex(re, im))->value << endl;
							break;
						}
					}
                    continue;
				}
				case Exit: {
					return 0;
				}
			};
        } catch (Exception exc) {
            cout << resolve_exception(exc);
            continue;
        }
    }

	for (auto const& [key, val] : m) {
		delete val;
	}

    return 0;
}
