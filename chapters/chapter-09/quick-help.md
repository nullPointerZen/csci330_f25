# Chapter 9: Functions - Quick Help Guide

**For students with Python/Java background learning C++ function pointers, lambdas, and function objects**

---

## 🚨 Most Common Mistakes

### 1. Function Pointer Syntax Confusion
```cpp
// WRONG - missing parentheses around pointer name
int *func_ptr(int, int);  // This declares a function returning int*

// RIGHT - parentheses group the pointer part
int (*func_ptr)(int, int);  // This declares a pointer to function

// WRONG - trying to call without assignment
int (*operation)(int, int);
int result = operation(5, 3);  // Undefined behavior!

// RIGHT - assign before calling
int (*operation)(int, int) = add;
int result = operation(5, 3);  // Safe
```

### 2. Lambda Capture Confusion
```cpp
int x = 10;

// WRONG - will capture x by value even if you modify it later
auto bad_lambda = [x]() mutable { 
    x = 20;  // Only modifies the copy inside lambda
    return x; 
};
// x is still 10 outside!

// RIGHT - capture by reference to modify original
auto good_lambda = [&x]() { 
    x = 20;  // Modifies the original x
    return x; 
};
// Now x is 20 outside too
```

### 3. Dangling Reference Captures
```cpp
// DANGEROUS - local variable lifetime issue
auto create_lambda() {
    int local_var = 42;
    return [&local_var]() { return local_var; };  // DANGER!
}
// local_var is destroyed when function exits

// SAFE - capture by value instead
auto create_lambda() {
    int local_var = 42;
    return [local_var]() { return local_var; };  // Safe copy
}
```

---

## 📋 Function Type Quick Reference

### Function Pointers
```cpp
// Declaration pattern
return_type (*pointer_name)(parameter_types);

// Examples
int (*math_op)(int, int);           // Points to function taking 2 ints, returning int
void (*callback)(const std::string&); // Points to function taking string ref, returning void
bool (*comparator)(double, double);  // Points to comparison function

// Assignment (& is optional)
math_op = &add;     // Explicit address-of
math_op = add;      // Implicit conversion (preferred)

// Calling
int result = math_op(5, 3);         // Direct call
int result = (*math_op)(5, 3);      // Explicit dereference (also works)
```

### Lambda Expressions
```cpp
// Basic syntax: [capture](parameters) -> return_type { body }

// No capture, simple lambda
auto simple = [](int x) { return x * 2; };

// Capture by value
int multiplier = 3;
auto by_value = [multiplier](int x) { return x * multiplier; };

// Capture by reference  
auto by_ref = [&multiplier](int x) { return x * multiplier; };

// Mixed capture
auto mixed = [multiplier, &some_ref](int x) { /* ... */ };

// Capture all by value/reference
auto capture_all_val = [=](int x) { /* can use all local vars by value */ };
auto capture_all_ref = [&](int x) { /* can use all local vars by reference */ };

// Generic lambda (C++14)
auto generic = [](const auto& x) { return x + x; };
```

### Function Objects (Functors)
```cpp
class MyFunctor {
private:
    int state;
    
public:
    MyFunctor(int initial) : state(initial) {}
    
    // Function call operator - this makes it callable
    int operator()(int x) {
        state += x;
        return state;
    }
    
    int get_state() const { return state; }
};

// Usage
MyFunctor func(10);
int result = func(5);  // Calls operator(), state becomes 15
```

### std::function (Type Erasure)
```cpp
#include <functional>

// Can hold any callable with matching signature
std::function<int(int, int)> operation;

// Assign different callable types
operation = add;                           // Function pointer
operation = [](int a, int b){ return a*b; }; // Lambda
operation = Multiplier{};                  // Function object

// Call through std::function
int result = operation(5, 3);
```

---

## ⚡ Lambda Capture Modes Cheat Sheet

| Capture | Syntax | What it does | When to use |
|---------|--------|--------------|-------------|
| **None** | `[]` | No access to outside variables | Pure functions, utilities |
| **By Value** | `[var]` | Copies var into lambda | Want to freeze current value |
| **By Reference** | `[&var]` | References original var | Want to modify original |
| **All by Value** | `[=]` | Copies all used variables | Closures, callbacks |
| **All by Reference** | `[&]` | References all used variables | Local processing |
| **Mixed** | `[=, &var]` | Copy all except var (by ref) | Mostly copy, some references |
| **Init Capture** | `[x = value]` | Initialize new variable in capture | Transform values, C++14+ |

### Capture Examples
```cpp
int a = 10, b = 20;
std::string msg = "Hello";

// Different capture strategies
auto lambda1 = [a](int x) { return a + x; };           // Copy a
auto lambda2 = [&b](int x) { b += x; return b; };      // Reference b  
auto lambda3 = [=](int x) { return a + b + x; };       // Copy a, b, msg
auto lambda4 = [&](int x) { a += x; return a + b; };   // Reference all
auto lambda5 = [=, &b](int x) { b += x; return a + b; }; // Copy a,msg; reference b
auto lambda6 = [doubled = a * 2](int x) { return doubled + x; }; // Init capture
```

---

## 🔧 When to Use Which Function Type

### Use Function Pointers When:
- Interfacing with C code
- Simple callbacks without state
- Performance is critical (no std::function overhead)
- Working with existing APIs that expect function pointers

```cpp
// Good for simple callbacks
void register_callback(void (*callback)(int error_code));

// Good for C-style APIs
int compare_ints(const void* a, const void* b);
qsort(array, size, sizeof(int), compare_ints);
```

