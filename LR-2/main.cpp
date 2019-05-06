#include <any>
#include <iostream>
#include <vector>
#include <map>
#include "set.hpp"
#include "types.hpp"
#include "node.hpp"

// - map, where +
// + объединение +
// + пересечение +
// + вычитание +
// + проверка на включение подмножества +
// + проверка на вхождение элемента +
// + сравнение (равенство) двух множеств +

enum Type {
    IntType,
    FloatType,
    ComplexType,
};

enum Exception {
    InvalidType,
    InvalidAction,
    InsertFailed,
    SetDoesNotExist,
    SetsDoNotExist,
};

enum Action {
    Help,
    ShowSets,
    Create,
    Insert,
    Delete,
    Clear,
    Print,
    Merge,
    Intersection,
    Subtract,
    Equal,
    Includes,
    Exit
};

void clear_stream() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string resolve_exception(Exception exc) {
    switch (exc) {
        case InvalidType: return "invalid type\n";
        case InvalidAction: return "invalid action\n";
        case InsertFailed: return "failed to insert. check yout input\n";
        case SetDoesNotExist: return "no such set\n";
        case SetsDoNotExist: return "you do not have any sets yet\n";
    }
}

Type resolve_type(std::string &type) {
    if (type == "int") {
        return IntType;
    } else if (type == "complex") {
        return ComplexType;
    } else if (type == "float") {
        return FloatType;
    } else {
        clear_stream();
        throw InvalidType;
    }
}

Action resolve_action(std::string &action) {
    if (action == "help") {
        return Help;
    } else if (action == "sets") {
        return ShowSets;
    } else if (action == "create") {
        return Create;
    } else if (action == "insert") {
        return Insert;
    } else if (action == "delete") {
        return Delete;
    } else if (action == "clear") {
        return Clear;
    } else if (action == "print") {
        return Print;
    } else if (action == "+" || action == "merge") {
        return Merge;
    } else if (action == "*" || action == "intersection") {
        return Intersection;
    } else if (action == "-" || action == "subtract") {
        return Subtract;
    } else if (action == "==" || action == "equal") {
        return Equal;
    } else if (action == "includes") {
        return Includes;
    } else if (action == "exit") {
        return Exit;
    } else {
        clear_stream();
        throw InvalidAction;
    }
}

class SetClient {
    public:
        std::string name;
        Set<Number*> set;

        SetClient(std::string _name) {
            name = _name;
        }

        void insert() {
            std::string type;
            std::cin >> type;

            switch (resolve_type(type)) {
                case IntType: {
                    int some_int;
                    std::cin >> some_int;
                    set.insert(new Int(some_int));
                }
                case ComplexType: {
                    float some_re;
                    float some_im;
                    std::cin >> some_re >> some_im;
                    set.insert(new Complex(some_re, some_im));
                }
                case FloatType: {
                    float some_float;
                    std::cin >> some_float;
                    set.insert(new Float(some_float));
                }
            }
        }
        
        void delete_elem() {
            std::string type;
            std::cin >> type;

            switch(resolve_type(type)) {
                case IntType: {
                    int some_int;
                    std::cin >> some_int;
                    set.insert(new Int(some_int));
                }
                case ComplexType: {
                    float some_re;
                    float some_im;
                    std::cin >> some_re >> some_im;
                    set.insert(new Complex(some_re, some_im));
                }
                case FloatType: {
                    float some_float;
                    std::cin >> some_float;
                    set.insert(new Float(some_float));
                }
            }
        }

        // void Merge
};

