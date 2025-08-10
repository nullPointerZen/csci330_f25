# Chapter 7: Expressions

Welcome to expressions and operator overloading! This chapter covers how C++ evaluates expressions and how you can make your custom types work naturally with familiar operators. You'll learn to control expression evaluation and create intuitive interfaces for your classes.

## 📖 How This Chapter Works

**🔄 Learning Sequence (IMPORTANT!):**
1. **📚 FIRST**: Read Textbook Chapter 7 "Expressions" (2-3 hours)
2. **🔍 SECOND**: Work through the lecture notes below for Python/Java context and hands-on practice (4-5 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 7 "Expressions" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Master** C++ expression evaluation rules and operator precedence
2. **Use** built-in operators effectively with type conversions
3. **Implement** operator overloading for custom classes
4. **Apply** operator overloading best practices and conventions
5. **Distinguish** when to overload operators vs using member functions
6. **Debug** expression evaluation using VS Code step-through

**⏱️ Time Budget:**
- **📚 Textbook Reading: 2-3 hours** (Chapter 7: "Expressions" - REQUIRED FIRST)
- **🛠️ Setup: Included in Chapter 1** (VS Code + debugger setup)
- **💻 Hands-on Work: 4-5 hours** (lecture notes + assignments)

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](../DEVELOPMENT_SETUP.md). All debugging examples use VS Code + Docker.

---

# Lecture Notes

## 📊 Core Concepts: Expressions and Operators

**📖 Bridge to Textbook**: Now that you've read about C++ expressions in Chapter 7, let's connect those concepts to the Python/Java knowledge you already have and see practical examples.

### 1. Understanding Expressions: The Building Blocks of Computation

**From Textbook to Context**: The textbook covered expression fundamentals. Now let's see how expressions work in practice and compare them to languages you know:

```cpp
// Simple expressions
int x = 5;                           // Assignment expression
int y = x + 3;                       // Arithmetic expression  
bool is_positive = (x > 0);          // Comparison expression

// Complex expressions - order matters!
int result = x + y * 2;              // What gets calculated first?
bool condition = x > 0 && y < 20;    // When does evaluation stop?

// Function call expressions
auto area = calculate_area(width, height);
auto total = sum(data) + bonus_points(level);
```

**Why this matters**: C++ expressions follow specific rules for evaluation order, type conversion, and operator precedence. Understanding these rules prevents bugs and makes code predictable.

**Key insight**: Unlike Python's more forgiving dynamic typing or Java's simpler type system, C++ gives you precise control over how expressions are evaluated - but you need to understand the rules.

### 2. Operator Precedence: Avoiding the "Order of Operations" Trap

**📖 Bridge to Textbook**: You read about operator precedence in the textbook. Here's how to apply those rules in practice and avoid common mistakes from Python/Java backgrounds:

**The #1 source of expression bugs**: Not understanding operator precedence. Here are the most important rules to remember:

```cpp
// Most common precedence mistakes:
int result1 = 2 + 3 * 4;           // 14, not 20! (* before +)
int result2 = 12 / 3 + 2;          // 6, not 2! (/ before +)  
bool test1 = x == 5 || y == 10;    // OK: == before ||
bool test2 = x = 5 || y == 10;     // BUG: assignment, not comparison!

// When in doubt, use parentheses for clarity:
int clear1 = 2 + (3 * 4);          // Explicit: 14
int clear2 = (12 / 3) + 2;         // Explicit: 6
bool clear3 = (x == 5) || (y == 10); // Explicit comparison
```

**Essential precedence levels (high to low):**

| Level | Operators | Memory Aid | Example |
|-------|-----------|------------|---------|
| **Highest** | `()` `[]` `.` `->` | "Access first" | `obj.member`, `arr[i]` |
| | `!` `++` `--` `+/-` (unary) | "Unary operators" | `!flag`, `++count` |
| | `*` `/` `%` | "Math first: multiply/divide" | `a * b / c` |
| | `+` `-` | "Then add/subtract" | `a + b - c` |
| | `<` `<=` `>` `>=` | "Compare values" | `x < y` |
| | `==` `!=` | "Test equality" | `x == y` |
| | `&&` | "Logical AND" | `a && b` |
| | `\|\|` | "Logical OR" | `a \|\| b` |
| **Lowest** | `=` `+=` `-=` | "Assignment last" | `x = y + 1` |

