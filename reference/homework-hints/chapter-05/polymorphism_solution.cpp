#include <iostream>
#include <vector>
#include <memory>

// Basic inheritance and virtual functions
class Animal {
public:
    virtual ~Animal() = default;
    virtual void make_sound() const {
        std::cout << "Some generic animal sound\n";
    }
};

class Dog : public Animal {
public:
    void make_sound() const override {
        std::cout << "Woof!\n";
    }
};

class Cat : public Animal {
public:
    void make_sound() const override {
        std::cout << "Meow!\n";
    }
};

// Abstract base class example
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;

    virtual void display_info() const {
        std::cout << "Area: " << area() << ", Perimeter: " << perimeter() << "\n";
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return 3.14159 * radius * radius;
    }

    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
};

// Logging system example
class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(const std::string& message) const = 0;

    virtual void log_error(const std::string& message) const {
        log("ERROR: " + message);
    }
};

class ConsoleLogger : public Logger {
public:
    void log(const std::string& message) const override {
        std::cout << "[Console] " << message << "\n";
    }
};

class FileLogger : public Logger {
private:
    std::string filename;

public:
    FileLogger(const std::string& file) : filename(file) {}

    void log(const std::string& message) const override {
        // In a real implementation, would write to file
        std::cout << "[File: " << filename << "] " << message << "\n";
    }
};

class SilentLogger : public Logger {
public:
    void log(const std::string& message) const override {
        // Do nothing - silent logger
    }
};

class Application {
private:
    Logger* logger;

public:
    Application(Logger* log) : logger(log) {}

    void run() {
        logger->log("Application started");
        do_some_work();
        logger->log("Application finished");
    }

private:
    void do_some_work() {
        logger->log("Doing important work...");
        logger->log_error("Something went wrong!");
        logger->log("Recovered from error");
    }
};

int main() {
    std::cout << "=== Animal Polymorphism Demo ===\n";

    // Using polymorphic behavior
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Dog>());
    zoo.push_back(std::make_unique<Cat>());
    zoo.push_back(std::make_unique<Animal>());

    for (const auto& animal : zoo) {
        animal->make_sound();
    }

    std::cout << "\n=== Shape Polymorphism Demo ===\n";

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(4.0, 5.0));
    shapes.push_back(std::make_unique<Circle>(3.0));

    for (const auto& shape : shapes) {
        shape->display_info();
    }

    std::cout << "\n=== Logger Polymorphism Demo ===\n";

    // Test different loggers
    ConsoleLogger console_logger;
    FileLogger file_logger("app.log");
    SilentLogger silent_logger;

    Application app1(&console_logger);
    std::cout << "With Console Logger:\n";
    app1.run();

    std::cout << "\nWith File Logger:\n";
    Application app2(&file_logger);
    app2.run();

    std::cout << "\nWith Silent Logger:\n";
    Application app3(&silent_logger);
    app3.run();
    std::cout << "(Silent logger produces no output)\n";

    return 0;
}