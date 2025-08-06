# Chapter 15: Strings - Quick Help Guide

## Top 5 String Errors (Most Common)

### 1. "std::out_of_range" exception
**Error Message**: `terminate called after throwing an instance of 'std::out_of_range'`

**What it means**: Accessing string with invalid index using `.at()`.

**Bad**:
```cpp
std::string text = "Hello";
char c = text.at(10);  // Throws exception - index 10 doesn't exist
```

**Fixed**:
```cpp
std::string text = "Hello";
if (10 < text.size()) {
    char c = text.at(10);
} else {
    std::cout << "Index out of range" << std::endl;
}

// Or use bounds-safe access
char c = (10 < text.size()) ? text[10] : '\0';
```

**Python/Java Note**: Unlike Python (raises IndexError) or Java (throws StringIndexOutOfBoundsException), C++ `.at()` throws `std::out_of_range`.

---

### 2. Undefined behavior with operator[]
**Error Message**: No error message - silent corruption or crash

**What it means**: Using `[]` with invalid index doesn't throw - just corrupt memory.

**Bad**:
```cpp
std::string text = "Hello";
char c = text[100];     // Undefined behavior - could be any value
text[100] = 'X';        // Undefined behavior - memory corruption!
```

**Fixed**:
```cpp
std::string text = "Hello";
// Always check bounds first
if (100 < text.size()) {
    char c = text[100];
}

// Or use .at() for automatic bounds checking
try {
    char c = text.at(100);
} catch (const std::out_of_range& e) {
    std::cout << "Invalid index: " << e.what() << std::endl;
}
```

---

### 3. "std::invalid_argument" in string conversions
**Error Message**: `terminate called after throwing an instance of 'std::invalid_argument'`

**What it means**: Failed to convert string to number.

**Bad**:
```cpp
std::string text = "not_a_number";
int value = std::stoi(text);  // Throws std::invalid_argument
```

**Fixed**:
```cpp
std::string text = "not_a_number";
try {
    int value = std::stoi(text);
    std::cout << "Value: " << value << std::endl;
} catch (const std::invalid_argument& e) {
    std::cout << "Cannot convert '" << text << "' to integer" << std::endl;
} catch (const std::out_of_range& e) {
    std::cout << "Number too large: " << e.what() << std::endl;
}
```

---

### 4. String comparison confusion
**Error Message**: No error - wrong logic results

**What it means**: Mixing up string comparison methods or case sensitivity.

**Bad**:
```cpp
std::string s1 = "Hello";
std::string s2 = "hello";

if (s1 == s2) {  // False - case sensitive!
    std::cout << "Same" << std::endl;
}

// Wrong three-way comparison
if (s1.compare(s2) == true) {  // Wrong! compare() returns int, not bool
    std::cout << "Same" << std::endl;
}
```

**Fixed**:
```cpp
std::string s1 = "Hello";
std::string s2 = "hello";

// Case-sensitive comparison
if (s1 == s2) {
    std::cout << "Exactly same" << std::endl;
}

// Case-insensitive comparison
std::string s1_lower = s1;
std::string s2_lower = s2;
std::transform(s1_lower.begin(), s1_lower.end(), s1_lower.begin(), ::tolower);
std::transform(s2_lower.begin(), s2_lower.end(), s2_lower.begin(), ::tolower);

if (s1_lower == s2_lower) {
    std::cout << "Same (ignoring case)" << std::endl;
}

// Correct three-way comparison
int result = s1.compare(s2);
if (result == 0) {
    std::cout << "Equal" << std::endl;
} else if (result < 0) {
    std::cout << "s1 comes before s2" << std::endl;
} else {
    std::cout << "s1 comes after s2" << std::endl;
}
```

---

### 5. Dangling string_view references
**Error Message**: Crashes or garbage output - hard to debug

**What it means**: `string_view` pointing to destroyed string memory.

**Bad**:
```cpp
std::string_view get_temp_string() {
    std::string temp = "temporary";
    return std::string_view(temp);  // DANGER! temp destroyed when function ends
}

int main() {
    auto view = get_temp_string();
    std::cout << view << std::endl;  // Undefined behavior - temp is gone!
    return 0;
}
```

**Fixed**:
```cpp
// Option 1: Return std::string (owns the data)
std::string get_temp_string() {
    return std::string("temporary");
}

// Option 2: Use string_view with static/global data
std::string_view get_static_string() {
    static const std::string static_str = "temporary";
    return std::string_view(static_str);
}

// Option 3: Pass string_view as parameter (most common)
void process_string(std::string_view sv) {
    std::cout << sv << std::endl;  // Safe - caller owns the data
}

int main() {
    std::string text = "Hello";
    process_string(text);      // Safe
    process_string("World");   // Safe - string literal has static duration
    return 0;
}
```

---

## Debugging Tips

### Visual Debugging String Issues