**Pro tip**: When expressions get complex, break them into multiple lines with meaningful variable names.

### 3. Type Conversions in Expressions

**📖 Bridge to Textbook**: The textbook explained C++ type conversion rules. Here's how they work in practice with familiar Python/Java comparisons:

**C++ performs automatic conversions, but you can control them:**

```cpp
int i = 42;
double d = 3.14;
float f = 2.5f;

// Implicit conversions
double result1 = i + d;        // int promoted to double
double result2 = i * f;        // int and float promoted to double

// Explicit conversions (casts)
int truncated = static_cast<int>(d);           // 3.14 → 3
int rounded = static_cast<int>(d + 0.5);       // Round before cast
double precise = static_cast<double>(i) / 3;   // Avoid integer division
```

**Conversion Rules (simplified)**:
1. **bool** → **int** → **float** → **double**
2. Smaller types promote to larger types
3. Signed/unsigned conversions can be tricky
4. Use explicit casts when conversion might lose data

### 4. Operator Overloading: Making Your Classes Feel Natural

**📖 Bridge to Textbook**: You've read about operator overloading basics in the textbook. Now let's see how to design and implement them with Python/Java context for intuitive class behavior:

**Goal**: Make custom types work intuitively with familiar operators. Good operator overloading makes code readable and expressive.

```cpp
// Example: A Money class that behaves like a number
class Money {
private:
    int cents;  // Store as cents to avoid floating-point errors
    
public:
    Money(double dollars = 0.0) : cents{static_cast<int>(dollars * 100 + 0.5)} {}
    
    // Addition: money + money = money
    Money operator+(const Money& other) const {
        Money result;
        result.cents = cents + other.cents;
        return result;
    }
    
    // Comparison: natural for money
    bool operator<(const Money& other) const {
        return cents < other.cents;
    }
    
    bool operator==(const Money& other) const {
        return cents == other.cents;
    }
    
    // Compound assignment: efficient for updates
    Money& operator+=(const Money& other) {
        cents += other.cents;
        return *this;
    }
    
    // Output: readable display
    friend std::ostream& operator<<(std::ostream& os, const Money& money) {
        return os << "$" << (money.cents / 100.0);
    }
    
    double to_dollars() const { return cents / 100.0; }
};

// Usage feels natural and intuitive:
Money price{12.50};
Money tax{1.25};
Money total = price + tax;        // Readable: adding money amounts

if (total > Money{10.00}) {       // Natural: comparing money
    std::cout << "Expensive: " << total << std::endl;
}

total += Money{0.50};             // Efficient: in-place addition
```

### 5. Operator Overloading Best Practices: The "Principle of Least Surprise"

**Golden Rule**: Operators should behave the way users expect them to. If your `+` operator doesn't "add" in some intuitive sense, don't overload it.

**Implementation patterns that work:**

```cpp
class MyClass {
public:
    // Arithmetic operators: Return new objects, don't modify originals
    MyClass operator+(const MyClass& other) const {
        MyClass result = *this;
        result += other;  // Implement + in terms of +=
        return result;
    }
    
    // Compound assignment: Modify *this, return reference for chaining
    MyClass& operator+=(const MyClass& other) {
        // Modify this object
        return *this;  // Enable: a += b += c
    }
    
    // Comparison: Usually implement < first, then others in terms of it
    bool operator<(const MyClass& other) const {
        // Compare logic here
        return /* comparison */;
    }
    
    bool operator==(const MyClass& other) const {
        return !(*this < other) && !(other < *this);  // Using <
    }
    
    // Stream output: Friend function (stream is left operand)
    friend std::ostream& operator<<(std::ostream& os, const MyClass& obj) {
        os << "MyClass contents";
        return os;  // Enable: cout << obj1 << obj2
    }
};
```

