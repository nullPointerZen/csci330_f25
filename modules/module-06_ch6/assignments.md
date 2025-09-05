# Chapter 6: Compile-Time Polymorphism - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 6 "Compile-Time Polymorphism"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

**Total Time: 1.5 hours across both problem sets**

## Problem Set 1: Template Fundamentals and Classes (50 minutes)

### Problem 1.1: Essential Function Templates (15 minutes)
Create a comprehensive template utility with multiple functions.

**Requirements:**
- `absolute_value` template for any numeric type
- `safe_divide` template with zero-division handling  
- `swap` template with both explicit and automatic deduction

**Complete Template:**
```cpp
#include <iostream>
using namespace std;

// Absolute value template
template<typename T>
T absolute_value(T value) {
    // Implement this - handle negative values
}

// Safe division template
template<typename T1, typename T2>
auto safe_divide(T1 numerator, T2 denominator) -> decltype(numerator/denominator) {
    // Implement this - handle division by zero by returning 0
}

// Swap template
template<typename T>
void swap_values(T& a, T& b) {
    // Implement this to exchange values
}

int main() {
    // Test absolute_value
    cout << "=== Absolute Value Tests ===" << endl;
    cout << "absolute_value(-5) = " << absolute_value(-5) << endl;
    cout << "absolute_value(-3.14) = " << absolute_value(-3.14) << endl;
    cout << "absolute_value(42) = " << absolute_value(42) << endl;
    
    // Test safe_divide
    cout << "\n=== Safe Division Tests ===" << endl;
    cout << "10 / 2 = " << safe_divide(10, 2) << endl;
    cout << "10.5 / 2 = " << safe_divide(10.5, 2) << endl;
    cout << "10 / 0 = " << safe_divide(10, 0) << " (division by zero)" << endl;
    
    // Test swap
    cout << "\n=== Swap Tests ===" << endl;
    int x = 10, y = 20;
    cout << "Before swap: x=" << x << ", y=" << y << endl;
    swap_values(x, y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    return 0;
}
```

### Problem 1.2: Template Container Class (35 minutes)
Create a `Pair` template class and extend it to `SimpleArray` for dynamic storage.

**Requirements:**
- `Pair<T>` class with two values, getters, setters, and swap method
- `SimpleArray<T>` class with dynamic memory, proper destructor, bounds checking

**Complete Template:**
```cpp
#include <iostream>
#include <string>
using namespace std;

// Pair template class
template<typename T>
class Pair {
private:
    T first_value;
    T second_value;
public:
    // Constructor
    Pair(T first, T second) : first_value(first), second_value(second) {}
    
    // Getters
    T first() const { return first_value; }
    T second() const { return second_value; }
    
    // Setters
    void set_first(T value) { /* implement */ }
    void set_second(T value) { /* implement */ }
    
    // Swap method
    void swap() { /* implement - exchange first and second */ }
};

// SimpleArray template class
template<typename T>
class SimpleArray {
private:
    T* data;
    size_t array_size;
public:
    SimpleArray(size_t size) : array_size(size) {
        data = new T[size];
    }
    
    ~SimpleArray() {
        delete[] data;
    }
    
    // Disable copying to prevent double-delete
    SimpleArray(const SimpleArray&) = delete;
    SimpleArray& operator=(const SimpleArray&) = delete;
    
    // Methods to implement
    T get(size_t index) const {
        // Add bounds checking - print error for invalid index
        // Return data[index] if valid
    }
    
    void set(size_t index, const T& value) {
        // Add bounds checking - print error for invalid index
        // Set data[index] = value if valid
    }
    
    size_t size() const { return array_size; }
};

int main() {
    // Test Pair class
    cout << "=== Pair Class Tests ===" << endl;
    Pair<int> numbers(10, 20);
    cout << "First: " << numbers.first() << ", Second: " << numbers.second() << endl;
    
    numbers.swap();
    cout << "After swap - First: " << numbers.first() << ", Second: " << numbers.second() << endl;
    
    Pair<string> words("hello", "world");
    cout << words.first() << " " << words.second() << endl;
    
    // Test SimpleArray class
    cout << "\n=== SimpleArray Class Tests ===" << endl;
    SimpleArray<int> numbers_array(5);
    numbers_array.set(0, 100);
    numbers_array.set(1, 200);
    cout << "numbers[0] = " << numbers_array.get(0) << endl;
    cout << "Size: " << numbers_array.size() << endl;
    
    // Test bounds checking
    numbers_array.get(10);  // Should show error
    
    SimpleArray<string> words_array(3);
    words_array.set(0, "apple");
    words_array.set(1, "banana");
    cout << "words[0] = " << words_array.get(0) << endl;
    
    return 0;
}
```

