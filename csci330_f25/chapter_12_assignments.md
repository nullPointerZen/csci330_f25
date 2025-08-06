# Chapter 12: Utilities - Programming Problems

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 12 "Utilities"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 2.25 hours total for all three problem sets
- Test all programs thoroughly before submission

---

## Problem Set 1: Foundation Problems (45 minutes)
*Focus: Basic usage of each utility type*

### Problem 1.1: Safe String Operations (15 minutes)
**Learning Objective**: Practice `std::optional` for safe operations

**Problem**: Create a `SafeStringProcessor` class that handles potentially invalid string operations.

```cpp
class SafeStringProcessor {
public:
    // Returns the character at index, or nullopt if index is invalid
    static std::optional<char> char_at(const std::string& str, size_t index);
    
    // Finds the first occurrence of a character, returns its index or nullopt
    static std::optional<size_t> find_char(const std::string& str, char c);
    
    // Converts string to integer, returns nullopt if conversion fails
    static std::optional<int> to_int(const std::string& str);
};
```

**Test Cases**:
```cpp
// Should work
assert(SafeStringProcessor::char_at("hello", 1) == 'e');
assert(SafeStringProcessor::find_char("hello", 'l') == 2);
assert(SafeStringProcessor::to_int("123") == 123);

// Should return nullopt
assert(!SafeStringProcessor::char_at("hello", 10).has_value());
assert(!SafeStringProcessor::find_char("hello", 'x').has_value());
assert(!SafeStringProcessor::to_int("not_a_number").has_value());
```

**Python/Java Connection**: Similar to Python's string methods that return None or Java's Optional returns.

---

### Problem 1.2: Data Processor with Multiple Types (15 minutes)
**Learning Objective**: Practice `std::variant` for handling different data types

**Problem**: Create a simple data processor that can handle different types of input.

```cpp
using DataValue = std::variant<int, double, std::string>;

class DataProcessor {
public:
    // Process a single data value and return a description string
    static std::string describe(const DataValue& data);
    
    // Calculate the "size" of the data (int->value, double->rounded, string->length)
    static int calculate_size(const DataValue& data);
};
```

**Expected Behavior**:
```cpp
DataValue int_data = 42;
DataValue double_data = 3.14159;
DataValue string_data = std::string("Hello World");

assert(DataProcessor::describe(int_data) == "Integer: 42");
assert(DataProcessor::describe(double_data) == "Double: 3.14159");
assert(DataProcessor::describe(string_data) == "String: Hello World");

assert(DataProcessor::calculate_size(int_data) == 42);
assert(DataProcessor::calculate_size(double_data) == 3);  // rounded
assert(DataProcessor::calculate_size(string_data) == 11); // length
```

---

### Problem 1.3: Student Record System (15 minutes)
**Learning Objective**: Practice `std::tuple` for grouping related data

**Problem**: Create a student record system that uses tuples to manage student information.

```cpp
using StudentRecord = std::tuple<std::string, int, double>; // name, age, gpa

class StudentManager {
public:
    // Create a student record
    static StudentRecord create_student(const std::string& name, int age, double gpa);
    
    // Extract student information
    static std::string get_name(const StudentRecord& student);
    static int get_age(const StudentRecord& student);
    static double get_gpa(const StudentRecord& student);
    
    // Format student information as a string
    static std::string format_student(const StudentRecord& student);
};
```

**Expected Output**:
```cpp
auto student = StudentManager::create_student("Alice Johnson", 20, 3.75);
assert(StudentManager::get_name(student) == "Alice Johnson");
assert(StudentManager::get_age(student) == 20);
assert(StudentManager::get_gpa(student) == 3.75);
assert(StudentManager::format_student(student) == "Alice Johnson (20) - GPA: 3.75");
```

---

## Problem Set 2: Intermediate Applications (50 minutes)
*Focus: Practical applications combining multiple utilities*

### Problem 2.1: Configuration Parser (25 minutes)
**Learning Objective**: Combine `std::optional` and `std::variant` for robust parsing

