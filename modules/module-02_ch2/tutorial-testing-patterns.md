# Tutorial: C++ Testing and Validation Patterns

## 🎯 Learning Objectives

After completing this tutorial, you will:
- Design systematic test cases for C++ programs
- Implement input validation patterns to prevent crashes
- Debug programs using test-driven approaches
- Handle edge cases and error conditions gracefully
- Verify program correctness before submission

**⏱️ Time Estimate**: 45-60 minutes  
**Prerequisites**: Completed Chapter 2 lecture notes and VS Code mastery tutorial

---

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] Completed Chapter 2 lecture notes (types, arrays, basic I/O)
- [ ] VS Code development workflow mastery
- [ ] Understanding of fundamental C++ types and memory concepts
- [ ] Can compile and debug C++ programs

**🚫 Don't continue** until you can create, compile, and run basic C++ programs.

---

## 🧪 Section 1: Testing Methodology (15 minutes)

### The Problem: "It Works on My Machine"

Most beginning programmers test like this:
```cpp
// Bad testing approach
int main() {
    // Try one example
    int result = calculate_average(10, 20, 30);
    std::cout << result << std::endl;  // "20 - looks good!"
    return 0;
}
```

**What's wrong?** This tests only one "happy path" scenario.

### Systematic Testing Strategy

Professional developers test using **categories**:

#### **1. Happy Path Testing**
- Normal, expected inputs
- Typical use cases
- Should work perfectly

#### **2. Edge Case Testing**  
- Boundary conditions
- Minimum/maximum values
- Empty or single-element data

#### **3. Error Case Testing**
- Invalid inputs
- Unexpected conditions
- Program should handle gracefully

#### **4. Integration Testing**
- Multiple components working together
- Real-world scenarios

### Testing Template Pattern

Here's a systematic testing pattern you can use for every program:

```cpp
#include <iostream>
#include <cassert>  // For simple testing

// Your function here
double calculate_average(double a, double b, double c) {
    return (a + b + c) / 3.0;
}

void test_happy_path() {
    std::cout << "Testing happy path cases...\n";
    
    // Test 1: Normal positive numbers
    double result1 = calculate_average(10, 20, 30);
    assert(result1 == 20.0);
    std::cout << "✓ Normal positive numbers: " << result1 << std::endl;
    
    // Test 2: Mixed positive/negative
    double result2 = calculate_average(-10, 10, 20);
    assert(result2 == 20.0/3.0);
    std::cout << "✓ Mixed pos/neg numbers: " << result2 << std::endl;
}

void test_edge_cases() {
    std::cout << "Testing edge cases...\n";
    
    // Test 1: All zeros
    double result1 = calculate_average(0, 0, 0);
    assert(result1 == 0.0);
    std::cout << "✓ All zeros: " << result1 << std::endl;
    
    // Test 2: Very large numbers
    double result2 = calculate_average(1e6, 2e6, 3e6);
    assert(result2 == 2e6);
    std::cout << "✓ Large numbers: " << result2 << std::endl;
}

int main() {
    test_happy_path();
    test_edge_cases();
    std::cout << "All tests passed!\n";
    return 0;
}
```

### ✅ Checkpoint 1: Basic Testing Pattern
**Test**: Apply systematic testing to a simple function

Create a function that finds the maximum of three numbers:
```cpp
int find_max(int a, int b, int c) {
    // Your implementation here
}
```

**Your task:**
- [ ] Implement the `find_max` function
- [ ] Create `test_happy_path()` function with 3 test cases
- [ ] Create `test_edge_cases()` function with 3 test cases
- [ ] Use `assert()` to verify results
- [ ] All tests should pass

**Test cases to include:**
- Happy path: Different orderings (max first, middle, last)
- Edge cases: All equal, negative numbers, zero values

**Success Criteria**: You have a systematic testing approach that catches bugs before submission.

---

## 🛡️ Section 2: Input Validation Patterns (15 minutes)

