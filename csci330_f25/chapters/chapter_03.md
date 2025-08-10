# Chapter 3: References and Aliases

Welcome to C++ references! References provide a cleaner, safer alternative to pointers for creating aliases to existing variables. This chapter will show you how to use references effectively and when they're better than pointers.

## 📖 How This Chapter Works

**🔄 Learning Sequence (IMPORTANT!):**
1. **📚 FIRST**: Read Textbook Chapter 3 "References and Aliases" (1-2 hours)
2. **🔍 SECOND**: Work through the lecture notes below for Python/Java context and hands-on practice (4.5 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 3 "References and Aliases" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Create and use references** - Cleaner alternatives to pointers for aliasing variables
2. **Master const correctness** - Prevent accidental modifications with const references
3. **Distinguish references from pointers** - Know when to use each approach
4. **Debug reference errors** - Fix common binding and initialization issues
5. **Apply references in functions** - Pass parameters efficiently and safely

**⏱️ Time Budget:**
- **📚 Textbook Reading: 1-2 hours** (Chapter 3: "References and Aliases" - REQUIRED FIRST)
- **🛠️ Setup: Included in Chapter 1** (VS Code + debugger setup)
- **💻 Hands-on Work: 4.5 hours** (lecture notes + assignments)

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](../DEVELOPMENT_SETUP.md). All debugging examples use VS Code + Docker.

---

# Lecture Notes

## 🔗 Core Concepts: References vs Python/Java

**📖 Bridge to Textbook**: Now that you've read about references as aliases in Chapter 3, let's connect those concepts to the Python/Java knowledge you already have.

### 1. What Are References?

**References are permanent aliases to existing variables:**

```cpp
int score = 85;
int& score_ref = score;  // score_ref is now another name for score

score_ref = 92;          // Changes score to 92
printf("%d", score);     // Prints 92
```

**Think of it as**: Having two names for the same person - changing one changes the other because they're the same entity.

| Aspect | C++ References | Python Variables | Java Object References |
|--------|----------------|------------------|----------------------|
| **Nature** | Permanent alias | Rebindable name | Rebindable reference |
| **Reassignment** | ❌ Cannot reassign | ✅ Can reassign | ✅ Can reassign |
| **Initialization** | ✅ Must initialize | ✅ Created on assignment | ✅ Can be null initially |

### 2. References vs Pointers: The Key Differences

```cpp
int value = 42;

// Pointer approach
int* ptr = &value;    // Holds address
*ptr = 99;           // Dereference to change value

// Reference approach  
int& ref = value;    // Direct alias
ref = 99;           // No dereferencing needed
```

| Feature | References | Pointers |
|---------|------------|----------|
| **Syntax** | `int& ref = var;` | `int* ptr = &var;` |
| **Access** | `ref = 10;` | `*ptr = 10;` |
| **Null values** | ❌ Cannot be null | ✅ Can be `nullptr` |
| **Reassignment** | ❌ Cannot reassign | ✅ Can point elsewhere |
| **Initialization** | ✅ Must initialize | ❌ Can declare uninitialized |

**When to use which:**
- **References**: When you want a clean alias and won't reassign
- **Pointers**: When you need reassignment or might have null values

### 3. Const Correctness with References

**Const references prevent modification:**

```cpp
int value = 100;
const int& readonly_ref = value;

readonly_ref = 200;  // ❌ Error! Cannot modify
value = 200;         // ✅ OK, modify through original variable
```

**Const references are great for:**
- Function parameters (avoid copying large objects)
- Temporary values (like literals)
- Read-only access to data

```cpp
const int& temp_ref = 42;  // ✅ OK - const can bind to temporaries
int& bad_ref = 42;         // ❌ Error! Non-const cannot bind to temporaries
```

### 4. Auto Type Deduction with References

**The `auto` keyword can automatically deduce reference types:**

```cpp
int value = 42;
int& ref = value;

auto copy = value;        // auto deduces int (copy)
auto& auto_ref = value;   // auto deduces int& (reference)
const auto& const_ref = value;  // auto deduces const int& (const reference)
```

**Auto with References Rules:**
- `auto` by itself makes a copy (removes reference)
- `auto&` preserves the reference
- `const auto&` creates a const reference (great for function parameters)

### 5. References in Functions

**Pass by reference avoids copying:**

```cpp
// Instead of copying the entire struct
void print_student_copy(Student s) {  // Slow - copies all data
    printf("Name: %s\n", s.name);
}

// Use const reference for read-only
void print_student_ref(const Student& s) {  // Fast - no copying
    printf("Name: %s\n", s.name);
}

// Use non-const reference for modification
void update_gpa(Student& s, double new_gpa) {
    s.gpa = new_gpa;  // Modifies original
}
```

