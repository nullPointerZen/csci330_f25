# Chapter 15: Strings - Complete Guide

## 📖 Learning Sequence (IMPORTANT!)

**🔄 How This Chapter Works:**
1. **📚 FIRST**: Read Textbook Chapter 15 "Strings" (2-3 hours)
2. **🔍 SECOND**: Work through these lecture notes for hands-on practice (3-4 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 15 "Strings" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Master** std::string operations and memory management
2. **Apply** std::string_view for performance optimization
3. **Implement** text processing algorithms and pattern matching
4. **Use** regular expressions for complex text manipulation
5. **Optimize** string operations for performance-critical code
6. **Debug** string-related issues and memory problems

**⏱️ Time Budget:**
- **📚 Textbook Reading: 2-3 hours** (Chapter 15: "Strings" - REQUIRED FIRST)
- **💻 Hands-on Work: 4-5 hours** (course materials + assignments + debugging)
- **📖 Note: Reading time is separate and must be completed BEFORE hands-on work**

## 🧠 Key Concepts Summary

### **1. std::string Fundamentals**
- **Dynamic sizing**: Automatic memory management
- **Reference counting**: Copy-on-write in some implementations
- **Small string optimization**: Stack storage for short strings
- **Capacity management**: reserve(), shrink_to_fit()

### **2. std::string_view (C++17)**
- **Non-owning reference**: View into existing string data
- **Zero-copy**: No memory allocation for substrings
- **Performance**: Avoid unnecessary copies in function parameters
- **Safety**: Must ensure underlying string outlives the view

### **3. String Operations**
- **Construction**: Various initialization methods
- **Access**: operator[], at(), front(), back(), data()
- **Modification**: append(), insert(), erase(), replace()
- **Searching**: find(), rfind(), find_first_of()

### **4. Text Processing**
- **Parsing**: Tokenization and splitting
- **Formatting**: Stream-based and printf-style
- **Comparison**: Lexicographic ordering and case handling
- **Conversion**: To/from numeric types

### **5. Regular Expressions**
- **Pattern matching**: std::regex for complex patterns
- **Search operations**: regex_search(), regex_match()
- **Replacement**: regex_replace() for text transformation
- **Iteration**: sregex_iterator for multiple matches

## 💻 Performance Optimization

### **String vs. String_view Guidelines**
```cpp
// Prefer string_view for function parameters (read-only)
void process_text(std::string_view text) {  // No copy
    // Process text without modifying
}

// Use string for ownership and modification
std::string transform_text(std::string_view input) {
    std::string result(input);  // Copy when needed
    // Modify result
    return result;  // Move optimized
}
```

### **Memory Management**
```cpp
// Reserve capacity when size is known
std::string build_large_string() {
    std::string result;
    result.reserve(expected_size);  // Avoid reallocations
    
    for (const auto& part : parts) {
        result += part;  // Efficient with reserved capacity
    }
    return result;
}
```

## 💻 Text Processing Patterns

### **String Parsing**
```cpp
// Tokenization
std::vector<std::string_view> split(std::string_view text, char delimiter) {
    std::vector<std::string_view> tokens;
    size_t start = 0;
    size_t end = text.find(delimiter);
    
    while (end != std::string_view::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
        end = text.find(delimiter, start);
    }
    tokens.push_back(text.substr(start));
    return tokens;
}
```

### **Regular Expressions**
```cpp
// Email validation
std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
bool is_valid_email = std::regex_match(email, email_pattern);

// Text replacement
std::string text = "The year 2023 was great!";
std::regex year_pattern(R"(\d{4})");
std::string result = std::regex_replace(text, year_pattern, "YYYY");
```

## 🔧 Common Patterns and Pitfalls

### **Best Practices**
- Use std::string_view for function parameters (read-only)
- Reserve string capacity when building large strings
- Prefer string algorithms over manual character iteration
- Use raw string literals for complex patterns: R"(...)"

### **Common Mistakes**
- string_view dangling references to temporary strings
- Inefficient string concatenation without reserve()
- Not handling Unicode properly in text processing
- Expensive regex compilation in loops

### **Performance Considerations**
- string_view has minimal overhead
- String concatenation can be expensive without planning
- Regular expressions have compilation cost
- Consider string interning for frequently used strings

### **Memory Safety**
```cpp
// Dangerous: string_view outliving source
std::string_view get_view() {
    std::string temp = "temporary";
    return temp;  // DANGER: temp destroyed, view invalid
}

// Safe: ensure string lifetime
class TextProcessor {
    std::string text_;
    std::string_view view_;
public:
    void set_text(std::string new_text) {
        text_ = std::move(new_text);
        view_ = text_;  // Safe: text_ outlives view_
    }
};
```

## 🔧 Advanced String Techniques

### **Unicode Handling**
- UTF-8 encoded strings in std::string
- Character vs. byte counting considerations  
- Locale-aware operations for internationalization

### **String Formatting**
```cpp
// Stream-based formatting
std::ostringstream oss;
oss << "Value: " << std::fixed << std::setprecision(2) << value;
std::string result = oss.str();

// C-style formatting (when needed)
char buffer[100];
std::sprintf(buffer, "Format: %.2f", value);
```

### **Custom String Classes**
- When std::string isn't sufficient
- Copy-on-write implementations
- Small string optimization techniques

## 📝 Before Next Chapter

Ensure you understand:
- When to use std::string vs. std::string_view
- String performance optimization techniques  
- Regular expression usage patterns
- Text processing algorithm design

**Course Completion**: This completes the core C++ curriculum. Next steps involve applying these concepts in the semester project and advanced topics.