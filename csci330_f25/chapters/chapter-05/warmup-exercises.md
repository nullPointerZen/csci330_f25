# Chapter 5: Warmup Exercises - Runtime Polymorphism (30 minutes)

## Purpose
Need some help getting started? Work through these exercises before tackling the main assignments. They'll build your confidence with inheritance, virtual functions, and polymorphism. (Be sure to read the textbook chapter and lecture notes before starting these!)

---

## Exercise 1: Basic Inheritance (10 minutes)

### Goal
Understand the basics of inheritance and method overriding.

### Your Task
Create `warmup1.cpp`:

```cpp
#include <cstdio>

class Animal {
protected:
    char name[50];

public:
    Animal(const char* n) {
        strcpy(name, n);
        printf("Animal constructor: %s\n", name);
    }

    void eat() {
        printf("%s is eating\n", name);
    }

    void sleep() {
        printf("%s is sleeping\n", name);
    }

    // Regular (non-virtual) method
    void identify() {
        printf("I am an animal named %s\n", name);
    }
};

class Dog : public Animal {
public:
    Dog(const char* n) : Animal(n) {
        printf("Dog constructor: %s\n", name);
    }

    // Override identify (but it's not virtual!)
    void identify() {
        printf("I am a dog named %s\n", name);
    }

    // Add new method
    void bark() {
        printf("%s says: Woof!\n", name);
    }
};

int main() {
    printf("Creating Dog object:\n");
    Dog buddy("Buddy");

    printf("\nCalling inherited methods:\n");
    buddy.eat();    // Inherited from Animal
    buddy.sleep();  // Inherited from Animal

    printf("\nCalling overridden method:\n");
    buddy.identify();  // Dog's version

    printf("\nCalling Dog-specific method:\n");
    buddy.bark();     // Only in Dog

    return 0;
}
```

### Expected Output
```
Creating Dog object:
Animal constructor: Buddy
Dog constructor: Buddy

Calling inherited methods:
Buddy is eating
Buddy is sleeping

Calling overridden method:
I am a dog named Buddy

Calling Dog-specific method:
Buddy says: Woof!
```

### Key Points
- Derived classes inherit base class members
- Constructors are called in order: base then derived
- Non-virtual functions are statically bound

---

## Exercise 2: Virtual Functions (10 minutes)

### Goal
See the difference virtual functions make for polymorphism.

### Your Task
Create `warmup2.cpp`:

```cpp
#include <cstdio>

class Shape {
public:
    // Virtual function
    virtual void draw() {
        printf("Drawing a generic shape\n");
    }

    // Non-virtual function
    void info() {
        printf("This is a shape\n");
    }

    // Virtual destructor (important!)
    virtual ~Shape() {
        printf("Shape destructor\n");
    }
};

class Circle : public Shape {
public:
    void draw() override {  // override keyword (C++11)
        printf("Drawing a circle: O\n");
    }

    void info() {
        printf("This is a circle\n");
    }

    ~Circle() {
        printf("Circle destructor\n");
    }
};

class Square : public Shape {
public:
    void draw() override {
        printf("Drawing a square: []\n");
    }

    void info() {
        printf("This is a square\n");
    }

    ~Square() {
        printf("Square destructor\n");
    }
};

void demonstrate_polymorphism(Shape* shape) {
    printf("Via pointer:\n");
    shape->draw();  // Virtual - calls correct version
    shape->info();  // Non-virtual - calls Shape's version
}

int main() {
    printf("Creating shapes:\n");
    Circle circle;
    Square square;

    printf("\nDirect calls:\n");
    circle.draw();
    circle.info();

    printf("\nPolymorphic calls:\n");
    demonstrate_polymorphism(&circle);
    demonstrate_polymorphism(&square);

    printf("\nCleanup:\n");
    return 0;
}
```

### Expected Output
```
Creating shapes:

Direct calls:
Drawing a circle: O
This is a circle

Polymorphic calls:
Via pointer:
Drawing a circle: O
This is a shape
Via pointer:
Drawing a square: []
This is a shape

Cleanup:
Square destructor
Shape destructor
Circle destructor
Shape destructor
```

