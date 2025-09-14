# Chapter 13: STL Containers - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 13 "STL Containers"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 2.25 hours total for all three problem sets
- Test all programs thoroughly before submission

---

## Problem Set 1: Container Basics and Sequence Containers (45 minutes)

### Problem 1.1: Vector Fundamentals (15 minutes)
**Scenario**: You're building a grade management system similar to a Python list of grades.

Create a program that:
1. Declares a `std::vector<double>` to store student grades
2. Adds at least 5 grades using `push_back()`
3. Calculates and displays the average grade
4. Finds and displays the highest grade
5. Uses both `[]` operator and `at()` method to access elements

**Python Equivalent**:
```python
grades = []
grades.append(85.5)
# ... add more grades
average = sum(grades) / len(grades)
highest = max(grades)
```

**Learning Focus**: Basic vector operations, element access methods, iteration

### Problem 1.2: Dynamic Array Operations (15 minutes)
**Scenario**: You need to manage a dynamic list of student names that can grow and shrink.

Requirements:
1. Create a `std::vector<std::string>` for student names
2. Implement functions to:
   - Add a student name to the end
   - Insert a student name at a specific position
   - Remove a student by name (use `std::find` and `erase`)
   - Display all students with their positions

**Starter Code**:
```cpp
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class StudentRoster {
private:
    std::vector<std::string> students;
public:
    void addStudent(const std::string& name);
    void insertStudent(const std::string& name, size_t position);
    void removeStudent(const std::string& name);
    void displayStudents() const;
};
```

**Learning Focus**: Vector modification operations, iterator usage, searching

### Problem 1.3: Performance Comparison (15 minutes)
**Scenario**: Compare vector and list performance for different operations.

Create a program that:
1. Creates both a `std::vector<int>` and `std::list<int>` with 10,000 elements
2. Measures time for:
   - Adding elements to the front (hint: use `insert()` for vector)
   - Adding elements to the back
   - Accessing the middle element (only possible with vector)
3. Reports which container is faster for each operation

**Timing Helper**:
```cpp
#include <chrono>

auto start = std::chrono::high_resolution_clock::now();
// ... operation to time
auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
```

**Learning Focus**: Performance characteristics, when to choose vector vs list

---

## Problem Set 2: Associative Containers (50 minutes)

### Problem 2.1: Word Frequency Counter (20 minutes)
**Scenario**: Build a word frequency analyzer like Python's `collections.Counter`.

Requirements:
1. Read words from user input (or a string) until "quit"
2. Use `std::map<std::string, int>` to count word frequencies
3. Display all words and their counts in alphabetical order
4. Find and display the most frequent word

**Python Equivalent**:
```python
from collections import Counter
words = ["apple", "banana", "apple", "cherry", "banana", "apple"]
counter = Counter(words)
most_common = counter.most_common(1)
```

**Sample Input/Output**:
```
Enter words (type 'quit' to finish):
apple banana apple cherry banana apple quit

Word frequencies:
apple: 3
banana: 2
cherry: 1

Most frequent word: apple (3 times)
```

**Learning Focus**: Map operations, key-value pairs, iteration over maps

### Problem 2.2: Set Operations (15 minutes)
**Scenario**: Implement basic set operations like Python's set type.

Create a program that:
1. Creates two `std::set<int>` objects with different numbers
2. Implements functions to find:
   - Union of two sets (elements in either set)
   - Intersection (elements in both sets)
   - Difference (elements in first set but not second)
3. Uses `std::set_union`, `std::set_intersection`, and `std::set_difference`

**Starter Code**:
```cpp
#include <set>
#include <algorithm>
#include <iterator>

std::set<int> setUnion(const std::set<int>& set1, const std::set<int>& set2);
std::set<int> setIntersection(const std::set<int>& set1, const std::set<int>& set2);
std::set<int> setDifference(const std::set<int>& set1, const std::set<int>& set2);
```

**Learning Focus**: Set operations, STL algorithms, set theory concepts

### Problem 2.3: Student Database (15 minutes)
**Scenario**: Create a student information system using multiple associative containers.

