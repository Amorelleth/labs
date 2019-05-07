#include <iostream>
#include <map>
#include "set.hpp"
#include "types.hpp"
#include "node.hpp"

class SetClient;

enum Type { IntType, FloatType, ComplexType };
enum Helper { Exit, ShowSets, Help, Create };
enum Exception {
    InvalidType, InvalidAction, InsertFailed,
    SetDoesNotExist, SetsDoNotExist,
};
enum Action {
    Insert, Delete, Clear, Equal,
    Print, Includes, HelperAction,
    Merge, Intersection, Subtract
};

void clear_stream() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void does_key_exist(std::map<std::string, SetClient*> &m, std::string &key) {
    if (m.find(key) == m.end() || m.find(key) == m.end()) {
        clear_stream();
        throw SetDoesNotExist;
    }
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
    if (type == "int") return IntType;
    else if (type == "complex") return ComplexType;
    else if (type == "float") return FloatType;
    else {
        clear_stream();
        throw InvalidType;
    }
}

Action resolve_action(std::string &action) {
    if (action == "insert") return Insert;
    else if (action == "delete") return Delete;
    else if (action == "clear") return Clear;
    else if (action == "==" || action == "equal") return Equal;
    else if (action == "print") return Print;
    else if (action == "includes") return Includes;
    else if (action == "+" || action == "merge") return Merge;
    else if (action == "*" || action == "intersection") return Intersection;
    else if (action == "-" || action == "subtract") return Subtract;
    else return HelperAction;
}

Helper resolve_helper(std::string &action) {
    if (action == "create") return Create;
    else if (action == "help") return Help;
    else if (action == "sets") return ShowSets;
    else if (action == "exit") return Exit;
    else {
        clear_stream();
        throw InvalidAction;
    }
}

class SetClient {
    public:
        std::string name;
        Set<Number*>* set;

        SetClient(std::string _name) : name(_name), set(new Set<Number*>) {};
        SetClient(std::string _name, Set<Number*>* _set) : name(_name), set(_set) {};
        ~SetClient() { delete set; };

        void insert() {
            std::string type;
            std::cin >> type;

            switch (resolve_type(type)) {
                case IntType: {
                    int some_int;
                    std::cin >> some_int;
                    set->insert(new Int(some_int));
                    break;
                }
                case ComplexType: {
                    float some_re;
                    float some_im;
                    std::cin >> some_re >> some_im;
                    set->insert(new Complex(some_re, some_im));
                    break;
                }
                case FloatType: {
                    float some_float;
                    std::cin >> some_float;
                    set->insert(new Float(some_float));
                    break;
                }
                default: {
                    clear_stream();
                    throw InvalidType;
                }
            }
        }

        bool includes(std::string type) {
            switch (resolve_type(type)) {
                case IntType: {
                    int some_int;
                    std::cin >> some_int;
                    return set->includes(new Int(some_int));
                    break;
                }
                case ComplexType: {
                    float some_re;
                    float some_im;
                    std::cin >> some_re >> some_im;
                    return set->includes(new Complex(some_re, some_im));
                    break;
                }
                case FloatType: {
                    float some_float;
                    std::cin >> some_float;
                    return set->includes(new Float(some_float));
                    break;
                }
                default: {
                    clear_stream();
                    throw InvalidType;
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
                    set->delete_elem(new Int(some_int));
                    break;
                }
                case ComplexType: {
                    float some_re;
                    float some_im;
                    std::cin >> some_re >> some_im;
                    set->delete_elem(new Complex(some_re, some_im));
                    break;
                }
                case FloatType: {
                    float some_float;
                    std::cin >> some_float;
                    set->delete_elem(new Float(some_float));
                    break;
                }
                default: {
                    clear_stream();
                    throw InvalidType;
                }
            }
        }
};

