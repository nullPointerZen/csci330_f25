#include <iostream>
#include <optional>
#include <variant>
#include <tuple>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <functional>
#include <sstream>

// Safe String Operations using std::optional
class SafeStringProcessor {
public:
    static std::optional<char> char_at(const std::string& str, size_t index) {
        if (index >= str.length()) {
            return std::nullopt;
        }
        return str[index];
    }

    static std::optional<size_t> find_char(const std::string& str, char c) {
        size_t pos = str.find(c);
        if (pos == std::string::npos) {
            return std::nullopt;
        }
        return pos;
    }

    static std::optional<int> to_int(const std::string& str) {
        try {
            size_t pos;
            int result = std::stoi(str, &pos);
            // Check if entire string was converted
            if (pos == str.length()) {
                return result;
            }
        } catch (const std::exception&) {
            // Conversion failed
        }
        return std::nullopt;
    }
};

// Data Processor using std::variant
using DataValue = std::variant<int, double, std::string>;

class DataProcessor {
public:
    static std::string describe(const DataValue& data) {
        return std::visit([](const auto& value) -> std::string {
            using T = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<T, int>) {
                return "Integer: " + std::to_string(value);
            } else if constexpr (std::is_same_v<T, double>) {
                return "Double: " + std::to_string(value);
            } else if constexpr (std::is_same_v<T, std::string>) {
                return "String: " + value;
            }
        }, data);
    }

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
};

// Student Record System using std::tuple
using StudentRecord = std::tuple<std::string, int, double>; // name, age, gpa

class StudentManager {
public:
    static StudentRecord create_student(const std::string& name, int age, double gpa) {
        return std::make_tuple(name, age, gpa);
    }

    static std::string get_name(const StudentRecord& student) {
        return std::get<0>(student);
    }

    static int get_age(const StudentRecord& student) {
        return std::get<1>(student);
    }

    static double get_gpa(const StudentRecord& student) {
        return std::get<2>(student);
    }

    static std::string format_student(const StudentRecord& student) {
        auto [name, age, gpa] = student;  // Structured binding
        return name + " (" + std::to_string(age) + ") - GPA: " + std::to_string(gpa);
    }
};

// Configuration Parser combining std::optional and std::variant
using ConfigValue = std::variant<int, double, std::string, bool>;

class ConfigParser {
private:
    std::map<std::string, std::string> raw_data;

public:
    ConfigParser(const std::map<std::string, std::string>& data) : raw_data(data) {}

    template<typename T>
    std::optional<T> get_value(const std::string& key) {
        auto it = raw_data.find(key);
        if (it == raw_data.end()) {
            return std::nullopt;
        }

        const std::string& value = it->second;

        if constexpr (std::is_same_v<T, int>) {
            try {
                return std::stoi(value);
            } catch (...) {
                return std::nullopt;
            }
        } else if constexpr (std::is_same_v<T, double>) {
            try {
                return std::stod(value);
            } catch (...) {
                return std::nullopt;
            }
        } else if constexpr (std::is_same_v<T, std::string>) {
            return value;
        } else if constexpr (std::is_same_v<T, bool>) {
            if (value == "true" || value == "1") return true;
            if (value == "false" || value == "0") return false;
            return std::nullopt;
        }
    }

    template<typename T>
    T get_value_or(const std::string& key, const T& default_value) {
        auto result = get_value<T>(key);
        return result.value_or(default_value);
    }

    std::map<std::string, ConfigValue> get_all_parsed() {
        std::map<std::string, ConfigValue> result;
        for (const auto& [key, value] : raw_data) {
            // Try to parse as different types
            if (auto int_val = get_value<int>(key)) {
                result[key] = *int_val;
            } else if (auto double_val = get_value<double>(key)) {
                result[key] = *double_val;
            } else if (auto bool_val = get_value<bool>(key)) {
                result[key] = *bool_val;
            } else {
                result[key] = value;  // Store as string
            }
        }
        return result;
    }
};

// Performance Benchmarker using std::chrono and std::tuple
using BenchmarkResult = std::tuple<double, double, double>; // min_time, max_time, avg_time

class Benchmarker {
public:
    template<typename Func>
    static BenchmarkResult benchmark(Func function, int iterations = 1000) {
        std::vector<double> times;
        times.reserve(iterations);

        for (int i = 0; i < iterations; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            function();
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            times.push_back(duration.count() / 1000000.0); // Convert to milliseconds
        }

        auto min_time = *std::min_element(times.begin(), times.end());
        auto max_time = *std::max_element(times.begin(), times.end());
        auto avg_time = std::accumulate(times.begin(), times.end(), 0.0) / times.size();

        return std::make_tuple(min_time, max_time, avg_time);
    }

