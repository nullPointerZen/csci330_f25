/*
 * Chapter 11, Problem 1.2: Factory Pattern with unique_ptr
 * 
 * Solution: Shape factory that returns unique_ptr for proper ownership transfer
 * 
 * Key concepts demonstrated:
 * - Factory pattern with smart pointers
 * - Returning unique_ptr from factory functions
 * - Polymorphism with smart pointers
 * - nullptr for invalid cases
 */

#include <memory>
#include <iostream>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual double area() const = 0;
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    
    void draw() const override {
        std::cout << "Drawing circle with radius " << radius << std::endl;
    }
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    void draw() const override {
        std::cout << "Drawing rectangle " << width << "x" << height << std::endl;
    }
    
    double area() const override {
        return width * height;
    }
};

class ShapeFactory {
public:
    static std::unique_ptr<Shape> create_shape(const std::string& type, double param1, double param2 = 0) {
        if (type == "circle") {
            return std::make_unique<Circle>(param1);
        } else if (type == "rectangle") {
            return std::make_unique<Rectangle>(param1, param2);
        }
        
        // Return nullptr for unknown types
        return nullptr;
    }
};

int main() {
    auto circle = ShapeFactory::create_shape("circle", 5.0);
    auto rectangle = ShapeFactory::create_shape("rectangle", 3.0, 4.0);
    auto unknown = ShapeFactory::create_shape("triangle", 1.0, 2.0);
    
    if (circle) {
        circle->draw();
        std::cout << "Area: " << circle->area() << std::endl;
    }
    
    if (rectangle) {
        rectangle->draw();
        std::cout << "Area: " << rectangle->area() << std::endl;
    }
    
    if (!unknown) {
        std::cout << "Unknown shape type" << std::endl;
    }
    
    return 0;
}

/*
 * Expected Output:
 * Drawing circle with radius 5
 * Area: 78.5397
 * Drawing rectangle 3x4
 * Area: 12
 * Unknown shape type
 * 
 * Key benefits of using unique_ptr in factory pattern:
 * 1. Clear ownership transfer from factory to caller
 * 2. Automatic cleanup when shapes go out of scope
 * 3. Exception safety - if constructor throws, no memory leak
 * 4. Type-safe null checking with if (ptr) syntax
 * 5. Move semantics allow efficient transfer of ownership
 * 6. Works seamlessly with polymorphism
 */