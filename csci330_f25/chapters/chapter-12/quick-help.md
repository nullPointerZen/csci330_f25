# Chapter 12: Utilities - Quick Help Reference

**Target Audience**: Students with Python/Java experience struggling with C++ utilities

## Essential Headers and Includes

```cpp
#include <optional>     // For std::optional
#include <variant>      // For std::variant  
#include <tuple>        // For std::tuple
#include <chrono>       // For time operations
```

## std::optional Quick Reference

### Common Patterns
```cpp
// Creation
std::optional<int> opt1;                    // Empty
std::optional<int> opt2 = 42;              // With value
std::optional<int> opt3 = std::nullopt;    // Explicitly empty

// Checking for value
if (opt2) { /* has value */ }
if (opt2.has_value()) { /* has value */ }

// Getting value
int val1 = *opt2;           // Direct access (unsafe if empty)
int val2 = opt2.value();    // Throws if empty
int val3 = opt2.value_or(0); // Default if empty (RECOMMENDED)
```

### Python/Java Comparison
```python
# Python equivalent
def find_item(items, target):
    return item if item in items else None

result = find_item(my_list, "target")
if result is not None:
    print(result)
```

```cpp
// C++ equivalent
std::optional<std::string> find_item(const std::vector<std::string>& items, 
                                     const std::string& target) {
    auto it = std::find(items.begin(), items.end(), target);
    if (it != items.end()) {
        return *it;
    }
    return std::nullopt;
}

auto result = find_item(my_vector, "target");
if (result) {
    std::cout << *result << std::endl;
}
```

## std::variant Quick Reference

### Common Patterns
```cpp
// Declaration
std::variant<int, double, std::string> var;

// Assignment
var = 42;
var = 3.14;
var = std::string("hello");

// Type checking
if (var.index() == 0) { /* it's an int */ }
if (std::holds_alternative<int>(var)) { /* it's an int */ }

// Safe access
if (auto* int_ptr = std::get_if<int>(&var)) {
    std::cout << "Int value: " << *int_ptr << std::endl;
}

// Visitor pattern (RECOMMENDED)
std::visit([](const auto& value) {
    std::cout << "Value: " << value << std::endl;
}, var);
```

### Python Comparison
```python
# Python - dynamic typing
def process_value(value):
    if isinstance(value, int):
        return f"Integer: {value}"
    elif isinstance(value, float):
        return f"Float: {value}"
    elif isinstance(value, str):
        return f"String: {value}"
```

```cpp
// C++ equivalent
std::string process_value(const std::variant<int, double, std::string>& value) {
    return std::visit([](const auto& v) -> std::string {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, int>) {
            return "Integer: " + std::to_string(v);
        } else if constexpr (std::is_same_v<T, double>) {
            return "Double: " + std::to_string(v);
        } else {
            return "String: " + v;
        }
    }, value);
}
```

## std::tuple Quick Reference

### Common Patterns
```cpp
// Creation
std::tuple<int, double, std::string> t1{42, 3.14, "hello"};
auto t2 = std::make_tuple(42, 3.14, "hello");

// C++17 structured bindings (RECOMMENDED)
auto [num, pi, text] = t1;

// Access by index
int num = std::get<0>(t1);
double pi = std::get<1>(t1);
std::string text = std::get<2>(t1);

// Access by type (if unique)
std::string text = std::get<std::string>(t1);
```

### Python Comparison
```python
# Python tuples
def get_user_info():
    return "Alice", 25, 3.8

name, age, gpa = get_user_info()  # Unpacking
print(f"{name} is {age} years old with GPA {gpa}")
```

```cpp
// C++ equivalent
std::tuple<std::string, int, double> get_user_info() {
    return {"Alice", 25, 3.8};
}

auto [name, age, gpa] = get_user_info();  // C++17
std::cout << name << " is " << age << " years old with GPA " << gpa << std::endl;
```

## std::chrono Quick Reference

