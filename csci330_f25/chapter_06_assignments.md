# Chapter 6: Compile-Time Polymorphism - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 6 "Compile-Time Polymorphism"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

**Total Time: 2.25 hours across all problem sets**

## Problem Set 1: Function Template Fundamentals (45 minutes)

### Problem 1.1: Basic Function Templates (15 minutes)
Write a function template called `absolute_value` that returns the absolute value of any numeric type.

**Requirements:**
- Template should work with int, double, float
- Use proper template syntax
- Test with both positive and negative values

**Expected Output:**
```
absolute_value(-5) = 5
absolute_value(-3.14) = 3.14
absolute_value(42) = 42
```

**Starter Template:**
```cpp
#include <iostream>
using namespace std;

// Your template function here
template<typename T>
T absolute_value(T value) {
    // Implement this
}

int main() {
    cout << "absolute_value(-5) = " << absolute_value(-5) << endl;
    cout << "absolute_value(-3.14) = " << absolute_value(-3.14) << endl;
    cout << "absolute_value(42) = " << absolute_value(42) << endl;
    return 0;
}
```

### Problem 1.2: Multiple Template Parameters (20 minutes)
Create a function template `safe_divide` that takes two parameters of potentially different types and returns their quotient. Handle division by zero by returning 0.

**Requirements:**
- Template should accept two different types
- Return type should be appropriate for division
- Handle division by zero case
- Test with mixed types (int/double, double/int, etc.)

**Expected Output:**
```
10 / 2 = 5
10.5 / 2 = 5.25
10 / 0 = 0 (division by zero)
```

**Starter Template:**
```cpp
#include <iostream>
using namespace std;

// Your template function here
template<typename T1, typename T2>
auto safe_divide(T1 numerator, T2 denominator) -> decltype(numerator/denominator) {
    // Implement this
}

int main() {
    cout << "10 / 2 = " << safe_divide(10, 2) << endl;
    cout << "10.5 / 2 = " << safe_divide(10.5, 2) << endl;
    cout << "10 / 0 = " << safe_divide(10, 0) << " (division by zero)" << endl;
    return 0;
}
```

### Problem 1.3: Template Argument Deduction (10 minutes)
Write a `swap` function template that exchanges the values of two variables. Demonstrate both explicit template arguments and automatic deduction.

**Requirements:**
- Function should work with any type
- Modify the original variables (use references)
- Show both `swap<int>(a, b)` and `swap(a, b)` usage

---

## Problem Set 2: Template Classes (60 minutes)

### Problem 2.1: Simple Template Container (35 minutes)
Create a template class `Pair` that holds two values of the same type. This is similar to Python tuples or Java's paired objects.

**Requirements:**
- Template class with two private members
- Constructor to initialize both values
- Getter methods `first()` and `second()`
- Setter methods `set_first()` and `set_second()`
- A `swap()` method that exchanges the two values

**Expected Usage:**
```cpp
Pair<int> numbers(10, 20);
cout << "First: " << numbers.first() << ", Second: " << numbers.second() << endl;
numbers.swap();
cout << "After swap - First: " << numbers.first() << ", Second: " << numbers.second() << endl;

Pair<string> words("hello", "world");
cout << words.first() << " " << words.second() << endl;
```

**Starter Template:**
```cpp
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Pair {
private:
    T first_value;
    T second_value;
public:
    // Implement constructor and methods here
};

int main() {
    Pair<int> numbers(10, 20);
    cout << "First: " << numbers.first() << ", Second: " << numbers.second() << endl;
    
    numbers.swap();
    cout << "After swap - First: " << numbers.first() << ", Second: " << numbers.second() << endl;
    
    Pair<string> words("hello", "world");
    cout << words.first() << " " << words.second() << endl;
    
    return 0;
}
```

### Problem 2.2: Template Container with Dynamic Storage (25 minutes)
Extend the concept to create a `SimpleArray` template that manages dynamic memory for an array of any type.

