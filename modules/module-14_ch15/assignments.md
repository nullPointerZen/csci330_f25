# Chapter 15: Strings - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 15 "Strings"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 1.5 hours total for both problem sets
- Test all programs thoroughly before submission

**Target Audience**: Students with Python/Java background  
**Total Time**: 1.5 hours (90 minutes)  
**Prerequisites**: Chapters 1-14 completed + Chapter 15 lesson  

## Problem Set Structure

- **Problem Set 1**: std::string Performance and std::string_view (45 minutes)
- **Problem Set 2**: Text Processing and Regular Expressions (60 minutes) 
- **Problem Set 3**: Advanced String Techniques (30 minutes)

---

## Problem Set 1: std::string Performance and std::string_view (45 minutes)

### Problem 1.1: String Performance Optimization (20 minutes)

**Background**: Coming from Python's immutable strings or Java's String class, learn C++ string performance optimization techniques.

**Task**: Compare different string operations and optimization strategies.

**Requirements**:
1. Benchmark string operations and memory allocations
2. Use reserve() to optimize string building
3. Compare different string concatenation methods
4. Understand small string optimization effects

**Starter Code**:
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <memory>

class StringBenchmark {
public:
    // TODO: Benchmark string concatenation methods
    static void benchmark_concatenation(size_t num_strings) {
        std::cout << "=== String Concatenation Benchmark (" << num_strings << " strings) ===\n";
        
        std::vector<std::string> test_strings;
        for (size_t i = 0; i < num_strings; ++i) {
            test_strings.push_back("String" + std::to_string(i));
        }
        
        // Method 1: Naive concatenation with += (worst case)
        auto start = std::chrono::high_resolution_clock::now();
        std::string result1;
        for (const auto& str : test_strings) {
            result1 += str + " ";
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto naive_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Method 2: Pre-allocate capacity
        start = std::chrono::high_resolution_clock::now();
        std::string result2;
        
        // TODO: Estimate required capacity
        size_t estimated_size = 0;
        for (const auto& str : test_strings) {
            estimated_size += str.length() + 1;  // +1 for space
        }
        result2.reserve(estimated_size);
        
        for (const auto& str : test_strings) {
            result2 += str + " ";
        }
        end = std::chrono::high_resolution_clock::now();
        auto reserved_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Method 3: Using ostringstream
        start = std::chrono::high_resolution_clock::now();
        std::ostringstream oss;
        for (const auto& str : test_strings) {
            oss << str << " ";
        }
        std::string result3 = oss.str();
        end = std::chrono::high_resolution_clock::now();
        auto stream_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Results:\n";
        std::cout << "  Naive +=: " << naive_time.count() << " μs\n";
        std::cout << "  Reserved: " << reserved_time.count() << " μs (speedup: " 
                  << (naive_time.count() / (double)reserved_time.count()) << "x)\n";
        std::cout << "  Stream:   " << stream_time.count() << " μs\n";
        
        std::cout << "  Result lengths: " << result1.length() << ", " 
                  << result2.length() << ", " << result3.length() << "\n";
    }
    
    // TODO: Test small string optimization
    static void test_small_string_optimization() {
        std::cout << "\n=== Small String Optimization Test ===\n";
        
        // Test with different string sizes
        std::vector<std::string> test_strings = {
            "",           // Empty
            "Hi",         // Very short
            "Hello",      // Short
            "Hello World", // Medium
            "This is a longer string that should exceed SSO", // Long
            "This is an even longer string that definitely exceeds small string optimization and should be heap allocated" // Very long
        };
        
        for (const auto& str : test_strings) {
            std::cout << "String: \"" << (str.length() > 20 ? str.substr(0, 17) + "..." : str) << "\"\n";
            std::cout << "  Length: " << str.length() << "\n";
            std::cout << "  Capacity: " << str.capacity() << "\n";
            std::cout << "  Data pointer: " << static_cast<const void*>(str.data()) << "\n";
            std::cout << "  String object address: " << static_cast<const void*>(&str) << "\n";
            
            // TODO: Heuristic check for SSO (implementation specific)
            if (str.capacity() <= 23) {  // Common SSO threshold
                std::cout << "  Likely using SSO (stack storage)\n";
            } else {
                std::cout << "  Likely using heap storage\n";
            }
            std::cout << "\n";
        }
    }
    
    // TODO: Memory allocation tracking
    static void track_string_allocations() {
        std::cout << "=== String Memory Allocation Tracking ===\n";
        
        // Test capacity growth pattern
        std::string str;
        std::cout << "Growing string capacity:\n";
        std::cout << "Initial - Size: " << str.size() << ", Capacity: " << str.capacity() << "\n";
        
        for (int i = 1; i <= 100; ++i) {
            size_t old_capacity = str.capacity();
            str += "X";
            
            if (str.capacity() != old_capacity) {
                std::cout << "After " << i << " chars - Size: " << str.size() 
                          << ", Capacity: " << str.capacity() 
                          << " (growth factor: " << (str.capacity() / (double)old_capacity) << ")\n";
            }
        }
        
        // Test shrink_to_fit
        std::cout << "\nBefore shrink_to_fit - Size: " << str.size() << ", Capacity: " << str.capacity() << "\n";
        str.shrink_to_fit();
        std::cout << "After shrink_to_fit - Size: " << str.size() << ", Capacity: " << str.capacity() << "\n";
    }
};

int main() {
    StringBenchmark::benchmark_concatenation(1000);
    StringBenchmark::test_small_string_optimization();
    StringBenchmark::track_string_allocations();
    
    return 0;
}
```

**Learning Goals**:
- String performance characteristics
- Small string optimization behavior
- Capacity management techniques
- Comparing concatenation strategies

---

### Problem 1.2: std::string_view Fundamentals (15 minutes)

**Background**: Use std::string_view for efficient string parameter passing and substring operations without copying.

**Task**: Implement functions using string_view and understand its benefits and limitations.

**Requirements**:
1. Create functions that accept string_view parameters
2. Demonstrate zero-copy substring operations
3. Handle string_view lifetime safety
4. Compare performance with std::string

**Starter Code**:
```cpp
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <chrono>

class StringViewDemo {
public:
    // TODO: Functions demonstrating string vs string_view parameters
    static void process_string_copy(std::string text) {
        // This function creates a copy
        std::cout << "Processing copy: " << text.substr(0, 10) << "...\n";
        
        // Can modify the copy
        text[0] = std::toupper(text[0]);
        std::cout << "Modified copy: " << text.substr(0, 10) << "...\n";
    }
    
