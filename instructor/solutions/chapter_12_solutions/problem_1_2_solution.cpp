/**
 * Chapter 12 - Problem 1.2: Data Processor with Multiple Types
 * 
 * This solution demonstrates the use of std::variant for handling multiple types
 * in a type-safe manner.
 * 
 * Key learning points:
 * - Using std::variant for type-safe unions
 * - std::visit for type-safe operations on variants
 * - Pattern matching with visitors
 */

#include <variant>
#include <string>
#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <cmath>

using DataValue = std::variant<int, double, std::string>;

class DataProcessor {
public:
    /**
     * Process a single data value and return a description string
     * Uses std::visit for type-safe processing
     */
    static std::string describe(const DataValue& data) {
        return std::visit([](const auto& value) -> std::string {
            using T = std::decay_t<decltype(value)>;
            
            if constexpr (std::is_same_v<T, int>) {
                return "Integer: " + std::to_string(value);
            } else if constexpr (std::is_same_v<T, double>) {
                std::ostringstream oss;
                oss << "Double: " << value;
                return oss.str();
            } else if constexpr (std::is_same_v<T, std::string>) {
                return "String: " + value;
            }
        }, data);
    }
    
    /**
     * Calculate the "size" of the data 
     * - int: return the value itself
     * - double: return rounded value
     * - string: return length
     */
    static int calculate_size(const DataValue& data) {
        return std::visit([](const auto& value) -> int {
            using T = std::decay_t<decltype(value)>;
            
            if constexpr (std::is_same_v<T, int>) {
                return value;
            } else if constexpr (std::is_same_v<T, double>) {
                return static_cast<int>(std::round(value));
            } else if constexpr (std::is_same_v<T, std::string>) {
                return static_cast<int>(value.length());
            }
        }, data);
    }
    
    /**
     * Alternative implementation using traditional approach for comparison
     * Shows how std::visit compares to manual type checking
     */
    static std::string describe_traditional(const DataValue& data) {
        if (std::holds_alternative<int>(data)) {
            return "Integer: " + std::to_string(std::get<int>(data));
        } else if (std::holds_alternative<double>(data)) {
            std::ostringstream oss;
            oss << "Double: " << std::get<double>(data);
            return oss.str();
        } else if (std::holds_alternative<std::string>(data)) {
            return "String: " + std::get<std::string>(data);
        }
        return "Unknown type";
    }
    
    /**
     * Get the type name as a string - useful for debugging
     */
    static std::string get_type_name(const DataValue& data) {
        return std::visit([](const auto& value) -> std::string {
            using T = std::decay_t<decltype(value)>;
            
            if constexpr (std::is_same_v<T, int>) {
                return "int";
            } else if constexpr (std::is_same_v<T, double>) {
                return "double";
            } else if constexpr (std::is_same_v<T, std::string>) {
                return "string";
            }
        }, data);
    }
};

#ifdef RUN_TESTS
void run_tests() {
    std::cout << "Running DataProcessor tests...\n";
    
    // Test data
    DataValue int_data = 42;
    DataValue double_data = 3.14159;
    DataValue string_data = std::string("Hello World");
    
    // Test describe function
    std::cout << "Testing describe...\n";
    assert(DataProcessor::describe(int_data) == "Integer: 42");
    assert(DataProcessor::describe(double_data) == "Double: 3.14159");
    assert(DataProcessor::describe(string_data) == "String: Hello World");
    std::cout << "✓ describe tests passed\n";
    
    // Test calculate_size function
    std::cout << "Testing calculate_size...\n";
    assert(DataProcessor::calculate_size(int_data) == 42);
    assert(DataProcessor::calculate_size(double_data) == 3);  // rounded
    assert(DataProcessor::calculate_size(string_data) == 11); // length
    std::cout << "✓ calculate_size tests passed\n";
    
    // Test edge cases
    std::cout << "Testing edge cases...\n";
    DataValue zero_int = 0;
    DataValue negative_double = -2.7;
    DataValue empty_string = std::string("");
    
    assert(DataProcessor::calculate_size(zero_int) == 0);
    assert(DataProcessor::calculate_size(negative_double) == -3);  // rounded
    assert(DataProcessor::calculate_size(empty_string) == 0);     // empty length
    std::cout << "✓ edge case tests passed\n";
    
    std::cout << "All tests passed! ✓\n";
}
#endif

int main() {
    std::cout << "Chapter 12 - Problem 1.2: Data Processor with Multiple Types\n";
    std::cout << "==========================================================\n\n";
    
    // Create different types of data
    std::vector<DataValue> data_items = {
        42,                           // int
        3.14159,                     // double
        std::string("Hello World"),  // string
        -17,                         // negative int
        2.71828,                     // another double
        std::string("C++"),          // short string
        0,                           // zero
        std::string("")              // empty string
    };
    
    std::cout << "Processing various data types:\n";
    std::cout << "============================\n\n";
    
    for (size_t i = 0; i < data_items.size(); ++i) {
        const auto& item = data_items[i];
        
        std::cout << "Item " << (i + 1) << ":\n";
        std::cout << "  Type: " << DataProcessor::get_type_name(item) << "\n";
        std::cout << "  Description: " << DataProcessor::describe(item) << "\n";
        std::cout << "  Size: " << DataProcessor::calculate_size(item) << "\n";
        std::cout << "\n";
    }
    
    // Demonstrate dynamic type handling
    std::cout << "Dynamic Type Handling Example:\n";
    std::cout << "=============================\n";
    
    DataValue dynamic_data = 100;
    std::cout << "Initial: " << DataProcessor::describe(dynamic_data) 
              << " (size: " << DataProcessor::calculate_size(dynamic_data) << ")\n";
    
    dynamic_data = 99.5;
    std::cout << "Changed to: " << DataProcessor::describe(dynamic_data) 
              << " (size: " << DataProcessor::calculate_size(dynamic_data) << ")\n";
    
    dynamic_data = std::string("Dynamic!");
    std::cout << "Changed to: " << DataProcessor::describe(dynamic_data) 
              << " (size: " << DataProcessor::calculate_size(dynamic_data) << ")\n";
    
    // Show comparison with traditional approach
    std::cout << "\nComparison with Traditional Approach:\n";
    std::cout << "===================================\n";
    
    DataValue test_data = 42.7;
    std::cout << "Using std::visit: " << DataProcessor::describe(test_data) << "\n";
    std::cout << "Using traditional: " << DataProcessor::describe_traditional(test_data) << "\n";
    std::cout << "(Both produce the same result, but std::visit is more modern and flexible)\n";
    
#ifdef RUN_TESTS
    std::cout << "\n";
    run_tests();
#endif
    
    return 0;
}