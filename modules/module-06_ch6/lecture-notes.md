# Chapter 6: Compile-Time Polymorphism - Complete Guide

## 📖 Learning Sequence (IMPORTANT!)

**🔄 How This Chapter Works:**
1. **📚 FIRST**: Read Textbook Chapter 6 "Compile-Time Polymorphism" (3-4 hours)
2. **🔍 SECOND**: Work through these lecture notes for Python/Java context and hands-on practice (7-9 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 6 "Compile-Time Polymorphism" FIRST**
**📝 Template Warning**: Templates are one of the most challenging C++ concepts - thorough textbook reading is essential before attempting assignments.

After completing the textbook reading and this chapter's materials, you will:
1. **Understand** compile-time vs runtime polymorphism trade-offs
2. **Write** function templates that work with multiple types safely
3. **Create** template classes for generic data containers
4. **Debug** template instantiation errors effectively
5. **Apply** template argument deduction for cleaner code
6. **Compare** C++ templates with Java generics and Python's dynamic typing

**⏱️ Time Budget:**
- **📚 Textbook Reading: 3-4 hours** (Chapter 6: "Compile-Time Polymorphism" - REQUIRED FIRST, complex topic)
- **🔍 Learning: 2.5 hours** (core concepts with Python/Java context)
- **💻 Hands-on Work: 4.5-6.5 hours** (comprehensive template assignments + debugging)
- **✅ Assignments: 2.25 hours** (demonstrate mastery)
- **📖 Note: Reading time is separate and must be completed BEFORE hands-on work**
- **📖 Reading Note**: Templates are complex - the author's step-by-step approach is invaluable

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](../../setup/DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 🔄 Core Concepts: Templates vs Virtual Functions (2.5 hours)

**📖 Bridge to Textbook**: Now that you've read about templates and compile-time polymorphism in Chapter 6, let's connect those concepts to Java generics and Python's dynamic typing, and see them in action.

### 1. The Motivation: Why Templates Matter

**Real-world scenario**: You're building a data processing system that needs to work with different number types:

```cpp
// Without templates - code explosion as requirements grow
double calculate_average(const vector<double>& data) {
    double sum = 0;
    for (double value : data) sum += value;
    return sum / data.size();
}

float calculate_average(const vector<float>& data) {
    float sum = 0;
    for (float value : data) sum += value;
    return sum / data.size();
}

int calculate_average(const vector<int>& data) {
    int sum = 0;
    for (int value : data) sum += value;
    return sum / data.size();
}
// ... Need more? Write more functions!
```

**Templates solve this**: Write once, work with any type that supports the operations:

```cpp
template<typename T>
T calculate_average(const vector<T>& data) {
    T sum = T{};  // Default-initialized sum
    for (const T& value : data) sum += value;
    return sum / static_cast<T>(data.size());
}

// Compiler automatically creates the right version:
auto avg1 = calculate_average(vector<double>{1.1, 2.2, 3.3});  // double version
auto avg2 = calculate_average(vector<int>{10, 20, 30});        // int version
```

### 2. Compile-Time vs Runtime Polymorphism

**When to use templates vs virtual functions:**

| **Use Templates When...** | **Use Virtual Functions When...** |
|---------------------------|------------------------------------|
| You know all types at compile time | Types are determined at runtime |
| You want maximum performance | You need runtime flexibility |
| Working with value types (int, double) | Working with object hierarchies |
| You need type-specific optimizations | You want a common interface |

**Performance & Trade-offs:**
- **Templates**: Zero runtime overhead, but larger executable (code for each type)
- **Virtual functions**: Small runtime overhead, smaller executable (one implementation)

**Example decision**:
```cpp
// Template - for math operations on known numeric types
template<typename T> T square(T x) { return x * x; }

// Virtual - for different drawing behaviors determined at runtime  
struct Shape { virtual void draw() = 0; };
```

**Python/Java Connection**:
- **Templates** are like Python's duck typing but checked at compile time
- **Virtual functions** are like Java's polymorphism through inheritance

### 3. Function Templates

**Basic syntax for function templates:**

```cpp
template<typename T>
T absolute_value(T value) {
    return (value < T{}) ? -value : value;
}

// Multiple template parameters
template<typename T, typename U>
auto safe_divide(T numerator, U denominator) -> decltype(numerator / denominator) {
    if (denominator != U{}) {
        return numerator / denominator;
    }
    return decltype(numerator / denominator){};
}
```

**Template Argument Deduction**: The compiler figures out types automatically, but this can sometimes be tricky:

```cpp
// Easy cases - compiler deduces correctly
auto result1 = absolute_value(42);    // T = int
auto result2 = absolute_value(-3.14); // T = double

// Challenging cases - deduction can fail or be ambiguous
template<typename T>
T maximum(T a, T b) { return (a > b) ? a : b; }

// maximum(5, 3.14);        // ERROR: T can't be both int and double
maximum<double>(5, 3.14);   // OK: Explicit type, 5 converted to double
maximum(5.0, 3.14);         // OK: Both are double

// Pro tip: Use auto parameters in C++14+ for even more flexibility
auto generic_max = [](auto a, auto b) { return (a > b) ? a : b; };
generic_max(5, 3.14);       // OK: Each parameter can be different type
```

### 4. Class Templates

**Templates work with classes too:**

```cpp
template<typename T>
class SimpleVector {
public:
    SimpleVector(size_t capacity) : capacity_{capacity}, size_{0} {
        data_ = new T[capacity_];
    }
    
    ~SimpleVector() {
        delete[] data_;
    }
    
    void push_back(const T& value) {
        if (size_ < capacity_) {
            data_[size_++] = value;
        }
    }
    
    T& operator[](size_t index) {
        return data_[index];
    }
    
    size_t size() const { return size_; }
    
private:
    T* data_;
    size_t capacity_;
    size_t size_;
};

// Usage
SimpleVector<int> int_vector{10};
SimpleVector<string> string_vector{5};
```

**Compared to Languages**:
- **Java**: `ArrayList<Integer>` - similar concept, type erasure at runtime
- **Python**: Lists hold any type - C++ templates are type-safe versions

### 5. Template Specialization

**Sometimes you need special behavior for specific types:**

```cpp
template<typename T>
struct TypeInfo {
    static string name() { return "unknown"; }
};

// Specialization for int
template<>
struct TypeInfo<int> {
    static string name() { return "integer"; }
};

// Specialization for string
template<>
struct TypeInfo<string> {
    static string name() { return "text string"; }
};

// Usage
cout << TypeInfo<int>::name() << "\n";    // "integer"
cout << TypeInfo<double>::name() << "\n"; // "unknown"
cout << TypeInfo<string>::name() << "\n"; // "text string"
```

---

## 🧩 Hands-On Problems (2.25 hours)

**📖 Ready to Apply**: You've read the textbook and reviewed the Python/Java connections above. Now let's put that knowledge to work with hands-on practice that prepares you for the assignments.

### Problem Set 1: Function Template Fundamentals (45 minutes)

#### Problem 1.1: Temperature Conversion Template (15 minutes)
**Create a practical template that students can relate to:**

```cpp
#include <iostream>
using namespace std;

// TODO: Create template for temperature conversion
template<typename T>
T celsius_to_fahrenheit(T celsius) {
    return celsius * T{9} / T{5} + T{32};
}

template<typename T>  
T fahrenheit_to_celsius(T fahrenheit) {
    return (fahrenheit - T{32}) * T{5} / T{9};
}

// TODO: Generic temperature display
template<typename T>
void display_temperature(T temp, const string& unit) {
    cout << "Temperature: " << temp << "°" << unit << endl;
}

int main() {
    // TODO: Test with different numeric types
    cout << "=== Integer Temperatures ===\n";
    int temp_c = 25;
    int temp_f = celsius_to_fahrenheit(temp_c);
    display_temperature(temp_c, "C");
    display_temperature(temp_f, "F");
    
    cout << "\n=== Precise Temperatures ===\n";
    double precise_c = 23.5;
    double precise_f = celsius_to_fahrenheit(precise_c);
    display_temperature(precise_c, "C");
    display_temperature(precise_f, "F");
    
    cout << "\n=== Converting Back ===\n";
    double back_to_c = fahrenheit_to_celsius(precise_f);
    display_temperature(back_to_c, "C (converted back)");
    
    return 0;
}
```

**Expected Output:**
```
=== Integer Temperatures ===
Temperature: 25°C
Temperature: 77°F

=== Precise Temperatures ===
Temperature: 23.5°C
Temperature: 74.3°F

=== Converting Back ===
Temperature: 23.5°C (converted back)
```

#### Problem 1.2: Multiple Template Parameters (20 minutes)
**Create a safe division function with two template types:**

```cpp
#include <iostream>
using namespace std;

template<typename T, typename U>
auto safe_divide(T numerator, U denominator) -> decltype(numerator / denominator) {
    // TODO: Check for zero denominator
    if (denominator != U{}) {
        return numerator / denominator;
    }
    return decltype(numerator / denominator){};  // Return zero of result type
}

int main() {
    cout << "safe_divide(10, 3) = " << safe_divide(10, 3) << endl;
    cout << "safe_divide(10.0, 3) = " << safe_divide(10.0, 3) << endl;
    cout << "safe_divide(10, 3.0) = " << safe_divide(10, 3.0) << endl;
    cout << "safe_divide(10, 0) = " << safe_divide(10, 0) << endl;
    cout << "safe_divide(10.5, 0.0) = " << safe_divide(10.5, 0.0) << endl;
    
    return 0;
}
```

#### Problem 1.3: Smart Template Deduction (10 minutes)
**Learn when deduction works and when it fails:**

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// TODO: Template that finds average of any container
template<typename Container>
auto calculate_average(const Container& data) {
    using ValueType = typename Container::value_type;
    ValueType sum = ValueType{};
    
    for (const auto& value : data) {
        sum += value;
    }
    
    return static_cast<double>(sum) / data.size();
}

// TODO: Function to demonstrate deduction challenges
template<typename T>
void compare_and_print(T a, T b) {
    cout << "Comparing " << a << " and " << b;
    cout << " -> larger is " << ((a > b) ? a : b) << endl;
}

int main() {
    // TODO: Test with different containers - deduction works!
    vector<int> grades = {85, 92, 78, 96, 88};
    vector<double> prices = {12.99, 8.50, 15.25, 22.00};
    
    cout << "Average grade: " << calculate_average(grades) << endl;
    cout << "Average price: $" << calculate_average(prices) << endl;
    
    // TODO: Test deduction successes and failures
    cout << "\n=== Deduction Examples ===\n";
    compare_and_print(10, 5);        // OK: both int
    compare_and_print(3.14, 2.71);   // OK: both double
    
    // TODO: This would fail - mixed types!
    // compare_and_print(10, 3.14);  // ERROR: T can't be both int and double
    
    // TODO: Solutions for mixed types
    compare_and_print<double>(10, 3.14);  // Explicit type
    compare_and_print(10.0, 3.14);        // Make both same type
    
    return 0;
}
```

### Problem Set 2: Class Templates (60 minutes)

#### Problem 2.1: Generic Stack Container (25 minutes)
**Build a templated stack data structure:**

```cpp
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Stack {
public:
    Stack(size_t capacity = 10) : capacity_{capacity}, size_{0} {
        data_ = new T[capacity_];
    }
    
    ~Stack() {
        delete[] data_;
    }
    
    void push(const T& value) {
        if (size_ < capacity_) {
            data_[size_++] = value;
        } else {
            cout << "Stack overflow!\n";
        }
    }
    
    T pop() {
        if (size_ > 0) {
            return data_[--size_];
        } else {
            cout << "Stack underflow!\n";
            return T{};  // Return default-constructed T
        }
    }
    
    T& top() {
        return data_[size_ - 1];
    }
    
    bool empty() const {
        return size_ == 0;
    }
    
    size_t size() const {
        return size_;
    }
    
private:
    T* data_;
    size_t capacity_;
    size_t size_;
};

int main() {
    // TODO: Test with int stack
    Stack<int> int_stack{5};
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);
    
    cout << "Int stack size: " << int_stack.size() << endl;
    cout << "Popping: " << int_stack.pop() << endl;
    cout << "Top: " << int_stack.top() << endl;
    
    // TODO: Test with string stack
    Stack<string> string_stack{3};
    string_stack.push("hello");
    string_stack.push("world");
    
    cout << "String stack size: " << string_stack.size() << endl;
    cout << "Popping: " << string_stack.pop() << endl;
    
    return 0;
}
```

#### Problem 2.2: Template Pair Class (20 minutes)
**Create a templated pair container:**

```cpp
#include <iostream>
#include <string>
using namespace std;