void get_help(std::string &action) {
    std::string str;
    switch(resolve_action(action)) {
        case Insert: std::cout << ">>USAGE: {{ set name }} insert {{ type }} {{ value }}\n"; break;
        case Print: std::cout << ">>USAGE: {{ set name }} print\n"; break;
        case Delete: std::cout << ">>USAGE: {{ set name }} delete {{ elem type }} {{ elem value }} \n"; break;
        case Clear: std::cout << ">>USAGE: {{ set name }} clear\n"; break;
        case Includes: std::cout << ">>USAGE: {{ set name }} inclues {{ elem type }} {{ elem value }}" << ">>USAGE: {{ set1 name }} inclues {{ set2 name }}"; break;
        case Equal: std::cout << ">>USAGE: {{ set1 name }} == {{ set2 name }}\n" << ">>USAGE: {{ set1 name }} equal {{ set2 name }}\n"; break;
        case Merge: std::cout << ">>USAGE: {{ set1 name }} + {{ set2 name }}\n" << ">>USAGE: {{ set1 name }} merge {{ set2 name }}\n"; break;
        case Intersection: std::cout << ">>USAGE:  set1 name }} * {{ set2 name }}\n" << ">>USAGE:  set1 name }} intersection {{ set2 name }}\n"; break;
        case Subtract: std::cout << ">>USAGE: {{ set1 name }} - {{ set2 name }}\n" << ">>USAGE: {{ set1 name }} subtract {{ set2 name }}\n"; break;
        case HelperAction: {
            switch(resolve_helper(action)) {
                case Create: std::cout << ">>USAGE: create {{ set name }}\n"; break;
                case Exit: std::cout << ">>USAGE: exit\n"; break;
                case ShowSets: std::cout << ">>USAGE: sets\n"; break;
                case Help: clear_stream(); throw InvalidAction;
            }
        }
    }
}

int main() {
    std::map<std::string, SetClient*> m;
    std::string action, name;

    while (true) {
        std::cin >> name;
        try {
            if (m.find(name) == m.end()) {
                switch (resolve_helper(name)) {
                    case Create: {
                        std::cin >> name;
                        m.insert(std::pair<std::string, SetClient*>(name, new SetClient(name)));
                        continue;
                    }
                    case Help: {
                        std::cin >> action;
                        get_help(action);
                        continue;
                    }
                    case ShowSets: {
                        if (m.size() == 0) {
                            clear_stream();
                            throw SetsDoNotExist;
                        }
                        std::cout << "your sets: ";
                        for (auto const& [key, val] : m) {
                            std::cout << key << " ";
                        }
                        std::cout << "\n";
                        continue;
                    }
                    case Exit: {
                        for (auto const& [key, val] : m) {
                            delete val;
                        }
                        return 0;
                    }
                }
            }

            std::cin >> action;
            Action act = resolve_action(action);
            switch (act) {
                case Insert: {
                    does_key_exist(m, name);
                    m[name]->insert();
                    continue;
                }
                case Delete: {
                    does_key_exist(m, name);
                    if (std::cin.peek() == '\n') {
                        m[name]->set->~Set();
                        m.erase(name);
                    } else {
                        m[name]->delete_elem();
                    }
                    continue;
                }
                case Clear: {
                    does_key_exist(m, name);
                    m[name]->set->clear();
                    continue;
                }
                case Print: {
                    does_key_exist(m, name);
                    std::cout << *m[name]->set;
                    continue;
                }
                case Equal: {
                    std::string name2;
                    std::cin >> name2;
                    does_key_exist(m, name);
                    does_key_exist(m, name2);
                    std::cout << (*m[name]->set == *m[name2]->set ? "true\n" : "false\n");
                    continue;
                }
                case Includes: {
                    std::string type;
                    std::cin >> type;
                    does_key_exist(m, name);
                    if (m.find(type) != m.end()) {
                        std::cout << (m[name]->set->includes_set(*m[type]->set) ? "true\n" : "false\n");
                    } else {
                        std::cout << (m[name]->includes(type) ? "true\n" : "false\n");
                    }
                    continue;
                }
                case Merge:
                case Intersection:
                case Subtract: {
                    std::string name2, name3 = "";
                    std::cin >> name2;
                    if (std::cin.peek() != '\n') {
                        std::cin >> name3;
                    }
                    does_key_exist(m, name);
                    does_key_exist(m, name2);

                    Set<Number*>* set3;
                    if (act == Merge) {
                        set3 = *m[name]->set + *m[name2]->set;
                    } else if (act == Intersection) {
                        set3 = *m[name]->set * *m[name2]->set;
                    } else if (act == Subtract) {
                        set3 = *m[name]->set - *m[name2]->set;
                    } else {
                        throw InvalidAction;
                    }
                    if (name3 != "") {
                        m.insert(std::pair<std::string, SetClient*>(name3, new SetClient(name3, set3)));
                    }
                    std::cout << *set3;
                    continue;
                }
                case HelperAction: continue;
            }
        } catch (Exception exc) {
            std::cout << resolve_exception(exc);
            continue;
        }
    }

    return 0;
}
