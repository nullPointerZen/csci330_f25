#include <iostream>
#include <string>
#include <optional>
#include <variant>
#include <tuple>
#include <map>
#include <vector>
#include <chrono>
#include <functional>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cctype>

// =============================================================================
// PROBLEM SET 1: FOUNDATION PROBLEMS
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 1.1: Safe String Operations
// Learning Objective: Practice std::optional for safe operations
// -----------------------------------------------------------------------------

class SafeStringProcessor {
public:
    // Returns the character at index, or nullopt if index is invalid
    static std::optional<char> char_at(const std::string& str, size_t index) {
        if (index >= str.length()) {
            return std::nullopt;  // Index out of bounds
        }
        return str[index];
    }

    // Finds the first occurrence of a character, returns its index or nullopt
    static std::optional<size_t> find_char(const std::string& str, char c) {
        size_t pos = str.find(c);
        if (pos == std::string::npos) {
            return std::nullopt;  // Character not found
        }
        return pos;
    }

    // Converts string to integer, returns nullopt if conversion fails
    static std::optional<int> to_int(const std::string& str) {
        try {
            size_t pos = 0;
            int result = std::stoi(str, &pos);
            // Check if entire string was consumed
            if (pos == str.length()) {
                return result;
            }
            return std::nullopt;  // Partial conversion
        } catch (...) {
            return std::nullopt;  // Conversion failed
        }
    }
};

// -----------------------------------------------------------------------------
// Problem 1.2: Data Processor with Multiple Types
// Learning Objective: Practice std::variant for handling different data types
// -----------------------------------------------------------------------------

using DataValue = std::variant<int, double, std::string>;

class DataProcessor {
public:
    // Process a single data value and return a description string
    static std::string describe(const DataValue& data) {
        // Using std::visit with a lambda to handle each type
        return std::visit([](auto&& arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;
            std::ostringstream oss;

            if constexpr (std::is_same_v<T, int>) {
                oss << "Integer: " << arg;
            } else if constexpr (std::is_same_v<T, double>) {
                oss << "Double: " << arg;
            } else if constexpr (std::is_same_v<T, std::string>) {
                oss << "String: " << arg;
            }

            return oss.str();
        }, data);
    }

    // Calculate the "size" of the data (int->value, double->rounded, string->length)
    static int calculate_size(const DataValue& data) {
        return std::visit([](auto&& arg) -> int {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, int>) {
                return arg;  // Return the integer value
            } else if constexpr (std::is_same_v<T, double>) {
                return static_cast<int>(std::round(arg));  // Round to nearest int
            } else if constexpr (std::is_same_v<T, std::string>) {
                return static_cast<int>(arg.length());  // String length
            }
        }, data);
    }
};

// -----------------------------------------------------------------------------
// Problem 1.3: Student Record System
// Learning Objective: Practice std::tuple for grouping related data
// -----------------------------------------------------------------------------

using StudentRecord = std::tuple<std::string, int, double>; // name, age, gpa

class StudentManager {
public:
    // Create a student record
    static StudentRecord create_student(const std::string& name, int age, double gpa) {
        return std::make_tuple(name, age, gpa);
    }

    // Extract student information using std::get
    static std::string get_name(const StudentRecord& student) {
        return std::get<0>(student);
    }

    static int get_age(const StudentRecord& student) {
        return std::get<1>(student);
    }

    static double get_gpa(const StudentRecord& student) {
        return std::get<2>(student);
    }

    // Format student information as a string
    static std::string format_student(const StudentRecord& student) {
        std::ostringstream oss;
        oss << get_name(student) << " (" << get_age(student)
            << ") - GPA: " << get_gpa(student);
        return oss.str();
    }
};

// =============================================================================
// PROBLEM SET 2: INTERMEDIATE APPLICATIONS
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 2.1: Configuration Parser
// Learning Objective: Combine std::optional and std::variant for robust parsing
// -----------------------------------------------------------------------------

using ConfigValue = std::variant<int, double, std::string, bool>;

class ConfigParser {
private:
    std::map<std::string, std::string> raw_data;

