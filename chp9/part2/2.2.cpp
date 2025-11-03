#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <algorithm>

class DataProcessor {
private:
    std::string processor_name;
    int processing_count;
    std::vector<int> results;

public:
    DataProcessor(const std::string& name)
        : processor_name(name), processing_count(0) {}

    // Lambda that captures processor_name by value and processing_count by reference
    auto create_filter(int threshold) {
        return [threshold, name = processor_name, &count = processing_count](int value) {
            ++count;
            return value > threshold;
        };
    }

    // Lambda factory using init captures
    auto create_transformer(int multiplier, int offset) {
        return [m = multiplier, o = offset](int value) {
            return value * m + o;
        };
    }

    // Stateful lambda with captured sum
    auto create_accumulator() {
        int sum = 0;
        return [sum](int value) mutable {
            sum += value;
            return sum;
        };
    }

    void process_data(const std::vector<int>& input_data) {
        std::cout << "Processing with " << processor_name << ":\n";

        auto filter = create_filter(10);
        auto transformer = create_transformer(2, 5);
        auto accumulator = create_accumulator();

        std::vector<int> filtered;
        std::copy_if(input_data.begin(), input_data.end(), std::back_inserter(filtered), filter);

        std::vector<int> transformed;
        std::transform(filtered.begin(), filtered.end(), std::back_inserter(transformed), transformer);

        std::cout << "Filtered and transformed data:\n";
        for (int val : transformed) {
            int total = accumulator(val);
            std::cout << "Value: " << val << ", Running Total: " << total << "\n";
        }

        std::cout << "Items processed: " << processing_count << "\n";
    }

    // Problematic lambda: captures local_var by reference
    auto create_problematic_lambda() {
        int local_var = 42;
        return [&local_var]() { return local_var; }; // Dangling reference after local_var goes out of scope
    }

    // Safe lambda: captures local_var by value
    auto create_safe_lambda() {
        int local_var = 42;
        return [local_var]() { return local_var; };
    }
};

int main() {
    DataProcessor processor("NumberCruncher");
    std::vector<int> test_data = {5, 15, 8, 22, 3, 18, 12, 7};

    processor.process_data(test_data);

    std::cout << "\nTesting lambda lifetime:\n";

    auto bad_lambda = processor.create_problematic_lambda();
    auto good_lambda = processor.create_safe_lambda();

    // Warning: bad_lambda may access invalid memory
    std::cout << "Safe lambda result: " << good_lambda() << "\n";
    std::cout << "Problematic lambda result (undefined behavior): " << bad_lambda() << "\n";

    return 0;
}