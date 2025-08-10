# Chapter 2: Types and Memory

Welcome to C++ types and memory management! This chapter introduces fundamental concepts that distinguish C++ from Python and Java - you'll learn about static typing, direct memory control, and why these features make C++ powerful for systems programming.

## 📖 How This Chapter Works

**🔄 Learning Sequence (IMPORTANT!):**
1. **📚 FIRST**: Read Textbook Chapter 2 "Types" (2-3 hours) 
2. **🔍 SECOND**: Work through the lecture notes below for Python/Java context and hands-on practice (6-8 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (3 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 2 "Types" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Master** C++ fundamental types (int, double, char, bool) with proper declarations
2. **Create and use** static arrays with safe indexing practices
3. **Understand** basic pointer concepts and memory addresses
4. **Define** simple structs to group related data
5. **Debug** memory-related issues using VS Code's visual tools
6. **Bridge** C++ static typing concepts with your Python/Java knowledge

**⏱️ Time Budget:**
- **📚 Textbook Reading: 2-3 hours** (Chapter 2: "Types" - REQUIRED FIRST)
- **🛠️ Setup: Included in Chapter 1** (VS Code + debugger setup)
- **💻 Hands-on Work: 6-8 hours** (lecture notes + assignments)

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](../DEVELOPMENT_SETUP.md). All debugging examples use VS Code + Docker.

---

# Lecture Notes

## 🔗 Core Concepts: C++ vs Python/Java

**📖 Bridge to Textbook**: Now that you've read about C++ types in Chapter 2, let's connect those concepts to the Python/Java knowledge you already have.

### 1. Static Typing: The Big Difference

**C++ requires you to declare types explicitly and they can't change:**

```cpp
int age = 25;        // Must specify 'int'
age = "twenty-five"; // ❌ ERROR! Can't change type
```

| Aspect | C++ | Python | Java |
|--------|-----|--------|------|
| **Type Required** | ✅ Always | ❌ Dynamic | ✅ Always |
| **Type Changes** | ❌ Never | ✅ Anytime | ❌ Never |
| **Error Detection** | Compile-time | Runtime | Compile-time |

**Key Insight**: C++ is like Java's static typing but more strict. Unlike Python where `x = 5` then `x = "five"` works, C++ catches type mismatches before your program runs.

### 2. Fundamental Types

```cpp
int count = 42;          // Whole numbers (-2B to +2B roughly)
double price = 19.99;    // Decimal numbers (64-bit precision)
char grade = 'A';        // Single character (use single quotes!)
bool passed = true;      // true or false only

// Literal variations
int hex_val = 0xFF;      // Hexadecimal literal (255 in decimal)
float precise = 3.14f;   // Float literal (f suffix)
double scientific = 1e6; // Scientific notation (1,000,000)
```

| C++ Type | Memory Size | Python Equivalent | Java Equivalent |
|----------|-------------|-------------------|-----------------|
| `int` | 4 bytes | `int` | `int` |
| `double` | 8 bytes | `float` | `double` |
| `char` | 1 byte | `str[0]` (single char) | `char` |
| `bool` | 1 byte | `bool` | `boolean` |

### 3. Arrays: Fixed-Size Collections

**C++ arrays are more like hardware - fixed size, no bounds checking:**

```cpp
int scores[5];                    // Declares 5 integers (uninitialized!)
int values[] = {10, 20, 30, 40};  // Size automatically becomes 4
int zeros[10] = {};               // Zero-initialize all elements
int partial[5] = {1, 2};          // {1, 2, 0, 0, 0} - remaining zero-filled
```

| Feature | C++ Arrays | Python Lists | Java Arrays |
|---------|------------|--------------|-------------|
| **Size** | Fixed at compile time | Dynamic | Fixed at creation |
| **Bounds Check** | ❌ No safety net | ✅ IndexError | ✅ Exception |
| **Access** | `arr[0]` | `arr[0]` | `arr[0]` |
| **Length** | No built-in | `len(arr)` | `arr.length` |

**Danger Zone**: C++ won't stop you from accessing `arr[100]` on a 5-element array!

### 4. Pointers: Memory Addresses Made Visible

**Think of pointers as "explicit Java references" where you can see the memory address:**

```cpp
int value = 42;
int* ptr = &value;  // ptr holds the address of value
*ptr = 99;          // Changes value to 99 through the pointer
```

| Concept | C++ | Python | Java |
|---------|-----|--------|------|
| **Get Address** | `&variable` | Hidden | Hidden |
| **Follow Address** | `*pointer` | Automatic | Automatic |
| **Null Reference** | `nullptr` | `None` | `null` |

### 5. Structs: Simple Data Grouping

**Structs are like simplified Python classes or Java classes with all public fields:**

```cpp
struct Student {
    char name[30];
    int age;
    double gpa;
};

Student alice;
strcpy(alice.name, "Alice");  // Use strcpy for strings in C++
alice.age = 20;
alice.gpa = 3.8;
```

## 🧩 Hands-On Practice Problems

### Problem Set 1: Fundamental Types (45 minutes)

#### Problem 1.1: Type Explorer
Create a program showcasing all fundamental types:

```cpp
#include <cstdio>

int main() {
    int count = 42;
    double price = 3.14;
    char grade = 'A';
    bool passed = true;
    
    printf("Integer: %d (size: %zu bytes)\n", count, sizeof(count));
    printf("Double: %.2f (size: %zu bytes)\n", price, sizeof(price));
    printf("Character: %c (size: %zu bytes)\n", grade, sizeof(grade));
    printf("Boolean: %d (size: %zu bytes)\n", passed, sizeof(passed));
    
    // Type conversion
    printf("Conversion: %d -> %.2f\n", count, (double)count);
    
    return 0;
}
```

#### Problem 1.2: Temperature Converter Improved
Practice precision with different types:

```cpp
#include <cstdio>

int main() {
    int celsius = 25;
    
    // Calculate fahrenheit as double for precision
    double fahrenheit_double = (celsius * 9.0 / 5.0) + 32;
    int fahrenheit_int = (celsius * 9 / 5) + 32;  // Integer arithmetic
    
    printf("%d°C = %.1f°F (double)\n", celsius, fahrenheit_double);
    printf("%d°C = %d°F (int)\n", celsius, fahrenheit_int);
    
    return 0;
}
```

### Problem Set 2: Arrays and Memory (60 minutes)

#### Problem 2.1: Grade Calculator
Work with arrays safely:

```cpp
#include <cstdio>

int main() {
    const int SIZE = 5;
    int scores[SIZE] = {85, 92, 78, 96, 88};
    
    // Calculate average
    double total = 0.0;
    for (int i = 0; i < SIZE; i++) {
        total += scores[i];
    }
    double average = total / SIZE;
    
    // Find highest and lowest
    int highest = scores[0];
    int lowest = scores[0];
    for (int i = 1; i < SIZE; i++) {
        if (scores[i] > highest) highest = scores[i];
        if (scores[i] < lowest) lowest = scores[i];
    }
    
    printf("Average: %.1f\n", average);
    printf("Highest: %d\n", highest);
    printf("Lowest: %d\n", lowest);
    
    return 0;
}
```

#### Problem 2.2: Array Bounds Safety
Learn the importance of bounds checking:

```cpp
#include <cstdio>

void safe_print(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        printf("arr[%d] = %d\n", index, arr[index]);
    } else {
        printf("Index %d is out of bounds!\n", index);
    }
}

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    
    // Safe access
    for (int i = 0; i < 5; i++) {
        safe_print(arr, 5, i);
    }
    
    // Test bounds checking
    safe_print(arr, 5, 10);  // Out of bounds
    
    return 0;
}
```

### Problem Set 3: Pointers and Structs (40 minutes)

#### Problem 3.1: Pointer Basics
Master pointer syntax:

```cpp
#include <cstdio>

int main() {
    int value = 42;
    int* ptr = &value;
    
    printf("Value: %d\n", value);
    printf("Address of value: %p\n", &value);
    printf("Pointer holds: %p\n", ptr);
    printf("Pointer points to: %d\n", *ptr);
    
    // Change value through pointer
    *ptr = 99;
    printf("After *ptr = 99, value is: %d\n", value);
    
    // Null pointer safety
    ptr = nullptr;
    if (ptr != nullptr) {
        printf("Safe to dereference: %d\n", *ptr);
    } else {
        printf("ptr is null - cannot dereference\n");
    }
    
    return 0;
}
```

#### Problem 3.2: Student Record System
Combine structs, arrays, and pointers:

```cpp
#include <cstdio>
#include <cstring>

struct Student {
    char name[30];
    int age;
    double gpa;
    int courses_taken;
};

void print_student(const Student* s) {
    printf("Name: %s\n", s->name);
    printf("Age: %d\n", s->age);
    printf("GPA: %.2f\n", s->gpa);
    printf("Courses: %d\n", s->courses_taken);
    printf("---\n");
}

int main() {
    const int CLASS_SIZE = 3;
    Student students[CLASS_SIZE];
    
    // Initialize students
    strcpy(students[0].name, "Alice");
    students[0].age = 20;
    students[0].gpa = 3.8;
    students[0].courses_taken = 12;
    
    strcpy(students[1].name, "Bob");
    students[1].age = 19;
    students[1].gpa = 3.5;
    students[1].courses_taken = 10;
    
    strcpy(students[2].name, "Carol");
    students[2].age = 21;
    students[2].gpa = 3.9;
    students[2].courses_taken = 15;
    
    // Print all students
    for (int i = 0; i < CLASS_SIZE; i++) {
        print_student(&students[i]);
    }
    
    return 0;
}
```

---

# Assignments

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 2 "Types"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Assignment Structure
- **Core Assignment 1**: Type System Exploration (90 minutes) - REQUIRED
- **Core Assignment 2**: Memory and Data Structures (90 minutes) - REQUIRED  
- **Total Time**: 3 hours for both core assignments

## 🎯 Core Assignment 1: Type System Exploration (90 minutes)

### Part A: Type Discovery and Analysis (30 minutes)
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
```

### Part B: Practical Application - Multi-Unit Converter (30 minutes)
Extend your program to include a multi-unit converter that handles:

**Temperature Conversions:**
- Celsius ↔ Fahrenheit ↔ Kelvin
- Handle integer inputs but provide precise double outputs
- Show the impact of integer vs floating-point arithmetic

**Distance Conversions:**  
- Miles ↔ Kilometers ↔ Meters
- Feet ↔ Meters ↔ Inches

### Part C: Memory Behavior and Scope Analysis (30 minutes)
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

## 🎯 Core Assignment 2: Memory and Data Structures (90 minutes)

### Part A: Student Grade Management System (45 minutes)
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
8. Sort students by average grade

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
  Class Average: 88.9
```

### Part B: Advanced Memory Operations and Pointers (45 minutes)
Extend your student management program with advanced memory operations:

**Pointer Operations:**
1. Rewrite array processing functions using pointer arithmetic instead of indices
2. Create functions that take pointer parameters: `calculate_average(int* grades, size_t count)`
3. Demonstrate pointer vs array notation equivalence
4. Show memory addresses of array elements

**Advanced Array Operations:**
5. Implement a generic `safe_access` function
6. Create array copying functions using pointers
7. Implement array search functions (linear search using pointers)
8. Build a simple "database" query system (find students by ID, by grade range)

## Submission Guidelines

**For each assignment**:
1. Include source code with clear comments
2. Show compilation method used
3. Provide sample output
4. Document any challenges faced

**File organization**:
```
chapter02_solutions/
├── type_explorer.cpp
├── student_manager.cpp
└── README.md (with compilation notes)
```

---

# Quick Reference

## Top 5 Memory Errors

### 1. Uninitialized Variables
```cpp
int age;              // ❌ Random garbage value
printf("%d", age);    // Unpredictable output

int age = 0;          // ✅ Always initialize
```

### 2. Array Bounds Violation
```cpp
int arr[5] = {1,2,3,4,5};
printf("%d", arr[10]);    // ❌ Undefined behavior

// ✅ Always check bounds
if (index >= 0 && index < 5) {
    printf("%d", arr[index]);
}
```

### 3. Pointer/Value Confusion
```cpp
int value = 42;
int* ptr = &value;
printf("%d", ptr);        // ❌ Prints address, not value

printf("%d", *ptr);       // ✅ Dereference to get value
printf("%p", ptr);        // ✅ Use %p for addresses
```

### 4. String Assignment
```cpp
char name[30];
name = "Alice";           // ❌ Can't assign like Python

strcpy(name, "Alice");    // ✅ Use strcpy for strings
```

### 5. Null Pointer Dereferencing
```cpp
int* ptr = nullptr;
*ptr = 42;                // ❌ Crash! Segmentation fault

if (ptr != nullptr) {     // ✅ Always check first
    *ptr = 42;
}
```

## Format Specifiers Quick Reference

```cpp
printf("%d", int_var);        // Integer
printf("%.2f", double_var);   // Double (2 decimal places)
printf("%c", char_var);       // Character
printf("%s", string_var);     // String (char array)
printf("%p", pointer_var);    // Pointer address
printf("%zu", sizeof(var));   // Size in bytes
```

## C++ vs Python/Java Quick Comparison

| Need | C++ | Python | Java |
|------|-----|--------|------|
| **Variable** | `int x = 5;` | `x = 5` | `int x = 5;` |
| **Array** | `int arr[5];` | `arr = [1,2,3]` | `int[] arr = new int[5];` |
| **Pointer** | `int* ptr = &x;` | Hidden | Hidden |

## Success Checklist

After Chapter 2, you should be able to:
- [ ] Declare and initialize all fundamental types correctly
- [ ] Create and use arrays safely with bounds checking
- [ ] Use pointers to access and modify memory
- [ ] Define and use structs to organize data
- [ ] Debug common memory-related errors
- [ ] Understand the differences between C++ and Python/Java memory models

**Not there yet?** Review the concepts you're missing and try the problems again. Use the debugger to visualize memory - that's what makes the difference!

**Ready to move on?** Excellent! Chapter 3 will introduce references as a cleaner alternative to pointers, plus const correctness for safer code.

---

## What's Next?

**Chapter 3: References and Aliases** will cover:
- Reference variables (cleaner alternative to pointers)
- Const correctness (preventing accidental changes)  
- Pass-by-reference vs pass-by-value
- When to use references vs pointers

**You've mastered the fundamentals!** Chapter 2 is challenging because it introduces manual memory management. With this foundation, the rest of C++ will build naturally on these core concepts.

---

*Remember: C++ gives you direct control over memory - this makes it powerful and fast, but requires careful programming. Always initialize, always check bounds, always validate pointers. The debugger is your best friend!*