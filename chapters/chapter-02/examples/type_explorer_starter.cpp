// type_explorer_starter.cpp
// Starter code for Assignment 1: Type System Exploration
// TODO markers indicate where you need to add code

#include <cstdio>
#include <climits>  // For INT_MAX, INT_MIN, etc.
#include <cfloat>   // For DBL_MAX, FLT_MAX, etc.

// ============================================
// PART A: Type Discovery and Analysis
// ============================================

void analyze_fundamental_types() {
    printf("=== C++ Type System Analysis ===\n");
    printf("Fundamental Types:\n");

    // Integer type
    int my_int = 42;
    printf("  int: %d (size: %zu bytes, range: %d to %d)\n",
           my_int, sizeof(int), INT_MIN, INT_MAX);

    // TODO: Add double type
    double my_double = 3.14159;
    // printf(...)  // Use %.6f for value, DBL_MIN and DBL_MAX for range

    // TODO: Add char type
    char my_char = 'A';
    // printf(...)  // Use %c for value, CHAR_MIN and CHAR_MAX for range

    // TODO: Add bool type
    bool my_bool = true;
    // printf(...)  // Use %d for value (prints as 0 or 1)

    // TODO: Add long type
    // long my_long = ...

    // TODO: Add float type
    // float my_float = ...
}

void demonstrate_type_conversions() {
    printf("\nType Conversions:\n");

    // Implicit conversions
    int whole_number = 42;
    double decimal_number = 3.14159;

    // TODO: Show int to double conversion (no loss)
    double int_to_double = whole_number;
    printf("  int(%d) -> double: %.6f (no loss)\n", whole_number, int_to_double);

    // TODO: Show double to int conversion (precision lost)
    // int double_to_int = ...
    // printf(...)

    // TODO: Show char to int conversion (ASCII value)
    char letter = 'A';
    // int char_to_int = ...
    // printf(...)

    // Explicit conversions with static_cast
    printf("\nExplicit vs Implicit:\n");

    // TODO: Show implicit conversion in mixed arithmetic
    double result = whole_number + decimal_number;
    // printf(...)

    // TODO: Show explicit casting
    int truncated = static_cast<int>(decimal_number);
    // printf(...)
}

// ============================================
// PART B: Multi-Unit Converter
// ============================================

// Temperature conversion functions
double celsius_to_fahrenheit(double celsius) {
    // TODO: Implement formula: (C * 9/5) + 32
    return 0.0;  // Replace with actual calculation
}

double fahrenheit_to_celsius(double fahrenheit) {
    // TODO: Implement formula: (F - 32) * 5/9
    return 0.0;  // Replace with actual calculation
}

double celsius_to_kelvin(double celsius) {
    // TODO: Implement formula: C + 273.15
    return 0.0;  // Replace with actual calculation
}

// Distance conversion functions
const double MILES_TO_KM = 1.60934;
const double FEET_TO_METERS = 0.3048;
const double METERS_TO_FEET = 3.28084;

double miles_to_kilometers(double miles) {
    // TODO: Implement using MILES_TO_KM constant
    return 0.0;  // Replace with actual calculation
}

double kilometers_to_miles(double km) {
    // TODO: Implement (inverse of above)
    return 0.0;  // Replace with actual calculation
}

double feet_to_meters(double feet) {
    // TODO: Implement using FEET_TO_METERS constant
    return 0.0;  // Replace with actual calculation
}