void get_help(std::string &action) {
    std::string str;
    switch(resolve_action(action)) {
        case Create: {
            std::cout << ">>USAGE: create {{ set name }}\n";
            break;
        }
        case Insert: {
            std::cout << ">>USAGE: insert {{ set name }} {{ type }} {{ value }}\n";
            break;
        }
        case ShowSets: {
            std::cout << ">>USAGE: sets\n";
            break;
        }
        case Merge: {
            std::cout << ">>USAGE: {{ set1 name }} + {{ set2 name }}\n>>{{ set1 name }} merge {{ set2 name }}\n";
            break;
        }
        case Intersection: {
            std::cout << ">>USAGE:  set1 name }} * {{ set2 name }}\n>>{{ set1 name }} intersection {{ set2 name }}\n";
            break;
        }
        case Subtract: {
            std::cout << ">>USAGE: {{ set1 name }} - {{ set2 name }}\n";
            break;
        }
        case Equal: {
            std::cout << ">>USAGE: {{ set1 name }} == {{ set2 name }}\n";
            break;
        }
        case Print: {
            std::cout << ">>USAGE: print {{ set name }}\n";
            break;
        }
        case Delete: {
            std::cout << ">>USAGE: delete {{ set name }}\n>>delete {{ set name }} {{ elem type }} {{ elem vslue }} \n";
            break;
        }
        case Clear: {
            std::cout << ">>USAGE: clear {{ set name }}\n";
            break;
        }
        case Includes: {
            std::cout << ">>USAGE: includes {{ set name }}\n>>inclues {{ elem type }} {{ elem value }}";
            break;
        }
        case Exit: {
            std::cout << ">>USAGE: exit\n";
            break;
        }
        case Help: throw InvalidAction;
    }
}

void init() {
    std::cout << "** enter 'help {{ command }}' to get info **\n";
    std::cout << "** commands **\n" << " -create\n" << " -insert\n";
    std::cout << " -sets\n" << " -merge (also '+')\n";
    std::cout << " -intersection (also '*')\n" << " -subtract (also '-')\n";
    std::cout << " -equal (also '==')\n" << " -print\n" << " -delete\n";
    std::cout << " -clear\n" << " -includes\n" << " -exit\n";
}

int main() {
    init();

    std::map<std::string, SetClient*> m;

    std::string action;
    std::string name;

    while (true) {
        std::cin >> action;
        std::cout << action;
        switch (resolve_action(action)) {
            case Help: {
                try {
                    std::cin >> action;
                    get_help(action);
                    clear_stream();
                } catch (Exception exc) {
                    std::cout << resolve_exception(exc);
                }
                break;
            }
            case ShowSets: {
                try {
                    if (m.size() == 0) {
                        clear_stream();
                        // throw SetsDoNotExist;
                    }
                    std::cout << "YOUR SETS: ";
                    for(auto const& [key, val] : m) {
                        std::cout << key << " ";
                    }
                    std::cout << "\n";
                } catch (Exception exc) {
                    std::cout << resolve_exception(exc);
                    get_help(action);
                }
                break;
            }
            case Create: {
                std::cin >> name;
                m.insert(std::pair<std::string, SetClient*>(name, new SetClient(name)));
                break;
            }
            case Insert: {
                // try {
                //     std::cin >> name;
                //     if (m[name] == nullptr) {
                //         clear_stream();
                //         throw SetDoesNotExist;
                //         break;
                //     }
                //     m[name]->insert();
                // } catch (...) {
                //     // clear_stream();
                //     // std::cout << resolve_exception(exc);
                //     get_help(action);
                //     continue;
                // }
                std::cout << "okkkkk";
                break;
            }
            case Delete: {
                std::cin >> name;
                if (m[name] == nullptr) {
                    clear_stream();
                    throw SetDoesNotExist;
                    break;
                }
                std::cout << m[name]->set;
                break;
            }
            case Clear: {
                std::cin >> name;
                if (m[name] == nullptr) {
                    clear_stream();
                    throw SetDoesNotExist;
                    break;
                }
                m[name]->set.clear();
                break;
            }
            case Print: {
                std::cin >> name;
                if (m[name] == nullptr) {
                    clear_stream();
                    // throw SetDoesNotExist;
                    break;
                }
                std::cout << m[name]->set;
                break;
            }
            case Merge: {
                std::string name2;
                std::cin >> name;
                std::cin >> name2;
                if (m[name] == nullptr || m[name2] == nullptr) {
                    clear_stream();
                    throw SetDoesNotExist;
                    break;
                }
                std::cout << m[name]->set + m[name2]->set;
                break;
            }
            case Intersection: {
                break;
            }
            case Subtract: {
                break;
            }
            case Equal: {
                break;
            }
            case Includes: {
                break;                    
            }
            case Exit: {
                return 0;
            }
            default: {
                clear_stream();
                continue;
                // throw InvalidAction;
            }
        }
    }

    return 0;
}
