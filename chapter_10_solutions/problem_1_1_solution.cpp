// Problem 1.1: Simple Assertion Testing Solution
// Demonstrates basic testing framework construction

#include <cstdio>

// Global test counters
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

void assert_true(bool condition, const char* test_name) {
    if (condition) {
        printf("[PASS] %s\n", test_name);
        tests_passed++;
    } else {
        printf("[FAIL] %s: condition was false\n", test_name);
        tests_failed++;
    }
}

void run_tests() {
    printf("\n=== Test Summary ===\n");
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_failed);
    printf("Total tests:  %d\n", tests_passed + tests_failed);
    
    if (tests_failed == 0) {
        printf("🎉 All tests passed!\n");
    } else {
        printf("❌ %d test(s) failed. Review and fix issues.\n", tests_failed);
    }
}

// Simple function to test
int add(int a, int b) {
    return a + b;
}

int main() {
    printf("Running basic assertion tests...\n\n");
    
    // Test the add function with various cases
    assert_equal(5, add(2, 3), "add_positive_numbers");
    assert_equal(0, add(-1, 1), "add_negative_positive");
    assert_equal(-5, add(-2, -3), "add_two_negatives");
    assert_true(add(0, 0) == 0, "add_zeros");
    assert_true(add(100, -100) == 0, "add_opposites");
    
    // Test edge cases
    assert_equal(1000000, add(500000, 500000), "add_large_numbers");
    
    run_tests();
    return 0;
}

/*
Compilation command:
g++ -o test_assertions problem_1_1_solution.cpp

Expected Output:
Running basic assertion tests...

[PASS] add_positive_numbers
[PASS] add_negative_positive
[PASS] add_two_negatives
[PASS] add_zeros
[PASS] add_opposites
[PASS] add_large_numbers

=== Test Summary ===
Tests passed: 6
Tests failed: 0
Total tests:  6
🎉 All tests passed!

Key Learning Points:
1. Test framework provides consistent reporting
2. Global counters track overall test results
3. Clear test names explain what's being tested
4. Summary helps identify overall success/failure
5. Good foundation for more complex testing
*/