    static std::string format_results(const BenchmarkResult& results) {
        auto [min_time, max_time, avg_time] = results;
        std::ostringstream oss;
        oss << "Min: " << min_time << "ms, Max: " << max_time << "ms, Avg: " << avg_time << "ms";
        return oss.str();
    }

    static std::optional<std::string> compare_results(
        const BenchmarkResult& result1,
        const BenchmarkResult& result2,
        const std::string& name1 = "Function 1",
        const std::string& name2 = "Function 2") {

        auto avg1 = std::get<2>(result1);
        auto avg2 = std::get<2>(result2);

        if (avg1 == avg2) {
            return std::nullopt; // Performance is identical
        }

        std::ostringstream oss;
        if (avg1 < avg2) {
            double speedup = avg2 / avg1;
            oss << name1 << " is " << speedup << "x faster than " << name2;
        } else {
            double speedup = avg1 / avg2;
            oss << name2 << " is " << speedup << "x faster than " << name1;
        }
        return oss.str();
    }
};

// Data Analysis Pipeline - Integration of all utilities
using DataPoint = std::variant<int, double, std::string>;
using ProcessingResult = std::tuple<size_t, size_t, double>; // processed_count, error_count, processing_time_ms
using DataSummary = std::tuple<std::optional<double>, std::optional<double>, size_t>; // min, max, count

class TimedOperation {
private:
    std::chrono::steady_clock::time_point start_time;
    std::string operation_name;

public:
    TimedOperation(const std::string& name) : operation_name(name) {
        start_time = std::chrono::steady_clock::now();
        std::cout << "Starting: " << operation_name << std::endl;
    }

    ~TimedOperation() {
        auto elapsed = elapsed_ms();
        std::cout << "Completed: " << operation_name << " in " << elapsed << " ms" << std::endl;
    }

    double elapsed_ms() const {
        auto end_time = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return duration.count() / 1000.0;
    }
};

class DataAnalyzer {
private:
    std::vector<DataPoint> data;

public:
    void add_data_point(const DataPoint& point) {
        data.push_back(point);
    }

    void load_from_strings(const std::vector<std::string>& raw_data) {
        for (const auto& str : raw_data) {
            // Try to convert to int first, then double, otherwise store as string
            if (auto int_val = SafeStringProcessor::to_int(str)) {
                add_data_point(*int_val);
            } else {
                try {
                    double double_val = std::stod(str);
                    add_data_point(double_val);
                } catch (...) {
                    add_data_point(str); // Store as string
                }
            }
        }
    }

    ProcessingResult process_data() {
        TimedOperation timer("Data Processing");

        size_t processed_count = data.size();
        size_t error_count = 0; // No errors in this simple implementation
        double processing_time = timer.elapsed_ms();

        return std::make_tuple(processed_count, error_count, processing_time);
    }

    DataSummary calculate_numeric_summary() {
        std::optional<double> min_val, max_val;
        size_t numeric_count = 0;

        for (const auto& point : data) {
            if (std::holds_alternative<int>(point)) {
                double val = static_cast<double>(std::get<int>(point));
                update_min_max(min_val, max_val, val);
                numeric_count++;
            } else if (std::holds_alternative<double>(point)) {
                double val = std::get<double>(point);
                update_min_max(min_val, max_val, val);
                numeric_count++;
            }
        }

        return std::make_tuple(min_val, max_val, numeric_count);
    }

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

    std::optional<std::string> export_summary() {
        if (data.empty()) {
            return std::nullopt;
        }

        auto [min_val, max_val, numeric_count] = calculate_numeric_summary();
        auto string_count = get_data_of_type<std::string>().size();

        std::ostringstream oss;
        oss << "Data Analysis Summary\n";
        oss << "====================\n";
        oss << "Total data points: " << data.size() << "\n";

        if (numeric_count > 0) {
            oss << "Numeric values: " << numeric_count;
            if (min_val && max_val) {
                oss << " (min: " << *min_val << ", max: " << *max_val << ")";
            }
            oss << "\n";
        }

        if (string_count > 0) {
            oss << "String values: " << string_count << "\n";
        }

        return oss.str();
    }

private:
    void update_min_max(std::optional<double>& min_val, std::optional<double>& max_val, double val) {
        if (!min_val || val < *min_val) {
            min_val = val;
        }
        if (!max_val || val > *max_val) {
            max_val = val;
        }
    }
};

