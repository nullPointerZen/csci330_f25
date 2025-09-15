# Chapter 10: Testing - Complete Guide

## 🎯 Learning Objectives (5 minutes)

By the end of this chapter, you will:
1. **Understand** the importance of unit testing in C++ development
2. **Set up and use** a basic C++ unit testing framework
3. **Write** effective unit tests for C++ functions and classes
4. **Apply** test-driven development (TDD) basics in C++
5. **Debug** failed tests and improve code quality through testing
6. **Compare** C++ testing approaches with Python/Java frameworks

**⏱️ Time Budget: ~4.75 hours total**
- Learning: 2.5 hours
- Problems: 2.25 hours

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](./DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 🧪 Core Concepts: Testing in C++ (2.5 hours)

### 1. Why Testing Matters in C++

**C++ testing is crucial due to:**
- **Manual memory management** - Easy to create leaks and dangling pointers
- **No runtime type checking** - Template errors can be complex
- **Undefined behavior** - Buffer overflows, null pointer dereferencing
- **Complex compilation** - Linking errors, template instantiation issues

```cpp
// Example: Why we need tests for C++ memory management
class ResourceManager {
private:
    int* data;
    size_t size;
    
public:
    ResourceManager(size_t n) : size{n} {
        data = new int[size];  // What if this throws?
    }
    
    ~ResourceManager() {
        delete[] data;  // What if data is null? What if we delete twice?
    }
    
    int& at(size_t index) {
        return data[index];  // What if index >= size?
    }
};

// Without tests, these edge cases might go unnoticed!
```

### 2. Testing Frameworks Comparison

| Language | Popular Frameworks | Basic Assertion | Test Organization |
|----------|-------------------|-----------------|-------------------|
| **C++** | Catch2, Google Test, Simple Assert | `assert()`, `REQUIRE()` | Test functions/classes |
| **Python** | unittest, pytest | `assert`, `self.assertEqual()` | Methods or functions |
| **Java** | JUnit, TestNG | `assertEquals()`, `assertTrue()` | Methods in test classes |

### 3. Simple Testing Framework

**Let's build a minimal testing framework to understand the concepts:**

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <exception>
using namespace std;

class SimpleTest {
private:
    static vector<function<void()>> tests;
    static int total_tests;
    static int passed_tests;
    
public:
    static void add_test(const string& name, function<void()> test_func) {
        tests.push_back([name, test_func]() {
            cout << "Running test: " << name << "... ";
            try {
                test_func();
                cout << "PASSED" << endl;
                passed_tests++;
            } catch (const exception& e) {
                cout << "FAILED - " << e.what() << endl;
            } catch (...) {
                cout << "FAILED - Unknown exception" << endl;
            }
            total_tests++;
        });
    }
    
    static void run_all_tests() {
        cout << "Running " << tests.size() << " tests..." << endl;
        cout << "================================" << endl;
        
        for (auto& test : tests) {
            test();
        }
        
        cout << "================================" << endl;
        cout << "Tests passed: " << passed_tests << "/" << total_tests << endl;
        
        if (passed_tests == total_tests) {
            cout << "All tests passed! ✓" << endl;
        } else {
            cout << "Some tests failed! ✗" << endl;
        }
    }
    
    // Assertion helpers
    template<typename T>
    static void assert_equal(const T& expected, const T& actual, const string& message = "") {
        if (expected != actual) {
            throw runtime_error("Expected " + to_string(expected) + 
                              " but got " + to_string(actual) + 
                              (message.empty() ? "" : " - " + message));
        }
    }
    
    static void assert_true(bool condition, const string& message = "") {
        if (!condition) {
            throw runtime_error("Expected true but got false" + 
                              (message.empty() ? "" : " - " + message));
        }
    }
    
    static void assert_throws(function<void()> func, const string& message = "") {
        try {
            func();
            throw runtime_error("Expected exception but none was thrown" + 
                              (message.empty() ? "" : " - " + message));
        } catch (const runtime_error& e) {
            // Re-throw our own assertion errors
            if (string(e.what()).find("Expected exception") == 0) {
                throw;
            }
            // Other exceptions are expected
        } catch (...) {
            // Any exception is good
        }
    }
};

// Static member definitions
vector<function<void()>> SimpleTest::tests;
int SimpleTest::total_tests = 0;
int SimpleTest::passed_tests = 0;

// Macro for easier test registration
#define TEST(name, body) \
    static void test_##name() body \
    static bool name##_registered = (SimpleTest::add_test(#name, test_##name), true);
```

### 4. Test-Driven Development (TDD)

**TDD follows the Red-Green-Refactor cycle:**

1. **Red**: Write a failing test
2. **Green**: Write minimal code to make it pass
3. **Refactor**: Improve the code while keeping tests passing

```cpp
// Step 1: RED - Write failing test first
TEST(calculator_add, {
    Calculator calc;
    SimpleTest::assert_equal(5, calc.add(2, 3));
    SimpleTest::assert_equal(0, calc.add(-1, 1));
    SimpleTest::assert_equal(-5, calc.add(-2, -3));
})

// Step 2: GREEN - Write minimal implementation
class Calculator {
public:
    int add(int a, int b) {
        return a + b;  // Simplest implementation that passes
    }
};

// Step 3: REFACTOR - Improve if needed (in this case, it's already good)
```

### 5. Testing Best Practices

**Good Test Characteristics (FIRST):**
- **Fast**: Run quickly so you run them often
- **Independent**: Don't depend on other tests
- **Repeatable**: Same result every time
- **Self-validating**: Clear pass/fail, no manual checking
- **Timely**: Written just before or with the production code

```cpp
// Good test structure: Arrange-Act-Assert (AAA)
TEST(bank_account_deposit, {
    // Arrange
    BankAccount account{100.0};
    
    // Act
    account.deposit(50.0);
    
    // Assert
    SimpleTest::assert_equal(150.0, account.get_balance());
})

// Test edge cases and error conditions
TEST(bank_account_negative_deposit, {
    BankAccount account{100.0};
    
    SimpleTest::assert_throws([&]() {
        account.deposit(-10.0);
    }, "Should throw on negative deposit");
})
```

---

## 🧩 Hands-On Problems (2.25 hours)

### Problem Set 1: Basic Testing Setup (45 minutes)

#### Problem 1.1: Testing Simple Functions (15 minutes)
**Create tests for basic mathematical functions:**

```cpp
#include <iostream>
#include <cmath>
using namespace std;

// Include the SimpleTest framework from above

// Functions to test
int factorial(int n) {
    if (n < 0) throw invalid_argument("Factorial of negative number");
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

double safe_divide(double a, double b) {
    if (abs(b) < 1e-10) throw invalid_argument("Division by zero");
    return a / b;
}

// TODO: Write tests for these functions
TEST(factorial_positive, {
    SimpleTest::assert_equal(1, factorial(0));
    SimpleTest::assert_equal(1, factorial(1));
    SimpleTest::assert_equal(6, factorial(3));
    SimpleTest::assert_equal(24, factorial(4));
    SimpleTest::assert_equal(120, factorial(5));
})

TEST(factorial_negative, {
    SimpleTest::assert_throws([]() {
        factorial(-1);
    }, "Should throw on negative input");
})

TEST(is_prime_basic, {
    SimpleTest::assert_true(is_prime(2), "2 should be prime");
    SimpleTest::assert_true(is_prime(3), "3 should be prime");
    SimpleTest::assert_true(is_prime(5), "5 should be prime");
    SimpleTest::assert_true(is_prime(7), "7 should be prime");
    
    SimpleTest::assert_true(!is_prime(1), "1 should not be prime");
    SimpleTest::assert_true(!is_prime(4), "4 should not be prime");
    SimpleTest::assert_true(!is_prime(9), "9 should not be prime");
    SimpleTest::assert_true(!is_prime(15), "15 should not be prime");
})

TEST(safe_divide_normal, {
    SimpleTest::assert_equal(2.0, safe_divide(10.0, 5.0));
    SimpleTest::assert_equal(-2.0, safe_divide(-10.0, 5.0));
    SimpleTest::assert_equal(0.5, safe_divide(1.0, 2.0));
})

TEST(safe_divide_by_zero, {
    SimpleTest::assert_throws([]() {
        safe_divide(10.0, 0.0);
    }, "Should throw on division by zero");
})

int main() {
    SimpleTest::run_all_tests();
    return 0;
}
```

#### Problem 1.2: Testing a Simple Class (15 minutes)
**Create comprehensive tests for a Counter class:**

```cpp
// Counter class to test
class Counter {
private:
    int value;
    int max_value;
    
public:
    Counter(int initial = 0, int max = 100) : value{initial}, max_value{max} {
        if (initial < 0) throw invalid_argument("Initial value cannot be negative");
        if (max <= 0) throw invalid_argument("Max value must be positive");
        if (initial > max) throw invalid_argument("Initial value exceeds maximum");
    }
    
    void increment() {
        if (value >= max_value) {
            throw runtime_error("Counter at maximum value");
        }
        value++;
    }
    
    void decrement() {
        if (value <= 0) {
            throw runtime_error("Counter at minimum value");
        }
        value--;
    }
    
    void reset() {
        value = 0;
    }
    
    int get_value() const { return value; }
    int get_max() const { return max_value; }
    bool is_at_max() const { return value == max_value; }
    bool is_at_min() const { return value == 0; }
};

// TODO: Write comprehensive tests
TEST(counter_construction, {
    Counter c1;
    SimpleTest::assert_equal(0, c1.get_value());
    SimpleTest::assert_equal(100, c1.get_max());
    
    Counter c2{10, 50};
    SimpleTest::assert_equal(10, c2.get_value());
    SimpleTest::assert_equal(50, c2.get_max());
})

TEST(counter_invalid_construction, {
    SimpleTest::assert_throws([]() {
        Counter c{-1};
    }, "Negative initial value should throw");
    
    SimpleTest::assert_throws([]() {
        Counter c{0, 0};
    }, "Zero max value should throw");
    
    SimpleTest::assert_throws([]() {
        Counter c{10, 5};
    }, "Initial > max should throw");
})

TEST(counter_increment, {
    Counter c{0, 3};
    
    c.increment();
    SimpleTest::assert_equal(1, c.get_value());
    
    c.increment();
    SimpleTest::assert_equal(2, c.get_value());
    
    c.increment();
    SimpleTest::assert_equal(3, c.get_value());
    SimpleTest::assert_true(c.is_at_max());
    
    SimpleTest::assert_throws([&]() {
        c.increment();
    }, "Should throw at maximum");
})

TEST(counter_decrement, {
    Counter c{3};
    
    c.decrement();
    SimpleTest::assert_equal(2, c.get_value());
    
    c.decrement();
    c.decrement();
    SimpleTest::assert_equal(0, c.get_value());
    SimpleTest::assert_true(c.is_at_min());
    
    SimpleTest::assert_throws([&]() {
        c.decrement();
    }, "Should throw at minimum");
})

TEST(counter_reset, {
    Counter c{50};
    c.reset();
    SimpleTest::assert_equal(0, c.get_value());
    SimpleTest::assert_true(c.is_at_min());
})
```

#### Problem 1.3: Testing with Test Fixtures (15 minutes)
**Create reusable test setup for a BankAccount class:**

```cpp
class BankAccount {
private:
    double balance;
    string account_holder;
    
public:
    BankAccount(const string& holder, double initial_balance = 0.0) 
        : account_holder{holder}, balance{initial_balance} {
        if (initial_balance < 0) {
            throw invalid_argument("Initial balance cannot be negative");
        }
    }
    
    void deposit(double amount) {
        if (amount <= 0) throw invalid_argument("Deposit amount must be positive");
        balance += amount;
    }
    
    void withdraw(double amount) {
        if (amount <= 0) throw invalid_argument("Withdrawal amount must be positive");
        if (amount > balance) throw runtime_error("Insufficient funds");
        balance -= amount;
    }
    
    double get_balance() const { return balance; }
    string get_holder() const { return account_holder; }
    
    void transfer_to(BankAccount& other, double amount) {
        withdraw(amount);  // This might throw
        other.deposit(amount);
    }
};

// Test fixture helper
class BankAccountTestFixture {
public:
    BankAccount* account;
    BankAccount* other_account;
    
    void setup() {
        account = new BankAccount{"Alice", 100.0};
        other_account = new BankAccount{"Bob", 50.0};
    }
    
    void teardown() {
        delete account;
        delete other_account;
    }
};

// TODO: Write tests using the fixture pattern
TEST(bank_account_deposit, {
    BankAccountTestFixture fixture;
    fixture.setup();
    
    fixture.account->deposit(25.0);
    SimpleTest::assert_equal(125.0, fixture.account->get_balance());
    
    SimpleTest::assert_throws([&]() {
        fixture.account->deposit(-10.0);
    }, "Should throw on negative deposit");
    
    fixture.teardown();
})

TEST(bank_account_withdraw, {
    BankAccountTestFixture fixture;
    fixture.setup();
    
    fixture.account->withdraw(30.0);
    SimpleTest::assert_equal(70.0, fixture.account->get_balance());
    
    SimpleTest::assert_throws([&]() {
        fixture.account->withdraw(200.0);
    }, "Should throw on insufficient funds");
    
    fixture.teardown();
})

TEST(bank_account_transfer, {
    BankAccountTestFixture fixture;
    fixture.setup();
    
    fixture.account->transfer_to(*fixture.other_account, 25.0);
    
    SimpleTest::assert_equal(75.0, fixture.account->get_balance());
    SimpleTest::assert_equal(75.0, fixture.other_account->get_balance());
    
    SimpleTest::assert_throws([&]() {
        fixture.account->transfer_to(*fixture.other_account, 100.0);
    }, "Should throw on insufficient funds for transfer");
    
    fixture.teardown();
})
```

### Problem Set 2: Test-Driven Development (60 minutes)

#### Problem 2.1: TDD - String Utilities (25 minutes)
**Use TDD to build string utility functions:**

```cpp
#include <string>
#include <vector>
using namespace std;

// Step 1: Write tests FIRST (these will fail initially)
TEST(string_utils_trim, {
    SimpleTest::assert_equal(string("hello"), trim("  hello  "));
    SimpleTest::assert_equal(string("hello"), trim("hello"));
    SimpleTest::assert_equal(string(""), trim("   "));
    SimpleTest::assert_equal(string("hello world"), trim("  hello world  "));
})

TEST(string_utils_split, {
    vector<string> expected = {"hello", "world", "test"};
    vector<string> result = split("hello,world,test", ',');
    
    SimpleTest::assert_equal(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); i++) {
        SimpleTest::assert_equal(expected[i], result[i]);
    }
    
    // Test edge cases
    vector<string> empty_result = split("", ',');
    SimpleTest::assert_equal(size_t(0), empty_result.size());
    
    vector<string> single_result = split("hello", ',');
    SimpleTest::assert_equal(size_t(1), single_result.size());
    SimpleTest::assert_equal(string("hello"), single_result[0]);
})

TEST(string_utils_starts_with, {
    SimpleTest::assert_true(starts_with("hello world", "hello"));
    SimpleTest::assert_true(starts_with("test", "test"));
    SimpleTest::assert_true(!starts_with("hello", "world"));
    SimpleTest::assert_true(!starts_with("hi", "hello"));
    SimpleTest::assert_true(starts_with("anything", ""));  // Empty prefix
})

// Step 2: Now implement the functions to make tests pass
string trim(const string& str) {
    // TODO: Implement trim function
    if (str.empty()) return str;
    
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";  // All whitespace
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

vector<string> split(const string& str, char delimiter) {
    // TODO: Implement split function
    vector<string> result;
    if (str.empty()) return result;
    
    size_t start = 0;
    size_t pos = str.find(delimiter);
    
    while (pos != string::npos) {
        result.push_back(str.substr(start, pos - start));
        start = pos + 1;
        pos = str.find(delimiter, start);
    }
    
    result.push_back(str.substr(start));
    return result;
}

bool starts_with(const string& str, const string& prefix) {
    // TODO: Implement starts_with function
    if (prefix.length() > str.length()) return false;
    return str.substr(0, prefix.length()) == prefix;
}
```

#### Problem 2.2: TDD - Vector Math Library (35 minutes)
**Build a 2D vector math library using TDD:**

```cpp
#include <cmath>

// Step 1: Write tests for Vector2D class
TEST(vector2d_construction, {
    Vector2D v1;  // Default constructor
    SimpleTest::assert_equal(0.0, v1.x);
    SimpleTest::assert_equal(0.0, v1.y);
    
    Vector2D v2{3.0, 4.0};
    SimpleTest::assert_equal(3.0, v2.x);
    SimpleTest::assert_equal(4.0, v2.y);
})

TEST(vector2d_addition, {
    Vector2D v1{1.0, 2.0};
    Vector2D v2{3.0, 4.0};
    Vector2D result = v1 + v2;
    
    SimpleTest::assert_equal(4.0, result.x);
    SimpleTest::assert_equal(6.0, result.y);
})

TEST(vector2d_subtraction, {
    Vector2D v1{5.0, 7.0};
    Vector2D v2{2.0, 3.0};
    Vector2D result = v1 - v2;
    
    SimpleTest::assert_equal(3.0, result.x);
    SimpleTest::assert_equal(4.0, result.y);
})

TEST(vector2d_scalar_multiplication, {
    Vector2D v{3.0, 4.0};
    Vector2D result = v * 2.0;
    
    SimpleTest::assert_equal(6.0, result.x);
    SimpleTest::assert_equal(8.0, result.y);
})

TEST(vector2d_magnitude, {
    Vector2D v{3.0, 4.0};  // 3-4-5 triangle
    double mag = v.magnitude();
    SimpleTest::assert_equal(5.0, mag);
    
    Vector2D zero;
    SimpleTest::assert_equal(0.0, zero.magnitude());
})

TEST(vector2d_normalize, {
    Vector2D v{3.0, 4.0};
    Vector2D normalized = v.normalize();
    
    // Should have magnitude 1
    double mag = normalized.magnitude();
    SimpleTest::assert_true(abs(mag - 1.0) < 1e-10, "Normalized vector should have magnitude 1");
    
    // Should be in same direction
    SimpleTest::assert_equal(0.6, normalized.x);  // 3/5
    SimpleTest::assert_equal(0.8, normalized.y);  // 4/5
})

TEST(vector2d_dot_product, {
    Vector2D v1{2.0, 3.0};
    Vector2D v2{4.0, 5.0};
    double dot = v1.dot(v2);
    
    SimpleTest::assert_equal(23.0, dot);  // 2*4 + 3*5 = 8 + 15 = 23
    
    // Perpendicular vectors have dot product 0
    Vector2D v3{1.0, 0.0};
    Vector2D v4{0.0, 1.0};
    SimpleTest::assert_equal(0.0, v3.dot(v4));
})

// Step 2: Implement Vector2D class to make tests pass
class Vector2D {
public:
    double x, y;
    
    // TODO: Implement constructors
    Vector2D() : x{0.0}, y{0.0} {}
    Vector2D(double x_val, double y_val) : x{x_val}, y{y_val} {}
    
    // TODO: Implement operators
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D{x + other.x, y + other.y};
    }
    
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D{x - other.x, y - other.y};
    }
    
    Vector2D operator*(double scalar) const {
        return Vector2D{x * scalar, y * scalar};
    }
    
    // TODO: Implement mathematical operations
    double magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    Vector2D normalize() const {
        double mag = magnitude();
        if (mag == 0.0) return Vector2D{0.0, 0.0};
        return Vector2D{x / mag, y / mag};
    }
    
    double dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }
};
```

### Problem Set 3: Advanced Testing Patterns (40 minutes)

#### Problem 3.1: Mock Objects and Dependency Injection (20 minutes)
**Test a class that depends on external services:**

```cpp
// Interface for external dependency
class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(const string& message) = 0;
    virtual void error(const string& message) = 0;
};

