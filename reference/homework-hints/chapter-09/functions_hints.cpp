#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <numeric>
#include <cmath>

// =============================================================================
// PROBLEM SET 1: FUNCTION POINTERS AND CALLBACKS
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 1.1: Calculator with Function Pointers
// -----------------------------------------------------------------------------
// Basic arithmetic operations that can be called through function pointers

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    // Always check for division by zero
    if (b == 0.0) {
        std::cout << "Error: Division by zero!\n";
        return 0.0;
    }
    return a / b;
}

void demo_calculator() {
    std::cout << "\n=== Problem 1.1: Calculator with Function Pointers ===\n\n";

    // Create array of function pointers
    // Syntax: return_type (*pointer_name)(param_types)
    double (*operations[])(double, double) = {add, subtract, multiply, divide};
    const char* op_names[] = {"Add", "Subtract", "Multiply", "Divide"};
    const char* op_symbols[] = {"+", "-", "*", "/"};

    // Test with some sample operations
    double a = 15.0, b = 3.0;

    std::cout << "Testing calculator with a = " << a << ", b = " << b << "\n\n";

    for (int i = 0; i < 4; i++) {
        std::cout << i + 1 << ". " << op_names[i] << ": ";
        double result = operations[i](a, b);  // Call through function pointer
        if (i != 3 || b != 0.0) {  // Skip printing result for division by zero
            std::cout << a << " " << op_symbols[i] << " " << b << " = " << result << "\n";
        }
    }

    // Test division by zero
    std::cout << "\nTesting division by zero:\n";
    double zero_test = divide(10.0, 0.0);
}

// -----------------------------------------------------------------------------
// Problem 1.2: Event System with Callbacks
// -----------------------------------------------------------------------------
// Demonstrates callback pattern using function pointers

// Event handler function type
typedef void (*EventHandler)(const std::string& event_data);

// Different types of event handlers
void log_handler(const std::string& event_data) {
    std::cout << "[LOG] " << event_data << "\n";
}

void alert_handler(const std::string& event_data) {
    std::cout << "[ALERT] Critical event: " << event_data << "\n";
}

void debug_handler(const std::string& event_data) {
    std::cout << "[DEBUG] Event details: " << event_data << "\n";
}

// Simple event system that manages multiple callbacks
class EventSystem {
private:
    std::vector<EventHandler> handlers;

public:
    // Register a new event handler
    void register_handler(EventHandler handler) {
        handlers.push_back(handler);
    }

    // Fire an event to all registered handlers
    void fire_event(const std::string& event_data) {
        for (EventHandler handler : handlers) {
            handler(event_data);  // Call each handler
        }
    }

    // Get number of registered handlers
    size_t get_handler_count() const {
        return handlers.size();
    }
};

void demo_event_system() {
    std::cout << "\n=== Problem 1.2: Event System with Callbacks ===\n\n";

    EventSystem event_system;

    // Register multiple handlers
    std::cout << "Registering event handlers...\n";
    event_system.register_handler(log_handler);
    event_system.register_handler(alert_handler);
    event_system.register_handler(debug_handler);

    std::cout << "Handlers registered: " << event_system.get_handler_count() << "\n\n";

    // Fire some test events
    std::cout << "Firing event: \"User logged in\"\n";
    event_system.fire_event("User logged in");

    std::cout << "\nFiring event: \"File uploaded\"\n";
    event_system.fire_event("File uploaded");
}

// -----------------------------------------------------------------------------
// Problem 1.3: Sorting with Custom Comparators
// -----------------------------------------------------------------------------
// Use function pointers for customizable comparison strategies

// Comparison function type - returns true if first should come before second
typedef bool (*Comparator)(int a, int b);

bool ascending(int a, int b) {
    return a < b;
}

bool descending(int a, int b) {
    return a > b;
}

