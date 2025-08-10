# Chapter 8: Statements

Welcome to control flow and exception handling! This chapter covers how to make decisions and handle errors in C++. You'll learn to write robust programs that flow logically and handle exceptional situations gracefully.

## 📖 How This Chapter Works

**🔄 Learning Sequence (IMPORTANT!):**
1. **📚 FIRST**: Read Textbook Chapter 8 "Statements" (2-3 hours)
2. **🔍 SECOND**: Work through the lecture notes below for Python/Java context and hands-on practice (4-5 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 8 "Statements" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Master** C++ control flow statements with proper syntax
2. **Handle** exceptions using try/catch blocks effectively
3. **Apply** RAII principles to resource management in control structures
4. **Write** robust programs using appropriate error handling patterns
5. **Debug** control flow and exception handling using VS Code
6. **Compare** C++ control flow with Python/Java equivalents

**⏱️ Time Budget:**
- **📚 Textbook Reading: 2-3 hours** (Chapter 8: "Statements" - REQUIRED FIRST)
- **🛠️ Setup: Included in Chapter 1** (VS Code + debugger setup)
- **💻 Hands-on Work: 4-5 hours** (lecture notes + assignments)

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](../DEVELOPMENT_SETUP.md). All debugging examples use VS Code + Docker.

---

# Lecture Notes

## 🎛️ Core Concepts: Control Flow and Exception Handling

**📖 Bridge to Textbook**: Now that you've read about C++ statements in Chapter 8, let's connect those concepts to the Python/Java knowledge you already have and see practical examples.

### 1. Conditional Statements: Making Decisions

**From Textbook to Context**: The textbook covered C++ control flow statements. Here's how they compare to languages you know and work in practice:

```cpp
// Basic if/else - same as Python/Java
int score = 85;
if (score >= 90) {
    cout << "Grade: A" << endl;
} else if (score >= 80) {
    cout << "Grade: B" << endl;
} else if (score >= 70) {
    cout << "Grade: C" << endl;
} else {
    cout << "Grade: F" << endl;
}

// C++17 initialization in if statements
if (auto result = calculate_score(); result > 80) {
    cout << "Good score: " << result << endl;
}

// Switch statements with better syntax than Java
switch (grade) {
    case 'A':
    case 'a':
        cout << "Excellent!" << endl;
        break;
    case 'B':
    case 'b':
        cout << "Good job!" << endl;
        break;
    case 'C':
    case 'c':
        cout << "Satisfactory" << endl;
        break;
    default:
        cout << "Needs improvement" << endl;
        break;
}
```

| Feature | C++ | Python | Java |
|---------|-----|--------|------|
| **Basic if** | `if (condition) { }` | `if condition:` | `if (condition) { }` |
| **Multiple conditions** | `if/else if/else` | `if/elif/else` | `if/else if/else` |
| **Switch** | `switch(expr) { case: }` | No built-in switch | `switch(expr) { case: }` |
| **Initialization** | `if (int x = func(); x > 0)` | Assignment in if discouraged | No initialization syntax |

### 2. Loop Statements: Repetition Control

**📖 Bridge to Textbook**: The textbook explained C++ loop types. Here's how they compare to Python/Java loops and when to use each type:

**C++ offers several loop types, each with specific use cases:**

```cpp
// Traditional for loop - more explicit than Python
for (int i = 0; i < 10; i++) {
    cout << i << " ";
}

// Range-based for loop - like Python's for..in
vector<string> names = {"Alice", "Bob", "Charlie"};
for (const auto& name : names) {
    cout << "Hello, " << name << endl;
}

// While loop - same concept as Python/Java
int count = 0;
while (count < 5) {
    cout << "Count: " << count << endl;
    count++;
}

// Do-while loop - executes at least once
int input;
do {
    cout << "Enter a positive number: ";
    cin >> input;
} while (input <= 0);

// C++20 range-based for with initialization
for (auto data = load_data(); const auto& item : data) {
    process(item);
}
```

**Key Differences**:
- **C++**: More explicit loop control, multiple loop types
- **Python**: `for item in collection`, `while condition`
- **Java**: Similar to C++ but with different collection iteration

### 3. Exception Handling: Robust Error Management

**📖 Bridge to Textbook**: You've read about C++ exceptions in the textbook. Here's how they compare to error handling in Python and Java:

**C++ exceptions provide structured error handling:**

