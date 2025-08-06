# Chapter 15: Strings - Complete Guide

## 🎯 Learning Objectives (5 minutes)

By the end of this chapter, you will:
- **Master C++ string fundamentals** - Understand `std::string` vs C-style strings
- **Connect to your Python/Java knowledge** - See familiar string operations in C++ syntax
- **Apply modern string techniques** - Use string views, formatting, and efficient operations
- **Debug string problems** - Recognize common string errors and memory issues
- **Write robust string code** - Handle Unicode, locales, and performance considerations

**Time Commitment**: ~5 hours (2.5 hours concepts + 2.25 hours hands-on)

---

## 🛠️ Development Environment Check

Before starting, verify your environment works:
```bash
cd csci330_f25/assignment-templates/HW_01
mkdir -p build && cd build
cmake .. && make
./hello_world  # Should compile and run
```

If you see errors, review [chapter_01_development_setup.md](chapter_01_development_setup.md).

---

## 📚 Core Concepts

### Python/Java Developers: What's Different?

| Concept | Python | Java | C++ |
|---------|---------|------|-----|
| **String Type** | `str` (immutable) | `String` (immutable) | `std::string` (mutable) |
| **Creation** | `s = "hello"` | `String s = "hello"` | `std::string s = "hello"` |
| **Concatenation** | `s1 + s2` | `s1 + s2` | `s1 + s2` or `s1.append(s2)` |
| **Length** | `len(s)` | `s.length()` | `s.length()` or `s.size()` |
| **Indexing** | `s[0]` | `s.charAt(0)` | `s[0]` or `s.at(0)` |
| **Slicing** | `s[1:5]` | `s.substring(1,5)` | `s.substr(1,4)` |

**Key Insight**: Unlike Python/Java, C++ strings are **mutable** and give you direct memory access.

---

## 1. String Fundamentals

### C++ String Types Overview

```cpp
#include <string>
#include <string_view>  // C++17
#include <cstring>      // C-style functions

// Modern C++ strings (prefer these)
std::string name = "Alice";           // Mutable, owns memory
std::string_view view = "Bob";        // Read-only view, no ownership

// C-style strings (avoid unless interfacing with C libraries)
char old_style[] = "Charlie";         // Mutable array
const char* literal = "Dave";         // Immutable string literal
```

**Python/Java Note**: C++ gives you multiple string types for different use cases, unlike the single string type in Python/Java.

### String Creation and Initialization

```cpp
#include <string>

// Various initialization methods
std::string s1;                       // Empty string
std::string s2("Hello");              // From string literal
std::string s3 = "World";             // Copy initialization
std::string s4(10, 'A');             // 10 'A' characters: "AAAAAAAAAA"
std::string s5(s2);                   // Copy constructor
std::string s6 = s2 + " " + s3;       // Concatenation

// Range-based initialization
char chars[] = {'H', 'e', 'l', 'l', 'o'};
std::string s7(chars, chars + 5);     // From character array

// Substring from another string
std::string s8(s6, 0, 5);            // "Hello" (first 5 chars)
```

---

## 2. String Operations

### Basic Operations

```cpp
std::string text = "Hello, World!";

// Length and capacity
std::cout << text.size() << std::endl;        // 13 (same as length())
std::cout << text.capacity() << std::endl;    // Usually > size() for growth
std::cout << text.max_size() << std::endl;    // Maximum possible size

// Access characters
char first = text[0];                          // 'H' (no bounds checking)
char first_safe = text.at(0);                 // 'H' (throws if out of bounds)
char last = text.back();                      // '!' (C++11)
char& front_ref = text.front();               // 'H' (C++11, modifiable)

// Check if empty
if (text.empty()) {
    std::cout << "String is empty" << std::endl;
}
```

**Safety Tip**: Use `.at()` instead of `[]` when you're unsure about bounds - it throws exceptions for invalid indices.

### String Modification

```cpp
std::string text = "Hello";

// Append operations
text += " World";                    // "Hello World"
text.append("!");                    // "Hello World!"
text.append(3, '.');                 // "Hello World!..."
text.push_back('?');                 // "Hello World!...?"

// Insert operations
text.insert(5, ",");                 // "Hello, World!...?"
text.insert(6, " Beautiful");       // "Hello, Beautiful World!...?"

// Replace operations
text.replace(7, 9, "Amazing");       // "Hello, Amazing World!...?"
                                     // (pos=7, len=9, new_str)

// Erase operations
text.erase(text.size() - 4);         // Remove last 4 characters
text.clear();                        // Empty the string

// Resize
text.resize(10, 'X');               // "XXXXXXXXXX"
text.resize(5);                     // "XXXXX"
```

