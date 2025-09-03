// HW_02: Part 1 - Type System Explorer
// Time: 90 minutes
// Topics: Fundamental types, sizeof, type conversion, practical applications

#include <cstdio>
#include <climits>  // For INT_MAX, INT_MIN, etc.
#include <cfloat>   // For DBL_MAX, FLT_MAX, etc.

// ============================================================================
// PART A: Type Discovery and Analysis (30 minutes)
// ============================================================================

void exploreBasicTypes() {
    printf("=== C++ Type System Analysis ===\n\n");
    printf("Fundamental Types:\n");
    
    // TODO 1: Declare variables of each fundamental type and display their size
    // Example started for you:
    int myInt = 42;
    printf("  int: %d (size: %zu bytes, range: %d to %d)\n", 
           myInt, sizeof(int), INT_MIN, INT_MAX);
    
    // TODO: Add double, char, bool, long, float
    // Hint: Use sizeof() and appropriate format specifiers
    
    printf("\n");
}

void exploreTypeConversions() {
    printf("Type Conversions:\n");
    
    // TODO 2: Demonstrate implicit conversions
    int intVal = 42;
    // double doubleVal = 3.14159;  // TODO: Uncomment and use this variable
    
    // Example: int to double (no loss)
    double promoted = intVal;  // Implicit conversion
    printf("  int(%d) -> double: %.6f (no loss)\n", intVal, promoted);
    
    // TODO: Show double to int (precision loss)
    // TODO: Show char to int (ASCII value)
    // TODO: Compare implicit vs explicit with static_cast<>
    
    printf("\n");
}

// ============================================================================
// PART B: Practical Application - Multi-Unit Converter (30 minutes)
// ============================================================================

void temperatureConverter() {
    printf("=== Temperature Converter ===\n");
    
    // TODO 3: Implement temperature conversions
    // double celsius = 25.0;  // TODO: Uncomment and use this variable
    
    // TODO: Convert Celsius to Fahrenheit: F = (C * 9/5) + 32
    // TODO: Convert Celsius to Kelvin: K = C + 273.15
    // TODO: Show difference between integer and floating-point division
    
    // Example output:
    // printf("  %.1f°C = %.1f°F = %.2fK\n", celsius, fahrenheit, kelvin);
    
    printf("\n");
}

void distanceConverter() {
    printf("=== Distance Converter ===\n");
    
    // TODO 4: Implement distance conversions
    // double miles = 5.0;  // TODO: Uncomment and use this variable
    
    // TODO: Miles to Kilometers (1 mile = 1.60934 km)
    // TODO: Kilometers to Meters
    // TODO: Feet to Meters (1 foot = 0.3048 meters)
    
    printf("\n");
}

// ============================================================================
// PART C: Memory Behavior and Scope Analysis (30 minutes)
// ============================================================================

// Global variable for demonstration
int globalVar = 100;  // Automatically initialized to 100

void demonstrateInitialization() {
    printf("=== Initialization Behavior ===\n");
    
    // TODO 5: Show uninitialized local variable behavior
    // WARNING: This is for educational purposes only!
    // int uninitializedLocal;  // Uncomment to see undefined behavior
    // printf("  Uninitialized local: %d (unpredictable!)\n", uninitializedLocal);
    
    // TODO: Show global variable auto-initialization
    printf("  Global variable: %d (auto-initialized)\n", globalVar);
    
    // TODO: Demonstrate const variable requirements
    const int mustInitialize = 42;  // Must be initialized
    printf("  Const variable: %d (must be initialized)\n", mustInitialize);
    
    printf("\n");
}

void demonstrateScope() {
    printf("=== Scope Investigation ===\n");
    
    int outerScope = 10;
    printf("  Outer scope: %d\n", outerScope);
    
    // TODO 6: Demonstrate block scope and variable shadowing
    {
        // int outerScope = 20;  // TODO: Uncomment to shadow outer variable
        // TODO: Print the shadowed value
        // TODO: Create another nested scope to show multiple levels
    }
    
    // TODO: Show that outer variable is unchanged
    
    printf("\n");
}

void showMemoryLayout() {
    printf("=== Memory Layout ===\n");
    
    // TODO 7: Compare addresses of different variable types
    int localVar = 42;
    static int staticVar = 100;
    
    printf("  Global variable address: %p\n", (void*)&globalVar);
    printf("  Static variable address: %p\n", (void*)&staticVar);
    printf("  Local variable address:  %p\n", (void*)&localVar);
    
    // TODO: Explain why addresses are in different ranges
    // (stack vs data segment)
    
    printf("\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("========================================\n");
    printf("     HW_02: Type System Explorer\n");
    printf("========================================\n\n");
    
    // Part A: Type Discovery (30 min)
    exploreBasicTypes();
    exploreTypeConversions();
    
    // Part B: Practical Applications (30 min)
    temperatureConverter();
    distanceConverter();
    
    // Part C: Memory Behavior (30 min)
    demonstrateInitialization();
    demonstrateScope();
    showMemoryLayout();
    
    printf("========================================\n");
    printf("     Program Complete!\n");
    printf("========================================\n");
    
    return 0;
}