/*
 * Chapter 2, Problem 1.2 Solution: Temperature Converter
 * 
 * This program converts temperatures between Celsius and Fahrenheit,
 * demonstrating practical use of int and double types.
 * 
 * Key Learning Points:
 * 1. Use int for whole number inputs (Celsius temperatures)
 * 2. Use double for precise calculations (Fahrenheit results)
 * 3. Integer division vs floating-point division
 * 4. Proper formatting for decimal output
 * 
 * Formula: F = (C × 9/5) + 32
 * 
 * Python Comparison: Python automatically handles int/float conversion
 * Java Comparison: Similar type handling, but Java has stricter casting rules
 */

#include <cstdio>

int main() {
    printf("=== Temperature Converter (Celsius to Fahrenheit) ===\n\n");
    
    // Test with common temperature values
    int celsius_freezing = 0;    // Water freezing point
    int celsius_boiling = 100;   // Water boiling point
    int celsius_body = 37;       // Human body temperature
    int celsius_room = 20;       // Comfortable room temperature
    
    // Convert each temperature to Fahrenheit
    // Important: Use 9.0/5.0 to ensure floating-point division
    double fahrenheit_freezing = (celsius_freezing * 9.0 / 5.0) + 32;
    double fahrenheit_boiling = (celsius_boiling * 9.0 / 5.0) + 32;
    double fahrenheit_body = (celsius_body * 9.0 / 5.0) + 32;
    double fahrenheit_room = (celsius_room * 9.0 / 5.0) + 32;
    
    // Display results with proper formatting
    printf("Temperature Conversions:\n");
    printf("%d°C = %.1f°F (Water freezing point)\n", celsius_freezing, fahrenheit_freezing);
    printf("%d°C = %.1f°F (Water boiling point)\n", celsius_boiling, fahrenheit_boiling);
    printf("%d°C = %.1f°F (Human body temperature)\n", celsius_body, fahrenheit_body);
    printf("%d°C = %.1f°F (Room temperature)\n", celsius_room, fahrenheit_room);
    
    printf("\n=== Demonstrating Integer vs Floating Division ===\n");
    
    // Show the difference between integer and floating-point division
    int test_celsius = 25;
    
    // WRONG WAY: Integer division
    double wrong_fahrenheit = (test_celsius * 9 / 5) + 32;  // 9 / 5 = 1 (integer division!)
    
    // RIGHT WAY: Floating-point division  
    double correct_fahrenheit = (test_celsius * 9.0 / 5.0) + 32;  // 9.0 / 5.0 = 1.8
    
    printf("For %d°C:\n", test_celsius);
    printf("Wrong (integer division): %.1f°F\n", wrong_fahrenheit);
    printf("Correct (float division): %.1f°F\n", correct_fahrenheit);
    
    /*
     * The difference occurs because:
     * - 9 / 5 in integer arithmetic = 1 (truncated)
     * - 9.0 / 5.0 in floating-point arithmetic = 1.8 (precise)
     */
    
    printf("\n=== Type Information ===\n");
    printf("Size of int (Celsius): %zu bytes\n", sizeof(int));
    printf("Size of double (Fahrenheit): %zu bytes\n", sizeof(double));
    
    return 0;
}

/*
 * Expected Output:
 * === Temperature Converter (Celsius to Fahrenheit) ===
 * 
 * Temperature Conversions:
 * 0°C = 32.0°F (Water freezing point)
 * 100°C = 212.0°F (Water boiling point)
 * 37°C = 98.6°F (Human body temperature)
 * 20°C = 68.0°F (Room temperature)
 * 
 * === Demonstrating Integer vs Floating Division ===
 * For 25°C:
 * Wrong (integer division): 70.0°F
 * Correct (float division): 77.0°F
 * 
 * === Type Information ===
 * Size of int (Celsius): 4 bytes
 * Size of double (Fahrenheit): 8 bytes
 * 
 * 
 * Key Teaching Points:
 * 
 * 1. INTEGER DIVISION TRAP:
 *    - 9 / 5 = 1 (not 1.8!) in C++ integer arithmetic
 *    - Always use 9.0 / 5.0 when you need decimal results
 *    - This is different from Python 3 where / always gives float result
 * 
 * 2. TYPE CHOICE REASONING:
 *    - int for Celsius: Usually whole numbers, saves memory
 *    - double for Fahrenheit: Needs decimal precision for accuracy
 * 
 * 3. FORMAT SPECIFIERS:
 *    - %d for int values
 *    - %.1f for double with 1 decimal place
 *    - %zu for sizeof results (size_t type)
 * 
 * 
 * Common Student Mistakes:
 * 
 * 1. WRONG: double f = (c * 9 / 5) + 32;     // Integer division problem
 *    RIGHT: double f = (c * 9.0 / 5.0) + 32; // Floating division
 * 
 * 2. WRONG: printf("%.1f°C", celsius);       // Wrong format for int
 *    RIGHT: printf("%d°C", celsius);         // Correct format for int
 * 
 * 3. WRONG: int fahrenheit = (c * 9.0/5.0) + 32; // Loses decimal precision
 *    RIGHT: double fahrenheit = (c * 9.0/5.0) + 32; // Keeps precision
 * 
 * 
 * Compilation: g++ -o temp_converter problem_2_2_solution.cpp
 * Execution: ./temp_converter
 */