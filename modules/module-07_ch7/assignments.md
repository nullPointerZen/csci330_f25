# Chapter 7: Expressions - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 7 "Expressions"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 1.5 hours total for both problem sets
- Test all programs thoroughly before submission

**Total Time Budget**: 1.5 hours across 2 problem sets  
**Target**: Students with Python/Java background learning C++ expressions and operator overloading

---

## Problem Set 1: Expression Fundamentals (45 minutes)
**Focus**: Operator precedence, type conversions, and expression evaluation

### Problem 1.1: Precedence Detective (15 minutes)
**Skill**: Understanding operator precedence and associativity

Predict the output of each expression without running the code. Then verify your answers by compiling and running.

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20, c = 5;
    
    // Question 1: What is the value of result1?
    int result1 = a + b * c;
    cout << "result1: " << result1 << endl;
    
    // Question 2: What is the value of result2?
    int result2 = (a + b) * c;
    cout << "result2: " << result2 << endl;
    
    // Question 3: What is the value of result3?
    int result3 = a < b && b > c;
    cout << "result3: " << result3 << endl;
    
    // Question 4: What is the value of result4?
    bool result4 = a < b || b < c && c > a;
    cout << "result4: " << result4 << endl;
    
    // Question 5: What are the final values of x and y?
    int x = 5;
    int y = ++x + x++;
    cout << "x: " << x << ", y: " << y << endl;
    
    return 0;
}
```

**Learning Goals**: 
- Understand that `*` has higher precedence than `+`
- Learn that `&&` has higher precedence than `||`
- Distinguish between prefix and postfix increment

### Problem 1.2: Type Conversion Traps (15 minutes)
**Skill**: Understanding implicit type conversions in expressions

Fix the bugs in the following code by adding appropriate type conversions:

```cpp
#include <iostream>
using namespace std;

int main() {
    // Bug 1: Integer division problem
    int total_items = 17;
    int groups = 5;
    double average = total_items / groups;  // Should be 3.4, but gives 3.0
    cout << "Average: " << average << endl;
    
    // Bug 2: Signed/unsigned comparison
    int signed_value = -1;
    unsigned int unsigned_value = 1;
    if (signed_value < unsigned_value) {
        cout << "This might not print when you expect!" << endl;
    }
    
    // Bug 3: Loss of precision
    double precise_value = 3.99999;
    int truncated = precise_value;  // We want to round, not truncate
    cout << "Rounded value should be 4, got: " << truncated << endl;
    
    return 0;
}
```

**Hint**: Use `static_cast<double>()` for safe conversions and consider using `std::round()` from `<cmath>`.

### Problem 1.3: Compound Assignment Efficiency (15 minutes)
**Skill**: Using compound assignment operators effectively

Rewrite the following code to use compound assignment operators where appropriate:

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Rewrite these using compound assignment operators
    int score = 100;
    score = score + 50;
    score = score * 2;
    score = score - 25;
    score = score / 3;
    score = score % 10;
    
    string message = "Hello";
    message = message + " ";
    message = message + "World";
    message = message + "!";
    
    bool flags = true;
    flags = flags && false;
    flags = flags || true;
    
    cout << "Final score: " << score << endl;
    cout << "Final message: " << message << endl;
    cout << "Final flags: " << flags << endl;
    
    return 0;
}
```

**Extension**: Research which compound operators are more efficient than their expanded forms and why.

---

## Problem Set 2: Basic Operator Overloading (60 minutes)
**Focus**: Implementing operators for custom classes

### Problem 2.1: Money Class with Arithmetic (25 minutes)
**Skill**: Implementing basic arithmetic operators

Create a `Money` class that represents currency amounts and supports basic arithmetic operations.

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

class Money {
private:
    int cents;  // Store as cents to avoid floating-point issues
    
public:
    // Constructor: Money(dollars, cents) or Money(total_cents)
    Money(int dollars = 0, int cents = 0) : cents(dollars * 100 + cents) {}
    explicit Money(int total_cents) : cents(total_cents) {}
    
    // TODO: Implement these operators
    // Addition
    Money operator+(const Money& other) const {
        // Your implementation here
    }
    
    // Subtraction  
    Money operator-(const Money& other) const {
        // Your implementation here
    }
    
    // Compound addition
    Money& operator+=(const Money& other) {
        // Your implementation here
    }
    
    // Compound subtraction
    Money& operator-=(const Money& other) {
        // Your implementation here
    }
    
    // Equality comparison
    bool operator==(const Money& other) const {
        // Your implementation here
    }
    
    // Less than comparison
    bool operator<(const Money& other) const {
        // Your implementation here
    }
    
    // Display function (we'll make this an operator later)
    void print() const {
        cout << "$" << cents / 100 << "." << setfill('0') << setw(2) << cents % 100;
    }
    
    // Getter for testing
    int get_cents() const { return cents; }
};

