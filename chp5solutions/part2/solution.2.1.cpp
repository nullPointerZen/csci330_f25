#include <iostream>
#include <cmath>

struct Shape {
    virtual ~Shape() = default;

    // Pure virtual functions
    virtual double area() const = 0;
    virtual double perimeter() const = 0;

    // Common display function
    virtual void display_info() const {
        std::cout << "Area: " << area()
                  << ", Perimeter: " << perimeter() << "\n";
    }
};