// Real implementation (not used in tests)
class FileLogger : public Logger {
public:
    void log(const string& message) override {
        cout << "LOG: " << message << endl;
    }
    
    void error(const string& message) override {
        cout << "ERROR: " << message << endl;
    }
};

// Mock implementation for testing
class MockLogger : public Logger {
public:
    vector<string> log_messages;
    vector<string> error_messages;
    
    void log(const string& message) override {
        log_messages.push_back(message);
    }
    
    void error(const string& message) override {
        error_messages.push_back(message);
    }
    
    void clear() {
        log_messages.clear();
        error_messages.clear();
    }
};

// Class under test
class UserManager {
private:
    Logger* logger;
    vector<string> users;
    
public:
    UserManager(Logger* log) : logger{log} {}
    
    bool add_user(const string& username) {
        if (username.empty()) {
            logger->error("Cannot add user with empty name");
            return false;
        }
        
        // Check if user already exists
        for (const auto& user : users) {
            if (user == username) {
                logger->error("User " + username + " already exists");
                return false;
            }
        }
        
        users.push_back(username);
        logger->log("Added user: " + username);
        return true;
    }
    
    bool remove_user(const string& username) {
        auto it = find(users.begin(), users.end(), username);
        if (it == users.end()) {
            logger->error("User " + username + " not found");
            return false;
        }
        
        users.erase(it);
        logger->log("Removed user: " + username);
        return true;
    }
    