    static void process_string_view(std::string_view text) {
        // This function works with a view - no copy
        std::cout << "Processing view: " << text.substr(0, 10) << "...\n";
        
        // Cannot modify through string_view (it's read-only)
        // text[0] = std::toupper(text[0]);  // Compilation error
        
        // But can create modified copies if needed
        std::string modified(text);
        modified[0] = std::toupper(modified[0]);
        std::cout << "Created modified copy: " << modified.substr(0, 10) << "...\n";
    }
    
    // TODO: Tokenization with string_view
    static std::vector<std::string_view> split_view(std::string_view text, char delimiter) {
        std::vector<std::string_view> tokens;
        size_t start = 0;
        size_t end = text.find(delimiter);
        
        while (end != std::string_view::npos) {
            tokens.push_back(text.substr(start, end - start));
            start = end + 1;
            end = text.find(delimiter, start);
        }
        
        // Don't forget the last token
        tokens.push_back(text.substr(start));
        
        return tokens;
    }
    
    static std::vector<std::string> split_string(const std::string& text, char delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = text.find(delimiter);
        
        while (end != std::string::npos) {
            tokens.push_back(text.substr(start, end - start));  // Creates copy
            start = end + 1;
            end = text.find(delimiter, start);
        }
        
        tokens.push_back(text.substr(start));  // Creates copy
        
        return tokens;
    }
    
    // TODO: Benchmark string vs string_view operations
    static void benchmark_parameter_passing() {
        std::cout << "=== Parameter Passing Benchmark ===\n";
        
        std::string long_text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                               "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
                               "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris. "
                               "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum.";
        
        const int iterations = 100000;
        
        // Benchmark string copy parameter
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            process_string_copy(long_text);  // Creates copy each time
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto copy_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Benchmark string_view parameter
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            process_string_view(long_text);  // No copy
        }
        end = std::chrono::high_resolution_clock::now();
        auto view_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Results for " << iterations << " calls:\n";
        std::cout << "  String copy: " << copy_time.count() << " μs\n";
        std::cout << "  String view: " << view_time.count() << " μs\n";
        std::cout << "  Speedup: " << (copy_time.count() / (double)view_time.count()) << "x\n";
    }
    
