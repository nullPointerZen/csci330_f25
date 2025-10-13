# Chapter 15: Strings - Practice Problems

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 15 "Strings"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 2.25 hours total for all three problem sets
- Test all programs thoroughly before submission

---

## Problem Set 1: String Fundamentals (45 minutes)

### Problem 1.1: String Creation and Basic Operations (15 minutes)

**Objective**: Practice different ways to create and manipulate strings.

```cpp
#include <iostream>
#include <string>

int main() {
    // TODO: Complete these string operations
    
    // 1. Create a string with your name
    std::string name = /* your code here */;
    
    // 2. Create a greeting by concatenating "Hello, " with your name
    std::string greeting = /* your code here */;
    
    // 3. Add an exclamation mark at the end
    /* your code here */
    
    // 4. Print the length of the greeting
    std::cout << "Length: " << /* your code here */ << std::endl;
    
    // 5. Print the first and last characters
    std::cout << "First: " << /* your code here */ << std::endl;
    std::cout << "Last: " << /* your code here */ << std::endl;
    
    // 6. Convert to uppercase (you'll need to look this up!)
    /* your code here */
    
    return 0;
}
```

**Expected Output**:
```
Length: 13
First: H
Last: !
HELLO, ALICE!
```

**Hints**:
- Use `std::transform` with `std::toupper` for uppercase conversion
- Remember to include `<algorithm>` and `<cctype>`

### Problem 1.2: String Searching and Extraction (15 minutes)

**Objective**: Learn to find and extract parts of strings.

```cpp
#include <iostream>
#include <string>

std::string extract_domain(const std::string& email) {
    // TODO: Extract domain from email address
    // Example: "user@example.com" -> "example.com"
    
    /* your code here */
}

std::string extract_filename(const std::string& path) {
    // TODO: Extract filename from file path
    // Example: "/home/user/documents/file.txt" -> "file.txt"
    
    /* your code here */
}

int main() {
    std::string email = "alice.smith@university.edu";
    std::string path = "/home/projects/cpp/main.cpp";
    
    std::cout << "Domain: " << extract_domain(email) << std::endl;
    std::cout << "Filename: " << extract_filename(path) << std::endl;
    
    return 0;
}
```

**Expected Output**:
```
Domain: university.edu
Filename: main.cpp
```

### Problem 1.3: String Validation (15 minutes)

**Objective**: Practice string comparison and validation.

```cpp
#include <iostream>
#include <string>
#include <cctype>

bool is_valid_password(const std::string& password) {
    // TODO: Validate password with these rules:
    // - At least 8 characters long
    // - Contains at least one uppercase letter
    // - Contains at least one lowercase letter  
    // - Contains at least one digit
    
    /* your code here */
}

bool is_palindrome(const std::string& text) {
    // TODO: Check if text is a palindrome (reads same forwards/backwards)
    // Ignore case and spaces
    // Example: "A man a plan a canal Panama" -> true
    
    /* your code here */
}

int main() {
    // Test passwords
    std::cout << "Password1: " << (is_valid_password("Password1") ? "Valid" : "Invalid") << std::endl;
    std::cout << "weak: " << (is_valid_password("weak") ? "Valid" : "Invalid") << std::endl;
    
    // Test palindromes
    std::cout << "racecar: " << (is_palindrome("racecar") ? "Palindrome" : "Not palindrome") << std::endl;
    std::cout << "hello: " << (is_palindrome("hello") ? "Palindrome" : "Not palindrome") << std::endl;
    
    return 0;
}
```

**Expected Output**:
```
Password1: Valid
weak: Invalid
racecar: Palindrome
hello: Not palindrome
```

---

## Problem Set 2: Text Processing (60 minutes)

### Problem 2.1: CSV Parser (20 minutes)

**Objective**: Parse comma-separated values with proper handling of quoted fields.

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class CSVParser {
public:
    std::vector<std::string> parse_line(const std::string& line) {
        // TODO: Parse CSV line handling:
        // - Basic comma separation
        // - Quoted fields (may contain commas)
        // - Escaped quotes within fields
        
        /* your code here */
    }
    
    void print_parsed(const std::vector<std::string>& fields) {
        for (size_t i = 0; i < fields.size(); ++i) {
            std::cout << "Field " << i << ": '" << fields[i] << "'" << std::endl;
        }
    }
};

