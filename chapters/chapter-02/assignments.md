# Chapter 2: Types - Problem Sets

## 📋 Before You Begin

**⚠️ Prerequisites Checklist - Complete ALL before starting assignments:**

- [ ] **📚 Textbook Reading**: Completed Chapter 2 "Types" (Josh Lospinoso explains memory management brilliantly - this is essential for success)
- [ ] **🔍 Lecture Notes**: Reviewed chapter_02_lecture_notes.md with all hands-on problems
- [ ] **🛠️ Development Environment**: VS Code + debugging setup ready from DEVELOPMENT_SETUP.md
- [ ] **📝 Knowledge Check**: Can explain the difference between C++ static typing and Python/Java
- [ ] **⚙️ Compiler Test**: Successfully compiled and debugged a simple program with variables and arrays

**🚀 Ready to Start**: All checkboxes above are marked? Great! These assignments will solidify your understanding through comprehensive practice.

**⚠️ WARNING**: Do NOT attempt these assignments without completing the textbook reading first. Memory management concepts are complex and require the foundation the textbook provides.

---

## ✨ Streamlined Assignment Structure
**New Approach**: 2 comprehensive assignments instead of 8 micro-problems
- **Core Assignment 1**: Type System Exploration (60 minutes) - REQUIRED
- **Core Assignment 2**: Memory and Data Structures (75 minutes) - REQUIRED  
- **Challenge Exercises**: Additional problems for advanced students - OPTIONAL

**Total Core Time**: 2.25 hours

---

## 🎯 Core Assignment 1: Type System Exploration (60 minutes)
*Comprehensive project combining fundamental types, conversions, and practical applications*

### Part A: Type Discovery and Analysis (30 minutes)
**Objective**: Build a comprehensive understanding of C++ type system through systematic exploration

Create a program called `type_explorer.cpp` that:

**Basic Type Analysis:**
1. Declare and initialize variables of each fundamental type: `int`, `double`, `char`, `bool`, `long`, `float`
2. Use `sizeof` to show the size in bytes of each type
3. Display the range limits using `<climits>` and `<cfloat>` (e.g., `INT_MAX`, `DBL_MAX`)
4. Show both positive and negative values for signed types

**Type Conversion Investigation:**
5. Demonstrate implicit conversions (int to double, char to int, etc.)
6. Show explicit casting with `static_cast<>`
7. Demonstrate information loss in narrowing conversions
8. Compare conversion results with and without explicit casting

**Expected Output** (partial example):
```
=== C++ Type System Analysis ===
Fundamental Types:
  int: 42 (size: 4 bytes, range: -2147483648 to 2147483647)
  double: 3.14159 (size: 8 bytes, precision: ~15-17 digits)
  char: 'A' (size: 1 byte, ASCII: 65)
  bool: true (size: 1 byte, values: 0 or 1)
  
Type Conversions:
  int(42) -> double: 42.000000 (no loss)
  double(3.14159) -> int: 3 (precision lost!)
  char('A') -> int: 65 (ASCII value)
  
Explicit vs Implicit:
  Implicit: 42 + 3.14 = 45.14 (int promoted to double)
  Explicit: static_cast<int>(3.14) = 3
```

### Part B: Practical Application - Multi-Unit Converter (30 minutes)
**Objective**: Apply type knowledge in a comprehensive conversion utility

Extend your program to include a multi-unit converter that handles:

**Temperature Conversions:**
- Celsius ↔ Fahrenheit ↔ Kelvin
- Handle integer inputs but provide precise double outputs
- Show the impact of integer vs floating-point arithmetic

**Distance Conversions:**  
- Miles ↔ Kilometers ↔ Meters
- Feet ↔ Meters ↔ Inches

**Requirements:**
1. Use appropriate types for each unit (int for counts, double for precise measurements)
2. Demonstrate the difference between integer and floating-point division
3. Format output with appropriate precision
4. Handle common conversion scenarios with test cases

### Part C: Memory Behavior and Scope Analysis (30 minutes)
**Objective**: Explore memory behavior, initialization, and scope rules

