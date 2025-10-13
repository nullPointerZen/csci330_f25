#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <cmath>

// Function pointer examples
double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) {
    if (b == 0.0) {
        std::cout << "Error: Division by zero!";
        return 0.0;
    }
    return a / b;
}

void calculator_demo() {
    std::cout << "=== Function Pointer Calculator ===\n";

    double (*operations[])(double, double) = {add, subtract, multiply, divide};
    const char* op_names[] = {"Add", "Subtract", "Multiply", "Divide"};

    double a = 15.0, b = 3.0;
    std::cout << "Numbers: " << a << " and " << b << "\n\n";

    for (int i = 0; i < 4; ++i) {
        std::cout << op_names[i] << ": " << operations[i](a, b) << "\n";
    }
}

// Event system with callbacks
typedef void (*EventHandler)(const std::string& event_data);

void log_handler(const std::string& event_data) {
    std::cout << "[LOG] " << event_data << "\n";
}

void alert_handler(const std::string& event_data) {
    std::cout << "[ALERT] Critical event: " << event_data << "\n";
}

void debug_handler(const std::string& event_data) {
    std::cout << "[DEBUG] Event details: " << event_data << "\n";
}

class EventSystem {
private:
    std::vector<EventHandler> handlers;

public:
    void register_handler(EventHandler handler) {
        handlers.push_back(handler);
    }

    void fire_event(const std::string& event_data) {
        for (auto handler : handlers) {
            handler(event_data);
        }
    }

    size_t get_handler_count() const {
        return handlers.size();
    }
};

// Comparison functions for sorting
bool ascending(int a, int b) { return a < b; }
bool descending(int a, int b) { return a > b; }

typedef bool (*Comparator)(int a, int b);

