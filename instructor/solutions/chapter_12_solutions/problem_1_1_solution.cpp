/**
 * Chapter 12 - Problem 1.1: Safe String Operations
 * 
 * This solution demonstrates the use of std::optional for safe string operations
 * that might fail or return invalid results.
 * 
 * Key learning points:
 * - Using std::optional to handle potentially invalid operations
 * - Returning nullopt for error conditions
 * - Safe conversion patterns
 */

#include <optional>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cassert>

class SafeStringProcessor {
public:
    /**
     * Returns the character at index, or nullopt if index is invalid
     * Similar to Python's safe indexing or Java's Optional pattern
     */
    static std::optional<char> char_at(const std::string& str, size_t index) {
        if (index < str.length()) {
            return str[index];
        }
        return std::nullopt;
    }
    
    /**
     * Finds the first occurrence of a character, returns its index or nullopt
     * Similar to Python's str.find() returning -1 on failure, but safer
     */
    static std::optional<size_t> find_char(const std::string& str, char c) {
        auto pos = str.find(c);
        if (pos != std::string::npos) {
            return pos;
        }
        return std::nullopt;
    }
    
    /**
     * Converts string to integer, returns nullopt if conversion fails
     * Much safer than std::stoi which throws exceptions
     */
    static std::optional<int> to_int(const std::string& str) {
        try {
            // Check for empty string
            if (str.empty()) {
                return std::nullopt;
            }
            
            // Use stoi but catch exceptions
            size_t pos;
            int result = std::stoi(str, &pos);
            
            // Check if entire string was consumed
            if (pos == str.length()) {
                return result;
            }
            
            return std::nullopt;
        } catch (const std::exception&) {
            return std::nullopt;
        }
    }
};

#ifdef RUN_TESTS
void run_tests() {
    std::cout << "Running SafeStringProcessor tests...\n";
    
    // Test char_at
    std::cout << "Testing char_at...\n";
    assert(SafeStringProcessor::char_at("hello", 1) == 'e');
    assert(SafeStringProcessor::char_at("world", 0) == 'w');
    assert(!SafeStringProcessor::char_at("hello", 10).has_value());
    assert(!SafeStringProcessor::char_at("", 0).has_value());
    std::cout << "✓ char_at tests passed\n";
    
    // Test find_char
    std::cout << "Testing find_char...\n";
    assert(SafeStringProcessor::find_char("hello", 'l') == 2);
    assert(SafeStringProcessor::find_char("hello", 'h') == 0);
    assert(SafeStringProcessor::find_char("hello", 'o') == 4);
    assert(!SafeStringProcessor::find_char("hello", 'x').has_value());
    assert(!SafeStringProcessor::find_char("", 'a').has_value());
    std::cout << "✓ find_char tests passed\n";
    
    // Test to_int
    std::cout << "Testing to_int...\n";
    assert(SafeStringProcessor::to_int("123") == 123);
    assert(SafeStringProcessor::to_int("0") == 0);
    assert(SafeStringProcessor::to_int("-456") == -456);
    assert(!SafeStringProcessor::to_int("not_a_number").has_value());
    assert(!SafeStringProcessor::to_int("123abc").has_value());
    assert(!SafeStringProcessor::to_int("").has_value());
    assert(!SafeStringProcessor::to_int("12.34").has_value());  // Not an integer
    std::cout << "✓ to_int tests passed\n";
    
    std::cout << "All tests passed! ✓\n";
}
#endif

int main() {
    std::cout << "Chapter 12 - Problem 1.1: Safe String Operations\n";
    std::cout << "==============================================\n\n";
    
    // Example usage demonstrating the power of std::optional
    std::string text = "Hello World";
    
    std::cout << "Working with string: \"" << text << "\"\n\n";
    
    // Safe character access
    std::cout << "1. Safe character access:\n";
    auto char_result = SafeStringProcessor::char_at(text, 6);
    if (char_result) {
        std::cout << "Character at position 6: '" << *char_result << "'\n";
    } else {
        std::cout << "No character at position 6\n";
    }
    
    auto invalid_char = SafeStringProcessor::char_at(text, 50);
    if (invalid_char) {
        std::cout << "Character at position 50: '" << *invalid_char << "'\n";
    } else {
        std::cout << "No character at position 50 (index out of bounds)\n";
    }
    
    // Safe character finding
    std::cout << "\n2. Safe character finding:\n";
    auto find_result = SafeStringProcessor::find_char(text, 'W');
    if (find_result) {
        std::cout << "Found 'W' at position: " << *find_result << "\n";
    } else {
        std::cout << "'W' not found\n";
    }
    
    auto not_found = SafeStringProcessor::find_char(text, 'Z');
    if (not_found) {
        std::cout << "Found 'Z' at position: " << *not_found << "\n";
    } else {
        std::cout << "'Z' not found in the string\n";
    }
    
    // Safe string to integer conversion
    std::cout << "\n3. Safe string to integer conversion:\n";
    std::vector<std::string> test_numbers = {"123", "not_a_number", "-456", "12.34", ""};
    
    for (const auto& num_str : test_numbers) {
        auto int_result = SafeStringProcessor::to_int(num_str);
        std::cout << "\"" << num_str << "\" -> ";
        if (int_result) {
            std::cout << *int_result << "\n";
        } else {
            std::cout << "invalid conversion\n";
        }
    }
    
    std::cout << "\n4. Practical usage with value_or:\n";
    // This demonstrates how to provide defaults for failed operations
    std::string user_input = "invalid_number";
    int parsed_value = SafeStringProcessor::to_int(user_input).value_or(0);
    std::cout << "Parsed \"" << user_input << "\" as: " << parsed_value << " (using default 0)\n";
    
#ifdef RUN_TESTS
    std::cout << "\n";
    run_tests();
#endif
    
    return 0;
}