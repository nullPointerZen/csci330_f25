# Chapter 6: Compile-Time Polymorphism - Lesson Plan

## Estimated Time: 2.5 hours maximum

## Development Environment Setup
**Continue using your chosen workflow from previous chapters:**
- **Option A**: Docker + Command Line
- **Option B**: VS Code + Docker (great for template instantiation debugging)
- **Option C**: VS Code + Local Compiler

**For Chapter 6's template concepts, debugger helps understand compile-time vs runtime behavior!**

---

## Learning Objectives
By the end of this chapter, students will be able to:
1. **Explain the difference** between compile-time and runtime polymorphism, comparing templates to virtual functions
2. **Write basic function templates** that accept different types while maintaining type safety
3. **Create and use simple template classes** for generic data containers (like a templated version of SimpleString)
4. **Debug common template errors** and understand template instantiation messages
5. **Apply template argument deduction** to write cleaner, more maintainable code
6. **Compare templates to Java generics and Python's dynamic typing** to leverage prior knowledge

## Key Concepts with Python/Java Equivalencies

### NEW Concepts (Chapter 6 Focus)
- **Templates vs Runtime Polymorphism**: Compile-time decisions vs runtime decisions
- **Function Templates**: Similar to Java generics but more powerful
- **Template Classes**: Like Java `ArrayList<T>` but with C++ syntax and capabilities
- **Template Argument Deduction**: Automatic type inference (like Python's dynamic typing but checked at compile time)
- **Template Instantiation**: The compiler creates specific versions for each type used

### Building on Previous Knowledge
- **Type Safety** (Chapter 2): Templates maintain static typing while providing flexibility
- **Classes and Objects** (Chapter 4): Template classes are still classes with constructors/destructors
- **Inheritance vs Templates** (Chapter 5): Two different approaches to polymorphism

## Lesson Structure

### Module 1: Why Templates? (35 minutes)
**Motivation and Basic Concepts**

- **Problem Setup** (10 min): Show code duplication issue
  - Multiple functions that do the same thing for different types
  - Compare to Python's single function that works with any type
  - Compare to Java's need for Object/generics

- **First Function Template** (15 min):
  ```cpp
  template<typename T>
  T maximum(T a, T b) {
      return (a > b) ? a : b;
  }
  ```
  - Template syntax explanation
  - How the compiler creates multiple versions
  - Type safety maintained

- **Hands-on Practice** (10 min):
  - Students write a simple `minimum` function template
  - Test with int, double, string

### Module 2: Function Templates in Detail (45 minutes)
**Making Functions Work with Multiple Types**

- **Template Syntax Deep Dive** (15 min):
  - `template<typename T>` vs `template<class T>`
  - Multiple template parameters
  - Template argument deduction vs explicit specification

- **Practical Examples** (20 min):
  - Swap function template
  - Simple container operations (find, count)
  - Comparison with Python's duck typing
  - Why this is better than Java's early Object-based approach

- **Common Errors and Debugging** (10 min):
  - Template instantiation error messages
  - Type requirements (what operations must T support?)
  - When template argument deduction fails

### Module 3: Template Classes (50 minutes)
**Generic Classes and Containers**

- **Motivation** (10 min):
  - Review SimpleString limitations
  - Need for containers that work with different types
  - Java's `ArrayList<String>` vs `ArrayList<Integer>`

- **Building a Template Class** (25 min):
  ```cpp
  template<typename T>
  class SimpleContainer {
  private:
      T* data;
      size_t capacity;
      size_t size;
  public:
      SimpleContainer(size_t initial_capacity);
      void add(const T& item);
      T& get(size_t index);
      // etc.
  };
  ```
  - Constructor syntax for template classes
  - Member function definitions
  - Template class instantiation

- **Using Template Classes** (15 min):
  - Declaration syntax: `SimpleContainer<int> numbers(10);`
  - Type safety benefits
  - Compiler generates separate classes for each type

### Module 4: Practical Applications and Best Practices (40 minutes)
**Real-World Usage and Guidelines**

- **When to Use Templates vs Inheritance** (15 min):
  - Compile-time vs runtime decisions
  - Performance implications
  - Code bloat considerations

- **Template Best Practices** (15 min):
  - Keep template code in header files
  - Meaningful template parameter names
  - Document type requirements
  - Error handling in templates

- **Comparison to Other Languages** (10 min):
  - Java generics: type erasure vs C++ template instantiation
  - Python duck typing: runtime flexibility vs compile-time safety
  - C++ templates: best of both worlds with some complexity

## Assessment Strategy: Simple Pass/Fail Project (45 minutes)

**Project: Generic Calculator Class**

Students implement a `Calculator<T>` template class that:
1. Stores two values of type T
2. Provides methods: `add()`, `subtract()`, `multiply()`
3. Has a `result()` method that returns the current result
4. Works with int, double, and any type that supports basic arithmetic

**Success Criteria:**
- Code compiles without template errors
- Works correctly with at least two different numeric types
- Proper template syntax used
- Basic error handling (like division by zero)

**Provided Starter Code:**
```cpp
template<typename T>
class Calculator {
private:
    T value1, value2;
public:
    Calculator(T v1, T v2);
    // Students implement the rest
};

// Test code provided
int main() {
    Calculator<int> int_calc(10, 5);
    Calculator<double> double_calc(10.5, 2.5);
    // Test calls provided
}
```

## Time Verification Checkpoints
- **35 min**: Module 1 complete, students understand template motivation
- **1:20**: Module 2 complete, students can write basic function templates
- **2:10**: Module 3 complete, students can create and use template classes
- **2:30**: Module 4 complete, ready for assessment
- **Total: 2.5 hours** including 45-minute practical project

## Prerequisites Check
Students should be comfortable with:
- Basic C++ classes and member functions (Chapter 4)
- Constructor/destructor concepts (Chapter 4)  
- Understanding of polymorphism concepts (Chapter 5)
- Function overloading and basic type systems (Chapter 2)

## Success Indicators
- Students can explain when to use templates vs virtual functions
- Students successfully complete the Calculator project
- Students understand compiler error messages related to templates
- Students can compare C++ templates to features in Python/Java