**Common mistakes to avoid:**
- **Don't overload operators with surprising behavior** (e.g., `+` that doesn't "add")
- **Don't forget the return types** (arithmetic returns objects, assignment returns references)
- **Don't break symmetry** (if `a == b`, then `b == a` should also be true)
- **Don't overload `&&`, `||`, or `,`** - you lose short-circuit evaluation

## 🧩 Hands-On Practice Problems

### Problem Set 1: Expression Fundamentals (45 minutes)

#### Problem 1.1: Expression Evaluation Detective (15 minutes)
**Learn to predict expression results before running code:**

```cpp
#include <iostream>
using namespace std;

int main() {
    // TODO: Before running, predict what each expression evaluates to
    cout << "=== Expression Detective Challenge ===" << endl;
    cout << "Predict the results, then run to check!" << endl << endl;
    
    // Basic precedence challenges
    cout << "Challenge 1: Basic arithmetic" << endl;
    cout << "2 + 3 * 4 = " << (2 + 3 * 4) << endl;
    cout << "Prediction: Is it 14 or 20?" << endl << endl;
    
    cout << "Challenge 2: Mixed operators" << endl;
    cout << "10 - 6 / 2 = " << (10 - 6 / 2) << endl;
    cout << "Prediction: Is it 2 or 7?" << endl << endl;
    
    cout << "Challenge 3: Boolean logic" << endl;
    bool x = true, y = false;
    cout << "true || false && false = " << (x || y && false) << endl;
    cout << "Prediction: Does && or || happen first?" << endl << endl;
    
    cout << "Challenge 4: Assignment vs comparison" << endl;
    int a = 5;
    // TODO: What's wrong with this condition?
    if (a = 10) {  // BUG: Assignment, not comparison!
        cout << "This will always execute (a is now " << a << ")" << endl;
    }
    
    a = 5;  // Reset
    if (a == 10) {  // Fixed: Comparison
        cout << "This won't execute" << endl;
    } else {
        cout << "Correct: a (" << a << ") is not 10" << endl;
    }
    
    cout << endl << "=== Pro Tips ===" << endl;
    cout << "1. When in doubt, use parentheses: (2 + 3) * 4" << endl;
    cout << "2. Watch out for = vs == in conditions" << endl;
    cout << "3. && has higher precedence than ||" << endl;
    
    return 0;
}
```

#### Problem 1.2: Type Conversions (15 minutes)
**Understand implicit and explicit conversions:**

```cpp
#include <iostream>
using namespace std;

int main() {
    int i = 42;
    double d = 3.14;
    float f = 2.5f;
    bool b = true;
    
    // TODO: Predict types and values
    cout << "Type conversion examples:" << endl;
    
    auto result1 = i + d;  // What type is result1?
    cout << "int + double = " << result1 << " (type: double)" << endl;
    
    auto result2 = i / 3;   // Integer division
    cout << "int / int = " << result2 << endl;
    
    auto result3 = static_cast<double>(i) / 3;  // Force double division
    cout << "double / int = " << result3 << endl;
    
    auto result4 = i * f;   // int * float
    cout << "int * float = " << result4 << " (what type?)" << endl;
    
    // TODO: Explore bool conversions
    auto result5 = b + i;   // bool + int
    cout << "bool + int = " << result5 << endl;
    
    // TODO: Explore truncation
    int truncated = d;      // double to int (implicit)
    cout << "double " << d << " as int = " << truncated << endl;
    
    int rounded = static_cast<int>(d + 0.5);  // Manual rounding
    cout << "rounded double = " << rounded << endl;
    
    return 0;
}
```

#### Problem 1.3: Short-Circuit Evaluation (15 minutes)
**Understand logical operator behavior:**