    // Helper function to trim whitespace
    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, last - first + 1);
    }

    // Helper to check if string is a valid integer
    static bool is_valid_int(const std::string& str) {
        if (str.empty()) return false;
        size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
        if (start >= str.length()) return false;

        for (size_t i = start; i < str.length(); ++i) {
            if (!std::isdigit(str[i])) return false;
        }
        return true;
    }

    // Helper to check if string is a valid double
    static bool is_valid_double(const std::string& str) {
        try {
            size_t pos = 0;
            std::stod(str, &pos);
            return pos == str.length();
        } catch (...) {
            return false;
        }
    }

public:
    ConfigParser(const std::map<std::string, std::string>& data) : raw_data(data) {}

    // Get a configuration value, attempting to parse it as the requested type
    template<typename T>
    std::optional<T> get_value(const std::string& key) {
        auto it = raw_data.find(key);
        if (it == raw_data.end()) {
            return std::nullopt;  // Key not found
        }

        std::string value = trim(it->second);

        // Parse based on requested type
        if constexpr (std::is_same_v<T, int>) {
            if (!is_valid_int(value)) return std::nullopt;
            try {
                return std::stoi(value);
            } catch (...) {
                return std::nullopt;
            }
        } else if constexpr (std::is_same_v<T, double>) {
            if (!is_valid_double(value)) return std::nullopt;
            try {
                return std::stod(value);
            } catch (...) {
                return std::nullopt;
            }
        } else if constexpr (std::is_same_v<T, std::string>) {
            return value;
        } else if constexpr (std::is_same_v<T, bool>) {
            std::string lower = value;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            if (lower == "true" || lower == "1") return true;
            if (lower == "false" || lower == "0") return false;
            return std::nullopt;
        }

        return std::nullopt;
    }

    // Get a value with a default fallback
    template<typename T>
    T get_value_or(const std::string& key, const T& default_value) {
        auto result = get_value<T>(key);
        return result.value_or(default_value);
    }

    // Get all configuration as a map of ConfigValues
    std::map<std::string, ConfigValue> get_all_parsed() {
        std::map<std::string, ConfigValue> result;

        for (const auto& [key, value] : raw_data) {
            std::string trimmed = trim(value);

            // Try to parse as int first
            if (is_valid_int(trimmed)) {
                try {
                    result[key] = std::stoi(trimmed);
                    continue;
                } catch (...) {}
            }

            // Try to parse as double
            if (is_valid_double(trimmed)) {
                try {
                    result[key] = std::stod(trimmed);
                    continue;
                } catch (...) {}
            }

            // Try to parse as bool
            std::string lower = trimmed;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            if (lower == "true" || lower == "false") {
                result[key] = (lower == "true");
                continue;
            }

            // Default to string
            result[key] = trimmed;
        }

        return result;
    }
};

// -----------------------------------------------------------------------------
// Problem 2.2: Performance Benchmarker
// Learning Objective: Use std::chrono and std::tuple for performance measurement
// -----------------------------------------------------------------------------

using BenchmarkResult = std::tuple<double, double, double>; // min_time, max_time, avg_time (in milliseconds)

class Benchmarker {
public:
    // Run a function multiple times and return timing statistics
    template<typename Func>
    static BenchmarkResult benchmark(Func function, int iterations = 1000) {
        std::vector<double> times;
        times.reserve(iterations);

        for (int i = 0; i < iterations; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            function();
            auto end = std::chrono::high_resolution_clock::now();

            // Convert to milliseconds
            std::chrono::duration<double, std::milli> duration = end - start;
            times.push_back(duration.count());
        }

        // Calculate statistics
        double min_time = *std::min_element(times.begin(), times.end());
        double max_time = *std::max_element(times.begin(), times.end());
        double avg_time = 0.0;
        for (double t : times) {
            avg_time += t;
        }
        avg_time /= iterations;

        return std::make_tuple(min_time, max_time, avg_time);
    }

    // Format benchmark results as a string
    static std::string format_results(const BenchmarkResult& results) {
        auto [min_time, max_time, avg_time] = results;  // Structured binding

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(6);
        oss << "Min: " << min_time << "ms, "
            << "Max: " << max_time << "ms, "
            << "Avg: " << avg_time << "ms";
        return oss.str();
    }