### String Searching

```cpp
std::string text = "The quick brown fox jumps over the lazy dog";

// Find operations (return std::string::npos if not found)
size_t pos = text.find("fox");                    // Position of "fox"
size_t pos2 = text.find("cat");                   // std::string::npos

if (pos != std::string::npos) {
    std::cout << "Found 'fox' at position " << pos << std::endl;
}

// Find with starting position
size_t pos3 = text.find("the", 10);               // Find "the" after position 10

// Other find variants
size_t last_pos = text.rfind("the");               // Find last occurrence
size_t vowel = text.find_first_of("aeiou");        // First vowel
size_t consonant = text.find_first_not_of("aeiou "); // First consonant (not vowel/space)
```

### Substring Operations

```cpp
std::string text = "Hello, Beautiful World!";

// Extract substrings
std::string hello = text.substr(0, 5);        // "Hello"
std::string world = text.substr(16);          // "World!" (from pos 16 to end)
std::string beautiful = text.substr(7, 9);    // "Beautiful"

// Python-style slicing comparison:
// Python: text[7:16]
// C++:    text.substr(7, 9)  // Note: length, not end position!
```

**Python Developer Note**: C++ `substr(start, length)` vs Python `text[start:end]` - different parameter meaning!

---

## 3. String Comparison

### Comparison Operations

```cpp
std::string a = "apple";
std::string b = "banana";
std::string c = "apple";

// Lexicographic comparison (like Python/Java)
bool equal = (a == c);              // true
bool not_equal = (a != b);          // true
bool less = (a < b);                // true (alphabetical order)
bool greater = (b > a);             // true

// Compare method (returns <0, 0, >0 like strcmp)
int result = a.compare(b);          // < 0 (a comes before b)
int result2 = a.compare(c);         // 0 (equal)
int result3 = b.compare(a);         // > 0 (b comes after a)

// Substring comparison
int result4 = a.compare(0, 3, "app"); // Compare first 3 chars with "app"
```

### Case-Insensitive Comparison

```cpp
#include <algorithm>
#include <cctype>

std::string lower_text(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), 
                   [](unsigned char c) { return std::tolower(c); });
    return s;
}

bool case_insensitive_equal(const std::string& a, const std::string& b) {
    return lower_text(a) == lower_text(b);
}

// Usage
std::string s1 = "Hello";
std::string s2 = "HELLO";
bool same = case_insensitive_equal(s1, s2);  // true
```

---

## 4. String Views (C++17)

### Understanding String Views

```cpp
#include <string_view>

// String view - lightweight, non-owning reference
void print_string(std::string_view sv) {  // More efficient than std::string&
    std::cout << sv << std::endl;
}

std::string text = "Hello, World!";
print_string(text);           // Works with std::string
print_string("Literal");      // Works with string literals
print_string(text.substr(0, 5)); // Works with substrings

// String view operations
std::string_view view = "The quick brown fox";
std::string_view sub = view.substr(4, 5);  // "quick" (no memory allocation!)
```

**Performance Note**: `string_view` avoids copying - perfect for read-only operations and function parameters.

### When to Use String Views

```cpp
// ✅ Good: Read-only function parameter
void process_text(std::string_view text) {
    // Read-only operations
    if (text.find("error") != std::string_view::npos) {
        // Handle error
    }
}

// ❌ Avoid: Storing string_view as member variable
class BadClass {
    std::string_view data;  // Dangerous - what if source string dies?
};

// ✅ Better: Store std::string for ownership
class GoodClass {
    std::string data;       // Owns the data safely
};
```

---

## 5. String Formatting and Conversion

### Numeric Conversions

```cpp
#include <string>

// Numbers to strings
int num = 42;
double pi = 3.14159;

std::string s1 = std::to_string(num);      // "42"
std::string s2 = std::to_string(pi);       // "3.141590" (default precision)

// Strings to numbers
std::string text = "123";
std::string float_text = "45.67";

int value = std::stoi(text);               // 123
double dvalue = std::stod(float_text);     // 45.67

// Error handling for conversions
try {
    int bad_conversion = std::stoi("not_a_number");
} catch (const std::invalid_argument& e) {
    std::cout << "Invalid conversion: " << e.what() << std::endl;
} catch (const std::out_of_range& e) {
    std::cout << "Out of range: " << e.what() << std::endl;
}
```

### Modern String Formatting (C++20)

```cpp
#include <format>  // C++20

int age = 25;
std::string name = "Alice";
double salary = 75000.50;

// Python-style formatting
std::string message = std::format("Hello {}, you are {} years old", name, age);
std::string money = std::format("Salary: ${:.2f}", salary);  // "Salary: $75000.50"

// Positional arguments
std::string ordered = std::format("{1} is {0} years old", age, name);
```