// Simple bubble sort that accepts a comparison function
void sort_with_comparator(std::vector<int>& data, Comparator comp) {
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Use the provided comparator to determine order
            if (!comp(data[j], data[j + 1])) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

void print_vector(const std::vector<int>& data, const std::string& label = "") {
    if (!label.empty()) {
        std::cout << label << ": ";
    }
    for (int n : data) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

void demo_sorting() {
    std::cout << "\n=== Problem 1.3: Sorting with Custom Comparators ===\n\n";

    std::vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};

    print_vector(numbers, "Original");

    // Sort ascending using function pointer
    std::vector<int> ascending_copy = numbers;
    sort_with_comparator(ascending_copy, ascending);
    print_vector(ascending_copy, "Ascending");

    // Sort descending using function pointer
    std::vector<int> descending_copy = numbers;
    sort_with_comparator(descending_copy, descending);
    print_vector(descending_copy, "Descending");
}

// =============================================================================
// PROBLEM SET 2: LAMBDA EXPRESSIONS AND CAPTURES
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 2.1: STL Algorithm Integration
// -----------------------------------------------------------------------------
// Use lambdas with standard algorithms for data processing

struct Student {
    std::string name;
    int grade;

    Student(const std::string& n, int g) : name(n), grade(g) {}
};

void demo_stl_lambdas() {
    std::cout << "\n=== Problem 2.1: STL Algorithm Integration ===\n\n";

    std::vector<Student> students = {
        {"Alice", 92}, {"Bob", 87}, {"Charlie", 78},
        {"Diana", 95}, {"Eve", 82}, {"Frank", 69}
    };

    std::cout << "All students:\n";
    // Use std::for_each with lambda to print all students
    std::for_each(students.begin(), students.end(),
                  [](const Student& s) {
                      std::cout << s.name << ": " << s.grade << "\n";
                  });

    std::cout << "\nHonor roll students (grade >= 90):\n";
    // Use lambda as predicate for filtering
    std::for_each(students.begin(), students.end(),
                  [](const Student& s) {
                      if (s.grade >= 90) {
                          std::cout << s.name << ": " << s.grade << "\n";
                      }
                  });

    // Count students passing (grade >= 70) using std::count_if
    int passing_count = std::count_if(students.begin(), students.end(),
                                      [](const Student& s) {
                                          return s.grade >= 70;
                                      });

    // Calculate average grade using std::accumulate and lambda
    int total = std::accumulate(students.begin(), students.end(), 0,
                               [](int sum, const Student& s) {
                                   return sum + s.grade;
                               });
    double average = static_cast<double>(total) / students.size();

    // Apply curve (+5 points) using capture by value
    int curve_points = 5;
    std::cout << "\nAfter applying " << curve_points << " point curve:\n";
    std::for_each(students.begin(), students.end(),
                  [curve_points](Student& s) {  // Capture curve_points by value
                      s.grade += curve_points;
                      // Cap at 100
                      if (s.grade > 100) s.grade = 100;
                      std::cout << s.name << ": " << s.grade << "\n";
                  });

    std::cout << "\nStatistics:\n";
    std::cout << "Passing students: " << passing_count << "\n";
    std::cout << "Average grade (before curve): " << average << "\n";
}

// -----------------------------------------------------------------------------
// Problem 2.2: Advanced Lambda Captures
// -----------------------------------------------------------------------------
// Demonstrates different capture modes and their uses

class DataProcessor {
private:
    std::string processor_name;
    int processing_count;
    std::vector<int> results;

public:
    DataProcessor(const std::string& name)
        : processor_name(name), processing_count(0) {}

    // Create a lambda that filters values above threshold
    // Demonstrates mixed captures: by value and by reference
    auto create_filter(int threshold) {
        // Capture 'this' to access member variables
        // Capture threshold by value
        return [this, threshold](int value) {
            processing_count++;  // Modify member variable through 'this'
            return value > threshold;
        };
    }

    // Create a lambda factory for transformations
    // Demonstrates init captures (C++14 feature)
    auto create_transformer(int multiplier, int offset) {
        // Init captures: create new variables in the lambda's closure
        return [mult = multiplier, off = offset](int value) {
            return value * mult + off;
        };
    }

    // Create a stateful lambda for accumulation
    // Demonstrates mutable lambda with capture by value
    auto create_accumulator() {
        // Capture sum by value but make it mutable
        return [sum = 0](int value) mutable {
            sum += value;
            return sum;
        };
    }

    void process_data(const std::vector<int>& input_data) {
        std::cout << "Processing with " << processor_name << ":\n";

        // Use the filter lambda
        auto filter = create_filter(10);
        std::vector<int> filtered;
        std::copy_if(input_data.begin(), input_data.end(),
                    std::back_inserter(filtered), filter);

        std::cout << "Filtered values (> 10): ";
        for (int v : filtered) std::cout << v << " ";
        std::cout << "\n";

        // Use the transformer lambda
        auto transform = create_transformer(2, 5);
        std::vector<int> transformed;
        std::transform(filtered.begin(), filtered.end(),
                      std::back_inserter(transformed), transform);

        std::cout << "Transformed values (x*2+5): ";
        for (int v : transformed) std::cout << v << " ";
        std::cout << "\n";

        // Use the accumulator lambda
        auto accumulate = create_accumulator();
        std::cout << "Running totals: ";
        for (int v : transformed) {
            std::cout << accumulate(v) << " ";
        }
        std::cout << "\n";

        std::cout << "Items processed: " << processing_count << "\n";
    }

    // PROBLEMATIC: Returns lambda with dangling reference
    auto create_problematic_lambda() {
        int local_var = 42;
        // BAD: Captures local variable by reference
        // local_var will be destroyed when function returns!
        return [&local_var]() { return local_var; };
    }

    // SAFE: Returns lambda with value capture
    auto create_safe_lambda() {
        int local_var = 42;
        // GOOD: Captures local variable by value
        // Value is copied into lambda's closure
        return [local_var]() { return local_var; };
    }
};

void demo_lambda_captures() {
    std::cout << "\n=== Problem 2.2: Advanced Lambda Captures ===\n\n";

    DataProcessor processor("NumberCruncher");
    std::vector<int> test_data = {5, 15, 8, 22, 3, 18, 12, 7};

    processor.process_data(test_data);

    // Demonstrate the problematic vs safe lambda
    std::cout << "\nTesting lambda lifetime:\n";

    auto safe_lambda = processor.create_safe_lambda();
    std::cout << "Safe lambda (capture by value): " << safe_lambda() << "\n";

    // Note: Calling problematic_lambda would cause undefined behavior
    // We demonstrate it exists but don't call it
    std::cout << "Problematic lambda demonstrates why reference captures "
              << "of local variables are dangerous!\n";
}

// -----------------------------------------------------------------------------
// Problem 2.3: Generic Lambdas and Function Templates
// -----------------------------------------------------------------------------
// Use generic lambdas (auto parameters) for flexible, reusable code

void demo_generic_lambdas() {
    std::cout << "\n=== Problem 2.3: Generic Lambdas ===\n\n";

    // Generic lambda for printing with custom format
    auto printer = [](const auto& item, const std::string& prefix = "") {
        std::cout << prefix << item << " ";
    };

    // Generic lambda for comparison
    auto less_than = [](const auto& a, const auto& b) {
        return a < b;
    };

    // Generic lambda for transformation
    // Works differently for numbers (doubles) and strings (concatenates)
    auto doubler = [](auto item) -> decltype(item) {
        return item + item;  // + means addition for numbers, concatenation for strings
    };

    // Test with integers
    std::vector<int> numbers = {5, 2, 8, 1, 9};
    std::cout << "Original numbers: ";
    std::for_each(numbers.begin(), numbers.end(),
                  [&printer](const auto& n) { printer(n, ""); });
    std::cout << "\n";

    // Use doubler with transform on numbers
    std::vector<int> doubled_numbers;
    std::transform(numbers.begin(), numbers.end(),
                  std::back_inserter(doubled_numbers), doubler);
    std::cout << "Doubled numbers: ";
    for (int v : doubled_numbers) std::cout << v << " ";
    std::cout << "\n";

    // Test with strings
    std::vector<std::string> words = {"hello", "world", "cpp", "lambda"};
    std::cout << "\nOriginal words: ";
    for (const auto& w : words) printer(w, "");
    std::cout << "\n";

    // Use doubler with transform on strings
    std::vector<std::string> doubled_words;
    std::transform(words.begin(), words.end(),
                  std::back_inserter(doubled_words), doubler);
    std::cout << "Doubled words: ";
    for (const auto& w : doubled_words) printer(w, "");
    std::cout << "\n";

    // Test comparison with different types
    std::cout << "\n5 < 10: " << less_than(5, 10) << "\n";
    std::cout << "hello < world: " << less_than(std::string("hello"), std::string("world")) << "\n";

    // Use generic comparison with std::sort
    std::vector<int> sort_numbers = {64, 34, 25, 12, 22};
    std::sort(sort_numbers.begin(), sort_numbers.end(), less_than);
    std::cout << "Sorted numbers: ";
    for (int v : sort_numbers) std::cout << v << " ";
    std::cout << "\n";

    std::vector<std::string> sort_words = {"delta", "alpha", "charlie", "bravo"};
    std::sort(sort_words.begin(), sort_words.end(), less_than);
    std::cout << "Sorted words: ";
    for (const auto& w : sort_words) std::cout << w << " ";
    std::cout << "\n";
}

// =============================================================================
// PROBLEM SET 3: FUNCTION OBJECTS AND INTEGRATION
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 3.1: Custom Function Objects (Functors)
// -----------------------------------------------------------------------------
// Stateful function objects for scenarios where lambdas aren't sufficient

// Statistics accumulator function object
class StatisticsAccumulator {
private:
    int count;
    double sum;
    double sum_squares;
    double min_val;
    double max_val;

public:
    StatisticsAccumulator()
        : count(0), sum(0.0), sum_squares(0.0),
          min_val(std::numeric_limits<double>::max()),
          max_val(std::numeric_limits<double>::lowest()) {}

    // Function call operator - makes this object callable like a function
    void operator()(double value) {
        count++;
        sum += value;
        sum_squares += value * value;
        if (value < min_val) min_val = value;
        if (value > max_val) max_val = value;
    }

    // Getter methods to access accumulated statistics
    double get_mean() const {
        return count > 0 ? sum / count : 0.0;
    }

    double get_variance() const {
        if (count < 2) return 0.0;
        double mean = get_mean();
        return (sum_squares / count) - (mean * mean);
    }

    double get_std_dev() const {
        return std::sqrt(get_variance());
    }

    double get_min() const { return min_val; }
    double get_max() const { return max_val; }
    int get_count() const { return count; }

    void reset() {
        count = 0;
        sum = 0.0;
        sum_squares = 0.0;
        min_val = std::numeric_limits<double>::max();
        max_val = std::numeric_limits<double>::lowest();
    }
};

// Histogram builder function object
class HistogramBuilder {
private:
    double min_value;
    double max_value;
    int num_bins;
    std::vector<int> bins;
    double bin_width;

public:
    HistogramBuilder(double min_val, double max_val, int num_bins_)
        : min_value(min_val), max_value(max_val), num_bins(num_bins_),
          bins(num_bins_, 0) {
        bin_width = (max_value - min_value) / num_bins;
    }

    // Function call operator - adds value to appropriate bin
    void operator()(double value) {
        if (value < min_value || value > max_value) return;

        int bin_index = static_cast<int>((value - min_value) / bin_width);
        if (bin_index >= num_bins) bin_index = num_bins - 1;
        bins[bin_index]++;
    }

    void print_histogram() const {
        int max_count = *std::max_element(bins.begin(), bins.end());

        for (int i = 0; i < num_bins; i++) {
            double range_start = min_value + i * bin_width;
            double range_end = range_start + bin_width;

            printf("[%6.1f-%6.1f]: ", range_start, range_end);

            // Print bar proportional to count
            int bar_length = max_count > 0 ? (bins[i] * 40) / max_count : 0;
            for (int j = 0; j < bar_length; j++) {
                std::cout << "█";
            }
            std::cout << " (" << bins[i] << ")\n";
        }
    }
};

void demo_function_objects() {
    std::cout << "\n=== Problem 3.1: Custom Function Objects ===\n\n";

    std::vector<double> data = {
        23.5, 45.2, 12.8, 67.1, 34.6, 89.3, 56.7, 78.9,
        43.2, 29.1, 65.4, 87.6, 54.3, 32.8, 76.5
    };

    std::cout << "Processing " << data.size() << " data points\n\n";

    // Use StatisticsAccumulator with std::for_each
    // std::for_each returns a copy of the functor with accumulated state
    StatisticsAccumulator stats = std::for_each(data.begin(), data.end(),
                                                StatisticsAccumulator());

    std::cout << "Statistics:\n";
    std::cout << "  Count: " << stats.get_count() << "\n";
    std::cout << "  Mean: " << stats.get_mean() << "\n";
    std::cout << "  Std Dev: " << stats.get_std_dev() << "\n";
    std::cout << "  Min: " << stats.get_min() << "\n";
    std::cout << "  Max: " << stats.get_max() << "\n";

    // Use HistogramBuilder
    HistogramBuilder histogram(0, 100, 10);
    std::for_each(data.begin(), data.end(), std::ref(histogram));

    std::cout << "\nHistogram:\n";
    histogram.print_histogram();
}

// -----------------------------------------------------------------------------
// Problem 3.2: Complete Function Integration Project
// -----------------------------------------------------------------------------
// Integrate all function types using std::function for type erasure

// Function pointer type for simple transformations
typedef double (*SimpleTransform)(double);

// Simple transform functions
double square(double x) { return x * x; }
double cube(double x) { return x * x * x; }
double negate(double x) { return -x; }

// Function object for scaling and offsetting
class ScaleAndOffset {
private:
    double scale, offset;

public:
    ScaleAndOffset(double s, double o) : scale(s), offset(o) {}
    double operator()(double x) const { return x * scale + offset; }
};

// Data processing pipeline using std::function
class DataPipeline {
private:
    std::vector<std::function<double(double)>> stages;
    std::string pipeline_name;

public:
    DataPipeline(const std::string& name) : pipeline_name(name) {}

    // Add a processing stage - accepts any callable
    void add_stage(std::function<double(double)> stage) {
        stages.push_back(stage);
    }

    // Process a single value through all stages
    double process(double input) {
        double result = input;
        for (const auto& stage : stages) {
            result = stage(result);
        }
        return result;
    }

    // Process a vector of values
    std::vector<double> process_batch(const std::vector<double>& inputs) {
        std::vector<double> results;
        std::transform(inputs.begin(), inputs.end(),
                      std::back_inserter(results),
                      [this](double value) { return process(value); });
        return results;
    }

    void print_info() const {
        std::cout << "Pipeline '" << pipeline_name
                  << "' has " << stages.size() << " stages\n";
    }
};

void demo_integration_project() {
    std::cout << "\n=== Problem 3.2: Complete Function Integration Project ===\n\n";

    std::vector<double> test_data = {1.0, 2.0, 3.0, 4.0, 5.0};

    // Create pipeline and add different types of stages
    DataPipeline pipeline("MathProcessor");

    // Stage 1: Function pointer - square the value
    pipeline.add_stage(square);

    // Stage 2: Lambda with capture - multiply by 0.5
    double multiplier = 0.5;
    pipeline.add_stage([multiplier](double x) { return x * multiplier; });

    // Stage 3: Function object - scale by 2 and add 10
    pipeline.add_stage(ScaleAndOffset(2.0, 10.0));

    // Stage 4: Generic lambda - ReLU activation (clip at 0)
    pipeline.add_stage([](auto x) { return x < 0 ? 0.0 : x; });

    pipeline.print_info();

    std::cout << "\nProcessing data through pipeline:\n";
    std::cout << "Stages: square -> *0.5 -> *2+10 -> ReLU\n\n";

    std::cout << "Original -> Processed:\n";
    for (double value : test_data) {
        double result = pipeline.process(value);
        printf("%.1f -> %.1f\n", value, result);
    }

    // Demonstrate batch processing
    std::cout << "\nBatch processing:\n";
    auto results = pipeline.process_batch(test_data);
    std::cout << "Results: ";
    for (double r : results) {
        printf("%.1f ", r);
    }
    std::cout << "\n";
}

// =============================================================================
// MAIN FUNCTION - Demonstrates All Concepts
// =============================================================================

int main() {
    std::cout << "========================================\n";
    std::cout << "   CHAPTER 9: Functions - Complete Hints\n";
    std::cout << "========================================\n";

    // Problem Set 1: Function Pointers and Callbacks
    demo_calculator();
    demo_event_system();
    demo_sorting();

    // Problem Set 2: Lambda Expressions and Captures
    demo_stl_lambdas();
    demo_lambda_captures();
    demo_generic_lambdas();

    // Problem Set 3: Function Objects and Integration
    demo_function_objects();
    demo_integration_project();

    std::cout << "\n========================================\n";
    std::cout << "   All demonstrations complete!\n";
    std::cout << "========================================\n\n";

    return 0;
}

/*
================================================================================
KEY LEARNING POINTS
================================================================================

1. FUNCTION POINTERS
   - Syntax: return_type (*pointer_name)(param_types)
   - Can store addresses of functions and call them indirectly
   - Useful for callbacks and strategy patterns
   - typedef makes syntax cleaner

2. LAMBDA EXPRESSIONS
   - Syntax: [captures](parameters) { body }
   - Inline, anonymous functions
   - Capture modes:
     * [=] - capture all by value
     * [&] - capture all by reference
     * [x, &y] - mixed captures
     * [this] - capture member variables
   - mutable keyword allows modifying captured values
   - Generic lambdas use 'auto' parameters (C++14)

3. FUNCTION OBJECTS (FUNCTORS)
   - Classes with operator() overloaded
   - Can maintain state between calls
   - Better than lambdas when you need:
     * Multiple member functions
     * Complex state management
     * Named, reusable components

4. std::function
   - Type-erased wrapper for any callable
   - Can store functions, lambdas, functors, member functions
   - Enables heterogeneous collections of callables
   - Small overhead from type erasure

5. WHEN TO USE EACH
   - Function pointers: Simple callbacks, C compatibility
   - Lambdas: One-off operations, STL algorithms, modern C++
   - Functors: Stateful operations, complex logic
   - std::function: Type erasure, storing different callable types

6. BEST PRACTICES
   - Prefer lambdas for simple, local operations
   - Use function objects for complex, reusable logic
   - Be careful with reference captures and lifetimes
   - Use std::function when you need type erasure
   - Generic lambdas provide template-like behavior without complexity

================================================================================
COMPILATION AND TESTING
================================================================================

To compile and run this file:

    g++ -std=c++14 -Wall -Wextra -o functions_hints functions_hints.cpp
    ./functions_hints

Expected output shows all demonstrations working correctly with clear
explanations of each concept.

Students should study each section to understand:
- How to declare and use each function type
- When each approach is most appropriate
- Common pitfalls and how to avoid them
- Integration patterns for real-world applications

================================================================================
*/
