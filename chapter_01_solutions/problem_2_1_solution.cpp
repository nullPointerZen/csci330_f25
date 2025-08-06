// Problem 2.1: Temperature Converter Solution
// Demonstrates integer vs floating-point arithmetic

#include <cstdio>

int main() {
    // Part 1: Using integers
    printf("=== Using Integer Types ===\n");
    int celsius_int = 25;
    int fahrenheit_int = (celsius_int * 9 / 5) + 32;
    
    printf("Celsius (int): %d\n", celsius_int);
    printf("Fahrenheit (int): %d\n", fahrenheit_int);
    printf("Note: Integer division truncates!\n\n");
    
    // Part 2: Using doubles for precision
    printf("=== Using Double Types ===\n");
    double celsius_double = 25.0;
    double fahrenheit_double = (celsius_double * 9.0 / 5.0) + 32.0;
    
    printf("Celsius (double): %.1f\n", celsius_double);
    printf("Fahrenheit (double): %.1f\n", fahrenheit_double);
    printf("Note: Floating-point preserves precision!\n\n");
    
    // Part 3: Demonstrating the difference
    printf("=== Precision Comparison ===\n");
    int test_celsius = 23;  // Choose a value where precision matters
    
    int f_int = (test_celsius * 9 / 5) + 32;
    double f_double = (test_celsius * 9.0 / 5.0) + 32.0;
    
    printf("23°C converted:\n");
    printf("  As integer: %d°F\n", f_int);
    printf("  As double: %.1f°F\n", f_double);
    printf("  Difference: %.1f°F\n", f_double - f_int);
    
    return 0;
}

/* 
Compilation command:
g++ -o temp_converter problem_2_1_solution.cpp

Expected Output:
=== Using Integer Types ===
Celsius (int): 25
Fahrenheit (int): 77
Note: Integer division truncates!

=== Using Double Types ===
Celsius (double): 25.0
Fahrenheit (double): 77.0
Note: Floating-point preserves precision!

=== Precision Comparison ===
23°C converted:
  As integer: 73°F
  As double: 73.4°F
  Difference: 0.4°F

Key Learning Points:
1. Integer division in C++ truncates (unlike Python 3's / operator)
2. Similar to Java's integer division behavior
3. Use double for scientific calculations requiring precision
4. Format specifiers: %d for int, %f for double
*/