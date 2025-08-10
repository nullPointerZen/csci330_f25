# Chapter 5: Runtime Polymorphism

Welcome to runtime polymorphism! This chapter introduces one of C++'s most powerful features: the ability to treat different objects uniformly through a common interface, with behavior determined at runtime. You'll learn virtual functions, abstract classes, and how to design flexible, extensible systems.

## 📖 How This Chapter Works

**🔄 Learning Sequence (IMPORTANT!):**
1. **📚 FIRST**: Read Textbook Chapter 5 "Runtime Polymorphism" (1-2 hours)
2. **🔍 SECOND**: Work through the lecture notes below for Python/Java context and hands-on practice (4.5 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 5 "Runtime Polymorphism" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Create** polymorphic class hierarchies using virtual functions
2. **Implement** abstract base classes with pure virtual functions
3. **Use** the `override` keyword for safe function overriding
4. **Apply** polymorphism through base class pointers and references
5. **Design** flexible systems using runtime polymorphism
6. **Debug** virtual function dispatch using VS Code

**⏱️ Time Budget:**
- **📚 Textbook Reading: 1-2 hours** (Chapter 5: "Runtime Polymorphism" - REQUIRED FIRST)
- **🛠️ Setup: Included in Chapter 1** (VS Code + debugger setup)
- **💻 Hands-on Work: 4.5 hours** (lecture notes + assignments)

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](../DEVELOPMENT_SETUP.md). All debugging examples use VS Code + Docker.

---

# Lecture Notes

## 🎭 Core Concepts: Runtime Polymorphism

**📖 Bridge to Textbook**: Now that you've read about virtual functions and runtime polymorphism in Chapter 5, let's connect those concepts to Python/Java inheritance patterns.

### 1. The Problem: Why Do We Need Polymorphism?

**Imagine building a graphics application that draws different shapes:**

```cpp
// Without polymorphism - rigid, hard to extend
void draw_shapes() {
    Rectangle rect{5, 3};
    Circle circle{2.5};
    Triangle triangle{4, 6};
    
    // Must know exact types - can't treat them uniformly
    rect.draw();     // Rectangle::draw()
    circle.draw();   // Circle::draw() 
    triangle.draw(); // Triangle::draw()
}
```

**Problem**: Adding new shapes requires modifying existing code everywhere.

### 2. Virtual Functions: The Polymorphic Solution

**Virtual functions let different objects respond to the same interface differently:**

```cpp
struct Shape {  // Common interface
    virtual ~Shape() = default;
    virtual void draw() const = 0;  // Pure virtual - must be implemented
    virtual double area() const = 0;
};

struct Rectangle : Shape {
    double width, height;
    Rectangle(double w, double h) : width{w}, height{h} {}
    
    void draw() const override {
        std::cout << "Drawing rectangle " << width << "x" << height << "\n";
    }
    double area() const override { return width * height; }
};

// Now we can treat all shapes uniformly!
void draw_shapes(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        shape->draw();  // Calls correct draw() method automatically
    }
}
```

**Key Insight**: C++ makes polymorphism explicit through the `virtual` keyword.

| Language Feature | C++ | Python | Java |
|-----------------|-----|--------|------|
| **Making methods virtual** | `virtual` keyword required | All methods virtual by default | All methods virtual by default |
| **Override safety** | `override` keyword prevents errors | No compile-time checking | `@Override` annotation |
| **Interface definition** | Pure virtual: `= 0` | `@abstractmethod` decorator | `abstract` keyword |
| **Performance cost** | Only when using `virtual` | Always present | Always present |

### 3. Pure Virtual Functions (Abstract Classes)

**Pure virtual functions create abstract base classes that define interfaces:**

