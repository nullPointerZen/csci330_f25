#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

// =============================================================================
// PART 1: Basic Inheritance and Virtual Functions
// =============================================================================

/*
 * KEY CONCEPT: Virtual Functions
 *
 * In C++ (unlike Python/Java), methods are NOT polymorphic by default.
 * You must use the 'virtual' keyword to enable polymorphic behavior.
 *
 * Without 'virtual': Compile-time binding (static dispatch)
 * With 'virtual': Runtime binding (dynamic dispatch)
 */

class Animal {
public:
    // Virtual destructor - ALWAYS needed when using inheritance
    // This ensures derived class destructors are called properly
    virtual ~Animal() = default;

    // Virtual function - can be overridden by derived classes
    // The 'const' means this function doesn't modify the object
    virtual void make_sound() const {
        std::cout << "Some generic animal sound\n";
    }

    // Another virtual function to demonstrate polymorphism
    virtual std::string get_type() const {
        return "Animal";
    }

    // Non-virtual function - always calls Animal's version
    void describe() const {
        std::cout << "I am a " << get_type() << " and I say: ";
        make_sound();
    }
};

/*
 * Derived class: Dog
 *
 * The 'override' keyword is optional but HIGHLY RECOMMENDED
 * It tells the compiler: "I intend to override a base class function"
 * If you make a typo (like make_soud), the compiler will catch it!
 */
class Dog : public Animal {
public:
    // Override the virtual function
    // Note: 'virtual' keyword is optional here but good for clarity
    void make_sound() const override {
        std::cout << "Woof!\n";
    }

    std::string get_type() const override {
        return "Dog";
    }
};

class Cat : public Animal {
public:
    void make_sound() const override {
        std::cout << "Meow!\n";
    }

    std::string get_type() const override {
        return "Cat";
    }
};

/*
 * IMPORTANT: Why virtual destructors?
 *
 * Animal* animal = new Dog();
 * delete animal;  // Without virtual destructor, only ~Animal() is called!
 *                 // With virtual destructor, ~Dog() then ~Animal() are called.
 */

// =============================================================================
// PART 2: Abstract Classes and Pure Virtual Functions
// =============================================================================

/*
 * Abstract Base Class: Shape
 *
 * A pure virtual function is declared with '= 0'
 * A class with at least one pure virtual function is ABSTRACT
 * You CANNOT create instances of abstract classes
 *
 * Purpose: Define an interface that all derived classes must implement
 */
class Shape {
public:
    virtual ~Shape() = default;

    // Pure virtual functions - derived classes MUST implement these
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string get_name() const = 0;

    // Regular virtual function - can be overridden but has a default implementation
    virtual void display_info() const {
        std::cout << get_name() << ": "
                  << "Area = " << area()
                  << ", Perimeter = " << perimeter() << "\n";
    }
};

/*
 * Concrete class: Circle
 *
 * Must implement ALL pure virtual functions from Shape
 * Otherwise, Circle would also be abstract!
 */
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    // Implement the pure virtual functions
    double area() const override {
        return M_PI * radius * radius;
    }

    double perimeter() const override {
        return 2 * M_PI * radius;
    }

    std::string get_name() const override {
        return "Circle";
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }

    std::string get_name() const override {
        return "Rectangle";
    }
};

class Triangle : public Shape {
private:
    double side_a, side_b, side_c;

public:
    Triangle(double a, double b, double c)
        : side_a(a), side_b(b), side_c(c) {}

    double area() const override {
        // Using Heron's formula
        double s = perimeter() / 2.0;
        return std::sqrt(s * (s - side_a) * (s - side_b) * (s - side_c));
    }

    double perimeter() const override {
        return side_a + side_b + side_c;
    }

    std::string get_name() const override {
        return "Triangle";
    }
};

// =============================================================================
// PART 3: Advanced Logging System (Practical Polymorphism)
// =============================================================================

/*
 * Logger Interface
 *
 * This demonstrates the Strategy Pattern - a design pattern that uses
 * polymorphism to allow selecting different algorithms at runtime.
 *
 * The Application class can work with ANY logger implementation!
 */
class Logger {
public:
    virtual ~Logger() = default;

    // Pure virtual - must be implemented by all loggers
    virtual void log(const std::string& message) const = 0;

    // Convenience methods with default implementations
    virtual void log_error(const std::string& message) const {
        log("ERROR: " + message);
    }

    virtual void log_warning(const std::string& message) const {
        log("WARNING: " + message);
    }

    virtual void log_info(const std::string& message) const {
        log("INFO: " + message);
    }
};

/*
 * ConsoleLogger - logs to standard output
 */
class ConsoleLogger : public Logger {
public:
    void log(const std::string& message) const override {
        std::cout << "[Console] " << message << "\n";
    }
};

/*
 * FileLogger - logs to a file
 *
 * Note: This uses 'mutable' keyword which allows modifying the member
 * even in a const method. This is occasionally useful for logging/caching.
 */
class FileLogger : public Logger {
private:
    std::string filename;

public:
    explicit FileLogger(const std::string& file) : filename(file) {
        // Clear the file when logger is created
        std::ofstream out(filename, std::ios::trunc);
        if (out) {
            out << "=== Log Session Started ===\n";
        }
    }