### Time Points and Durations
```cpp
using namespace std::chrono;

// Get current time
auto now = system_clock::now();
auto steady_now = steady_clock::now();  // For measuring intervals

// Durations
auto ms = milliseconds(100);
auto sec = seconds(1);
auto min = minutes(5);

// Time measurement
auto start = steady_clock::now();
// ... do work ...
auto end = steady_clock::now();
auto duration = end - start;

// Convert to specific units
auto ms_count = duration_cast<milliseconds>(duration).count();
auto sec_count = duration_cast<seconds>(duration).count();
```

### Common Timer Pattern
```cpp
class SimpleTimer {
    std::chrono::steady_clock::time_point start_time;
public:
    void start() {
        start_time = std::chrono::steady_clock::now();
    }
    
    double elapsed_seconds() {
        auto now = std::chrono::steady_clock::now();
        auto duration = now - start_time;
        return std::chrono::duration<double>(duration).count();
    }
};
```

## Common Debugging Techniques

### For std::optional
```cpp
// Debug printing
template<typename T>
void debug_optional(const std::optional<T>& opt, const std::string& name) {
    if (opt) {
        std::cout << name << " has value: " << *opt << std::endl;
    } else {
        std::cout << name << " is empty" << std::endl;
    }
}
```

### For std::variant
```cpp
// Debug printing
template<typename... Types>
void debug_variant(const std::variant<Types...>& var, const std::string& name) {
    std::cout << name << " contains (index " << var.index() << "): ";
    std::visit([](const auto& value) {
        std::cout << value << std::endl;
    }, var);
}
```

### For std::tuple
```cpp
// Debug printing (C++17)
template<typename... Types>
void debug_tuple(const std::tuple<Types...>& t, const std::string& name) {
    std::cout << name << " contains: ";
    std::apply([](const auto&... args) {
        ((std::cout << args << " "), ...);
    }, t);
    std::cout << std::endl;
}
```

## Common Mistakes and Solutions

### std::optional Mistakes
```cpp
// ❌ DON'T: Direct access without checking
std::optional<int> opt;
int value = *opt;  // Undefined behavior!

// ✅ DO: Always check first
if (opt) {
    int value = *opt;  // Safe
}
// OR use value_or
int value = opt.value_or(0);  // Safe with default
```

### std::variant Mistakes
```cpp
// ❌ DON'T: Assume the type
std::variant<int, std::string> var = "hello";
int value = std::get<int>(var);  // Throws std::bad_variant_access!

// ✅ DO: Check type first
if (std::holds_alternative<int>(var)) {
    int value = std::get<int>(var);
}
// OR use std::get_if
if (auto* int_ptr = std::get_if<int>(&var)) {
    int value = *int_ptr;
}
```

### std::tuple Mistakes
```cpp
// ❌ DON'T: Wrong index
std::tuple<int, double> t{42, 3.14};
std::string s = std::get<2>(t);  // Compile error!

// ✅ DO: Use correct index or structured binding
auto [num, pi] = t;  // C++17 - RECOMMENDED
// OR
int num = std::get<0>(t);
double pi = std::get<1>(t);
```

## When to Use What

### Use std::optional when:
- A function might not return a value
- You want to avoid special "sentinel" values (like -1 for "not found")
- You need null safety similar to Java's Optional or Python's None

### Use std::variant when:
- You need to store one of several possible types
- You want type-safe unions
- You're implementing state machines or parsers

### Use std::tuple when:
- You need to return multiple values from a function
- You want to group related values temporarily
- You're interfacing with APIs that expect tuples

### Use std::chrono when:
- You need to measure time intervals
- You want portable, precise timing
- You're implementing timeouts or delays

## IDE and Compiler Tips

### Compiler Flags
```bash
# Enable C++17 for structured bindings
g++ -std=c++17 your_file.cpp

# Common warnings for these utilities
g++ -Wall -Wextra -std=c++17 your_file.cpp
```

### VS Code IntelliSense
Add to your `c_cpp_properties.json`:
```json
{
    "cppStandard": "c++17",
    "compilerArgs": ["-std=c++17"]
}
```

This quick reference should help you avoid common pitfalls and write more effective C++ code using these essential utilities!