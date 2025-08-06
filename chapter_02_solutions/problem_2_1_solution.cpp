/*
 * Chapter 2, Problem 1.1 Solution: Type Explorer
 * 
 * This program demonstrates fundamental C++ types and their characteristics.
 * 
 * Key Learning Points:
 * 1. Each type has a specific size in memory
 * 2. Format specifiers must match the data type
 * 3. Type conversions can happen automatically but may lose precision
 * 4. sizeof() operator gives size in bytes
 * 
 * Python Comparison: Python's int/float are dynamic, C++ types are fixed
 * Java Comparison: Similar to Java primitives but C++ shows exact memory usage
 */

#include <cstdio>

int main() {
    // Declare and initialize variables of each fundamental type
    int integer_value = 42;
    double double_value = 3.14159;
    char character_value = 'A';
    bool boolean_value = true;
    
    printf("=== Fundamental C++ Types ===\n\n");
    
    // Print each variable with its appropriate format specifier
    printf("Integer: %d (size: %zu bytes)\n", integer_value, sizeof(int));
    printf("Double: %.2f (size: %zu bytes)\n", double_value, sizeof(double));
    printf("Character: %c (size: %zu bytes)\n", character_value, sizeof(char));
    printf("Boolean: %d (size: %zu bytes)\n", boolean_value, sizeof(bool));
    
    printf("\n=== Type Conversion Example ===\n");
    
    // Demonstrate type conversion
    // When we convert int to double, it's safe (no data loss)
    double converted_int = integer_value;
    printf("Conversion: %d -> %.2f\n", integer_value, converted_int);
    
    // When we convert double to int, we lose the decimal part
    int converted_double = (int)double_value;  // Explicit cast
    printf("Conversion: %.2f -> %d (precision lost!)\n", double_value, converted_double);
    
    printf("\n=== Memory Layout Information ===\n");
    printf("Address of integer_value: %p\n", &integer_value);
    printf("Address of double_value:  %p\n", &double_value);
    printf("Address of character_value: %p\n", &character_value);
    printf("Address of boolean_value: %p\n", &boolean_value);
    
    /*
     * Why this matters:
     * - C++ gives you direct control over memory usage
     * - Knowing type sizes helps optimize programs
     * - Format specifiers prevent undefined behavior
     * - Type conversions can cause data loss if not careful
     */
    
    return 0;
}

/*
 * Expected Output:
 * === Fundamental C++ Types ===
 * 
 * Integer: 42 (size: 4 bytes)
 * Double: 3.14 (size: 8 bytes)
 * Character: A (size: 1 byte)
 * Boolean: 1 (size: 1 byte)
 * 
 * === Type Conversion Example ===
 * Conversion: 42 -> 42.00
 * Conversion: 3.14 -> 3 (precision lost!)
 * 
 * === Memory Layout Information ===
 * Address of integer_value: 0x7fff5fbff6ac
 * Address of double_value:  0x7fff5fbff6a0
 * Address of character_value: 0x7fff5fbff69f
 * Address of boolean_value: 0x7fff5fbff69e
 * 
 * 
 * Common Student Mistakes to Avoid:
 * 
 * 1. WRONG: printf("%d", double_value);  // Wrong format specifier
 *    RIGHT: printf("%f", double_value);  // Correct format specifier
 * 
 * 2. WRONG: char letter = "A";           // Double quotes make it a string
 *    RIGHT: char letter = 'A';           // Single quotes for character
 * 
 * 3. WRONG: bool flag = 1;               // Works but not clear
 *    RIGHT: bool flag = true;            // Clear and idiomatic
 * 
 * 
 * Compilation: g++ -o type_explorer problem_2_1_solution.cpp
 * Execution: ./type_explorer
 */