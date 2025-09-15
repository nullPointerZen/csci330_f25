# Chapter 3: Assignment Helpers - References

## Purpose
Scaffolding and hints for the reference assignments. Use when stuck or to verify your approach.

---

## Key Concepts Reminder

### Reference Rules
1. **Must be initialized**: `int& ref = variable;`
2. **Cannot be rebound**: Once set, always refers to same variable
3. **No null references**: Unlike pointers, must refer to something
4. **Automatic dereferencing**: No need for `*` operator

### Function Parameter Guidelines
```cpp
void by_value(Type x)           // Copies, safe but potentially slow
void by_reference(Type& x)       // No copy, can modify
void by_const_ref(const Type& x) // No copy, cannot modify
```

---

## Problem Set Solutions Structure

### Problem 1.1: Reference Fundamentals Helper
```cpp
int main() {
    int score = 85;
    int& score_ref = score;  // Reference MUST be initialized

    // Both refer to same memory location
    printf("Original score: %d, Reference: %d\n", score, score_ref);
    printf("Addresses: %p vs %p\n", &score, &score_ref);  // Same!

    score_ref = 92;  // Modifies original
    printf("Modified score: %d, Reference: %d\n", score, score_ref);
}
```

### Problem 1.2: Array References Helper
```cpp
// Function taking array by reference (preserves size info!)
void process_array(int (&arr)[5]) {  // Note syntax: (&arr)[5]
    // sizeof(arr) works correctly here!
    for (int i = 0; i < 5; i++) {
        arr[i] *= 2;
    }
}
```

### Problem 2.1: Swap Function Pattern
```cpp
// Classic swap with references
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
    // No return needed - originals are modified!
}

// Generic swap template (preview of templates)
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```

### Problem 2.2: Struct Modification Pattern
```cpp
struct Student {
    char name[50];
    double gpa;
};

// Read-only access
void print_student(const Student& s) {
    // s.gpa = 4.0;  // ERROR: cannot modify const reference
    printf("%s: %.2f\n", s.name, s.gpa);
}

// Modification access
void update_gpa(Student& s, double new_gpa) {
    s.gpa = new_gpa;  // OK: non-const reference
}
```

### Problem 2.3: Reference Return Pattern
```cpp
// Safe: returning reference to parameter
int& max(int& a, int& b) {
    return (a > b) ? a : b;
}

// DANGEROUS: returning reference to local
int& bad_function() {
    int local = 42;
    return local;  // WARNING: local dies after function!
}

// Safe: returning reference to static/global
int& get_counter() {
    static int counter = 0;
    return counter;  // OK: static lives forever
}
```

---

## Common Patterns and Solutions

### Pattern 1: Const-Correctness Chain
```cpp
void read_only(const int& x) {
    // Cannot modify x
    print_value(x);  // OK if print_value also takes const&
}

void modifier(int& x) {
    x = 42;
    read_only(x);  // OK: can pass non-const to const function
}
```

### Pattern 2: Reference vs Pointer Decision
```cpp
// Use reference when:
void process(Data& data) {  // Never null, must exist
    data.value = 42;
}

// Use pointer when:
void process(Data* data) {  // Could be nullptr
    if (data) {
        data->value = 42;
    }
}
```

### Pattern 3: Large Object Optimization
```cpp
struct LargeData {
    char buffer[10000];
};

// BAD: Makes expensive copy
void slow_function(LargeData data) { }

// GOOD: No copy, read-only
void fast_function(const LargeData& data) { }
```

---

## Debugging Tips

### Check Reference Binding
```cpp
int x = 5;
int& ref = x;
printf("x address: %p\n", &x);
printf("ref address: %p\n", &ref);  // Should be same!
```

### Trace Modifications
```cpp
void debug_swap(int& a, int& b) {
    printf("Before: a=%d, b=%d\n", a, b);
    int temp = a;
    a = b;
    b = temp;
    printf("After: a=%d, b=%d\n", a, b);
}
```

### Validate Const-Correctness
If you get "cannot bind non-const lvalue reference" errors:
- Check if you're trying to pass a temporary
- Check if you're mixing const and non-const incorrectly
- Consider adding const to your parameter

---

## Safety Checklist

Before submitting:
- [ ] No references to local variables returned
- [ ] All references initialized at declaration
- [ ] Const used for read-only parameters
- [ ] No attempts to rebind references
- [ ] Large objects passed by const reference
- [ ] Function signatures match intended usage