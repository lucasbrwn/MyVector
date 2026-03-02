# MyVector (C++)

A template-based dynamic array (similar to `std::vector`) built to practice manual memory management, resizing strategies, and copy semantics.

## Features

- Template container: `MyVector<T>`
- Dynamic resizing:
  - Grows by doubling when full
  - Shrinks when size drops below ~1/3 of capacity (down to a minimum capacity)
- Element operations:
  - `push_back`, `pop_back`
  - `insert`, `erase`
  - `set`, `clear`
  - `reserve`
- Element access:
  - `operator[]` (bounds-checked in this implementation)
  - `at()` (index bounds-checked)
  - `elements()` (raw pointer access)
- Capacity info:
  - `size()`, `capacity()`, `empty()`
- Copy semantics:
  - Copy constructor + copy assignment + destructor (Rule of Three)
- Debug:
  - `print_helper()` to print size/capacity and contents

## Time Complexity

size(): O(1)  
capacity(): O(1)  
empty(): O(1)  
elements(): O(1)  
at(index): O(1)  
operator[]: O(1)  
set(index, element): O(1)  
reserve(): O(n)  
push_back(): O(1) normally, O(n) when capacity increases  
pop_back(): O(1) normally, O(n) when capacity decreases  
insert(index, element): O(n)  
erase(index): O(n)  
clear(): O(n)  
print_helper(): O(n)

## Project Structure

```
MyVector/
├── include/
│   └── MyVector.hpp
├── examples/
│   └── main.cpp
└── README.md
```

## Build and Run

From the project root:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic examples/main.cpp -I include -o myvector_example
./myvector_example
```

## Example Demonstration

The example program demonstrates:

- Dynamic growth (capacity 64 → 128)
- Shrink behavior when size falls below capacity / 3
- Element shifting with `insert` and `erase`
- Deep copy behavior (Rule of Three)
- Bounds-checking exception handling

## Design Decisions

- **Growth strategy:** Capacity doubles when full to provide amortized O(1) `push_back()`
- **Shrink strategy:** Capacity is reduced when `size < capacity / 3` to balance memory usage and performance
- **Minimum capacity:** Prevents excessive reallocations for small vectors
- **Safety:** Bounds checking added to both `at()` and `operator[]` in this implementation

## Purpose

This project was developed to strengthen understanding of:

- Manual memory management in C++
- Dynamic resizing strategies and performance tradeoffs
- Copy semantics and resource management (Rule of Three)
- Maintaining container class invariants