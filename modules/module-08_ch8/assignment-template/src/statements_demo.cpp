// HW_08: Statements and Control Flow
// Time: 2.25 hours (45 minutes per problem set)
// Topics: if/else, switch, loops, scope, control flow

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <random>

// ============================================================================
// PROBLEM SET 1: Conditional Statements (45 minutes)
// ============================================================================

void if_else_chains() {
    printf("=== If/Else Statement Chains ===\n");
    
    // TODO 1: Grade classification system
    printf("Grade Classification:\n");
    
    int scores[] = {95, 87, 76, 63, 45};
    int num_scores = sizeof(scores) / sizeof(scores[0]);
    
    for (int i = 0; i < num_scores; i++) {
        int score = scores[i];
        char grade;
        std::string description;
        
        // TODO: Implement complete if/else chain
        if (score >= 90) {
            grade = 'A';
            description = "Excellent";
        } else if (score >= 80) {
            grade = 'B';
            description = "Good";
        } else if (score >= 70) {
            grade = 'C';
            description = "Satisfactory";
        } else if (score >= 60) {
            grade = 'D';
            description = "Needs Improvement";
        } else {
            grade = 'F';
            description = "Failing";
        }
        
        printf("  Score %d: Grade %c (%s)\n", score, grade, description.c_str());
    }
    
    // TODO 2: Complex conditional logic
    printf("\nComplex Conditional Logic:\n");
    
    int age = 25;
    bool has_license = true;
    bool has_car = false;
    int years_experience = 3;
    
    // TODO: Combine multiple conditions
    if (age >= 18 && has_license) {
        if (has_car) {
            printf("  Can drive own car\n");
        } else {
            printf("  Can drive but needs to borrow/rent car\n");
        }
        
        if (years_experience >= 5) {
            printf("  Eligible for lower insurance rates\n");
        } else {
            printf("  Higher insurance rates due to limited experience\n");
        }
    } else {
        printf("  Cannot legally drive\n");
    }
    
    printf("\n");
}

void switch_statements() {
    printf("=== Switch Statements ===\n");
    
    // TODO 3: Day of week calculator
    printf("Day of Week Calculator:\n");
    
    int days[] = {1, 3, 5, 7, 0, 8};  // Include invalid day
    int num_days = sizeof(days) / sizeof(days[0]);
    
    for (int i = 0; i < num_days; i++) {
        int day = days[i];
        printf("  Day %d: ", day);
        
        // TODO: Implement switch statement
        switch (day) {
            case 1:
                printf("Monday\n");
                break;
            case 2:
                printf("Tuesday\n");
                break;
            case 3:
                printf("Wednesday\n");
                break;
            case 4:
                printf("Thursday\n");
                break;
            case 5:
                printf("Friday\n");
                break;
            case 6:
                printf("Saturday\n");
                break;
            case 7:
                printf("Sunday\n");
                break;
            default:
                printf("Invalid day\n");
                break;
        }
    }
    
    // TODO 4: Switch with fallthrough
    printf("\nSeason Classification (with fallthrough):\n");
    
    int months[] = {12, 3, 6, 9, 13};
    int num_months = sizeof(months) / sizeof(months[0]);
    
    for (int i = 0; i < num_months; i++) {
        int month = months[i];
        printf("  Month %d: ", month);
        
        switch (month) {
            case 12:
            case 1:
            case 2:
                printf("Winter\n");
                break;
            case 3:
            case 4:
            case 5:
                printf("Spring\n");
                break;
            case 6:
            case 7:
            case 8:
                printf("Summer\n");
                break;
            case 9:
            case 10:
            case 11:
                printf("Fall\n");
                break;
            default:
                printf("Invalid month\n");
                break;
        }
    }
    
    printf("\n");
}

void conditional_operators() {
    printf("=== Conditional Operators and Logic ===\n");
    
    // TODO 5: Ternary operator usage
    printf("Ternary Operator Examples:\n");
    
    int numbers[] = {-5, 0, 7, -12, 15};
    int num_numbers = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < num_numbers; i++) {
        int num = numbers[i];
        
        // Simple ternary
        const char* sign = (num >= 0) ? "positive or zero" : "negative";
        
        // Nested ternary
        const char* category = (num > 0) ? "positive" : 
                              (num < 0) ? "negative" : "zero";
        
        // Ternary for computation
        int abs_value = (num >= 0) ? num : -num;
        
        printf("  %d is %s (%s), absolute value: %d\n", 
               num, sign, category, abs_value);
    }
    
    // TODO 6: Short-circuit evaluation
    printf("\nShort-Circuit Evaluation:\n");
    
    int x = 5, y = 0;
    
    // Logical AND short-circuit
    if (y != 0 && x / y > 2) {
        printf("  Division result > 2\n");
    } else {
        printf("  Division avoided or result <= 2\n");
    }
    
    // Logical OR short-circuit
    if (x > 10 || y == 0) {
        printf("  Either x > 10 OR y == 0 (or both)\n");
    }
    
    printf("\n");
}

