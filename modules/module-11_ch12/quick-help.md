# Chapter 12: Utilities - Quick Help Guide

**For students with Python/Java background learning C++ move semantics, optional, variant, and modern utilities**

---

## 🚨 Most Common Mistakes

### 1. Unnecessary std::move Usage
```cpp
// WRONG - Don't move when returning local objects (RVO applies)
std::string bad_function() {
    std::string result = "hello";
    return std::move(result);  // Prevents RVO optimization!
}

// RIGHT - Let RVO work
std::string good_function() {
    std::string result = "hello";
    return result;  // RVO optimizes this automatically
}

// WRONG - Moving copyable primitives
int x = 42;
int y = std::move(x);  // Pointless, int is cheap to copy

// RIGHT - Move expensive objects when needed
std::vector<int> vec = create_large_vector();
std::vector<int> moved = std::move(vec);  // Good, avoids copying
```

### 2. std::optional Value Access Without Checking
```cpp
// DANGEROUS - Can throw std::bad_optional_access
std::optional<int> maybe_int = get_optional_int();
int value = maybe_int.value();  // Might throw!

// SAFE - Always check first
if (maybe_int.has_value()) {
    int value = maybe_int.value();  // Safe
}
// Or use operator*
if (maybe_int) {
    int value = *maybe_int;  // Safe
}
// Or provide default
int value = maybe_int.value_or(0);  // Safe with fallback
```

### 3. std::variant Access Without Visitor
```cpp
// WRONG - Assumes which type is stored
std::variant<int, std::string> v = get_variant();
std::string s = std::get<std::string>(v);  // Might throw!

// RIGHT - Use std::visit for type safety
std::visit([](const auto& value) {
    using T = std::decay_t<decltype(value)>;
    if constexpr (std::is_same_v<T, int>) {
        std::cout << "Integer: " << value << "\n";
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "String: " << value << "\n";
    }
}, v);
```

---

## 📋 Move Semantics Quick Reference

### Move Constructor and Assignment
```cpp
class MyClass {
private:
    std::vector<int> data_;
    std::string name_;
    
public:
    // Move constructor
    MyClass(MyClass&& other) noexcept
        : data_(std::move(other.data_)),
          name_(std::move(other.name_)) {
        // other is now in valid but unspecified state
    }
    
    // Move assignment
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            name_ = std::move(other.name_);
        }
        return *this;
    }
};
```

### When Moves Happen Automatically
```cpp
// 1. Return by value (RVO/NRVO or move)
std::vector<int> create_vector() {
    std::vector<int> v{1, 2, 3};
    return v;  // RVO or move, never copy
}

// 2. Passing temporaries
void process(std::vector<int> data) { }
process({1, 2, 3});  // Move from temporary

// 3. Move initialization
std::vector<int> v1{1, 2, 3};
std::vector<int> v2 = std::move(v1);  // Explicit move

// 4. Container operations
std::vector<std::string> vec;
vec.push_back(std::string("hello"));  // Move from temporary
vec.emplace_back("world");            // Construct in place (better)
```

### std::exchange Pattern
```cpp
// Atomic replacement - returns old value
class Resource {
    std::unique_ptr<Data> data_;
    
public:
    // Move constructor using exchange
    Resource(Resource&& other) noexcept
        : data_(std::exchange(other.data_, nullptr)) {
        // other.data_ is now null, this->data_ has the value
    }
    
    // Setter with exchange
    void set_data(std::unique_ptr<Data> new_data) {
        auto old_data = std::exchange(data_, std::move(new_data));
        // old_data is automatically cleaned up
    }
};
```

---

## ⚡ std::optional Cheat Sheet

### Creation and Assignment
```cpp
#include <optional>

// Empty optional
std::optional<int> empty;
std::optional<int> also_empty = std::nullopt;

// With value
std::optional<int> with_value = 42;
std::optional<int> constructed{42};
std::optional<int> made = std::make_optional<int>(42);

// From function
std::optional<std::string> parse_config(const std::string& key);
```

