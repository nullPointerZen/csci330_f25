# Chapter 5: Assignment Helpers - Runtime Polymorphism

## Purpose
Scaffolding and hints for the polymorphism assignments. Use when stuck or to verify your approach.

---

## Key Concepts Reminder

### Virtual Function Rules
```cpp
class Base {
public:
    virtual void func() { }      // Can be overridden
    virtual void pure() = 0;     // Must be overridden
    virtual ~Base() { }          // Virtual destructor essential!
};

class Derived : public Base {
public:
    void func() override { }     // override keyword (C++11)
    void pure() override { }     // Implements pure virtual
};
```

### Polymorphism Requirements
1. **Inheritance** - Derived class inherits from base
2. **Virtual functions** - Enable dynamic binding
3. **Pointer/Reference** - Access through base class pointer/reference
4. **Matching signatures** - Same parameters and return type

---

## Problem Set 1: Shape Hierarchy Helpers

### Base Shape Class
```cpp
class Shape {
protected:
    char name[50];
    double x, y;  // Position

public:
    Shape(const char* n, double px = 0, double py = 0)
        : x(px), y(py) {
        strcpy(name, n);
    }

    // Pure virtual functions (interface)
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;

    // Concrete virtual function
    virtual void move(double dx, double dy) {
        x += dx;
        y += dy;
    }

    // Non-virtual function
    void print_info() const {
        printf("%s at (%.1f, %.1f)\n", name, x, y);
        printf("  Area: %.2f\n", area());
        printf("  Perimeter: %.2f\n", perimeter());
    }

    // Virtual destructor (essential!)
    virtual ~Shape() {
        printf("Shape destructor: %s\n", name);
    }
};
```

### Derived Classes
```cpp
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r, double x = 0, double y = 0)
        : Shape("Circle", x, y), radius(r) { }

    double area() const override {
        return 3.14159 * radius * radius;
    }

    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }

    void draw() const override {
        printf("Drawing circle with radius %.1f at (%.1f, %.1f)\n",
               radius, x, y);
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h, double x = 0, double y = 0)
        : Shape("Rectangle", x, y), width(w), height(h) { }

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }

    void draw() const override {
        printf("Drawing rectangle %.1fx%.1f at (%.1f, %.1f)\n",
               width, height, x, y);
    }
};

class Triangle : public Shape {
private:
    double base, height, side1, side2;

public:
    Triangle(double b, double h, double s1, double s2)
        : Shape("Triangle"), base(b), height(h),
          side1(s1), side2(s2) { }

    double area() const override {
        return 0.5 * base * height;
    }

    double perimeter() const override {
        return base + side1 + side2;
    }

    void draw() const override {
        printf("Drawing triangle with base %.1f, height %.1f\n",
               base, height);
    }
};
```

### Polymorphic Usage
```cpp
void process_shapes(Shape* shapes[], int count) {
    double total_area = 0;

    for (int i = 0; i < count; i++) {
        shapes[i]->draw();  // Polymorphic call
        shapes[i]->print_info();
        total_area += shapes[i]->area();  // Polymorphic call
    }

    printf("Total area of all shapes: %.2f\n", total_area);
}

int main() {
    // Create shapes polymorphically
    Shape* shapes[3];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 6.0);
    shapes[2] = new Triangle(3.0, 4.0, 3.0, 5.0);

    process_shapes(shapes, 3);

    // Clean up
    for (int i = 0; i < 3; i++) {
        delete shapes[i];  // Virtual destructor ensures proper cleanup
    }
}
```

---

## Problem Set 2: Employee Hierarchy Helpers

### Base Employee Class
```cpp
class Employee {
protected:
    char name[100];
    int id;
    static int next_id;

public:
    Employee(const char* n) : id(next_id++) {
        strcpy(name, n);
    }

    // Pure virtual - forces implementation in derived classes
    virtual double calculate_pay() const = 0;
    virtual const char* get_type() const = 0;

    // Concrete virtual function
    virtual void print() const {
        printf("%s (ID: %d, Type: %s)\n", name, id, get_type());
        printf("  Pay: $%.2f\n", calculate_pay());
    }

    virtual ~Employee() { }
};

int Employee::next_id = 1000;
```

### Derived Employee Types
```cpp
class HourlyEmployee : public Employee {
private:
    double hourly_rate;
    double hours_worked;

public:
    HourlyEmployee(const char* n, double rate, double hours)
        : Employee(n), hourly_rate(rate), hours_worked(hours) { }

    double calculate_pay() const override {
        double regular_hours = (hours_worked <= 40) ? hours_worked : 40;
        double overtime_hours = (hours_worked > 40) ? hours_worked - 40 : 0;
        return regular_hours * hourly_rate +
               overtime_hours * hourly_rate * 1.5;
    }

    const char* get_type() const override {
        return "Hourly";
    }
};

class SalariedEmployee : public Employee {
private:
    double annual_salary;

public:
    SalariedEmployee(const char* n, double salary)
        : Employee(n), annual_salary(salary) { }

    double calculate_pay() const override {
        return annual_salary / 52;  // Weekly pay
    }

    const char* get_type() const override {
        return "Salaried";
    }
};

class CommissionEmployee : public Employee {
private:
    double base_salary;
    double sales;
    double commission_rate;

public:
    CommissionEmployee(const char* n, double base, double s, double rate)
        : Employee(n), base_salary(base), sales(s),
          commission_rate(rate) { }

    double calculate_pay() const override {
        return base_salary / 52 + (sales * commission_rate);
    }

    const char* get_type() const override {
        return "Commission";
    }
};
```

