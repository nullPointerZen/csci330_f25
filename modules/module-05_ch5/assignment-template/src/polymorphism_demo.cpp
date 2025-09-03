// HW_05: Runtime Polymorphism
// Time: 2.25 hours (45 minutes per problem set)
// Topics: Inheritance, virtual functions, abstract classes, override

#include <cstdio>
#include <vector>
#include <memory>  // For smart pointers

// ============================================================================
// PROBLEM SET 1: Basic Inheritance and Virtual Functions (45 minutes)
// ============================================================================

// TODO 1: Create Animal base class with virtual functions
class Animal {
public:
    // TODO: Add virtual destructor (why is this important?)
    virtual ~Animal() = default;
    
    // TODO: Add pure virtual function make_sound()
    virtual void make_sound() const = 0;
    
    // TODO: Add virtual function get_species() 
    virtual const char* get_species() const { return "Unknown"; }
};

// TODO 2: Create Dog class that inherits from Animal
class Dog : public Animal {
public:
    // TODO: Override make_sound()
    void make_sound() const override {
        printf("Woof! Woof!\n");
    }
    
    // TODO: Override get_species()
    const char* get_species() const override {
        return "Dog";
    }
};

// TODO 3: Create Cat class
class Cat : public Animal {
public:
    // TODO: Implement required virtual functions
    void make_sound() const override {
        printf("Meow!\n");
    }
    
    const char* get_species() const override {
        return "Cat";
    }
};

// TODO 4: Abstract Shape base class
class Shape {
public:
    virtual ~Shape() = default;
    
    // TODO: Pure virtual functions
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
    virtual const char* get_type() const = 0;
};

// TODO 5: Circle class
class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    // TODO: Implement all pure virtual functions
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void draw() const override {
        printf("Drawing Circle with radius %.2f\n", radius);
    }
    
    const char* get_type() const override {
        return "Circle";
    }
};

// TODO 6: Rectangle class
class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    // TODO: Implement all pure virtual functions
    double area() const override {
        // Your code here
        return width * height;
    }
    
    double perimeter() const override {
        // Your code here
        return 2 * (width + height);
    }
    
    void draw() const override {
        // Your code here
        printf("Drawing Rectangle %.2f x %.2f\n", width, height);
    }
    
    const char* get_type() const override {
        return "Rectangle";
    }
};

void problem_set_1_demo() {
    printf("=== Problem Set 1: Basic Inheritance ===\n\n");
    
    // Animal polymorphism
    printf("Animal Polymorphism:\n");
    std::vector<std::unique_ptr<Animal>> zoo;
    
    // TODO 7: Add different animals to the zoo
    zoo.push_back(std::make_unique<Dog>());
    zoo.push_back(std::make_unique<Cat>());
    
    // TODO 8: Loop through and call virtual functions
    for (const auto& animal : zoo) {
        printf("  %s says: ", animal->get_species());
        animal->make_sound();
    }
    
    // Shape polymorphism
    printf("\nShape Polymorphism:\n");
    std::vector<std::unique_ptr<Shape>> shapes;
    
    // TODO 9: Add different shapes
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    
    // TODO 10: Display shape information polymorphically
    for (const auto& shape : shapes) {
        shape->draw();
        printf("  Type: %s, Area: %.2f, Perimeter: %.2f\n",
               shape->get_type(), shape->area(), shape->perimeter());
    }
    
    printf("\n");
}

// ============================================================================
// PROBLEM SET 2: Advanced Polymorphism (45 minutes)
// ============================================================================

// TODO 11: Game Character System
class GameCharacter {
protected:
    char name[50];
    int health;
    int level;
    
public:
    GameCharacter(const char* n, int h, int l) : health(h), level(l) {
        // Copy name safely
    }
    
    virtual ~GameCharacter() = default;
    
    // TODO: Add virtual functions for attack, defend, special_ability
    virtual int attack() const = 0;
    virtual void defend(int damage) = 0;
    virtual void special_ability() = 0;
    
    virtual void display() const {
        printf("%s (Level %d, Health: %d)\n", name, level, health);
    }
};

// TODO 12: Warrior class
class Warrior : public GameCharacter {
private:
    int armor;
    
public:
    Warrior(const char* n) : GameCharacter(n, 100, 1), armor(50) {}
    
    // TODO: Implement virtual functions
    int attack() const override {
        return 20 + level * 5;  // Base damage + level bonus
    }
    
    void defend(int damage) override {
        int actual_damage = damage - armor / 10;
        if (actual_damage > 0) health -= actual_damage;
    }
    
    void special_ability() override {
        printf("  %s uses Shield Bash!\n", name);
        armor += 20;
    }
};

