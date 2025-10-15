#include <iostream>

// Base class
struct Animal {
    virtual ~Animal() = default;

    // Virtual function to be overridden
    virtual void make_sound() const {
        std::cout << "Some generic animal sound\n";
    }
};

// Derived class with correct override
struct Dog : Animal {
    void make_sound() const override {
        std::cout << "Woof!\n";
    }
};

int main() {
    std::cout << "=== Demonstrating override keyword ===\n";

    Animal* animal = new Dog();
    animal->make_sound();  // Prints "Woof!"
    delete animal;

    return 0;
}