```cpp
#include <iostream>
using namespace std;

bool expensive_check() {
    cout << "Expensive check called!" << endl;
    return true;
}

bool another_check() {
    cout << "Another check called!" << endl;
    return false;
}

int main() {
    cout << "Short-circuit evaluation examples:" << endl;
    
    // TODO: AND short-circuit
    cout << endl << "Testing: false && expensive_check()" << endl;
    bool result1 = false && expensive_check();  // Should expensive_check() be called?
    cout << "Result: " << result1 << endl;
    
    cout << endl << "Testing: true && expensive_check()" << endl;
    bool result2 = true && expensive_check();   // What about now?
    cout << "Result: " << result2 << endl;
    
    // TODO: OR short-circuit
    cout << endl << "Testing: true || another_check()" << endl;
    bool result3 = true || another_check();     // Should another_check() be called?
    cout << "Result: " << result3 << endl;
    
    cout << endl << "Testing: false || another_check()" << endl;
    bool result4 = false || another_check();    // What about now?
    cout << "Result: " << result4 << endl;
    
    return 0;
}
```

### Problem Set 2: Basic Operator Overloading (60 minutes)

#### Problem 2.1: Fraction Class (25 minutes)
**Create a practical class that students understand:**

```cpp
#include <iostream>
#include <numeric>  // for std::gcd
using namespace std;

class Fraction {
private:
    int numerator, denominator;
    
    // Helper function to reduce fractions
    void reduce() {
        int gcd = std::gcd(abs(numerator), abs(denominator));
        numerator /= gcd;
        denominator /= gcd;
        
        // Keep denominator positive
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }
    
public:
    Fraction(int num = 0, int den = 1) : numerator{num}, denominator{den} {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        reduce();
    }
    
    // Addition operator (a/b + c/d = (ad + bc)/(bd))
    Fraction operator+(const Fraction& other) const {
        int new_num = numerator * other.denominator + other.numerator * denominator;
        int new_den = denominator * other.denominator;
        return Fraction{new_num, new_den};
    }
    
    // Subtraction operator
    Fraction operator-(const Fraction& other) const {
        int new_num = numerator * other.denominator - other.numerator * denominator;
        int new_den = denominator * other.denominator;
        return Fraction{new_num, new_den};
    }
    
    // Multiplication operator (a/b * c/d = ac/bd)
    Fraction operator*(const Fraction& other) const {
        return Fraction{numerator * other.numerator, denominator * other.denominator};
    }
    
    // Division operator (a/b / c/d = ad/bc)
    Fraction operator/(const Fraction& other) const {
        return Fraction{numerator * other.denominator, denominator * other.numerator};
    }
    
    // Compound assignment
    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }
    
    // Comparison operators
    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }
    
    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }
    
    // Stream output operator
    friend ostream& operator<<(ostream& os, const Fraction& f) {
        if (f.denominator == 1) {
            return os << f.numerator;
        } else {
            return os << f.numerator << "/" << f.denominator;
        }
    }
    
    double to_decimal() const {
        return static_cast<double>(numerator) / denominator;
    }
};

int main() {
    try {
        Fraction a{3, 4};      // 3/4
        Fraction b{1, 2};      // 1/2
        Fraction c{2, 3};      // 2/3
        
        cout << "Working with fractions:" << endl;
        cout << "a = " << a << " (" << a.to_decimal() << ")" << endl;
        cout << "b = " << b << " (" << b.to_decimal() << ")" << endl;
        cout << "c = " << c << " (" << c.to_decimal() << ")" << endl << endl;
        
        // Test arithmetic
        cout << "Arithmetic operations:" << endl;
        cout << a << " + " << b << " = " << (a + b) << endl;
        cout << a << " - " << b << " = " << (a - b) << endl;
        cout << a << " * " << b << " = " << (a * b) << endl;
        cout << a << " / " << b << " = " << (a / b) << endl << endl;
        
        // Test compound assignment
        Fraction sum = a;
        sum += b;
        cout << "After " << a << " += " << b << ": " << sum << endl << endl;
        
        // Test comparison
        cout << "Comparisons:" << endl;
        cout << a << " == " << b << ": " << (a == b) << endl;
        cout << a << " < " << c << ": " << (a < c) << endl;
        
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    return 0;
}
```

#### Problem 2.2: Money Class with Operators (20 minutes)
**Create a practical class with operator overloading:**

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

class Money {
public:
    int cents;  // Store as cents to avoid floating point issues
    
    Money(double dollars = 0.0) : cents{static_cast<int>(dollars * 100 + 0.5)} {}
    Money(int dollars, int cents_part) : cents{dollars * 100 + cents_part} {}
    
