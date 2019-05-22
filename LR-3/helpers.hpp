#include <iostream>
#include "types.hpp"
#include "tree.hpp"

Number* mapfunc(Number* v) {
    return *v + Int(5);
}

bool wherefunc(Number* v) {
    return *v < Int(10);
}
