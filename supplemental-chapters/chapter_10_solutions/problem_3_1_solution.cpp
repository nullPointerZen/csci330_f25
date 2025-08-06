// Problem 3.1: TDD Calculator Enhancement Solution
// Demonstrates Test-Driven Development process with power function

#include <cstdio>

// Test framework
int tests_passed = 0;
int tests_failed = 0;

void assert_equal(int expected, int actual, const char* test_name) {
    if (expected == actual) {
        printf("[PASS] %s\n", test_name);
        tests_passed++;
    } else {
        printf("[FAIL] %s: expected %d, got %d\n", test_name, expected, actual);
        tests_failed++;
    }
}

void print_test_summary() {
    printf("\n=== Test Summary ===\n");
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_failed);
    
    if (tests_failed == 0) {
        printf("🎉 All tests passed!\n");
    } else {
        printf("❌ %d test(s) failed.\n", tests_failed);
    }
}

// Calculator class with basic operations
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
    int multiply(int a, int b) { return a * b; }
    
    // Power function - implemented using TDD process
    int power(int base, int exponent) {
        // Final implementation after TDD cycle
        if (exponent == 0) return 1;  // Any number to power 0 is 1
        if (exponent == 1) return base;  // Any number to power 1 is itself
        
        int result = 1;
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
        return result;
    }
};

/*
TDD PROCESS DOCUMENTATION:
==========================

CYCLE 1: Basic functionality
----------------------------
RED: Write failing test for power(2, 3)
*/
void test_power_basic() {
    Calculator calc;
    assert_equal(8, calc.power(2, 3), "power_2_cubed");
}

/*
GREEN: Minimal implementation (first attempt)
int power(int base, int exponent) {
    if (base == 2 && exponent == 3) return 8;  // Hard-coded!
    return 0;
}

CYCLE 2: Zero exponent
----------------------
RED: Write test for power(5, 0) - this will fail with hard-coded version
*/
void test_power_zero_exponent() {
    Calculator calc;
    assert_equal(1, calc.power(5, 0), "power_any_number_to_zero");
    assert_equal(1, calc.power(100, 0), "power_large_number_to_zero");
}

/*
GREEN: Updated implementation
int power(int base, int exponent) {
    if (exponent == 0) return 1;
    if (base == 2 && exponent == 3) return 8;
    return 0;
}

CYCLE 3: Exponent of 1
---------------------
RED: Write test for power(3, 1) - will fail
*/
void test_power_one_exponent() {
    Calculator calc;
    assert_equal(3, calc.power(3, 1), "power_three_to_one");
    assert_equal(17, calc.power(17, 1), "power_seventeen_to_one");
}

/*
GREEN: Updated implementation
int power(int base, int exponent) {
    if (exponent == 0) return 1;
    if (exponent == 1) return base;
    if (base == 2 && exponent == 3) return 8;
    return 0;
}

CYCLE 4: General case
--------------------
RED: Write test for power(2, 10) - will fail with hard-coded version
*/
void test_power_larger_exponents() {
    Calculator calc;
    assert_equal(1024, calc.power(2, 10), "power_2_to_10");
    assert_equal(32, calc.power(2, 5), "power_2_to_5");
    assert_equal(81, calc.power(3, 4), "power_3_to_4");
}

/*
GREEN: General implementation (REFACTOR)
int power(int base, int exponent) {
    if (exponent == 0) return 1;
    if (exponent == 1) return base;
    
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

CYCLE 5: Edge cases
------------------
RED: Add tests for edge cases
*/
void test_power_edge_cases() {
    Calculator calc;
    
    // Test base of 0
    assert_equal(0, calc.power(0, 5), "power_zero_base");
    assert_equal(1, calc.power(0, 0), "power_zero_to_zero");  // Mathematical convention
    
    // Test base of 1
    assert_equal(1, calc.power(1, 100), "power_one_to_large_exponent");
    
    // Test negative base with even exponent
    assert_equal(4, calc.power(-2, 2), "power_negative_base_even_exp");
    
    // Test negative base with odd exponent
    assert_equal(-8, calc.power(-2, 3), "power_negative_base_odd_exp");
}

