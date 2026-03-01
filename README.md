# MyVector – Custom C++ Dynamic Array

Custom C++ container that replicates core functionality of `std::vector`.
This project demonstrates manual memory management, template programming, and dynamic resizing strategies.

---

## Overview

* Template-based dynamic array implementation
* Automatic capacity growth (doubles when full)
* Capacity shrink when size drops below 1/3
* Full Rule of Three:

  * Copy constructor
  * Assignment operator
  * Destructor
* Core operations:

  * `push_back`, `pop_back`
  * `insert`, `erase`
  * `clear`, `reserve`
  * `size`, `capacity`, `empty`
  * `operator[]` and bounds-checked `at()`
* Exception handling for invalid access and operations

---

## Design Highlights

* Dynamic memory managed using `new` and `delete[]`
* Amortized **O(1)** insertion at the end
* Automatic memory growth and shrink policies
* Bounds checking with `std::out_of_range`
* Capacity never drops below a minimum threshold
* Helper functions used for:

  * Copy logic
  * Range validation
  * Capacity management

---

## Project Structure

```
include/
  MyVector.hpp    // Template implementation

main.cpp          // Optional demo/test file
README.md
```

---

## Example Usage

```cpp
#include <iostream>
#include "MyVector.hpp"

int main() {
    CPSC131::MyVector::MyVector<int> vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    vec.insert(1, 15);   // [10, 15, 20, 30]
    vec.erase(2);        // removes 20

    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
}
```

Output:

```
10 15 30
```

---

## How to Build

From the project root:

```
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -I include -o demo
./demo
```

---

## What I Learned

* Manual memory management and ownership in C++
* Implementing the Rule of Three
* Designing dynamic data structures
* Amortized time complexity and resizing tradeoffs
* Writing reusable template classes
* Exception-safe container operations

---

## Tech Stack

* C++
* Standard Library