**Note**: If C++20 isn't available, use `<sstream>` or consider the {fmt} library.

### Stream-based Formatting (Pre-C++20)

```cpp
#include <sstream>
#include <iomanip>

std::ostringstream oss;
oss << "Hello " << name << ", you are " << age << " years old";
std::string message = oss.str();

// Precision control
std::ostringstream money_stream;
money_stream << std::fixed << std::setprecision(2) << "Salary: $" << salary;
std::string money = money_stream.str();
```

---

## 6. Advanced String Operations

### String Splitting

```cpp
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

// Usage
std::string csv = "apple,banana,cherry";
auto fruits = split(csv, ',');  // {"apple", "banana", "cherry"}
```

### String Trimming

```cpp
#include <algorithm>
#include <cctype>

std::string trim(std::string s) {
    // Trim from start
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    
    // Trim from end
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    
    return s;
}

// Usage
std::string messy = "  hello world  ";
std::string clean = trim(messy);  // "hello world"
```

### Regular Expressions

```cpp
#include <regex>

std::string text = "Phone: 123-456-7890, Email: user@example.com";

// Find phone numbers
std::regex phone_pattern(R"(\d{3}-\d{3}-\d{4})");
std::smatch match;

if (std::regex_search(text, match, phone_pattern)) {
    std::cout << "Phone: " << match.str() << std::endl;  // "123-456-7890"
}

// Replace emails
std::regex email_pattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)");
std::string masked = std::regex_replace(text, email_pattern, "[EMAIL]");
// "Phone: 123-456-7890, Email: [EMAIL]"
```

---

## 7. Performance Considerations

### Memory Management

```cpp
// Reserve capacity for better performance
std::string result;
result.reserve(1000);  // Pre-allocate space for 1000 characters

for (int i = 0; i < 100; ++i) {
    result += "data ";  // No reallocations needed
}

// Small String Optimization (SSO)
std::string small = "Hi";      // Stored in object itself (fast)
std::string large = "This is a very long string that exceeds SSO buffer"; // Heap allocated
```

### Efficient Concatenation

```cpp
// ❌ Inefficient: Multiple temporary objects
std::string result = s1 + s2 + s3 + s4;

// ✅ Better: Use append
std::string result = s1;
result.append(s2).append(s3).append(s4);

// ✅ Best: Use ostringstream for many concatenations
std::ostringstream oss;
oss << s1 << s2 << s3 << s4;
std::string result = oss.str();
```

---

## 8. Unicode and Internationalization

### UTF-8 Handling

```cpp
#include <locale>
#include <codecvt>

// C++17 and later: Use specialized libraries like ICU
// Basic UTF-8 validation
bool is_valid_utf8(const std::string& str) {
    // Implementation would check UTF-8 byte sequences
    // This is complex - use proven libraries in production
    return true;  // Simplified
}

// Working with Unicode
std::string utf8_text = u8"Hello 世界! 🌍";
std::cout << "UTF-8 text: " << utf8_text << std::endl;

// Character counting vs byte counting
std::cout << "Bytes: " << utf8_text.size() << std::endl;      // Byte count
// For actual character count, use ICU or similar library
```

**Important**: C++ strings store bytes, not characters. For proper Unicode handling, use specialized libraries.

---

## 🧩 Hands-On Problems

See [chapter_15_problems.md](chapter_15_problems.md) for practice exercises.

---

## 🔧 Quick Reference

See [chapter_15_quick_help.md](chapter_15_quick_help.md) for common errors and solutions.

---

## ✅ Success Checklist

Before moving on, ensure you can:

- [ ] Create and initialize strings in multiple ways
- [ ] Perform basic string operations (append, insert, erase)
- [ ] Search and extract substrings effectively
- [ ] Compare strings properly (case-sensitive and insensitive)
- [ ] Convert between strings and numbers
- [ ] Use string_view for efficient read-only operations
- [ ] Handle basic Unicode text appropriately
- [ ] Debug common string problems

---

## 🚀 What's Next

**Congratulations!** You've mastered C++ strings. This is a crucial skill that you'll use in every C++ program.

**Coming up**: Continue with the supplemental chapters for advanced topics like streams, filesystems, and algorithms, or apply your string knowledge to build more complex applications.

**Project Ideas**:
- Text processing utility
- CSV parser
- Simple template engine
- Log file analyzer

**Remember**: Strings are fundamental to most applications. The patterns you've learned here will serve you well in all your C++ projects!

---

*This chapter is part of the core C++ curriculum. Master these string concepts before moving to supplemental topics.*