Requirements:
1. Use `std::map<int, std::string>` for student ID to name mapping
2. Use `std::map<std::string, double>` for student name to GPA mapping
3. Use `std::set<std::string>` for honor roll students (GPA >= 3.5)
4. Implement functions to:
   - Add a student with ID, name, and GPA
   - Find a student's GPA by ID
   - List all honor roll students
   - Display all students with their information

**Learning Focus**: Multiple container coordination, real-world data modeling

---

## Problem Set 3: Unordered Containers and Integration Project (50 minutes)

### Problem 3.1: Hash Performance Comparison (15 minutes)
**Scenario**: Compare performance of ordered vs unordered containers for large datasets.

Create a program that:
1. Generates 100,000 random integers
2. Inserts them into both `std::map<int, int>` and `std::unordered_map<int, int>`
3. Measures insertion time for both
4. Measures lookup time for 10,000 random searches in both
5. Reports performance differences

**Learning Focus**: Hash table performance, when to use unordered containers

### Problem 3.2: Custom Hash Function (20 minutes)
**Scenario**: Create a hash table for custom objects (similar to Python's custom `__hash__`).

Requirements:
1. Define a `Student` struct with name, ID, and major
2. Create a custom hash function for `Student`
3. Use `std::unordered_set<Student>` to store unique students
4. Implement equality operator for duplicate detection
5. Test with students having same names but different IDs

**Starter Code**:
```cpp
struct Student {
    std::string name;
    int id;
    std::string major;
    
    bool operator==(const Student& other) const;
};

struct StudentHash {
    std::size_t operator()(const Student& s) const;
};

// Usage: std::unordered_set<Student, StudentHash> students;
```

**Learning Focus**: Custom hash functions, equality operators, advanced unordered container usage

### Problem 3.3: Container Integration Project - Library Management System (15 minutes)
**Scenario**: Build a simplified library management system that demonstrates multiple container usage.

Requirements:
1. **Books**: Use `std::map<std::string, Book>` (ISBN -> Book details)
2. **Authors**: Use `std::unordered_set<std::string>` for unique author names  
3. **Categories**: Use `std::set<std::string>` for book categories (auto-sorted)
4. **Checked Out**: Use `std::unordered_map<std::string, std::string>` (ISBN -> borrower name)

Implement functions:
- `addBook(isbn, title, author, category)`
- `checkOutBook(isbn, borrower)`
- `returnBook(isbn)`
- `findBooksByAuthor(author)` -> returns vector of books
- `listCategories()` -> shows all categories in alphabetical order
- `showCheckedOutBooks()` -> shows all currently borrowed books

**Book Structure**:
```cpp
struct Book {
    std::string title;
    std::string author;
    std::string category;
    bool isAvailable = true;
};
```

**Learning Focus**: Container selection for real scenarios, integration of multiple containers, practical system design

---

## Debugging Challenges (Extra Credit - 15 minutes)

### Challenge 1: Iterator Invalidation Bug
Find and fix the bug in this code:
```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
for (auto it = numbers.begin(); it != numbers.end(); ++it) {
    if (*it % 2 == 0) {
        numbers.erase(it);  // Bug: What's wrong here?
    }
}
```

### Challenge 2: Map Access Bug  
Find and fix the bug in this code:
```cpp
std::map<std::string, int> scores;
// ... add some scores
std::string name = "John";
if (scores[name] > 0) {  // Bug: What's the issue?
    std::cout << name << " has a positive score\n";
}
```

---


## Compilation Instructions

**Choose your workflow:**

**Docker/Command Line:**
```bash
g++ -std=c++17 -Wall -Wextra -g -o containers_program program.cpp
```

**VS Code (any workflow):**
- Press `Ctrl+Shift+B` (or `Cmd+Shift+B` on macOS)
- Or use Terminal → Run Build Task

**VS Code Container Debugging Tips:**
- Use Variables panel to see container contents and sizes
- Watch container growth during insertions
- Debug performance comparisons with timing measurements
- Monitor memory usage patterns with different containers

---

## Time Management Tips
- **Problem Set 1**: Focus on getting basic operations working first, then optimize
- **Problem Set 2**: Start with simple test cases, then expand functionality  
- **Problem Set 3**: Plan your data structures before coding, think about which container fits each need
- **If stuck**: Review the Python/Java equivalents to understand the concept, then translate to C++