### Checking and Access
```cpp
std::optional<int> maybe_int = get_value();

// Method 1: has_value() + value()
if (maybe_int.has_value()) {
    int val = maybe_int.value();
    std::cout << val << "\n";
}

// Method 2: Implicit bool + operator*
if (maybe_int) {
    int val = *maybe_int;
    std::cout << val << "\n";
}

// Method 3: value_or() with default
int val = maybe_int.value_or(0);
std::cout << val << "\n";  // Prints value or 0

// Method 4: Transform operations (C++23)
auto doubled = maybe_int.transform([](int x) { return x * 2; });
```

### Common Patterns
```cpp
// Optional chaining
std::optional<User> get_user(int id);
std::optional<Profile> get_profile(const User& user);

auto profile = get_user(123)
    .and_then([](const User& u) { return get_profile(u); })
    .transform([](const Profile& p) { return p.display_name; });

// Factory pattern
template<typename T, typename... Args>
std::optional<T> try_create(Args&&... args) {
    try {
        return T(std::forward<Args>(args)...);
    } catch (...) {
        return std::nullopt;
    }
}
```

---

## 🔧 std::variant Complete Guide

### Creation and Assignment
```cpp
#include <variant>

// Define variant type
using Value = std::variant<int, double, std::string>;

// Initialize with different types
Value v1 = 42;              // int
Value v2 = 3.14;            // double  
Value v3 = "hello";         // string
Value v4{std::string("world")}; // explicit string construction
```

### Type Checking and Access
```cpp
Value v = 42;

// Method 1: index()
if (v.index() == 0) {  // int is first alternative
    int val = std::get<0>(v);  // Access by index
}

// Method 2: holds_alternative()
if (std::holds_alternative<int>(v)) {
    int val = std::get<int>(v);  // Access by type
}

// Method 3: std::get_if (safe)
if (auto* ptr = std::get_if<int>(&v)) {
    int val = *ptr;  // ptr is not null, safe to dereference
}

// Method 4: try-catch
try {
    int val = std::get<int>(v);
} catch (const std::bad_variant_access&) {
    // Handle wrong type
}
```

### std::visit Pattern Matching
```cpp
Value v = get_some_value();

// Generic visitor
std::visit([](const auto& value) {
    std::cout << "Value: " << value << "\n";
}, v);

// Type-specific visitor  
std::visit([](const auto& value) {
    using T = std::decay_t<decltype(value)>;
    if constexpr (std::is_same_v<T, int>) {
        std::cout << "Integer: " << value << "\n";
    } else if constexpr (std::is_same_v<T, double>) {
        std::cout << "Double: " << value << "\n";
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "String: " << value << "\n";
    }
}, v);

// Visitor class
struct Printer {
    void operator()(int i) { std::cout << "Int: " << i << "\n"; }
    void operator()(double d) { std::cout << "Double: " << d << "\n"; }
    void operator()(const std::string& s) { std::cout << "String: " << s << "\n"; }
};

std::visit(Printer{}, v);
```

### Advanced Variant Patterns
```cpp
// Result type pattern
template<typename T, typename E>
using Result = std::variant<T, E>;

struct Error { std::string message; };

Result<int, Error> divide(int a, int b) {
    if (b == 0) return Error{"Division by zero"};
    return a / b;
}

// State machine pattern
struct Idle {};
struct Loading { std::string url; };
struct Ready { std::vector<std::string> data; };
struct Failed { std::string error; };

using State = std::variant<Idle, Loading, Ready, Failed>;

State handle_event(const State& current_state, const Event& event);
```

---

## 💾 std::any Quick Guide

### Basic Usage
```cpp
#include <any>

std::any value;

// Store different types
value = 42;
value = std::string("hello");
value = 3.14;
value = std::vector<int>{1, 2, 3};

// Check if empty
if (value.has_value()) {
    std::cout << "Has value\n";
}

// Get type info
std::cout << "Type: " << value.type().name() << "\n";

// Cast to retrieve
try {
    int i = std::any_cast<int>(value);
    std::cout << "Integer: " << i << "\n";
} catch (const std::bad_any_cast& e) {
    std::cout << "Wrong type: " << e.what() << "\n";
}

// Safe cast with pointer
if (auto* ptr = std::any_cast<int>(&value)) {
    std::cout << "Integer: " << *ptr << "\n";
} else {
    std::cout << "Not an integer\n";
}
```