Create a comprehensive analysis program that demonstrates:

**Initialization Behavior:**
1. Uninitialized local variables (show unpredictable values)
2. Global variable auto-initialization (show zero-initialization)
3. Const variable initialization requirements
4. Impact of uninitialized variables on program behavior

**Scope Investigation:**
5. Global vs local variable precedence
6. Block scope with nested braces `{ }`
7. Variable shadowing in different scopes
8. Lifetime differences between stack and global variables

**Memory Layout:**
9. Compare addresses of global vs local variables
10. Show how local variables get different addresses in different function calls

**Safety Analysis:**
11. Compile with warnings enabled (`-Wall -Wuninitialized`)
12. Document which initialization errors the compiler catches vs misses

**Files**: `type_explorer.cpp`
**Time Estimate**: 90 minutes total
**Skills Developed**: Type system mastery, conversion understanding, scope awareness, debugging mindset

---

## 🎯 Core Assignment 2: Memory and Data Structures (75 minutes)
*Comprehensive project integrating arrays, pointers, and structs for real-world data management*

### Part A: Student Grade Management System (40 minutes)
**Objective**: Build a comprehensive grade management system using arrays, pointers, and structs

Create a program called `student_manager.cpp` that manages multiple students and their grades:

**Data Structures:**
1. Create a `Student` struct with: name (char array), student_id (int), grades array, grade_count
2. Create an array to store multiple students (at least 3 students)
3. Use both stack arrays and demonstrate pointer arithmetic

**Core Functionality:**
4. Initialize sample data for 3 students with varying numbers of grades
5. Calculate individual student averages using pointer arithmetic
6. Find class-wide statistics (highest/lowest individual averages, overall class average)
7. Implement safe array access with bounds checking
8. Sort students by average grade (simple bubble sort)

**Memory Safety:**
9. Demonstrate safe vs unsafe array access
10. Show what happens with out-of-bounds access (controlled demonstration)
11. Use assert() statements for debugging array bounds

**Expected Output** (partial):
```
=== Student Grade Management System ===
Student: Alice Johnson (ID: 1001)
  Grades: [85, 92, 78, 96, 88]
  Average: 87.8
  
Student: Bob Smith (ID: 1002)  
  Grades: [90, 87, 93]
  Average: 90.0
  
Class Statistics:
  Highest Average: Bob Smith (90.0)
  Lowest Average: Alice Johnson (87.8)
  Class Average: 88.9
  
[Memory Safety Demo]
  Safe access: grades[2] = 78
  Unsafe access: grades[10] = [undefined/crash]
```

### Part B: Advanced Memory Operations and Pointers (45 minutes)
**Objective**: Master pointer arithmetic, memory layout, and dynamic operations

Extend your student management program with advanced memory operations:

**Pointer Operations:**
1. Rewrite array processing functions using pointer arithmetic instead of indices
2. Create functions that take pointer parameters: `calculate_average(int* grades, size_t count)`
3. Demonstrate pointer vs array notation equivalence
4. Show memory addresses of array elements (demonstrate contiguous layout)

**Advanced Array Operations:**
5. Implement a generic `safe_access` function template that works with any array type
6. Create array copying functions using pointers
7. Implement array search functions (linear search using pointers)
8. Build a simple "database" query system (find students by ID, by grade range)

**Memory Layout Investigation:**
9. Print addresses of struct members to understand memory layout
10. Show the difference between array of structs vs struct of arrays
11. Demonstrate memory alignment concepts with sizeof() on structs

**Error Handling:**
12. Implement comprehensive bounds checking for all array operations
13. Create error reporting system (error codes vs exceptions preview)
14. Build defensive programming practices into all functions

**Files**: `student_manager.cpp` (extended from Part A)
**Time Estimate**: 90 minutes total (45 + 45)
**Skills Developed**: Memory management, pointer arithmetic, struct design, defensive programming

---

## 🏆 Challenge Exercises (OPTIONAL - for advanced students)
*These problems provide additional practice but are not required for core competency*

### Challenge 1: Multi-dimensional Arrays (25 minutes)
**Objective**: Master 2D arrays and matrix operations

