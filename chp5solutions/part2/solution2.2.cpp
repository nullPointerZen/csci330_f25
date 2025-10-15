#include <iostream>
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
    Rectangle rect(4.0, 5.0);
    Circle circ(3.0);

    std::cout << "Rectangle:\n";
    rect.display_info();

    std::cout << "\nCircle:\n";
    circ.display_info();

    return 0;
}