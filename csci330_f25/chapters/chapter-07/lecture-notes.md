# Chapter 7: Expressions - Complete Guide

## 📖 Learning Sequence (IMPORTANT!)

**🔄 How This Chapter Works:**
1. **📚 FIRST**: Read Textbook Chapter 7 "Expressions" (2-3 hours)
2. **🔍 SECOND**: Work through these lecture notes for Python/Java context and hands-on practice (4-5 hours)
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
- **💻 Hands-on Work: 4-5 hours** (course materials + assignments + debugging)
- **📖 Note: Reading time is separate and must be completed BEFORE hands-on work**

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](./DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 📊 Core Concepts: Expressions and Operators (2.5 hours)

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
boolean condition = x > 0 && y < 20; // When does evaluation stop?

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

---

## 🔍 VS Code Debugging: Understanding Expression Evaluation (20 minutes)

### Debugging Expressions Like a Pro

**When expressions don't work as expected, VS Code is your detective tool:**

**1. Break Down Complex Expressions**
```cpp
// Instead of debugging this complex expression:
if ((user.age >= 18 && user.has_license()) || user.is_supervised() && vehicle.is_safe()) {
    // Hard to debug when this fails
}

// Break it down for easier debugging:
bool is_adult_with_license = user.age >= 18 && user.has_license();
bool is_supervised_safely = user.is_supervised() && vehicle.is_safe();
if (is_adult_with_license || is_supervised_safely) {
    // Now you can inspect each part in VS Code debugger
}
```

**2. Use Watch Panel for Subexpressions**
- Add `user.age >= 18` to watch
- Add `user.has_license()` to watch  
- See exactly where the logic fails

**3. Step Through Operator Overloading**
- Use F11 to step INTO overloaded operators
- See exactly what your custom `+`, `==`, `<<` operators are doing

**Debugging Strategy for Expressions:**
```cpp
// When this doesn't work as expected:
if (calculate_score() > threshold && player.is_active()) {
    // Confusing when it fails
}

// Debug version - break into parts:
double score = calculate_score();       // Set breakpoint here
bool active = player.is_active();      // And here  
bool should_proceed = score > threshold && active;

// Now you can inspect:
// - What value did calculate_score() return?
// - Is player.is_active() true or false?
// - What is threshold's current value?
// - Does the final boolean make sense?
```

### Debugging Strategies

| What to Debug | How to Debug It |
|---------------|-----------------|
| **Precedence confusion** | Use parentheses and step through |
| **Type conversions** | Watch panel to see actual types |
| **Operator overloading** | Step into custom operators |
| **Complex expressions** | Break into smaller parts |

---

## 🧩 Hands-On Problems (2.25 hours)

**📖 Ready to Apply**: You've read the textbook and reviewed the Python/Java connections above. Now let's put that knowledge to work with hands-on practice that prepares you for the assignments.

### Problem Set 1: Expression Fundamentals (45 minutes)

#### Problem 1.1: Expression Evaluation Detective (15 minutes)
**Learn to predict expression results before running code:**

```cpp
#include <iostream>
using namespace std;

int main() {
    // TODO: Before running, predict what each expression evaluates to
    cout << "=== Expression Detective Challenge ===\n";
    cout << "Predict the results, then run to check!\n\n";
    
    // Basic precedence challenges
    cout << "Challenge 1: Basic arithmetic\n";
    cout << "2 + 3 * 4 = " << (2 + 3 * 4) << endl;
    cout << "Prediction: Is it 14 or 20?\n\n";
    
    cout << "Challenge 2: Mixed operators\n";
    cout << "10 - 6 / 2 = " << (10 - 6 / 2) << endl;
    cout << "Prediction: Is it 2 or 7?\n\n";
    
    cout << "Challenge 3: Boolean logic\n";
    bool x = true, y = false;
    cout << "true || false && false = " << (x || y && false) << endl;
    cout << "Prediction: Does && or || happen first?\n\n";
    
    cout << "Challenge 4: Assignment vs comparison\n";
    int a = 5;
    // TODO: What's wrong with this condition?
    if (a = 10) {  // BUG: Assignment, not comparison!
        cout << "This will always execute (a is now " << a << ")\n";
    }
    
    a = 5;  // Reset
    if (a == 10) {  // Fixed: Comparison
        cout << "This won't execute\n";
    } else {
        cout << "Correct: a (" << a << ") is not 10\n";
    }
    
    cout << "\n=== Pro Tips ===\n";
    cout << "1. When in doubt, use parentheses: (2 + 3) * 4\n";
    cout << "2. Watch out for = vs == in conditions\n";
    cout << "3. && has higher precedence than ||\n";
    
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
    cout << "Type conversion examples:\n";
    
    auto result1 = i + d;  // What type is result1?
    cout << "int + double = " << result1 << " (type: double)\n";
    
    auto result2 = i / 3;   // Integer division
    cout << "int / int = " << result2 << endl;
    
    auto result3 = static_cast<double>(i) / 3;  // Force double division
    cout << "double / int = " << result3 << endl;
    
    auto result4 = i * f;   // int * float
    cout << "int * float = " << result4 << " (what type?)\n";
    
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
    cout << "Expensive check called!\n";
    return true;
}

bool another_check() {
    cout << "Another check called!\n";
    return false;
}

int main() {
    cout << "Short-circuit evaluation examples:\n";
    
    // TODO: AND short-circuit
    cout << "\nTesting: false && expensive_check()\n";
    bool result1 = false && expensive_check();  // Should expensive_check() be called?
    cout << "Result: " << result1 << "\n";
    
    cout << "\nTesting: true && expensive_check()\n";
    bool result2 = true && expensive_check();   // What about now?
    cout << "Result: " << result2 << "\n";
    
    // TODO: OR short-circuit
    cout << "\nTesting: true || another_check()\n";
    bool result3 = true || another_check();     // Should another_check() be called?
    cout << "Result: " << result3 << "\n";
    
    cout << "\nTesting: false || another_check()\n";
    bool result4 = false || another_check();    // What about now?
    cout << "Result: " << result4 << "\n";
    
    return 0;
}
```

### Problem Set 2: Basic Operator Overloading (60 minutes)

#### Problem 2.1: Fraction Class (25 minutes)
**Create a practical class that students understand better than complex numbers:**

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
    
    // TODO: Addition operator (a/b + c/d = (ad + bc)/(bd))
    Fraction operator+(const Fraction& other) const {
        int new_num = numerator * other.denominator + other.numerator * denominator;
        int new_den = denominator * other.denominator;
        return Fraction{new_num, new_den};
    }
    
    // TODO: Subtraction operator
    Fraction operator-(const Fraction& other) const {
        int new_num = numerator * other.denominator - other.numerator * denominator;
        int new_den = denominator * other.denominator;
        return Fraction{new_num, new_den};
    }
    
    // TODO: Multiplication operator (a/b * c/d = ac/bd)
    Fraction operator*(const Fraction& other) const {
        return Fraction{numerator * other.numerator, denominator * other.denominator};
    }
    
    // TODO: Division operator (a/b / c/d = ad/bc)
    Fraction operator/(const Fraction& other) const {
        return Fraction{numerator * other.denominator, denominator * other.numerator};
    }
    
    // TODO: Compound assignment
    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }
    
    // TODO: Comparison operators
    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }
    
    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }
    
    // TODO: Stream output operator
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
        
        cout << "Working with fractions:\n";
        cout << "a = " << a << " (" << a.to_decimal() << ")\n";
        cout << "b = " << b << " (" << b.to_decimal() << ")\n";
        cout << "c = " << c << " (" << c.to_decimal() << ")\n\n";
        
        // Test arithmetic
        cout << "Arithmetic operations:\n";
        cout << a << " + " << b << " = " << (a + b) << "\n";
        cout << a << " - " << b << " = " << (a - b) << "\n";
        cout << a << " * " << b << " = " << (a * b) << "\n";
        cout << a << " / " << b << " = " << (a / b) << "\n\n";
        
        // Test compound assignment
        Fraction sum = a;
        sum += b;
        cout << "After " << a << " += " << b << ": " << sum << "\n\n";
        
        // Test comparison
        cout << "Comparisons:\n";
        cout << a << " == " << b << ": " << (a == b) << "\n";
        cout << a << " < " << c << ": " << (a < c) << "\n";
        
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
    
    // TODO: Addition
    Money operator+(const Money& other) const {
        Money result;
        result.cents = cents + other.cents;
        return result;
    }
    
    // TODO: Subtraction
    Money operator-(const Money& other) const {
        Money result;
        result.cents = cents - other.cents;
        return result;
    }
    
    // TODO: Comparison operators
    bool operator==(const Money& other) const {
        return cents == other.cents;
    }
    
    bool operator<(const Money& other) const {
        return cents < other.cents;
    }
    
    bool operator>(const Money& other) const {
        return cents > other.cents;
    }
    
    // TODO: Compound assignment
    Money& operator+=(const Money& other) {
        cents += other.cents;
        return *this;
    }
    
    // TODO: Stream output
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
        cout << "Price 1 is more expensive than Price 2\n";
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
    
    // TODO: Concatenation operators
    MyString operator+(const MyString& other) const {
        return MyString{data + other.data};
    }
    
    MyString operator+(const string& str) const {
        return MyString{data + str};
    }
    
    // TODO: Compound assignment
    MyString& operator+=(const MyString& other) {
        data += other.data;
        return *this;
    }
    
    // TODO: Subscript operator
    char& operator[](size_t index) {
        return data[index];
    }
    
    const char& operator[](size_t index) const {
        return data[index];
    }
    
    // TODO: Comparison
    bool operator==(const MyString& other) const {
        return data == other.data;
    }
    
    // TODO: Stream operators
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

