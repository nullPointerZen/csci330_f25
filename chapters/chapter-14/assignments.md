# Chapter 14: Iterators - Problem Sets

## Instructions
- Complete these problems after reading Chapter 14
- Each problem builds understanding of iterator concepts and usage
- **Time expectation**: 2.25 hours total for all three problem sets
- Focus on connecting iterator concepts to your Python/Java experience

---

## Problem Set 1: Iterator Basics (45 minutes)

### Problem 1.1: First Steps with Iterators
**Objective**: Understand basic iterator operations

Given this vector, use iterators to accomplish the tasks:
```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers{10, 20, 30, 40, 50};
    
    // TODO: Use iterators to complete these tasks:
    // 1. Print the first element using an iterator
    // 2. Print the last element using an iterator  
    // 3. Print all elements using a traditional iterator loop
    
    return 0;
}
```

**Python Connection**: This is like using `iter()` and `next()` in Python, but more explicit.

**Expected Output**:
```
First: 10
Last: 50
All: 10 20 30 40 50
```

### Problem 1.2: Iterator vs Index Comparison
**Objective**: Compare different ways to access container elements

Complete both versions of this program:
```cpp
#include <vector>
#include <iostream>
#include <string>

int main() {
    std::vector<std::string> languages{"Python", "Java", "C++", "JavaScript"};
    
    // Version 1: Traditional index-based approach (like Java)
    std::cout << "Index-based:\n";
    // TODO: Print all elements using indices
    
    // Version 2: Iterator-based approach  
    std::cout << "Iterator-based:\n";
    // TODO: Print all elements using iterators
    
    // Version 3: Range-based for loop (like Python)
    std::cout << "Range-based:\n";
    // TODO: Print all elements using range-based for
    
    return 0;
}
```

**Reflection**: Which approach feels most natural coming from Python/Java? Why?

### Problem 1.3: Iterator Arithmetic
**Objective**: Practice moving through containers with iterators

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> data{1, 3, 5, 7, 9, 11, 13, 15};
    
    // TODO: Using iterators, accomplish these tasks:
    // 1. Print the element at position 3 (should be 7)
    // 2. Print every other element starting from the beginning
    // 3. Print the last 3 elements
    
    return 0;
}
```

**Hint**: Remember that `begin() + n` moves n positions forward.

---

## Problem Set 2: Range-Based For Loops and Practical Usage (45 minutes)

### Problem 2.1: Modernizing Loops
**Objective**: Convert traditional loops to range-based for loops

Rewrite these traditional loops using range-based for loops:

```cpp
#include <vector>
#include <iostream>
#include <string>

void old_style_examples() {
    std::vector<double> grades{85.5, 92.0, 78.5, 96.0, 88.5};
    
    // Old style 1: Index-based
    std::cout << "Grades: ";
    for(size_t i = 0; i < grades.size(); ++i) {
        std::cout << grades[i] << " ";
    }
    std::cout << "\n";
    
    // Old style 2: Iterator-based
    double total = 0.0;
    for(auto it = grades.begin(); it != grades.end(); ++it) {
        total += *it;
    }
    std::cout << "Average: " << total / grades.size() << "\n";
}

int main() {
    // TODO: Rewrite the above function using range-based for loops
    // Name your new function: modern_style_examples()
    
    old_style_examples();
    // modern_style_examples();  // Uncomment when ready
    
    return 0;
}
```

**Python Note**: Your range-based for loops should feel very similar to Python's `for item in list` syntax.

### Problem 2.2: Modifying Elements
**Objective**: Use range-based for loops to modify container contents

```cpp
#include <vector>
#include <iostream>
#include <string>