    void log(const std::string& message) const override {
        // Append mode - adds to end of file
        std::ofstream out(filename, std::ios::app);
        if (out) {
            out << "[File] " << message << "\n";
        } else {
            std::cerr << "Failed to open log file: " << filename << "\n";
        }
    }
};

/*
 * SilentLogger - does nothing (useful for testing/production)
 *
 * This might seem silly, but it's actually very useful:
 * - During testing, you don't want spam in the console
 * - In production, you might want to disable logging for performance
 * - The application code doesn't need to know - just swap the logger!
 */
class SilentLogger : public Logger {
public:
    void log(const std::string& /* message */) const override {
        // Intentionally does nothing
        // Parameter commented out to avoid unused parameter warning
    }
};

/*
 * MultiLogger - logs to multiple destinations
 *
 * This demonstrates composition with polymorphism
 */
class MultiLogger : public Logger {
private:
    std::vector<Logger*> loggers;

public:
    void add_logger(Logger* logger) {
        loggers.push_back(logger);
    }

    void log(const std::string& message) const override {
        for (const auto& logger : loggers) {
            logger->log(message);
        }
    }
};

// =============================================================================
// Application Class - Uses Dependency Injection
// =============================================================================

/*
 * Dependency Injection Pattern
 *
 * The Application class doesn't create its own Logger.
 * Instead, the logger is "injected" from outside.
 *
 * Benefits:
 * - Application is decoupled from specific logger implementations
 * - Easy to test (inject a SilentLogger or mock logger)
 * - Easy to change logging behavior without modifying Application code
 * - Follows the Dependency Inversion Principle (SOLID principles)
 */
class Application {
private:
    Logger* logger;  // Pointer to abstract Logger interface
    std::string app_name;

public:
    Application(const std::string& name, Logger* log)
        : logger(log), app_name(name) {}

    void run() {
        logger->log_info("Application '" + app_name + "' started");

        // Simulate some work
        perform_task("Data Processing");
        perform_task("Report Generation");

        // Simulate an error scenario
        if (!handle_error_scenario()) {
            logger->log_error("Critical error occurred!");
        }

        logger->log_info("Application '" + app_name + "' finished");
    }

private:
    void perform_task(const std::string& task_name) {
        logger->log_info("Starting task: " + task_name);
        // ... actual work happens here ...
        logger->log_info("Completed task: " + task_name);
    }

    bool handle_error_scenario() {
        logger->log_warning("Potential issue detected");
        logger->log("Attempting recovery...");
        // Simulate recovery failure
        return false;
    }
};

// =============================================================================
// Demonstration Functions
// =============================================================================

void demo_basic_polymorphism() {
    std::cout << "\n=== DEMO 1: Basic Polymorphism with Animals ===\n\n";

    // Create a "zoo" using base class pointers
    // This is polymorphism in action!
    std::vector<Animal*> zoo;
    zoo.push_back(new Dog());
    zoo.push_back(new Cat());
    zoo.push_back(new Animal());  // Base class is not abstract, so we can create instances
    zoo.push_back(new Dog());

    std::cout << "Visiting the zoo:\n";
    for (const auto& animal : zoo) {
        animal->describe();  // Polymorphic call - different behavior for each type!
    }

    // MEMORY MANAGEMENT: Clean up
    // Because we have a virtual destructor, the correct destructor is called
    std::cout << "\nClosing the zoo (cleaning up memory):\n";
    for (auto& animal : zoo) {
        delete animal;
    }
    zoo.clear();
}

void demo_abstract_classes() {
    std::cout << "\n=== DEMO 2: Abstract Classes with Shapes ===\n\n";

    // Shape* s = new Shape();  // ERROR! Cannot instantiate abstract class

    // Create a collection of different shapes
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle(5.0));
    shapes.push_back(new Rectangle(4.0, 6.0));
    shapes.push_back(new Triangle(3.0, 4.0, 5.0));
    shapes.push_back(new Circle(10.0));

    std::cout << "Shape information:\n";
    double total_area = 0.0;
    for (const auto& shape : shapes) {
        shape->display_info();  // Polymorphic call
        total_area += shape->area();
    }

    std::cout << "\nTotal area of all shapes: " << total_area << "\n";

    // Clean up
    for (auto& shape : shapes) {
        delete shape;
    }
    shapes.clear();
}

void demo_logger_system() {
    std::cout << "\n=== DEMO 3: Polymorphic Logger System ===\n\n";

    // Create different logger types
    ConsoleLogger console_logger;
    FileLogger file_logger("application.log");
    SilentLogger silent_logger;

    // Create a multi-logger that logs to multiple destinations
    MultiLogger multi_logger;
    multi_logger.add_logger(&console_logger);
    multi_logger.add_logger(&file_logger);

    // Run the same application with different loggers
    std::cout << "--- Running with Console Logger ---\n";
    Application app1("DataProcessor", &console_logger);
    app1.run();

    std::cout << "\n--- Running with Silent Logger ---\n";
    Application app2("BackgroundTask", &silent_logger);
    app2.run();
    std::cout << "(Notice: no output because logger is silent)\n";

    std::cout << "\n--- Running with Multi Logger ---\n";
    Application app3("CriticalProcess", &multi_logger);
    app3.run();

    std::cout << "\nCheck 'application.log' file for file logger output!\n";
}