**Python/Java Bridge**: This is like passing objects in Python/Java - you get the original, not a copy.

## 🧩 Hands-On Practice Problems

### Problem Set 1: Basic References (45 minutes)

#### Problem 1.1: Reference Fundamentals
Master the basics of reference creation:

```cpp
#include <cstdio>

int main() {
    int score = 85;
    int& score_ref = score;
    
    printf("Original score: %d, Reference: %d\n", score, score_ref);
    
    // Modify score through the reference
    score_ref = 92;
    
    printf("Modified score: %d, Reference: %d\n", score, score_ref);
    
    return 0;
}
```

**Expected Output:**
```
Original score: 85, Reference: 85
Modified score: 92, Reference: 92
```

#### Problem 1.2: References vs Copies
Understand that references are aliases, not copies:

```cpp
#include <cstdio>

int main() {
    int original = 100;
    
    int copy_val = original;    // Independent copy
    int& ref_val = original;    // Alias to original
    
    original = 200;
    
    printf("Original: %d, Copy: %d, Reference: %d\n", 
           original, copy_val, ref_val);
    
    return 0;
}
```

**Expected Output:**
```
Original: 200, Copy: 100, Reference: 200
```

### Problem Set 2: Const References (45 minutes)

#### Problem 2.1: Read-only References
Practice const reference usage:

```cpp
#include <cstdio>

void print_value(const int& val) {
    printf("Value is: %d\n", val);
}

int main() {
    int number = 42;
    
    print_value(number);    // Pass variable
    print_value(99);        // Pass literal
    
    // Const references can bind to temporaries
    const int& temp_ref = number + 10;
    printf("Temporary result: %d\n", temp_ref);
    
    return 0;
}
```

#### Problem 2.2: Modifying Through References
Learn when const is needed and when it's not:

```cpp
#include <cstdio>

void double_value(int& val) {
    val *= 2;  // Modifies the original
}

void show_value(const int& val) {
    printf("Current value: %d\n", val);
}

int main() {
    int number = 25;
    
    show_value(number);
    double_value(number);
    show_value(number);
    
    return 0;
}
```

### Problem Set 3: Advanced References (55 minutes)

#### Problem 3.1: Reference Return Types
Understand functions that return references:

```cpp
#include <cstdio>

int global_counter = 0;

// Returns reference to global variable
int& get_counter() {
    return global_counter;
}

// Returns reference to array element
int& get_element(int arr[], int index) {
    return arr[index];
}

int main() {
    // Use get_counter to modify global_counter
    get_counter() = 10;
    printf("Counter: %d\n", global_counter);
    
    // Use get_element to modify array elements
    int numbers[5] = {1, 2, 3, 4, 5};
    get_element(numbers, 2) = 99;
    
    printf("Array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    return 0;
}
```

#### Problem 3.2: Student Record System
Combine structs, references, and functions:

```cpp
#include <cstdio>
#include <cstring>

struct Student {
    char name[30];
    int age;
    double gpa;
};

void print_student(const Student& s) {
    printf("Name: %s, Age: %d, GPA: %.2f\n", s.name, s.age, s.gpa);
}

void update_gpa(Student& s, double new_gpa) {
    s.gpa = new_gpa;
}

bool is_honor_student(const Student& s) {
    return s.gpa >= 3.5;
}

int main() {
    Student alice;
    strcpy(alice.name, "Alice Johnson");
    alice.age = 20;
    alice.gpa = 3.2;
    
    print_student(alice);
    printf("Honor student: %s\n", is_honor_student(alice) ? "Yes" : "No");
    
    update_gpa(alice, 3.8);
    print_student(alice);
    printf("Honor student: %s\n", is_honor_student(alice) ? "Yes" : "No");
    
    return 0;
}
```

---

# Assignments

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 3 "References and Aliases"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Problem Set 1: Basic References (45 minutes)

### Problem 1.1: Reference Fundamentals (15 minutes)
**Objective**: Understand reference creation and basic usage

Create a program that demonstrates basic reference usage:

```cpp
#include <cstdio>

int main() {
    // TODO: Create an integer variable 'score' with value 85
    // TODO: Create a reference 'score_ref' that refers to 'score'
    // TODO: Print both score and score_ref
    // TODO: Modify score through score_ref to 92
    // TODO: Print both values again to show they're the same
    
    return 0;
}
```