template<typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;
    
    Pair(const T1& f, const T2& s) : first{f}, second{s} {}
    
    void display() const {
        cout << "(" << first << ", " << second << ")";
    }
    
    // TODO: Add comparison operators
    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }
    
    bool operator!=(const Pair& other) const {
        return !(*this == other);
    }
};

int main() {
    // TODO: Create different types of pairs
    Pair<int, string> id_name{123, "Alice"};
    Pair<double, double> coordinates{3.14, 2.71};
    Pair<string, int> word_count{"hello", 5};
    
    cout << "ID-Name pair: ";
    id_name.display();
    cout << endl;
    
    cout << "Coordinates: ";
    coordinates.display();
    cout << endl;
    
    cout << "Word-Count: ";
    word_count.display();
    cout << endl;
    
    // TODO: Test comparison
    Pair<int, string> another_pair{123, "Alice"};
    cout << "Pairs equal? " << (id_name == another_pair) << endl;
    
    return 0;
}
```

#### Problem 2.3: Generic Array with Bounds Checking (15 minutes)
**Build a safe array template:**

```cpp
#include <iostream>
using namespace std;

template<typename T, size_t N>
class Array {
public:
    Array() {
        // Initialize all elements to default value
        for (size_t i = 0; i < N; i++) {
            data_[i] = T{};
        }
    }
    
