# Chapter 2: Types - Problem Sets

## Total Estimated Time: 2.25 hours across all problem sets

---

## Problem Set 1: Fundamental Types and Variables (45 minutes)
*Focus: Basic type usage, declarations, and initialization*

### Problem 1.1: Type Explorer (15 minutes)
**Objective**: Practice with fundamental types and format specifiers

Create a program that demonstrates all fundamental types. Your program should:

1. Declare and initialize variables of each type: `int`, `double`, `char`, `bool`
2. Print each variable with appropriate format specifiers
3. Use `sizeof` to show the size in bytes of each type
4. Show type conversion behavior

**Expected Output**:
```
Integer: 42 (size: 4 bytes)
Double: 3.14 (size: 8 bytes)  
Character: A (size: 1 byte)
Boolean: 1 (size: 1 byte)
Conversion: 42 -> 42.00
```

**Time Estimate**: 15 minutes
**Files**: `problem_1_1.cpp`

---

### Problem 1.2: Temperature Converter with Multiple Types (15 minutes)
**Objective**: Apply type usage in a practical program

Write a program that converts temperatures between Celsius and Fahrenheit:

1. Store the Celsius temperature as an `int`
2. Calculate Fahrenheit as a `double` for precision
3. Display results with proper formatting
4. Test with freezing point (0°C) and boiling point (100°C)

**Formula**: F = (C × 9/5) + 32

**Expected Output**:
```
0°C = 32.0°F
100°C = 212.0°F
```

**Time Estimate**: 15 minutes
**Files**: `problem_1_2.cpp`

---

### Problem 1.3: Variable Scope and Initialization (15 minutes)
**Objective**: Understand initialization importance and scope

Create a program that shows:

1. Uninitialized variables (observe unpredictable values)
2. Properly initialized variables
3. Local vs global variable scope
4. Variable shadowing in nested blocks

Include comments explaining what happens with uninitialized variables.

**Time Estimate**: 15 minutes
**Files**: `problem_1_3.cpp`

---

## Problem Set 2: Arrays and Basic Memory Management (60 minutes)
*Focus: Static arrays, bounds checking, and memory layout*

### Problem 2.1: Grade Calculator with Arrays (20 minutes)
**Objective**: Practice array declaration, initialization, and processing

Write a program that:

1. Creates an array to store 5 test scores
2. Initializes with sample scores: {85, 92, 78, 96, 88}
3. Calculates and prints the average
4. Finds and prints the highest and lowest scores
5. Counts how many scores are above average

**Expected Output**:
```
Scores: 85, 92, 78, 96, 88
Average: 87.8
Highest: 96
Lowest: 78
Above average: 2 scores
```

**Template Provided**:
```cpp
#include <cstdio>

int main() {
    int scores[5] = {85, 92, 78, 96, 88};
    
    // TODO: Calculate average
    // TODO: Find min/max
    // TODO: Count above average
    
    return 0;
}
```

**Time Estimate**: 20 minutes
**Files**: `problem_2_1.cpp`

---

### Problem 2.2: Safe Array Access (20 minutes)
**Objective**: Understand array bounds and implement safety checks

Create a program that:

1. Declares an array of 10 integers
2. Implements a "safe access" function that checks bounds
3. Demonstrates what happens with out-of-bounds access
4. Shows how to protect against buffer overflows

**VS Code Debugging Tips for this Problem:**
- Set breakpoints in your bounds-checking code
- Use Watch panel to monitor `index` and `size` values
- Try running with Address Sanitizer to catch bounds violations automatically
- Step through the function to see how bounds checking works

**Function Signature**:
```cpp
bool safeArrayAccess(int arr[], int size, int index, int* value);
// Returns true if access is safe, stores value in *value
// Returns false if index is out of bounds
```

**Time Estimate**: 20 minutes
**Files**: `problem_2_2.cpp`

---

### Problem 2.3: Multi-dimensional Arrays (20 minutes)
**Objective**: Work with 2D arrays for matrix operations

Write a program that:

1. Creates a 3x3 matrix (2D array)
2. Initializes it with sample values
3. Calculates the sum of each row
4. Calculates the sum of each column
5. Finds the overall sum

**Sample Matrix**:
```
1 2 3
4 5 6  
7 8 9
```

**Expected Output**:
```
Matrix:
1 2 3 (row sum: 6)
4 5 6 (row sum: 15)
7 8 9 (row sum: 24)
Column sums: 12, 15, 18
Total sum: 45
```

**Time Estimate**: 20 minutes
**Files**: `problem_2_3.cpp`

---

## Problem Set 3: Pointers and Structs Integration (90 minutes)
*Focus: Combining pointers, structs, and arrays for practical applications*

### Problem 3.1: Student Management System (45 minutes)
**Objective**: Integrate structs, arrays, and pointers

**VS Code Debugging Strategy for Complex Problem:**
- Set breakpoints at the beginning of each function
- Use Variables panel to expand struct members and see all data
- Add watch expressions for pointer values: `student`, `*student`, `&(student->grades[0])`
- Step through pointer arithmetic and function calls carefully

Create a comprehensive student management system:

#### Part A: Struct Definition (10 minutes)
Define a `Student` struct with:
- Name (character array of size 30)
- Student ID (integer)
- Grades array (5 test scores)
- GPA (double)

#### Part B: Core Functions (25 minutes)
Implement these functions:

```cpp
// Calculate GPA from grades array
double calculateGPA(Student* student);

// Print student information nicely formatted
void printStudent(const Student* student);

// Find student with highest GPA from array
Student* findTopStudent(Student students[], int count);

// Update a specific grade for a student
void updateGrade(Student* student, int testIndex, int newGrade);
```