```cpp
#include <iostream>
#include <string>

void debug_string(const std::string& s, const std::string& name) {
    std::cout << "String '" << name << "':" << std::endl;
    std::cout << "  Value: '" << s << "'" << std::endl;
    std::cout << "  Size: " << s.size() << std::endl;
    std::cout << "  Capacity: " << s.capacity() << std::endl;
    std::cout << "  Empty: " << (s.empty() ? "Yes" : "No") << std::endl;
    
    // Show each character with index
    for (size_t i = 0; i < s.size(); ++i) {
        std::cout << "  [" << i << "] = '" << s[i] << "' (ASCII: " << static_cast<int>(s[i]) << ")" << std::endl;
    }
    std::cout << std::endl;
}

// Usage
std::string test = "Hello\n";  // Has newline
debug_string(test, "test");
```

### Memory Debugging

```cpp
// Check for memory issues with address sanitizer
// Compile with: g++ -fsanitize=address -g program.cpp

#include <string>
#include <iostream>

void test_string_memory() {
    std::string s = "test";
    
    // This will be caught by address sanitizer if there's an issue
    for (size_t i = 0; i <= s.size(); ++i) {  // Note: <= will access one past end
        std::cout << "s[" << i << "] = ";
        if (i < s.size()) {
            std::cout << s[i] << std::endl;
        } else {
            std::cout << "past end!" << std::endl;
        }
    }
}
```

---

## Performance Tips

### String Concatenation

```cpp
// ❌ Slow: Creates many temporary objects
std::string result;
for (int i = 0; i < 1000; ++i) {
    result = result + "data";  // New string created each time
}

// ✅ Fast: Reserve space and use append
std::string result;
result.reserve(4000);  // Pre-allocate space
for (int i = 0; i < 1000; ++i) {
    result += "data";  // Or result.append("data");
}

// ✅ Fast: Use stringstream for many concatenations
std::ostringstream oss;
for (int i = 0; i < 1000; ++i) {
    oss << "data";
}
std::string result = oss.str();
```

### Function Parameters

```cpp
// ❌ Inefficient: Copies string
void process_text(std::string text) {
    // ...
}

// ✅ Better: Read-only reference
void process_text(const std::string& text) {
    // ...
}

// ✅ Best: String view for read-only (C++17)
void process_text(std::string_view text) {
    // Works with string, string literals, substrings
}
```

---

## Common Gotchas

### 1. substr() uses length, not end position

```cpp
std::string text = "Hello World";

// Python-style thinking (WRONG in C++)
std::string sub = text.substr(0, 5);  // This gets "Hello" (5 characters)

// What you might expect from Python text[0:5]
// In C++: substr(start_pos, length)
// In Python: text[start:end]
```

### 2. find() returns std::string::npos when not found

```cpp
std::string text = "Hello World";
size_t pos = text.find("xyz");

// ❌ Wrong check
if (pos) {  // This is wrong! npos is a large number, not 0
    std::cout << "Found" << std::endl;
}

// ✅ Correct check
if (pos != std::string::npos) {
    std::cout << "Found at position " << pos << std::endl;
}
```

### 3. Character encoding assumptions

```cpp
std::string utf8_text = u8"Hello 世界";

// ❌ Wrong: This counts bytes, not characters
std::cout << "Characters: " << utf8_text.size() << std::endl;  // Might be 11, not 8

// ✅ For byte counting, be explicit
std::cout << "Bytes: " << utf8_text.size() << std::endl;

// For actual character counting, use specialized library or manual parsing
```

---

## Quick Reference

### Essential String Operations

```cpp
// Creation
std::string s1;                    // Empty
std::string s2("hello");           // From literal
std::string s3 = s2;               // Copy
std::string s4(10, 'A');           // "AAAAAAAAAA"

// Access
char c = s2[0];                    // Unchecked
char c = s2.at(0);                 // Bounds checked
char& front = s2.front();          // First character
char& back = s2.back();            // Last character

// Information
size_t len = s2.size();            // Length
bool empty = s2.empty();           // Is empty?
size_t cap = s2.capacity();        // Capacity

// Modification
s2 += "world";                     // Append
s2.append(" test");                // Append
s2.insert(5, " ");                 // Insert at position
s2.erase(5, 1);                    // Erase 1 char at pos 5
s2.replace(0, 5, "hi");            // Replace substring
s2.clear();                        // Empty string

// Search
size_t pos = s2.find("lo");        // Find substring
size_t pos = s2.rfind("l");        // Find from end
size_t pos = s2.find_first_of("aeiou");  // Find any vowel

// Substring
std::string sub = s2.substr(1, 3); // From pos 1, length 3

// Conversion
int num = std::stoi("123");        // String to int
std::string str = std::to_string(123);  // Int to string
```

---

## When to Use Each String Type

| Type | Use When | Example |
|------|----------|---------|
| `std::string` | You own the data, need to modify | `std::string name = "Alice";` |
| `std::string_view` | Read-only parameter, no ownership | `void print(std::string_view sv)` |
| `const char*` | Interfacing with C APIs | `printf("%s\n", str.c_str());` |
| `char[]` | Fixed-size buffer, C-style code | `char buffer[256];` |

Remember: When in doubt, use `std::string` for ownership and `std::string_view` for parameters!