### Critical Observations
- Virtual functions use dynamic binding (runtime decision)
- Non-virtual functions use static binding (compile-time decision)
- Through base pointer, only virtual functions are polymorphic

---

## Exercise 3: Abstract Classes (10 minutes)

### Goal
Work with pure virtual functions and abstract classes.

### Your Task
Create `warmup3.cpp`:

```cpp
#include <cstdio>

// Abstract class (has pure virtual function)
class Vehicle {
protected:
    int speed;

public:
    Vehicle() : speed(0) { }

    // Pure virtual function - MUST be overridden
    virtual void accelerate() = 0;

    // Regular virtual function - CAN be overridden
    virtual void brake() {
        speed = 0;
        printf("Vehicle stopped\n");
    }

    // Non-virtual function
    void show_speed() {
        printf("Current speed: %d mph\n", speed);
    }

    virtual ~Vehicle() { }
};

class Car : public Vehicle {
public:
    void accelerate() override {
        speed += 10;
        printf("Car accelerating: vroom!\n");
    }
};

class Bicycle : public Vehicle {
public:
    void accelerate() override {
        speed += 5;
        printf("Bicycle pedaling faster\n");
    }

    void brake() override {
        speed = 0;
        printf("Bicycle hand brakes applied\n");
    }
};

int main() {
    // Vehicle v;  // ERROR! Cannot instantiate abstract class

    printf("Testing Car:\n");
    Car myCar;
    myCar.accelerate();
    myCar.show_speed();
    myCar.brake();

    printf("\nTesting Bicycle:\n");
    Bicycle myBike;
    myBike.accelerate();
    myBike.show_speed();
    myBike.brake();

    printf("\nPolymorphic usage:\n");
    Vehicle* vehicle = &myCar;
    vehicle->accelerate();
    vehicle->show_speed();

    return 0;
}
```

### Expected Output
```
Testing Car:
Car accelerating: vroom!
Current speed: 10 mph
Vehicle stopped

Testing Bicycle:
Bicycle pedaling faster
Current speed: 5 mph
Bicycle hand brakes applied

Polymorphic usage:
Car accelerating: vroom!
Current speed: 20 mph
```

### Key Concepts
- Pure virtual functions make a class abstract
- Cannot instantiate abstract classes
- Derived classes MUST implement pure virtual functions
- Can have mix of pure virtual, virtual, and non-virtual

---

## Success Checklist

Before moving to main assignments:
- [ ] I understand basic inheritance syntax
- [ ] I know the difference between virtual and non-virtual functions
- [ ] I can explain when to use virtual functions
- [ ] I understand pure virtual functions and abstract classes
- [ ] I know why virtual destructors are important
- [ ] I can predict which function version will be called

---

## Quick Reference

### Inheritance Syntax
```cpp
class Derived : public Base {
    // Inherits all public/protected members
};
```

### Virtual Function Rules
```cpp
class Base {
    virtual void func();     // Can be overridden
    void regular();          // Cannot be polymorphic
    virtual void pure() = 0; // Must be overridden
};
```

### Polymorphism Requirements
1. Inheritance relationship
2. Virtual functions
3. Access through pointer or reference
4. Correct function signature in derived class

---

## Common Mistakes

1. **Forgetting virtual destructor**
   ```cpp
   class Base {
       // Need: virtual ~Base() { }
   };
   ```

2. **Slicing problem**
   ```cpp
   Derived d;
   Base b = d;  // Slices off Derived parts!
   Base& r = d; // OK - reference preserves type
   ```

3. **Hiding vs overriding**
   ```cpp
   class Base {
       virtual void func(int x);
   };
   class Derived : public Base {
       void func(double x);  // Hides, doesn't override!
   };
   ```

---

## Next Steps

The main assignments will have you:
- Design class hierarchies
- Implement interfaces with pure virtual functions
- Use polymorphism for flexible designs
- Build factory patterns
- Work with multiple inheritance

You've got the basics - now go build something cool!