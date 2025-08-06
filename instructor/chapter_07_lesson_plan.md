# Chapter 7: Expressions - Lesson Plan

**Target Audience**: Students with Python or Java experience  
**Time Budget**: Maximum 2.5 hours of learning content  
**Prerequisites**: Students understand basic programming, types, references, object lifecycle, runtime/compile-time polymorphism, and basic templates from Chapters 1-6.

## Development Environment Setup
**Continue using your chosen workflow from previous chapters:**
- **Option A**: Docker + Command Line
- **Option B**: VS Code + Docker (helpful for operator overloading debugging)
- **Option C**: VS Code + Local Compiler

**For Chapter 7's operator concepts, stepping through expressions shows evaluation order!**

---

## Learning Objectives
By the end of this chapter, students will be able to:
1. Understand C++'s expression evaluation rules and operator precedence
2. Use built-in operators effectively with proper type conversions
3. Implement basic operator overloading for custom classes
4. Apply operator overloading best practices and conventions
5. Distinguish when and why to overload operators vs. using member functions

## Lesson Structure (2.5 hours total)

### Part 1: Expression Fundamentals (45 minutes)

#### 1.1 What are Expressions? (15 minutes)
**Connecting to Python/Java Experience**:
- In Python: `x + y`, `obj.method()`, `list[index]` are all expressions
- In Java: Similar concept but with strict typing
- C++: More explicit control over expression evaluation

**Key Concepts**:
```cpp
// Simple expressions
int x = 5;
int y = 10;
int result = x + y * 2;  // Precedence matters!

// Complex expressions with function calls
auto value = calculate(x) + transform(y);

// Expressions have types and values
double ratio = static_cast<double>(x) / y;  // Type conversion
```

**Practice Activity (5 minutes)**:
Students predict the output of various expressions with different precedence.

#### 1.2 Operator Precedence and Associativity (15 minutes)
**Coming from Python/Java**:
- Similar precedence rules but C++ is more explicit
- Parentheses work the same way
- Assignment operators are right-associative

**Essential Precedence Rules**:
```cpp
// High to low precedence (common ones)
obj.member          // Member access
arr[index]          // Subscript  
func()              // Function call
++x, --x            // Prefix increment/decrement
x++, x--            // Postfix increment/decrement
*, /, %             // Multiplicative
+, -                // Additive
<<, >>              // Shift operators
<, <=, >, >=        // Relational
==, !=              // Equality
&&                  // Logical AND
||                  // Logical OR
=, +=, -=, etc.     // Assignment (right-associative)
```

**Practice Activity (10 minutes)**:
Work through precedence exercises, emphasizing when to use parentheses for clarity.

#### 1.3 Type Conversions in Expressions (15 minutes)
**Different from Python/Java**:
- C++ has implicit conversions that can be surprising
- Need to understand when conversions happen

```cpp
// Implicit conversions
int x = 5;
double y = 2.0;
auto result = x + y;  // x promoted to double

// Mixed signed/unsigned (dangerous!)
int signed_val = -1;
unsigned int unsigned_val = 1;
if (signed_val < unsigned_val) {  // Surprising result!
    // This might not work as expected
}

// Safe explicit conversions
double safe_division = static_cast<double>(x) / y;
```

### Part 2: Built-in Operators Deep Dive (45 minutes)

#### 2.1 Arithmetic and Assignment Operators (15 minutes)
**Familiar from other languages but with C++ specifics**:

```cpp
// Basic arithmetic - same as Python/Java
int a = 10, b = 3;
int sum = a + b;      // 13
int diff = a - b;     // 7
int product = a * b;  // 30
int quotient = a / b; // 3 (integer division!)
int remainder = a % b; // 1

// Compound assignment - efficient and clear
a += 5;  // Same as a = a + 5, but potentially more efficient
b *= 2;  // Same as b = b * 2

// Increment/decrement - be careful with pre vs post
int x = 5;
int y = ++x;  // x becomes 6, y gets 6
int z = x++;  // z gets 6, then x becomes 7
```

**Common Mistake Discussion (5 minutes)**:
Integer division surprises for Python developers.

#### 2.2 Logical and Comparison Operators (15 minutes)
**Mostly familiar but with C++ quirks**:

```cpp
// Comparison operators
bool result1 = (5 > 3);        // true
bool result2 = (5.0 == 5);     // true (implicit conversion)
bool result3 = (5 != 10);      // true

// Logical operators with short-circuit evaluation
bool condition1 = true;
bool condition2 = false;
bool result = condition1 && condition2;  // false, condition2 evaluated
bool result2 = condition1 || condition2; // true, condition2 NOT evaluated

// Be careful with operator precedence
if (x > 0 && y > 0 || z > 0) {  // Confusing! Better to use parentheses
}
if ((x > 0 && y > 0) || z > 0) {  // Clear intent
}
```

#### 2.3 Bitwise and Shift Operators (15 minutes)
**New for many Python developers**:

```cpp
// Bitwise operators
int a = 12;   // 1100 in binary
int b = 10;   // 1010 in binary
int and_result = a & b;  // 1000 = 8
int or_result = a | b;   // 1110 = 14
int xor_result = a ^ b;  // 0110 = 6
int not_result = ~a;     // Bitwise NOT

// Shift operators
int left_shift = a << 2;  // 1100 -> 110000 = 48
int right_shift = a >> 1; // 1100 -> 110 = 6

// Common use: powers of 2
int power_of_2 = 1 << 4;  // 1 * 2^4 = 16
```

**When to use**: Low-level programming, flags, performance-critical code.

### Part 3: Introduction to Operator Overloading (60 minutes)

#### 3.1 Why Operator Overloading? (20 minutes)
**Motivation from familiar examples**:

```cpp
// Without operator overloading - verbose
std::string first = "Hello";
std::string second = "World";
std::string result = first.append(" ").append(second);

// With operator overloading - natural
std::string result = first + " " + second;

// Mathematical types become intuitive
Vector3D a{1.0, 2.0, 3.0};
Vector3D b{4.0, 5.0, 6.0};
Vector3D sum = a + b;  // Much better than a.add(b)
```

**Design Principles**:
1. Make operators behave as users expect
2. Don't overload operators for unrelated operations
3. Maintain relationships between operators (if you overload `+`, consider `+=`)
4. Be consistent with built-in types

#### 3.2 Basic Operator Overloading Syntax (20 minutes)

```cpp
class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    // Member function approach
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    // Compound assignment
    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;  // Return reference for chaining
    }
    
    // Comparison operator
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    // For debugging
    void print() const {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};

// Usage
Point p1{3.0, 4.0};
Point p2{1.0, 2.0};
Point sum = p1 + p2;  // Creates Point(4.0, 6.0)
p1 += p2;             // Modifies p1 in place
bool same = (p1 == sum);  // true
```

#### 3.3 Friend Functions and Non-Member Operators (20 minutes)

**When member functions aren't enough**:

```cpp
class Point {
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend Point operator*(double scalar, const Point& p);
    
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    // This works: point * scalar
    Point operator*(double scalar) const {
        return Point(x * scalar, y * scalar);
    }
};

// This enables: scalar * point (can't be a member function)
Point operator*(double scalar, const Point& p) {
    return Point(scalar * p.x, scalar * p.y);
}

// Stream output operator
std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

// Usage
Point p{3.0, 4.0};
Point scaled1 = p * 2.0;    // member function
Point scaled2 = 2.0 * p;    // non-member function
std::cout << p << std::endl; // stream operator
```

### Part 4: Best Practices and Common Patterns (20 minutes)

#### 4.1 The Big Three for Operators (10 minutes)
**Essential operator relationships**:

```cpp
class MyClass {
public:
    // If you implement ==, also implement !=
    bool operator==(const MyClass& other) const { /* ... */ }
    bool operator!=(const MyClass& other) const { 
        return !(*this == other); 
    }
    
    // If you implement <, you can derive the others
    bool operator<(const MyClass& other) const { /* ... */ }
    bool operator<=(const MyClass& other) const { 
        return *this < other || *this == other; 
    }
    bool operator>(const MyClass& other) const { 
        return !(*this <= other); 
    }
    bool operator>=(const MyClass& other) const { 
        return !(*this < other); 
    }
    
    // If you implement +, consider implementing +=
    MyClass& operator+=(const MyClass& other) { /* modify this */ return *this; }
    MyClass operator+(const MyClass& other) const { 
        MyClass result = *this; 
        result += other; 
        return result; 
    }
};
```

#### 4.2 What NOT to Overload (10 minutes)
**Common mistakes to avoid**:

```cpp
// DON'T do this - violates expectations
class Employee {
public:
    // BAD: + doesn't make sense for employees
    Employee operator+(const Employee& other) const;
    
    // BAD: << should be for output, not some other operation
    void operator<<(const std::string& task) const;
};

// Instead, use descriptive member functions
class Employee {
public:
    Employee merge_with(const Employee& other) const;
    void assign_task(const std::string& task);
};
```

**Guidelines**:
- Only overload operators when the meaning is obvious
- Don't overload `&&`, `||`, or `,` (comma operator) - you lose short-circuit evaluation
- Be very careful with conversion operators

## Hands-On Activities Throughout

### Quick Checks (5 minutes each)
1. Precedence quiz with mixed expressions
2. Predict output of increment/decrement operations
3. Identify when operator overloading is appropriate

### Coding Exercises (10 minutes each)
1. Fix precedence issues in given expressions
2. Implement basic arithmetic operators for a `Fraction` class
3. Add stream output operator to a custom class

## Key Takeaways
1. **Expressions are more than just math** - they include function calls, member access, etc.
2. **Precedence matters** - when in doubt, use parentheses for clarity
3. **Operator overloading should feel natural** - don't surprise users
4. **Member vs. non-member operators** - choose based on what makes sense
5. **Implement related operators together** - maintain consistency

## Connection to Next Chapter
Chapter 8 will cover statements and control flow, building on expression evaluation to control program behavior. Students will use the operators learned here in conditional statements and loops.

## Assessment Preparation
Students should be comfortable:
- Reading complex expressions and predicting their evaluation order
- Implementing basic operator overloading for custom classes
- Choosing appropriate operators to overload for different scenarios
- Understanding when to use member vs. non-member operator functions