int main() {
    CSVParser parser;
    
    // Test cases
    std::string simple = "John,Doe,30,Engineer";
    std::string quoted = "John,\"Doe, Jr.\",30,\"Software Engineer\"";
    std::string escaped = "John,\"He said \"\"Hello\"\"\",30,Engineer";
    
    std::cout << "Simple CSV:" << std::endl;
    parser.print_parsed(parser.parse_line(simple));
    
    std::cout << "\nQuoted CSV:" << std::endl;
    parser.print_parsed(parser.parse_line(quoted));
    
    return 0;
}
```

### Problem 2.2: Text Statistics (20 minutes)

**Objective**: Analyze text and generate statistics.

```cpp
#include <iostream>
#include <string>
#include <map>
#include <cctype>

class TextAnalyzer {
private:
    std::string text;
    
public:
    TextAnalyzer(const std::string& input) : text(input) {}
    
    int count_words() {
        // TODO: Count words (separated by whitespace)
        /* your code here */
    }
    
    int count_sentences() {
        // TODO: Count sentences (ending with . ! ?)
        /* your code here */
    }
    
    std::map<char, int> character_frequency() {
        // TODO: Count frequency of each alphabetic character (case-insensitive)
        /* your code here */
    }
    
    std::string most_common_word() {
        // TODO: Find the most frequently occurring word (case-insensitive)
        /* your code here */
    }
    
    void print_statistics() {
        std::cout << "Words: " << count_words() << std::endl;
        std::cout << "Sentences: " << count_sentences() << std::endl;
        std::cout << "Most common word: " << most_common_word() << std::endl;
        
        std::cout << "Character frequencies:" << std::endl;
        auto freq = character_frequency();
        for (const auto& pair : freq) {
            std::cout << "  " << pair.first << ": " << pair.second << std::endl;
        }
    }
};

int main() {
    std::string text = "The quick brown fox jumps over the lazy dog. "
                       "The dog was sleeping in the sun. What a beautiful day!";
    
    TextAnalyzer analyzer(text);
    analyzer.print_statistics();
    
    return 0;
}
```

### Problem 2.3: Simple Template Engine (20 minutes)

**Objective**: Create a basic template replacement system.

```cpp
#include <iostream>
#include <string>
#include <map>
#include <regex>

class TemplateEngine {
private:
    std::map<std::string, std::string> variables;
    
public:
    void set_variable(const std::string& name, const std::string& value) {
        variables[name] = value;
    }
    
    std::string render(const std::string& template_text) {
        // TODO: Replace {{variable_name}} with values
        // Example: "Hello {{name}}!" with name="World" -> "Hello World!"
        
        /* your code here */
    }
    
    std::string render_with_conditionals(const std::string& template_text) {
        // TODO: Handle simple conditionals
        // {{#if variable_name}}text{{/if}} - show text if variable exists and is not empty
        // {{#unless variable_name}}text{{/unless}} - show text if variable doesn't exist or is empty
        
        /* your code here */
    }
};

int main() {
    TemplateEngine engine;
    engine.set_variable("name", "Alice");
    engine.set_variable("age", "25");
    engine.set_variable("city", "New York");
    
    std::string basic_template = "Hello {{name}}! You are {{age}} years old and live in {{city}}.";
    std::cout << engine.render(basic_template) << std::endl;
    
    std::string conditional_template = 
        "Welcome {{name}}! "
        "{{#if age}}You are {{age}} years old. {{/if}}"
        "{{#unless phone}}Please provide your phone number. {{/unless}}";
    
    std::cout << engine.render_with_conditionals(conditional_template) << std::endl;
    
    return 0;
}
```

---

## Problem Set 3: Advanced String Operations (40 minutes)

### Problem 3.1: String Compression (20 minutes)

**Objective**: Implement basic string compression algorithms.

```cpp
#include <iostream>
#include <string>
#include <sstream>

class StringCompressor {
public:
    std::string run_length_encode(const std::string& input) {
        // TODO: Implement run-length encoding
        // Example: "aaabbc" -> "a3b2c1"
        // Example: "abcd" -> "a1b1c1d1" (or return original if not shorter)
        
        /* your code here */
    }
    
    std::string run_length_decode(const std::string& encoded) {
        // TODO: Decode run-length encoded string
        // Example: "a3b2c1" -> "aaabbc"
        
        /* your code here */
    }
    
    std::string remove_duplicates(const std::string& input) {
        // TODO: Remove consecutive duplicate characters
        // Example: "aaabbbccc" -> "abc"
        // Example: "abccba" -> "abcba"
        
        /* your code here */
    }
};