### When to Use std::any
```cpp
// Good: Heterogeneous containers when types unknown at compile time
std::map<std::string, std::any> config;
config["window_width"] = 800;
config["window_height"] = 600;
config["title"] = std::string("My App");
config["fullscreen"] = false;

// Good: Plugin systems
class Plugin {
public:
    virtual std::any execute(const std::any& input) = 0;
};

// AVOID: When you know the possible types (use std::variant instead)
// std::any is slower and less type-safe than std::variant
```

---

## 🔍 Structured Bindings Quick Reference

### Basic Syntax
```cpp
// With std::pair
std::pair<int, std::string> get_id_and_name();
auto [id, name] = get_id_and_name();

// With std::tuple
std::tuple<int, double, std::string> get_data();
auto [count, average, label] = get_data();

// With arrays
int coordinates[3] = {10, 20, 30};
auto [x, y, z] = coordinates;

// With custom types (if structured binding is supported)
struct Point { int x, y; };
Point p{10, 20};
auto [px, py] = p;
```

### Container Iteration
```cpp
std::map<std::string, int> scores{{"Alice", 95}, {"Bob", 87}};

// Before structured bindings
for (const auto& pair : scores) {
    std::cout << pair.first << ": " << pair.second << "\n";
}

// With structured bindings
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << "\n";
}

// Modifying values
for (auto& [name, score] : scores) {
    score += 10;  // Bonus points!
}
```

---

## ⚠️ Performance Considerations

### Move vs Copy Performance
```cpp
// Expensive to copy
std::vector<int> large_vector(1000000, 42);

// SLOW: Copy
std::vector<int> copy = large_vector;  // Copies all elements

// FAST: Move  
std::vector<int> moved = std::move(large_vector);  // Just moves pointers

// FAST: Perfect forwarding
template<typename T>
void process(T&& value) {
    store_value(std::forward<T>(value));  // Preserves value category
}
```

### std::optional vs Pointer Performance
```cpp
// Similar performance for small types
std::optional<int> opt_int;     // sizeof(int) + bool flag
int* ptr_int = nullptr;         // sizeof(void*)

// optional might be better for larger types (no heap allocation)
std::optional<std::array<int, 100>> opt_array;  // Stack storage
std::unique_ptr<std::array<int, 100>> ptr_array; // Heap allocation
```

### std::variant vs std::any Performance
```cpp
// FASTER: std::variant (compile-time dispatch)
std::variant<int, double, std::string> v = 42;
std::visit([](const auto& x) { process(x); }, v);

// SLOWER: std::any (runtime type checking)
std::any a = 42;
if (a.type() == typeid(int)) {
    process(std::any_cast<int>(a));
}
```

---

## 🆘 Emergency Syntax Reference

### Move Operations
```cpp
// std::move - cast to rvalue reference
T&& moved = std::move(object);

// std::forward - perfect forwarding
template<typename T>
void func(T&& param) {
    other_func(std::forward<T>(param));
}

// std::exchange - atomic replace and return old
T old_value = std::exchange(variable, new_value);
```

### Optional Operations
```cpp
std::optional<T> opt;

opt = value;              // Assign value
opt = std::nullopt;       // Clear
opt.reset();              // Clear
opt.emplace(args...);     // Construct in place
bool has = opt.has_value(); // or if (opt)
T val = opt.value();      // May throw
T val = *opt;             // Direct access
T val = opt.value_or(default_val);
```

### Variant Operations
```cpp
std::variant<T1, T2, T3> var;

var = T1{};               // Assign first type
var.emplace<T2>(args);    // Construct T2 in place
size_t idx = var.index(); // Get current type index
bool has = std::holds_alternative<T1>(var);
T1 val = std::get<T1>(var);     // May throw
T1* ptr = std::get_if<T1>(&var); // Returns null if wrong type
std::visit(visitor, var);        // Apply visitor
```

**Remember**: Modern C++ utilities make code safer and more expressive. Use them to eliminate raw pointers, null checks, and type-unsafe operations!