---

### Problem 2.1: Template Specialization and Debugging (25 minutes)
Create a `Printer` template with specializations and fix template errors.

**Requirements:**
- General template prints: "Value: [value]"
- Specializations for `bool` and `string` types
- Fix provided buggy template code
- Understand and explain template error messages

**Complete Template:**
```cpp
#include <iostream>
#include <string>
using namespace std;

// General template
template<typename T>
class Printer {
public:
    static void print(const T& value) {
        cout << "Value: " << value << endl;
    }
};

// TODO: Add specialization for bool
template<>
class Printer<bool> {
public:
    static void print(const bool& value) {
        cout << "Boolean: " << (value ? "true" : "false") << endl;
    }
};

// TODO: Add specialization for string
template<>
class Printer<string> {
public:
    static void print(const string& value) {
        // Implement: print "Text: [value]"
    }
};

// DEBUGGING EXERCISE: Fix the Calculator template
template<typename T>
class Calculator {
private:
    T value;
public:
    Calculator(T initial) : value(initial) {}
    
    void add(T amount) {
        value += amount;
    }
    
    void print() {
        cout << "Result: " << value << endl;
    }
    
    // TODO: Fix this declaration for outside definition
    T getValue();
};

// TODO: Fix this template method definition
// HINT: Need proper template syntax
template<typename T>
T Calculator<T>::getValue() {
    return value;
}

int main() {
    // Test Printer specializations
    cout << "=== Printer Tests ===" << endl;
    Printer<int>::print(42);
    Printer<bool>::print(true);
    Printer<string>::print("hello world");
    Printer<double>::print(3.14);
    
    // Test fixed Calculator
    cout << "\n=== Calculator Tests ===" << endl;
    Calculator<int> calc(10);
    calc.add(5);
    calc.print();
    cout << "Final value: " << calc.getValue() << endl;
    
    return 0;
}
```

### Problem 2.2: Template Error Analysis (15 minutes)
Analyze and document common template errors.

**Task:** Study the following problematic code and explain each error in comments:

```cpp
#include <iostream>
using namespace std;

// Error Example 1: Incorrect template syntax
template<typename T>
void problematic_function1() {
    T value;
    value.nonexistent_method();  // What's wrong here?
}

// Error Example 2: Template instantiation issues  
template<typename T>
class ProblematicClass {
public:
    void process(T data) {
        // Assume T has operator+, but what if it doesn't?
        T result = data + data;
        cout << result << endl;
    }
};

int main() {
    // TODO: Comment out problematic lines and explain why they fail
    // problematic_function1<int>();  // Why does this fail?
    
    ProblematicClass<int> works;
    works.process(5);  // This works
    
    // ProblematicClass<string> might_fail;
    // might_fail.process("hello");  // Does this work? Why or why not?
    
    cout << "Template error analysis complete." << endl;
    return 0;
}
```

**Requirements:**
- Add detailed comments explaining each potential error
- Test which lines work and which don't
- Explain the difference between compilation errors and logical errors
- Suggest how to make the templates more robust

---

## Time Distribution Summary
- **Problem Set 1** (50 min): Template fundamentals and container classes
- **Problem Set 2** (40 min): Specialization and debugging skills
- **Total: 1.5 hours**

## Learning Progression
1. **Set 1**: Students master template syntax and create useful generic classes
2. **Set 2**: Students learn specialization and develop debugging skills for template errors

## Success Criteria
Students successfully complete when they can:
- Write function and class templates with proper syntax
- Handle template specialization for different types
- Debug common template compilation errors
- Understand when and how to use templates effectively