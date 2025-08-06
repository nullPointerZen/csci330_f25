# Chapter 7: Expressions - Complete Guide

## 🎯 Learning Objectives (5 minutes)

By the end of this chapter, you will:
1. **Master** C++ expression evaluation rules and operator precedence
2. **Use** built-in operators effectively with type conversions
3. **Implement** operator overloading for custom classes
4. **Apply** operator overloading best practices and conventions
5. **Distinguish** when to overload operators vs using member functions
6. **Debug** expression evaluation using VS Code step-through

**⏱️ Time Budget: ~4.75 hours total**
- Learning: 2.5 hours
- Problems: 2.25 hours

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](./DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 📊 Core Concepts: Expressions and Operators (2.5 hours)

### 1. What Are Expressions?

**Expressions are combinations of operators, operands, and function calls that produce values:**

```cpp
int x = 5;
int y = 10;
int result = x + y * 2;          // Expression: x + (y * 2)
bool condition = (x > 0) && (y < 20);  // Boolean expression
auto value = calculate(x) + transform(y); // Function call expressions
```

**Python/Java Connection**:
- **Python**: `x + y`, `obj.method()`, `list[index]` - same concept, dynamic typing
- **Java**: Similar expressions but with strict compile-time typing
- **C++**: More explicit control over type conversions and evaluation

### 2. Operator Precedence and Associativity

**C++ has well-defined rules for expression evaluation:**

| Precedence | Operators | Associativity | Example |
|-----------|-----------|---------------|---------|
| **Highest** | `::` (scope) | Left-to-right | `std::cout` |
| | `()` `[]` `->` `.` | Left-to-right | `arr[i]`, `obj.member` |
| | `!` `~` `++` `--` `+` `-` `*` `&` | Right-to-left | `!flag`, `++i` |
| | `*` `/` `%` | Left-to-right | `a * b / c` |
| | `+` `-` | Left-to-right | `a + b - c` |
| | `<<` `>>` | Left-to-right | `cout << x` |
| | `<` `<=` `>` `>=` | Left-to-right | `a < b <= c` |
| | `==` `!=` | Left-to-right | `a == b != c` |
| | `&&` | Left-to-right | `a && b && c` |
| | `\|\|` | Left-to-right | `a \|\| b \|\| c` |
| **Lowest** | `=` `+=` `-=` etc. | Right-to-left | `a = b = c` |

**Example with precedence:**
```cpp
int result = 2 + 3 * 4;        // 2 + (3 * 4) = 14, not (2 + 3) * 4 = 20
bool test = x > 0 && y < 10;   // (x > 0) && (y < 10) - comparison before logical
```

### 3. Type Conversions in Expressions

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

### 4. Operator Overloading: Making Your Classes Expressive

**You can define how operators work with your custom types:**

```cpp
class Vector2D {
public:
    double x, y;
    
    Vector2D(double x = 0, double y = 0) : x{x}, y{y} {}
    
    // Addition operator
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D{x + other.x, y + other.y};
    }
    
    // Subtraction operator
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D{x - other.x, y - other.y};
    }
    
    // Scalar multiplication
    Vector2D operator*(double scalar) const {
        return Vector2D{x * scalar, y * scalar};
    }
    
    // Compound assignment
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    // Comparison
    bool operator==(const Vector2D& other) const {
        return (x == other.x) && (y == other.y);
    }
    
    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};

// Usage looks natural!
Vector2D a{1.0, 2.0};
Vector2D b{3.0, 4.0};
Vector2D c = a + b;        // Uses operator+
c *= 2.0;                  // Uses operator*= (if defined)
std::cout << c << std::endl; // Uses operator<<
```

### 5. Best Practices for Operator Overloading

**Follow these conventions to make your code intuitive:**

| Operator | Implementation | Return Type | Notes |
|----------|---------------|-------------|--------|
| `+` `-` `*` `/` | Member or friend | New object | Don't modify operands |
| `+=` `-=` `*=` `/=` | Member | Reference to `*this` | Modify left operand |
| `==` `!=` `<` `>` | Member or friend | `bool` | Comparison operators |
| `<<` `>>` | Friend function | Stream reference | For I/O streams |
| `[]` | Member only | Reference | Array-like access |
| `()` | Member only | Any type | Function call operator |

**Golden Rules**:
1. **Don't surprise users** - `+` should add, `==` should compare
2. **Be consistent** - if you define `==`, define `!=` too
3. **Return appropriate types** - arithmetic returns values, assignment returns references
4. **Use member vs friend appropriately** - member when left operand is your type

---

## 🔍 VS Code Debugging Expressions (20 minutes)

### Debugging Complex Expressions

**VS Code techniques for understanding expression evaluation:**

1. **Step Through Evaluation**: Use F10 to see order of operations
2. **Watch Subexpressions**: Add parts of complex expressions to Watch panel
3. **Inspect Conversions**: See how types are converted during evaluation
4. **Operator Overloading**: Step into custom operators to see implementation

**Debug Configuration for Expressions:**
```json
{
    "name": "Debug Expressions",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/${fileBasenameNoExtension}",
    "setupCommands": [
        {
            "description": "Show expression evaluation order",
            "text": "-gdb-set print expression on"
        }
    ]
}
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

### Problem Set 1: Expression Fundamentals (45 minutes)

#### Problem 1.1: Precedence and Evaluation (15 minutes)
**Master operator precedence:**

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5, b = 10, c = 15, d = 20;
    
    // TODO: Predict the results, then verify
    cout << "Expression results:\n";
    
    int result1 = a + b * c;
    cout << "a + b * c = " << result1 << endl;
    // What is this: 5 + (10 * 15) or (5 + 10) * 15?
    
    int result2 = a + b * c / d;
    cout << "a + b * c / d = " << result2 << endl;
    // What about: 5 + (10 * 15) / 20 or 5 + 10 * (15 / 20)?
    
    bool result3 = a < b && c > d;
    cout << "a < b && c > d = " << result3 << endl;
    
    bool result4 = a == 5 || b == 10 && c == 15;
    cout << "a == 5 || b == 10 && c == 15 = " << result4 << endl;
    // Which operator has higher precedence: || or &&?
    
    // TODO: Add parentheses to make precedence explicit
    int explicit1 = a + (b * c);
    int explicit2 = (a < b) && (c > d);
    
    cout << "With explicit parentheses:\n";
    cout << "a + (b * c) = " << explicit1 << endl;
    cout << "(a < b) && (c > d) = " << explicit2 << endl;
    
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

#### Problem 2.1: Complex Number Class (25 minutes)
**Create a mathematical class with operators:**

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Complex {
public:
    double real, imag;
    
    Complex(double r = 0.0, double i = 0.0) : real{r}, imag{i} {}
    
    // TODO: Addition operator
    Complex operator+(const Complex& other) const {
        return Complex{real + other.real, imag + other.imag};
    }
    
    // TODO: Subtraction operator
    Complex operator-(const Complex& other) const {
        return Complex{real - other.real, imag - other.imag};
    }
    
    // TODO: Multiplication operator (a+bi)(c+di) = (ac-bd) + (ad+bc)i
    Complex operator*(const Complex& other) const {
        double new_real = real * other.real - imag * other.imag;
        double new_imag = real * other.imag + imag * other.real;
        return Complex{new_real, new_imag};
    }
    
    // TODO: Compound assignment
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    // TODO: Equality comparison
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }
    
    // TODO: Stream output operator
    friend ostream& operator<<(ostream& os, const Complex& c) {
        if (c.imag >= 0) {
            return os << c.real << " + " << c.imag << "i";
        } else {
            return os << c.real << " " << c.imag << "i";
        }
    }
    
    // TODO: Magnitude method
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }
};

int main() {
    Complex a{3.0, 4.0};    // 3 + 4i
    Complex b{1.0, 2.0};    // 1 + 2i
    
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    
    Complex sum = a + b;
    cout << "a + b = " << sum << endl;
    
    Complex product = a * b;
    cout << "a * b = " << product << endl;
    
    a += b;
    cout << "After a += b, a = " << a << endl;
    
    cout << "Magnitude of a: " << a.magnitude() << endl;
    
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