```cpp
struct Shape {  // Abstract base class
    virtual ~Shape() = default;
    virtual double area() const = 0;      // Pure virtual = interface
    virtual double perimeter() const = 0; // Must be implemented by derived classes
    
    // Can have concrete methods too
    virtual void display_info() const {
        std::cout << "Area: " << area() << ", Perimeter: " << perimeter() << "\n";
    }
};

struct Circle : Shape {
    double radius;
    Circle(double r) : radius{r} {}
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
};
```

**Python/Java Bridge**: This is like ABC (Abstract Base Classes) in Python or `abstract` classes in Java.

### 4. Virtual Destructors: Preventing Memory Leaks

**Why virtual destructors are essential for polymorphic deletion:**

```cpp
struct Shape {
    // ❌ Non-virtual destructor - DANGEROUS!
    ~Shape() { std::cout << "Shape destructor\n"; }
    virtual void draw() const = 0;
};

struct Circle : Shape {
    double* coordinates;  // Dynamically allocated
    Circle() : coordinates{new double[2]} {}
    ~Circle() { 
        delete[] coordinates;  // This cleanup won't happen!
        std::cout << "Circle destructor\n"; 
    }
    void draw() const override {}
};

// The problem:
Shape* shape = new Circle{};  // Creates Circle object
delete shape;  // Only calls ~Shape(), NOT ~Circle() - MEMORY LEAK!
```

**The solution: Always use virtual destructors in base classes:**

```cpp
struct Shape {
    virtual ~Shape() = default;  // ✅ Virtual destructor
    virtual void draw() const = 0;
};

// Now polymorphic deletion works correctly:
Shape* shape = new Circle{};  
delete shape;  // Calls ~Circle() then ~Shape() - no leak!
```

### 5. The `override` Keyword: Your Safety Net

**`override` catches typos and signature mismatches at compile time:**

```cpp
struct Base {
    virtual void calculate(int value) const = 0;
};

struct Derived : Base {
    // Without override - this creates a NEW function (typo!)
    void calcuate(int value) const {}  // Typo in name
    
    // With override - compiler catches the error
    void calcuate(int value) const override {}  // ERROR: no matching virtual function
    
    // Correct
    void calculate(int value) const override {}  // ✅ Safe override
};
```

## 🧩 Hands-On Practice Problems

### Problem Set 1: Basic Virtual Functions (45 minutes)

#### Problem 1.1: Media Player System
Master virtual functions with a practical example:

```cpp
#include <iostream>
#include <vector>
#include <memory>

struct MediaFile {
    std::string filename;
    virtual ~MediaFile() = default;
    
    MediaFile(const std::string& name) : filename{name} {}
    
    virtual void play() const {
        std::cout << "Playing " << filename << "\n";
    }
    virtual void stop() const {
        std::cout << "Stopping " << filename << "\n";
    }
};

struct AudioFile : MediaFile {
    AudioFile(const std::string& name) : MediaFile{name} {}
    
    void play() const override {
        std::cout << "🎵 Playing audio: " << filename << " (stereo sound)\n";
    }
};

struct VideoFile : MediaFile {
    VideoFile(const std::string& name) : MediaFile{name} {}
    
    void play() const override {
        std::cout << "🎬 Playing video: " << filename << " (HD display)\n";
    }
};

int main() {
    std::vector<std::unique_ptr<MediaFile>> playlist;
    playlist.push_back(std::make_unique<AudioFile>("song.mp3"));
    playlist.push_back(std::make_unique<VideoFile>("movie.mp4"));
    playlist.push_back(std::make_unique<AudioFile>("podcast.wav"));
    
    std::cout << "=== Starting Playlist ===\n";
    for (const auto& file : playlist) {
        file->play();  // Calls correct play() method for each type
    }
    
    std::cout << "\n=== Stopping All ===\n";
    for (const auto& file : playlist) {
        file->stop();
    }
    
    return 0;
}
```

**Expected Output:**
```
=== Starting Playlist ===
🎵 Playing audio: song.mp3 (stereo sound)
🎬 Playing video: movie.mp4 (HD display) 
🎵 Playing audio: podcast.wav (stereo sound)

=== Stopping All ===
Stopping song.mp3
Stopping movie.mp4
Stopping podcast.wav
```