    // Addition
    Money operator+(const Money& other) const {
        Money result;
        result.cents = cents + other.cents;
        return result;
    }
    
    // Subtraction
    Money operator-(const Money& other) const {
        Money result;
        result.cents = cents - other.cents;
        return result;
    }
    
    // Comparison operators
    bool operator==(const Money& other) const {
        return cents == other.cents;
    }
    
    bool operator<(const Money& other) const {
        return cents < other.cents;
    }
    
    bool operator>(const Money& other) const {
        return cents > other.cents;
    }
    
    // Compound assignment
    Money& operator+=(const Money& other) {
        cents += other.cents;
        return *this;
    }
    
    // Stream output
    friend ostream& operator<<(ostream& os, const Money& money) {
        double dollars = money.cents / 100.0;
        return os << "$" << fixed << setprecision(2) << dollars;
    }
    
    double to_dollars() const {
        return cents / 100.0;
    }
};

int main() {
    Money price1{12.50};
    Money price2{7, 25};    // $7.25
    Money price3{5.99};
    
    cout << "Price 1: " << price1 << endl;
    cout << "Price 2: " << price2 << endl;
    cout << "Price 3: " << price3 << endl;
    
    Money total = price1 + price2 + price3;
    cout << "Total: " << total << endl;
    
    Money change = Money{30.00} - total;
    cout << "Change from $30: " << change << endl;
    
    if (price1 > price2) {
        cout << "Price 1 is more expensive than Price 2" << endl;
    }
    
    return 0;
}
```

#### Problem 2.3: String Wrapper with Operations (15 minutes)
**Practice with string-like operator overloading:**

```cpp
#include <iostream>
#include <string>
using namespace std;

class MyString {
public:
    string data;
    
    MyString(const string& s = "") : data{s} {}
    
    // Concatenation operators
    MyString operator+(const MyString& other) const {
        return MyString{data + other.data};
    }
    
    MyString operator+(const string& str) const {
        return MyString{data + str};
    }
    
    // Compound assignment
    MyString& operator+=(const MyString& other) {
        data += other.data;
        return *this;
    }
    
    // Subscript operator
    char& operator[](size_t index) {
        return data[index];
    }
    
    const char& operator[](size_t index) const {
        return data[index];
    }
    
    // Comparison
    bool operator==(const MyString& other) const {
        return data == other.data;
    }
    
    // Stream operators
    friend ostream& operator<<(ostream& os, const MyString& str) {
        return os << str.data;
    }
    
    friend istream& operator>>(istream& is, MyString& str) {
        return is >> str.data;
    }
    
    size_t length() const {
        return data.length();
    }
};

int main() {
    MyString first{"Hello"};
    MyString second{" World"};
    MyString greeting = first + second;
    
    cout << "First: " << first << endl;
    cout << "Second: " << second << endl;
    cout << "Greeting: " << greeting << endl;
    
    greeting += "!";
    cout << "With exclamation: " << greeting << endl;
    
    cout << "First character: " << greeting[0] << endl;
    cout << "Length: " << greeting.length() << endl;
    
    return 0;
}
```

---

# Assignments

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 7 "Expressions"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

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
    cout << endl << "Comparison tests:" << endl;
    cout << "c1 == c3: " << (c1 == c3) << endl;
    cout << "c1 != c2: " << (c1 != c2) << endl;
    cout << "c1 < c2: " << (c1 < c2) << endl;
    cout << "c1 <= c3: " << (c1 <= c3) << endl;
    cout << "c2 > c1: " << (c2 > c1) << endl;
    cout << "c2 >= c1: " << (c2 >= c1) << endl;
    
    // Test increment
    cout << endl << "Increment tests:" << endl;
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

## Submission Guidelines

**File organization**:
```
chapter07_solutions/
├── problem_1_1.cpp
├── problem_1_2.cpp
├── problem_1_3.cpp
├── problem_2_1.cpp
├── problem_2_2.cpp
├── problem_3_1.cpp
├── problem_3_2.cpp
└── README.md (with compilation notes)
```

---

# Quick Reference

## Top 5 Expression Errors

### 1. Operator Precedence Confusion
```cpp
// Wrong assumption
int result = 5 + 3 * 2;  // Not 16! It's 11 because * comes first