### Use Lambdas When:
- Need closures (access to local variables)
- Short, one-off functions
- Working with STL algorithms
- Modern C++ code style

```cpp
// Perfect for STL algorithms
std::sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; });

// Great for closures
int threshold = 50;
auto filter = [threshold](int x) { return x > threshold; };
```

### Use Function Objects When:
- Need complex state management
- Want both callable behavior and regular methods
- Performance-critical code (can be optimized better than std::function)
- Reusable, configurable behavior

```cpp
// Good for stateful operations
class RunningAverage {
    double sum = 0;
    int count = 0;
public:
    double operator()(double x) {
        sum += x;
        return sum / ++count;
    }
    void reset() { sum = 0; count = 0; }
};
```

### Use std::function When:
- Need to store different types of callables in same container
- Type erasure is needed
- Flexible interfaces
- Don't know the exact callable type at compile time

```cpp
// Good for flexible interfaces
class EventSystem {
    std::vector<std::function<void(const Event&)>> handlers;
public:
    void add_handler(std::function<void(const Event&)> h) {
        handlers.push_back(h);
    }
};
```

---

## 🔍 Common Debugging Issues

### 1. "Cannot convert" function pointer errors
```cpp
// Problem: Type mismatch
void func(int x, int y);
int (*ptr)(int, int) = func;  // ERROR: return type mismatch

// Solution: Match types exactly
void (*ptr)(int, int) = func;  // OK: return types match
```

### 2. Lambda capture compilation errors
```cpp
// Problem: Trying to modify by-value capture
auto lambda = [x](int y) { 
    x += y;  // ERROR: x is const copy
    return x; 
};

// Solutions:
auto lambda1 = [x](int y) mutable {  // Make lambda mutable
    x += y;  // OK: can modify copy
    return x; 
};

auto lambda2 = [&x](int y) {  // Or capture by reference
    x += y;  // OK: modifying original
    return x; 
};
```

### 3. std::function assignment errors
```cpp
// Problem: Signature mismatch
std::function<int(int)> func;
func = [](int a, int b) { return a + b; };  // ERROR: wrong signature

// Solution: Match signature exactly
std::function<int(int, int)> func;  // OK: signature matches
func = [](int a, int b) { return a + b; };
```

---

## 🎯 Best Practices

### Lambda Style Guidelines
```cpp
// GOOD: Clear capture intent
auto processor = [data_size = input.size()](const auto& item) {
    return item.process(data_size);
};

// AVOID: Unclear capture
auto processor = [=](const auto& item) {  // What's being captured?
    return item.process(input.size());
};

// GOOD: Explicit types when needed
auto comparator = [](const std::string& a, const std::string& b) -> bool {
    return a.length() < b.length();
};

// GOOD: Multi-line formatting
auto complex_lambda = [captured_data, &counter](const Data& input) {
    if (input.is_valid()) {
        ++counter;
        return captured_data.process(input);
    }
    return Data{};
};
```

### Function Pointer Safety
```cpp
// ALWAYS check for null before calling
int (*operation)(int, int) = nullptr;
// ... some assignment logic ...
if (operation != nullptr) {  // or if (operation)
    int result = operation(5, 3);
}
```

### std::function Efficiency
```cpp
// GOOD: Avoid std::function for simple cases
template<typename Callable>
void process_data(const std::vector<int>& data, Callable func) {
    for (int item : data) {
        func(item);
    }
}

// ONLY use std::function when type erasure is actually needed
class FlexibleProcessor {
    std::function<void(int)> processor;  // OK: need to store different types
public:
    void set_processor(std::function<void(int)> p) { processor = p; }
};
```

---

## ⚠️ Performance Considerations

### Function Call Overhead (fastest to slowest)
1. **Direct function call**: `add(5, 3)` - inlined by compiler
2. **Function pointer**: `(*func_ptr)(5, 3)` - indirect call
3. **Lambda/functor**: Usually inlined, same as direct call
4. **std::function**: Type erasure overhead, virtual-like dispatch

### When Performance Matters
```cpp
// High-performance scenario - prefer templates
template<typename Comparator>
void fast_sort(std::vector<int>& data, Comparator comp) {
    std::sort(data.begin(), data.end(), comp);  // comp can be inlined
}

// Flexible but slower - use std::function
void flexible_sort(std::vector<int>& data, std::function<bool(int,int)> comp) {
    std::sort(data.begin(), data.end(), comp);  // comp has call overhead
}
```

---

## 🆘 Emergency Syntax Reference

### Function Pointer Declaration Patterns
```cpp
// Basic pattern
return_type (*name)(param_types);

// Array of function pointers
return_type (*name[])(param_types) = {func1, func2, func3};

// Function taking function pointer
void higher_order(return_type (*func)(param_types));

// Function returning function pointer  
return_type (*get_function())(param_types);

// Typedef for readability
typedef return_type (*FuncPtr)(param_types);
FuncPtr my_func = some_function;
```

### Lambda Quick Templates
```cpp
// Basic lambda template
auto name = [capture](params) -> return_type { 
    // body
    return value;
};

// Common patterns
auto predicate = [](const auto& x) { return x > 0; };
auto transform = [multiplier](auto x) { return x * multiplier; };
auto accumulator = [sum = 0](auto x) mutable { return sum += x; };
```

### std::function Declaration Pattern
```cpp
#include <functional>

std::function<return_type(param_types)> name;
name = some_callable;
return_type result = name(arguments);
```

**Remember**: When in doubt, prefer lambdas for modern C++ code. They're usually the right choice!