#### Problem 1.2: Virtual Destructor Importance
See what happens without virtual destructors:

```cpp
#include <iostream>

// Version 1: Without virtual destructor (problematic)
struct BadBase {
    BadBase() { std::cout << "BadBase constructor\n"; }
    ~BadBase() { std::cout << "BadBase destructor\n"; }  // NOT virtual
    virtual void method() {}
};

struct BadDerived : BadBase {
    int* data;
    BadDerived() : data{new int[10]} { 
        std::cout << "BadDerived constructor\n"; 
    }
    ~BadDerived() { 
        delete[] data; 
        std::cout << "BadDerived destructor\n"; 
    }
};

// Version 2: With virtual destructor (correct)
struct GoodBase {
    GoodBase() { std::cout << "GoodBase constructor\n"; }
    virtual ~GoodBase() { std::cout << "GoodBase destructor\n"; }  // Virtual!
    virtual void method() {}
};

struct GoodDerived : GoodBase {
    int* data;
    GoodDerived() : data{new int[10]} { 
        std::cout << "GoodDerived constructor\n"; 
    }
    ~GoodDerived() { 
        delete[] data; 
        std::cout << "GoodDerived destructor\n"; 
    }
};

int main() {
    std::cout << "=== Bad Example (memory leak) ===\n";
    BadBase* bad = new BadDerived{};
    delete bad;  // Only ~BadBase() called - memory leak!
    
    std::cout << "\n=== Good Example (proper cleanup) ===\n";
    GoodBase* good = new GoodDerived{};
    delete good;  // Both destructors called - no leak!
    
    return 0;
}
```

**Observe**: Which destructors are called in each case?

### Problem Set 2: Abstract Classes and Interfaces (60 minutes)

#### Problem 2.1: Shape Interface
Create a complete abstract interface:

```cpp
#include <iostream>
#include <cmath>

struct Shape {
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;
    
    // Concrete method using pure virtual functions
    virtual void display_info() const {
        std::cout << name() << " - Area: " << area() 
                  << ", Perimeter: " << perimeter() << "\n";
    }
};

struct Rectangle : Shape {
    double width, height;
    
    Rectangle(double w, double h) : width{w}, height{h} {}
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    std::string name() const override {
        return "Rectangle";
    }
};

struct Circle : Shape {
    double radius;
    
    Circle(double r) : radius{r} {}
    
    double area() const override {
        return M_PI * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * M_PI * radius;
    }
    
    std::string name() const override {
        return "Circle";
    }
};

int main() {
    Shape* shapes[] = {
        new Rectangle{3.0, 4.0},
        new Circle{2.5},
        new Rectangle{5.0, 5.0}
    };
    
    for (size_t i = 0; i < 3; i++) {
        shapes[i]->display_info();
    }
    
    // Find shape with largest area
    Shape* largest = shapes[0];
    for (size_t i = 1; i < 3; i++) {
        if (shapes[i]->area() > largest->area()) {
            largest = shapes[i];
        }
    }
    
    std::cout << "Largest shape: ";
    largest->display_info();
    
    // Clean up
    for (size_t i = 0; i < 3; i++) {
        delete shapes[i];
    }
    
    return 0;
}
```

#### Problem 2.2: Notification System
Build a practical polymorphic system:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct Notification {
    virtual ~Notification() = default;
    virtual void send(const std::string& message) const = 0;
    virtual std::string get_type() const = 0;
};

struct EmailNotification : Notification {
    std::string email_address;
    
    EmailNotification(const std::string& email) : email_address{email} {}
    
    void send(const std::string& message) const override {
        std::cout << "📧 Email to " << email_address << ": " << message << "\n";
    }
    
    std::string get_type() const override { return "Email"; }
};

struct SMSNotification : Notification {
    std::string phone_number;
    