// Safe approach - use parentheses when in doubt
int result = 5 + (3 * 2);  // Clear: 11
int result = (5 + 3) * 2;  // Clear: 16
```

### 2. Integer Division Trap
```cpp
// Wrong - gives 0, not 0.666...
double result = 2 / 3;

// Right - force floating-point division
double result = 2.0 / 3.0;
// OR
double result = static_cast<double>(2) / 3;
```

### 3. Assignment vs Comparison
```cpp
if (x = 5) { /* ... */ }       // Assignment! Always true
if (x == 5) { /* ... */ }      // Comparison - what you meant
```

### 4. Overloaded Operator Return Types
```cpp
// Wrong - should return new object
MyClass& operator+(const MyClass& rhs) const;

// Right - arithmetic operators return new objects
MyClass operator+(const MyClass& rhs) const;
```

### 5. Const-Correctness in Operators
```cpp
// Wrong - can't call non-const method on const object
bool operator==(const MyClass& other) {  // Missing const!

// Right
bool operator==(const MyClass& other) const;
```

## Operator Overloading Quick Reference

```cpp
class MyClass {
public:
    // Arithmetic operators (return new objects)
    MyClass operator+(const MyClass& rhs) const;
    MyClass operator-(const MyClass& rhs) const;
    MyClass operator*(const MyClass& rhs) const;
    
    // Compound assignment (return reference to *this)
    MyClass& operator+=(const MyClass& rhs);
    MyClass& operator-=(const MyClass& rhs);
    
    // Comparison operators (return bool)
    bool operator==(const MyClass& rhs) const;
    bool operator!=(const MyClass& rhs) const;
    bool operator<(const MyClass& rhs) const;
    
    // Subscript operator (return reference)
    Type& operator[](size_t index);
    const Type& operator[](size_t index) const;
    
    // Stream operators (friend functions)
    friend std::ostream& operator<<(std::ostream& os, const MyClass& obj);
    friend std::istream& operator>>(std::istream& is, MyClass& obj);
};
```

## Precedence Cheat Sheet

| Precedence | Operators | Example | Note |
|------------|-----------|---------|------|
| 1 | `()` `[]` `.` `->` | `obj.member` | Access first |
| 2 | `++` `--` (prefix) `!` `~` | `++x` | Unary operators |
| 3 | `*` `/` `%` | `x * y` | Math first |
| 4 | `+` `-` | `x + y` | Then add/subtract |
| 5 | `<` `<=` `>` `>=` | `x < y` | Compare values |
| 6 | `==` `!=` | `x == y` | Test equality |
| 7 | `&&` | `x && y` | Logical AND |
| 8 | `\|\|` | `x \|\| y` | Logical OR |
| 9 | `=` `+=` `-=` | `x = y` | Assignment last |

## Success Checklist

After Chapter 7, you should be able to:
- [ ] Understand operator precedence and predict expression evaluation
- [ ] Handle type conversions safely in mixed expressions
- [ ] Implement basic arithmetic operators for custom classes
- [ ] Create comparison operators following canonical patterns
- [ ] Implement stream output operators correctly
- [ ] Know when operator overloading is appropriate vs. function names
- [ ] Debug expression evaluation using parentheses and explicit casts

**Not there yet?** Focus on operator precedence first - it's the foundation. Use parentheses liberally until precedence becomes automatic.

**Ready to move on?** Great! Chapter 8 will cover control flow statements and exception handling.

---

## What's Next?

**Chapter 8: Statements** will cover:
- Control flow statements (if/else, switch, loops)
- Exception handling with try/catch blocks
- RAII principles in control structures
- Advanced control flow patterns

**You've mastered expressions and operators!** Good operator overloading makes your classes feel natural and intuitive to use. You now have the power to make custom types work seamlessly with familiar syntax.

---

*Remember: Expressions are the building blocks of computation. Master precedence, use explicit conversions, and make your operators intuitive - your code will be both correct and beautiful.*