    // Compare two benchmark results - returns optional<string> with comparison
    static std::optional<std::string> compare_results(
        const BenchmarkResult& result1,
        const BenchmarkResult& result2,
        const std::string& name1 = "Function 1",
        const std::string& name2 = "Function 2"
    ) {
        auto [min1, max1, avg1] = result1;
        auto [min2, max2, avg2] = result2;

        if (avg1 == 0.0 || avg2 == 0.0) {
            return std::nullopt;  // Can't compare if either has zero time
        }

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);

        double speedup = avg2 / avg1;
        if (speedup > 1.0) {
            oss << name1 << " is " << speedup << "x faster than " << name2;
        } else {
            oss << name2 << " is " << (1.0 / speedup) << "x faster than " << name1;
        }

        return oss.str();
    }
};

// =============================================================================
// PROBLEM SET 3: INTEGRATION PROJECT
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 3.1: Data Analysis Pipeline
// Learning Objective: Integrate all utilities in a realistic data processing scenario
// -----------------------------------------------------------------------------

using DataPoint = std::variant<int, double, std::string>;
using ProcessingResult = std::tuple<size_t, size_t, double>; // processed_count, error_count, processing_time_ms
using DataSummary = std::tuple<std::optional<double>, std::optional<double>, size_t>; // min, max, count

// Helper class for timing operations
class TimedOperation {
private:
    std::chrono::steady_clock::time_point start_time;
    std::string operation_name;

public:
    TimedOperation(const std::string& name)
        : start_time(std::chrono::steady_clock::now()), operation_name(name) {
        std::cout << "[TimedOperation] Started: " << operation_name << std::endl;
    }

    ~TimedOperation() {
        double elapsed = elapsed_ms();
        std::cout << "[TimedOperation] Completed: " << operation_name
                  << " (took " << elapsed << "ms)" << std::endl;
    }

    double elapsed_ms() const {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> duration = now - start_time;
        return duration.count();
    }
};

class DataAnalyzer {
private:
    std::vector<DataPoint> data;

    // Helper to try converting string to double
    static std::optional<double> try_parse_double(const std::string& str) {
        try {
            size_t pos = 0;
            double result = std::stod(str, &pos);
            if (pos == str.length()) {
                return result;
            }
        } catch (...) {}
        return std::nullopt;
    }

    // Helper to extract numeric value from DataPoint
    static std::optional<double> get_numeric_value(const DataPoint& point) {
        return std::visit([](auto&& arg) -> std::optional<double> {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, int>) {
                return static_cast<double>(arg);
            } else if constexpr (std::is_same_v<T, double>) {
                return arg;
            } else {
                return std::nullopt;  // String values are not numeric
            }
        }, point);
    }