```cpp
#include <stdexcept>
#include <iostream>
using namespace std;

// Function that might throw exceptions
double safe_divide(double numerator, double denominator) {
    if (denominator == 0.0) {
        throw runtime_error("Division by zero!");
    }
    if (denominator < 0.0) {
        throw invalid_argument("Negative denominator not allowed");
    }
    return numerator / denominator;
}

// Exception handling with try/catch
void demonstrate_exceptions() {
    try {
        double result1 = safe_divide(10.0, 2.0);   // OK
        cout << "Result 1: " << result1 << endl;
        
        double result2 = safe_divide(10.0, 0.0);   // Throws exception
        cout << "This won't be printed" << endl;
    }
    catch (const runtime_error& e) {
        cout << "Runtime error: " << e.what() << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Invalid argument: " << e.what() << endl;
    }
    catch (const exception& e) {  // Catch-all for standard exceptions
        cout << "General exception: " << e.what() << endl;
    }
    catch (...) {  // Catch absolutely everything
        cout << "Unknown exception caught" << endl;
    }
}
```

| Aspect | C++ | Python | Java |
|--------|-----|--------|------|
| **Throwing** | `throw exception_object` | `raise Exception("msg")` | `throw new Exception("msg")` |
| **Catching** | `catch (const Type& e)` | `except Type as e:` | `catch (Type e)` |
| **Multiple catches** | Multiple `catch` blocks | Multiple `except` blocks | Multiple `catch` blocks |
| **Finally equivalent** | Destructors/RAII | `finally:` block | `finally` block |

### 4. RAII: Automatic Resource Management in Control Structures

**📖 Bridge to Textbook**: The textbook introduced RAII concepts. Here's how this C++-unique pattern compares to resource management in Python/Java:

**RAII (Resource Acquisition Is Initialization) ensures resources are cleaned up automatically, even when exceptions occur:**

```cpp
#include <fstream>
#include <memory>

// RAII with file handling - resources cleaned up automatically
void process_configuration_file(const string& filename) {
    // File opened in constructor, closed in destructor
    ifstream config_file{filename};
    
    if (!config_file) {
        throw runtime_error("Cannot open config file: " + filename);
    }
    
    string setting;
    while (getline(config_file, setting)) {
        // Process each configuration setting
        if (setting.empty() || setting[0] == '#') {
            continue;  // Skip empty lines and comments
        }
        
        if (setting.find("CRITICAL_ERROR") != string::npos) {
            // Even if we throw here, file is automatically closed!
            throw runtime_error("Critical error in configuration");
        }
        
        cout << "Config: " << setting << endl;
    }
    // File automatically closed here by destructor
}

// RAII with dynamic memory
void process_data_safely() {
    // Smart pointer automatically manages memory
    auto data = make_unique<int[]>(1000);  // Allocate array
    
    for (int i = 0; i < 1000; ++i) {
        data[i] = i * i;
        
        if (i == 500) {
            // Even if we throw here, memory is automatically freed!
            throw runtime_error("Processing error at element 500");
        }
    }
    // Memory automatically freed here by smart pointer destructor
}

// RAII principle: Constructor acquires, destructor releases
class DatabaseConnection {
private:
    bool connected = false;
    string connection_string;
    
public:
    DatabaseConnection(const string& conn_str) : connection_string{conn_str} {
        cout << "Connecting to database..." << endl;
        // Simulate connection
        connected = true;
    }
    
    ~DatabaseConnection() {
        if (connected) {
            cout << "Disconnecting from database..." << endl;
            // Cleanup happens automatically
        }
    }
    
    void execute_query(const string& query) {
        if (!connected) {
            throw runtime_error("Not connected to database");
        }
        cout << "Executing: " << query << endl;
        
        if (query.find("DROP") != string::npos) {
            // Even if we throw, destructor will still be called!
            throw runtime_error("Dangerous query detected");
        }
    }
};
```

**Key Insight**: RAII is C++'s automatic resource management. Unlike Python's `with` statement or Java's try-with-resources (which require explicit syntax), C++ RAII works through constructors and destructors - it's always active and doesn't require special syntax.

### 5. Advanced Control Flow Patterns

**C++ provides some unique control flow features:**

```cpp
// Structured bindings (C++17) in control flow
map<string, int> scores = {{"Alice", 95}, {"Bob", 87}};

for (const auto& [name, score] : scores) {
    if (score >= 90) {
        cout << name << " gets an A!" << endl;
    }
}

// Exception specifications and noexcept
double safe_calculation(double x) noexcept {
    // This function promises not to throw
    return x * x + 1.0;
}

// Conditional operator (ternary) - more powerful in C++
int abs_value = (x >= 0) ? x : -x;
string grade = (score >= 60) ? "Pass" : "Fail";

// Early return pattern with RAII
unique_ptr<Resource> get_resource() {
    auto resource = make_unique<Resource>();
    
    if (!resource->initialize()) {
        return nullptr;  // RAII cleanup happens automatically
    }
    
    if (!resource->validate()) {
        throw runtime_error("Invalid resource");  // RAII cleanup happens
    }
    
    return resource;  // Transfer ownership
}
```

## 🧩 Hands-On Practice Problems

### Problem Set 1: Control Flow Fundamentals (45 minutes)

