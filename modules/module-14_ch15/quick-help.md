# Chapter 15: Strings - Quick Help Guide

**For students with Python/Java background learning C++ string performance, string_view, and text processing**

---

## 🚨 Most Common Mistakes

### 1. std::string_view Lifetime Issues
```cpp
// DANGEROUS - string_view outlives the source string
std::string_view create_view() {
    std::string temp = "temporary string";
    return temp;  // DANGER: temp destroyed, view becomes invalid!
}

// SAFE - Return by value or use reference to persistent string
std::string create_string() {
    return "persistent string";  // Safe, returns copy
}

// DANGEROUS - string_view from temporary
std::string get_temp_string();
std::string_view view = get_temp_string();  // Temporary destroyed immediately!

// SAFE - Store the string first
std::string str = get_temp_string();
std::string_view view = str;  // Safe, str outlives view
```

### 2. Inefficient String Concatenation
```cpp
// VERY SLOW - Creates many temporary strings
std::string result;
for (int i = 0; i < 1000; ++i) {
    result = result + "item" + std::to_string(i) + " ";  // Creates temporaries!
}

// SLOW - Better but still reallocates
std::string result;
for (int i = 0; i < 1000; ++i) {
    result += "item" + std::to_string(i) + " ";
}

// FAST - Pre-allocate capacity
std::string result;
result.reserve(estimated_final_size);  // Prevents reallocations
for (int i = 0; i < 1000; ++i) {
    result += "item";
    result += std::to_string(i);
    result += " ";
}

// FASTEST - Use ostringstream for complex building
std::ostringstream oss;
for (int i = 0; i < 1000; ++i) {
    oss << "item" << i << " ";
}
std::string result = oss.str();
```

### 3. C-style String Confusion
```cpp
// WRONG - Comparing C-style strings with ==
const char* str1 = "hello";
const char* str2 = "hello";
if (str1 == str2) {  // Compares pointers, not content!
    // This might work by accident due to string pooling, but don't rely on it
}

// RIGHT - Use std::string for content comparison
std::string s1 = "hello";
std::string s2 = "hello";
if (s1 == s2) {  // Compares content correctly
    // Always works
}

// RIGHT - For C-style strings, use strcmp
if (std::strcmp(str1, str2) == 0) {  // Content comparison
    // Correct
}
```

---

## 📋 std::string Quick Reference

### Construction and Assignment
```cpp
#include <string>

// Various construction methods
std::string s1;                          // Empty string
std::string s2("hello");                 // From C-string
std::string s3{"hello"};                 // From C-string (preferred)
std::string s4(5, 'a');                  // "aaaaa" - repeat character
std::string s5(s3, 1, 3);                // Substring: "ell"
std::string s6(s3.begin(), s3.end());    // From iterators
std::string s7 = "hello";                // Copy initialization
std::string s8 = std::move(s7);          // Move (s7 becomes empty)

// Assignment
s1 = "new value";
s1 = s2;
s1 = std::move(s2);
s1.assign("hello");
s1.assign(5, 'x');      // "xxxxx"
```

### Capacity and Size Management
```cpp
std::string str = "hello";

// Size information
str.size()              // Number of characters
str.length()            // Same as size()
str.empty()             // True if size() == 0
str.max_size()          // Maximum possible size

// Capacity management
str.capacity()          // Allocated space
str.reserve(100);       // Ensure capacity >= 100
str.shrink_to_fit();    // Reduce capacity to size
str.resize(10);         // Change size, pad with '\0'
str.resize(10, 'x');    // Change size, pad with 'x'

// Clear
str.clear();            // Make empty (size = 0)
```

### Access and Modification
```cpp
std::string str = "hello";

// Element access
str[0]                  // 'h' - no bounds checking
str.at(0)               // 'h' - throws on out of bounds
str.front()             // 'h' - first character
str.back()              // 'o' - last character
str.data()              // const char* to internal buffer
str.c_str()             // const char* null-terminated

// Modification
str += " world";        // Append string
str += '!';            // Append character
str.append(" more");    // Append string
str.append(3, '!');     // Append "!!!"
str.push_back('?');     // Append single character
str.pop_back();         // Remove last character
str.insert(5, " big");  // Insert at position
str.erase(5, 4);        // Erase 4 chars starting at position 5
str.replace(0, 5, "hi");// Replace substring
```

---

## ⚡ std::string_view Complete Guide

### Basic Usage
```cpp
#include <string_view>

// Creation
std::string_view sv1 = "string literal";  // From literal (safe)
std::string str = "hello world";
std::string_view sv2 = str;               // From string (safe if str outlives sv2)
std::string_view sv3(str.data(), 5);      // First 5 chars: "hello"
std::string_view sv4 = str.substr(6);     // From position 6: "world"

// Unlike std::string, string_view is cheap to copy
void process(std::string_view sv) {  // Pass by value is preferred!
    std::cout << sv << "\n";
}
```

