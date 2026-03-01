#include <iostream>
#include "MyVector.hpp"

int main() {
    CPSC131::MyVector::MyVector<int> v;

    for (int i = 1; i <= 5; i++) {
        v.push_back(i);
    }

    v.insert(2, 99);
    v.erase(1);

    v.print_helper();
}