// =============================================================================
// Main Function
// =============================================================================

int main() {
    std::cout << "╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  Chapter 5: Runtime Polymorphism - Complete Demo          ║\n";
    std::cout << "║  Demonstrates: Virtual Functions, Abstract Classes, and   ║\n";
    std::cout << "║  Practical Design Patterns using Polymorphism             ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n";

    // Run all demonstrations
    demo_basic_polymorphism();
    demo_abstract_classes();
    demo_logger_system();

    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "Demo complete! Review the code comments for explanations.\n";
    std::cout << std::string(60, '=') << "\n";

    return 0;
}

/*
╔═══════════════════════════════════════════════════════════════════════════╗
║                          KEY LEARNING POINTS                              ║
╚═══════════════════════════════════════════════════════════════════════════╝

1. VIRTUAL FUNCTIONS
   - Enable runtime polymorphism (dynamic dispatch)
   - Required for polymorphic behavior through base class pointers/references
   - Use 'override' keyword for safety (catches typos at compile time)

2. VIRTUAL DESTRUCTORS
   - ALWAYS make destructors virtual in base classes
   - Ensures proper cleanup when deleting through base class pointer
   - Without virtual destructor: memory leaks and undefined behavior!

3. ABSTRACT CLASSES
   - Contain at least one pure virtual function (= 0)
   - Cannot be instantiated directly
   - Define interfaces that derived classes must implement
   - Forces consistency across derived classes

4. PURE VIRTUAL FUNCTIONS
   - Declared with '= 0' syntax
   - Must be implemented by non-abstract derived classes
   - Define a contract that all derived classes must follow

5. DESIGN PATTERNS WITH POLYMORPHISM
   - Strategy Pattern: Logger system demonstrates this
   - Dependency Injection: Application class receives logger from outside
   - Interface Segregation: Clients depend on abstractions, not implementations

6. MEMORY MANAGEMENT
   - Virtual destructors ensure proper cleanup
   - Always delete objects created with 'new'
   - Consider using smart pointers (std::unique_ptr, std::shared_ptr) for safety

7. C++ vs PYTHON/JAVA
   - C++: Must use 'virtual' for polymorphic behavior
   - Python/Java: All methods are virtual by default
   - C++: Gives you control but requires explicit 'virtual' keyword

╔═══════════════════════════════════════════════════════════════════════════╗
║                        COMMON MISTAKES TO AVOID                           ║
╚═══════════════════════════════════════════════════════════════════════════╝

1. Forgetting 'virtual' keyword
   Result: No polymorphism, always calls base class version

2. Forgetting virtual destructor
   Result: Derived class destructor not called, memory leaks

3. Forgetting to implement pure virtual functions
   Result: Derived class is still abstract, cannot instantiate

4. Not using 'override' keyword
   Result: Typos in function names go undetected

5. Deleting objects without virtual destructor
   Result: Undefined behavior, only base destructor called

6. Trying to instantiate abstract classes
   Result: Compile error

╔═══════════════════════════════════════════════════════════════════════════╗
║                         ASSIGNMENT MAPPING                                ║
╚═══════════════════════════════════════════════════════════════════════════╝

PROBLEM SET 1: Basic Inheritance and Virtual Functions
- See demo_basic_polymorphism() function
- Animal/Dog/Cat hierarchy demonstrates Problems 1.1-1.3

PROBLEM SET 2: Abstract Classes and Pure Virtual Functions
- See demo_abstract_classes() function
- Shape/Circle/Rectangle/Triangle hierarchy demonstrates Problems 2.1-2.3

PROBLEM SET 3: Advanced Logging System
- See demo_logger_system() function
- Logger hierarchy and Application class demonstrate Problems 3.1-3.3

╔═══════════════════════════════════════════════════════════════════════════╗
║                      HOW TO USE THIS FILE                                 ║
╚═══════════════════════════════════════════════════════════════════════════╝

COMPILATION:
    g++ -std=c++17 -Wall -Wextra polymorphism_hints.cpp -o polymorphism_demo

    or

    clang++ -std=c++17 -Wall -Wextra polymorphism_hints.cpp -o polymorphism_demo

EXECUTION:
    ./polymorphism_demo

EXPECTED OUTPUT:
    - Console output showing polymorphic behavior
    - File 'application.log' created with log messages

WHEN YOU'RE STUCK:
    1. Read the comments for the relevant section
    2. Run this program and observe the output
    3. Modify the code to experiment with different scenarios
    4. Compare your assignment code with this reference

LEARNING STRATEGY:
    1. First, understand the Animal example (simplest)
    2. Then, study the Shape example (abstract classes)
    3. Finally, analyze the Logger example (practical application)
    4. Experiment: Add your own derived classes!

*/