#### Part C: Main Program (10 minutes)
Create a program that:
1. Creates array of 3 students with sample data
2. Calculates GPA for each student
3. Prints all student information
4. Finds and announces the top student
5. Updates one grade and recalculates

**Starter Template**:
```cpp
#include <cstdio>
#include <cstring>

struct Student {
    char name[30];
    int studentId;
    int grades[5];
    double gpa;
};

double calculateGPA(Student* student) {
    // TODO: Calculate GPA from grades (assume 4.0 scale)
    // A simple conversion: average grade / 25.0 for 0-4.0 scale
}

void printStudent(const Student* student) {
    // TODO: Print formatted student information
}

// TODO: Implement other functions

int main() {
    Student students[3];
    
    // Sample data for first student
    strcpy(students[0].name, "Alice Johnson");
    students[0].studentId = 12345;
    students[0].grades[0] = 85; // Initialize remaining grades
    
    // TODO: Initialize other students
    // TODO: Use your functions
    
    return 0;
}
```

**Expected Output**:
```
Student: Alice Johnson (ID: 12345)
Grades: 85, 92, 78, 96, 89
GPA: 3.52

Student: Bob Smith (ID: 12346)
Grades: 78, 85, 82, 90, 88
GPA: 3.29

Student: Carol Davis (ID: 12347)
Grades: 95, 98, 92, 94, 96
GPA: 3.75

Top Student: Carol Davis with GPA 3.75

After updating Alice's test 3 from 78 to 88:
Alice's new GPA: 3.68
```

**Time Estimate**: 45 minutes
**Files**: `problem_3_1.cpp`

---

### Problem 3.2: Dynamic Inventory System (45 minutes)
**Objective**: Advanced struct usage with business logic

Create an inventory management system for a small store:

#### Requirements:
1. Define `Product` struct with:
   - Name (char array)
   - Price (double)
   - Quantity in stock (int)
   - Product code (char array)

2. Implement functions for:
   - Adding new products
   - Updating stock quantities
   - Calculating total inventory value
   - Finding low-stock items (quantity < 5)
   - Processing sales (reducing stock)

3. Handle edge cases:
   - Selling more items than in stock
   - Invalid product codes
   - Negative quantities

**Function Signatures**:
```cpp
void addProduct(Product inventory[], int* count, const char* name, 
                double price, int quantity, const char* code);

bool processSale(Product* product, int quantitySold);

double calculateTotalValue(const Product inventory[], int count);

void printLowStock(const Product inventory[], int count);
```

**Sample Interaction**:
```
Inventory System
================
Added: Laptop (LP001) - $999.99 x 10
Added: Mouse (MS001) - $25.50 x 15
Added: Keyboard (KB001) - $75.00 x 3

Processing sale: 2 Laptops
Sale successful. 8 Laptops remaining.

Low stock items:
- Keyboard (KB001): 3 remaining

Total inventory value: $12,407.42
```

**Starter Template**:
```cpp
#include <cstdio>
#include <cstring>

struct Product {
    char name[50];
    double price;
    int quantity;
    char code[10];
};

const int MAX_PRODUCTS = 100;

// TODO: Implement required functions

int main() {
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;
    
    // TODO: Test your system with sample products
    
    return 0;
}
```

**Time Estimate**: 45 minutes
**Files**: `problem_3_2.cpp`

---

## Submission Guidelines

### File Organization
Create the following files in your working directory:
```
chapter_02_problems/
├── problem_1_1.cpp
├── problem_1_2.cpp  
├── problem_1_3.cpp
├── problem_2_1.cpp
├── problem_2_2.cpp
├── problem_2_3.cpp
├── problem_3_1.cpp
└── problem_3_2.cpp
```

### Compilation Instructions

**Choose your workflow:**

**Docker/Command Line:**
```bash
g++ -o program_name program_name.cpp
```

**VS Code (any workflow):**
- Press `Ctrl+Shift+B` (or `Cmd+Shift+B` on macOS)
- Or use Terminal → Run Build Task

**CMake (if using assignment templates):**
```bash
mkdir -p build && cd build
cmake .. && make
```

**For memory debugging, compile with debug flags:**
```bash
g++ -g -fsanitize=address -o program_name program_name.cpp
```

### Testing Requirements
1. **Compilation**: All programs must compile without errors
2. **Execution**: Programs should run and produce expected output
3. **Edge Cases**: Test boundary conditions (empty arrays, null pointers)
4. **Documentation**: Include comments explaining complex logic

### Common Pitfalls to Avoid
1. **Uninitialized Variables**: Always initialize variables before use
2. **Array Bounds**: Never access beyond array limits
3. **Null Pointers**: Check pointers before dereferencing
4. **String Handling**: Use `strcpy` for string assignment, not `=`
5. **Integer Division**: Remember that `5/2 = 2`, use `5.0/2` for decimals

---

## Grading Rubric

### Problem Set 1 (30 points)
- **Compilation (10 points)**: All programs compile cleanly
- **Correctness (15 points)**: Programs produce expected output
- **Code Quality (5 points)**: Proper formatting and comments

### Problem Set 2 (40 points)  
- **Array Usage (15 points)**: Proper declaration and manipulation
- **Bounds Safety (10 points)**: Demonstrates understanding of array limits
- **Logic Implementation (15 points)**: Correct algorithms and calculations

### Problem Set 3 (60 points)
- **Struct Design (15 points)**: Appropriate data organization
- **Pointer Usage (20 points)**: Correct pointer operations and safety
- **Function Implementation (20 points)**: Working functions with proper parameters
- **Integration (5 points)**: All components work together

### Bonus Opportunities (+10 points each)
- Implement additional safety checks
- Add user input validation
- Create additional utility functions
- Optimize algorithms for better performance

**Total Points**: 130 (plus up to 40 bonus points)