    size_t get_user_count() const { return users.size(); }
};

// TODO: Write tests using mock objects
TEST(user_manager_add_user_success, {
    MockLogger mock_logger;
    UserManager manager{&mock_logger};
    
    bool result = manager.add_user("alice");
    
    SimpleTest::assert_true(result);
    SimpleTest::assert_equal(size_t(1), manager.get_user_count());
    SimpleTest::assert_equal(size_t(1), mock_logger.log_messages.size());
    SimpleTest::assert_equal(string("Added user: alice"), mock_logger.log_messages[0]);
    SimpleTest::assert_equal(size_t(0), mock_logger.error_messages.size());
})

TEST(user_manager_add_empty_user, {
    MockLogger mock_logger;
    UserManager manager{&mock_logger};
    
    bool result = manager.add_user("");
    
    SimpleTest::assert_true(!result);
    SimpleTest::assert_equal(size_t(0), manager.get_user_count());
    SimpleTest::assert_equal(size_t(0), mock_logger.log_messages.size());
    SimpleTest::assert_equal(size_t(1), mock_logger.error_messages.size());
    SimpleTest::assert_equal(string("Cannot add user with empty name"), mock_logger.error_messages[0]);
})

TEST(user_manager_add_duplicate_user, {
    MockLogger mock_logger;
    UserManager manager{&mock_logger};
    
    manager.add_user("alice");
    mock_logger.clear();  // Clear previous messages
    
    bool result = manager.add_user("alice");  // Duplicate
    
    SimpleTest::assert_true(!result);
    SimpleTest::assert_equal(size_t(1), manager.get_user_count());  // Still only one user
    SimpleTest::assert_equal(size_t(0), mock_logger.log_messages.size());
    SimpleTest::assert_equal(size_t(1), mock_logger.error_messages.size());
    SimpleTest::assert_equal(string("User alice already exists"), mock_logger.error_messages[0]);
})
```

#### Problem 3.2: Performance and Stress Testing (20 minutes)
**Test performance characteristics and edge cases:**

```cpp
#include <chrono>
#include <random>

