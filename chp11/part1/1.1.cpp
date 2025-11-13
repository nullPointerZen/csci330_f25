#include <iostream>
#include <memory>
#include <string>

class DataProcessor {
private:
    std::unique_ptr<int[]> data;
    size_t size;

public:
    // Constructor
    DataProcessor(size_t n) : data(std::make_unique<int[]>(n)), size(n) {
        for (size_t i = 0; i < n; ++i) {
            data[i] = static_cast<int>(i * i);
        }
    }

    // Destructor no longer needed — unique_ptr handles cleanup

    // Delete copy operations to enforce unique ownership
    DataProcessor(const DataProcessor&) = delete;
    DataProcessor& operator=(const DataProcessor&) = delete;

    // Move constructor
    DataProcessor(DataProcessor&& other) noexcept
        : data(std::move(other.data)), size(other.size) {
        other.size = 0;
    }

    // Move assignment
    DataProcessor& operator=(DataProcessor&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            size = other.size;
            other.size = 0;
        }
        return *this;
    }

    // Print contents
    void print_data() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Access value safely
    int get_value(size_t index) const {
        if (index < size) return data[index];
        return -1;
    }
};

// Test move semantics
int main() {
    DataProcessor processor(5);
    processor.print_data();

    DataProcessor processor2 = std::move(processor);  // Move ownership
    processor2.print_data();

    std::cout << "Value at index 3: " << processor2.get_value(3) << std::endl;
    return 0;
}