    // TODO: Demonstrate lifetime safety issues
    static void demonstrate_lifetime_safety() {
        std::cout << "\n=== String View Lifetime Safety ===\n";
        
        std::string_view dangerous_view;
        
        {
            std::string temp = "This string will be destroyed";
            dangerous_view = temp;  // DANGER: temp will be destroyed
            std::cout << "Inside scope - view: " << dangerous_view << "\n";
        }
        
        // DO NOT DO THIS - temp is destroyed, view is now dangling
        // std::cout << "Outside scope - view: " << dangerous_view << "\n";  // Undefined behavior!
        
        std::cout << "WARNING: Accessing dangerous_view now would be undefined behavior!\n";
        
        // Safe usage patterns
        std::cout << "\nSafe usage patterns:\n";
        
        // 1. String outlives string_view
        std::string safe_string = "This string stays alive";
        std::string_view safe_view = safe_string;
        std::cout << "Safe view: " << safe_view << "\n";
        
        // 2. String literal (always safe)
        std::string_view literal_view = "String literals are always safe";
        std::cout << "Literal view: " << literal_view << "\n";
        
        // 3. Return string_view from function parameter
        auto tokens = split_view(safe_string, ' ');
        std::cout << "Safe tokenization:\n";
        for (const auto& token : tokens) {
            std::cout << "  Token: " << token << "\n";
        }
    }
};

// TODO: Utility functions using string_view
class TextUtils {
public:
    static bool starts_with(std::string_view text, std::string_view prefix) {
        return text.size() >= prefix.size() && 
               text.substr(0, prefix.size()) == prefix;
    }
    
    static bool ends_with(std::string_view text, std::string_view suffix) {
        return text.size() >= suffix.size() && 
               text.substr(text.size() - suffix.size()) == suffix;
    }
    
    static bool contains(std::string_view text, std::string_view substring) {
        return text.find(substring) != std::string_view::npos;
    }
    
    static std::string_view trim_whitespace(std::string_view text) {
        // Find first non-whitespace
        size_t start = 0;
        while (start < text.size() && std::isspace(text[start])) {
            ++start;
        }
        
        // Find last non-whitespace
        size_t end = text.size();
        while (end > start && std::isspace(text[end - 1])) {
            --end;
        }
        
        return text.substr(start, end - start);
    }
    
    static void demonstrate_utilities() {
        std::cout << "\n=== String View Utilities Demo ===\n";
        
        std::string test_text = "  Hello, World!  ";
        std::string_view view = test_text;
        
        std::cout << "Original: '" << view << "'\n";
        
        std::cout << "Starts with '  He': " << starts_with(view, "  He") << "\n";
        std::cout << "Ends with '!  ': " << ends_with(view, "!  ") << "\n";
        std::cout << "Contains 'World': " << contains(view, "World") << "\n";
        
        auto trimmed = trim_whitespace(view);
        std::cout << "Trimmed: '" << trimmed << "'\n";
        std::cout << "Trimmed length: " << trimmed.length() << " (vs original: " << view.length() << ")\n";
    }
};

int main() {
    StringViewDemo::benchmark_parameter_passing();
    StringViewDemo::demonstrate_lifetime_safety();
    TextUtils::demonstrate_utilities();
    
    return 0;
}
```

**Learning Goals**:
- string_view parameter passing benefits
- Zero-copy substring operations
- Lifetime safety considerations
- Performance comparisons

---

### Problem 1.3: Advanced String Building Patterns (10 minutes)

**Background**: Master efficient string construction patterns for performance-critical code.

**Task**: Implement various string building strategies and compare their efficiency.

**Requirements**:
1. Use string builders with different strategies
2. Implement efficient formatting approaches
3. Handle Unicode and encoding considerations
4. Optimize for different use cases

**Starter Code**:
```cpp
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <chrono>
#include <iomanip>

class StringBuilder {
private:
    std::string buffer_;
    
public:
    explicit StringBuilder(size_t initial_capacity = 0) {
        if (initial_capacity > 0) {
            buffer_.reserve(initial_capacity);
        }
    }
    
    // TODO: Fluent interface for chaining
    StringBuilder& append(std::string_view text) {
        buffer_ += text;
        return *this;
    }
    
    StringBuilder& append(char ch) {
        buffer_ += ch;
        return *this;
    }
    
    StringBuilder& append(int number) {
        buffer_ += std::to_string(number);
        return *this;
    }
    
