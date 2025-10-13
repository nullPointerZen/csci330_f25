# Chapter 3: Warmup Exercises - References (30 minutes)

## Purpose
Need some help getting started? Work through these exercises before tackling the main assignments. They'll build your confidence with references and const-correctness. (Be sure to read the textbook chapter and lecture notes before starting these!)

---

## Exercise 1: Reference Basics (10 minutes)

### Goal
Understand that references are aliases (alternative names) for existing variables.

### Your Task
Create a file `warmup1.cpp`:

```cpp
#include <cstdio>

int main() {
    // Step 1: Create a variable and a reference to it
    int original = 100;
    int& ref = original;  // ref is now another name for original

    // Step 2: Print addresses to prove they're the same
    printf("Value of original: %d\n", original);
    printf("Value of ref: %d\n", ref);
    printf("Address of original: %p\n", (void*)&original);
    printf("Address of ref: %p\n", (void*)&ref);  // Same address!

    // Step 3: Modify through reference
    ref = 200;  // This changes original too
    printf("\nAfter ref = 200:\n");
    printf("original = %d\n", original);  // TODO: What prints?

    // Step 4: Modify original directly
    original = 300;
    printf("\nAfter original = 300:\n");
    printf("ref = %d\n", ref);  // TODO: What prints?

    return 0;
}
```

### Expected Insights
- References and original variables share the same memory address
- Changing one affects the other (they're the same thing!)
- References must be initialized when declared

### Check Yourself
- Do both variables show the same address?
- When you change one, does the other change?
- Can you create a reference without initializing it? (Try it - it won't compile!)

---

## Exercise 2: Reference vs Pointer vs Copy (10 minutes)

### Goal
Understand the differences between references, pointers, and copies.

### Your Task
Create a file `warmup2.cpp`:

```cpp
#include <cstdio>

void modify_by_value(int x) {
    x = 999;  // Only changes local copy
}

void modify_by_pointer(int* x) {
    *x = 888;  // Changes original through pointer
}

void modify_by_reference(int& x) {
    x = 777;  // Changes original through reference
}

int main() {
    int number = 100;

    // Test 1: Pass by value (copy)
    printf("Original number: %d\n", number);
    modify_by_value(number);
    printf("After modify_by_value: %d\n", number);  // TODO: What prints?

    // Test 2: Pass by pointer
    modify_by_pointer(&number);  // Note: need & to get address
    printf("After modify_by_pointer: %d\n", number);  // TODO: What prints?

    // Test 3: Pass by reference
    modify_by_reference(number);  // Note: no & needed here!
    printf("After modify_by_reference: %d\n", number);  // TODO: What prints?

    return 0;
}
```

### Expected Output
```
Original number: 100
After modify_by_value: 100
After modify_by_pointer: 888
After modify_by_reference: 777
```

### Check Yourself
- Which function actually modified the original?
- Why didn't `modify_by_value` change the original?
- Notice the syntax difference: pointers need `&` when calling, references don't

---

## Exercise 3: Const References (10 minutes)

### Goal
Learn when and why to use const references.

### Your Task
Create a file `warmup3.cpp`:

```cpp
#include <cstdio>

struct Book {
    char title[100];
    int pages;
    double price;
};

// Function that only reads the book (const reference)
void print_book(const Book& book) {
    printf("Title: %s\n", book.title);
    printf("Pages: %d\n", book.pages);
    printf("Price: $%.2f\n", book.price);

    // TODO: Try to modify the book here
    // book.pages = 500;  // Uncomment this - what happens?
}

// Function that modifies the book (non-const reference)
void discount_book(Book& book, double percent) {
    book.price = book.price * (1.0 - percent/100.0);
    printf("Applied %g%% discount\n", percent);
}

// Function that makes a copy (expensive for large structs!)
void print_book_copy(Book book) {  // No & means copy
    printf("This function got a copy at address: %p\n", (void*)&book);
}

int main() {
    Book myBook = {"C++ Primer", 976, 59.99};

    // Show original
    printf("Original book:\n");
    print_book(myBook);  // Efficient: no copy made

    // Apply discount
    printf("\nApplying discount:\n");
    discount_book(myBook, 20);  // 20% off

    // Show after discount
    printf("\nAfter discount:\n");
    print_book(myBook);

    // Show copy vs reference addresses
    printf("\nAddress comparison:\n");
    printf("Original book address: %p\n", (void*)&myBook);
    print_book_copy(myBook);  // Makes a copy

    return 0;
}
```

### Expected Insights
- `const Book&` prevents accidental modifications
- References avoid expensive copies of large structs
- Use const references for read-only access
- Use non-const references when you need to modify

### Check Yourself
- What happens if you try to modify a const reference?
- Why use `const Book&` instead of just `Book`?
- When would you use non-const references?

---

## Success Checklist

Before moving to the main assignments, confirm:

### Understanding
- [ ] I know references are aliases, not copies
- [ ] I understand references share the same address as the original
- [ ] I can explain when to use references vs pointers vs copies
- [ ] I know why const references are useful for large objects

### Can Do
- [ ] Create and use basic references
- [ ] Pass arguments by reference to functions
- [ ] Use const references for read-only parameters
- [ ] Understand compiler errors when violating const

### Ready For
- [ ] Complex reference scenarios in main assignments
- [ ] Reference parameters in larger programs
- [ ] Const-correctness in real code
- [ ] Reference return types from functions

---

## Quick Reference Card

### Declaration Syntax
```cpp
int x = 5;
int& ref = x;        // Reference must be initialized
const int& cref = x; // Const reference
```

### Function Parameters
```cpp
void by_value(int x)        // Makes a copy
void by_pointer(int* x)      // Needs address when calling
void by_reference(int& x)    // No copy, can modify
void by_const_ref(const int& x)  // No copy, can't modify
```

### When to Use What
- **By value**: Small types (int, char, bool), when you need a copy
- **By const reference**: Large objects you only need to read
- **By reference**: When you need to modify the original
- **By pointer**: When nullptr is a valid option, or C compatibility

---

## Common Mistakes to Avoid

1. **Forgetting to initialize references**
   ```cpp
   int& ref;  // ERROR: references must be initialized
   ```

2. **Trying to rebind references**
   ```cpp
   int a = 5, b = 10;
   int& ref = a;
   ref = b;  // This assigns b's value to a, doesn't rebind ref!
   ```

3. **Returning references to local variables**
   ```cpp
   int& bad_function() {
       int local = 42;
       return local;  // DANGER: local dies when function ends!
   }
   ```

---

## Next Steps

After completing these warmups (30 minutes), you're ready for the main assignments which will:
- Use references in complex data structures
- Implement swap functions with references
- Build const-correct interfaces
- Optimize performance with reference parameters

Remember: References are one of C++'s most powerful features for writing efficient, safe code!