### The Problem: Programs That Crash

Consider this typical student code:
```cpp
int main() {
    int age;
    std::cout << "Enter your age: ";
    std::cin >> age;  // What if they enter "hello"?
    
    int days = age * 365;  // Garbage calculation if input failed
    std::cout << "You've lived " << days << " days\n";
    return 0;
}
```

**Problem**: No validation - crashes or produces garbage on invalid input.

### Input Validation Patterns

#### **Pattern 1: Basic Input Validation**
```cpp
#include <iostream>
#include <limits>

int get_valid_age() {
    int age;
    
    while (true) {
        std::cout << "Enter your age (0-120): ";
        
        if (!(std::cin >> age)) {
            // Input wasn't a number
            std::cout << "Error: Please enter a number.\n";
            std::cin.clear();  // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        if (age < 0 || age > 120) {
            std::cout << "Error: Age must be between 0 and 120.\n";
            continue;
        }
        
        return age;  // Valid input!
    }
}
```

#### **Pattern 2: Array Bounds Validation**
```cpp
#include <array>

template<size_t N>
int get_valid_index(const std::array<int, N>& arr) {
    int index;
    
    while (true) {
        std::cout << "Enter index (0-" << (N-1) << "): ";
        
        if (!(std::cin >> index)) {
            std::cout << "Error: Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        if (index < 0 || index >= static_cast<int>(N)) {
            std::cout << "Error: Index must be between 0 and " << (N-1) << ".\n";
            continue;
        }
        
        return index;
    }
}
```

#### **Pattern 3: Menu Validation**
```cpp
int get_menu_choice() {
    int choice;
    
    std::cout << "\nMenu:\n";
    std::cout << "1. Option A\n";
    std::cout << "2. Option B\n"; 
    std::cout << "3. Option C\n";
    std::cout << "4. Exit\n";
    
    while (true) {
        std::cout << "Enter choice (1-4): ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Error: Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        if (choice >= 1 && choice <= 4) {
            return choice;
        }
        
        std::cout << "Error: Please enter 1, 2, 3, or 4.\n";
    }
}
```

### ✅ Checkpoint 2: Input Validation Practice
**Test**: Create a robust input validation function

Create a function that gets a valid test score (0-100):

```cpp
double get_test_score(const std::string& prompt) {
    // Your implementation here
    // Should handle:
    // - Non-numeric input
    // - Negative numbers
    // - Numbers > 100
    // - Keep asking until valid input
}
```

**Your task:**
- [ ] Implement `get_test_score()` function
- [ ] Test with invalid inputs: "hello", -5, 150
- [ ] Test with valid inputs: 0, 50, 100, 85.5
- [ ] Function should never crash or accept invalid input

**Test scenarios:**
1. Run program, enter "abc" - should ask again
2. Run program, enter "-10" - should ask again  
3. Run program, enter "150" - should ask again
4. Run program, enter "85.5" - should accept

**Success Criteria**: Your function handles all invalid inputs gracefully and only accepts valid scores.

---

## 🔍 Section 3: Debugging with Test Cases (15 minutes)

### Test-Driven Debugging Approach

Instead of guessing what's wrong, use tests to isolate bugs:

#### **Example: Debugging Array Processing**

Suppose you have a buggy function:
```cpp
// Buggy function - calculates average of array
double calculate_average(const int arr[], int size) {
    int sum = 0;
    for (int i = 1; i <= size; i++) {  // Bug: starts at 1, goes to size
        sum += arr[i];
    }
    return sum / size;
}
```

