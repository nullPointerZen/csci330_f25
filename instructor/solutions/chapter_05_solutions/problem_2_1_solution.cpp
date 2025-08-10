// Problem 2.1 Solution: Abstract Shape Classes
// Demonstrates pure virtual functions and abstract base classes

#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

// Abstract base class - cannot be instantiated
struct Shape {
    virtual ~Shape() = default;  // Essential for polymorphic deletion
    
    // Pure virtual functions - must be implemented by derived classes
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    
    // Virtual function with default implementation
    virtual void display_info() const {
        std::cout << "Area: " << area() << ", Perimeter: " << perimeter() << "\n";
    }
};

// Concrete implementation #1
struct Rectangle : Shape {
    double width, height;
    
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
};

// Concrete implementation #2
struct Circle : Shape {
    double radius;
    static constexpr double PI = 3.14159265359;
    
    Circle(double r) : radius(r) {}
    
    double area() const override {
        return PI * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * PI * radius;
    }
};

int main() {
    // Cannot instantiate abstract class:
    // Shape shape;  // Error: cannot instantiate abstract class
    
    // Create concrete shapes
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(4.0, 5.0));
    shapes.push_back(std::make_unique<Circle>(3.0));
    shapes.push_back(std::make_unique<Rectangle>(2.0, 8.0));
    
    // Polymorphic usage
    std::cout << "Shape Information:\n";
    for (const auto& shape : shapes) {
        shape->display_info();  // Calls appropriate overridden methods
    }
    
    // Individual shape usage
    Rectangle rect(10.0, 15.0);
    Circle circle(7.0);
    
    std::cout << "\nDirect usage:\n";
    std::cout << "Rectangle area: " << rect.area() << "\n";
    std::cout << "Circle perimeter: " << circle.perimeter() << "\n";
    
    return 0;
}

/* Expected Output:
Shape Information:
Area: 20, Perimeter: 18
Area: 28.2743, Perimeter: 18.8496
Area: 16, Perimeter: 20

Direct usage:
Rectangle area: 150
Circle perimeter: 43.9823
*/

/* Key Learning Points:
1. Pure virtual functions (= 0) create abstract classes
2. Abstract classes cannot be instantiated directly
3. All pure virtual functions must be implemented in derived classes
4. Smart pointers (unique_ptr) provide automatic memory management
5. Polymorphism works seamlessly with containers
*/