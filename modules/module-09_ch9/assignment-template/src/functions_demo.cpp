// HW_09: Functions and Lambdas
// Time: 2.25 hours (45 minutes per problem set)
// Topics: Functions, lambdas, function pointers, std::function

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <numeric>

// ============================================================================
// PROBLEM SET 1: Function Fundamentals (45 minutes)
// ============================================================================

// TODO 1: Function declaration, definition, parameters, return types
int add(int a, int b) {
    return a + b;
}

double divide(double numerator, double denominator) {
    if (denominator == 0.0) {
        printf("Error: Division by zero!\n");
        return 0.0;
    }
    return numerator / denominator;
}

void print_info(const std::string& name, int age, bool is_student) {
    printf("Name: %s, Age: %d, Student: %s\n", 
           name.c_str(), age, is_student ? "Yes" : "No");
}

void function_basics() {
    printf("=== Function Basics ===\n");
    
    // TODO: Call functions with different parameters
    printf("Basic Function Calls:\n");
    printf("  add(5, 3) = %d\n", add(5, 3));
    printf("  divide(10.0, 3.0) = %.2f\n", divide(10.0, 3.0));
    printf("  divide(10.0, 0.0) = %.2f\n", divide(10.0, 0.0));
    
    printf("\nFunction with multiple parameter types:\n");
    print_info("Alice", 20, true);
    print_info("Bob", 35, false);
    
    printf("\n");
}

// TODO 2: Function overloading - same name, different signatures
void process(int value) {
    printf("  Processing integer: %d\n", value);
}

void process(double value) {
    printf("  Processing double: %.2f\n", value);
}

void process(const std::string& value) {
    printf("  Processing string: %s\n", value.c_str());
}

void process(int x, int y) {
    printf("  Processing two integers: %d, %d (sum: %d)\n", x, y, x + y);
}

void function_overloading() {
    printf("=== Function Overloading ===\n");
    
    printf("Same function name, different parameter types:\n");
    process(42);
    process(3.14159);
    process("Hello, World!");
    process(10, 20);
    
    printf("\n");
}

// TODO 3: Default parameters
void create_user(const std::string& name, 
                int age = 18, 
                const std::string& role = "Student", 
                bool is_active = true) {
    printf("  User: %s, Age: %d, Role: %s, Active: %s\n",
           name.c_str(), age, role.c_str(), is_active ? "Yes" : "No");
}

void calculate_interest(double principal, 
                       double rate = 0.05, 
                       int years = 1) {
    double interest = principal * rate * years;
    printf("  Principal: $%.2f, Rate: %.1f%%, Years: %d -> Interest: $%.2f\n",
           principal, rate * 100, years, interest);
}

void default_parameters() {
    printf("=== Default Parameters ===\n");
    
    printf("User creation with defaults:\n");
    create_user("Alice");                           // All defaults
    create_user("Bob", 25);                        // Age specified
    create_user("Carol", 30, "Instructor");        // Age and role
    create_user("Dave", 22, "TA", false);         // All specified
    
    printf("\nInterest calculation with defaults:\n");
    calculate_interest(1000.0);                    // Use defaults
    calculate_interest(1000.0, 0.07);             // Custom rate
    calculate_interest(1000.0, 0.07, 3);          // Custom rate and years
    
    printf("\n");
}

void problem_set_1_demo() {
    printf("=== Problem Set 1: Function Fundamentals ===\n\n");
    
    function_basics();
    function_overloading();
    default_parameters();
}

// ============================================================================
// PROBLEM SET 2: Lambda Expressions (45 minutes)
// ============================================================================

void basic_lambdas() {
    printf("=== Basic Lambda Expressions ===\n");
    
    // TODO 4: Simple lambda syntax
    printf("Simple Lambda Expressions:\n");
    
    // Basic lambda with no capture
    auto simple_add = [](int a, int b) {
        return a + b;
    };
    
    // Lambda with explicit return type
    auto divide_lambda = [](double a, double b) -> double {
        return (b != 0.0) ? a / b : 0.0;
    };
    
    // Lambda with no parameters
    auto greeting = []() {
        return "Hello from lambda!";
    };
    
    printf("  simple_add(5, 3) = %d\n", simple_add(5, 3));
    printf("  divide_lambda(10.0, 3.0) = %.2f\n", divide_lambda(10.0, 3.0));
    printf("  greeting() = %s\n", greeting());
    
    // TODO 5: Lambda with algorithm usage
    printf("\nLambda with STL Algorithms:\n");
    
    std::vector<int> numbers = {1, 5, 3, 9, 2, 8, 4};
    printf("  Original: ");
    for (int n : numbers) printf("%d ", n);
    printf("\n");
    
    // Sort using lambda
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a < b;  // Ascending order
    });
    printf("  Sorted:   ");
    for (int n : numbers) printf("%d ", n);
    printf("\n");
    
    // Count elements using lambda
    auto count_even = std::count_if(numbers.begin(), numbers.end(), 
                                   [](int n) { return n % 2 == 0; });
    printf("  Even numbers count: %ld\n", count_even);
    
    printf("\n");
}