#### **Systematic Debug Testing**
```cpp
void debug_with_tests() {
    std::cout << "Debug testing...\n";
    
    // Test 1: Simple case to check basic logic
    int test1[] = {10, 20, 30};
    double avg1 = calculate_average(test1, 3);
    std::cout << "Test 1 - Expected: 20, Got: " << avg1 << std::endl;
    
    // Test 2: Single element to check boundary
    int test2[] = {42};
    double avg2 = calculate_average(test2, 1);
    std::cout << "Test 2 - Expected: 42, Got: " << avg2 << std::endl;
    
    // Test 3: All same numbers to check calculation
    int test3[] = {5, 5, 5, 5};
    double avg3 = calculate_average(test3, 4);
    std::cout << "Test 3 - Expected: 5, Got: " << avg3 << std::endl;
}
```

**What the tests reveal:**
- Test 1: Wrong result → loop or calculation error
- Test 2: Crash or garbage → boundary condition bug  
- Test 3: Wrong result confirms calculation bug

### Debugging Process with VS Code

1. **Set breakpoints** in your function
2. **Run with debugger** (`F5`)
3. **Step through** each test case
4. **Watch variables** to see what's happening
5. **Identify discrepancy** between expected and actual

### ✅ Checkpoint 3: Debug Using Tests
**Test**: Find and fix bugs using systematic testing

Here's a buggy function that's supposed to find the minimum value in an array:
```cpp
int find_minimum(const int arr[], int size) {
    int min = 0;  // Potential bug here
    for (int i = 0; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}
```

**Your task:**
1. **Create test cases:**
   - [ ] Test with positive numbers: {10, 5, 8} → should return 5
   - [ ] Test with negative numbers: {-3, -1, -5} → should return -5  
   - [ ] Test with mixed: {-2, 0, 3} → should return -2
   - [ ] Test with single element: {42} → should return 42

2. **Use debugger to find bugs:**
   - [ ] Set breakpoint in `find_minimum`
   - [ ] Run each test case
   - [ ] Watch `min` variable change
   - [ ] Identify what's wrong with initialization

3. **Fix the bugs** and verify all tests pass

**Success Criteria**: You can systematically identify and fix bugs using test cases and debugging.

---

## 📊 Section 4: Comprehensive Testing Strategy (10 minutes)

### Real-World Testing Template

Here's a complete testing framework you can adapt for any assignment:

```cpp
#include <iostream>
#include <cassert>
#include <vector>
#include <string>

class TestRunner {
private:
    int tests_passed = 0;
    int tests_failed = 0;
    
public:
    void test_case(const std::string& name, bool condition, const std::string& message = "") {
        std::cout << "Testing " << name << "... ";
        if (condition) {
            std::cout << "✓ PASS\n";
            tests_passed++;
        } else {
            std::cout << "✗ FAIL";
            if (!message.empty()) {
                std::cout << " - " << message;
            }
            std::cout << std::endl;
            tests_failed++;
        }
    }
    
    void print_summary() {
        std::cout << "\n=== Test Summary ===\n";
        std::cout << "Passed: " << tests_passed << std::endl;
        std::cout << "Failed: " << tests_failed << std::endl;
        std::cout << "Total:  " << (tests_passed + tests_failed) << std::endl;
        
        if (tests_failed == 0) {
            std::cout << "🎉 All tests passed!\n";
        } else {
            std::cout << "⚠️  Some tests failed - fix before submission!\n";
        }
    }
};

// Example usage for testing a calculator function
double divide(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}

void test_calculator() {
    TestRunner runner;
    
    // Happy path tests
    runner.test_case("normal division", divide(10, 2) == 5.0);
    runner.test_case("decimal result", std::abs(divide(1, 3) - 0.333333) < 0.0001);
    
    // Edge case tests
    runner.test_case("divide by 1", divide(42, 1) == 42);
    runner.test_case("divide zero", divide(0, 5) == 0);
    
    // Error case tests
    bool caught_exception = false;
    try {
        divide(1, 0);
    } catch (const std::runtime_error&) {
        caught_exception = true;
    }
    runner.test_case("division by zero throws", caught_exception);
    
    runner.print_summary();
}
```

### ✅ Checkpoint 4: Complete Testing Framework
**Test**: Create comprehensive tests for a complex function