public:
    // Load data from different sources
    void add_data_point(const DataPoint& point) {
        data.push_back(point);
    }

    void load_from_strings(const std::vector<std::string>& raw_data) {
        TimedOperation timer("load_from_strings");

        for (const std::string& raw : raw_data) {
            // Try to parse as integer first
            try {
                size_t pos = 0;
                int int_val = std::stoi(raw, &pos);
                if (pos == raw.length()) {
                    // Check if it looks like an integer (no decimal point)
                    if (raw.find('.') == std::string::npos) {
                        data.push_back(int_val);
                        continue;
                    }
                }
            } catch (...) {}

            // Try to parse as double
            auto double_opt = try_parse_double(raw);
            if (double_opt) {
                data.push_back(*double_opt);
                continue;
            }

            // Store as string if not numeric
            data.push_back(raw);
        }
    }

    // Process data with error handling and timing
    ProcessingResult process_data() {
        TimedOperation timer("process_data");

        size_t processed = 0;
        size_t errors = 0;

        auto start = std::chrono::high_resolution_clock::now();

        for (const auto& point : data) {
            try {
                // Simulate processing - just verify we can access the data
                std::visit([](auto&& arg) {
                    // Processing happens here
                    (void)arg;  // Suppress unused variable warning
                }, point);
                processed++;
            } catch (...) {
                errors++;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        return std::make_tuple(processed, errors, duration.count());
    }

    // Calculate statistics for numeric data only
    DataSummary calculate_numeric_summary() {
        TimedOperation timer("calculate_numeric_summary");

        std::vector<double> numeric_values;

        for (const auto& point : data) {
            auto numeric_opt = get_numeric_value(point);
            if (numeric_opt) {
                numeric_values.push_back(*numeric_opt);
            }
        }

        if (numeric_values.empty()) {
            return std::make_tuple(std::nullopt, std::nullopt, 0);
        }

        double min_val = *std::min_element(numeric_values.begin(), numeric_values.end());
        double max_val = *std::max_element(numeric_values.begin(), numeric_values.end());

        return std::make_tuple(
            std::optional<double>(min_val),
            std::optional<double>(max_val),
            numeric_values.size()
        );
    }

    // Get data points of a specific type
    template<typename T>
    std::vector<T> get_data_of_type() {
        std::vector<T> result;

        for (const auto& point : data) {
            if (std::holds_alternative<T>(point)) {
                result.push_back(std::get<T>(point));
            }
        }

        return result;
    }

    // Export results with timing information
    std::optional<std::string> export_summary() {
        if (data.empty()) {
            return std::nullopt;
        }

        TimedOperation timer("export_summary");

        auto [min_val, max_val, numeric_count] = calculate_numeric_summary();

        // Count types
        size_t int_count = 0;
        size_t double_count = 0;
        size_t string_count = 0;

        for (const auto& point : data) {
            if (std::holds_alternative<int>(point)) {
                int_count++;
            } else if (std::holds_alternative<double>(point)) {
                double_count++;
            } else if (std::holds_alternative<std::string>(point)) {
                string_count++;
            }
        }

        std::ostringstream oss;
        oss << "Data Analysis Summary\n";
        oss << "====================\n";
        oss << "Total data points: " << data.size() << "\n";

        if (min_val && max_val) {
            oss << "Numeric values: " << numeric_count
                << " (min: " << *min_val << ", max: " << *max_val << ")\n";
        } else {
            oss << "Numeric values: 0\n";
        }

        oss << "String values: " << string_count << "\n";
        oss << "Type breakdown:\n";
        oss << "  - Integers: " << int_count << "\n";
        oss << "  - Doubles: " << double_count << "\n";
        oss << "  - Strings: " << string_count << "\n";

        return oss.str();
    }
};

// =============================================================================
// MAIN FUNCTION - COMPREHENSIVE DEMONSTRATION
// =============================================================================

int main() {
    std::cout << "=== Chapter 12: Utilities - Comprehensive Demo ===\n\n";

    // =========================================================================
    // PROBLEM SET 1 DEMOS
    // =========================================================================

    std::cout << "--- Problem 1.1: Safe String Operations ---\n";
    {
        std::string test = "hello";

        // Valid operations
        auto ch = SafeStringProcessor::char_at(test, 1);
        if (ch) {
            std::cout << "Character at index 1: " << *ch << std::endl;
        }

        auto pos = SafeStringProcessor::find_char(test, 'l');
        if (pos) {
            std::cout << "First 'l' found at index: " << *pos << std::endl;
        }

        auto num = SafeStringProcessor::to_int("123");
        if (num) {
            std::cout << "Parsed integer: " << *num << std::endl;
        }

        // Invalid operations (returns nullopt)
        auto invalid_ch = SafeStringProcessor::char_at(test, 10);
        std::cout << "char_at(10) has value: " << (invalid_ch.has_value() ? "yes" : "no") << std::endl;

        auto invalid_pos = SafeStringProcessor::find_char(test, 'x');
        std::cout << "find_char('x') has value: " << (invalid_pos.has_value() ? "yes" : "no") << std::endl;

        auto invalid_num = SafeStringProcessor::to_int("not_a_number");
        std::cout << "to_int('not_a_number') has value: " << (invalid_num.has_value() ? "yes" : "no") << std::endl;
    }

    std::cout << "\n--- Problem 1.2: Data Processor with Multiple Types ---\n";
    {
        DataValue int_data = 42;
        DataValue double_data = 3.14159;
        DataValue string_data = std::string("Hello World");

        std::cout << DataProcessor::describe(int_data) << std::endl;
        std::cout << DataProcessor::describe(double_data) << std::endl;
        std::cout << DataProcessor::describe(string_data) << std::endl;

        std::cout << "Size of int_data: " << DataProcessor::calculate_size(int_data) << std::endl;
        std::cout << "Size of double_data: " << DataProcessor::calculate_size(double_data) << std::endl;
        std::cout << "Size of string_data: " << DataProcessor::calculate_size(string_data) << std::endl;
    }

    std::cout << "\n--- Problem 1.3: Student Record System ---\n";
    {
        auto student = StudentManager::create_student("Alice Johnson", 20, 3.75);

        std::cout << "Name: " << StudentManager::get_name(student) << std::endl;
        std::cout << "Age: " << StudentManager::get_age(student) << std::endl;
        std::cout << "GPA: " << StudentManager::get_gpa(student) << std::endl;
        std::cout << "Formatted: " << StudentManager::format_student(student) << std::endl;
    }

    // =========================================================================
    // PROBLEM SET 2 DEMOS
    // =========================================================================

    std::cout << "\n--- Problem 2.1: Configuration Parser ---\n";
    {
        std::map<std::string, std::string> config_data = {
            {"port", "8080"},
            {"host", "localhost"},
            {"timeout", "30.5"},
            {"debug", "true"},
            {"invalid_number", "not_a_number"}
        };

        ConfigParser parser(config_data);

        // Successful parsing
        auto port = parser.get_value<int>("port");
        if (port) {
            std::cout << "Port: " << *port << std::endl;
        }

        auto host = parser.get_value<std::string>("host");
        if (host) {
            std::cout << "Host: " << *host << std::endl;
        }

        auto timeout = parser.get_value<double>("timeout");
        if (timeout) {
            std::cout << "Timeout: " << *timeout << std::endl;
        }

        auto debug = parser.get_value<bool>("debug");
        if (debug) {
            std::cout << "Debug: " << (*debug ? "true" : "false") << std::endl;
        }

        // Failed parsing
        auto invalid = parser.get_value<int>("invalid_number");
        std::cout << "Invalid number has value: " << (invalid.has_value() ? "yes" : "no") << std::endl;

        // Using defaults
        int default_port = parser.get_value_or<int>("missing_key", 3000);
        std::cout << "Port with default: " << default_port << std::endl;
    }

    std::cout << "\n--- Problem 2.2: Performance Benchmarker ---\n";
    {
        // Test functions
        auto fast_function = []() {
            int sum = 0;
            for (int i = 0; i < 100; ++i) sum += i;
            return sum;
        };

        auto slow_function = []() {
            int sum = 0;
            for (int i = 0; i < 10000; ++i) sum += i;
            return sum;
        };

        std::cout << "Benchmarking fast function..." << std::endl;
        auto fast_results = Benchmarker::benchmark(fast_function, 1000);
        std::cout << "Fast function: " << Benchmarker::format_results(fast_results) << std::endl;

        std::cout << "Benchmarking slow function..." << std::endl;
        auto slow_results = Benchmarker::benchmark(slow_function, 100);
        std::cout << "Slow function: " << Benchmarker::format_results(slow_results) << std::endl;

        auto comparison = Benchmarker::compare_results(fast_results, slow_results, "Fast", "Slow");
        if (comparison) {
            std::cout << "Comparison: " << *comparison << std::endl;
        }
    }

    // =========================================================================
    // PROBLEM SET 3 DEMO
    // =========================================================================

    std::cout << "\n--- Problem 3.1: Data Analysis Pipeline ---\n";
    {
        DataAnalyzer analyzer;

        // Load mixed data
        std::vector<std::string> raw_data = {
            "42",           // int
            "3.14159",      // double
            "hello",        // string
            "99",           // int
            "2.71828",      // double
            "invalid_num",  // string (not convertible to number)
            "world"         // string
        };

        std::cout << "Loading data from strings..." << std::endl;
        analyzer.load_from_strings(raw_data);

        // Process and analyze
        std::cout << "\nProcessing data..." << std::endl;
        auto [processed, errors, time_ms] = analyzer.process_data();
        std::cout << "Processed: " << processed << ", Errors: " << errors
                  << ", Time: " << time_ms << "ms" << std::endl;

        std::cout << "\nCalculating numeric summary..." << std::endl;
        auto [min_val, max_val, numeric_count] = analyzer.calculate_numeric_summary();

        if (min_val && max_val) {
            std::cout << "Numeric statistics: count=" << numeric_count
                      << ", min=" << *min_val << ", max=" << *max_val << std::endl;
        }

        // Test type filtering
        auto strings = analyzer.get_data_of_type<std::string>();
        std::cout << "String values found: " << strings.size() << std::endl;
        for (const auto& s : strings) {
            std::cout << "  - \"" << s << "\"" << std::endl;
        }

        auto integers = analyzer.get_data_of_type<int>();
        std::cout << "Integer values found: " << integers.size() << std::endl;
        for (const auto& i : integers) {
            std::cout << "  - " << i << std::endl;
        }

        // Export summary
        std::cout << "\nExporting summary..." << std::endl;
        auto summary = analyzer.export_summary();
        if (summary) {
            std::cout << "\n" << *summary << std::endl;
        }
    }

    std::cout << "\n=== All Demos Complete ===\n";

    return 0;
}

/*
================================================================================
KEY LEARNING POINTS FOR CHAPTER 12: UTILITIES
================================================================================

1. std::optional - Safe handling of optional values
   - Use nullopt for "no value"
   - Check has_value() before accessing
   - Use value_or() for defaults
   - Perfect for operations that might fail

2. std::variant - Type-safe unions
   - Can hold one of several types
   - Use std::visit for type-safe access
   - Use std::holds_alternative to check type
   - Use std::get to extract value

3. std::tuple - Group related data
   - Fixed-size collection of different types
   - Use std::get<N> or std::get<Type> to access
   - Structured bindings make it easy: auto [a, b, c] = tuple
   - Great for returning multiple values

4. std::chrono - Time and duration utilities
   - high_resolution_clock for benchmarking
   - steady_clock for timing operations
   - duration for time measurements
   - Convert between units (seconds, milliseconds, etc.)

5. Combining utilities
   - optional + variant = robust error handling
   - tuple + chrono = performance tracking
   - variant + visit = type-safe processing
   - All work together seamlessly

6. Modern C++ idioms
   - Use structured bindings with tuples
   - Use if-init with optional: if (auto val = get_value(); val)
   - Use std::visit with lambdas for variants
   - Template functions for generic code

7. Error handling patterns
   - Return optional instead of exceptions
   - Use variant for result types (success/error)
   - Combine with tuples for complex results
   - Always handle the "no value" case

8. Performance considerations
   - Use steady_clock for reliable timing
   - Multiple iterations for accurate benchmarks
   - Consider warm-up runs for cache effects
   - Report min/max/avg for complete picture

================================================================================
COMMON PATTERNS AND BEST PRACTICES
================================================================================

Pattern 1: Safe operations with optional
    std::optional<T> safe_operation() {
        if (can_succeed()) {
            return result;
        }
        return std::nullopt;
    }

Pattern 2: Visiting variants
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Type>) {
            // Handle Type
        }
    }, variant_value);

Pattern 3: Structured bindings with tuples
    auto [a, b, c] = get_tuple();
    // Direct access to all elements

Pattern 4: Timing operations
    auto start = std::chrono::high_resolution_clock::now();
    do_work();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

Pattern 5: RAII timing helper
    class Timer {
        auto start = std::chrono::steady_clock::now();
    public:
        ~Timer() {
            auto elapsed = std::chrono::steady_clock::now() - start;
            // Log or report elapsed time
        }
    };

================================================================================
DEBUGGING TIPS
================================================================================

1. For optional:
   - Always check has_value() before dereferencing
   - Use value_or() for safe defaults
   - Print "has value: yes/no" in debug output

2. For variant:
   - Use std::holds_alternative<T> to check type
   - Catch std::bad_variant_access exceptions
   - Print variant index() for debugging

3. For tuple:
   - Remember std::get is 0-indexed
   - Use structured bindings for clarity
   - std::tuple_size for number of elements

4. For chrono:
   - Use steady_clock for consistent timing
   - Convert to milliseconds for readability
   - Watch out for clock precision limitations

================================================================================
*/