void capture_modes() {
    printf("=== Lambda Capture Modes ===\n");
    
    int x = 10;
    int y = 20;
    std::string message = "Lambda captures";
    
    // TODO 6: Capture by value [=]
    printf("Capture by Value [=]:\n");
    auto capture_all_by_value = [=]() {
        printf("  Inside lambda: x=%d, y=%d, message='%s'\n", 
               x, y, message.c_str());
        // Note: cannot modify captured values
    };
    capture_all_by_value();
    
    // TODO 7: Capture by reference [&]
    printf("\nCapture by Reference [&]:\n");
    auto capture_all_by_ref = [&]() {
        x += 5;  // Can modify original variables
        y += 10;
        message += " modified";
        printf("  Inside lambda: x=%d, y=%d, message='%s'\n", 
               x, y, message.c_str());
    };
    capture_all_by_ref();
    printf("  After lambda: x=%d, y=%d, message='%s'\n", 
           x, y, message.c_str());
    
    // TODO 8: Explicit captures
    printf("\nExplicit Captures:\n");
    int a = 100, b = 200;
    
    // Capture 'a' by value, 'b' by reference
    auto mixed_capture = [a, &b](int multiplier) {
        b *= multiplier;  // Modify original b
        printf("  a (by value): %d, b (by ref, modified): %d\n", a, b);
        return a + b;
    };
    
    int result = mixed_capture(3);
    printf("  Result: %d, original b is now: %d\n", result, b);
    
    printf("\n");
}

void lambda_applications() {
    printf("=== Lambda Applications ===\n");
    
    // TODO 9: Lambda as callback
    printf("Lambda as Callback:\n");
    
    auto process_data = [](const std::vector<int>& data, 
                          std::function<void(int)> callback) {
        for (int item : data) {
            callback(item);
        }
    };
    
    std::vector<int> data = {1, 4, 7, 2, 9};
    printf("  Processing data: ");
    process_data(data, [](int value) { 
        printf("%d ", value * value); 
    });
    printf("(squared values)\n");
    
    // TODO 10: Lambda for filtering and transformation
    printf("\nLambda for Data Processing:\n");
    
    std::vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
    // Filter words longer than 5 characters
    std::vector<std::string> long_words;
    std::copy_if(words.begin(), words.end(), 
                std::back_inserter(long_words),
                [](const std::string& word) { return word.length() > 5; });
    
    printf("  Long words (>5 chars): ");
    for (const auto& word : long_words) {
        printf("%s ", word.c_str());
    }
    printf("\n");
    
    // Transform to uppercase (first letter)
    std::transform(words.begin(), words.end(), words.begin(),
                  [](std::string word) {
                      if (!word.empty()) {
                          word[0] = std::toupper(word[0]);
                      }
                      return word;
                  });
    
    printf("  Capitalized: ");
    for (const auto& word : words) {
        printf("%s ", word.c_str());
    }
    printf("\n");
    
    printf("\n");
}

void problem_set_2_demo() {
    printf("=== Problem Set 2: Lambda Expressions ===\n\n");
    
    basic_lambdas();
    capture_modes();
    lambda_applications();
}

// ============================================================================
// PROBLEM SET 3: Advanced Function Concepts (45 minutes)
// ============================================================================

// TODO 11: Function pointers
int multiply(int a, int b) {
    return a * b;
}

int subtract(int a, int b) {
    return a - b;
}

void function_pointers() {
    printf("=== Function Pointers ===\n");
    
    // TODO: Traditional C-style function pointers
    printf("Traditional Function Pointers:\n");
    
    // Declare function pointer
    int (*operation)(int, int);
    
    // Point to add function
    operation = add;
    printf("  add(10, 5) via pointer = %d\n", operation(10, 5));
    
    // Point to multiply function
    operation = multiply;
    printf("  multiply(10, 5) via pointer = %d\n", operation(10, 5));
    
    // Point to subtract function
    operation = subtract;
    printf("  subtract(10, 5) via pointer = %d\n", operation(10, 5));
    
    // TODO: Array of function pointers
    printf("\nArray of Function Pointers:\n");
    
    int (*operations[])(int, int) = {add, multiply, subtract};
    const char* op_names[] = {"add", "multiply", "subtract"};
    
    int x = 12, y = 4;
    for (int i = 0; i < 3; i++) {
        printf("  %s(%d, %d) = %d\n", 
               op_names[i], x, y, operations[i](x, y));
    }
    
    printf("\n");
}