// Performance testing utilities
class PerformanceTimer {
private:
    chrono::high_resolution_clock::time_point start_time;
    
public:
    void start() {
        start_time = chrono::high_resolution_clock::now();
    }
    
    double elapsed_ms() {
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        return duration.count() / 1000.0;  // Convert to milliseconds
    }
};

// Data structure to test
class FastLookupContainer {
private:
    vector<int> data;
    
public:
    void add(int value) {
        data.push_back(value);
    }
    
    bool contains(int value) const {
        return find(data.begin(), data.end(), value) != data.end();
    }
    
    size_t size() const { return data.size(); }
    
    void clear() { data.clear(); }
};

// TODO: Write performance tests
TEST(container_performance_small, {
    FastLookupContainer container;
    PerformanceTimer timer;
    
    // Add 1000 elements
    timer.start();
    for (int i = 0; i < 1000; i++) {
        container.add(i);
    }
    double add_time = timer.elapsed_ms();
    
    // Search for elements
    timer.start();
    bool found = container.contains(999);  // Last element (worst case)
    double search_time = timer.elapsed_ms();
    
    SimpleTest::assert_true(found);
    SimpleTest::assert_equal(size_t(1000), container.size());
    
    cout << "Add 1000 elements: " << add_time << "ms" << endl;
    cout << "Search worst case: " << search_time << "ms" << endl;
    
    // Performance assertions (adjust based on your system)
    SimpleTest::assert_true(add_time < 10.0, "Adding should be fast");
    SimpleTest::assert_true(search_time < 1.0, "Search should be reasonable");
})