int main() {
    Money wallet(25, 50);  // $25.50
    Money coffee(4, 75);   // $4.75
    Money lunch(12, 30);   // $12.30
    
    cout << "Starting amount: ";
    wallet.print();
    cout << endl;
    
    // Test your operators
    Money after_coffee = wallet - coffee;
    cout << "After buying coffee: ";
    after_coffee.print();
    cout << endl;
    
    after_coffee -= lunch;
    cout << "After buying lunch: ";
    after_coffee.print();
    cout << endl;
    
    Money total_spent = coffee + lunch;
    cout << "Total spent: ";
    total_spent.print();
    cout << endl;
    
    // Test comparisons
    if (after_coffee < Money(10, 0)) {
        cout << "Running low on money!" << endl;
    }
    
    return 0;
}
```

**Expected Output**:
```
Starting amount: $25.50
After buying coffee: $20.75
After buying lunch: $8.45
Total spent: $17.05
Running low on money!
```

### Problem 2.2: Vector2D with Mathematical Operations (35 minutes)
**Skill**: Implementing mathematical operators and understanding member vs. non-member functions

Create a 2D vector class that supports vector arithmetic:

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Vector2D {
private:
    double x, y;
    
public:
    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    
    // Getters
    double get_x() const { return x; }
    double get_y() const { return y; }
    
    // TODO: Implement these operators
    
    // Vector addition
    Vector2D operator+(const Vector2D& other) const {
        // Your implementation here
    }
    
    // Vector subtraction
    Vector2D operator-(const Vector2D& other) const {
        // Your implementation here
    }
    
    // Scalar multiplication (vector * scalar)
    Vector2D operator*(double scalar) const {
        // Your implementation here
    }
    
    // Dot product (return scalar)
    double operator*(const Vector2D& other) const {
        // Your implementation here
    }
    
    // Compound addition
    Vector2D& operator+=(const Vector2D& other) {
        // Your implementation here
    }
    
    // Equality (be careful with floating-point comparison!)
    bool operator==(const Vector2D& other) const {
        const double EPSILON = 1e-9;
        // Your implementation here
    }
    
    // Calculate magnitude
    double magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    // Normalize vector (make it unit length)
    Vector2D normalize() const {
        double mag = magnitude();
        if (mag == 0.0) return Vector2D(0, 0);
        return Vector2D(x / mag, y / mag);
    }
};

// TODO: Implement this non-member function
// Scalar multiplication (scalar * vector)
Vector2D operator*(double scalar, const Vector2D& vec) {
    // Your implementation here
}

// TODO: Implement stream output operator
ostream& operator<<(ostream& os, const Vector2D& vec) {
    // Format: (x, y)
    // Your implementation here
}

int main() {
    Vector2D v1(3.0, 4.0);
    Vector2D v2(1.0, 2.0);
    
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;
    
    Vector2D sum = v1 + v2;
    cout << "v1 + v2: " << sum << endl;
    
    Vector2D scaled = v1 * 2.0;
    cout << "v1 * 2: " << scaled << endl;
    
    Vector2D scaled2 = 3.0 * v2;
    cout << "3 * v2: " << scaled2 << endl;
    
    double dot = v1 * v2;  // dot product
    cout << "v1 · v2: " << dot << endl;
    
    cout << "Magnitude of v1: " << v1.magnitude() << endl;
    cout << "v1 normalized: " << v1.normalize() << endl;
    
    return 0;
}
```

**Expected Output**:
```
v1: (3, 4)
v2: (1, 2)
v1 + v2: (4, 6)
v1 * 2: (6, 8)
3 * v2: (3, 6)
v1 · v2: 11
Magnitude of v1: 5
v1 normalized: (0.6, 0.8)
```

---

## Problem Set 3: Advanced Operators and Best Practices (40 minutes)
**Focus**: Complex operator scenarios and design decisions

### Problem 3.1: Smart Counter with All Comparison Operators (20 minutes)
**Skill**: Implementing complete set of comparison operators efficiently

Create a counter class that implements all comparison operators using the canonical pattern:

```cpp
#include <iostream>
using namespace std;

class Counter {
private:
    int value;
    
public:
    Counter(int initial_value = 0) : value(initial_value) {}
    
    // Increment operators
    Counter& operator++() {      // prefix ++counter
        ++value;
        return *this;
    }
    
    Counter operator++(int) {    // postfix counter++
        Counter temp = *this;
        ++value;
        return temp;
    }
    
    // TODO: Implement the canonical comparison operators
    // Start with == and <, then derive the others
    
    bool operator==(const Counter& other) const {
        // Your implementation here
    }
    
    bool operator!=(const Counter& other) const {
        // Implement in terms of ==
    }
    
    bool operator<(const Counter& other) const {
        // Your implementation here
    }
    
    bool operator<=(const Counter& other) const {
        // Implement in terms of < and ==
    }
    
    bool operator>(const Counter& other) const {
        // Implement in terms of <=
    }
    
    bool operator>=(const Counter& other) const {
        // Implement in terms of <
    }
    
    // For output
    int get_value() const { return value; }
};

int main() {
    Counter c1(5);
    Counter c2(10);
    Counter c3(5);
    
    cout << "c1: " << c1.get_value() << endl;
    cout << "c2: " << c2.get_value() << endl;
    cout << "c3: " << c3.get_value() << endl;
    
    // Test all comparison operators
    cout << "\nComparison tests:" << endl;
    cout << "c1 == c3: " << (c1 == c3) << endl;
    cout << "c1 != c2: " << (c1 != c2) << endl;
    cout << "c1 < c2: " << (c1 < c2) << endl;
    cout << "c1 <= c3: " << (c1 <= c3) << endl;
    cout << "c2 > c1: " << (c2 > c1) << endl;
    cout << "c2 >= c1: " << (c2 >= c1) << endl;
    
    // Test increment
    cout << "\nIncrement tests:" << endl;
    cout << "++c1: " << (++c1).get_value() << endl;
    cout << "c1++ then c1: " << (c1++).get_value() << " then " << c1.get_value() << endl;
    
    return 0;
}
```