    SMSNotification(const std::string& phone) : phone_number{phone} {}
    
    void send(const std::string& message) const override {
        std::cout << "📱 SMS to " << phone_number << ": " << message << "\n";
    }
    
    std::string get_type() const override { return "SMS"; }
};

struct PushNotification : Notification {
    std::string device_id;
    
    PushNotification(const std::string& device) : device_id{device} {}
    
    void send(const std::string& message) const override {
        std::cout << "🔔 Push to device " << device_id << ": " << message << "\n";
    }
    
    std::string get_type() const override { return "Push"; }
};

int main() {
    std::vector<std::unique_ptr<Notification>> channels;
    channels.push_back(std::make_unique<EmailNotification>("user@example.com"));
    channels.push_back(std::make_unique<SMSNotification>("555-0123"));
    channels.push_back(std::make_unique<PushNotification>("device-abc123"));
    
    std::string alert = "Security alert: Unusual login detected";
    
    std::cout << "Broadcasting alert:\n";
    for (const auto& channel : channels) {
        std::cout << "Sending via " << channel->get_type() << ": ";
        channel->send(alert);
    }
    
    return 0;
}
```

### Problem Set 3: Advanced Polymorphism (40 minutes)

#### Problem 3.1: Observer Pattern
Implement a classic design pattern with polymorphism:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Observer {
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

struct Subject {
    virtual ~Subject() = default;
    
    void attach(Observer* observer) {
        observers.push_back(observer);
    }
    
    void detach(Observer* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }
    
    void notify(const std::string& message) {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }
    
private:
    std::vector<Observer*> observers;
};

struct NewsChannel : Observer {
    std::string name;
    
    NewsChannel(const std::string& channel_name) : name{channel_name} {}
    
    void update(const std::string& message) override {
        std::cout << "NewsChannel " << name << " received: " << message << "\n";
    }
};

struct EmailNotifier : Observer {
    std::string email;
    
    EmailNotifier(const std::string& email_addr) : email{email_addr} {}
    
    void update(const std::string& message) override {
        std::cout << "Email to " << email << ": " << message << "\n";
    }
};

struct WeatherStation : Subject {
    void weather_changed(const std::string& weather_info) {
        std::cout << "Weather Station: " << weather_info << "\n";
        notify(weather_info);
    }
};

int main() {
    WeatherStation station;
    
    NewsChannel cnn{"CNN"};
    NewsChannel bbc{"BBC"};
    EmailNotifier email{"user@example.com"};
    
    // Attach observers
    station.attach(&cnn);
    station.attach(&bbc);
    station.attach(&email);
    
    // Trigger weather updates
    station.weather_changed("Sunny, 75°F");
    std::cout << "\n";
    
    station.weather_changed("Storm warning issued");
    std::cout << "\n";
    
    // Detach one observer and update again
    station.detach(&bbc);
    station.weather_changed("All clear, 70°F");
    
    return 0;
}
```

---

# Assignments

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 5 "Runtime Polymorphism"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Problem Set 1: Basic Inheritance and Virtual Functions (45 minutes)

### Problem 1.1: Your First Virtual Function (15 minutes)
**Objective**: Practice basic inheritance with virtual functions

Create a base class `Animal` with:
- A virtual function `make_sound()` that prints "Some generic animal sound"
- A virtual destructor

Create a derived class `Dog` that:
- Inherits from `Animal`
- Overrides `make_sound()` to print "Woof!"

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

### Problem 1.2: Understanding Override (15 minutes)
**Objective**: Learn the importance of the `override` keyword

Take your solution from 1.1 and:
1. Add the `override` keyword to your `Dog::make_sound()` function
2. Deliberately introduce a typo in the function name (like `make_soud`)
3. Observe the compiler error
4. Fix the typo and verify everything works

### Problem 1.3: Base Class Pointers (15 minutes)
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

## Problem Set 2: Abstract Classes and Pure Virtual Functions (60 minutes)

