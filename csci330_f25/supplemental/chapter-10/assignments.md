# Chapter 10: Testing - Problem Sets

## Instructions
- Complete these problems after reading Chapter 10 and working through the lesson plan
- Each problem builds on testing concepts and practical skills
- **Time expectation**: 2.25 hours total for all three problem sets
- Focus on writing clear, comprehensive tests that actually catch bugs

---

## Problem Set 1: Basic Testing Foundations (45 minutes)

### Problem 1.1: Simple Assertion Testing
**Objective**: Create and use basic assertion functions

Write a simple testing framework with these functions:
```cpp
void assert_equal(int expected, int actual, const char* test_name);
void assert_true(bool condition, const char* test_name);
void run_tests();  // Prints summary of passed/failed tests
```

**Template to get you started**:
```cpp
#include <cstdio>

// Global test counters
int tests_passed = 0;
int tests_failed = 0;

void assert_equal(int expected, int actual, const char* test_name) {
    // Your implementation here
    // Print PASSED or FAILED message
    // Update counters
}

void assert_true(bool condition, const char* test_name) {
    // Your implementation here
}

void run_tests() {
    // Print test summary
}

// Simple function to test
int add(int a, int b) {
    return a + b;
}

int main() {
    // Test the add function
    assert_equal(5, add(2, 3), "add_positive_numbers");
    assert_equal(0, add(-1, 1), "add_negative_positive");
    assert_true(add(0, 0) == 0, "add_zeros");
    
    run_tests();
    return 0;
}
```

### Problem 1.2: Testing Edge Cases
**Objective**: Practice testing boundary conditions

Test this potentially buggy function thoroughly:
```cpp
int safe_divide(int numerator, int denominator) {
    if (denominator == 0) {
        return -1;  // Error indicator
    }
    return numerator / denominator;
}
```

Write tests for:
- Normal division cases
- Division by zero (should return -1)
- Division resulting in zero
- Division with negative numbers

### Problem 1.3: Finding Bugs Through Testing
**Objective**: Use tests to discover bugs

This function has subtle bugs. Write comprehensive tests to find them:
```cpp
#include <string>

// Function to test - has bugs!
bool is_valid_email(const std::string& email) {
    // Check if email contains @ symbol
    bool has_at = false;
    for (char c : email) {
        if (c == '@') {
            has_at = true;
            break;
        }
    }
    
    // Check if email has content before and after @
    int at_pos = email.find('@');
    if (!has_at || at_pos == 0 || at_pos == email.length() - 1) {
        return false;
    }
    
    return true;
}
```

**Your task**: Write at least 6 tests that will reveal the bugs in this function.

---

## Problem Set 2: Class Testing (60 minutes)

### Problem 2.1: Testing a BankAccount Class
**Objective**: Test object-oriented code with state

Test this `BankAccount` class thoroughly:
```cpp
#include <string>

class BankAccount {
private:
    std::string owner;
    double balance;
    
public:
    BankAccount(const std::string& owner_name) 
        : owner(owner_name), balance(0.0) {}
    
    bool deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            return true;
        }
        return false;
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    double get_balance() const {
        return balance;
    }
    
    std::string get_owner() const {
        return owner;
    }
};
```

**Required tests**:
1. Test account creation with proper owner name
2. Test successful deposits
3. Test invalid deposits (negative amounts, zero)
4. Test successful withdrawals
5. Test invalid withdrawals (insufficient funds, negative amounts)
6. Test balance accuracy after multiple operations

**Template structure**:
```cpp
void test_account_creation() {
    BankAccount account("Alice");
    assert_equal(0.0, account.get_balance(), "initial_balance_zero");
    // Add more assertions
}

void test_deposit() {
    // Your tests here
}

void test_withdraw() {
    // Your tests here
}

// Add more test functions...

int main() {
    test_account_creation();
    test_deposit();
    test_withdraw();
    // Call other test functions
    
    run_tests();
    return 0;
}
```

### Problem 2.2: Testing String Utilities
**Objective**: Test utility functions with various string inputs

Create comprehensive tests for these string utility functions:
```cpp
#include <string>
#include <vector>

bool starts_with(const std::string& str, const std::string& prefix) {
    if (prefix.length() > str.length()) return false;
    return str.substr(0, prefix.length()) == prefix;
}

std::string remove_spaces(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

std::vector<std::string> split_by_comma(const std::string& str) {
    std::vector<std::string> result;
    std::string current = "";
    
    for (char c : str) {
        if (c == ',') {
            result.push_back(current);
            current = "";
        } else {
            current += c;
        }
    }
    result.push_back(current);  // Add last part
    return result;
}
```

**Test each function with**:
- Normal cases
- Empty string inputs
- Edge cases (string equals prefix, no commas, only spaces)
- Boundary conditions

### Problem 2.3: Setup and Teardown
**Objective**: Practice test organization with setup/cleanup