### Problem Set 3: Advanced Expression Techniques (40 minutes)

#### Problem 3.1: Matrix Class with Multiple Operators (25 minutes)
**Build a mathematical matrix class:**

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Matrix {
public:
    vector<vector<double>> data;
    size_t rows, cols;
    
    Matrix(size_t r, size_t c) : rows{r}, cols{c} {
        data.resize(rows, vector<double>(cols, 0.0));
    }
    
    // TODO: Access operators
    vector<double>& operator[](size_t row) {
        return data[row];
    }
    
    const vector<double>& operator[](size_t row) const {
        return data[row];
    }
    
    // TODO: Matrix addition
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions must match for addition");
        }
        
        Matrix result{rows, cols};
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result[i][j] = data[i][j] + other[i][j];
            }
        }
        return result;
    }
    
    // TODO: Scalar multiplication
    Matrix operator*(double scalar) const {
        Matrix result{rows, cols};
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }
    
    // TODO: Stream output
    friend ostream& operator<<(ostream& os, const Matrix& m) {
        for (size_t i = 0; i < m.rows; i++) {
            os << "[";
            for (size_t j = 0; j < m.cols; j++) {
                os << m.data[i][j];
                if (j < m.cols - 1) os << ", ";
            }
            os << "]";
            if (i < m.rows - 1) os << "\n";
        }
        return os;
    }
};

