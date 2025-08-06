// Problem 1.1 Solution: Basic Virtual Functions
// Demonstrates basic inheritance and virtual function overriding

#include <iostream>

struct Animal {
    virtual ~Animal() = default;  // Virtual destructor for safe cleanup
    
    virtual void make_sound() const {
        std::cout << "Some generic animal sound\n";
    }
};

struct Dog : Animal {
    void make_sound() const override {  // override keyword for safety
        std::cout << "Woof!\n";
    }
};

int main() {
    // Demonstrate polymorphic behavior
    Animal* animal = new Dog();
    animal->make_sound();  // Calls Dog::make_sound() due to virtual dispatch
    
    // Clean up memory
    delete animal;
    
    // Also demonstrate with stack objects
    Dog dog;
    Animal& animal_ref = dog;
    animal_ref.make_sound();  // Also calls Dog::make_sound()
    
    return 0;
}

/* Expected Output:
Woof!
Woof!
*/

/* Key Learning Points:
1. virtual keyword in base class enables polymorphism
2. override keyword catches signature mismatches at compile time
3. Virtual destructor ensures proper cleanup through base pointer
4. Works with both pointers and references
*/