int main() {
    StringCompressor compressor;
    
    std::string test1 = "aaabbbccc";
    std::string test2 = "abcdef";
    std::string test3 = "aabbcc";
    
    std::cout << "Original: " << test1 << std::endl;
    std::string encoded1 = compressor.run_length_encode(test1);
    std::cout << "Encoded: " << encoded1 << std::endl;
    std::cout << "Decoded: " << compressor.run_length_decode(encoded1) << std::endl;
    
    std::cout << "\nDuplicate removal:" << std::endl;
    std::cout << test1 << " -> " << compressor.remove_duplicates(test1) << std::endl;
    std::cout << "abccba -> " << compressor.remove_duplicates("abccba") << std::endl;
    
    return 0;
}
```

### Problem 3.2: Advanced Text Search (20 minutes)

**Objective**: Implement fuzzy string matching and advanced search.

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class FuzzyMatcher {
public:
    int levenshtein_distance(const std::string& s1, const std::string& s2) {
        // TODO: Calculate edit distance between two strings
        // (insertions, deletions, substitutions needed to transform s1 to s2)
        
        /* your code here */
    }
    
    double similarity_ratio(const std::string& s1, const std::string& s2) {
        // TODO: Calculate similarity ratio (0.0 to 1.0)
        // 1.0 = identical, 0.0 = completely different
        // Formula: 1.0 - (edit_distance / max(len1, len2))
        
        /* your code here */
    }
    
    std::vector<std::string> find_similar(const std::string& query, 
                                         const std::vector<std::string>& candidates,
                                         double threshold = 0.6) {
        // TODO: Find all candidates with similarity >= threshold
        
        /* your code here */
    }
    
    bool contains_pattern(const std::string& text, const std::string& pattern) {
        // TODO: Check if pattern exists allowing for * (any characters) wildcards
        // Example: pattern "he*o" matches "hello", "hero", "helllo"
        
        /* your code here */
    }
};

int main() {
    FuzzyMatcher matcher;
    
    std::cout << "Edit distance between 'kitten' and 'sitting': " 
              << matcher.levenshtein_distance("kitten", "sitting") << std::endl;
    
    std::cout << "Similarity ratio: " 
              << matcher.similarity_ratio("hello", "helo") << std::endl;
    
    std::vector<std::string> words = {"hello", "world", "help", "hero", "hell", "welcome"};
    auto similar = matcher.find_similar("hello", words, 0.6);
    
    std::cout << "Words similar to 'hello':" << std::endl;
    for (const auto& word : similar) {
        std::cout << "  " << word << " (similarity: " 
                  << matcher.similarity_ratio("hello", word) << ")" << std::endl;
    }
    
    // Test pattern matching
    std::cout << "\nPattern matching:" << std::endl;
    std::cout << "he*o matches hello: " 
              << (matcher.contains_pattern("hello", "he*o") ? "Yes" : "No") << std::endl;
    std::cout << "he*o matches world: " 
              << (matcher.contains_pattern("world", "he*o") ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

---

## 🚀 Challenge Problems (Optional)

### Challenge 1: Simple Regex Engine

Implement a basic regular expression engine that supports:
- Literal characters
- `.` (any character)
- `*` (zero or more of previous)
- `^` (start of string)
- `$` (end of string)

### Challenge 2: Unicode Text Processor

Create a text processor that:
- Counts actual characters (not bytes) in UTF-8 strings
- Handles different Unicode normalization forms
- Extracts words from multilingual text

### Challenge 3: Efficient String Pool

Implement a string interning system that:
- Stores unique strings only once in memory
- Provides fast lookup and comparison
- Automatically manages memory

---

## 📝 Submission Guidelines

1. **Code Quality**:
   - Use meaningful variable names
   - Add comments for complex algorithms
   - Handle edge cases (empty strings, null inputs)
   - Follow const-correctness

2. **Testing**:
   - Test with edge cases
   - Verify memory safety (no buffer overflows)
   - Check Unicode handling where applicable

3. **Performance Considerations**:
   - Use string_view for read-only parameters
   - Reserve capacity for strings that will grow
   - Consider algorithmic complexity

4. **Error Handling**:
   - Use exceptions for invalid input
   - Check bounds when accessing string elements
   - Handle conversion errors gracefully

---

## 💡 Hints and Tips

- **String Comparison**: Use `std::string::compare()` for three-way comparison
- **Case-Insensitive Operations**: Convert to lowercase first
- **Unicode**: Consider using specialized libraries for production code
- **Performance**: Profile before optimizing - std::string is often fast enough
- **Memory**: Watch out for dangling string_view references

Remember: These problems build real-world text processing skills you'll use in many applications!

---

## Evaluation Criteria

**Total: 16 Points (4 points per outcome criteria)**

1. **Correctness** (4 points): Programs compile and work as specified
2. **Code Quality** (4 points): Clean, readable, well-organized code
3. **Best Practices** (4 points): Following C++ idioms and conventions
4. **Documentation** (4 points): Appropriate comments and clear output
