# Chapter 5: Runtime Polymorphism - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 5 "Runtime Polymorphism"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- Complete these problems after reading Chapter 5 and working through the lesson
- Each problem builds on concepts from inheritance and virtual functions
- **Time expectation**: 2.25 hours total for all three problem sets
- Test all programs thoroughly and pay attention to virtual function behavior

---

## Problem Set 1: Basic Inheritance and Virtual Functions (45 minutes)

### Problem 1.1: Your First Virtual Function
**Objective**: Practice basic inheritance with virtual functions

Create a base class `Animal` with:
- A virtual function `make_sound()` that prints "Some generic animal sound"
- A virtual destructor

Create a derived class `Dog` that:
- Inherits from `Animal`
- Overrides `make_sound()` to print "Woof!"

**Template to get you started**:
```cpp
#include <iostream>

struct Animal {
    virtual ~Animal() = default;
    virtual void make_sound() const {
        std::cout << "Some generic animal sound\n";
    }
};

struct Dog : Animal {
    // Your override here
};

int main() {
    Animal* animal = new Dog();
    animal->make_sound();  // Should print "Woof!"
    delete animal;
    return 0;
}
```

**Python/Java Note**: Unlike Python/Java where all methods are virtual by default, C++ requires the `virtual` keyword for polymorphic behavior.

### Problem 1.2: Understanding Override
**Objective**: Learn the importance of the `override` keyword

Take your solution from 1.1 and:
1. Add the `override` keyword to your `Dog::make_sound()` function
2. Deliberately introduce a typo in the function name (like `make_soud`)
3. Observe the compiler error
4. Fix the typo and verify everything works

**Key Learning**: The `override` keyword helps catch mistakes at compile time!

### Problem 1.3: Base Class Pointers
**Objective**: Practice polymorphic behavior through base class pointers

Create an array of `Animal*` pointers containing different animal types:
```cpp
Animal* zoo[3] = {
    new Dog(),
    new Animal(),
    // Add a Cat class that meows
};
```

Loop through the array and call `make_sound()` on each animal. Don't forget to clean up memory!

---

## Problem Set 2: Abstract Classes and Pure Virtual Functions (60 minutes)

### Problem 2.1: Creating an Abstract Shape Class
**Objective**: Work with pure virtual functions and abstract base classes

Create an abstract `Shape` class with:
- Pure virtual function `double area() const = 0`
- Pure virtual function `double perimeter() const = 0`
- Virtual destructor

**Template**:
```cpp
#include <iostream>
#include <cmath>

struct Shape {
    virtual ~Shape() = default;
    // Add your pure virtual functions here
    
    // This can be implemented in base class
    virtual void display_info() const {
        std::cout << "Area: " << area() << ", Perimeter: " << perimeter() << "\n";
    }
};
```

### Problem 2.2: Implementing Concrete Shapes
**Objective**: Create concrete implementations of abstract interface

Implement two derived classes:

**Rectangle**:
```cpp
struct Rectangle : Shape {
    double width, height;
    
    Rectangle(double w, double h) : width(w), height(h) {}
    
    // Implement area() and perimeter()
};
```

**Circle**:
```cpp
struct Circle : Shape {
    double radius;
    
    Circle(double r) : radius(r) {}
    
    // Implement area() and perimeter()
    // Use M_PI for pi (or 3.14159)
};
```

### Problem 2.3: Polymorphic Shape Collection
**Objective**: Use polymorphism with collections of objects

Create a program that:
1. Creates a vector or array of `Shape*` containing different shape types
2. Loops through and calls `display_info()` on each shape
3. Properly cleans up memory

**Expected output example**:
```
Area: 20, Perimeter: 18
Area: 12.566, Perimeter: 12.566
```

---

## Problem Set 3: Advanced Logging System (60 minutes)

### Problem 3.1: Logger Interface Design
**Objective**: Create a practical logging system using polymorphism

Create an abstract `Logger` base class:
```cpp
#include <iostream>
#include <fstream>
#include <string>

struct Logger {
    virtual ~Logger() = default;
    virtual void log(const std::string& message) const = 0;
    
    // Convenience function implemented in base
    virtual void log_error(const std::string& message) const {
        log("ERROR: " + message);
    }
};
```

### Problem 3.2: Multiple Logger Implementations
**Objective**: Implement different logging strategies

Create three concrete logger classes:

**ConsoleLogger**:
```cpp
struct ConsoleLogger : Logger {
    void log(const std::string& message) const override {
        std::cout << "[Console] " << message << "\n";
    }
};
```

**FileLogger** (Starter code provided):
```cpp
struct FileLogger : Logger {
    std::string filename;
    
    FileLogger(const std::string& file) : filename(file) {}
    
    void log(const std::string& message) const override {
        std::ofstream out(filename, std::ios::app);
        if (out) {
            out << "[File] " << message << "\n";
        }
    }
};
```

**SilentLogger** (for testing/debugging):
```cpp
struct SilentLogger : Logger {
    // Implement this - it should do nothing but satisfy the interface
};
```

### Problem 3.3: Application with Configurable Logging
**Objective**: Use polymorphism to create flexible, configurable systems

Create a simple application class that uses logging:

```cpp
struct Application {
    Logger* logger;
    
    Application(Logger* log) : logger(log) {}
    
    void run() {
        logger->log("Application started");
        do_some_work();
        logger->log("Application finished");
    }
    
private:
    void do_some_work() {
        logger->log("Doing important work...");
        // Simulate potential error
        logger->log_error("Something went wrong!");
        logger->log("Recovered from error");
    }
};
```

**Your task**: Create a main function that:
1. Creates different logger types
2. Runs the application with each logger
3. Demonstrates how the same application code works with different logging strategies
4. Properly manages memory

**Test cases to verify**:
- Console output appears immediately
- File logging creates/appends to a file
- Silent logger produces no output
- Error messages are properly prefixed

---

## Submission Guidelines

**For each problem set**:
1. Include source code with clear comments explaining virtual function usage
2. Show compilation commands used
3. Provide sample output demonstrating polymorphic behavior
4. Explain any challenges you encountered with virtual functions

**File organization**:
```
chapter05_solutions/
├── problem_set_1/
│   ├── problem_1_1.cpp
│   ├── problem_1_2.cpp
│   └── problem_1_3.cpp
├── problem_set_2/
│   ├── problem_2_1.cpp
│   ├── problem_2_2.cpp
│   └── problem_2_3.cpp
├── problem_set_3/
│   ├── problem_3_1.cpp
│   ├── problem_3_2.cpp
│   └── problem_3_3.cpp
├── log_output.txt (from Problem 3.2)
└── README.md (with compilation notes and observations)
```

**Expected time commitment**: 2.25 hours total for all problem sets. If you're taking longer, focus on understanding the core concepts rather than perfect implementation, and ask for help!

## Key Concepts to Demonstrate

By completing these problems, you should be comfortable with:
- Declaring and implementing virtual functions
- Using the `override` keyword for safety
- Creating abstract base classes with pure virtual functions
- Working with polymorphic objects through base class pointers
- Understanding when and why virtual destructors are needed
- Applying polymorphism to solve real-world design problems