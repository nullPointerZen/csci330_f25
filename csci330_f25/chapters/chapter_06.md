# Chapter 6: Compile-time Polymorphism

Welcome to compile-time polymorphism! This chapter introduces C++ templates - one of the most powerful and distinctive features of C++. Templates allow you to write generic code that works with multiple types while maintaining full type safety and zero runtime overhead.

## 📖 How This Chapter Works

**🔄 Learning Sequence (IMPORTANT!):**
1. **📚 FIRST**: Read Textbook Chapter 6 "Compile-Time Polymorphism" (3-4 hours)
2. **🔍 SECOND**: Work through the lecture notes below for Python/Java context and hands-on practice (7-9 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 6 "Compile-Time Polymorphism" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Understand** compile-time vs runtime polymorphism trade-offs
2. **Write** function templates that work with multiple types safely
3. **Create** template classes for generic data containers
4. **Debug** template instantiation errors effectively
5. **Apply** template argument deduction for cleaner code
6. **Compare** C++ templates with Java generics and Python's dynamic typing

**⏱️ Time Budget:**
- **📚 Textbook Reading: 3-4 hours** (Chapter 6: "Compile-Time Polymorphism" - REQUIRED FIRST)
- **🛠️ Setup: Included in Chapter 1** (VS Code + debugger setup)
- **💻 Hands-on Work: 7-9 hours** (lecture notes + assignments)

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](../DEVELOPMENT_SETUP.md). All debugging examples use VS Code + Docker.

---

# Lecture Notes

## 🔄 Core Concepts: Templates vs Virtual Functions

**📖 Bridge to Textbook**: Now that you've read about templates and compile-time polymorphism in Chapter 6, let's connect those concepts to Java generics and Python's dynamic typing.

### 1. The Motivation: Why Templates Matter

**Templates solve the code explosion problem:**

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
// ... Need more? Write more functions!
```

**Templates solve this**: Write once, work with any type:

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
- **Templates**: Zero runtime overhead, but larger executable
- **Virtual functions**: Small runtime overhead, smaller executable

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

**Template Argument Deduction:**

```cpp
// Easy cases - compiler deduces correctly
auto result1 = absolute_value(42);    // T = int
auto result2 = absolute_value(-3.14); // T = double

// Challenging cases - deduction can fail
template<typename T>
T maximum(T a, T b) { return (a > b) ? a : b; }

// maximum(5, 3.14);        // ERROR: T can't be both int and double
maximum<double>(5, 3.14);   // OK: Explicit type, 5 converted to double
maximum(5.0, 3.14);         // OK: Both are double
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

## 🧩 Hands-On Practice Problems

### Problem Set 1: Function Template Fundamentals (45 minutes)

#### Problem 1.1: Temperature Conversion Template
Create a practical template:

```cpp
#include <iostream>
using namespace std;

template<typename T>
T celsius_to_fahrenheit(T celsius) {
    return celsius * T{9} / T{5} + T{32};
}

template<typename T>  
T fahrenheit_to_celsius(T fahrenheit) {
    return (fahrenheit - T{32}) * T{5} / T{9};
}

template<typename T>
void display_temperature(T temp, const string& unit) {
    cout << "Temperature: " << temp << "°" << unit << endl;
}

int main() {
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
    
    return 0;
}
```

#### Problem 1.2: Multiple Template Parameters
Create a safe division function:

```cpp
#include <iostream>
using namespace std;

template<typename T, typename U>
auto safe_divide(T numerator, U denominator) -> decltype(numerator / denominator) {
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
    
    return 0;
}
```

### Problem Set 2: Class Templates (60 minutes)

#### Problem 2.1: Generic Stack Container
Build a templated stack:

```cpp
#include <iostream>
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
    Stack<int> int_stack{5};
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);
    
    cout << "Int stack size: " << int_stack.size() << endl;
    cout << "Popping: " << int_stack.pop() << endl;
    
    Stack<string> string_stack{3};
    string_stack.push("hello");
    string_stack.push("world");
    
    cout << "String stack size: " << string_stack.size() << endl;
    cout << "Popping: " << string_stack.pop() << endl;
    
    return 0;
}
```

#### Problem 2.2: Template Pair Class
Create a templated pair container:

```cpp
#include <iostream>
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
    
    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }
};

int main() {
    Pair<int, string> id_name{123, "Alice"};
    Pair<double, double> coordinates{3.14, 2.71};
    
    cout << "ID-Name pair: ";
    id_name.display();
    cout << endl;
    
    cout << "Coordinates: ";
    coordinates.display();
    cout << endl;
    
    return 0;
}
```

---