    T& operator[](size_t index) {
        if (index >= N) {
            cout << "Index " << index << " out of bounds for array of size " << N << endl;
            return data_[0];  // Return first element as fallback
        }
        return data_[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= N) {
            cout << "Index " << index << " out of bounds for array of size " << N << endl;
            return data_[0];
        }
        return data_[index];
    }
    
    constexpr size_t size() const {
        return N;
    }
    
    void fill(const T& value) {
        for (size_t i = 0; i < N; i++) {
            data_[i] = value;
        }
    }
    
private:
    T data_[N];
};

int main() {
    // TODO: Create arrays of different types and sizes
    Array<int, 5> int_array;
    Array<string, 3> string_array;
    
    // TODO: Test bounds checking
    int_array[0] = 10;
    int_array[1] = 20;
    int_array[10] = 30;  // Should trigger bounds check
    
    string_array.fill("hello");
    
    cout << "Int array size: " << int_array.size() << endl;
    cout << "String array size: " << string_array.size() << endl;
    
    return 0;
}
```

### Problem Set 3: Advanced Templates (40 minutes)

#### Problem 3.1: Template Specialization (20 minutes)
**Create specialized behavior for specific types:**

```cpp
#include <iostream>
#include <string>
using namespace std;

// Primary template
template<typename T>
struct Printer {
    static void print(const T& value) {
        cout << "Generic: " << value << endl;
    }
};