TEST(container_stress_test, {
    FastLookupContainer container;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);
    
    // Add many random elements
    const int num_elements = 10000;
    vector<int> added_elements;
    
    for (int i = 0; i < num_elements; i++) {
        int value = dis(gen);
        container.add(value);
        added_elements.push_back(value);
    }
    
    SimpleTest::assert_equal(size_t(num_elements), container.size());
    
    // Verify all added elements can be found
    int found_count = 0;
    for (int value : added_elements) {
        if (container.contains(value)) {
            found_count++;
        }
    }
    
    SimpleTest::assert_equal(num_elements, found_count);
    
    // Test memory cleanup
    container.clear();
    SimpleTest::assert_equal(size_t(0), container.size());
})

// Edge case testing
TEST(container_edge_cases, {
    FastLookupContainer container;
    
    // Empty container
    SimpleTest::assert_true(!container.contains(42));
    SimpleTest::assert_equal(size_t(0), container.size());
    
    // Single element
    container.add(42);
    SimpleTest::assert_true(container.contains(42));
    SimpleTest::assert_true(!container.contains(43));
    
    // Duplicate elements
    container.add(42);  // Add same element again
    SimpleTest::assert_equal(size_t(2), container.size());  // Should allow duplicates
    
    // Negative numbers
    container.add(-1);
    container.add(-100);
    SimpleTest::assert_true(container.contains(-1));
    SimpleTest::assert_true(container.contains(-100));
    
    // Large numbers
    container.add(1000000);
    SimpleTest::assert_true(container.contains(1000000));
})
```

---

## 🔧 Quick Reference & Troubleshooting

### Testing Best Practices

```cpp
// Good test structure (AAA pattern)
TEST(descriptive_test_name, {
    // Arrange - Set up test data
    Calculator calc;
    int a = 5, b = 3;
    
    // Act - Perform the operation
    int result = calc.add(a, b);
    
    // Assert - Verify the result
    SimpleTest::assert_equal(8, result);
})