---

## Problem Set 3: Game Character System Helpers

### Base Character Class
```cpp
class Character {
protected:
    char name[50];
    int health;
    int max_health;
    int level;

public:
    Character(const char* n, int hp, int lvl = 1)
        : health(hp), max_health(hp), level(lvl) {
        strcpy(name, n);
    }

    // Pure virtual combat methods
    virtual int attack() const = 0;
    virtual void defend(int damage) = 0;
    virtual const char* get_class() const = 0;

    // Concrete virtual methods
    virtual void level_up() {
        level++;
        max_health += 10;
        health = max_health;
        printf("%s leveled up to %d!\n", name, level);
    }

    virtual void print_status() const {
        printf("%s (%s, Level %d)\n", name, get_class(), level);
        printf("  Health: %d/%d\n", health, max_health);
    }

    bool is_alive() const { return health > 0; }

    virtual ~Character() { }
};
```

### Derived Character Classes
```cpp
class Warrior : public Character {
private:
    int armor;

public:
    Warrior(const char* n) : Character(n, 150), armor(10) { }

    int attack() const override {
        int damage = 20 + (level * 5);
        printf("%s swings sword for %d damage!\n", name, damage);
        return damage;
    }

    void defend(int damage) override {
        int reduced_damage = damage - armor;
        if (reduced_damage < 0) reduced_damage = 0;
        health -= reduced_damage;
        printf("%s blocks %d damage with armor!\n", name, armor);
    }

    const char* get_class() const override { return "Warrior"; }

    void level_up() override {
        Character::level_up();  // Call base class version
        armor += 2;
        printf("  Armor increased to %d\n", armor);
    }
};

class Mage : public Character {
private:
    int mana;
    int max_mana;

public:
    Mage(const char* n) : Character(n, 80), mana(100), max_mana(100) { }

    int attack() const override {
        if (mana >= 10) {
            int damage = 30 + (level * 8);
            printf("%s casts fireball for %d damage!\n", name, damage);
            // Note: can't modify mana here because method is const
            return damage;
        } else {
            printf("%s is out of mana!\n", name);
            return 5;  // Weak staff attack
        }
    }

    void defend(int damage) override {
        health -= damage;  // No armor
        printf("%s takes full %d damage!\n", name, damage);
    }

    const char* get_class() const override { return "Mage"; }
};
```

### Combat System
```cpp
void combat_round(Character* attacker, Character* defender) {
    printf("\n--- Combat Round ---\n");
    int damage = attacker->attack();
    defender->defend(damage);
    defender->print_status();
}

void tournament(Character* characters[], int count) {
    printf("=== Tournament Begins ===\n");

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            printf("\n%s vs %s\n",
                   characters[i]->get_class(),
                   characters[j]->get_class());

            combat_round(characters[i], characters[j]);
            if (characters[j]->is_alive()) {
                combat_round(characters[j], characters[i]);
            }
        }
    }
}
```

---

## Common Patterns

### Factory Pattern
```cpp
class CharacterFactory {
public:
    static Character* create_character(const char* type, const char* name) {
        if (strcmp(type, "warrior") == 0) {
            return new Warrior(name);
        } else if (strcmp(type, "mage") == 0) {
            return new Mage(name);
        } else if (strcmp(type, "rogue") == 0) {
            return new Rogue(name);
        }
        return nullptr;
    }
};
```

### Interface Segregation
```cpp
// Separate interfaces for different capabilities
class Drawable {
public:
    virtual void draw() const = 0;
};

class Moveable {
public:
    virtual void move(double dx, double dy) = 0;
};

class GameObject : public Drawable, public Moveable {
    // Implements both interfaces
};
```

---

## Debugging Tips

### Track Virtual Calls
```cpp
class Base {
public:
    virtual void func() {
        printf("Base::func() called\n");
    }
};

class Derived : public Base {
public:
    void func() override {
        printf("Derived::func() called\n");
        Base::func();  // Call parent version if needed
    }
};
```

### Verify Polymorphism
```cpp
void test_polymorphism() {
    Derived d;
    Base* ptr = &d;
    Base& ref = d;

    ptr->func();  // Should call Derived version
    ref.func();   // Should call Derived version

    Base b = d;   // SLICING! Loses Derived parts
    b.func();     // Calls Base version
}
```

---

## Checklist

- [ ] All classes with virtual functions have virtual destructors
- [ ] Pure virtual functions implemented in all concrete classes
- [ ] Override keyword used for clarity (C++11)
- [ ] No object slicing (use pointers/references)
- [ ] Consistent function signatures in inheritance hierarchy
- [ ] Factory pattern for object creation (optional)
- [ ] Proper cleanup with delete for polymorphic objects