**Problem**: Create a configuration parser that can handle different types of configuration values safely.

```cpp
using ConfigValue = std::variant<int, double, std::string, bool>;

class ConfigParser {
private:
    std::map<std::string, std::string> raw_data;
    
public:
    ConfigParser(const std::map<std::string, std::string>& data) : raw_data(data) {}
    
    // Get a configuration value, attempting to parse it as the requested type
    template<typename T>
    std::optional<T> get_value(const std::string& key);
    
    // Get a value with a default fallback
    template<typename T>
    T get_value_or(const std::string& key, const T& default_value);
    
    // Get all configuration as a map of ConfigValues
    std::map<std::string, ConfigValue> get_all_parsed();
};
```

**Test Scenario**:
```cpp
std::map<std::string, std::string> config_data = {
    {"port", "8080"},
    {"host", "localhost"},
    {"timeout", "30.5"},
    {"debug", "true"},
    {"invalid_number", "not_a_number"}
};

ConfigParser parser(config_data);

// Should successfully parse
assert(parser.get_value<int>("port") == 8080);
assert(parser.get_value<std::string>("host") == "localhost");
assert(parser.get_value<double>("timeout") == 30.5);

// Should return nullopt for invalid parsing
assert(!parser.get_value<int>("invalid_number").has_value());

// Should use defaults
assert(parser.get_value_or<int>("missing_key", 3000) == 3000);
```

---

### Problem 2.2: Performance Benchmarker (25 minutes)
**Learning Objective**: Use `std::chrono` and `std::tuple` for performance measurement

**Problem**: Create a benchmarking utility that measures function performance and returns detailed statistics.

```cpp
#include <chrono>
#include <functional>

using BenchmarkResult = std::tuple<double, double, double>; // min_time, max_time, avg_time (in milliseconds)

class Benchmarker {
public:
    // Run a function multiple times and return timing statistics
    template<typename Func>
    static BenchmarkResult benchmark(Func function, int iterations = 1000);
    
    // Format benchmark results as a string
    static std::string format_results(const BenchmarkResult& results);
    
    // Compare two benchmark results - returns optional<string> with comparison
    static std::optional<std::string> compare_results(
        const BenchmarkResult& result1, 
        const BenchmarkResult& result2,
        const std::string& name1 = "Function 1",
        const std::string& name2 = "Function 2"
    );
};
```

**Example Usage**:
```cpp
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

auto fast_results = Benchmarker::benchmark(fast_function, 1000);
auto slow_results = Benchmarker::benchmark(slow_function, 100);

std::cout << "Fast function: " << Benchmarker::format_results(fast_results) << std::endl;
std::cout << "Slow function: " << Benchmarker::format_results(slow_results) << std::endl;

auto comparison = Benchmarker::compare_results(fast_results, slow_results, "Fast", "Slow");
if (comparison) {
    std::cout << *comparison << std::endl;
}
```

---

## Problem Set 3: Integration Project (40 minutes)
*Focus: Building a complete application using all utilities*

### Problem 3.1: Data Analysis Pipeline (40 minutes)
**Learning Objective**: Integrate all utilities in a realistic data processing scenario

**Problem**: Build a data analysis pipeline that processes mixed-type data from different sources, handles errors gracefully, and provides timing information.

```cpp
// Data structures
using DataPoint = std::variant<int, double, std::string>;
using ProcessingResult = std::tuple<size_t, size_t, double>; // processed_count, error_count, processing_time_ms
using DataSummary = std::tuple<std::optional<double>, std::optional<double>, size_t>; // min, max, count

class DataAnalyzer {
private:
    std::vector<DataPoint> data;
    
public:
    // Load data from different sources
    void add_data_point(const DataPoint& point);
    void load_from_strings(const std::vector<std::string>& raw_data);
    
    // Process data with error handling and timing
    ProcessingResult process_data();
    
    // Calculate statistics for numeric data only
    DataSummary calculate_numeric_summary();
    
    // Get data points of a specific type
    template<typename T>
    std::vector<T> get_data_of_type();
    
    // Export results with timing information
    std::optional<std::string> export_summary();
};

// Helper class for timing operations
class TimedOperation {
private:
    std::chrono::steady_clock::time_point start_time;
    std::string operation_name;
    
public:
    TimedOperation(const std::string& name);
    ~TimedOperation(); // Print timing on destruction
    
    double elapsed_ms() const;
};
```