void sort_with_comparator(std::vector<int>& data, Comparator comp) {
    // Simple bubble sort
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data.size() - 1 - i; ++j) {
            if (!comp(data[j], data[j + 1])) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

void print_vector(const std::vector<int>& data) {
    for (int n : data) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

// Lambda examples with STL algorithms
struct Student {
    std::string name;
    int grade;

    Student(const std::string& n, int g) : name(n), grade(g) {}
};

void lambda_stl_demo() {
    std::cout << "\n=== Lambda with STL Algorithms ===\n";

    std::vector<Student> students = {
        {"Alice", 92}, {"Bob", 87}, {"Charlie", 78},
        {"Diana", 95}, {"Eve", 82}, {"Frank", 69}
    };

    std::cout << "All students:\n";
    std::for_each(students.begin(), students.end(),
        [](const Student& s) {
            std::cout << s.name << ": " << s.grade << "\n";
        });

    std::cout << "\nHonor roll students (grade >= 90):\n";
    std::for_each(students.begin(), students.end(),
        [](const Student& s) {
            if (s.grade >= 90) {
                std::cout << s.name << ": " << s.grade << "\n";
            }
        });

    // Count passing students
    int passing_count = std::count_if(students.begin(), students.end(),
        [](const Student& s) { return s.grade >= 70; });

    // Calculate average
    double total = 0.0;
    std::for_each(students.begin(), students.end(),
        [&total](const Student& s) { total += s.grade; });
    double average = total / students.size();

    // Apply curve
    int curve_points = 5;
    std::for_each(students.begin(), students.end(),
        [curve_points](Student& s) { s.grade += curve_points; });

    std::cout << "\nAfter applying " << curve_points << " point curve:\n";
    std::for_each(students.begin(), students.end(),
        [](const Student& s) {
            std::cout << s.name << ": " << s.grade << "\n";
        });

    std::cout << "\nStatistics:\n";
    std::cout << "Passing students: " << passing_count << "\n";
    std::cout << "Original average: " << average << "\n";
}

// Advanced lambda captures
class DataProcessor {
private:
    std::string processor_name;
    int processing_count;

public:
    DataProcessor(const std::string& name)
        : processor_name(name), processing_count(0) {}

    auto create_filter(int threshold) {
        return [this, threshold](int value) {
            processing_count++;
            return value > threshold;
        };
    }

    auto create_transformer(int multiplier, int offset) {
        return [multiplier, offset](int value) {
            return value * multiplier + offset;
        };
    }

    auto create_accumulator() {
        return [sum = 0](int value) mutable {
            sum += value;
            return sum;
        };
    }

    void process_data(const std::vector<int>& input_data) {
        std::cout << "Processing with " << processor_name << ":\n";

        auto filter = create_filter(10);
        auto transform = create_transformer(2, 5);
        auto accumulate = create_accumulator();

        int total = 0;
        for (int value : input_data) {
            if (filter(value)) {
                int transformed = transform(value);
                total = accumulate(transformed);
                std::cout << value << " -> " << transformed << " (running total: " << total << ")\n";
            }
        }

        std::cout << "Items processed: " << processing_count << "\n";
    }
};

// Generic lambdas
void generic_lambda_demo() {
    std::cout << "\n=== Generic Lambda Demo ===\n";

    auto printer = [](const auto& item, const std::string& prefix = "") {
        std::cout << prefix << item << " ";
    };

    auto less_than = [](const auto& a, const auto& b) {
        return a < b;
    };

    auto doubler = [](auto item) {
        return item + item;  // Works for numbers (addition) and strings (concatenation)
    };

    // Test with integers
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Original numbers: ";
    std::for_each(numbers.begin(), numbers.end(),
                  [&printer](const auto& n) { printer(n, ""); });
    std::cout << "\n";

    std::transform(numbers.begin(), numbers.end(), numbers.begin(), doubler);
    std::cout << "Doubled numbers: ";
    std::for_each(numbers.begin(), numbers.end(),
                  [&printer](const auto& n) { printer(n, ""); });
    std::cout << "\n";

    // Test with strings
    std::vector<std::string> words = {"hello", "world", "cpp", "lambda"};
    std::cout << "Original words: ";
    std::for_each(words.begin(), words.end(),
                  [&printer](const auto& w) { printer(w, ""); });
    std::cout << "\n";

    std::transform(words.begin(), words.end(), words.begin(), doubler);
    std::cout << "Doubled words: ";
    std::for_each(words.begin(), words.end(),
                  [&printer](const auto& w) { printer(w, ""); });
    std::cout << "\n";

    // Test comparisons
    std::cout << "5 < 10: " << less_than(5, 10) << "\n";
    std::cout << "hello < world: " << less_than(std::string("hello"), std::string("world")) << "\n";
}

// Function objects (functors)
class StatisticsAccumulator {
private:
    int count;
    double sum;
    double sum_squares;
    double min_val;
    double max_val;
    bool first_value;

public:
    StatisticsAccumulator() : count(0), sum(0.0), sum_squares(0.0),
                             min_val(0.0), max_val(0.0), first_value(true) {}

    void operator()(double value) {
        if (first_value) {
            min_val = max_val = value;
            first_value = false;
        } else {
            if (value < min_val) min_val = value;
            if (value > max_val) max_val = value;
        }

        count++;
        sum += value;
        sum_squares += value * value;
    }

    double get_mean() const {
        return count > 0 ? sum / count : 0.0;
    }

    double get_variance() const {
        if (count <= 1) return 0.0;
        double mean = get_mean();
        return (sum_squares - count * mean * mean) / (count - 1);
    }

    double get_std_dev() const {
        return std::sqrt(get_variance());
    }

    double get_min() const { return min_val; }
    double get_max() const { return max_val; }
    int get_count() const { return count; }

    void reset() {
        count = 0;
        sum = sum_squares = min_val = max_val = 0.0;
        first_value = true;
    }
};

// Integration project: Data Pipeline
typedef double (*SimpleTransform)(double);

double square(double x) { return x * x; }
double cube(double x) { return x * x * x; }
double negate(double x) { return -x; }

class ScaleAndOffset {
private:
    double scale, offset;

public:
    ScaleAndOffset(double s, double o) : scale(s), offset(o) {}
    double operator()(double x) const { return x * scale + offset; }
};

class DataPipeline {
private:
    std::vector<std::function<double(double)>> stages;
    std::string pipeline_name;

public:
    DataPipeline(const std::string& name) : pipeline_name(name) {}

    void add_stage(std::function<double(double)> stage) {
        stages.push_back(stage);
    }

    double process(double input) {
        double result = input;
        for (auto& stage : stages) {
            result = stage(result);
        }
        return result;
    }

    std::vector<double> process_batch(const std::vector<double>& inputs) {
        std::vector<double> results;
        for (double input : inputs) {
            results.push_back(process(input));
        }
        return results;
    }

    void print_info() const {
        std::cout << "Pipeline '" << pipeline_name
                  << "' has " << stages.size() << " stages\n";
    }
};

int main() {
    calculator_demo();

    std::cout << "\n=== Event System Demo ===\n";
    EventSystem event_system;
    event_system.register_handler(log_handler);
    event_system.register_handler(alert_handler);
    event_system.register_handler(debug_handler);

    std::cout << "Handlers registered: " << event_system.get_handler_count() << "\n\n";

    std::cout << "Firing event: \"User logged in\"\n";
    event_system.fire_event("User logged in");

    std::cout << "\n=== Sorting Demo ===\n";
    std::vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};

    std::cout << "Original: ";
    print_vector(numbers);

    auto ascending_copy = numbers;
    sort_with_comparator(ascending_copy, ascending);
    std::cout << "Ascending: ";
    print_vector(ascending_copy);

    auto descending_copy = numbers;
    sort_with_comparator(descending_copy, descending);
    std::cout << "Descending: ";
    print_vector(descending_copy);

    lambda_stl_demo();

    std::cout << "\n=== Advanced Lambda Captures Demo ===\n";
    DataProcessor processor("NumberCruncher");
    std::vector<int> test_data = {5, 15, 8, 22, 3, 18, 12, 7};
    processor.process_data(test_data);

    generic_lambda_demo();

    std::cout << "\n=== Function Object Demo ===\n";
    std::vector<double> data = {23.5, 45.2, 12.8, 67.1, 34.6, 89.3, 56.7};

    StatisticsAccumulator stats;
    std::for_each(data.begin(), data.end(), std::ref(stats));

    std::cout << "Statistics for " << stats.get_count() << " values:\n";
    std::cout << "Mean: " << stats.get_mean() << "\n";
    std::cout << "Min: " << stats.get_min() << "\n";
    std::cout << "Max: " << stats.get_max() << "\n";
    std::cout << "Std Dev: " << stats.get_std_dev() << "\n";

    std::cout << "\n=== Data Pipeline Demo ===\n";
    std::vector<double> pipeline_data = {1.0, 2.0, 3.0, 4.0, 5.0};

    DataPipeline pipeline("MathProcessor");
    pipeline.add_stage(square);  // Function pointer

    double multiplier = 0.5;
    pipeline.add_stage([multiplier](double x) { return x * multiplier; });  // Lambda

    pipeline.add_stage(ScaleAndOffset(2.0, 10.0));  // Function object

    pipeline.add_stage([](auto x) { return x < 0 ? 0 : x; });  // Generic lambda

    pipeline.print_info();

    std::cout << "\nOriginal -> Processed:\n";
    for (double value : pipeline_data) {
        double result = pipeline.process(value);
        std::cout << value << " -> " << result << "\n";
    }

    return 0;
}