# Assignments

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 6 "Compile-Time Polymorphism"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Problem Set 1: Function Template Fundamentals (45 minutes)

### Problem 1.1: Basic Function Templates (15 minutes)
Write a function template called `absolute_value` that returns the absolute value of any numeric type.

**Requirements:**
- Template should work with int, double, float
- Use proper template syntax
- Test with both positive and negative values

### Problem 1.2: Multiple Template Parameters (20 minutes)
Create a function template `safe_divide` that takes two parameters of potentially different types and returns their quotient. Handle division by zero by returning 0.

### Problem 1.3: Template Argument Deduction (10 minutes)
Write a `swap` function template that exchanges the values of two variables. Demonstrate both explicit template arguments and automatic deduction.

## Problem Set 2: Template Classes (60 minutes)

### Problem 2.1: Simple Template Container (35 minutes)
Create a template class `Pair` that holds two values of the same type.

**Requirements:**
- Template class with two private members
- Constructor to initialize both values
- Getter methods `first()` and `second()`
- Setter methods `set_first()` and `set_second()`
- A `swap()` method that exchanges the two values

### Problem 2.2: Template Container with Dynamic Storage (25 minutes)
Extend the concept to create a `SimpleArray` template that manages dynamic memory.

**Requirements:**
- Constructor takes size parameter
- Proper destructor to avoid memory leaks
- `get(index)` and `set(index, value)` methods
- `size()` method
- Basic bounds checking

## Problem Set 3: Applied Templates and Debugging (40 minutes)

### Problem 3.1: Template Specialization Introduction (20 minutes)
Create a `Printer` template that has different behavior for different types.

**Requirements:**
- General template prints: "Value: [value]"
- Specialization for `bool` prints: "Boolean: true/false"  
- Specialization for `string` prints: "Text: [value]"

### Problem 3.2: Debugging Template Errors (20 minutes)
Fix the provided buggy template code. Learn to read template error messages.

## Submission Guidelines

**File organization**:
```
chapter06_solutions/
├── problem_1_1.cpp
├── problem_1_2.cpp
├── problem_1_3.cpp
├── problem_2_1.cpp
├── problem_2_2.cpp
├── problem_3_1.cpp
├── problem_3_2.cpp
└── README.md (with compilation notes)
```

---

# Quick Reference

## Top 5 Template Errors

### 1. Forgetting Template Declaration
```cpp
// ❌ Error: 'T' was not declared in this scope
T maximum(T a, T b) { return (a > b) ? a : b; }

// ✅ Solution: Add template declaration above function
template<typename T>
T maximum(T a, T b) { return (a > b) ? a : b; }
```

### 2. Mixed Type Deduction Failures
```cpp
template<typename T>
T add(T a, T b) { return a + b; }

// ❌ Error: Can't deduce T (int vs double)
auto result = add(5, 3.14);

// ✅ Solutions:
auto result1 = add<double>(5, 3.14);  // Explicit type
auto result2 = add(5.0, 3.14);        // Make types match
```

### 3. Template Definition in Wrong Place
```cpp
// ❌ Problem: Template implementation in .cpp file won't link!
// ✅ Solution: Keep template definitions in headers
```

### 4. Template Syntax Confusion
```cpp
// All valid, but use consistent style
template<class T>        // Old C++ style - still works
template<typename T>     // Modern preferred style
```

### 5. Specialization Syntax Errors
```cpp
template<typename T>
void print_value(T value) { cout << "Generic: " << value; }

// ❌ Wrong: Missing template<> 
void print_value<int>(int value) { cout << "Integer: " << value; }

// ✅ Correct: Full specialization syntax
template<>
void print_value<int>(int value) { cout << "Integer: " << value; }
```

## Template Best Practices

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
```

## Success Checklist

After Chapter 6, you should be able to:
- [ ] Write basic function templates with proper syntax
- [ ] Understand template argument deduction
- [ ] Create class templates for generic containers
- [ ] Know when to use explicit template parameters
- [ ] Debug template instantiation errors
- [ ] Understand when templates are better than virtual functions

**Not there yet?** Focus on the core concepts - templates are resolved at compile time and provide zero runtime overhead. This is C++'s unique strength.

**Ready to move on?** Great! Chapter 7 will cover expressions and operator overloading.

---

## What's Next?

**Chapter 7: Expressions** will cover:
- Expression evaluation and operator precedence
- Operator overloading for custom types
- Type conversions and casting
- Expression templates and advanced techniques

**You've mastered compile-time polymorphism!** Templates provide compile-time polymorphism with zero runtime overhead - a unique strength of C++.

---

*Remember: Templates are resolved at compile time, so all types must be known when you compile. This trade-off gives you maximum performance with full type safety!*