void test_safe_string_operations() {
    std::cout << "=== Safe String Operations Demo ===\n";

    std::string test_str = "hello";

    auto char_result = SafeStringProcessor::char_at(test_str, 1);
    if (char_result) {
        std::cout << "Character at index 1: " << *char_result << std::endl;
    }

    auto not_found = SafeStringProcessor::char_at(test_str, 10);
    std::cout << "Character at index 10 exists: " << not_found.has_value() << std::endl;

    auto find_result = SafeStringProcessor::find_char(test_str, 'l');
    if (find_result) {
        std::cout << "First 'l' found at index: " << *find_result << std::endl;
    }

    auto int_result = SafeStringProcessor::to_int("123");
    if (int_result) {
        std::cout << "Converted to int: " << *int_result << std::endl;
    }

    auto invalid_int = SafeStringProcessor::to_int("not_a_number");
    std::cout << "Invalid conversion successful: " << invalid_int.has_value() << std::endl;
}

void test_data_processor() {
    std::cout << "\n=== Data Processor Demo ===\n";

    DataValue int_data = 42;
    DataValue double_data = 3.14159;
    DataValue string_data = std::string("Hello World");

    std::cout << DataProcessor::describe(int_data) << std::endl;
    std::cout << DataProcessor::describe(double_data) << std::endl;
    std::cout << DataProcessor::describe(string_data) << std::endl;

    std::cout << "Sizes: " << DataProcessor::calculate_size(int_data) << ", "
              << DataProcessor::calculate_size(double_data) << ", "
              << DataProcessor::calculate_size(string_data) << std::endl;
}

void test_student_manager() {
    std::cout << "\n=== Student Manager Demo ===\n";

    auto student = StudentManager::create_student("Alice Johnson", 20, 3.75);

    std::cout << "Name: " << StudentManager::get_name(student) << std::endl;
    std::cout << "Age: " << StudentManager::get_age(student) << std::endl;
    std::cout << "GPA: " << StudentManager::get_gpa(student) << std::endl;
    std::cout << "Formatted: " << StudentManager::format_student(student) << std::endl;
}

void test_config_parser() {
    std::cout << "\n=== Configuration Parser Demo ===\n";

    std::map<std::string, std::string> config_data = {
        {"port", "8080"},
        {"host", "localhost"},
        {"timeout", "30.5"},
        {"debug", "true"},
        {"invalid_number", "not_a_number"}
    };

    ConfigParser parser(config_data);

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

    auto invalid = parser.get_value<int>("invalid_number");
    std::cout << "Invalid number parsed: " << invalid.has_value() << std::endl;

    auto missing = parser.get_value_or<int>("missing_key", 3000);
    std::cout << "Missing key with default: " << missing << std::endl;
}

void test_benchmarker() {
    std::cout << "\n=== Performance Benchmarker Demo ===\n";

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
}

void test_data_analyzer() {
    std::cout << "\n=== Data Analysis Pipeline Demo ===\n";

    DataAnalyzer analyzer;

    std::vector<std::string> raw_data = {
        "42",           // int
        "3.14159",      // double
        "hello",        // string
        "99",           // int
        "2.71828",      // double
        "invalid_num",  // string
        "world"         // string
    };

    analyzer.load_from_strings(raw_data);

    auto [processed, errors, time_ms] = analyzer.process_data();
    auto [min_val, max_val, numeric_count] = analyzer.calculate_numeric_summary();

    std::cout << "Processed: " << processed << " items" << std::endl;
    std::cout << "Errors: " << errors << std::endl;
    std::cout << "Processing time: " << time_ms << " ms" << std::endl;

    if (min_val && max_val) {
        std::cout << "Numeric range: " << *min_val << " to " << *max_val << std::endl;
    }
    std::cout << "Numeric count: " << numeric_count << std::endl;

    auto strings = analyzer.get_data_of_type<std::string>();
    std::cout << "String count: " << strings.size() << std::endl;

    auto summary = analyzer.export_summary();
    if (summary) {
        std::cout << "\n" << *summary << std::endl;
    }
}

int main() {
    test_safe_string_operations();
    test_data_processor();
    test_student_manager();
    test_config_parser();
    test_benchmarker();
    test_data_analyzer();

    std::cout << "\n=== All utility demos completed successfully ===\n";

    return 0;
}