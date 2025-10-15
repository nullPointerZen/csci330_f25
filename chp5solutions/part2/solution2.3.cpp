#include <iostream>
#include <vector>
#include <cmath>

// Abstract base class
struct Shape {
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;

    virtual void display_info() const {
        std::cout << "Area: " << area()
                  << ", Perimeter: " << perimeter() << "\n";
    }
};

// Rectangle implementation
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

// Circle implementation
struct Circle : Shape {
    double radius;

    Circle(double r) : radius(r) {}

    double area() const override {
        return M_PI * radius * radius;
    }

    double perimeter() const override {
        return 2 * M_PI * radius;
    }
};

int main() {
    std::vector<Shape*> shapes;

    // Add different shapes
    shapes.push_back(new Rectangle(4.0, 5.0));   // Area: 20, Perimeter: 18
    shapes.push_back(new Circle(2.0));           // Area: ~12.566, Perimeter: ~12.566

    // Display info for each shape
    for (const Shape* shape : shapes) {
        shape->display_info();
    }

    // Clean up memory
    for (Shape* shape : shapes) {
        delete shape;
    }

    return 0;
}