// Test one thing at a time
TEST(calculator_add_positive_numbers, {
    Calculator calc;
    SimpleTest::assert_equal(8, calc.add(5, 3));
})

TEST(calculator_add_negative_numbers, {
    Calculator calc;
    SimpleTest::assert_equal(-8, calc.add(-5, -3));
})

// Test edge cases
TEST(calculator_divide_by_zero, {
    Calculator calc;
    SimpleTest::assert_throws([&]() {
        calc.divide(10, 0);
    });
})
```

### Common Testing Mistakes

#### 1. Testing Implementation Instead of Behavior
```cpp
// ❌ Bad - tests internal implementation
TEST(bad_test, {
    List list;
    list.add(1);
    SimpleTest::assert_equal(1, list.internal_array[0]);  // Don't test internals
})

// ✅ Good - tests public behavior
TEST(good_test, {
    List list;
    list.add(1);
    SimpleTest::assert_equal(1, list.get(0));  // Test public interface
})
```

#### 2. Tests That Are Too Complex
```cpp
// ❌ Bad - doing too much in one test
TEST(complex_test, {
    // ... 50 lines of setup and assertions
})

// ✅ Good - focused, simple tests
TEST(user_creation, {
    User user{"Alice"};
    SimpleTest::assert_equal("Alice", user.get_name());
})
```

#### 3. Tests With Dependencies
```cpp
// ❌ Bad - depends on other tests
TEST(test_depends_on_other, {
    // Assumes some_global_state was set by previous test
})