#### Problem 1.1: Student Assessment System (15 minutes)
**Practice nested conditions with clearer logic:**

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Grade {
    char letter;
    string description;
};

Grade calculate_grade(double average) {
    if (average >= 90) {
        return {'A', "Excellent"};
    } else if (average >= 80) {
        return {'B', "Good"};
    } else if (average >= 70) {
        return {'C', "Satisfactory"};
    } else if (average >= 60) {
        return {'D', "Needs Improvement"};
    } else {
        return {'F', "Failing"};
    }
}

string get_study_recommendation(char grade) {
    switch (grade) {
        case 'A':
            return "Keep up the excellent work!";
        case 'B':
            return "Good job! Consider reviewing challenging topics.";
        case 'C':
            return "You're passing. Focus on weak areas for improvement.";
        case 'D':
            return "Warning: Consider additional study time and tutoring.";
        case 'F':
            return "Urgent: Meet with instructor and develop study plan.";
        default:
            return "Invalid grade - please check input.";
    }
}

int main() {
    vector<double> scores;
    double score;
    
    cout << "Enter test scores (negative number to stop):" << endl;
    
    // Input loop with validation
    while (true) {
        cout << "Score: ";
        cin >> score;
        
        if (score < 0) break;
        
        if (score > 100) {
            cout << "Score cannot be greater than 100. Try again." << endl;
            continue;
        }
        
        scores.push_back(score);
    }
    
    if (scores.empty()) {
        cout << "No scores entered." << endl;
        return 1;
    }
    
    // Calculate average
    double total = 0;
    for (double s : scores) {
        total += s;
    }
    double average = total / scores.size();
    
    Grade final_grade = calculate_grade(average);
    string recommendation = get_study_recommendation(final_grade.letter);
    
    cout << endl << "=== Final Assessment ===" << endl;
    cout << "Number of scores: " << scores.size() << endl;
    cout << "Average: " << fixed << setprecision(1) << average << "%" << endl;
    cout << "Letter grade: " << final_grade.letter << " (" << final_grade.description << ")" << endl;
    cout << "Recommendation: " << recommendation << endl;
    
    return 0;
}
```

#### Problem 1.2: Smart Calculator System (15 minutes)
**Enhanced calculator with better error handling:**

```cpp
#include <iostream>
using namespace std;

// Enhanced operations with better error handling
double safe_add(double a, double b) { 
    // Check for overflow (simplified)
    return a + b; 
}

double safe_subtract(double a, double b) { return a - b; }
double safe_multiply(double a, double b) { return a * b; }

double safe_divide(double a, double b) { 
    if (b == 0.0) {
        throw runtime_error("Division by zero is not allowed");
    }
    return a / b; 
}

double safe_power(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < abs(exponent); i++) {
        result *= base;
    }
    return (exponent < 0) ? 1.0 / result : result;
}

void display_menu() {
    cout << endl << "=== Smart Calculator ===" << endl;
    cout << "1. Addition" << endl;
    cout << "2. Subtraction" << endl;
    cout << "3. Multiplication" << endl;
    cout << "4. Division" << endl;
    cout << "5. Power (x^y)" << endl;
    cout << "6. Exit" << endl;
    cout << "Choice: ";
}

