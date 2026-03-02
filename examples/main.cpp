#include <iostream>
#include "MyVector.hpp"

using CPSC131::MyVector::MyVector;

int main()
{
    MyVector<int> v;

    // Growth Demo
    // Push elements until we exceed the default capacity (64)
    // This should trigger a resize from 64 -> 128
    std::cout << "=== Push Back (Growth Demo) ===\n";

    for (int i = 1; i <= 70; i++)
    {
        v.push_back(i);

        // Print at key points to observe capacity changes
        if (i == 1 || i == 8 || i == 16 || i == 64 || i == 65 || i == 70)
        {
            v.print_helper();
            std::cout << "\n";
        }
    }

    // Insert / Erase Demo
    // Tests shifting of elements within the array
    // Insert: shifts elements to the right
    // Erase: shifts elements to the left
    std::cout << "=== Insert / Erase Demo ===\n";

    v.insert(2, 99); // Insert 99 at index 2
    v.erase(5);      // Remove element at index 5

    v.print_helper();
    std::cout << "\n";

    // Shrink Demo
    // Pop elements until size falls below capacity/3
    // This triggers capacity reductions (e.g., 128 -> 64 -> 32 -> ...)
    std::cout << "=== Pop Back (Shrink Demo) ===\n";

    for (int i = 0; i < 65; i++)
    {
        v.pop_back();

        // Print at key points to observe capacity changes
        if (i == 0 || i == 20 || i == 40 || i == 60)
        {
            v.print_helper();
            std::cout << "\n";
        }
    }

    std::cout << "Final after pops:\n";
    v.print_helper();
    std::cout << "\n";

    // Copy Demo (Rule of Three)
    // Verify that the copy constructor creates a deep copy
    // Changes to the original should not affect the copy
    std::cout << "=== Copy Semantics Demo ===\n";

    MyVector<int> copy = v;   // Copy constructor
    v.set(0, 777);            // Modify original

    std::cout << "Original:\n";
    v.print_helper();

    std::cout << "Copy (should be unchanged):\n";
    copy.print_helper();

    // Exception Demo
    // Accessing an invalid index throws std::out_of_range
    std::cout << "\n=== Exception Demo ===\n";
    try
    {
        v.at(1000);  // Invalid index
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    return 0;
}