**Expected Output:**
```
Original score: 85, Reference: 85
Modified score: 92, Reference: 92
```

### Problem 1.2: References vs Copies (15 minutes)
**Objective**: Understand that references are aliases, not copies

Write a program that shows the difference between references and copies:

```cpp
#include <cstdio>

int main() {
    int original = 100;
    
    // TODO: Create a copy of original called 'copy_val'
    // TODO: Create a reference to original called 'ref_val'
    // TODO: Modify original to 200
    // TODO: Print all three values to show the difference
    
    return 0;
}
```

**Expected Output:**
```
Original: 200, Copy: 100, Reference: 200
```

### Problem 1.3: Multiple References (15 minutes)
**Objective**: Multiple references can refer to the same object

Create a program where multiple references point to the same variable:

```cpp
#include <cstdio>

int main() {
    int shared_value = 50;
    
    // TODO: Create two different references to shared_value
    // TODO: Modify shared_value through the first reference
    // TODO: Print the value using the second reference
    // TODO: Show that all three (original + 2 references) have the same value
    
    return 0;
}
```

## Problem Set 2: Const References and Functions (45 minutes)

### Problem 2.1: Const Reference Parameters (20 minutes)
**Objective**: Use const references for read-only function parameters

Create a program with functions that use const references:

```cpp
#include <cstdio>

struct Student {
    char name[50];
    int age;
    double gpa;
};

// TODO: Write a function 'display_student' that takes a const Student reference
// and prints the student's information

// TODO: Write a function 'is_honor_student' that takes a const Student reference
// and returns true if GPA >= 3.5

int main() {
    Student alice = {"Alice Johnson", 20, 3.8};
    
    // TODO: Call both functions with alice
    
    return 0;
}
```

**Expected Output:**
```
Student: Alice Johnson, Age: 20, GPA: 3.80
Alice is an honor student: Yes
```

### Problem 2.2: Modifying Through Non-Const References (25 minutes)
**Objective**: Use non-const references to modify objects in functions

Extend the previous program:

```cpp
#include <cstdio>
#include <cstring>

struct Student {
    char name[50];
    int age;
    double gpa;
};

// TODO: Keep your display_student and is_honor_student functions from 2.1

// TODO: Write a function 'update_gpa' that takes a Student reference (non-const)
// and a new GPA value, then updates the student's GPA

// TODO: Write a function 'celebrate_birthday' that takes a Student reference
// and increments their age by 1

int main() {
    Student bob = {"Bob Smith", 19, 3.2};
    
    // TODO: Display Bob's initial info
    // TODO: Update Bob's GPA to 3.6
    // TODO: Celebrate Bob's birthday
    // TODO: Display Bob's updated info
    // TODO: Check if Bob is now an honor student
    
    return 0;
}
```

**Expected Output:**
```
Initial - Student: Bob Smith, Age: 19, GPA: 3.20
Bob is an honor student: No
Updated - Student: Bob Smith, Age: 20, GPA: 3.60
Bob is an honor student: Yes
```

## Problem Set 3: Advanced References and Object Lifecycle (55 minutes)

### Problem 3.1: Reference Return Types (25 minutes)
**Objective**: Understand functions that return references

Create a program that demonstrates reference return types:

```cpp
#include <cstdio>

struct BankAccount {
    double balance;
    int account_number;
};

// TODO: Write a function 'get_balance' that takes a const BankAccount reference
// and returns a const reference to the balance

// TODO: Write a function 'get_account_for_update' that takes an array of BankAccount
// and an account number, then returns a reference to the matching account
// (For simplicity, assume the account exists and is at index = account_number - 1)

int main() {
    BankAccount accounts[3] = {
        {1000.50, 1},
        {2500.75, 2}, 
        {750.25, 3}
    };
    
    // TODO: Use get_balance to display account 2's balance
    // TODO: Use get_account_for_update to modify account 1's balance to 1200.00
    // TODO: Display all account balances
    
    return 0;
}
```

### Problem 3.2: Object Lifecycle with References (30 minutes)
**Objective**: Understand object creation, copying, and references

Create a comprehensive program that demonstrates object lifecycle:

```cpp
#include <cstdio>
#include <cstring>

struct Book {
    char title[100];
    char author[50];
    int pages;
    double price;
};

// TODO: Write a function 'create_book' that takes title, author, pages, price
// and returns a Book (by value)

// TODO: Write a function 'print_book_info' that takes a const Book reference
// and prints all book information

// TODO: Write a function 'apply_discount' that takes a Book reference and 
// discount percentage, then reduces the price

// TODO: Write a function 'copy_book' that takes a const Book reference and
// returns a new Book with the same information but prefix "Copy of " to title

int main() {
    printf("=== Creating original book ===\n");
    // TODO: Create a book "The C++ Journey" by "Jane Programmer", 300 pages, $49.99
    
    printf("\n=== Original book info ===\n");
    // TODO: Print the original book info
    
    printf("\n=== Applying 20%% discount ===\n");
    // TODO: Apply 20% discount to original book
    // TODO: Print updated info
    
    printf("\n=== Creating a copy ===\n");
    // TODO: Create a copy of the discounted book
    // TODO: Print copy info
    
    printf("\n=== Modifying copy only ===\n");
    // TODO: Apply 10% discount to copy only
    // TODO: Print both original and copy to show they're different
    
    return 0;
}
```

## Submission Guidelines

**For each assignment**:
1. Include source code with clear comments
2. Show compilation method used
3. Provide sample output
4. Document any challenges faced

**File organization**:
```
chapter03_solutions/
├── problem_1_1_basic_references.cpp
├── problem_1_2_references_vs_copies.cpp
├── problem_1_3_multiple_references.cpp
├── problem_2_1_const_references.cpp
├── problem_2_2_modifying_references.cpp
├── problem_3_1_reference_returns.cpp
├── problem_3_2_object_lifecycle.cpp
└── README.md (with compilation notes)
```

---

# Quick Reference

## Top 5 Reference Errors

### 1. Uninitialized Reference
```cpp
int& bad_ref;              // ❌ Error: must initialize

int value = 10;
int& good_ref = value;     // ✅ Initialize when declaring
```

### 2. Non-const Reference to Temporary
```cpp
int& bad_ref = 42;         // ❌ Error: non-const to temporary

const int& good_ref = 42;  // ✅ Const reference to temporary
```

### 3. Modifying Const Reference
```cpp
const int& ref = some_value;
ref = 100;                 // ❌ Error: cannot modify const

int& ref = some_value;     // ✅ Remove const to modify
ref = 100;
```

### 4. Reference Reassignment
```cpp
int a = 10, b = 20;
int& ref = a;
ref = b;                   // ❌ This assigns b's value to a, doesn't reassign ref!

// References cannot be reassigned - use pointers if needed
```

### 5. Dangling References
```cpp
int& bad_function() {
    int local = 42;
    return local;          // ❌ Error: returns reference to local variable
}

int global = 42;
int& good_function() {
    return global;         // ✅ OK: returns reference to global
}
```

## Reference Syntax Quick Guide

```cpp
// Declaration and initialization
int value = 100;
int& ref = value;           // Reference to int
const int& const_ref = value; // Const reference to int

// Function parameters
void modify(int& param);         // Can modify parameter
void read_only(const int& param); // Cannot modify parameter

// Function return values
int& get_reference();           // Returns modifiable reference
const int& get_const_ref();     // Returns read-only reference

// Arrays and references
int arr[5] = {1, 2, 3, 4, 5};
int& first = arr[0];           // Reference to first element
```

## When to Use References vs Pointers

**Use references when:**
- You need an alias to an existing object
- The object will definitely exist (not null)
- You don't need to reassign to different objects
- You want cleaner, safer syntax

**Use pointers when:**
- You need to represent "no object" (null)
- You need to reassign to different objects
- You're doing pointer arithmetic
- You're working with dynamic memory

## Success Checklist

After Chapter 3, you should be able to:
- [ ] Create references and understand they're aliases
- [ ] Use const references for read-only access
- [ ] Write functions that take reference parameters
- [ ] Return references from functions safely
- [ ] Understand when objects are copied vs referenced
- [ ] Apply const correctness principles
- [ ] Choose between references and pointers appropriately

**Not there yet?** Review the concepts you're missing and try the problems again. Use the debugger to watch how references behave - they should show the same memory address as the original variable.

**Ready to move on?** Excellent! Chapter 4 will cover object lifecycle, constructors, destructors, and RAII patterns.

---

## What's Next?

**Chapter 4: Object Lifecycle** will cover:
- Constructors and destructors
- RAII (Resource Acquisition Is Initialization)
- Copy semantics and move semantics
- Object lifetime management

**You've mastered aliasing!** References are one of C++'s cleanest features - they provide pointer-like functionality with simpler syntax. This foundation will serve you well as we explore object-oriented programming concepts.

---

*Remember: References are permanent aliases - think of them as giving a second name to something that already exists. Once created, they always refer to the same object. This constraint makes them safe and predictable!*