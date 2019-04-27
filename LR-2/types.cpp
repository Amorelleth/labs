#pragma once
#include "types.hpp"

// флот
//
//

bool Float::equal(const Int* some_int) const {
    return data == some_int->data;
}
// bool Float::equal(const Complex* some_complex) const {
//     return false;
// }
bool Float::equal(const Float* some_float) const {
    std::cout << "it works maybe";
    return data == some_float->data;
}
bool Float::less(const Any* any) const {
    std::cout << "it works maybe";
    return any->less(this);
}
bool Float::equal(const Any* any) const {
    std::cout << "it works maybe";
    return any->less(this);
}
bool Float::less(const Int* some_int) const {
    return data < some_int->data;
}
bool Float::less(const Float* some_float) const {
    return data < some_float->data;
}
// bool Float::less(const Complex* some_complex) const {
//     return false;
// }



// инт
//
//

bool Int::equal(const Int* some_int) const {
    return data == some_int->data;
}
bool Int::equal(const Float* some_float) const {
    return data == some_float->data;
}
// bool Int::equal(const Complex* some_complex) const {
//     return false;
// }
bool Int::less(const Any* any) const {
    std::cout << "it works maybe";

    return any->less(this);
}
bool Int::equal(const Any* any) const {
    std::cout << "it works maybe";

    return any->less(this);
}
bool Int::less(const Int* some_int) const {
    return data < some_int->data;
}
bool Int::less(const Float* some_float) const {
    return data < some_float->data;
}
// bool Int::less(const Complex* some_complex) const {
//     return false;
// }


// комплекс
// пока дознт ворк
//

// void Complex::serialize (std::ostream& out) const {
//     out << data;
// }
// bool Complex::equal(const Any* any) const {
//     return any->equal(this);
// }
// bool Complex::equal(const Int* some_int) const {
//     return false;
// }
// bool Complex::equal(const Float* some_float) const {
//     return false;
// }
// // bool Complex::equal(const Complex* some_complex) const {
// //     return data == some_complex;
// // }
// bool Complex::less(const Any* any) const {
//     return any->less(this);
// }
// bool Complex::less(const Int* some_int) const {
//     return data < some_int->data;
// }
// bool Complex::less(const Float* some_float) const {
//     return data < some_float->data;
// }
// // bool Complex::less(const Complex* some_complex) const {
// //     return data < some_complex
// // }

bool operator<=(const Float& any_1, const Float& any_2) {
    std::cout << "<=";
    return any_1.equal(&any_2) || (&any_1)->less(&any_2);
}
// bool operator<(const Any& any_1, const Any& any_2) {
//     std::cout << "<";
//     return any_1.less(&any_2);
// }