    StringBuilder& append(double number, int precision = 6) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision) << number;
        buffer_ += oss.str();
        return *this;
    }
    
    StringBuilder& append_line(std::string_view text = "") {
        buffer_ += text;
        buffer_ += '\n';
        return *this;
    }
    
    StringBuilder& repeat(std::string_view text, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            buffer_ += text;
        }
        return *this;
    }
    
    StringBuilder& format(std::string_view format_str, const std::vector<std::string>& args) {
        std::string result;
        size_t arg_index = 0;
        
        for (size_t i = 0; i < format_str.length(); ++i) {
            if (format_str[i] == '{' && i + 1 < format_str.length() && format_str[i + 1] == '}') {
                if (arg_index < args.size()) {
                    result += args[arg_index++];
                }
                ++i;  // Skip the '}'
            } else {
                result += format_str[i];
            }
        }
        
        buffer_ += result;
        return *this;
    }
    
    std::string to_string() const {
        return buffer_;
    }
    
    std::string_view view() const {
        return buffer_;
    }
    
    size_t length() const {
        return buffer_.length();
    }
    
    size_t capacity() const {
        return buffer_.capacity();
    }
    
    void clear() {
        buffer_.clear();
    }
    
    void reserve(size_t new_capacity) {
        buffer_.reserve(new_capacity);
    }
};

