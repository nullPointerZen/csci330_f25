/*
 * Chapter 14: Iterators - Problem 1.1 Solution
 * Basic iterator operations: dereference, traversal, positioning
 * 
 * This solution demonstrates fundamental iterator operations that all
 * C++ iterators support, connecting to Python/Java iteration concepts.
 */

#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers{10, 20, 30, 40, 50};
    
    // Task 1: Print the first element using an iterator
    // Python equivalent: next(iter(numbers))
    auto first_it = numbers.begin();
    std::cout << "First: " << *first_it << "\n";
    
    // Task 2: Print the last element using an iterator  
    // Note: end() points "one past the end", so we need end() - 1
    // Python equivalent: numbers[-1]
    auto last_it = numbers.end() - 1;  // Only works with random access iterators
    std::cout << "Last: " << *last_it << "\n";
    
    // Task 3: Print all elements using a traditional iterator loop
    // Python equivalent: for item in numbers: print(item)
    // Java equivalent: Iterator<Integer> it = list.iterator(); while(it.hasNext())...
    std::cout << "All: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // Bonus: Demonstrating the three essential iterator operations
    std::cout << "\nDemonstrating essential iterator operations:\n";
    auto it = numbers.begin();
    
    // Operation 1: Dereference (*) - get current element
    std::cout << "Current element: " << *it << "\n";
    
    // Operation 2: Increment (++) - move to next element
    ++it;
    std::cout << "After increment: " << *it << "\n";
    
    // Operation 3: Comparison (==, !=) - check positions
    if (it != numbers.end()) {
        std::cout << "Iterator is not at end\n";
    }
    
    return 0;
}

/*
 * Expected Output:
 * First: 10
 * Last: 50
 * All: 10 20 30 40 50 
 * 
 * Demonstrating essential iterator operations:
 * Current element: 10
 * After increment: 20
 * Iterator is not at end
 * 
 * Key Learning Points:
 * 1. All iterators support: dereference (*), increment (++), comparison (==, !=)
 * 2. end() points "one past the last element" (half-open range concept)
 * 3. Iterator loops follow the pattern: begin() to end() with != comparison
 * 4. Random access iterators (like vector's) support arithmetic (-, +)
 */