### Substring Operations (Zero-Copy!)
```cpp
std::string text = "The quick brown fox jumps over the lazy dog";
std::string_view full_view = text;

// All these operations are O(1) and don't copy data!
auto word1 = full_view.substr(0, 3);    // "The"
auto word2 = full_view.substr(4, 5);    // "quick"
auto word3 = full_view.substr(10, 5);   // "brown"

// Remove prefix/suffix
full_view.remove_prefix(4);  // Remove "The "
full_view.remove_suffix(4);  // Remove " dog"
// full_view now refers to "quick brown fox jumps over the lazy"
```

### Safe Usage Patterns
```cpp
// PATTERN 1: Function parameters (recommended)
void process_text(std::string_view text) {  // Accepts any string-like type
    // Use text here - caller guarantees lifetime
}

// Call with various types
process_text("literal");           // String literal
process_text(std::string("temp"));// Temporary (safe within function)
process_text(persistent_string);  // Persistent string

// PATTERN 2: Tokenization without copying
std::vector<std::string_view> tokenize(std::string_view text, char delimiter) {
    std::vector<std::string_view> tokens;
    size_t start = 0;
    
    while (true) {
        size_t end = text.find(delimiter, start);
        if (end == std::string_view::npos) {
            tokens.push_back(text.substr(start));
            break;
        }
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    
    return tokens;  // Caller must ensure text outlives returned tokens!
}

// PATTERN 3: Configuration parsing
class Config {
    std::string data_;  // Store the actual data
    std::map<std::string, std::string_view> values_;  // Views into data_
    
public:
    void parse(std::string config_text) {
        data_ = std::move(config_text);  // Take ownership
        // Now create views into data_
        std::string_view view = data_;
        // Parse and populate values_ with views into data_
    }
};
```

---

## 🔧 String Performance Optimization

### Small String Optimization (SSO)
```cpp
// Most implementations optimize strings <= ~23 characters
// These are stored directly in the string object (no heap allocation)

std::string small = "short";        // Likely uses SSO
std::string large = "this is a very long string that exceeds SSO capacity";  // Heap allocated

// You can sometimes detect SSO by comparing addresses
std::string s = "small";
bool uses_sso = (s.data() >= reinterpret_cast<const char*>(&s) && 
                 s.data() < reinterpret_cast<const char*>(&s + 1));
```

### Efficient String Building
```cpp
class StringBuilder {
private:
    std::string buffer_;
    
public:
    explicit StringBuilder(size_t reserve_size = 0) {
        if (reserve_size > 0) buffer_.reserve(reserve_size);
    }
    
    StringBuilder& append(std::string_view text) {
        buffer_.append(text);
        return *this;  // Enable method chaining
    }
    
    StringBuilder& append(char c) {
        buffer_.push_back(c);
        return *this;
    }
    
    StringBuilder& append_line(std::string_view text = "") {
        buffer_.append(text);
        buffer_.push_back('\n');
        return *this;
    }
    
    std::string str() const { return buffer_; }
    std::string_view view() const { return buffer_; }
};

// Usage
StringBuilder builder(1000);  // Pre-allocate
std::string result = builder
    .append("Hello")
    .append(' ')
    .append("World")
    .append_line("!")
    .str();
```

### Memory-Efficient Text Processing
```cpp
// SLOW - Creates many temporary strings
std::string process_slow(const std::string& input) {
    std::string result;
    for (size_t i = 0; i < input.length(); ++i) {
        std::string word = extract_word(input, i);  // Creates copy
        std::string processed = process_word(word);  // Creates copy
        result += processed + " ";                   // More copies
    }
    return result;
}

// FAST - Uses string_view to avoid copies
std::string process_fast(std::string_view input) {
    std::string result;
    result.reserve(input.length() * 2);  // Estimate final size
    
    size_t pos = 0;
    while (pos < input.length()) {
        auto word_view = extract_word_view(input, pos);  // No copy
        process_word_to_buffer(word_view, result);       // Append directly
        result.push_back(' ');
    }
    return result;
}
```

---

## 💡 Text Processing Patterns

### String Searching and Finding
```cpp
std::string text = "The quick brown fox jumps over the lazy dog";

// Find operations
size_t pos = text.find("fox");           // Find substring
size_t pos = text.find("fox", 10);       // Find starting from position 10
size_t pos = text.rfind("the");          // Find last occurrence
size_t pos = text.find_first_of("aeiou"); // Find first vowel
size_t pos = text.find_last_of("aeiou");  // Find last vowel
size_t pos = text.find_first_not_of(" "); // Find first non-space

// Check if found
if (pos != std::string::npos) {
    std::cout << "Found at position " << pos << "\n";
}

// Contains (C++23) or custom implementation
bool contains(std::string_view haystack, std::string_view needle) {
    return haystack.find(needle) != std::string_view::npos;
}
```

### String Comparison
```cpp
std::string s1 = "hello";
std::string s2 = "world";

// Comparison operators
bool equal = (s1 == s2);
bool less = (s1 < s2);           // Lexicographic comparison

// Compare method (returns <0, 0, or >0)
int result = s1.compare(s2);
int result = s1.compare(0, 3, s2, 0, 3);  // Compare substrings

// Case-insensitive comparison (custom)
bool equal_ignore_case(std::string_view a, std::string_view b) {
    return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                     [](char c1, char c2) {
                         return std::tolower(c1) == std::tolower(c2);
                     });
}
```