**Requirements:**
- Constructor takes size parameter
- Proper destructor to avoid memory leaks
- `get(index)` and `set(index, value)` methods
- `size()` method
- Basic bounds checking (print error for invalid index)

**Expected Behavior:**
```cpp
SimpleArray<int> numbers(5);
numbers.set(0, 100);
numbers.set(1, 200);
cout << "numbers[0] = " << numbers.get(0) << endl;
cout << "Size: " << numbers.size() << endl;

SimpleArray<string> words(3);
words.set(0, "apple");
words.set(1, "banana");
cout << "words[0] = " << words.get(0) << endl;
```

**Starter Template:**
```cpp
#include <iostream>
#include <string>
using namespace std;

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
    
    // Implement the rest of the methods
};

int main() {
    SimpleArray<int> numbers(5);
    numbers.set(0, 100);
    numbers.set(1, 200);
    cout << "numbers[0] = " << numbers.get(0) << endl;
    cout << "Size: " << numbers.size() << endl;
    
    SimpleArray<string> words(3);
    words.set(0, "apple");
    words.set(1, "banana");
    cout << "words[0] = " << words.get(0) << endl;
    
    return 0;
}
```

---

## Problem Set 3: Applied Templates and Debugging (40 minutes)

### Problem 3.1: Template Specialization Introduction (20 minutes)
Create a `Printer` template that has different behavior for different types. This introduces the concept of template specialization.

**Requirements:**
- General template prints: "Value: [value]"
- Specialization for `bool` prints: "Boolean: true/false"  
- Specialization for `string` prints: "Text: [value]"
- Test with int, bool, string, and double

**Expected Output:**
```
Value: 42
Boolean: true
Text: hello world
Value: 3.14
```

**Starter Template:**
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

// TODO: Add specializations for bool and string
// Hint: template<> class Printer<bool> { ... };

int main() {
    Printer<int>::print(42);
    Printer<bool>::print(true);
    Printer<string>::print("hello world");
    Printer<double>::print(3.14);
    return 0;
}
```

### Problem 3.2: Debugging Template Errors (20 minutes)
Fix the provided buggy template code. This teaches students to read template error messages.

**Provided Buggy Code:**
```cpp
#include <iostream>
using namespace std;

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
    
    // Bug 1: Missing template syntax in method definition outside class
    T getValue();
};

T Calculator::getValue() {  // This line has errors
    return value;
}

// Bug 2: Trying to use undefined operation
template<typename T>
void processValue(T val) {
    val.doSomething();  // Not all types have this method
}

int main() {
    Calculator<int> calc(10);
    calc.add(5);
    calc.print();
    cout << "Final value: " << calc.getValue() << endl;
    
    // Bug 3: This will cause compilation error
    processValue(42);  // int doesn't have doSomething()
    
    return 0;
}
```

**Student Task:**
1. Identify and fix the template syntax error in `getValue()` definition
2. Comment out or fix the `processValue` function call that causes errors
3. Explain what each error means in comments

**Debugging Hints Provided:**
- Template methods defined outside the class need full template syntax
- Template functions can only use operations that work for all possible types
- Read compiler errors carefully - they often point to the exact problem line

---

## Time Distribution Summary
- **Problem Set 1** (45 min): Basic function templates and syntax
- **Problem Set 2** (60 min): Template classes with practical applications  
- **Problem Set 3** (40 min): Advanced concepts and debugging skills
- **Total: 2.25 hours** (2 hours 15 minutes)

## Learning Progression
1. **Set 1**: Students learn basic template syntax and understand type deduction
2. **Set 2**: Students apply templates to create useful generic classes
3. **Set 3**: Students learn to debug template code and understand specialization

## Instructor Notes
- Emphasize that templates are compile-time features (unlike virtual functions)
- Show how template errors can be verbose but are usually specific
- Connect back to Python's duck typing and Java's generics frequently
- Stress the performance benefits of templates over runtime polymorphism