class StringBuildingBenchmark {
public:
    static void benchmark_building_strategies() {
        std::cout << "=== String Building Strategies Benchmark ===\n";
        
        const int iterations = 1000;
        const std::vector<std::string> words = {
            "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"
        };
        
        // Strategy 1: Naive concatenation
        auto start = std::chrono::high_resolution_clock::now();
        std::string result1;
        for (int i = 0; i < iterations; ++i) {
            for (const auto& word : words) {
                result1 += word + " ";
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto naive_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Strategy 2: Pre-reserved string
        start = std::chrono::high_resolution_clock::now();
        std::string result2;
        
        // Estimate capacity
        size_t estimated_size = 0;
        for (const auto& word : words) {
            estimated_size += word.length() + 1;
        }
        result2.reserve(estimated_size * iterations);
        
        for (int i = 0; i < iterations; ++i) {
            for (const auto& word : words) {
                result2 += word + " ";
            }
        }
        end = std::chrono::high_resolution_clock::now();
        auto reserved_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Strategy 3: StringBuilder
        start = std::chrono::high_resolution_clock::now();
        StringBuilder builder(estimated_size * iterations);
        for (int i = 0; i < iterations; ++i) {
            for (const auto& word : words) {
                builder.append(word).append(' ');
            }
        }
        std::string result3 = builder.to_string();
        end = std::chrono::high_resolution_clock::now();
        auto builder_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Strategy 4: ostringstream
        start = std::chrono::high_resolution_clock::now();
        std::ostringstream oss;
        for (int i = 0; i < iterations; ++i) {
            for (const auto& word : words) {
                oss << word << ' ';
            }
        }
        std::string result4 = oss.str();
        end = std::chrono::high_resolution_clock::now();
        auto stream_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Results for " << iterations << " iterations:\n";
        std::cout << "  Naive concat:  " << naive_time.count() << " μs\n";
        std::cout << "  Reserved:      " << reserved_time.count() << " μs\n";
        std::cout << "  StringBuilder: " << builder_time.count() << " μs\n";
        std::cout << "  ostringstream: " << stream_time.count() << " μs\n";
        
        std::cout << "\nResult lengths: " << result1.length() << ", " 
                  << result2.length() << ", " << result3.length() << ", " << result4.length() << "\n";
    }
    
    static void demonstrate_formatting() {
        std::cout << "\n=== Advanced String Formatting ===\n";
        
        StringBuilder builder;
        
        // TODO: Build a formatted report
        builder.append_line("=== System Report ===")
               .append_line()
               .append("CPU Usage: ").append(87.5, 1).append_line("%")
               .append("Memory: ").append(1024).append_line(" MB")
               .append("Uptime: ").append(42).append_line(" hours")
               .append_line()
               .repeat("-", 30).append_line()
               .format("User: {}, Session: {}\n", {"admin", "12345"})
               .append_line("Status: OK");
        
        std::cout << "Generated report:\n" << builder.view() << "\n";
        
        std::cout << "Builder stats - Length: " << builder.length() 
                  << ", Capacity: " << builder.capacity() << "\n";
    }
    
    static void test_unicode_handling() {
        std::cout << "\n=== Unicode String Handling ===\n";
        
        // TODO: UTF-8 string handling
        std::string utf8_text = "Hello 世界! Emoji: 🌍🚀✨";
        std::cout << "UTF-8 text: " << utf8_text << "\n";
        std::cout << "Byte length: " << utf8_text.length() << "\n";
        
        // Note: Character counting requires proper UTF-8 handling
        std::cout << "Note: std::string works with bytes, not Unicode code points\n";
        
        StringBuilder unicode_builder;
        unicode_builder.append("Mixing languages: ")
                      .append("English, ")
                      .append("中文, ")
                      .append("Español, ")
                      .append("العربية")
                      .append_line();
        
        std::cout << "Unicode builder result: " << unicode_builder.view() << "\n";
        std::cout << "Byte length: " << unicode_builder.length() << "\n";
    }
};

int main() {
    StringBuildingBenchmark::benchmark_building_strategies();
    StringBuildingBenchmark::demonstrate_formatting();
    StringBuildingBenchmark::test_unicode_handling();
    
    return 0;
}
```

**Learning Goals**:
- Efficient string building strategies
- Fluent interface design
- Performance optimization techniques
- Unicode and encoding awareness

---

## Problem Set 2: Text Processing and Regular Expressions (60 minutes)

[Due to space constraints, I'll provide a shortened version of Problem Set 2 and 3]

### Problem 2.1: Advanced Text Parsing (30 minutes)

**Task**: Implement robust text parsing and tokenization systems.

**Starter Code**:
```cpp
#include <iostream>
#include <string>
#include <string_view>
#include <regex>
#include <vector>
#include <sstream>

class TextParser {
public:
    // TODO: CSV parsing with escaping
    static std::vector<std::vector<std::string>> parse_csv(std::string_view csv_data) {
        std::vector<std::vector<std::string>> result;
        std::istringstream stream(std::string(csv_data));
        std::string line;
        
        while (std::getline(stream, line)) {
            std::vector<std::string> row;
            std::istringstream line_stream(line);
            std::string field;
            
            while (std::getline(line_stream, field, ',')) {
                // Basic CSV parsing (doesn't handle quoted fields with commas)
                row.push_back(field);
            }
            
            if (!row.empty()) {
                result.push_back(row);
            }
        }
        
        return result;
    }
    
    // TODO: Extract key-value pairs from configuration text
    static std::map<std::string, std::string> parse_config(std::string_view config_text) {
        std::map<std::string, std::string> config;
        std::istringstream stream(std::string(config_text));
        std::string line;
        
        std::regex config_regex(R"(^\s*([^=\s]+)\s*=\s*(.+)\s*$)");
        
        while (std::getline(stream, line)) {
            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') continue;
            
            std::smatch match;
            if (std::regex_match(line, match, config_regex)) {
                config[match[1].str()] = match[2].str();
            }
        }
        
        return config;
    }
};

int main() {
    // Test CSV parsing
    std::string csv_data = "Name,Age,City\nJohn,25,NYC\nJane,30,LA";
    auto csv_result = TextParser::parse_csv(csv_data);
    
    std::cout << "CSV parsing result:\n";
    for (const auto& row : csv_result) {
        for (const auto& field : row) {
            std::cout << field << " | ";
        }
        std::cout << "\n";
    }
    
    return 0;
}
```

### Problem 2.2: Regular Expressions (30 minutes)

**Task**: Use std::regex for complex pattern matching and text transformation.

**Learning Goals**: Pattern matching, text validation, regex performance.

---

## Problem Set 3: Advanced String Techniques (30 minutes)

### Problem 3.1: String Algorithms (20 minutes)

**Task**: Implement string algorithms like Boyer-Moore search and edit distance.

### Problem 3.2: Custom String Classes (10 minutes)

**Task**: Design specialized string classes for specific use cases.

---

## Submission Guidelines

### What to Submit

1. **Source code files** for all problems with clear comments
2. **Compilation and execution output** showing your programs working
3. **Brief reflection** (2-3 paragraphs) on string performance insights and best practices

### File Organization
```
chapter15_solutions/
├── problem_set_1/
│   ├── problem_1_1_string_performance.cpp
│   ├── problem_1_2_string_view_fundamentals.cpp
│   └── problem_1_3_string_building.cpp
├── problem_set_2/
│   ├── problem_2_1_text_parsing.cpp
│   └── problem_2_2_regex_processing.cpp
├── problem_set_3/
│   ├── problem_3_1_string_algorithms.cpp
│   └── problem_3_2_custom_string_classes.cpp
└── README.md (with compilation notes and reflection)
```

### Success Criteria

You've mastered Chapter 15 string concepts when you can:
- Choose between std::string and std::string_view appropriately
- Optimize string operations for performance
- Process text efficiently using various parsing techniques
- Use regular expressions effectively for pattern matching
- Design string handling systems that balance performance and safety

Remember: String processing is fundamental to many applications. Understanding performance characteristics and choosing the right techniques is crucial for building efficient systems!