// TODO 13: Mage class
class Mage : public GameCharacter {
private:
    int mana;
    
public:
    Mage(const char* n) : GameCharacter(n, 70, 1), mana(100) {}
    
    // TODO: Implement virtual functions with different behavior
    int attack() const override {
        return 30 + level * 3;  // Higher damage, less scaling
    }
    
    void defend(int damage) override {
        health -= damage;  // No armor
    }
    
    void special_ability() override {
        if (mana >= 20) {
            printf("  %s casts Fireball!\n", name);
            mana -= 20;
        }
    }
};

void problem_set_2_demo() {
    printf("=== Problem Set 2: Advanced Polymorphism ===\n\n");
    
    printf("Game Character System:\n");
    
    // TODO 14: Create different character types
    std::vector<std::unique_ptr<GameCharacter>> party;
    party.push_back(std::make_unique<Warrior>("Conan"));
    party.push_back(std::make_unique<Mage>("Gandalf"));
    
    // TODO 15: Simulate combat
    for (auto& character : party) {
        character->display();
        printf("  Attack power: %d\n", character->attack());
        character->special_ability();
    }
    
    printf("\n");
}

// ============================================================================
// PROBLEM SET 3: Practical Applications (45 minutes)
// ============================================================================

// TODO 16: Employee Management System
class Employee {
protected:
    char name[100];
    int id;
    
public:
    Employee(const char* n, int i) : id(i) {
        // Copy name
    }
    
    virtual ~Employee() = default;
    
    // TODO: Add pure virtual calculate_salary()
    virtual double calculate_salary() const = 0;
    virtual const char* get_type() const = 0;
    
    void display() const {
        printf("  %s (ID: %d) - %s - Salary: $%.2f\n", 
               name, id, get_type(), calculate_salary());
    }
};

// TODO 17: SalariedEmployee class
class SalariedEmployee : public Employee {
private:
    double annual_salary;
    
public:
    SalariedEmployee(const char* n, int i, double salary) 
        : Employee(n, i), annual_salary(salary) {}
    
    // TODO: Implement virtual functions
    double calculate_salary() const override {
        return annual_salary / 12;  // Monthly salary
    }
    
    const char* get_type() const override {
        return "Salaried";
    }
};

// TODO 18: HourlyEmployee class
class HourlyEmployee : public Employee {
private:
    double hourly_rate;
    int hours_worked;
    
public:
    HourlyEmployee(const char* n, int i, double rate, int hours)
        : Employee(n, i), hourly_rate(rate), hours_worked(hours) {}
    
    // TODO: Different salary calculation
    double calculate_salary() const override {
        return hourly_rate * hours_worked;
    }
    
    const char* get_type() const override {
        return "Hourly";
    }
};

// TODO 19: CommissionEmployee class
class CommissionEmployee : public Employee {
private:
    double base_salary;
    double commission_rate;
    double sales;
    
public:
    CommissionEmployee(const char* n, int i, double base, double rate, double s)
        : Employee(n, i), base_salary(base), commission_rate(rate), sales(s) {}
    
    // TODO: Commission-based calculation
    double calculate_salary() const override {
        return base_salary + (sales * commission_rate);
    }
    
    const char* get_type() const override {
        return "Commission";
    }
};

void problem_set_3_demo() {
    printf("=== Problem Set 3: Practical Applications ===\n\n");
    
    printf("Employee Management System:\n");
    
    // TODO 20: Create different employee types
    std::vector<std::unique_ptr<Employee>> employees;
    employees.push_back(std::make_unique<SalariedEmployee>("Alice", 101, 60000));
    employees.push_back(std::make_unique<HourlyEmployee>("Bob", 102, 25, 160));
    employees.push_back(std::make_unique<CommissionEmployee>("Carol", 103, 2000, 0.1, 50000));
    
    // TODO 21: Calculate total payroll polymorphically
    double total_payroll = 0;
    for (const auto& emp : employees) {
        emp->display();
        total_payroll += emp->calculate_salary();
    }
    
    printf("\nTotal Monthly Payroll: $%.2f\n", total_payroll);
    
    printf("\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("     HW_05: Runtime Polymorphism\n");
    printf("==========================================\n\n");
    
    // Problem Set 1: Basic Inheritance (45 min)
    problem_set_1_demo();
    
    // Problem Set 2: Advanced Polymorphism (45 min)
    problem_set_2_demo();
    
    // Problem Set 3: Practical Applications (45 min)
    problem_set_3_demo();
    
    printf("==========================================\n");
    printf("           Program Complete!\n");
    printf("==========================================\n");
    
    return 0;
}