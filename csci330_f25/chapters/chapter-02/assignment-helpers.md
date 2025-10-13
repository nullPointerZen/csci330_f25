# Chapter 2: Assignment Helpers

## Purpose
This document provides scaffolding and hints for the main assignments. Use this if you're stuck or want to verify you're on the right track.

---

## Assignment 1: Type System Exploration - Scaffolding

### Part A: Type Discovery Helper

#### Structure Template
```cpp
#include <cstdio>
#include <climits>  // For INT_MAX, INT_MIN
#include <cfloat>   // For DBL_MAX, FLT_MAX

void print_type_analysis() {
    printf("=== C++ Type System Analysis ===\n");
    printf("Fundamental Types:\n");

    // Hint: Create variables for each type
    int my_int = 42;
    // TODO: Add double, char, bool, long, float

    // Hint: Use this pattern for each type
    printf("  int: %d (size: %zu bytes, range: %d to %d)\n",
           my_int, sizeof(int), INT_MIN, INT_MAX);
    // TODO: Similar printf for other types
}

void demonstrate_conversions() {
    printf("\nType Conversions:\n");

    int whole = 42;
    double decimal = 3.14159;

    // Implicit conversion (automatic)
    double whole_as_double = whole;  // TODO: Print this

    // Explicit conversion (you control it)
    int decimal_as_int = static_cast<int>(decimal);  // TODO: Print this

    // Show precision loss
    // TODO: Print both values to show what was lost
}

int main() {
    print_type_analysis();
    demonstrate_conversions();
    // TODO: Add your converter functions
    return 0;
}
```

#### Key Functions You'll Need

**Temperature Conversion Formulas:**
```cpp
double celsius_to_fahrenheit(double c) {
    return (c * 9.0 / 5.0) + 32.0;  // Note: 9.0 not 9 for double math
}

double fahrenheit_to_celsius(double f) {
    // TODO: Implement (F - 32) * 5/9
}
```

**Distance Conversion Helpers:**
```cpp
const double MILES_TO_KM = 1.60934;
const double FEET_TO_METERS = 0.3048;

double miles_to_kilometers(double miles) {
    // TODO: Implement using the constant
}
```

### Part C: Memory Behavior Helper

#### Initialization Demo Structure
```cpp
int global_var;  // Global: auto-initialized to 0

void show_initialization() {
    int local_uninit;       // Dangerous: random value
    int local_init = 0;     // Safe: explicitly initialized
    static int static_var;  // Static: auto-initialized to 0

    printf("Global (auto-init): %d\n", global_var);
    printf("Local uninitialized: %d (RANDOM!)\n", local_uninit);
    printf("Local initialized: %d\n", local_init);
    printf("Static: %d\n", static_var);
}

void show_scope() {
    int x = 10;
    printf("Outer x: %d\n", x);

    {  // New scope block
        int x = 20;  // Shadows outer x
        printf("Inner x: %d\n", x);
    }

    printf("Outer x again: %d\n", x);  // What prints?
}
```

---

## Assignment 2: Student Grade Management - Scaffolding

### Part A: Core Structure Template

#### Start With This Structure
```cpp
#include <cstdio>
#include <cstring>
#include <cassert>

const int MAX_GRADES = 10;
const int MAX_STUDENTS = 5;

struct Student {
    char name[50];
    int student_id;
    int grades[MAX_GRADES];
    int grade_count;  // How many grades this student has
    double average;    // Calculated average
};

// Function to calculate one student's average
void calculate_average(Student* student) {
    if (student->grade_count == 0) {
        student->average = 0.0;
        return;
    }

    int total = 0;
    for (int i = 0; i < student->grade_count; i++) {
        total += student->grades[i];
    }
    student->average = (double)total / student->grade_count;
}

// Function to print one student
void print_student(const Student* s) {
    printf("Student: %s (ID: %d)\n", s->name, s->student_id);
    printf("  Grades: [");
    for (int i = 0; i < s->grade_count; i++) {
        printf("%d", s->grades[i]);
        if (i < s->grade_count - 1) printf(", ");
    }
    printf("]\n");
    printf("  Average: %.1f\n", s->average);
}

int main() {
    // Create array of students
    Student students[MAX_STUDENTS];
    int student_count = 0;  // Track how many we actually use

    // Initialize first student (example)
    strcpy(students[0].name, "Alice Johnson");
    students[0].student_id = 1001;
    students[0].grades[0] = 85;
    students[0].grades[1] = 92;
    students[0].grades[2] = 78;
    students[0].grades[3] = 96;
    students[0].grades[4] = 88;
    students[0].grade_count = 5;
    calculate_average(&students[0]);
    student_count++;

    // TODO: Add at least 2 more students

    // TODO: Print all students

    // TODO: Find class statistics

    return 0;
}
```

### Part B: Pointer Operations Helper

