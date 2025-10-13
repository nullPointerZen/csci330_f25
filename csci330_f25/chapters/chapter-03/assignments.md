# Chapter 3: Reference Types - Programming Problems

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 3 "References and Aliases"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

**Total Time Budget: 2.25 hours across all problem sets**

## Problem Set 1: Basic References (45 minutes)

### Problem 1.1: Reference Fundamentals (15 minutes)
**Objective**: Understand reference creation and basic usage

Create a program that demonstrates basic reference usage:

```cpp
// Template provided:
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
// Template provided:
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
// Template provided:
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

---

## Problem Set 2: Const References and Functions (45 minutes)

### Problem 2.1: Const Reference Parameters (20 minutes)
**Objective**: Use const references for read-only function parameters

Create a program with functions that use const references:

```cpp
// Template provided:
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
// Template provided (build on Problem 2.1):
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

---

## Problem Set 3: Advanced References and Object Lifecycle (55 minutes)

### Problem 3.1: Reference Return Types (25 minutes)
**Objective**: Understand functions that return references

Create a program that demonstrates reference return types:

```cpp
// Template provided:
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

**Expected Output:**
```
Account 2 balance: $2500.75
Updated balances:
Account 1: $1200.00
Account 2: $2500.75
Account 3: $750.25
```

### Problem 3.2: Object Lifecycle with References (30 minutes)
**Objective**: Understand object creation, copying, and references

Create a comprehensive program that demonstrates object lifecycle:

```cpp
// Template provided:
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

**Expected Output:**
```
=== Creating original book ===

=== Original book info ===
Title: The C++ Journey
Author: Jane Programmer
Pages: 300
Price: $49.99

=== Applying 20% discount ===
Title: The C++ Journey
Author: Jane Programmer
Pages: 300
Price: $39.99

=== Creating a copy ===
Title: Copy of The C++ Journey
Author: Jane Programmer
Pages: 300
Price: $39.99

=== Modifying copy only ===
Original - Title: The C++ Journey, Price: $39.99
Copy - Title: Copy of The C++ Journey, Price: $35.99
```

---

## File Organization

Create your solutions in the following structure:
```
chapter_03_solutions/
├── problem_1_1_basic_references.cpp
├── problem_1_2_references_vs_copies.cpp
├── problem_1_3_multiple_references.cpp
├── problem_2_1_const_references.cpp
├── problem_2_2_modifying_references.cpp
├── problem_3_1_reference_returns.cpp
└── problem_3_2_object_lifecycle.cpp
```

## Compilation Instructions

**Choose your workflow:**

**Docker/Command Line:**
```bash
g++ -std=c++17 -Wall -Wextra -o program_name source_file.cpp
```

**VS Code (any workflow):**
- Press `Ctrl+Shift+B` (or `Cmd+Shift+B` on macOS)
- Or use Terminal → Run Build Task

**CMake (if using assignment templates):**
```bash
mkdir -p build && cd build
cmake .. && make
```

**For reference debugging, add debug symbols:**
```bash
g++ -std=c++17 -g -Wall -Wextra -o program_name source_file.cpp
```

**VS Code Debugging Tips for Chapter 3:**
- Set breakpoints at reference declarations to watch alias creation
- Use Variables panel to see both variable and reference values
- Add `&variable` and `&reference` to Watch panel to confirm same address
- Step through functions to see reference parameter behavior

## Success Checklist

After completing all problems, you should be able to:
- [ ] Create references and understand they're aliases
- [ ] Use const references for read-only access
- [ ] Write functions that take reference parameters
- [ ] Return references from functions safely
- [ ] Understand when objects are copied vs referenced
- [ ] Apply const correctness principles
- [ ] Debug common reference-related errors

## Common Pitfalls to Avoid

1. **Uninitialized References**: References must be initialized when declared
2. **Returning Dangling References**: Don't return references to local variables
3. **Confusing Reference Syntax**: `&` in declaration, not in usage
4. **Const Violations**: Can't modify through const references
5. **Thinking References Can Be Reassigned**: References are permanent aliases

## Getting Help

If you get stuck:
1. Check the quick help guide (`chapter_03_quick_help.md`)
2. Review the lesson plan for concept explanations
3. Look at compiler error messages carefully
4. Test with simple examples first
5. Use the debugger to step through your code

---

## Evaluation Criteria

**Total: 16 Points (4 points per outcome criteria)**

1. **Correctness** (4 points): Programs compile and work as specified
2. **Code Quality** (4 points): Clean, readable, well-organized code
3. **Best Practices** (4 points): Following C++ idioms and conventions
4. **Documentation** (4 points): Appropriate comments and clear output
