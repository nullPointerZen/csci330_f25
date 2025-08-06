# Chapter 6: Compile-Time Polymorphism - Complete Guide

## 🎯 Learning Objectives (5 minutes)

By the end of this chapter, you will:
1. **Understand** compile-time vs runtime polymorphism trade-offs
2. **Write** function templates that work with multiple types safely
3. **Create** template classes for generic data containers
4. **Debug** template instantiation errors effectively
5. **Apply** template argument deduction for cleaner code
6. **Compare** C++ templates with Java generics and Python's dynamic typing

**⏱️ Time Budget: ~4.75 hours total**
- Learning: 2.5 hours
- Problems: 2.25 hours

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](./DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 🔄 Core Concepts: Templates vs Virtual Functions (2.5 hours)

### 1. Why Templates? The Code Duplication Problem

**Problem**: Without templates, you need separate functions for each type:

```cpp
// Without templates - lots of duplication!
int max_int(int a, int b) { return (a > b) ? a : b; }
double max_double(double a, double b) { return (a > b) ? a : b; }
string max_string(string a, string b) { return (a > b) ? a : b; }
```

**Solution**: Templates let you write one function that works for multiple types:

```cpp
// With templates - one function for all!
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Usage - compiler creates specific versions automatically
int result1 = maximum(5, 3);        // Creates maximum<int>
double result2 = maximum(3.14, 2.5); // Creates maximum<double>
string result3 = maximum("hello", "world"); // Creates maximum<string>
```

### 2. Compile-Time vs Runtime Polymorphism

| Aspect | Templates (Compile-time) | Virtual Functions (Runtime) |
|--------|-------------------------|----------------------------|
| **When decided** | Compile time | Runtime |
| **Performance** | Faster (no overhead) | Slower (virtual call overhead) |
| **Code size** | Larger (separate code for each type) | Smaller (one function) |
| **Type safety** | Very strong | Strong |
| **Flexibility** | Types must be known at compile time | Types can be determined at runtime |

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

**Template Argument Deduction**: The compiler figures out types automatically:

```cpp
auto result1 = absolute_value(42);    // T = int
auto result2 = absolute_value(-3.14); // T = double
auto result3 = safe_divide(10, 3.0);  // T = int, U = double
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

### Problem Set 1: Function Template Fundamentals (45 minutes)

#### Problem 1.1: Basic Function Template (15 minutes)
**Create a generic absolute value function:**

```cpp
#include <iostream>
using namespace std;

template<typename T>
T absolute_value(T value) {
    // TODO: Return absolute value
    // Hint: Compare with T{} (default-constructed T)
    return (value < T{}) ? -value : value;
}

int main() {
    cout << "absolute_value(-5) = " << absolute_value(-5) << endl;
    cout << "absolute_value(-3.14) = " << absolute_value(-3.14) << endl;
    cout << "absolute_value(42) = " << absolute_value(42) << endl;
    
    // TODO: Test with different types
    cout << "absolute_value(-2.5f) = " << absolute_value(-2.5f) << endl;
    
    return 0;
}
```

**Expected Output:**
```
absolute_value(-5) = 5
absolute_value(-3.14) = 3.14
absolute_value(42) = 42
absolute_value(-2.5f) = 2.5
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

#### Problem 1.3: Template Argument Deduction (10 minutes)
**Practice with automatic type deduction:**

```cpp
#include <iostream>
#include <string>
using namespace std;

template<typename T>
T maximum(T a, T b, T c) {
    T result = a;
    if (b > result) result = b;
    if (c > result) result = c;
    return result;
}

int main() {
    // TODO: Call maximum with different types
    // What happens with mixed types?
    
    cout << "max(1, 5, 3) = " << maximum(1, 5, 3) << endl;
    cout << "max(1.1, 5.5, 3.3) = " << maximum(1.1, 5.5, 3.3) << endl;
    cout << "max(\"apple\", \"zebra\", \"banana\") = " 
         << maximum(string("apple"), string("zebra"), string("banana")) << endl;
    
    // TODO: Try this - what error do you get?
    // cout << maximum(1, 2.5, 3) << endl;  // Mixed types!
    
    // TODO: Fix mixed types with explicit template parameter
    cout << "max<double>(1, 2.5, 3) = " << maximum<double>(1, 2.5, 3) << endl;
    
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

### Top 5 Template Errors

#### 1. Missing Template Declaration
```cpp
T maximum(T a, T b) { return (a > b) ? a : b; }  // ❌ T not declared

template<typename T>
T maximum(T a, T b) { return (a > b) ? a : b; }  // ✅ Proper template
```

#### 2. Template Argument Deduction Failure
```cpp
maximum(5, 3.14);                    // ❌ int vs double - ambiguous

maximum<double>(5, 3.14);            // ✅ Explicit type
maximum(5.0, 3.14);                  // ✅ Same types
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

#### 4. Incorrect Template Syntax
```cpp
template<class T, class U>            // ✅ Valid but old style
template<typename T, typename U>      // ✅ Modern preferred style
template<T, U>                        // ❌ Missing typename/class
```

#### 5. Template Specialization Issues
```cpp
template<typename T>
void func() { /* primary */ }

void func<int>() { /* specialization */ }  // ❌ Missing template<>

template<>
void func<int>() { /* specialization */ }  // ✅ Correct specialization
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