// ✅ Good - completely independent
TEST(independent_test, {
    // Sets up its own state
    Counter counter{0};
    counter.increment();
    SimpleTest::assert_equal(1, counter.get_value());
})
```

---

## ✅ Chapter 10 Success Checklist

### Testing Fundamentals
- [ ] Can set up and use a basic testing framework
- [ ] Can write unit tests with assertions
- [ ] Can test both normal cases and edge cases
- [ ] Can test error conditions with exception assertions

### Test-Driven Development
- [ ] Understand the Red-Green-Refactor cycle
- [ ] Can write failing tests first, then implement to pass
- [ ] Can refactor code while keeping tests passing
- [ ] Can use tests to drive design decisions

### Advanced Testing Techniques
- [ ] Can create and use mock objects for dependencies
- [ ] Can write performance and stress tests
- [ ] Can use test fixtures for setup and teardown
- [ ] Can identify and test edge cases effectively

---

## 🚀 What's Next?

**Chapter 11: Smart Pointers** will cover:
- unique_ptr for automatic memory management
- shared_ptr for shared ownership
- weak_ptr for breaking circular references
- RAII principles with smart pointers

**You've mastered testing in C++!** 🎉 Testing is crucial for C++ development because of the language's complexity and potential for undefined behavior. You now understand how to write reliable, maintainable tests that catch bugs early and drive good design.

**Key Takeaway**: Testing in C++ is not just about correctness - it's about safety. Memory management, exception safety, and resource management all require careful testing. TDD helps you design better interfaces and catch problems before they become bugs in production.

---

*Remember: Good tests are documentation of how your code should behave. They give you confidence to refactor, catch regressions, and serve as examples for other developers. In C++, where many errors can lead to undefined behavior, comprehensive testing is not optional - it's essential!*