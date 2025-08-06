/*
 * Chapter 11, Problem 1.1: Converting Raw Pointers to unique_ptr
 * 
 * Solution: DataProcessor class using unique_ptr for automatic memory management
 * 
 * Key concepts demonstrated:
 * - Converting from raw pointers to unique_ptr
 * - Using make_unique for array allocation
 * - Automatic cleanup with RAII
 * - Move semantics with unique_ptr
 */

#include <iostream>
#include <string>
#include <memory>

class DataProcessor {
private:
    std::unique_ptr<int[]> data;  // Changed from int* to unique_ptr<int[]>
    size_t size;

public:
    DataProcessor(size_t n) : size(n) {
        // Use make_unique for array allocation
        data = std::make_unique<int[]>(n);
        
        for (size_t i = 0; i < n; ++i) {
            data[i] = static_cast<int>(i * i);
        }
    }
    
    // Destructor is no longer needed - unique_ptr handles cleanup automatically
    // Rule of Zero applies: compiler-generated destructor, move constructor,
    // and move assignment operator work correctly
    
    void print_data() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    
    int get_value(size_t index) const {
        if (index < size) return data[index];
        return -1;
    }
};

int main() {
    DataProcessor processor(5);
    processor.print_data();
    
    // Test move semantics - unique_ptr supports move but not copy
    DataProcessor processor2 = std::move(processor);
    processor2.print_data();
    
    std::cout << "Value at index 3: " << processor2.get_value(3) << std::endl;
    
    return 0;
}

/*
 * Expected Output:
 * 0 1 4 9 16 
 * 0 1 4 9 16 
 * Value at index 3: 9
 * 
 * Key improvements over raw pointer version:
 * 1. Automatic memory cleanup (no explicit destructor needed)
 * 2. Exception safety - if constructor throws after allocation, cleanup is automatic
 * 3. Move semantics work correctly out of the box
 * 4. No risk of double-deletion or memory leaks
 * 5. Rule of Zero - no need to implement copy/move constructors or assignment operators
 */