Create an advanced gradebook with matrix-style operations:
1. Create a flexible gradebook supporting variable numbers of students and assignments
2. Implement matrix-style operations (row sums, column sums, transpose)
3. Add grade curve calculations (add points to all grades, percentage scaling)
4. Build a formatted report generator with proper alignment
5. Implement simple statistical analysis (standard deviation, grade distribution)

### Challenge 2: Dynamic Inventory System (30 minutes)
**Objective**: Advanced struct design with complex data relationships

Build an inventory management system:
1. Create nested struct hierarchy (Product -> Category -> Inventory)
2. Implement search and filtering capabilities
3. Add data validation and error handling
4. Create formatted reporting system
5. Demonstrate complex pointer relationships

### Challenge 3: Memory Debugging Workshop (20 minutes)
**Objective**: Master debugging techniques for memory-related issues

Create programs that demonstrate common memory bugs:
1. Buffer overflow demonstrations (controlled)
2. Uninitialized variable detection
3. Array bounds violation analysis
4. Memory layout visualization
5. Debugging with sanitizers and static analysis tools

### Challenge 4: Performance Optimization (25 minutes)
**Objective**: Understand performance implications of different approaches

Compare performance of different implementations:
1. Array access patterns (sequential vs random)
2. Pointer arithmetic vs array indexing
3. Struct layout optimization (memory alignment)
4. Cache-friendly data structures
5. Compiler optimization analysis

### Challenge 5: Cross-Platform Type Behavior (20 minutes)
**Objective**: Understand platform-dependent behavior

Explore how types behave across different systems:
1. Size differences on different architectures
2. Endianness investigation
3. Signed vs unsigned behavior differences
4. Floating-point precision across platforms
5. Compiler-specific behavior analysis

### Challenge 6: Advanced Type Safety (30 minutes)
**Objective**: Build type-safe programming patterns

Implement advanced safety mechanisms:
1. Strong typing with custom types
2. Compile-time size checking for arrays
3. Safe casting mechanisms
4. Type-safe printf alternatives
5. Runtime type information (RTTI) exploration

---

## 🎯 Success Criteria

Before moving to Chapter 3, you should be able to:

**Type System Mastery:**
- [ ] Explain the difference between all fundamental C++ types
- [ ] Predict the results of implicit and explicit type conversions
- [ ] Use appropriate types for different programming scenarios
- [ ] Debug type-related compilation errors

**Memory and Data Structure Competency:**
- [ ] Create and manipulate arrays safely with bounds checking
- [ ] Use pointer arithmetic confidently for array operations
- [ ] Design and implement struct-based data organization
- [ ] Understand memory layout and address relationships

**Professional Development Skills:**
- [ ] Write defensive code that handles edge cases
- [ ] Use debugging tools effectively to understand program behavior
- [ ] Document code clearly for future maintenance
- [ ] Follow consistent coding style and organization

**Problem-Solving Approach:**
- [ ] Break complex problems into manageable components
- [ ] Implement systematic testing and verification
- [ ] Handle errors gracefully with appropriate feedback
- [ ] Optimize solutions for both correctness and clarity

---

## 💡 Study Tips

### For Core Assignments:
- **Start Early**: These are comprehensive projects, not quick exercises
- **Test Incrementally**: Build and test each part before moving to the next
- **Use the Debugger**: Visual debugging is essential for understanding memory concepts
- **Ask Questions**: Don't struggle alone - use office hours and study groups

### For Challenge Exercises:
- **Choose Based on Interest**: Pick challenges that align with your career goals
- **Focus on Learning**: Perfect solutions aren't required - demonstrate understanding
- **Document Your Process**: Explain what you learned and what was difficult
- **Share with Peers**: Help others and learn from different approaches

### Time Management:
- **Week 1**: Complete Core Assignment 1 (Type System Exploration)
- **Week 2**: Complete Core Assignment 2 (Memory and Data Structures)
- **Bonus Time**: Work on Challenge Exercises if time permits

Remember: The goal is deep understanding, not speed. Take the time you need to truly master these foundational concepts.