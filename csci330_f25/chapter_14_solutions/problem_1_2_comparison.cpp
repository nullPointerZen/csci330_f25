/*
 * Chapter 14: Iterators - Problem 1.2 Solution
 * Comparing different iteration approaches in C++
 * 
 * This solution shows three ways to iterate in C++, connecting each
 * to familiar patterns from Python and Java.
 */

#include <vector>
#include <iostream>
#include <string>

int main() {
    std::vector<std::string> languages{"Python", "Java", "C++", "JavaScript"};
    
    // Version 1: Traditional index-based approach (familiar to Java programmers)
    // Java equivalent: for(int i = 0; i < list.size(); i++)
    std::cout << "Index-based (Java-style):\n";
    for (size_t i = 0; i < languages.size(); ++i) {
        std::cout << "  " << i << ": " << languages[i] << "\n";
    }
    
    // Version 2: Iterator-based approach (explicit iterator control)
    // Java equivalent: Iterator<String> it = list.iterator(); while(it.hasNext())
    std::cout << "\nIterator-based (explicit control):\n";
    for (auto it = languages.begin(); it != languages.end(); ++it) {
        // Calculate index manually for demonstration
        size_t index = it - languages.begin();  // Random access iterator arithmetic
        std::cout << "  " << index << ": " << *it << "\n";
    }
    
    // Version 3: Range-based for loop (most Python-like)
    // Python equivalent: for i, lang in enumerate(languages):
    std::cout << "\nRange-based (Python-style):\n";
    size_t index = 0;
    for (const auto& language : languages) {
        std::cout << "  " << index++ << ": " << language << "\n";
    }
    
    // Bonus: Demonstrating when each approach is preferred
    std::cout << "\nWhen to use each approach:\n";
    std::cout << "1. Index-based: When you need the index for logic\n";
    std::cout << "2. Iterator-based: When working with STL algorithms or need iterator control\n";
    std::cout << "3. Range-based: For simple traversal (recommended default)\n";
    
    // Performance note demonstration
    std::cout << "\nPerformance considerations:\n";
    std::cout << "- All three have similar performance for vector (random access)\n";
    std::cout << "- For std::list, index-based would be O(n²), others are O(n)\n";
    std::cout << "- Range-based is generally preferred for readability\n";
    
    return 0;
}

/*
 * Expected Output:
 * Index-based (Java-style):
 *   0: Python
 *   1: Java
 *   2: C++
 *   3: JavaScript
 * 
 * Iterator-based (explicit control):
 *   0: Python
 *   1: Java
 *   2: C++
 *   3: JavaScript
 * 
 * Range-based (Python-style):
 *   0: Python
 *   1: Java
 *   2: C++
 *   3: JavaScript
 * 
 * When to use each approach:
 * 1. Index-based: When you need the index for logic
 * 2. Iterator-based: When working with STL algorithms or need iterator control
 * 3. Range-based: For simple traversal (recommended default)
 * 
 * Performance considerations:
 * - All three have similar performance for vector (random access)
 * - For std::list, index-based would be O(n²), others are O(n)
 * - Range-based is generally preferred for readability
 * 
 * Reflection for Python/Java Programmers:
 * - Range-based for feels most natural coming from Python
 * - Index-based is familiar but not always optimal in C++
 * - Iterator-based gives fine control needed for STL algorithms
 * - Choice depends on what you need to do with the elements
 */