// Additional tests to verify existing functionality still works
void test_existing_functions() {
    printf("\n--- Testing Existing Calculator Functions ---\n");
    Calculator calc;
    
    assert_equal(7, calc.add(3, 4), "add_still_works");
    assert_equal(1, calc.subtract(5, 4), "subtract_still_works");
    assert_equal(12, calc.multiply(3, 4), "multiply_still_works");
}

int main() {
    printf("Running TDD Calculator Enhancement Tests...\n");
    printf("(This shows the final result after complete TDD cycles)\n\n");
    
    // Run all tests in order of TDD development
    printf("--- TDD Cycle 1: Basic Power Function ---\n");
    test_power_basic();
    
    printf("\n--- TDD Cycle 2: Zero Exponent ---\n");
    test_power_zero_exponent();
    
    printf("\n--- TDD Cycle 3: Exponent of One ---\n");
    test_power_one_exponent();
    
    printf("\n--- TDD Cycle 4: General Cases ---\n");
    test_power_larger_exponents();
    
    printf("\n--- TDD Cycle 5: Edge Cases ---\n");
    test_power_edge_cases();
    
    // Verify we didn't break existing functionality
    test_existing_functions();
    
    print_test_summary();
    
    printf("\n=== TDD Process Summary ===\n");
    printf("1. Started with simplest test (2^3 = 8)\n");
    printf("2. Added edge case (any^0 = 1)\n");
    printf("3. Added another edge case (any^1 = any)\n");
    printf("4. Generalized with loop for larger exponents\n");
    printf("5. Added comprehensive edge cases\n");
    printf("6. Verified existing functionality unchanged\n");
    printf("\nTDD Benefits Demonstrated:\n");
    printf("- Incremental development with confidence\n");
    printf("- Each step builds on previous working code\n");
    printf("- Comprehensive test coverage achieved naturally\n");
    printf("- Regression testing built-in\n");
    
    return 0;
}

/*
Compilation command:
g++ -o test_tdd_calculator problem_3_1_solution.cpp

Expected Output:
Running TDD Calculator Enhancement Tests...
(This shows the final result after complete TDD cycles)

--- TDD Cycle 1: Basic Power Function ---
[PASS] power_2_cubed

--- TDD Cycle 2: Zero Exponent ---
[PASS] power_any_number_to_zero
[PASS] power_large_number_to_zero

--- TDD Cycle 3: Exponent of One ---
[PASS] power_three_to_one
[PASS] power_seventeen_to_one

--- TDD Cycle 4: General Cases ---
[PASS] power_2_to_10
[PASS] power_2_to_5
[PASS] power_3_to_4

--- TDD Cycle 5: Edge Cases ---
[PASS] power_zero_base
[PASS] power_zero_to_zero
[PASS] power_one_to_large_exponent
[PASS] power_negative_base_even_exp
[PASS] power_negative_base_odd_exp

--- Testing Existing Calculator Functions ---
[PASS] add_still_works
[PASS] subtract_still_works
[PASS] multiply_still_works

=== Test Summary ===
Tests passed: 13
Tests failed: 0
🎉 All tests passed!

=== TDD Process Summary ===
1. Started with simplest test (2^3 = 8)
2. Added edge case (any^0 = 1)
3. Added another edge case (any^1 = any)
4. Generalized with loop for larger exponents
5. Added comprehensive edge cases
6. Verified existing functionality unchanged

TDD Benefits Demonstrated:
- Incremental development with confidence
- Each step builds on previous working code
- Comprehensive test coverage achieved naturally
- Regression testing built-in

Key Learning Points:
1. TDD forces you to think about requirements before implementation
2. Each cycle builds confidence - you never break working code
3. Tests become documentation of expected behavior
4. Edge cases emerge naturally through the TDD process
5. Refactoring is safe because tests catch regressions
6. Final implementation is thoroughly tested by design
*/