### Problem 3.2: Design Challenge - When NOT to Overload (20 minutes)
**Skill**: Making good design decisions about operator overloading

Review the following class designs and identify which operator overloadings are appropriate and which are not. Rewrite the problematic ones:

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Design 1: Student class
class Student {
private:
    string name;
    double gpa;
    
public:
    Student(const string& name, double gpa) : name(name), gpa(gpa) {}
    
    // Question: Are these good operator overloads?
    Student operator+(const Student& other) const {
        // "Adding" students by averaging their GPAs?
        return Student(name + " & " + other.name, (gpa + other.gpa) / 2);
    }
    
    bool operator<(const Student& other) const {
        // Comparing by GPA for sorting
        return gpa < other.gpa;
    }
    
    Student& operator<<(const string& course) {
        // "Enrolling" student in course?
        cout << name << " enrolled in " << course << endl;
        return *this;
    }
    
    string get_name() const { return name; }
    double get_gpa() const { return gpa; }
};

// Design 2: BankAccount class
class BankAccount {
private:
    string account_number;
    double balance;
    
public:
    BankAccount(const string& account_number, double initial_balance = 0.0) 
        : account_number(account_number), balance(initial_balance) {}
    
    // Question: Are these good operator overloads?
    BankAccount operator+(double amount) const {
        // Adding money to account
        return BankAccount(account_number, balance + amount);
    }
    
    BankAccount operator-(const BankAccount& other) const {
        // Transferring money between accounts?
        return BankAccount(account_number, balance - other.balance);
    }
    
    bool operator>(const BankAccount& other) const {
        // Comparing account balances
        return balance > other.balance;
    }
    
    double get_balance() const { return balance; }
    string get_account_number() const { return account_number; }
};

// TODO: For each questionable operator overload above, suggest a better alternative
// Write your analysis and improvements here:

/*
Your analysis:

Design 1 (Student class):
- operator+(): [Good/Bad?] Why?
- operator<(): [Good/Bad?] Why?  
- operator<<(): [Good/Bad?] Why?
- Better alternatives:

Design 2 (BankAccount class):
- operator+(): [Good/Bad?] Why?
- operator-(): [Good/Bad?] Why?
- operator>(): [Good/Bad?] Why?
- Better alternatives:
*/

int main() {
    // Test the designs and think about whether they feel natural
    Student alice("Alice", 3.8);
    Student bob("Bob", 3.2);
    
    // Does this make sense?
    Student combined = alice + bob;
    cout << "Combined student: " << combined.get_name() 
         << " with GPA: " << combined.get_gpa() << endl;
    
    // Does this make sense?
    alice << "Mathematics" << "Physics";
    
    BankAccount account1("12345", 1000.0);
    BankAccount account2("67890", 500.0);
    
    // Does this make sense?
    BankAccount after_deposit = account1 + 200.0;
    cout << "After deposit: $" << after_deposit.get_balance() << endl;
    
    // Does this make sense?
    BankAccount after_transfer = account1 - account2;
    cout << "After transfer: $" << after_transfer.get_balance() << endl;
    
    return 0;
}
```

**Discussion Questions**:
1. Which operations feel natural and which feel forced?
2. What would be better names for the problematic operations?
3. When should you use operator overloading vs. named member functions?

---

## Solutions Overview

### Problem Set 1 Solutions:
- **1.1**: Focuses on precedence rules and increment operators
- **1.2**: Emphasizes safe type conversions and common pitfalls
- **1.3**: Shows efficiency benefits of compound assignment

### Problem Set 2 Solutions:
- **2.1**: Money class with careful integer arithmetic
- **2.2**: Vector class showing mathematical operator patterns

### Problem Set 3 Solutions:
- **3.1**: Canonical comparison operator implementation
- **3.2**: Critical thinking about appropriate operator use

## Assessment Rubric

**Excellent (A)**: 
- All operators implemented correctly
- Follows const-correctness and return type conventions
- Shows understanding of when operators are appropriate
- Code is clean and well-commented

**Good (B)**:
- Most operators work correctly
- Minor issues with const-correctness or return types
- Generally makes good design decisions
- Code is mostly clean

**Satisfactory (C)**:
- Basic operators work
- Some confusion about member vs. non-member functions
- Inconsistent application of best practices
- Code works but may be unclear

**Needs Improvement (D/F)**:
- Operators don't compile or work correctly
- Poor understanding of operator overloading principles
- Code is difficult to read or understand