// TODO: Specialize for bool
template<>
struct Printer<bool> {
    static void print(const bool& value) {
        cout << "Boolean: " << (value ? "true" : "false") << endl;
    }
};

// TODO: Specialize for string
template<>
struct Printer<string> {
    static void print(const string& value) {
        cout << "String: \"" << value << "\"" << endl;
    }
};

// TODO: Specialize for pointers
template<typename T>
struct Printer<T*> {
    static void print(T* const& value) {
        if (value) {
            cout << "Pointer to: ";
            Printer<T>::print(*value);
        } else {
            cout << "Null pointer" << endl;
        }
    }
};

int main() {
    Printer<int>::print(42);
    Printer<bool>::print(true);
    Printer<string>::print("Hello World");
    Printer<double>::print(3.14159);
    
    int value = 100;
    int* ptr = &value;
    Printer<int*>::print(ptr);
    
    int* null_ptr = nullptr;
    Printer<int*>::print(null_ptr);
    
    return 0;
}
```

#### Problem 3.2: Function Template with Constraints (20 minutes)
**Create templates that work only with certain types:**

```cpp
#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

// Template that only works with numeric types
template<typename T>
typename enable_if<is_arithmetic<T>::value, T>::type
square(T value) {
    return value * value;
}

// Template that only works with types that have size() method
template<typename Container>
auto get_size(const Container& container) -> decltype(container.size()) {
    return container.size();
}