#### Array Access Patterns
```cpp
// Two ways to process arrays - both are equivalent

// Method 1: Array indexing (familiar)
void process_with_index(int grades[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Grade %d: %d\n", i, grades[i]);
    }
}

// Method 2: Pointer arithmetic (new concept)
void process_with_pointers(int* grades, int count) {
    int* end = grades + count;  // Point to one past the last element
    int index = 0;

    for (int* ptr = grades; ptr < end; ptr++) {
        printf("Grade %d: %d\n", index++, *ptr);
    }
}

// Understanding the equivalence:
// grades[i] is the same as *(grades + i)
// &grades[i] is the same as (grades + i)
```

#### Memory Layout Visualization
```cpp
void show_memory_layout(Student* s) {
    printf("Memory Layout of Student struct:\n");
    printf("  Base address: %p\n", (void*)s);
    printf("  name field: %p (offset: %ld)\n",
           (void*)&s->name, (char*)&s->name - (char*)s);
    printf("  id field: %p (offset: %ld)\n",
           (void*)&s->student_id, (char*)&s->student_id - (char*)s);
    printf("  grades field: %p (offset: %ld)\n",
           (void*)&s->grades, (char*)&s->grades - (char*)s);
    printf("  Total size: %zu bytes\n", sizeof(Student));
}
```

#### Safe Array Access Pattern
```cpp
// Always validate array access
bool safe_get_grade(const Student* s, int index, int* result) {
    if (index < 0 || index >= s->grade_count) {
        return false;  // Invalid index
    }
    *result = s->grades[index];
    return true;  // Success
}

// Usage:
int grade;
if (safe_get_grade(&students[0], 2, &grade)) {
    printf("Grade at index 2: %d\n", grade);
} else {
    printf("Invalid index!\n");
}
```

---

## Common Pitfalls and Solutions

### Pitfall 1: String Assignment
```cpp
// WRONG:
char name[50];
name = "Alice";  // ERROR: Can't assign arrays

// CORRECT:
strcpy(name, "Alice");  // Use strcpy for C-strings
```

### Pitfall 2: Uninitialized Arrays
```cpp
// DANGEROUS:
int grades[10];
printf("%d", grades[0]);  // Random value!

// SAFE:
int grades[10] = {0};  // Initialize all to zero
```

### Pitfall 3: Array Bounds
```cpp
// UNSAFE:
for (int i = 0; i <= 10; i++) {  // <= is wrong for size 10!
    arr[i] = 0;  // arr[10] is out of bounds
}

// SAFE:
for (int i = 0; i < 10; i++) {  // < not <=
    arr[i] = 0;
}
```

### Pitfall 4: Integer Division
```cpp
// WRONG:
int total = 24;
int count = 5;
double average = total / count;  // Result: 4.0 (not 4.8!)

// CORRECT:
double average = (double)total / count;  // Result: 4.8
```

### Pitfall 5: Pointer vs Value
```cpp
// Understanding the symbols:
int x = 42;
int* ptr = &x;   // & means "address of"

printf("%d", ptr);   // WRONG: Prints address as number
printf("%d", *ptr);  // CORRECT: * means "value at"
printf("%p", ptr);   // CORRECT: %p for addresses
```

---

## Debugging Strategies

### 1. Add Print Statements
```cpp
printf("DEBUG: Before calculation, total=%d, count=%d\n", total, count);
// Your calculation here
printf("DEBUG: After calculation, average=%.2f\n", average);
```

### 2. Use Assertions
```cpp
#include <cassert>

void process_array(int arr[], int size) {
    assert(size > 0);  // Program stops if false
    assert(arr != nullptr);
    // Safe to process now
}
```

### 3. Check Your Loops
```cpp
// Always verify loop bounds
for (int i = 0; i < size; i++) {
    printf("Processing index %d of %d\n", i, size-1);
    // Your code
}
```

### 4. Initialize Everything
```cpp
// Defensive initialization
Student s = {};  // Zero-initializes entire struct
int arr[10] = {};  // Zero-initializes entire array
```

---

## Progress Checkpoints

### Before Submitting Assignment 1
- [ ] All types print with correct format specifiers
- [ ] Size information displays correctly
- [ ] Type conversions show precision loss where expected
- [ ] Temperature converter handles negative values
- [ ] Distance converter maintains precision
- [ ] No compiler warnings with -Wall flag

### Before Submitting Assignment 2
- [ ] Students stored in array successfully
- [ ] Averages calculate correctly (watch integer division!)
- [ ] Sorting works (if implemented)
- [ ] Memory safety demonstrated
- [ ] Pointer arithmetic section works
- [ ] No array bounds violations

---

## When to Ask for Help

Get help immediately if:
1. Segmentation fault you can't trace
2. Compiler errors you don't understand
3. Stuck on same problem for 30+ minutes
4. Output doesn't match expected after debugging
5. Unsure about memory safety

Remember: The goal is learning, not struggling alone!