/**
 * Problem 1.3: Range-Based For Loop with Containers
 * 
 * Demonstrates:
 * - Range-based for loops (const auto& vs auto&)
 * - Vector operations and processing
 * - Accumulation patterns
 * - Proper const-correctness
 */

#include <iostream>
#include <vector>
#include <iomanip>  // for std::fixed and std::setprecision

int main() {
    // Initial temperature data
    std::vector<double> temperatures = {68.5, 72.1, 69.8, 74.2, 71.5, 73.0, 70.2};
    
    std::cout << std::fixed << std::setprecision(1);  // Format output to 1 decimal place
    
    // 1. Display all temperatures using range-based for loop
    std::cout << "Original temperatures: ";
    for (const auto& temp : temperatures) {  // const auto& for read-only access
        std::cout << temp << "°F ";
    }
    std::cout << std::endl;
    
    // 2. Calculate average temperature
    double sum = 0.0;
    for (const auto& temp : temperatures) {
        sum += temp;
    }
    double average = sum / temperatures.size();
    std::cout << "Average temperature: " << average << "°F" << std::endl;
    
    // 3. Count temperatures above average
    int above_average_count = 0;
    for (const auto& temp : temperatures) {
        if (temp > average) {
            ++above_average_count;
        }
    }
    std::cout << "Temperatures above average: " << above_average_count << std::endl;
    
    // 4. Modify all temperatures by adding 2.0 degrees
    std::cout << "\nAdding 2.0 degrees to all temperatures..." << std::endl;
    for (auto& temp : temperatures) {  // auto& for modifying elements
        temp += 2.0;
    }
    
    // 5. Display modified temperatures
    std::cout << "Modified temperatures: ";
    for (const auto& temp : temperatures) {
        std::cout << temp << "°F ";
    }
    std::cout << std::endl;
    
    // Bonus: Show temperatures with their indices using traditional for loop
    std::cout << "\nDetailed listing:" << std::endl;
    for (size_t i = 0; i < temperatures.size(); ++i) {
        std::cout << "Temperature " << (i + 1) << ": " << temperatures[i] << "°F";
        if (temperatures[i] - 2.0 > average) {  // Check if original was above average
            std::cout << " (was above original average)";
        }
        std::cout << std::endl;
    }
    
    return 0;
}