// Generic swap function
template<typename T>
void my_swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    // TODO: Test numeric square function
    cout << "square(5) = " << square(5) << endl;
    cout << "square(3.14) = " << square(3.14) << endl;
    // cout << square("hello") << endl;  // This would cause a compile error
    
    // TODO: Test container size function
    string text = "hello";
    cout << "size of \"hello\" = " << get_size(text) << endl;
    
    // TODO: Test swap function
    int x = 10, y = 20;
    cout << "Before swap: x=" << x << ", y=" << y << endl;
    my_swap(x, y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    string a = "first", b = "second";
    cout << "Before swap: a=" << a << ", b=" << b << endl;
    my_swap(a, b);
    cout << "After swap: a=" << a << ", b=" << b << endl;
    
    return 0;
}
```

---

## 🔧 Quick Reference & Troubleshooting

### Common Template Pitfalls and Solutions

#### 1. Forgetting Template Declaration
```cpp
// ❌ Error: 'T' was not declared in this scope
T maximum(T a, T b) { return (a > b) ? a : b; }

// ✅ Solution: Add template declaration above function
template<typename T>
T maximum(T a, T b) { return (a > b) ? a : b; }
```

#### 2. Mixed Type Deduction Failures
```cpp
template<typename T>
T add(T a, T b) { return a + b; }

// ❌ Error: Can't deduce T (int vs double)
auto result = add(5, 3.14);

// ✅ Solutions:
auto result1 = add<double>(5, 3.14);  // Explicit type
auto result2 = add(5.0, 3.14);        // Make types match

// ✅ Better: Use separate template parameters
template<typename T, typename U>
auto flexible_add(T a, U b) -> decltype(a + b) {
    return a + b;
}
```

#### 3. Template Definition in Wrong Place
```cpp
// header.h
template<typename T> class MyClass;   // ❌ Declaration only

// header.h
template<typename T>
class MyClass {                       // ✅ Full definition
    T data;
public:
    void method() { /* implementation */ }
};
```

#### 4. Template Syntax Confusion
```cpp
// All valid, but use consistent style
template<class T>        // Old C++ style - still works
template<typename T>     // Modern preferred style
// template<T>           // ❌ Missing typename/class keyword
```

#### 5. Specialization Syntax Errors
```cpp
template<typename T>
void print_value(T value) { cout << "Generic: " << value; }

// ❌ Wrong: Missing template<> 
void print_value<int>(int value) { cout << "Integer: " << value; }

// ✅ Correct: Full specialization syntax
template<>
void print_value<int>(int value) { cout << "Integer: " << value; }
```

#### 6. Template Definition Placement
```cpp
// ❌ Problem: Template implementation in .cpp file
// header.h
template<typename T> void func(T value);

// source.cpp  
template<typename T> void func(T value) { /* impl */ }  // Won't link!

// ✅ Solution: Keep template definitions in headers
template<typename T>
void func(T value) { /* implementation here */ }
```

### Template Best Practices

```cpp
// 1. Use meaningful template parameter names
template<typename ElementType>  // Better than just T
class Container { /*...*/ };

// 2. Provide default template arguments when useful
template<typename T, size_t Size = 10>
class FixedArray { /*...*/ };

// 3. Use auto for complex return types
template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

// 4. Consider using concepts (C++20) for better error messages
template<typename T>
requires std::is_arithmetic_v<T>
T square(T value) {
    return value * value;
}
```

---

## ✅ Chapter 6 Success Checklist

### Template Fundamentals
- [ ] Can write basic function templates with proper syntax
- [ ] Understand template argument deduction
- [ ] Can create class templates for generic containers
- [ ] Know when to use explicit template parameters

### Advanced Template Features
- [ ] Can write template specializations for specific types
- [ ] Understand the difference between compile-time and runtime polymorphism
- [ ] Can debug template instantiation errors
- [ ] Know template best practices and conventions

### Practical Applications
- [ ] Can create generic utility functions (max, swap, etc.)
- [ ] Can build templated data structures (stack, array, pair)
- [ ] Can apply templates to solve real programming problems
- [ ] Understand when templates are better than virtual functions

---

## 🚀 What's Next?

**Chapter 7: Expressions** will cover:
- Expression evaluation and operator precedence
- Operator overloading for custom types
- Type conversions and casting
- Expression templates and advanced techniques

**You've mastered compile-time polymorphism!** 🎉 Templates are one of C++'s most powerful features, enabling generic programming with zero runtime overhead. You now understand how to write code that works with multiple types while maintaining full type safety.

**Key Takeaway**: Templates provide compile-time polymorphism - the compiler generates specific code for each type you use. This gives you both flexibility and performance, making C++ templates more powerful than Java generics or Python's dynamic typing.

---

*Remember: Templates are resolved at compile time, so all types must be known when you compile. This trade-off gives you maximum performance with full type safety - a unique strength of C++!*