### Problem 2.1: Creating an Abstract Shape Class (20 minutes)
**Objective**: Work with pure virtual functions and abstract base classes

Create an abstract `Shape` class with:
- Pure virtual function `double area() const = 0`
- Pure virtual function `double perimeter() const = 0`
- Virtual destructor

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

### Problem 2.2: Implementing Concrete Shapes (20 minutes)
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

### Problem 2.3: Polymorphic Shape Collection (20 minutes)
**Objective**: Use polymorphism with collections of objects

Create a program that:
1. Creates a vector or array of `Shape*` containing different shape types
2. Loops through and calls `display_info()` on each shape
3. Properly cleans up memory

## Problem Set 3: Advanced Logging System (60 minutes)

### Problem 3.1: Logger Interface Design (20 minutes)
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

### Problem 3.2: Multiple Logger Implementations (20 minutes)
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

**FileLogger**:
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

### Problem 3.3: Application with Configurable Logging (20 minutes)
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
└── README.md (with compilation notes)
```

---

# Quick Reference

## Top 5 Virtual Function Errors

### 1. Missing Virtual Keyword
```cpp
struct Base {
    void method() {}           // ❌ Not virtual - no polymorphism
};

struct Base {
    virtual void method() {}   // ✅ Virtual - enables polymorphism
};
```

### 2. Forgetting Override
```cpp
struct Derived : Base {
    void method() {}           // ❌ Easy to make typos
    void metod() override {}   // ❌ Compiler catches typo with override
    void method() override {}  // ✅ Safe override
};
```

### 3. Missing Virtual Destructor
```cpp
struct Base {
    ~Base() {}                 // ❌ Memory leak with polymorphic deletion
    virtual ~Base() = default; // ✅ Safe polymorphic deletion
};
```

### 4. Object Slicing
```cpp
void process(Shape shape) {    // ❌ Slicing - loses derived info
    shape.area();              // Calls Base::area() only
}

void process(const Shape& shape) { // ✅ Polymorphism works
    shape.area();              // Calls correct derived version
}
```

### 5. Pure Virtual Implementation Missing
```cpp
struct Shape {
    virtual double area() const = 0;  // Pure virtual
};

struct Circle : Shape {
    // ❌ Error: missing area() implementation
};

struct Circle : Shape {
    double area() const override { return 3.14 * r * r; }  // ✅ Complete
};
```

## When to Use Virtual Functions

**Use virtual functions when:**
- You need different behavior for the same interface
- You want to work with objects through base class pointers
- You're designing a plugin or extensible system
- You need runtime polymorphism

**Don't use virtual functions when:**
- All derived classes have identical behavior
- Performance is critical and alternatives exist
- You only have one implementation (no polymorphism needed)
- You can solve the problem with templates (compile-time polymorphism)

## Success Checklist

After Chapter 5, you should be able to:
- [ ] Create abstract base classes with pure virtual functions
- [ ] Implement derived classes that override virtual functions
- [ ] Use the `override` keyword correctly
- [ ] Work with polymorphic objects through base class pointers
- [ ] Include virtual destructors in base classes
- [ ] Understand when to use virtual vs non-virtual functions
- [ ] Apply polymorphism to solve design problems

**Not there yet?** Review the logging example - it demonstrates all key concepts in a practical way.

**Ready to move on?** Excellent! Chapter 6 will cover compile-time polymorphism with templates.

---

## What's Next?

**Chapter 6: Compile-time Polymorphism** will cover:
- Templates and generic programming
- Function templates and class templates
- Template specialization
- Comparing runtime vs compile-time polymorphism

**You've mastered runtime polymorphism!** Virtual functions are one of C++'s most powerful features for creating flexible, extensible designs. The `override` keyword and virtual destructors are essential for safe, maintainable polymorphic code.

---

*Remember: Virtual functions enable the "Open/Closed Principle" - your code is open for extension but closed for modification. This is the foundation of many design patterns and flexible architectures!*