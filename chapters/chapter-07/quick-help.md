# Chapter 7: Expressions - Quick Help Guide

**For students with Python/Java background learning C++ expressions and operator overloading**

---

## 🚨 Most Common Mistakes

### 1. Operator Precedence Confusion
```cpp
// WRONG assumption
int result = 5 + 3 * 2;  // Not 16! It's 11 because * comes first

// SAFE approach - use parentheses when in doubt
int result = 5 + (3 * 2);  // Clear: 11
int result = (5 + 3) * 2;  // Clear: 16
```

### 2. Integer Division Trap (Python developers!)
```cpp
// WRONG - gives 0, not 0.666...
double result = 2 / 3;

// RIGHT - force floating-point division
double result = 2.0 / 3.0;
// OR
double result = static_cast<double>(2) / 3;
```

### 3. Signed/Unsigned Comparison
```cpp
// DANGEROUS - might not work as expected
int negative = -1;
unsigned int positive = 1;
if (negative < positive) { /* might not execute! */ }

// SAFER - cast to same type
if (negative < static_cast<int>(positive)) { /* works */ }
```

---

## 📋 Operator Precedence Cheat Sheet

**From highest to lowest precedence (most commonly used):**

| Precedence | Operators | Example | Note |
|------------|-----------|---------|------|
| 1 | `()` `[]` `.` `->` | `obj.member` | Left-to-right |
| 2 | `++` `--` (postfix) | `x++` | Left-to-right |
| 3 | `++` `--` (prefix) `!` `~` | `++x` | Right-to-left |
| 4 | `*` `/` `%` | `x * y` | Left-to-right |
| 5 | `+` `-` | `x + y` | Left-to-right |
| 6 | `<<` `>>` | `x << 2` | Left-to-right |
| 7 | `<` `<=` `>` `>=` | `x < y` | Left-to-right |
| 8 | `==` `!=` | `x == y` | Left-to-right |
| 9 | `&&` | `x && y` | Left-to-right |
| 10 | `\|\|` | `x \|\| y` | Left-to-right |
| 11 | `=` `+=` `-=` etc. | `x = y` | **Right-to-left** |

**Memory tip**: PEMDAS + comparisons + logical ops + assignment

---

## ⚡ Quick Operator Overloading Reference

### Basic Syntax Patterns
```cpp
class MyClass {
public:
    // Binary operators (usually const member functions)
    MyClass operator+(const MyClass& other) const {
        // Return new object
    }
    
    // Compound assignment (non-const, return reference)
    MyClass& operator+=(const MyClass& other) {
        // Modify this object
        return *this;
    }
    
    // Comparison (const member functions)
    bool operator==(const MyClass& other) const {
        // Return bool
    }
    
    // Stream output (must be non-member)
    friend ostream& operator<<(ostream& os, const MyClass& obj);
};

// Non-member operators (when left operand isn't your class)
MyClass operator*(double scalar, const MyClass& obj) {
    return obj * scalar;  // Reuse member operator
}
```

### Essential Return Types
- **Arithmetic operators** (`+`, `-`, `*`): Return new object by value
- **Compound assignment** (`+=`, `-=`): Return `MyClass&` (reference to *this)
- **Comparison operators** (`==`, `<`): Return `bool`
- **Stream operators** (`<<`, `>>`): Return stream reference
- **Increment/decrement**: Prefix returns reference, postfix returns copy

---

## 🔧 Debugging Checklist

### When Your Operators Don't Work:

1. **Check const-correctness**
   ```cpp
   // WRONG - can't call non-const method on const object
   bool operator==(const MyClass& other) {  // Missing const!
   
   // RIGHT
   bool operator==(const MyClass& other) const {
   ```

2. **Check return types**
   ```cpp
   // WRONG - should return reference for chaining
   MyClass operator+=(const MyClass& other) {
   
   // RIGHT
   MyClass& operator+=(const MyClass& other) {
       // ... modify this ...
       return *this;
   }
   ```

3. **Member vs. non-member function**
   ```cpp
   // Can't do this as member function:
   // 5.0 * my_object  
   
   // Must be non-member:
   MyClass operator*(double scalar, const MyClass& obj) {
       return obj * scalar;
   }
   ```

---

## 🎯 Common Operator Overloading Patterns

### The "Big Three" Relationships
```cpp
class MyClass {
public:
    // Implement these first
    bool operator==(const MyClass& other) const { /* ... */ }
    bool operator<(const MyClass& other) const { /* ... */ }
    MyClass& operator+=(const MyClass& other) { /* ... */ return *this; }
    
    // Then derive these from the above
    bool operator!=(const MyClass& other) const { return !(*this == other); }
    bool operator>(const MyClass& other) const { return other < *this; }
    bool operator<=(const MyClass& other) const { return !(other < *this); }
    bool operator>=(const MyClass& other) const { return !(*this < other); }
    
    MyClass operator+(const MyClass& other) const {
        MyClass result = *this;
        result += other;
        return result;
    }
};
```

### Stream Output Template
```cpp
// Always use this pattern for stream output
ostream& operator<<(ostream& os, const MyClass& obj) {
    os << "MyClass(" << obj.get_data() << ")";
    return os;  // DON'T FORGET THIS!
}
```

---

## ⚠️ What NOT to Overload

### Bad Ideas:
```cpp
// DON'T overload operators for unrelated operations
Employee operator+(const Employee& a, const Employee& b);  // What does this mean?
File operator*(const File& f, int copies);  // Confusing!

// DON'T overload these operators (you lose special behavior):
// &&, ||, comma operator

// DON'T surprise users
String operator+(const String& s, int x);  // Expected String + String
```

### Good Alternatives:
```cpp
// Use descriptive function names instead
Employee merge_employees(const Employee& a, const Employee& b);
File duplicate_file(const File& f, int copies);
String repeat(const String& s, int times);
```

---

## 🔍 Type Conversion Quick Fixes

### Safe Conversions
```cpp
// Integer to floating-point
double result = static_cast<double>(int_value) / another_int;

// Floating-point to integer (with rounding)
#include <cmath>
int rounded = static_cast<int>(std::round(double_value));

// Check for overflow before converting
if (large_value <= INT_MAX) {
    int safe_int = static_cast<int>(large_value);
}
```

### Avoid These Traps
```cpp
// Mixed signed/unsigned - cast to common type
int signed_val = -1;
unsigned int unsigned_val = 5;
// WRONG: if (signed_val < unsigned_val)
// RIGHT:
if (signed_val < static_cast<int>(unsigned_val))

// Floating-point equality - use epsilon
const double EPSILON = 1e-9;
// WRONG: if (a == b)
// RIGHT: 
if (std::abs(a - b) < EPSILON)
```

---

## 📝 Quick Testing Template

```cpp
// Use this to test your operator overloading
int main() {
    MyClass a(/* some values */);
    MyClass b(/* some values */);
    
    // Test arithmetic
    MyClass sum = a + b;
    a += b;
    
    // Test comparisons
    bool equal = (a == b);
    bool less = (a < b);
    
    // Test stream output
    cout << "a: " << a << endl;
    cout << "sum: " << sum << endl;
    
    return 0;
}
```

---

## 🆘 When You're Stuck

1. **Compiler errors about const**: Add `const` to member functions that don't modify the object
2. **Can't chain operations**: Make sure compound operators return `*this`
3. **Operator doesn't exist**: You might need a non-member function
4. **Weird comparison results**: Check for mixed signed/unsigned types
5. **Stream output doesn't work**: Make sure you return the stream reference

**Remember**: When in doubt, use parentheses for clarity and prefer explicit conversions over implicit ones!