int main() {
    // Task 1: Double all numbers
    std::vector<int> numbers{1, 2, 3, 4, 5};
    // TODO: Use range-based for to double each number
    
    // Task 2: Convert strings to uppercase (first character only)
    std::vector<std::string> words{"hello", "world", "cpp", "iterators"};
    // TODO: Use range-based for to capitalize first letter of each word
    
    // Task 3: Count positive numbers
    std::vector<int> mixed{-5, 3, -1, 8, 0, -2, 7};
    int positive_count = 0;
    // TODO: Use range-based for to count positive numbers
    
    // Print results to verify
    std::cout << "Doubled numbers: ";
    for(const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    
    return 0;
}
```

**Key Concept**: Use `auto&` to modify, `const auto&` to read-only.

### Problem 2.3: Reference Semantics Practice
**Objective**: Understand when to use references vs copies

Fill in the blanks with the correct range-based for loop syntax:

```cpp
#include <vector>
#include <iostream>
#include <string>

int main() {
    std::vector<std::string> names{"Alice", "Bob", "Charlie", "Diana"};
    
    // Scenario 1: Just reading/printing (most efficient?)
    std::cout << "Names: ";
    for(_______ name : names) {  // Fill in the blank
        std::cout << name << " ";
    }
    std::cout << "\n";
    
    // Scenario 2: Modifying each element
    std::cout << "Adding exclamation marks:\n";
    for(_______ name : names) {  // Fill in the blank
        name += "!";
        std::cout << name << "\n";
    }
    
    // Scenario 3: Expensive copy objects (what if names were large objects?)
    std::cout << "Efficient reading:\n";
    for(_______ name : names) {  // Fill in the blank
        std::cout << "Hello, " << name << "\n";
    }
    
    return 0;
}
```

**Think About**: What's the performance difference between your three approaches?

---

## Problem Set 3: Advanced Iterator Patterns (55 minutes)

### Problem 3.1: Custom Iterator Functions
**Objective**: Implement useful functions using iterators

Create these utility functions:

```cpp
#include <vector>
#include <iostream>

// TODO: Implement this function using iterators
template<typename Container, typename T>
bool contains(const Container& container, const T& value) {
    // Return true if container contains value, false otherwise
    // Hint: Use iterators to search through the container
}

// TODO: Implement this function using iterators  
template<typename Container, typename T>
size_t count_occurrences(const Container& container, const T& value) {
    // Count how many times value appears in container
    // Use iterators to traverse and count
}

// TODO: Implement this function using iterators
template<typename Container>
void print_reverse(const Container& container) {
    // Print container elements in reverse order
    // Hint: Some containers support reverse iterators (rbegin, rend)
}

int main() {
    std::vector<int> data{1, 3, 7, 3, 9, 3, 5};
    
    // Test your functions
    std::cout << "Contains 7: " << contains(data, 7) << "\n";
    std::cout << "Contains 4: " << contains(data, 4) << "\n";
    std::cout << "Count of 3: " << count_occurrences(data, 3) << "\n";
    std::cout << "Reverse: ";
    print_reverse(data);
    std::cout << "\n";
    
    return 0;
}
```

**Challenge**: Can you make these work with different container types (vector, list, array)?

### Problem 3.2: Safe Container Modification
**Objective**: Handle iterator invalidation correctly

Fix this buggy code that tries to remove even numbers:

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // BUGGY CODE - Don't run this as-is!
    // for(auto it = numbers.begin(); it != numbers.end(); ++it) {
    //     if(*it % 2 == 0) {
    //         numbers.erase(it);  // This invalidates the iterator!
    //     }
    // }
    
    // TODO: Fix the above code to safely remove even numbers
    // Hint: erase() returns an iterator to the next element
    
    std::cout << "Odd numbers remaining: ";
    for(const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    
    return 0;
}
```

**Expected Output**: `Odd numbers remaining: 1 3 5 7 9`

### Problem 3.3: Multi-Container Iterator Project
**Objective**: Work with multiple containers and iterator patterns

Create a simple gradebook system:

```cpp
#include <vector>
#include <iostream>
#include <string>

struct Student {
    std::string name;
    std::vector<double> grades;
    
    // TODO: Add a method to calculate average grade using iterators
    double calculate_average() const {
        // Use iterators to sum grades and return average
    }
};

int main() {
    std::vector<Student> class_roster{
        {"Alice", {85.0, 92.0, 78.0, 95.0}},
        {"Bob", {88.0, 76.0, 92.0, 85.0}},
        {"Charlie", {92.0, 88.0, 95.0, 90.0}}
    };
    
    // TODO: Using iterators and/or range-based for loops:
    // 1. Print each student's name and average grade
    // 2. Find the student with the highest average
    // 3. Count how many students have an average above 85.0
    
    return 0;
}
```

**Integration Challenge**: This combines containers (vector), custom types (Student), and multiple iteration patterns.

---

## Debugging and Reflection Questions

### Common Iterator Mistakes
For each code snippet, identify the problem and propose a fix:

1. **Off-by-one Error**:
```cpp
for(auto it = vec.begin(); it <= vec.end(); ++it) {  // What's wrong?
    std::cout << *it << " ";
}
```

2. **Iterator Invalidation**:
```cpp
for(auto it = vec.begin(); it != vec.end(); ++it) {
    vec.push_back(*it * 2);  // What's wrong?
}
```

3. **Mismatched Iterator Types**:
```cpp
std::vector<int> vec{1, 2, 3};
std::vector<double> other{4.0, 5.0, 6.0};
auto it = vec.begin();
auto end = other.end();  // What's wrong?
for(; it != end; ++it) { /* ... */ }
```

### Reflection Questions
1. **Python Connection**: How do C++ iterators compare to Python's `iter()` and `next()` functions?
2. **Java Connection**: How do C++ iterators differ from Java's Iterator interface?
3. **Performance**: When might traditional iterators be preferred over range-based for loops?
4. **Design**: Why do you think C++ uses "one past the end" for the end iterator?

---

## Compilation Instructions

**Choose your workflow:**

**Docker/Command Line:**
```bash
g++ -std=c++17 -Wall -Wextra -g -o iterators_program program.cpp
```

**VS Code (any workflow):**
- Press `Ctrl+Shift+B` (or `Cmd+Shift+B` on macOS)
- Or use Terminal → Run Build Task

**VS Code Iterator Debugging Tips:**
- Use Variables panel to see iterator positions and values
- Step through iterator operations to understand traversal
- Watch iterator arithmetic and comparisons
- Debug range-based for loops to see iterator usage internally

---

## Submission Guidelines

**For each problem set**:
1. Include working source code with comments explaining your approach
2. Show expected output for test cases
3. Note any connections you see to Python/Java iteration patterns
4. Document any challenges with iterator concepts

**File organization**:
```
chapter14_solutions/
├── problem_set_1/
│   ├── problem_1_1_iterator_basics.cpp
│   ├── problem_1_2_comparison.cpp
│   └── problem_1_3_arithmetic.cpp
├── problem_set_2/
│   ├── problem_2_1_modernizing.cpp
│   ├── problem_2_2_modifying.cpp
│   └── problem_2_3_references.cpp
├── problem_set_3/
│   ├── problem_3_1_custom_functions.cpp
│   ├── problem_3_2_safe_modification.cpp
│   └── problem_3_3_gradebook.cpp
└── README.md (with compilation notes and reflections)
```

**Expected time commitment**: 2.25 hours total. Ask for help if you're spending significantly more time!