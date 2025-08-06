# Chapter 5: Runtime Polymorphism - Complete Guide

## 🎯 Learning Objectives (5 minutes)

By the end of this chapter, you will:
1. **Create** polymorphic class hierarchies using virtual functions
2. **Implement** abstract base classes with pure virtual functions
3. **Use** the `override` keyword for safe function overriding
4. **Apply** polymorphism through base class pointers and references
5. **Design** flexible systems using runtime polymorphism
6. **Debug** virtual function dispatch using VS Code

**⏱️ Time Budget: ~4.75 hours total**
- Learning: 2.5 hours
- Problems: 2.25 hours

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](./DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 🎭 Core Concepts: Runtime Polymorphism (2.5 hours)

### 1. Understanding Virtual Functions

**Virtual functions enable runtime polymorphism - the ability to call different implementations through the same interface:**

```cpp
struct Animal {
    virtual ~Animal() = default;
    virtual void make_sound() const {
        std::cout << "Some generic animal sound\n";
    }
};

struct Dog : Animal {
    void make_sound() const override {
        std::cout << "Woof!\n";
    }
};

// Polymorphic usage
Animal* pet = new Dog{};
pet->make_sound();  // Calls Dog::make_sound() - "Woof!"
delete pet;
```

| Aspect | C++ | Python | Java |
|--------|-----|--------|------|
| **Virtual Methods** | Explicit `virtual` keyword | All methods virtual by default | All methods virtual by default |
| **Override Safety** | `override` keyword | No special syntax | `@Override` annotation |
| **Abstract Classes** | Pure virtual: `= 0` | `@abstractmethod` | `abstract` keyword |

**Key Insight**: C++ makes polymorphism explicit - you choose when to pay the virtual function cost.

### 2. Pure Virtual Functions (Abstract Classes)

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

### 3. Inheritance Syntax and Access

```cpp
struct Base {
    virtual void public_method() {}
protected:
    virtual void protected_method() {}
private:
    virtual void private_method() {}
};

struct Derived : Base {  // or "public Base" explicitly
    void public_method() override {}     // Can override
    void protected_method() override {}  // Can override
    // Cannot override private_method
};
```

| Access Level | Inherited As | Usage |
|-------------|--------------|-------|
| **public** | public | Interface methods - most common |
| **protected** | protected | Helper methods for derived classes |
| **private** | not accessible | Implementation details |

### 4. Virtual Destructors: Critical for Polymorphism

**Always use virtual destructors in polymorphic base classes:**

```cpp
struct Base {
    virtual ~Base() = default;  // CRITICAL for polymorphic deletion
    virtual void method() = 0;
};

struct Derived : Base {
    int* data;
    Derived() : data{new int[100]} {}
    ~Derived() { delete[] data; }  // This must be called!
    void method() override {}
};

// Without virtual destructor - memory leak!
Base* obj = new Derived{};
delete obj;  // Only ~Base() called without virtual destructor
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

---

## 🔍 VS Code Debugging Virtual Functions (20 minutes)

### Debugging Virtual Function Dispatch

**Key debugging techniques for understanding polymorphism:**

1. **Step Into Virtual Calls**: Use F11 to see which implementation is called
2. **Call Stack Analysis**: See the virtual function dispatch path
3. **Object Type Inspection**: Use Variables panel to see actual object types
4. **Breakpoints in Overrides**: Set breakpoints in both base and derived implementations

**Debug Configuration for Polymorphism:**
```json
{
    "name": "Debug Polymorphism",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/${fileBasenameNoExtension}",
    "setupCommands": [
        {
            "description": "Show virtual function tables",
            "text": "-gdb-set print vtbl on"
        }
    ]
}
```

### Debugging Strategies

| What to Debug | How to Debug It |
|---------------|-----------------|
| **Which function is called** | Step into (F11) virtual function calls |
| **Object type at runtime** | Variables panel - check actual type |
| **Virtual function table** | Memory view - see vtable pointers |
| **Override correctness** | Compiler errors with `override` keyword |

---

## 🧩 Hands-On Problems (2.25 hours)

### Problem Set 1: Basic Virtual Functions (45 minutes)

#### Problem 1.1: Animal Sounds (15 minutes)
**Master basic virtual function syntax:**

```cpp
#include <iostream>
#include <memory>

struct Animal {
    virtual ~Animal() = default;
    virtual void make_sound() const {
        std::cout << "Some generic animal sound\n";
    }
    virtual void move() const {
        std::cout << "The animal moves\n";
    }
};

struct Dog : Animal {
    void make_sound() const override {
        std::cout << "Woof!\n";
    }
    void move() const override {
        std::cout << "The dog runs\n";
    }
};

struct Cat : Animal {
    void make_sound() const override {
        std::cout << "Meow!\n";
    }
    void move() const override {
        std::cout << "The cat prowls\n";
    }
};

int main() {
    // TODO: Create array of Animal pointers with different animal types
    Animal* zoo[3] = {
        new Animal{},
        new Dog{},
        new Cat{}
    };
    
    // TODO: Loop through and call both methods on each animal
    for (int i = 0; i < 3; i++) {
        std::cout << "Animal " << i << ": ";
        zoo[i]->make_sound();
        zoo[i]->move();
        std::cout << "\n";
    }
    
    // TODO: Clean up memory
    for (int i = 0; i < 3; i++) {
        delete zoo[i];
    }
    
    return 0;
}
```

**Expected Output:**
```
Animal 0: Some generic animal sound
The animal moves

Animal 1: Woof!
The dog runs

Animal 2: Meow!
The cat prowls
```

#### Problem 1.2: Override Safety (15 minutes)
**Learn the importance of the `override` keyword:**

```cpp
#include <iostream>

struct Calculator {
    virtual ~Calculator() = default;
    virtual double calculate(double a, double b) const = 0;
    virtual void display_result(double result) const {
        std::cout << "Result: " << result << "\n";
    }
};

struct Adder : Calculator {
    // TODO: Implement calculate to add a + b
    // TODO: Use override keyword
    double calculate(double a, double b) const override {
        return a + b;
    }
};

struct Multiplier : Calculator {
    // TODO: Implement calculate to multiply a * b
    // TODO: Try introducing a typo in the function name first (like "calcuate")
    // TODO: See how override catches the error
    double calculate(double a, double b) const override {
        return a * b;
    }
};

int main() {
    Calculator* calc1 = new Adder{};
    Calculator* calc2 = new Multiplier{};
    
    double result1 = calc1->calculate(5.0, 3.0);
    double result2 = calc2->calculate(5.0, 3.0);
    
    calc1->display_result(result1);
    calc2->display_result(result2);
    
    delete calc1;
    delete calc2;
    
    return 0;
}
```

#### Problem 1.3: Virtual Destructor Importance (15 minutes)
**See what happens without virtual destructors:**

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

#### Problem 2.1: Shape Interface (20 minutes)
**Create a complete abstract interface:**

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
    // TODO: Create array of different shapes
    Shape* shapes[] = {
        new Rectangle{3.0, 4.0},
        new Circle{2.5},
        new Rectangle{5.0, 5.0}
    };
    
    // TODO: Display info for all shapes
    for (size_t i = 0; i < 3; i++) {
        shapes[i]->display_info();
    }
    
    // TODO: Find shape with largest area
    Shape* largest = shapes[0];
    for (size_t i = 1; i < 3; i++) {
        if (shapes[i]->area() > largest->area()) {
            largest = shapes[i];
        }
    }
    
    std::cout << "Largest shape: ";
    largest->display_info();
    
    // TODO: Clean up
    for (size_t i = 0; i < 3; i++) {
        delete shapes[i];
    }
    
    return 0;
}
```

#### Problem 2.2: Logger System (20 minutes)
**Build a practical polymorphic system:**

```cpp
#include <iostream>
#include <fstream>
#include <string>

struct Logger {
    virtual ~Logger() = default;
    virtual void log(const std::string& message) const = 0;
    
    // Convenience methods with default implementations
    virtual void log_info(const std::string& message) const {
        log("INFO: " + message);
    }
    
    virtual void log_error(const std::string& message) const {
        log("ERROR: " + message);
    }
    
    virtual void log_warning(const std::string& message) const {
        log("WARNING: " + message);
    }
};

struct ConsoleLogger : Logger {
    void log(const std::string& message) const override {
        std::cout << "[Console] " << message << "\n";
    }
};

struct FileLogger : Logger {
    std::string filename;
    
    FileLogger(const std::string& file) : filename{file} {}
    
    void log(const std::string& message) const override {
        std::ofstream out{filename, std::ios::app};
        if (out) {
            out << "[File] " << message << "\n";
        }
    }
};

struct SilentLogger : Logger {
    void log(const std::string& message) const override {
        // Do nothing - silent logging for testing
    }
};

// TODO: Create a ComboLogger that logs to multiple destinations
struct ComboLogger : Logger {
    Logger* primary;
    Logger* secondary;
    
    ComboLogger(Logger* p, Logger* s) : primary{p}, secondary{s} {}
    
    void log(const std::string& message) const override {
        primary->log(message);
        secondary->log(message);
    }
};

int main() {
    ConsoleLogger console;
    FileLogger file{"test.log"};
    SilentLogger silent;
    ComboLogger combo{&console, &file};
    
    // TODO: Test all logger types
    Logger* loggers[] = {&console, &file, &silent, &combo};
    
    for (Logger* logger : loggers) {
        logger->log_info("System started");
        logger->log_warning("Low memory");
        logger->log_error("Connection failed");
        std::cout << "---\n";
    }
    
    return 0;
}
```

#### Problem 2.3: Plugin Architecture (20 minutes)
**Design an extensible plugin system:**

```cpp
#include <iostream>
#include <vector>
#include <memory>

struct Plugin {
    virtual ~Plugin() = default;
    virtual std::string name() const = 0;
    virtual void initialize() = 0;
    virtual void execute() = 0;
    virtual void cleanup() = 0;
};

struct DatabasePlugin : Plugin {
    std::string name() const override { return "Database"; }
    
    void initialize() override {
        std::cout << "Database: Connecting to database...\n";
    }
    
    void execute() override {
        std::cout << "Database: Executing query...\n";
    }
    
    void cleanup() override {
        std::cout << "Database: Closing connection...\n";
    }
};

struct NetworkPlugin : Plugin {
    std::string name() const override { return "Network"; }
    
    void initialize() override {
        std::cout << "Network: Opening socket...\n";
    }
    
    void execute() override {
        std::cout << "Network: Sending data...\n";
    }
    
    void cleanup() override {
        std::cout << "Network: Closing socket...\n";
    }
};

struct PluginManager {
    std::vector<std::unique_ptr<Plugin>> plugins;
    
    void add_plugin(std::unique_ptr<Plugin> plugin) {
        plugins.push_back(std::move(plugin));
    }
    
    void run_all() {
        // Initialize all plugins
        for (auto& plugin : plugins) {
            std::cout << "Initializing " << plugin->name() << "\n";
            plugin->initialize();
        }
        
        // Execute all plugins
        for (auto& plugin : plugins) {
            std::cout << "Executing " << plugin->name() << "\n";
            plugin->execute();
        }
        
        // Cleanup all plugins (reverse order)
        for (auto it = plugins.rbegin(); it != plugins.rend(); ++it) {
            std::cout << "Cleaning up " << (*it)->name() << "\n";
            (*it)->cleanup();
        }
    }
};

int main() {
    PluginManager manager;
    
    // TODO: Add plugins to manager
    manager.add_plugin(std::make_unique<DatabasePlugin>());
    manager.add_plugin(std::make_unique<NetworkPlugin>());
    
    // TODO: Run all plugins
    manager.run_all();
    
    return 0;
}
```

### Problem Set 3: Advanced Polymorphism (40 minutes)

#### Problem 3.1: Template Method Pattern (20 minutes)
**Combine virtual and non-virtual functions:**

```cpp
#include <iostream>

struct DataProcessor {
    virtual ~DataProcessor() = default;
    
    // Template method - defines algorithm structure
    void process() {
        load_data();
        if (validate_data()) {
            transform_data();
            save_data();
            std::cout << "Processing completed successfully\n";
        } else {
            std::cout << "Data validation failed\n";
        }
    }
    
protected:
    // Steps to be implemented by derived classes
    virtual void load_data() = 0;
    virtual bool validate_data() = 0;
    virtual void transform_data() = 0;
    virtual void save_data() = 0;
};

struct CSVProcessor : DataProcessor {
protected:
    void load_data() override {
        std::cout << "Loading CSV data from file\n";
    }
    
    bool validate_data() override {
        std::cout << "Validating CSV format\n";
        return true;  // Assume validation passes
    }
    
    void transform_data() override {
        std::cout << "Converting CSV to internal format\n";
    }
    
    void save_data() override {
        std::cout << "Saving processed CSV data\n";
    }
};

struct JSONProcessor : DataProcessor {
protected:
    void load_data() override {
        std::cout << "Loading JSON data from API\n";
    }
    
    bool validate_data() override {
        std::cout << "Validating JSON schema\n";
        return true;
    }
    
    void transform_data() override {
        std::cout << "Parsing JSON structure\n";
    }
    
    void save_data() override {
        std::cout << "Saving processed JSON data\n";
    }
};

int main() {
    DataProcessor* processors[] = {
        new CSVProcessor{},
        new JSONProcessor{}
    };
    
    for (DataProcessor* processor : processors) {
        processor->process();
        std::cout << "---\n";
    }
    
    delete processors[0];
    delete processors[1];
    
    return 0;
}
```

#### Problem 3.2: Observer Pattern (20 minutes)
**Implement a classic design pattern with polymorphism:**

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
    
    // TODO: Attach observers
    station.attach(&cnn);
    station.attach(&bbc);
    station.attach(&email);
    
    // TODO: Trigger weather updates
    station.weather_changed("Sunny, 75°F");
    std::cout << "\n";
    
    station.weather_changed("Storm warning issued");
    std::cout << "\n";
    
    // TODO: Detach one observer and update again
    station.detach(&bbc);
    station.weather_changed("All clear, 70°F");
    
    return 0;
}
```

---

## 🔧 Quick Reference & Troubleshooting

### Top 5 Virtual Function Errors

#### 1. Missing Virtual Keyword
```cpp
struct Base {
    void method() {}           // ❌ Not virtual - no polymorphism
};

