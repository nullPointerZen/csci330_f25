# Chapter 10: Testing - Quick Help Guide

## Essential Testing Concepts (5-Minute Review)

### Testing vs Debugging
| Testing | Debugging |
|---------|-----------|
| **Prevents** bugs | **Fixes** bugs |
| **Systematic** checking | **Reactive** investigation |
| **Automated** execution | **Manual** investigation |
| **Documentation** of behavior | **Problem-solving** process |

### The Testing Mindset
**Before:** "My code works because I tried it once"  
**After:** "My code works because I tested all the important cases"

## Quick Testing Framework Template

```cpp
#include <cstdio>

// Simple test framework
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

void print_summary() {
    printf("\n=== Test Summary ===\n");
    printf("Passed: %d\n", tests_passed);
    printf("Failed: %d\n", tests_failed);
    printf("Total:  %d\n", tests_passed + tests_failed);
}
```

## Common Testing Patterns

### 1. Arrange-Act-Assert (AAA) Pattern
```cpp
void test_calculator_add() {
    // Arrange: Set up test data
    Calculator calc;  
    int a = 5, b = 3;
    
    // Act: Execute the function
    int result = calc.add(a, b);
    
    // Assert: Verify the result
    assert_equal(8, result, "calculator_add_positive");
}
```

### 2. Testing Edge Cases Checklist
**For every function, test:**
- [ ] Normal/typical inputs
- [ ] Boundary values (0, -1, maximum values)
- [ ] Invalid inputs (negative when positive expected)
- [ ] Empty inputs (empty strings, null pointers)
- [ ] Extreme inputs (very large numbers, very long strings)

### 3. Class Testing Template
```cpp
void test_class_name() {
    // Test constructor
    MyClass obj("test_param");
    assert_true(obj.is_valid(), "constructor_creates_valid_object");
    
    // Test normal operation
    bool result = obj.do_something();
    assert_true(result, "normal_operation_succeeds");
    
    // Test state changes
    int initial_value = obj.get_value();
    obj.modify_value(10);
    assert_equal(initial_value + 10, obj.get_value(), "state_change_correct");
}
```

## TDD Quick Reference

### The Red-Green-Refactor Cycle
1. **🔴 Red**: Write a failing test
2. **🟢 Green**: Write minimal code to pass
3. **🔄 Refactor**: Improve code quality
4. **Repeat**: Add next test

### TDD Example in 3 Steps
```cpp
// Step 1: Red - Write failing test
void test_power_function() {
    assert_equal(8, power(2, 3), "power_2_cubed");
    // This will fail because power() doesn't exist yet
}

// Step 2: Green - Minimal implementation
int power(int base, int exp) {
    if (base == 2 && exp == 3) return 8;  // Just make this test pass
    return 0;  // Wrong, but minimal
}

// Step 3: Refactor - Proper implementation after more tests
int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}
```

## Testing Troubleshooting

### "My test passes but my code is wrong"
**Problem**: Test doesn't cover the actual bug  
**Solution**: Add more test cases, especially edge cases

```cpp
// Weak test
assert_equal(4, divide(8, 2), "divide_normal");

// Better tests
assert_equal(4, divide(8, 2), "divide_normal");
assert_equal(0, divide(0, 5), "divide_zero_numerator");
assert_equal(-2, divide(-6, 3), "divide_negative");
// Don't forget: What about divide(5, 0)?
```

### "My test fails but my code looks right"
**Problem**: Test has wrong expected value or test logic error  
**Solution**: Double-check your expected values

```cpp
// Wrong expected value
assert_equal(9, 2 * 2, "multiply_test");  // Should be 4, not 9!

// Wrong test logic
assert_true(is_even(3), "three_is_even");  // 3 is not even!
```

### "I don't know what to test"
**Start with these questions:**
1. What should this function return for normal inputs?
2. What happens with edge cases (0, empty, negative)?
3. What happens with invalid inputs?
4. If this is a class method, does it change object state correctly?

## Quick Compilation & Running

```bash
# Compile your test file
g++ -o run_tests my_tests.cpp

# Run tests
./run_tests

# Example output you want to see:
# [PASS] add_positive_numbers
# [PASS] add_negative_numbers  
# [FAIL] add_with_overflow: expected 100, got -156
# 
# === Test Summary ===
# Passed: 2
# Failed: 1
# Total:  3
```

## Common Beginner Mistakes

| Mistake | Problem | Fix |
|---------|---------|-----|
| **Only testing happy path** | Bugs hide in edge cases | Always test boundaries and errors |
| **Tests too complex** | Hard to understand failures | One concept per test function |
| **No test names** | Can't tell what failed | Use descriptive test names |
| **Testing implementation details** | Tests break when refactoring | Test behavior, not how it's implemented |

## Language Comparison Cheat Sheet

### Python unittest → C++ Testing
```python
# Python
def test_add(self):
    self.assertEqual(calculator.add(2, 3), 5)
```
```cpp
// C++
void test_add() {
    assert_equal(5, calculator.add(2, 3), "add_two_three");
}
```

### Java JUnit → C++ Testing
```java
// Java
@Test
public void testAdd() {
    assertEquals(5, calculator.add(2, 3));
}
```
```cpp
// C++
void test_add() {
    assert_equal(5, calculator.add(2, 3), "add_two_three");
}
```

## When You're Stuck

### Test Writing Paralysis
**Problem**: "I don't know where to start"  
**Solution**: Start with the simplest possible test
```cpp
// Start here - just test that your function exists and compiles
void test_function_exists() {
    int result = my_function(1);  // Does it compile?
    assert_true(true, "function_exists");  // Always passes
}
```

### Test Debugging
**Problem**: "My test is failing and I don't know why"  
**Solution**: Add debug prints
```cpp
void test_debug_example() {
    int expected = 10;
    int actual = my_function(5);
    
    printf("DEBUG: expected=%d, actual=%d\n", expected, actual);
    assert_equal(expected, actual, "my_function_test");
}
```

### Overwhelm
**Problem**: "There are too many things to test"  
**Solution**: Test one thing at a time
1. Pick the most important behavior
2. Write one test for it
3. Make it pass
4. Move to next most important behavior

## Success Checklist

After working through Chapter 10, you should be able to:
- [ ] Write assertion functions that clearly report pass/fail
- [ ] Test normal cases and edge cases for any function
- [ ] Use TDD to build a simple function from scratch
- [ ] Debug failing tests to improve your code
- [ ] Organize tests logically with clear names
- [ ] Understand why testing makes development faster (not slower!)

**Remember**: Testing isn't about perfection - it's about confidence. Good tests let you change your code without fear!