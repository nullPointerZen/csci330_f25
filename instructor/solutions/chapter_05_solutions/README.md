# Chapter 5 Solutions: Runtime Polymorphism

## Overview
This directory contains solutions for Chapter 5 problems focusing on runtime polymorphism, inheritance, and virtual functions in C++.

## Compilation Instructions

All solutions can be compiled with:
```bash
g++ -std=c++17 -Wall -Wextra -o solution_name solution_file.cpp
```

### Individual Problem Solutions

**Problem 1.1 - Basic Virtual Functions:**
```bash
g++ -std=c++17 -Wall -Wextra -o problem_1_1 problem_1_1_solution.cpp
./problem_1_1
```

**Problem 2.1 - Abstract Shape Classes:**
```bash
g++ -std=c++17 -Wall -Wextra -o problem_2_1 problem_2_1_solution.cpp
./problem_2_1
```

**Problem 3.1 - Advanced Logging System:**
```bash
g++ -std=c++17 -Wall -Wextra -o problem_3_1 problem_3_1_solution.cpp
./problem_3_1
```

## Key Concepts Demonstrated

### 1. Virtual Functions and Inheritance
- **Virtual keyword**: Enables runtime polymorphism
- **Override keyword**: Provides compile-time safety
- **Virtual destructors**: Essential for safe polymorphic deletion

### 2. Abstract Base Classes
- **Pure virtual functions** (`= 0`): Create interface contracts
- **Abstract classes**: Cannot be instantiated directly
- **Concrete implementations**: Must implement all pure virtual functions

### 3. Polymorphic Usage Patterns
- **Base class pointers**: Enable runtime dispatch
- **Smart pointers**: Modern C++ memory management
- **Collections of polymorphic objects**: Containers with base class pointers

### 4. Real-world Applications
- **Strategy pattern**: Different implementations of the same interface
- **Plugin architecture**: Extensible systems through polymorphism
- **Testability**: Silent/mock implementations for testing

## Learning Progression

### Problem Set 1: Foundations
- Basic inheritance syntax in C++
- Virtual function declaration and overriding
- Polymorphic behavior through base class pointers

### Problem Set 2: Advanced Concepts
- Pure virtual functions and abstract classes
- Multiple implementations of the same interface
- Collections of polymorphic objects

### Problem Set 3: Practical Application
- Real-world system design using polymorphism
- Multiple inheritance strategies
- Composition patterns with polymorphic components

## Common Patterns Used

### 1. Basic Polymorphism
```cpp
struct Base {
    virtual ~Base() = default;  // Virtual destructor
    virtual void func() = 0;    // Pure virtual function
};

struct Derived : Base {
    void func() override { /* implementation */ }
};
```

### 2. Factory Pattern
```cpp
std::unique_ptr<Base> create_object(const std::string& type) {
    if (type == "type1") return std::make_unique<Derived1>();
    if (type == "type2") return std::make_unique<Derived2>();
    return nullptr;
}
```

### 3. Strategy Pattern
```cpp
struct Context {
    std::unique_ptr<Strategy> strategy;
    
    void set_strategy(std::unique_ptr<Strategy> s) {
        strategy = std::move(s);
    }
    
    void execute() { strategy->execute(); }
};
```

## Memory Management Notes

All solutions demonstrate safe memory management:
- **Smart pointers** (`std::unique_ptr`) for automatic cleanup
- **Virtual destructors** in base classes for safe polymorphic deletion
- **RAII principles** for resource management

## Testing and Verification

Each solution includes:
- **Expected output** in comments
- **Error handling** where appropriate
- **Multiple test cases** demonstrating different scenarios
- **Memory safety** verification

## Comparison with Python/Java

### Virtual Functions
- **C++**: Explicit `virtual` keyword required
- **Python/Java**: All methods virtual by default

### Abstract Classes
- **C++**: Pure virtual functions (`= 0`)
- **Python**: `@abstractmethod` decorator
- **Java**: `abstract` keyword

### Memory Management
- **C++**: Manual or smart pointer management
- **Python/Java**: Garbage collection

## Performance Considerations

Virtual functions have minimal overhead:
- **Virtual function table (vtable)**: One per class
- **Virtual function call**: One extra indirection
- **Memory overhead**: One pointer per object (vptr)

For most applications, this overhead is negligible compared to the design benefits of polymorphism.

## Next Steps

After mastering these concepts:
1. Explore multiple inheritance and virtual inheritance
2. Learn about compile-time polymorphism (templates)
3. Study design patterns that use runtime polymorphism
4. Practice with larger systems requiring flexible architectures