Create a function that validates and processes student grades:

```cpp
struct GradeResult {
    bool valid;
    char letter_grade;
    std::string message;
};

GradeResult process_grade(double score) {
    // Your implementation:
    // - Return {false, '?', error_message} for invalid input
    // - Return {true, letter, "Valid"} for valid grades
    // - Grade scale: A=90+, B=80-89, C=70-79, D=60-69, F=0-59
    // - Handle edge cases appropriately
}
```

**Your testing requirements:**
- [ ] **Happy path**: Test all letter grade ranges
- [ ] **Edge cases**: Test boundary values (90.0, 89.9, etc.)
- [ ] **Error cases**: Test negative numbers, numbers > 100
- [ ] **Integration**: Test the complete struct return values
- [ ] Use the TestRunner framework above

**Success Criteria**: Your testing suite is so comprehensive that you're confident submitting the function.

---

## 🎯 Final Challenge: Complete Testing Workflow

**Time Limit**: 15 minutes

Create a complete program with full testing for a real-world scenario:

### **Assignment: Grade Book Calculator**

Create a program that:
1. **Input**: Gets 5 test scores from user (with validation)
2. **Processing**: Calculates average, finds highest/lowest  
3. **Output**: Displays results with letter grade

### **Requirements**
- **Input validation** for all scores (0-100)
- **Comprehensive testing** for all functions
- **Error handling** for edge cases
- **User-friendly interface**

### **Implementation Template**
```cpp
#include <iostream>
#include <array>
#include <algorithm>
#include <limits>

// Your functions here
double get_valid_score(int test_number);
double calculate_average(const std::array<double, 5>& scores);
char get_letter_grade(double average);
void display_results(const std::array<double, 5>& scores);

// Your test functions here
void test_all_functions();

int main() {
    // First, run all tests
    test_all_functions();
    
    // Then run the actual program
    std::cout << "\n=== Grade Book Calculator ===\n";
    
    std::array<double, 5> scores;
    for (int i = 0; i < 5; i++) {
        scores[i] = get_valid_score(i + 1);
    }
    
    display_results(scores);
    return 0;
}
```

### ✅ Final Verification Checklist
- [ ] **Input Validation**: All score inputs validated (0-100)
- [ ] **Function Tests**: Each function has comprehensive tests
- [ ] **Edge Cases**: Boundary conditions tested (0, 100, etc.)
- [ ] **Error Handling**: Invalid inputs handled gracefully
- [ ] **Integration**: Full program works with various inputs
- [ ] **User Experience**: Clear prompts and error messages
- [ ] **Testing First**: Tests run before main program

---

## 🎉 Congratulations!

You've mastered systematic testing and validation for C++ programs! You now know how to:
- Design comprehensive test cases covering all scenarios
- Implement robust input validation patterns
- Debug systematically using test-driven approaches  
- Create professional-quality, crash-resistant programs
- Verify correctness before submission

### **Key Patterns You've Mastered**

#### **Testing Categories**
- **Happy Path**: Normal, expected cases
- **Edge Cases**: Boundary conditions and limits
- **Error Cases**: Invalid inputs and error conditions

#### **Validation Patterns**
- **Input Stream Validation**: Check `cin` success
- **Range Validation**: Verify values within acceptable bounds
- **Loop-Until-Valid**: Keep asking for correct input

#### **Debug Strategy**
- **Test-Driven**: Create failing tests first
- **Systematic**: Test one component at a time
- **Visual**: Use debugger to watch variables

### **Next Steps**
- Apply these patterns to all Chapter 2 assignments
- Create tests BEFORE implementing solutions
- Never submit code without comprehensive testing
- Reference this tutorial when programs don't work as expected

### **Testing Mantra**
> **"If it's not tested, it's probably broken"**
> 
> Professional developers test everything. Now you can too!

**Keep this tutorial handy** - systematic testing will make you a dramatically better programmer!