Create a test class that manages setup and cleanup:
```cpp
class TestRunner {
private:
    int tests_run;
    int tests_passed;
    
public:
    TestRunner() : tests_run(0), tests_passed(0) {}
    
    void run_test(bool (*test_function)(), const char* test_name) {
        // Your implementation: call test function, track results
    }
    
    void print_summary() {
        // Print final test results
    }
};
```

Use this to organize your BankAccount tests from Problem 2.1.

---

## Problem Set 3: Test-Driven Development (40 minutes)

### Problem 3.1: TDD Calculator Enhancement
**Objective**: Practice the Red-Green-Refactor cycle

You have this basic Calculator class:
```cpp
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
    int multiply(int a, int b) { return a * b; }
    
    // TODO: Add power function using TDD
};
```

**Using TDD, add a `power` function**:
1. **Red**: Write a test for `power(2, 3)` should return 8 - it will fail
2. **Green**: Implement minimal `power` function to make test pass
3. **Refactor**: Improve implementation if needed
4. **Repeat**: Add tests for `power(5, 0)`, `power(3, 1)`, `power(2, 10)`

**Document your TDD process**:
- Show each test you write
- Show the minimal implementation that makes it pass
- Note any refactoring you do

### Problem 3.2: TDD String Validator
**Objective**: Build a complete function using TDD

Using TDD, create a function `bool is_valid_password(const std::string& password)` that validates passwords.

**Requirements** (implement one test at a time):
1. Password must be at least 8 characters long
2. Password must contain at least one digit
3. Password must contain at least one uppercase letter
4. Password must contain at least one lowercase letter

**TDD Process**:
1. Write test for length requirement (fails)
2. Implement minimal code to pass
3. Write test for digit requirement (fails)
4. Implement minimal code to pass
5. Continue for each requirement

### Problem 3.3: Test Debugging Challenge
**Objective**: Debug failing tests and improve implementations

Here are some failing tests. Fix the code to make them pass:

```cpp
// These tests are failing - fix the implementations!

void test_buggy_fibonacci() {
    assert_equal(0, fibonacci(0), "fib_zero");
    assert_equal(1, fibonacci(1), "fib_one");
    assert_equal(1, fibonacci(2), "fib_two");
    assert_equal(2, fibonacci(3), "fib_three");
    assert_equal(5, fibonacci(5), "fib_five");
}

// Buggy implementation - fix it!
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void test_buggy_reverse_string() {
    assert_equal("olleh", reverse_string("hello"), "reverse_hello");
    assert_equal("", reverse_string(""), "reverse_empty");
    assert_equal("a", reverse_string("a"), "reverse_single");
}

// Buggy implementation - fix it!
std::string reverse_string(const std::string& str) {
    std::string result;
    for (int i = str.length(); i >= 0; i--) {
        result += str[i];
    }
    return result;
}
```

Run the tests, see what fails, and fix the implementations.

---

## Submission Guidelines

**For each problem set**:
1. Include all source code with clear test functions
2. Show sample test output (passed/failed messages)
3. For TDD problems, document your red-green-refactor process
4. Include notes on any bugs you found and how tests helped

**File organization**:
```
chapter10_solutions/
├── problem_set_1/
│   ├── problem_1_1_simple_assertions.cpp
│   ├── problem_1_2_edge_cases.cpp
│   └── problem_1_3_bug_hunting.cpp
├── problem_set_2/
│   ├── problem_2_1_bank_account_tests.cpp
│   ├── problem_2_2_string_utilities_tests.cpp
│   └── problem_2_3_test_runner.cpp
├── problem_set_3/
│   ├── problem_3_1_tdd_calculator.cpp
│   ├── problem_3_2_tdd_password_validator.cpp
│   └── problem_3_3_debug_tests.cpp
└── README.md (with compilation and testing notes)
```

**Testing Checklist**:
- [ ] All test functions have clear, descriptive names
- [ ] Tests cover normal cases, edge cases, and error conditions  
- [ ] Test output clearly shows what passed/failed
- [ ] Code compiles and runs without errors
- [ ] TDD process documented for applicable problems

**Compilation Instructions:**

**Choose your workflow:**

**Docker/Command Line:**
```bash
g++ -std=c++17 -Wall -Wextra -g -o test_program test_program.cpp
```

**VS Code (any workflow):**
- Press `Ctrl+Shift+B` (or `Cmd+Shift+B` on macOS)
- Or use Terminal → Run Build Task

**VS Code Testing Tips for Chapter 10:**
- Use VS Code's Test Explorer for visual test management
- Set breakpoints in failing tests to debug step-by-step
- Use integrated terminal to run test suites
- Watch variables during test execution to understand failures

**Expected time commitment**: 2.25 hours total. Focus on quality over quantity - better to have fewer, excellent tests than many poor ones!

## Success Criteria

You've mastered Chapter 10 testing concepts when you can:
- Write clear, focused unit tests
- Use tests to find bugs in existing code
- Apply test-driven development to build new features
- Organize tests logically and run them systematically
- Debug both test code and implementation code

Remember: Good tests are like good documentation - they explain what your code should do and verify that it actually does it!