void run_converter_demo() {
    printf("\n=== Multi-Unit Converter ===\n");

    // Temperature conversions
    printf("Temperature Conversions:\n");
    double temp_c = 25.0;
    printf("  %g°C = %g°F\n", temp_c, celsius_to_fahrenheit(temp_c));
    printf("  %g°C = %g K\n", temp_c, celsius_to_kelvin(temp_c));

    // TODO: Add more temperature examples, including negative values

    // Distance conversions
    printf("\nDistance Conversions:\n");
    double dist_miles = 10.0;
    printf("  %g miles = %g km\n", dist_miles, miles_to_kilometers(dist_miles));

    // TODO: Add more distance examples

    // Show integer vs floating-point division difference
    printf("\nInteger vs Floating-Point Division:\n");
    int int_celsius = 25;
    // TODO: Calculate Fahrenheit using integer math (note the difference!)
    // int int_fahrenheit = (int_celsius * 9 / 5) + 32;  // What's wrong here?
    // double float_fahrenheit = (int_celsius * 9.0 / 5.0) + 32.0;  // Correct way
}

// ============================================
// PART C: Memory Behavior and Scope Analysis
// ============================================

// Global variable (auto-initialized to 0)
int global_counter;

void analyze_initialization() {
    printf("\n=== Initialization Behavior ===\n");

    // Local variables
    int uninitialized_local;  // Contains garbage!
    int initialized_local = 0;  // Safe

    // Static variable (auto-initialized to 0)
    static int static_counter;

    printf("Uninitialized local: %d (DANGER: random value!)\n", uninitialized_local);
    printf("Initialized local: %d\n", initialized_local);
    printf("Global variable: %d (auto-initialized)\n", global_counter);
    printf("Static variable: %d (auto-initialized)\n", static_counter);

    // TODO: Show what happens when you increment the static variable
    // static_counter++;
    // printf("Static after increment: %d\n", static_counter);
}

void analyze_scope() {
    printf("\n=== Scope Analysis ===\n");

    int x = 10;
    printf("Outer scope x: %d\n", x);

    // Create inner scope
    {
        // TODO: Create a variable that shadows outer x
        // int x = 20;
        // printf("Inner scope x: %d\n", x);

        // TODO: Create a new variable y
        // int y = 30;
        // printf("Inner scope y: %d\n", y);
    }

    // TODO: Try to access inner scope variables (will cause error if uncommented)
    // printf("Can we access inner x? %d\n", x);  // Which x is this?
    // printf("Can we access y? %d\n", y);  // This would cause compilation error
}

void analyze_memory_addresses() {
    printf("\n=== Memory Layout ===\n");

    int local_var = 42;
    static int static_var = 100;

    // TODO: Print addresses to see memory layout
    printf("Address of global: %p\n", (void*)&global_counter);
    printf("Address of static: %p\n", (void*)&static_var);
    printf("Address of local: %p\n", (void*)&local_var);

    // TODO: Create an array and show how elements are contiguous
    // int arr[5] = {1, 2, 3, 4, 5};
    // for (int i = 0; i < 5; i++) {
    //     printf("arr[%d] at address: %p\n", i, (void*)&arr[i]);
    // }
}

// ============================================
// MAIN FUNCTION
// ============================================

int main() {
    // Part A: Type Analysis
    analyze_fundamental_types();
    demonstrate_type_conversions();

    // Part B: Converter
    run_converter_demo();

    // Part C: Memory Behavior
    analyze_initialization();
    analyze_scope();
    analyze_memory_addresses();

    // TODO: Add any additional demonstrations or tests

    printf("\n=== Program Complete ===\n");
    return 0;
}

/*
 * COMPILATION INSTRUCTIONS:
 * -------------------------
 * g++ -Wall -Wextra -o type_explorer type_explorer_starter.cpp
 * ./type_explorer
 *
 * EXPECTED OUTPUT PREVIEW:
 * ------------------------
 * Your program should produce organized output showing:
 * 1. All fundamental types with sizes and ranges
 * 2. Type conversion demonstrations
 * 3. Working unit converters
 * 4. Memory behavior analysis
 *
 * GRADING NOTES:
 * -------------
 * - All TODO sections must be completed
 * - Code must compile without warnings using -Wall -Wextra
 * - Output should be well-formatted and clear
 * - Demonstrate understanding of type system concepts
 */