int main() {
    Matrix a{2, 3};
    Matrix b{2, 3};
    
    // Fill matrices
    a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
    a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;
    
    b[0][0] = 7; b[0][1] = 8; b[0][2] = 9;
    b[1][0] = 1; b[1][1] = 2; b[1][2] = 3;
    
    cout << "Matrix A:\n" << a << endl;
    cout << "Matrix B:\n" << b << endl;
    
    Matrix sum = a + b;
    cout << "A + B:\n" << sum << endl;
    
    Matrix scaled = a * 2.5;
    cout << "A * 2.5:\n" << scaled << endl;
    
    return 0;
}
```

#### Problem 3.2: Smart Iterator Class (15 minutes)
**Create an iterator with operator overloading:**

```cpp
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class SimpleIterator {
public:
    T* ptr;
    
    SimpleIterator(T* p) : ptr{p} {}
    
    // TODO: Dereference operator
    T& operator*() {
        return *ptr;
    }
    
    // TODO: Pre-increment
    SimpleIterator& operator++() {
        ++ptr;
        return *this;
    }
    
    // TODO: Post-increment
    SimpleIterator operator++(int) {
        SimpleIterator temp{ptr};
        ++ptr;
        return temp;
    }
    
    // TODO: Comparison operators
    bool operator==(const SimpleIterator& other) const {
        return ptr == other.ptr;
    }
    
    bool operator!=(const SimpleIterator& other) const {
        return ptr != other.ptr;
    }
    
    // TODO: Arithmetic operators
    SimpleIterator operator+(int offset) const {
        return SimpleIterator{ptr + offset};
    }
    
    SimpleIterator operator-(int offset) const {
        return SimpleIterator{ptr - offset};
    }
};