### String Conversion
```cpp
// String to numbers
std::string str = "12345";
int i = std::stoi(str);
long l = std::stol(str);
float f = std::stof(str);
double d = std::stod(str);

// With error handling
std::string str = "123abc";
size_t pos;
try {
    int value = std::stoi(str, &pos);
    std::cout << "Converted: " << value << ", stopped at position: " << pos << "\n";
} catch (const std::exception& e) {
    std::cout << "Conversion error: " << e.what() << "\n";
}

// Numbers to string
std::string str = std::to_string(42);
std::string str = std::to_string(3.14);
```

---

## 🔍 Regular Expressions

### Basic Regex Usage
```cpp
#include <regex>

std::string text = "Contact: john@example.com or call 555-1234";

// Email pattern
std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

// Check if email exists
if (std::regex_search(text, email_pattern)) {
    std::cout << "Email found!\n";
}

// Extract email
std::smatch match;
if (std::regex_search(text, match, email_pattern)) {
    std::cout << "Email: " << match[0] << "\n";  // match[0] is full match
}

// Replace emails
std::string anonymized = std::regex_replace(text, email_pattern, "[EMAIL]");

// Find all matches
std::sregex_iterator begin(text.begin(), text.end(), email_pattern);
std::sregex_iterator end;
for (auto it = begin; it != end; ++it) {
    std::cout << "Found: " << it->str() << "\n";
}
```

### Common Regex Patterns
```cpp
// Phone number: (123) 456-7890 or 123-456-7890
std::regex phone(R"(\(?(\d{3})\)?[-.\s]?(\d{3})[-.\s]?(\d{4}))");

// URL: http://example.com or https://www.example.com/path
std::regex url(R"(https?://[^\s/$.?#].[^\s]*)");

// Date: MM/DD/YYYY or MM-DD-YYYY
std::regex date(R"((\d{1,2})[/-](\d{1,2})[/-](\d{4}))");

// Capture groups
std::smatch match;
if (std::regex_search(text, match, phone)) {
    std::cout << "Area code: " << match[1] << "\n";    // First capture group
    std::cout << "Exchange: " << match[2] << "\n";     // Second capture group
    std::cout << "Number: " << match[3] << "\n";       // Third capture group
}
```

---

## ⚠️ Performance Considerations

### String Operation Costs
```cpp
// EXPENSIVE operations (avoid in loops)
std::string a, b, c;
std::string result = a + b + c;  // Creates 2 temporary strings

// CHEAP alternatives
std::string result;
result.reserve(a.size() + b.size() + c.size());  // Pre-allocate
result = a;
result += b;
result += c;

// Or use ostringstream for many concatenations
std::ostringstream oss;
oss << a << b << c;
std::string result = oss.str();
```

### When to Use What
```cpp
// Use std::string when:
// - You need to own/modify the string
// - Storing for later use
// - Building/concatenating strings

// Use std::string_view when:
// - Function parameters (read-only)
// - Temporary processing
// - Avoiding copies of substrings
// - Working with string literals

// Use const char* when:
// - Interfacing with C APIs
// - String literals that never change
// - Embedded systems (memory constrained)

// Use std::ostringstream when:
// - Complex formatting
// - Many concatenations
// - Mixing different types (numbers, strings, etc.)
```

---

## 🆘 Emergency Syntax Reference

### String Creation
```cpp
std::string s1;                    // Empty
std::string s2("hello");           // From C-string
std::string s3(10, 'a');          // 10 'a' characters
std::string s4(s2, 1, 3);         // Substring of s2
std::string s5 = "hello";         // Copy initialization
std::string s6 = std::move(s5);   // Move initialization
```

### String_view Creation
```cpp
std::string_view sv1 = "literal";       // From literal
std::string_view sv2 = str;             // From string
std::string_view sv3(ptr, length);      // From pointer + length
std::string_view sv4 = str.substr(5);   // From string method
```

### Common Operations
```cpp
// Size and capacity
str.size(), str.length()           // Number of characters
str.empty()                        // True if empty
str.capacity()                     // Allocated space
str.reserve(n)                     // Ensure capacity

// Access
str[i], str.at(i)                 // Character access
str.front(), str.back()           // First/last character
str.data(), str.c_str()           // C-style string

// Search
str.find("text")                  // Find substring
str.find('c')                     // Find character
str.rfind("text")                 // Find last occurrence
pos != std::string::npos          // Check if found

// Modify
str += "text"                     // Append
str.append("text")                // Append
str.insert(pos, "text")           // Insert
str.erase(pos, len)               // Remove
str.replace(pos, len, "new")      // Replace
```

**Remember**: Choose the right string type for your use case. Use `std::string_view` for parameters, `std::string` for storage, and always be mindful of string lifetimes!