void std_function_usage() {
    printf("=== std::function - Modern C++ Callable Wrapper ===\n");
    
    // TODO 12: std::function can hold various callables
    printf("std::function with Different Callables:\n");
    
    // Function pointer
    std::function<int(int, int)> func = add;
    printf("  Function pointer: add(7, 3) = %d\n", func(7, 3));
    
    // Lambda
    func = [](int a, int b) { return a * b * 2; };
    printf("  Lambda: (a * b * 2) with (7, 3) = %d\n", func(7, 3));
    
    // Function object (functor)
    struct Divider {
        int operator()(int a, int b) const {
            return (b != 0) ? a / b : 0;
        }
    };
    
    func = Divider{};
    printf("  Function object: divide(21, 3) = %d\n", func(21, 3));
    
    // TODO 13: std::function as parameter
    printf("\nstd::function as Parameter:\n");
    
    auto apply_operation = [](int x, int y, std::function<int(int, int)> op) {
        return op(x, y);
    };
    
    printf("  apply_operation(8, 2, add) = %d\n", 
           apply_operation(8, 2, add));
    printf("  apply_operation(8, 2, multiply) = %d\n", 
           apply_operation(8, 2, multiply));
    printf("  apply_operation(8, 2, lambda) = %d\n", 
           apply_operation(8, 2, [](int a, int b) { return a - b; }));
    
    printf("\n");
}

// TODO 14: Constexpr functions - compile-time evaluation
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr double circle_area(double radius) {
    return 3.14159 * radius * radius;
}

constexpr bool is_power_of_two(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

void constexpr_functions() {
    printf("=== Constexpr Functions - Compile-Time Evaluation ===\n");
    
    // TODO: These can be evaluated at compile time
    printf("Compile-Time Function Evaluation:\n");
    
    // These values are computed at compile time
    constexpr int fact5 = factorial(5);
    constexpr double area = circle_area(3.0);
    constexpr bool is_pow2_8 = is_power_of_two(8);
    constexpr bool is_pow2_10 = is_power_of_two(10);
    
    printf("  factorial(5) = %d\n", fact5);
    printf("  circle_area(3.0) = %.2f\n", area);
    printf("  is_power_of_two(8) = %s\n", is_pow2_8 ? "true" : "false");
    printf("  is_power_of_two(10) = %s\n", is_pow2_10 ? "true" : "false");
    
    // TODO: Can also be used at runtime
    printf("\nRuntime Usage of Constexpr Functions:\n");
    
    int runtime_n = 6;  // Not known at compile time
    printf("  factorial(%d) = %d\n", runtime_n, factorial(runtime_n));
    
    double runtime_r = 2.5;
    printf("  circle_area(%.1f) = %.2f\n", runtime_r, circle_area(runtime_r));
    
    printf("\n");
}

// TODO 15: Auto return type deduction
auto get_maximum(int a, int b) {
    return (a > b) ? a : b;
}

auto create_multiplier(int factor) {
    return [factor](int value) {
        return value * factor;
    };
}

template<typename T>
auto compute_average(const std::vector<T>& values) {
    if (values.empty()) return T{};
    
    auto sum = std::accumulate(values.begin(), values.end(), T{});
    return sum / static_cast<T>(values.size());
}

void modern_function_features() {
    printf("=== Modern C++ Function Features ===\n");
    
    // TODO: Auto return type deduction
    printf("Auto Return Type Deduction:\n");
    
    printf("  get_maximum(15, 23) = %d\n", get_maximum(15, 23));
    
    auto triple = create_multiplier(3);
    printf("  create_multiplier(3)(7) = %d\n", triple(7));
    
    std::vector<double> grades = {85.5, 92.0, 78.5, 94.0, 87.5};
    printf("  average of grades = %.2f\n", compute_average(grades));
    
    std::vector<int> scores = {100, 95, 87, 92, 88};
    printf("  average of scores = %.1f\n", compute_average(scores));
    
    printf("\n");
}

void problem_set_3_demo() {
    printf("=== Problem Set 3: Advanced Function Concepts ===\n\n");
    
    function_pointers();
    std_function_usage();
    constexpr_functions();
    modern_function_features();
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("      HW_09: Functions and Lambdas\n");
    printf("==========================================\n\n");
    
    // Problem Set 1: Function Fundamentals (45 min)
    problem_set_1_demo();
    
    // Problem Set 2: Lambda Expressions (45 min)
    problem_set_2_demo();
    
    // Problem Set 3: Advanced Function Concepts (45 min)
    problem_set_3_demo();
    
    printf("==========================================\n");
    printf("           Program Complete!\n");
    printf("==========================================\n");
    
    return 0;
}