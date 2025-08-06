/**
 * Problem 1.2: Number Pattern Generator
 * 
 * Demonstrates:
 * - Nested for loops
 * - Continue statement usage
 * - Input validation with ranges
 * - Loop control flow
 */

#include <iostream>
#include <limits>

void clear_input_buffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int size;
    char mode;
    
    // Get and validate pattern size
    std::cout << "Enter pattern size (1-10): ";
    if (!(std::cin >> size) || size < 1 || size > 10) {
        std::cout << "Error: Size must be between 1 and 10" << std::endl;
        return 1;
    }
    
    // Get and validate mode
    std::cout << "Show all rows (a) or odd rows only (o)? ";
    if (!(std::cin >> mode) || (mode != 'a' && mode != 'o')) {
        std::cout << "Error: Please enter 'a' for all or 'o' for odd only" << std::endl;
        return 1;
    }
    
    std::cout << "\nPattern:" << std::endl;
    
    // Generate pattern using nested loops
    for (int row = 1; row <= size; ++row) {
        // Skip even rows if odd-only mode is selected
        if (mode == 'o' && row % 2 == 0) {
            continue;  // Skip to next iteration
        }
        
        // Print numbers for current row
        for (int col = 1; col <= row; ++col) {
            std::cout << col;
        }
        
        std::cout << std::endl;
    }
    
    return 0;
}