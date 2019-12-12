#pragma once
#include <iostream>

void FillWithRandom(int *a, const unsigned long long int size) {
    for (auto i = 0; i < size; i++) {
        a[i] = rand() % 100;
    }
}