struct Base {
    virtual void method() {}   // ✅ Virtual - enables polymorphism
};
```

#### 2. Forgetting Override
```cpp
struct Derived : Base {
    void method() {}           // ❌ Easy to make typos
    void metod() override {}   // ❌ Compiler catches typo with override
    void method() override {}  // ✅ Safe override
};
```

#### 3. Missing Virtual Destructor
```cpp
struct Base {
    ~Base() {}                 // ❌ Memory leak with polymorphic deletion
    virtual ~Base() = default; // ✅ Safe polymorphic deletion
};
```

#### 4. Object Slicing
```cpp
void process(Shape shape) {    // ❌ Slicing - loses derived info
    shape.area();              // Calls Base::area() only
}

void process(const Shape& shape) { // ✅ Polymorphism works
    shape.area();              // Calls correct derived version
}
```

#### 5. Pure Virtual Implementation Missing
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

### Virtual Function Best Practices

```cpp
// Complete polymorphic base class template
struct Interface {
    virtual ~Interface() = default;              // Virtual destructor
    virtual void pure_method() = 0;              // Pure virtual
    virtual void default_method() {              // Virtual with default
        std::cout << "Default implementation\n";
    }
};

// Safe derived class template
struct Implementation : Interface {
    void pure_method() override {                // Always use override
        std::cout << "Implementation\n";
    }
    void default_method() override {             // Override even defaults
        Interface::default_method();             // Can call base version
        std::cout << "Extended behavior\n";
    }
};
```

---

## ✅ Chapter 5 Success Checklist

### Virtual Function Mastery
- [ ] Can declare virtual functions in base classes
- [ ] Use pure virtual functions to create abstract interfaces
- [ ] Apply the `override` keyword consistently
- [ ] Understand when virtual functions are needed

### Polymorphic Design Skills
- [ ] Create abstract base classes for interfaces
- [ ] Implement multiple derived classes from same interface
- [ ] Use base class pointers/references for polymorphism
- [ ] Design flexible, extensible systems

### Memory Management with Polymorphism
- [ ] Always include virtual destructors in polymorphic base classes
- [ ] Properly delete polymorphic objects
- [ ] Avoid object slicing in function parameters
- [ ] Use smart pointers for automatic cleanup

### Advanced Patterns
- [ ] Implement template method pattern
- [ ] Create observer pattern with virtual functions
- [ ] Build plugin architectures using polymorphism
- [ ] Combine virtual and non-virtual methods effectively

---

## 🚀 What's Next?

**Chapter 6: Compile-time Polymorphism** will cover:
- Templates and generic programming
- Function templates and class templates
- Template specialization
- Comparing runtime vs compile-time polymorphism

**You've mastered runtime polymorphism!** 🎉 Virtual functions are one of C++'s most powerful features for creating flexible, extensible designs. You now understand how to create clean interfaces and implementations that can evolve over time.

**Key Takeaway**: Runtime polymorphism gives you flexibility at the cost of a small performance overhead. Use it when you need different behaviors determined at runtime. The `override` keyword and virtual destructors are essential for safe, maintainable polymorphic code.

---

*Remember: Virtual functions enable the "Open/Closed Principle" - your code is open for extension but closed for modification. This is the foundation of many design patterns and flexible architectures!*