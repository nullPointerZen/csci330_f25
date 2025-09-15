# Chapter 2: Warmup Exercises (30 minutes)

## Purpose
Need some help getting started? Work through these exercises before tackling the main assignments. They'll build your confidence with the core concepts. (Be sure to read the textbook chapter and lecture notes before starting these!)

---

## Exercise 1: Type Basics (10 minutes)

### Goal
Get comfortable with declaring variables and understanding type sizes.

### Your Task
Create a file `warmup1.cpp`:

```cpp
#include <cstdio>

int main() {
    // Step 1: Declare these variables (fill in the values)
    int my_age = ____;           // Your age
    double my_gpa = ____;        // A GPA (e.g., 3.5)
    char my_grade = '___';       // A letter grade
    bool is_student = ____;      // true or false

    // Step 2: Print each variable with its size
    printf("Age: %d (size: %zu bytes)\n", my_age, sizeof(my_age));
    // TODO: Add printf for my_gpa (use %.2f for the value)
    // TODO: Add printf for my_grade (use %c for the value)
    // TODO: Add printf for is_student (use %d for the value)

    // Step 3: Observe type conversion
    double age_as_double = my_age;  // Implicit conversion
    printf("\nInteger %d becomes double %.1f\n", my_age, age_as_double);

    return 0;
}
```

### Expected Output Example
```
Age: 20 (size: 4 bytes)
GPA: 3.50 (size: 8 bytes)
Grade: A (size: 1 byte)
Is student: 1 (size: 1 byte)

Integer 20 becomes double 20.0
```

### Check Yourself
- Did all variables print correctly?
- Are the sizes what you expected?
- Did the conversion work without errors?

---

## Exercise 2: Simple Array Practice (10 minutes)

### Goal
Work with arrays safely before building complex programs.

### Your Task
Create a file `warmup2.cpp`:

```cpp
#include <cstdio>

int main() {
    // Step 1: Create a small array
    int quiz_scores[3] = {8, 9, 7};  // Three quiz scores out of 10

    // Step 2: Print each element using a loop
    printf("Quiz scores:\n");
    for (int i = 0; i < 3; i++) {
        printf("  Quiz %d: %d/10\n", i+1, quiz_scores[i]);
    }

    // Step 3: Calculate the total (fill in the loop)
    int total = 0;
    for (int i = 0; i < 3; i++) {
        // TODO: Add quiz_scores[i] to total
    }
    printf("\nTotal points: %d/30\n", total);

    // Step 4: Try changing one score
    quiz_scores[1] = 10;  // Changed second quiz to perfect score
    printf("Updated Quiz 2: %d/10\n", quiz_scores[1]);

    return 0;
}
```

### Expected Output
```
Quiz scores:
  Quiz 1: 8/10
  Quiz 2: 9/10
  Quiz 3: 7/10

Total points: 24/30
Updated Quiz 2: 10/10
```

### Check Yourself
- Does your loop correctly access all three elements?
- Does the total calculate correctly?
- Can you modify array elements?

---

## Exercise 3: First Struct (10 minutes)

### Goal
Create and use a simple struct before building complex data structures.

### Your Task
Create a file `warmup3.cpp`:

```cpp
#include <cstdio>
#include <cstring>

// Step 1: Define a simple struct
struct Book {
    char title[50];
    int pages;
    double price;
};

int main() {
    // Step 2: Create and initialize a book
    Book my_book;
    strcpy(my_book.title, "C++ Primer");  // Note: strcpy for strings!
    my_book.pages = 976;
    my_book.price = 59.99;

    // Step 3: Print the book information
    printf("Book Information:\n");
    printf("  Title: %s\n", my_book.title);
    printf("  Pages: %d\n", my_book.pages);
    printf("  Price: $%.2f\n", my_book.price);

    // Step 4: Create another book (fill in the values)
    Book another_book;
    strcpy(another_book.title, "___________");  // TODO: Your favorite book
    another_book.pages = ____;                  // TODO: Estimate pages
    another_book.price = ____;                  // TODO: Estimate price

    // TODO: Print another_book's information

    return 0;
}
```

### Expected Output Example
```
Book Information:
  Title: C++ Primer
  Pages: 976
  Price: $59.99
```

### Check Yourself
- Did you use `strcpy` for the string (not `=`)?
- Can you access struct members with dot notation?
- Does everything compile without warnings?

---

## Success Checklist

Before moving to the main assignments, confirm:

### Comfort Level
- [ ] I can declare variables of different types
- [ ] I can print values with the correct format specifiers
- [ ] I can create and access array elements
- [ ] I can use a loop to process an array
- [ ] I can define and use a simple struct
- [ ] I understand why we use `strcpy` for strings

### No More Confusion About
- [ ] The difference between `%d`, `%.2f`, `%c`, `%s` in printf
- [ ] Why arrays start at index 0
- [ ] How to access struct members with dot notation
- [ ] Why C++ requires explicit type declarations

### Ready For
- [ ] Building larger programs with multiple functions
- [ ] Working with pointers and memory addresses
- [ ] Creating arrays of structs
- [ ] Implementing the main assignments

---

## Tips for Success

1. **Compile Often**: After each step, compile and run to catch errors early
   ```bash
   g++ -o warmup1 warmup1.cpp
   ./warmup1
   ```

2. **Use Compiler Warnings**: Add flags to catch common mistakes
   ```bash
   g++ -Wall -Wextra -o warmup1 warmup1.cpp
   ```

3. **Read Error Messages**: C++ errors can be verbose but usually point to the exact line

4. **Don't Skip Steps**: Each exercise builds on the previous one

5. **Ask for Help**: If you're stuck for more than 10 minutes on a warmup, ask for help!

---

## Next Steps

After completing these warmups (30 minutes), you should feel ready to tackle the main assignments. The warmups have introduced:
- Basic type usage → Needed for Type System Exploration
- Array manipulation → Needed for Student Grade Management
- Struct creation → Needed for the Student struct

Remember: The main assignments combine these concepts into larger programs. You now have the building blocks!