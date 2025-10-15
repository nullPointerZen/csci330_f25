#include <iostream>

// Base class
struct Animal {
    virtual ~Animal() = default;

    virtual void make_sound() const {
        std::cout << "Moo!\n";
    }
};

// Derived class: Dog
struct Dog : Animal {
    void make_sound() const override {
        std::cout << "Woof!\n";
    }
};

// Derived class: Cat
struct Cat : Animal {
    void make_sound() const override {
        std::cout << "Meow!\n";
    }
};

int main() {
    // Create an array of Animal* with different types
    Animal* zoo[3] = {
        new Dog(),
        new Animal(),
        new Cat()
    };

    // Loop through and call make_sound()
    for (int i = 0; i < 3; ++i) {
        zoo[i]->make_sound();
    }

    // Clean up memory
    for (int i = 0; i < 3; ++i) {
        delete zoo[i];
    }

    return 0;
}