void problem_set_1_demo() {
    printf("=== Problem Set 1: Conditional Statements ===\n\n");
    
    if_else_chains();
    switch_statements();
    conditional_operators();
}

// ============================================================================
// PROBLEM SET 2: Loop Constructs (45 minutes)
// ============================================================================

void for_loops() {
    printf("=== For Loop Variations ===\n");
    
    // TODO 7: Traditional for loop
    printf("Traditional For Loop:\n");
    printf("  Counting: ");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    // Different step sizes
    printf("  Even numbers: ");
    for (int i = 2; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
    
    // Countdown
    printf("  Countdown: ");
    for (int i = 5; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\n");
    
    // TODO 8: Range-based for loop (C++11)
    printf("\nRange-Based For Loop:\n");
    
    std::vector<std::string> fruits = {"apple", "banana", "orange", "grape"};
    
    printf("  Fruits: ");
    for (const auto& fruit : fruits) {
        std::cout << fruit << " ";
    }
    printf("\n");
    
    // With index using enumerate pattern
    printf("  Indexed fruits:\n");
    for (size_t i = 0; i < fruits.size(); i++) {
        printf("    %zu: %s\n", i + 1, fruits[i].c_str());
    }
    
    // TODO 9: Nested for loops
    printf("\nNested For Loops (Multiplication Table):\n");
    printf("   ");
    for (int i = 1; i <= 5; i++) {
        printf("%4d", i);
    }
    printf("\n");
    
    for (int i = 1; i <= 5; i++) {
        printf("%2d:", i);
        for (int j = 1; j <= 5; j++) {
            printf("%4d", i * j);
        }
        printf("\n");
    }
    
    printf("\n");
}

void while_loops() {
    printf("=== While and Do-While Loops ===\n");
    
    // TODO 10: While loop
    printf("While Loop (counting):\n");
    printf("  ");
    int count = 1;
    while (count <= 5) {
        printf("%d ", count);
        count++;
    }
    printf("\n");
    
    // TODO 11: While loop with complex condition
    printf("While Loop (finding first power of 2 > 100):\n");
    int power_of_2 = 1;
    int exponent = 0;
    
    while (power_of_2 <= 100) {
        printf("  2^%d = %d\n", exponent, power_of_2);
        power_of_2 *= 2;
        exponent++;
    }
    printf("  First power > 100: 2^%d = %d\n", exponent, power_of_2);
    
    // TODO 12: Do-while loop
    printf("\nDo-While Loop (input validation simulation):\n");
    int simulated_input[] = {-5, 0, 15, 25, 3};  // Simulate user input
    int input_index = 0;
    int value;
    
    do {
        value = simulated_input[input_index++];
        printf("  Input: %d", value);
        if (value < 1 || value > 10) {
            printf(" (invalid, try again)\n");
        } else {
            printf(" (valid!)\n");
        }
    } while ((value < 1 || value > 10) && input_index < 5);
    
    printf("\n");
}

void loop_control() {
    printf("=== Loop Control: Break and Continue ===\n");
    
    // TODO 13: Break statement
    printf("Break Statement (find first even number > 10):\n");
    printf("  Checking: ");
    for (int i = 11; i <= 20; i++) {
        printf("%d ", i);
        if (i % 2 == 0) {
            printf("\n  Found first even: %d\n", i);
            break;
        }
    }
    
    // TODO 14: Continue statement
    printf("\nContinue Statement (skip negative numbers):\n");
    int numbers[] = {1, -2, 3, -4, 5, -6, 7};
    int num_numbers = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("  Positive numbers only: ");
    for (int i = 0; i < num_numbers; i++) {
        if (numbers[i] < 0) {
            continue;  // Skip negative numbers
        }
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // TODO 15: Nested loop control
    printf("\nNested Loop Control (find first pair that sums to 10):\n");
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    bool found = false;
    
    for (int i = 0; i < 5 && !found; i++) {
        for (int j = 0; j < 5; j++) {
            if (arr1[i] + arr2[j] == 10) {
                printf("  Found: %d + %d = 10\n", arr1[i], arr2[j]);
                found = true;
                break;  // Break inner loop
            }
        }
    }
    
    printf("\n");
}

void problem_set_2_demo() {
    printf("=== Problem Set 2: Loop Constructs ===\n\n");
    
    for_loops();
    while_loops();
    loop_control();
}

// ============================================================================
// PROBLEM SET 3: Advanced Flow Control (45 minutes)
// ============================================================================

void scope_management() {
    printf("=== Scope Management and Variable Lifetime ===\n");
    
    // TODO 16: Block scope demonstration
    printf("Block Scope Demonstration:\n");
    
    int outer_var = 100;
    printf("  Outer scope: outer_var = %d\n", outer_var);
    
    {  // Inner scope
        printf("  Entering inner scope...\n");
        int inner_var = 200;
        printf("    Inner scope: inner_var = %d\n", inner_var);
        printf("    Inner scope: outer_var = %d (still accessible)\n", outer_var);
        
        {  // Nested inner scope
            printf("    Entering nested scope...\n");
            int nested_var = 300;
            outer_var = 150;  // Modify outer variable
            printf("      Nested scope: nested_var = %d\n", nested_var);
            printf("      Nested scope: modified outer_var = %d\n", outer_var);
            printf("    Exiting nested scope...\n");
            // nested_var destroyed here
        }
        
        printf("    Back in inner scope: outer_var = %d\n", outer_var);
        // printf("    inner_var = %d\n", nested_var);  // ERROR: nested_var not accessible
        printf("  Exiting inner scope...\n");
        // inner_var destroyed here
    }
    
    printf("  Back in outer scope: outer_var = %d\n", outer_var);
    
    // TODO 17: Variable shadowing
    printf("\nVariable Shadowing:\n");
    
    int value = 10;
    printf("  Outer value: %d\n", value);
    
    {
        int value = 20;  // Shadows outer value
        printf("  Inner value (shadows outer): %d\n", value);
        
        {
            int value = 30;  // Shadows both
            printf("  Nested value (shadows both): %d\n", value);
        }
        
        printf("  Back to inner value: %d\n", value);
    }
    
    printf("  Back to outer value: %d\n", value);
    
    printf("\n");
}

void exception_handling_preview() {
    printf("=== Exception Handling Preview ===\n");
    
    // TODO 18: Basic try/catch
    printf("Basic Try/Catch:\n");
    
    try {
        int numerator = 10;
        int denominators[] = {2, 0, 5};
        
        for (int i = 0; i < 3; i++) {
            int denom = denominators[i];
            printf("  Dividing %d by %d: ", numerator, denom);
            
            if (denom == 0) {
                throw std::runtime_error("Division by zero!");
            }
            
            double result = static_cast<double>(numerator) / denom;
            printf("%.2f\n", result);
        }
    } catch (const std::runtime_error& e) {
        printf("ERROR - %s\n", e.what());
    }
    
    // TODO 19: Multiple exception types
    printf("\nMultiple Exception Types:\n");
    
    try {
        std::vector<int> vec = {1, 2, 3};
        
        // This will throw std::out_of_range
        printf("  Accessing vec[5]: ");
        int value = vec.at(5);  // Safe access with bounds checking
        printf("%d\n", value);
    } catch (const std::out_of_range& e) {
        printf("Out of range error: %s\n", e.what());
    } catch (const std::exception& e) {
        printf("General exception: %s\n", e.what());
    }
    
    printf("\n");
}

void modern_constructs() {
    printf("=== Modern C++ Constructs ===\n");
    
    // TODO 20: If with initializer (C++17)
    printf("If with Initializer (C++17):\n");
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Traditional approach
    auto it = numbers.begin() + 2;
    if (it != numbers.end()) {
        printf("  Traditional: Found element %d\n", *it);
    }
    
    // C++17 if with initializer
    if (auto it = numbers.begin() + 2; it != numbers.end()) {
        printf("  C++17 style: Found element %d\n", *it);
        // it is only in scope within this if statement
    }
    
    // TODO 21: Switch with initializer (C++17)
    printf("\nSwitch with Initializer:\n");
    
    std::vector<std::string> words = {"hello", "world", "C++", "programming"};
    
    for (const auto& word : words) {
        switch (auto len = word.length(); len) {
            case 1:
            case 2:
                printf("  '%s' is short (%zu chars)\n", word.c_str(), len);
                break;
            case 3:
            case 4:
            case 5:
                printf("  '%s' is medium (%zu chars)\n", word.c_str(), len);
                break;
            default:
                printf("  '%s' is long (%zu chars)\n", word.c_str(), len);
                break;
        }
    }
    
    printf("\n");
}

void problem_set_3_demo() {
    printf("=== Problem Set 3: Advanced Flow Control ===\n\n");
    
    scope_management();
    exception_handling_preview();
    modern_constructs();
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("     HW_08: Statements and Control Flow\n");
    printf("==========================================\n\n");
    
    // Problem Set 1: Conditional Statements (45 min)
    problem_set_1_demo();
    
    // Problem Set 2: Loop Constructs (45 min)
    problem_set_2_demo();
    
    // Problem Set 3: Advanced Flow Control (45 min)
    problem_set_3_demo();
    
    printf("==========================================\n");
    printf("           Program Complete!\n");
    printf("==========================================\n");
    
    return 0;
}