int main() {
    bool running = true;
    
    while (running) {
        display_menu();
        
        int choice;
        cin >> choice;
        
        // Handle invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        
        try {
            switch (choice) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5: {
                    double a, b;
                    cout << "Enter first number: ";
                    cin >> a;
                    
                    if (choice == 5) {
                        int exp;
                        cout << "Enter exponent (integer): ";
                        cin >> exp;
                        double result = safe_power(a, exp);
                        cout << "Result: " << a << "^" << exp << " = " << result << endl;
                    } else {
                        cout << "Enter second number: ";
                        cin >> b;
                        
                        double result;
                        switch (choice) {
                            case 1: result = safe_add(a, b); break;
                            case 2: result = safe_subtract(a, b); break;
                            case 3: result = safe_multiply(a, b); break;
                            case 4: result = safe_divide(a, b); break;
                        }
                        cout << "Result: " << result << endl;
                    }
                    break;
                }
                case 6:
                    cout << "Goodbye!" << endl;
                    running = false;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    return 0;
}
```

#### Problem 1.3: Number Guessing Game (15 minutes)
**Practice different loop types and random numbers:**

```cpp
#include <iostream>
#include <random>
using namespace std;

int main() {
    // Setup random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    
    bool play_again = true;
    
    while (play_again) {
        int secret_number = dis(gen);
        int guess;
        int attempts = 0;
        const int max_attempts = 7;
        
        cout << endl << "=== Number Guessing Game ===" << endl;
        cout << "I'm thinking of a number between 1 and 100." << endl;
        cout << "You have " << max_attempts << " attempts." << endl;
        
        // Guessing loop
        do {
            cout << endl << "Attempt " << (attempts + 1) << "/" << max_attempts;
            cout << endl << "Enter your guess: ";
            cin >> guess;
            attempts++;
            
            if (guess == secret_number) {
                cout << "Congratulations! You got it in " << attempts << " attempts!" << endl;
                break;
            } else if (guess < secret_number) {
                cout << "Too low!";
            } else {
                cout << "Too high!";
            }
            
            if (attempts < max_attempts) {
                cout << " Try again.";
            }
            
        } while (attempts < max_attempts && guess != secret_number);
        
        if (guess != secret_number) {
            cout << endl << "Sorry! The number was " << secret_number << "." << endl;
        }
        
        // Play again logic
        char response;
        cout << endl << "Play again? (y/n): ";
        cin >> response;
        play_again = (response == 'y' || response == 'Y');
    }
    
    cout << "Thanks for playing!" << endl;
    return 0;
}
```

### Problem Set 2: Exception Handling (60 minutes)

#### Problem 2.1: Safe Array Class (25 minutes)
**Practice exception throwing and handling:**

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

class SafeArray {
private:
    int* data;
    size_t size_;
    
public:
    SafeArray(size_t size) : size_{size} {
        if (size == 0) {
            throw invalid_argument("Array size cannot be zero");
        }
        
        data = new int[size_];
        
        // Initialize to zero
        for (size_t i = 0; i < size_; i++) {
            data[i] = 0;
        }
        
        cout << "SafeArray created with size " << size_ << endl;
    }
    
    ~SafeArray() {
        delete[] data;
        cout << "SafeArray destroyed" << endl;
    }
    
    // Safe element access with bounds checking
    int& at(size_t index) {
        if (index >= size_) {
            throw out_of_range("Index " + to_string(index) + 
                             " is out of range for size " + to_string(size_));
        }
        return data[index];
    }
    
    const int& at(size_t index) const {
        if (index >= size_) {
            throw out_of_range("Index " + to_string(index) + 
                             " is out of range for size " + to_string(size_));
        }
        return data[index];
    }
    
    size_t size() const { return size_; }
    
    void fill(int value) {
        for (size_t i = 0; i < size_; i++) {
            data[i] = value;
        }
    }
};

int main() {
    try {
        // Test normal usage
        SafeArray arr{5};
        arr.fill(42);
        
        cout << "Array contents: ";
        for (size_t i = 0; i < arr.size(); i++) {
            cout << arr.at(i) << " ";
        }
        cout << endl;
        
        // Test bounds checking
        cout << "Accessing valid index (2): " << arr.at(2) << endl;
        
        // This should throw an exception
        cout << "Accessing invalid index (10): " << arr.at(10) << endl;
        
    } catch (const out_of_range& e) {
        cout << "Bounds error: " << e.what() << endl;
    } catch (const invalid_argument& e) {
        cout << "Invalid argument: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "General exception: " << e.what() << endl;
    }
    
    // Test zero-size array
    try {
        SafeArray empty_arr{0};  // Should throw
    } catch (const invalid_argument& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }
    
    return 0;
}
```

#### Problem 2.2: File Processing with Exception Safety (20 minutes)
**Practice RAII and exception handling together:**

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class FileProcessor {
public:
    static void process_file(const string& filename) {
        ifstream file{filename};
        
        if (!file.is_open()) {
            throw runtime_error("Cannot open file: " + filename);
        }
        
        cout << "Processing file: " << filename << endl;
        
        string line;
        int line_number = 0;
        
        while (getline(file, line)) {
            line_number++;
            
            // Process each line with error checking
            if (line.empty()) {
                continue;  // Skip empty lines
            }
            
            if (line.find("ERROR") != string::npos) {
                throw runtime_error("Error found in line " + to_string(line_number) + 
                                  ": " + line);
            }
            
            if (line.find("WARNING") != string::npos) {
                cout << "Warning on line " << line_number << ": " << line << endl;
                continue;
            }
            
            cout << "Line " << line_number << ": " << line << endl;
        }
        
        cout << "File processed successfully. Total lines: " << line_number << endl;
        // File automatically closed by destructor
    }
    
    static void safe_file_operation(const string& input_file, const string& output_file) {
        ofstream out{output_file};
        
        if (!out.is_open()) {
            throw runtime_error("Cannot create output file: " + output_file);
        }
        
        try {
            process_file(input_file);
            out << "Processing completed successfully\n";
        } catch (const exception& e) {
            out << "Processing failed: " << e.what() << "\n";
            throw;  // Re-throw the exception
        }
        // Both files automatically closed
    }
};

int main() {
    // Create a test file
    {
        ofstream test_file{"test_input.txt"};
        test_file << "This is line 1\n";
        test_file << "This is line 2\n";
        test_file << "WARNING: This is a warning\n";
        test_file << "This is line 4\n";
        test_file << "ERROR: This line has an error\n";
        test_file << "This line won't be processed\n";
    }
    
    // Test exception handling
    try {
        FileProcessor::process_file("test_input.txt");
    } catch (const runtime_error& e) {
        cout << "Runtime error caught: " << e.what() << endl;
    }
    
    // Test with non-existent file
    try {
        FileProcessor::process_file("nonexistent.txt");
    } catch (const runtime_error& e) {
        cout << "Expected error: " << e.what() << endl;
    }
    
    // Test safe file operation
    try {
        FileProcessor::safe_file_operation("test_input.txt", "output.txt");
    } catch (const exception& e) {
        cout << "Safe operation caught: " << e.what() << endl;
    }
    
    return 0;
}
```

#### Problem 2.3: Custom Exception Hierarchy (15 minutes)
**Create and use custom exception types:**

```cpp
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Custom exception hierarchy
class MathError : public runtime_error {
public:
    MathError(const string& message) : runtime_error("Math Error: " + message) {}
};

class DivisionByZeroError : public MathError {
public:
    DivisionByZeroError() : MathError("Division by zero is not allowed") {}
};

class NegativeSquareRootError : public MathError {
public:
    NegativeSquareRootError(double value) 
        : MathError("Cannot take square root of negative number: " + to_string(value)) {}
};

class Calculator {
public:
    static double divide(double a, double b) {
        if (b == 0.0) {
            throw DivisionByZeroError();
        }
        return a / b;
    }
    
    static double square_root(double x) {
        if (x < 0.0) {
            throw NegativeSquareRootError(x);
        }
        // Simplified square root approximation
        double guess = x / 2.0;
        for (int i = 0; i < 10; i++) {
            guess = (guess + x / guess) / 2.0;
        }
        return guess;
    }
    
    static double safe_calculation(double a, double b, char operation) {
        switch (operation) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return divide(a, b);
            case 's': return square_root(a);  // Square root of a
            default:
                throw invalid_argument("Unknown operation: " + string(1, operation));
        }
    }
};

int main() {
    // Test different exception types
    double a = 10.0, b = 2.0;
    
    try {
        cout << "10 / 2 = " << Calculator::divide(a, b) << endl;
        cout << "10 / 0 = " << Calculator::divide(a, 0) << endl;  // Should throw
    } catch (const DivisionByZeroError& e) {
        cout << "Division error: " << e.what() << endl;
    }
    
    try {
        cout << "sqrt(16) = " << Calculator::square_root(16) << endl;
        cout << "sqrt(-4) = " << Calculator::square_root(-4) << endl;  // Should throw
    } catch (const NegativeSquareRootError& e) {
        cout << "Square root error: " << e.what() << endl;
    }
    
    // Test with catch hierarchy
    try {
        Calculator::safe_calculation(10, 0, '/');
    } catch (const MathError& e) {  // Catches all MathError types
        cout << "Math error caught: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "General error: " << e.what() << endl;
    }
    
    return 0;
}
```

---

# Assignments

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 8 "Statements"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Problem Set 1: Control Flow Fundamentals (45 minutes)

### Problem 1.1: Grade Calculator with Switch (15 minutes)

**Background**: Coming from Python dictionaries or Java if-else chains, learn C++ switch statements.

**Task**: Create a program that converts numeric grades to letter grades using a switch statement.

**Requirements**:
1. Read a numeric grade (0-100) from user input
2. Convert to letter grade using this scale:
   - 90-100: A
   - 80-89: B  
   - 70-79: C
   - 60-69: D
   - Below 60: F
3. Use a switch statement (not if-else)
4. Handle invalid input (negative numbers, > 100)

**Starter Code**:
```cpp
#include <iostream>

int main() {
    std::cout << "Enter numeric grade (0-100): ";
    int grade;
    std::cin >> grade;
    
    // TODO: Validate input
    // TODO: Convert to letter grade using switch
    // TODO: Print result
    
    return 0;
}
```

**Expected Output**:
```
Enter numeric grade (0-100): 87
Grade: B

Enter numeric grade (0-100): 105
Error: Grade must be between 0 and 100

Enter numeric grade (0-100): -5
Error: Grade must be between 0 and 100
```

### Problem 1.2: Number Pattern Generator (15 minutes)

**Background**: Practice nested loops and loop control (break/continue).

**Task**: Generate number patterns using nested for loops.

**Requirements**:
1. Ask user for pattern size (1-10)
2. Generate this pattern for size = 5:
```
1
12
123
1234
12345
```
3. Use nested for loops
4. Validate input range
5. Use continue to skip even-numbered rows if user chooses "odd only" mode

**Starter Code**:
```cpp
#include <iostream>

int main() {
    int size;
    char mode;
    
    std::cout << "Enter pattern size (1-10): ";
    std::cin >> size;
    
    std::cout << "Show all rows (a) or odd rows only (o)? ";
    std::cin >> mode;
    
    // TODO: Validate inputs
    // TODO: Generate pattern with nested loops
    // TODO: Use continue for odd-only mode
    
    return 0;
}
```

### Problem 1.3: Range-Based For Loop with Containers (15 minutes)  

**Background**: Transition from Python's for-in loops to C++ range-based for loops.

**Task**: Create a program that processes a list of temperatures.

**Requirements**:
1. Start with a vector of temperatures: `{68.5, 72.1, 69.8, 74.2, 71.5, 73.0, 70.2}`
2. Display all temperatures using range-based for loop
3. Find and display the average temperature
4. Count temperatures above average
5. Modify all temperatures by adding 2.0 degrees (using range-based for with references)

**Starter Code**:
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<double> temperatures = {68.5, 72.1, 69.8, 74.2, 71.5, 73.0, 70.2};
    
    // TODO: Display all temperatures
    // TODO: Calculate average
    // TODO: Count above average
    // TODO: Add 2.0 to all temperatures
    // TODO: Display modified temperatures
    
    return 0;
}
```

## Problem Set 2: Exception Handling & RAII (50 minutes)

### Problem 2.1: Safe Division Calculator (20 minutes)

**Background**: Learn proper exception handling patterns, transitioning from Python's try/except or Java's try/catch.

**Task**: Create a calculator that safely handles division by zero and invalid input.

**Requirements**:
1. Create a `safe_divide` function that throws appropriate exceptions
2. Handle different types of exceptions with specific catch blocks
3. Use standard exception types (`std::invalid_argument`, `std::runtime_error`)
4. Implement a menu-driven calculator with exception handling

**Starter Code**:
```cpp
#include <iostream>
#include <stdexcept>

double safe_divide(double numerator, double denominator) {
    // TODO: Implement with proper exception throwing
}

int main() {
    double a, b;
    char operation;
    
    while (true) {
        std::cout << "Enter calculation (a op b) or 'q' to quit: ";
        
        if (!(std::cin >> a >> operation >> b)) {
            if (std::cin.eof()) break;
            // TODO: Handle invalid input
        }
        
        try {
            // TODO: Implement calculator with exception handling
        } catch (/* TODO: Add appropriate catch blocks */) {
            // TODO: Handle specific exceptions
        }
    }
    
    return 0;
}
```

### Problem 2.2: File Processor with RAII (30 minutes)

**Background**: Learn RAII (Resource Acquisition Is Initialization) - a key C++ concept not present in Python/Java garbage collection.

**Task**: Create a file processing class that demonstrates RAII principles.

**Requirements**:
1. Create a `FileProcessor` class that opens a file in constructor
2. Implement RAII: file should auto-close in destructor
3. Add methods to count lines, words, and characters
4. Handle file-related exceptions properly
5. Demonstrate that files close even when exceptions occur

**Starter Code**:
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

class FileProcessor {
private:
    std::ifstream file;
    std::string filename;

public:
    // TODO: Constructor - acquire resource (open file)
    FileProcessor(const std::string& filename) {
        // TODO: Open file and handle errors
    }
    
    // TODO: Destructor - release resource (close file)
    ~FileProcessor() {
        // TODO: Ensure file is closed
    }
    
    // TODO: Delete copy constructor and assignment (RAII best practice)
    
    int count_lines() {
        // TODO: Count lines in file
        // TODO: Reset file position after counting
    }
    
    int count_words() {
        // TODO: Count words in file
    }
    
    int count_characters() {
        // TODO: Count characters in file
    }
};

// Test function that demonstrates RAII even with exceptions
void test_file_processing(const std::string& filename) {
    try {
        FileProcessor processor(filename);
        
        std::cout << "Lines: " << processor.count_lines() << std::endl;
        std::cout << "Words: " << processor.count_words() << std::endl;
        std::cout << "Characters: " << processor.count_characters() << std::endl;
        
        // Simulate an exception
        if (processor.count_lines() > 100) {
            throw std::runtime_error("File too large!");
        }
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        // File should still be properly closed due to RAII
    }
}

int main() {
    // TODO: Create a test file or use existing file
    // TODO: Test with valid and invalid filenames
    // TODO: Demonstrate RAII behavior
    
    return 0;
}
```

## Problem Set 3: Advanced Integration Project (40 minutes)

### Problem 3.1: Student Management System (40 minutes)

**Background**: Integrate all Chapter 8 concepts into a comprehensive program that demonstrates control flow, exception handling, and RAII.

**Task**: Create a student management system with robust error handling.

**Requirements**:

**Core Features**:
1. Store student records (ID, name, grades)
2. Menu-driven interface with switch statement
3. Add, remove, search, and display students
4. Calculate GPA with exception handling
5. Save/load data from file using RAII

**Control Flow Requirements**:
- Use switch statement for menu system
- Use range-based for loops for processing collections
- Use traditional for loops where appropriate
- Implement input validation loops

**Exception Handling Requirements**:
- Custom exception classes for domain-specific errors
- File operation exceptions
- Input validation exceptions
- Graceful error recovery

**RAII Requirements**:
- Automatic file handling
- Proper resource cleanup
- Exception-safe operations

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>

// Custom exception classes
class StudentNotFoundException : public std::runtime_error {
public:
    StudentNotFoundException(const std::string& message)
        : std::runtime_error(message) {}
};

class InvalidGradeException : public std::invalid_argument {
public:
    InvalidGradeException(const std::string& message)
        : std::invalid_argument(message) {}
};

// Student class
class Student {
private:
    int id;
    std::string name;
    std::vector<double> grades;

public:
    // TODO: Implement constructors
    Student(int id, const std::string& name) : id(id), name(name) {}
    
    // TODO: Implement getters
    int get_id() const { return id; }
    const std::string& get_name() const { return name; }
    
    // TODO: Implement grade management with validation
    void add_grade(double grade) {
        // TODO: Validate grade (0-100)
        // TODO: Throw InvalidGradeException if invalid
    }
    
    double calculate_gpa() const {
        // TODO: Calculate GPA
        // TODO: Handle empty grades vector
    }
    
    // TODO: Implement display method
    void display() const;
};

// RAII File Manager
class StudentFileManager {
private:
    std::string filename;

public:
    StudentFileManager(const std::string& filename) : filename(filename) {}
    
    // TODO: Implement save_students with RAII file handling
    void save_students(const std::vector<Student>& students) {
        // TODO: Use RAII for file operations
        // TODO: Handle file exceptions
    }
    
    // TODO: Implement load_students with RAII file handling
    std::vector<Student> load_students() {
        // TODO: Use RAII for file operations
        // TODO: Handle file exceptions
        // TODO: Return loaded students
    }
};

// Main application class
class StudentManagementSystem {
private:
    std::vector<Student> students;
    StudentFileManager file_manager;

public:
    StudentManagementSystem(const std::string& data_file)
        : file_manager(data_file) {
        try {
            students = file_manager.load_students();
        } catch (const std::exception& e) {
            std::cout << "Warning: Could not load existing data: " 
                      << e.what() << std::endl;
        }
    }
    
    ~StudentManagementSystem() {
        try {
            file_manager.save_students(students);
        } catch (const std::exception& e) {
            std::cout << "Warning: Could not save data: " 
                      << e.what() << std::endl;
        }
    }
    
    void run() {
        int choice;
        
        do {
            display_menu();
            std::cout << "Enter choice: ";
            
            if (!(std::cin >> choice)) {
                // TODO: Handle invalid input
                continue;
            }
            
            try {
                switch (choice) {
                    case 1:
                        add_student();
                        break;
                    case 2:
                        remove_student();
                        break;
                    case 3:
                        search_student();
                        break;
                    case 4:
                        display_all_students();
                        break;
                    case 5:
                        add_grade_to_student();
                        break;
                    case 0:
                        std::cout << "Goodbye!" << std::endl;
                        break;
                    default:
                        std::cout << "Invalid choice!" << std::endl;
                }
            } catch (const StudentNotFoundException& e) {
                std::cout << "Student Error: " << e.what() << std::endl;
            } catch (const InvalidGradeException& e) {
                std::cout << "Grade Error: " << e.what() << std::endl;
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            
        } while (choice != 0);
    }

private:
    void display_menu() {
        std::cout << "\n=== Student Management System ===" << std::endl;
        std::cout << "1. Add Student" << std::endl;
        std::cout << "2. Remove Student" << std::endl;
        std::cout << "3. Search Student" << std::endl;
        std::cout << "4. Display All Students" << std::endl;
        std::cout << "5. Add Grade to Student" << std::endl;
        std::cout << "0. Exit" << std::endl;
    }
    
    // TODO: Implement menu functions
    void add_student();
    void remove_student();
    void search_student();
    void display_all_students();
    void add_grade_to_student();
    
    // TODO: Helper function to find student by ID
    Student* find_student_by_id(int id);
};

int main() {
    try {
        StudentManagementSystem system("students.txt");
        system.run();
    } catch (const std::exception& e) {
        std::cout << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```

## Submission Guidelines

**File organization**:
```
chapter08_solutions/
├── problem_1_1.cpp
├── problem_1_2.cpp
├── problem_1_3.cpp
├── problem_2_1.cpp
├── problem_2_2.cpp
├── problem_3_1.cpp
└── README.md (with compilation notes and brief reflection)
```

---

# Quick Reference

## Control Flow Quick Reference

### If Statements
```cpp
// Basic if-else (similar to Java)
if (condition) {
    // statements
} else if (other_condition) {
    // statements  
} else {
    // statements
}

// C++17: if with initialization
if (auto result = function(); result > 0) {
    // use result here
}
// result goes out of scope
```

### Switch Statements
```cpp
switch (variable) {
    case value1:
        // statements
        break;  // DON'T FORGET!
    case value2:
    case value3:  // fall-through for multiple values
        // statements
        break;
    default:
        // statements
        break;
}
```

### Loops
```cpp
// Traditional for loop
for (int i = 0; i < 10; ++i) {
    // use i
}

// Range-based for (like Python's for-in)
for (const auto& item : container) {
    // read-only access
}

for (auto& item : container) {
    // can modify item
}

// While loop (same as Python/Java)
while (condition) {
    // statements
}

// Do-while (Java-style, not in Python)
do {
    // statements
} while (condition);
```

## Exception Handling Quick Reference

### Basic Try-Catch
```cpp
try {
    // risky code
} catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
} catch (...) {  // catch all
    std::cout << "Unknown error" << std::endl;
}
```

### Throwing Exceptions
```cpp
// Standard exceptions
throw std::invalid_argument("Bad input");
throw std::runtime_error("Something went wrong");
throw std::out_of_range("Index too large");

// Custom exceptions
class MyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "My custom error";
    }
};
```

## RAII Patterns

### File Handling (RAII)
```cpp
// Good: RAII automatically closes file
void process_file(const std::string& filename) {
    std::ifstream file(filename);  // opens in constructor
    
    if (!file) {
        throw std::runtime_error("Cannot open file");
    }
    
    // use file...
    
} // file automatically closes in destructor
```

### Custom RAII Class
```cpp
class ResourceManager {
private:
    Resource* resource;

public:
    // Constructor acquires resource
    ResourceManager() : resource(acquire_resource()) {}
    
    // Destructor releases resource
    ~ResourceManager() {
        if (resource) {
            release_resource(resource);
        }
    }
    
    // Delete copy constructor/assignment (Rule of 5)
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    // Optional: Enable move semantics
    ResourceManager(ResourceManager&& other) noexcept 
        : resource(other.resource) {
        other.resource = nullptr;
    }
    
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            if (resource) release_resource(resource);
            resource = other.resource;
            other.resource = nullptr;
        }
        return *this;
    }
};
```

## Common Mistakes & Fixes

### 1. Forgetting Break in Switch
```cpp
// ❌ Wrong - falls through
switch (grade) {
    case 'A':
        std::cout << "Excellent";
    case 'B':  // Falls through from A!
        std::cout << "Good";
        break;
}

// ✅ Correct
switch (grade) {
    case 'A':
        std::cout << "Excellent";
        break;  // Add break!
    case 'B':
        std::cout << "Good";
        break;
}
```

### 2. Wrong Range-For Type
```cpp
// ❌ Wrong - makes unnecessary copies
for (auto item : large_objects) {
    std::cout << item << std::endl;
}

// ✅ Correct - use const reference
for (const auto& item : large_objects) {
    std::cout << item << std::endl;
}
```

### 3. Not Using RAII
```cpp
// ❌ Wrong - manual resource management
void bad_function() {
    std::ofstream* file = new std::ofstream("data.txt");
    // ... use file ...
    delete file;  // What if exception occurs above?
}

// ✅ Correct - RAII
void good_function() {
    std::ofstream file("data.txt");  // RAII
    // ... use file ...
    // File automatically closed
}
```

### 4. Exception Not Caught by Reference
```cpp
try {
    // ...
} catch (std::exception e) {    // ❌ Object slicing!
    // ...
}

try {
    // ...
} catch (const std::exception& e) {  // ✅ Catch by reference
    // ...
}
```

## Success Checklist

After Chapter 8, you should be able to:
- [ ] Use if/else statements with proper syntax and logic
- [ ] Implement switch statements with proper break handling
- [ ] Write different types of loops (for, while, do-while, range-based)
- [ ] Throw and catch exceptions properly
- [ ] Create custom exception classes
- [ ] Use try/catch blocks with multiple exception types
- [ ] Understand and implement RAII principles
- [ ] Write exception-safe code using RAII
- [ ] Debug control flow using VS Code effectively

**Not there yet?** Focus on the fundamentals first - control flow and basic exception handling. RAII will come naturally once you understand constructors and destructors.

**Ready to move on?** Great! Chapter 9 will cover functions, function pointers, and lambda expressions.

---

## What's Next?

**Chapter 9: Functions** will cover:
- Function pointers and lambda expressions
- Function objects (functors) and std::function
- Higher-order functions and callbacks
- Advanced function techniques and patterns

**You've mastered control flow and exception handling!** These are fundamental building blocks that make your programs robust and reliable. You now understand how to write code that handles both normal execution paths and error conditions gracefully.

---

*Remember: Control flow determines the logic of your program, while exception handling determines its robustness. RAII ties them together by ensuring resources are managed correctly regardless of how execution flows through your code.*