template<typename T>
class SimpleContainer {
public:
    vector<T> data;
    
    void push_back(const T& value) {
        data.push_back(value);
    }
    
    SimpleIterator<T> begin() {
        return SimpleIterator<T>{data.data()};
    }
    
    SimpleIterator<T> end() {
        return SimpleIterator<T>{data.data() + data.size()};
    }
};

int main() {
    SimpleContainer<int> container;
    container.push_back(10);
    container.push_back(20);
    container.push_back(30);
    container.push_back(40);
    
    cout << "Using custom iterator:\n";
    for (auto it = container.begin(); it != container.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // TODO: Test iterator arithmetic
    auto it = container.begin();
    cout << "First element: " << *it << endl;
    cout << "Third element: " << *(it + 2) << endl;
    
    return 0;
}
```

---

## 🔧 Quick Reference & Troubleshooting

### Operator Overloading Quick Reference

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

### Common Expression Errors

#### 1. Precedence Mistakes
```cpp
int result = 2 + 3 * 4;        // 14, not 20
bool test = a == b || c == d;  // Groups as: a == b || c == d
```

#### 2. Integer Division
```cpp
int result = 5 / 2;            // 2, not 2.5
double result = 5.0 / 2;       // 2.5 - at least one operand is double
```

#### 3. Assignment vs Comparison
```cpp
if (x = 5) { /* ... */ }       // Assignment! Always true
if (x == 5) { /* ... */ }      // Comparison - what you meant
```

#### 4. Overloaded Operator Returns
```cpp
// Wrong - should return new object
MyClass& operator+(const MyClass& rhs) const;

// Right - arithmetic operators return new objects
MyClass operator+(const MyClass& rhs) const;
```

---

## ✅ Chapter 7 Success Checklist

### Expression Fundamentals
- [ ] Understand operator precedence and associativity rules
- [ ] Can predict the order of expression evaluation
- [ ] Know how type conversions work in mixed expressions
- [ ] Understand short-circuit evaluation in logical operators

### Operator Overloading
- [ ] Can overload arithmetic operators (+, -, *, /)
- [ ] Can implement compound assignment operators (+=, -=, etc.)
- [ ] Can create comparison operators (==, !=, <, >, etc.)
- [ ] Can implement stream operators (<< and >>)

### Advanced Techniques
- [ ] Can overload subscript operator ([])
- [ ] Can create function call operator (())
- [ ] Understand when to use member vs friend functions
- [ ] Follow operator overloading best practices and conventions

---

## 🚀 What's Next?

**Chapter 8: Statements** will cover:
- Control flow statements (if/else, switch, loops)
- Exception handling with try/catch blocks
- RAII principles in control structures
- Advanced control flow patterns

**You've mastered expressions and operators!** 🎉 Operator overloading is one of C++'s most distinctive features, allowing you to create intuitive interfaces for your custom types. You now understand how to make your classes feel natural to use.

**Key Takeaway**: Good operator overloading makes code readable and intuitive. Follow conventions, don't surprise users, and remember that operator overloading is just syntactic sugar for function calls - but very powerful syntactic sugar!

---

*Remember: Expressions are the building blocks of computation. Understanding precedence, conversions, and operator overloading gives you precise control over how your code behaves and how natural it feels to use.*