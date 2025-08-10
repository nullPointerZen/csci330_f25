/**
 * Problem 2.1: Safe Division Calculator
 * 
 * Demonstrates:
 * - Exception throwing and catching
 * - Standard exception types
 * - Multiple catch blocks
 * - Input validation with exceptions
 * - Menu-driven program with exception handling
 */

#include <iostream>
#include <stdexcept>
#include <limits>
#include <string>

double safe_divide(double numerator, double denominator) {
    if (denominator == 0.0) {
        throw std::invalid_argument("Division by zero is not allowed");
    }
    
    double result = numerator / denominator;
    
    // Check for overflow/underflow (though less common with double)
    if (!std::isfinite(result)) {
        throw std::runtime_error("Result is not a finite number");
    }
    
    return result;
}

double safe_add(double a, double b) {
    return a + b;
}

double safe_subtract(double a, double b) {
    return a - b;
}

double safe_multiply(double a, double b) {
    double result = a * b;
    
    if (!std::isfinite(result)) {
        throw std::runtime_error("Result is not a finite number");
    }
    
    return result;
}

void clear_input_buffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    double a, b, result;
    char operation;
    std::string input_line;
    
    std::cout << "=== Safe Calculator ===" << std::endl;
    std::cout << "Enter calculations in format: number operator number" << std::endl;
    std::cout << "Supported operators: +, -, *, /" << std::endl;
    std::cout << "Enter 'q' to quit" << std::endl << std::endl;
    
    while (true) {
        std::cout << "Enter calculation (a op b) or 'q' to quit: ";
        
        // Try to read the input
        if (!(std::cin >> a >> operation >> b)) {
            // Check if it was 'q' to quit
            if (std::cin.eof()) {
                break;
            }
            
            // Check for 'q' character
            std::cin.clear();
            char quit_char;
            std::cin >> quit_char;
            if (quit_char == 'q' || quit_char == 'Q') {
                break;
            }
            
            // Handle invalid input
            std::cout << "Error: Invalid input format. Please use: number operator number" << std::endl;
            clear_input_buffer();
            continue;
        }
        
        try {
            // Perform the calculation based on operator
            switch (operation) {
                case '+':
                    result = safe_add(a, b);
                    break;
                case '-':
                    result = safe_subtract(a, b);
                    break;
                case '*':
                    result = safe_multiply(a, b);
                    break;
                case '/':
                    result = safe_divide(a, b);
                    break;
                default:
                    throw std::invalid_argument("Unsupported operator: " + std::string(1, operation));
            }
            
            std::cout << "Result: " << result << std::endl;
            
        } catch (const std::invalid_argument& e) {
            std::cout << "Input Error: " << e.what() << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << "Calculation Error: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Unexpected Error: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown error occurred" << std::endl;
        }
        
        std::cout << std::endl;  // Add blank line for readability
    }
    
    std::cout << "Calculator shutting down. Goodbye!" << std::endl;
    return 0;
}