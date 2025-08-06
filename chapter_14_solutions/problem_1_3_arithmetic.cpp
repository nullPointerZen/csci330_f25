/*
 * Chapter 14: Iterators - Problem 1.3 Solution
 * Iterator arithmetic and positioning
 * 
 * This solution demonstrates iterator arithmetic available with
 * random access iterators (like std::vector's iterators).
 */

#include <vector>
#include <iostream>

int main() {
    std::vector<int> data{1, 3, 5, 7, 9, 11, 13, 15};
    
    // Task 1: Print the element at position 3 (should be 7)
    // Python equivalent: data[3]
    // Java equivalent: data.get(3)
    std::cout << "Element at position 3: ";
    auto it_pos3 = data.begin() + 3;  // Iterator arithmetic: move 3 positions forward
    std::cout << *it_pos3 << "\n";
    
    // Task 2: Print every other element starting from the beginning
    // Python equivalent: data[::2] or for i in range(0, len(data), 2): print(data[i])
    std::cout << "Every other element: ";
    for (auto it = data.begin(); it < data.end(); it += 2) {  // Increment by 2 each time
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // Task 3: Print the last 3 elements
    // Python equivalent: data[-3:]
    // Java equivalent: subList(size-3, size)
    std::cout << "Last 3 elements: ";
    auto last_three_start = data.end() - 3;  // Start 3 positions before end
    for (auto it = last_three_start; it != data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // Bonus: Demonstrating various iterator arithmetic operations
    std::cout << "\nIterator arithmetic demonstrations:\n";
    
    auto begin_it = data.begin();
    auto end_it = data.end();
    
    // Distance between iterators
    auto distance = end_it - begin_it;
    std::cout << "Container size via iterators: " << distance << "\n";
    
    // Middle element
    auto middle_it = begin_it + distance / 2;
    std::cout << "Middle element: " << *middle_it << "\n";
    
    // Reverse arithmetic (moving backward)
    auto second_last = end_it - 2;
    std::cout << "Second to last element: " << *second_last << "\n";
    
    // Boundary checking demonstration
    std::cout << "\nBoundary safety:\n";
    auto safe_it = data.begin();
    if (safe_it + 10 < data.end()) {
        std::cout << "Safe to access element 10\n";
    } else {
        std::cout << "Element 10 would be out of bounds\n";
    }
    
    return 0;
}

/*
 * Expected Output:
 * Element at position 3: 7
 * Every other element: 1 5 9 13 
 * Last 3 elements: 11 13 15 
 * 
 * Iterator arithmetic demonstrations:
 * Container size via iterators: 8
 * Middle element: 7
 * Second to last element: 13
 * 
 * Boundary safety:
 * Element 10 would be out of bounds
 * 
 * Key Learning Points:
 * 1. Random access iterators support arithmetic: +, -, +=, -=
 * 2. Iterator differences give distances (similar to pointer arithmetic)
 * 3. end() - n gives iterator to nth element from the end
 * 4. Always check bounds when using iterator arithmetic
 * 5. Not all iterator types support arithmetic (only random access do)
 * 
 * Python/Java Connections:
 * - it + n is like accessing data[n] in Python/Java
 * - it += 2 in loops is like range(0, len(data), 2) in Python
 * - end() - 3 is like data[-3:] slicing in Python
 * - Iterator distance is like len(container)
 */