**Implementation Requirements**:

1. **Data Loading**: Handle conversion from strings to appropriate types, storing invalid conversions as error information
2. **Processing**: Time the processing operation and count successes/failures
3. **Analysis**: Calculate min/max for numeric values only, handle empty data gracefully
4. **Error Handling**: Use optional types for operations that might fail
5. **Timing**: Provide accurate timing for all major operations

**Test Scenario**:
```cpp
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

analyzer.load_from_strings(raw_data);

// Process and analyze
auto [processed, errors, time_ms] = analyzer.process_data();
auto [min_val, max_val, numeric_count] = analyzer.calculate_numeric_summary();

// Verify results
assert(processed == 7);  // All items processed
assert(errors == 0);     // No processing errors (conversion errors handled gracefully)
assert(time_ms > 0);     // Some time elapsed

assert(min_val.has_value() && *min_val == 2.71828);  // Min of numeric values
assert(max_val.has_value() && *max_val == 99);       // Max of numeric values
assert(numeric_count == 4);  // 42, 3.14159, 99, 2.71828

// Test type filtering
auto strings = analyzer.get_data_of_type<std::string>();
assert(strings.size() == 3);  // "hello", "invalid_num", "world"

// Export summary
auto summary = analyzer.export_summary();
assert(summary.has_value());
```

**Expected Summary Output**:
```
Data Analysis Summary
====================
Total data points: 7
Numeric values: 4 (min: 2.71828, max: 99)
String values: 3
Processing time: X.XX ms
```

---

## Time Verification

- **Problem Set 1**: 45 minutes (3 × 15 minutes)
- **Problem Set 2**: 50 minutes (25 + 25 minutes)  
- **Problem Set 3**: 40 minutes (1 × 40 minutes)
- **Total**: 135 minutes (2.25 hours) ✓

## Assessment Rubric

### Problem Set 1 (Foundation)
- **Excellent (90-100%)**: All functions work correctly, good use of utility types, clean code
- **Good (80-89%)**: Most functions work, minor issues with utility usage
- **Satisfactory (70-79%)**: Basic functionality present, some incorrect utility usage
- **Needs Improvement (<70%)**: Major functionality missing or incorrect

### Problem Set 2 (Intermediate)
- **Excellent (90-100%)**: Robust error handling, efficient implementation, good integration of utilities
- **Good (80-89%)**: Good functionality with minor edge case issues
- **Satisfactory (70-79%)**: Basic requirements met, limited error handling
- **Needs Improvement (<70%)**: Missing key functionality or poor utility integration

### Problem Set 3 (Integration)
- **Excellent (90-100%)**: Complete implementation, excellent error handling, clear output, efficient code
- **Good (80-89%)**: Most requirements met, good error handling, minor issues
- **Satisfactory (70-79%)**: Core functionality present, basic error handling
- **Needs Improvement (<70%)**: Incomplete implementation or major functionality issues

## Compilation Instructions

**Choose your workflow:**

**Docker/Command Line:**
```bash
g++ -std=c++17 -Wall -Wextra -g -o utilities_program program.cpp
```

**VS Code (any workflow):**
- Press `Ctrl+Shift+B` (or `Cmd+Shift+B` on macOS)
- Or use Terminal → Run Build Task

**VS Code Utility Types Debugging Tips:**
- Use Variables panel to see optional/variant internal state
- Watch tuple unpacking and structured bindings
- Debug std::chrono time calculations step-by-step
- Monitor variant type changes during execution

---

## Connections to Future Learning
These utilities prepare students for:
- Advanced template programming
- Modern C++ idioms and patterns
- Error handling strategies
- Performance measurement and optimization
- Data processing applications