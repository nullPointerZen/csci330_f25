# Chapter 8: Statements - Complete Guide

## 📖 Learning Sequence (IMPORTANT!)

**🔄 How This Chapter Works:**
1. **📚 FIRST**: Read Textbook Chapter 8 "Statements" (2-3 hours)
2. **🔍 SECOND**: Work through these lecture notes for Python/Java context and hands-on practice (4-5 hours)
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
- **💻 Hands-on Work: 4-5 hours** (course materials + assignments + debugging)
- **📖 Note: Reading time is separate and must be completed BEFORE hands-on work**

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](./DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 🎛️ Core Concepts: Control Flow and Exception Handling (2.5 hours)

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

---

## 🔍 VS Code Debugging Control Flow (20 minutes)

### Debugging Control Flow

**Essential debugging techniques for control structures:**

1. **Breakpoints in Conditions**: Set breakpoints on if/while conditions to see evaluation
2. **Step Over vs Step Into**: Use F10 for statements, F11 for function calls
3. **Watch Variables**: Monitor loop counters and condition variables
4. **Exception Breakpoints**: Catch exceptions when they're thrown

**Debug Configuration for Control Flow:**
```json
{
    "name": "Debug Control Flow",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/${fileBasenameNoExtension}",
    "stopAtEntry": false,
    "setupCommands": [
        {
            "description": "Break on exceptions",
            "text": "-gdb-set breakpoint pending on"
        },
        {
            "description": "Catch all exceptions",
            "text": "catch throw"
        }
    ]
}
```

### Debugging Strategies

| What to Debug | How to Debug It |
|---------------|-----------------|
| **Loop behavior** | Breakpoint in loop body, watch counter variables |
| **Condition evaluation** | Breakpoint on if/while, examine condition variables |
| **Exception flow** | Exception breakpoints, step through catch blocks |
| **RAII cleanup** | Breakpoints in destructors, watch resource states |

---

## 🧩 Hands-On Problems (2.25 hours)

**📖 Ready to Apply**: You've read the textbook and reviewed the Python/Java connections above. Now let's put that knowledge to work with hands-on practice that prepares you for the assignments.

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
    // TODO: Implement clearer grade calculation
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
    // TODO: Use switch statement for recommendations
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
    
    cout << "Enter test scores (negative number to stop):\n";
    
    // TODO: Input loop with validation
    while (true) {
        cout << "Score: ";
        cin >> score;
        
        if (score < 0) break;
        
        if (score > 100) {
            cout << "Score cannot be greater than 100. Try again.\n";
            continue;
        }
        
        scores.push_back(score);
    }
    
    if (scores.empty()) {
        cout << "No scores entered.\n";
        return 1;
    }
    
    // TODO: Calculate average
    double total = 0;
    for (double s : scores) {
        total += s;
    }
    double average = total / scores.size();
    
    Grade final_grade = calculate_grade(average);
    string recommendation = get_study_recommendation(final_grade.letter);
    
    cout << "\n=== Final Assessment ===\n";
    cout << "Number of scores: " << scores.size() << endl;
    cout << "Average: " << fixed << setprecision(1) << average << "%" << endl;
    cout << "Letter grade: " << final_grade.letter << " (" << final_grade.description << ")\n";
    cout << "Recommendation: " << recommendation << endl;
    
    return 0;
}
```

#### Problem 1.2: Smart Calculator System (15 minutes)
**Eliminate redundancy with the calculator from other chapters:**

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
    cout << "\n=== Smart Calculator ===\n";
    cout << "1. Addition\n";
    cout << "2. Subtraction\n";
    cout << "3. Multiplication\n";
    cout << "4. Division\n";
    cout << "5. Power (x^y)\n";
    cout << "6. Exit\n";
    cout << "Choice: ";
}

int main() {
    bool running = true;
    
    while (running) {
        display_menu();
        
        int choice;
        cin >> choice;
        
        // TODO: Handle invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
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
                    cout << "Goodbye!\n";
                    running = false;
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
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
    // TODO: Setup random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    
    bool play_again = true;
    
    while (play_again) {
        int secret_number = dis(gen);
        int guess;
        int attempts = 0;
        const int max_attempts = 7;
        
        cout << "\n=== Number Guessing Game ===\n";
        cout << "I'm thinking of a number between 1 and 100.\n";
        cout << "You have " << max_attempts << " attempts.\n";
        
        // TODO: Guessing loop
        do {
            cout << "\nAttempt " << (attempts + 1) << "/" << max_attempts;
            cout << "\nEnter your guess: ";
            cin >> guess;
            attempts++;
            
            if (guess == secret_number) {
                cout << "Congratulations! You got it in " << attempts << " attempts!\n";
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
            cout << "\nSorry! The number was " << secret_number << ".\n";
        }
        
        // TODO: Play again logic
        char response;
        cout << "\nPlay again? (y/n): ";
        cin >> response;
        play_again = (response == 'y' || response == 'Y');
    }
    
    cout << "Thanks for playing!\n";
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
    
    // TODO: Safe element access with bounds checking
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
        // TODO: Test normal usage
        SafeArray arr{5};
        arr.fill(42);
        
        cout << "Array contents: ";
        for (size_t i = 0; i < arr.size(); i++) {
            cout << arr.at(i) << " ";
        }
        cout << endl;
        
        // TODO: Test bounds checking
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
    
    // TODO: Test zero-size array
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
            
            // TODO: Process each line with error checking
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
    // TODO: Create a test file
    {
        ofstream test_file{"test_input.txt"};
        test_file << "This is line 1\n";
        test_file << "This is line 2\n";
        test_file << "WARNING: This is a warning\n";
        test_file << "This is line 4\n";
        test_file << "ERROR: This line has an error\n";
        test_file << "This line won't be processed\n";
    }
    
    // TODO: Test exception handling
    try {
        FileProcessor::process_file("test_input.txt");
    } catch (const runtime_error& e) {
        cout << "Runtime error caught: " << e.what() << endl;
    }
    
    // TODO: Test with non-existent file
    try {
        FileProcessor::process_file("nonexistent.txt");
    } catch (const runtime_error& e) {
        cout << "Expected error: " << e.what() << endl;
    }
    
    // TODO: Test safe file operation
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

// TODO: Custom exception hierarchy
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
    // TODO: Test different exception types
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
    
    // TODO: Test with catch hierarchy
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

### Problem Set 3: Advanced Control Flow (40 minutes)

#### Problem 3.1: State Machine Implementation (25 minutes)
**Practice complex control flow with state management:**

```cpp
#include <iostream>
#include <string>
using namespace std;

enum class State {
    IDLE,
    PROCESSING,
    WAITING,
    ERROR,
    FINISHED
};

class StateMachine {
private:
    State current_state;
    int error_count;
    int process_count;
    
public:
    StateMachine() : current_state{State::IDLE}, error_count{0}, process_count{0} {}
    
    void handle_event(const string& event) {
        cout << "Current state: " << state_to_string(current_state) 
             << ", Event: " << event << endl;
        
        switch (current_state) {
            case State::IDLE:
                if (event == "start") {
                    current_state = State::PROCESSING;
                    cout << "  -> Starting processing\n";
                } else {
                    cout << "  -> Ignoring event in IDLE state\n";
                }
                break;
                
            case State::PROCESSING:
                if (event == "success") {
                    process_count++;
                    current_state = State::WAITING;
                    cout << "  -> Processing completed, waiting for next\n";
                } else if (event == "error") {
                    error_count++;
                    current_state = State::ERROR;
                    cout << "  -> Error occurred\n";
                } else if (event == "finish") {
                    current_state = State::FINISHED;
                    cout << "  -> Processing finished\n";
                }
                break;
                
            case State::WAITING:
                if (event == "continue") {
                    current_state = State::PROCESSING;
                    cout << "  -> Continuing processing\n";
                } else if (event == "finish") {
                    current_state = State::FINISHED;
                    cout << "  -> Finished from waiting\n";
                }
                break;
                
            case State::ERROR:
                if (event == "retry") {
                    if (error_count < 3) {
                        current_state = State::PROCESSING;
                        cout << "  -> Retrying processing\n";
                    } else {
                        cout << "  -> Too many errors, staying in ERROR state\n";
                    }
                } else if (event == "reset") {
                    error_count = 0;
                    current_state = State::IDLE;
                    cout << "  -> Reset to IDLE\n";
                }
                break;
                
            case State::FINISHED:
                if (event == "reset") {
                    current_state = State::IDLE;
                    process_count = 0;
                    error_count = 0;
                    cout << "  -> Reset to IDLE\n";
                } else {
                    cout << "  -> Already finished\n";
                }
                break;
        }
        
        cout << "  New state: " << state_to_string(current_state) << "\n\n";
    }
    
    string state_to_string(State s) const {
        switch (s) {
            case State::IDLE: return "IDLE";
            case State::PROCESSING: return "PROCESSING";
            case State::WAITING: return "WAITING";
            case State::ERROR: return "ERROR";
            case State::FINISHED: return "FINISHED";
            default: return "UNKNOWN";
        }
    }
    
    void print_stats() const {
        cout << "Statistics:\n";
        cout << "  Processes completed: " << process_count << endl;
        cout << "  Errors encountered: " << error_count << endl;
        cout << "  Current state: " << state_to_string(current_state) << endl;
    }
};

int main() {
    StateMachine machine;
    
    // TODO: Test state machine with various events
    machine.handle_event("start");
    machine.handle_event("success");
    machine.handle_event("continue");
    machine.handle_event("error");
    machine.handle_event("retry");
    machine.handle_event("success");
    machine.handle_event("finish");
    
    machine.print_stats();
    
    // TODO: Test error handling
    cout << "\n=== Testing error recovery ===\n";
    machine.handle_event("reset");
    machine.handle_event("start");
    
    // Generate multiple errors
    for (int i = 0; i < 4; i++) {
        machine.handle_event("error");
        machine.handle_event("retry");
    }
    
    machine.print_stats();
    
    return 0;
}
```

#### Problem 3.2: Resource Pool with RAII (15 minutes)
**Combine RAII with complex control flow:**

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
using namespace std;

class Resource {
private:
    int id;
    bool in_use;
    
public:
    Resource(int resource_id) : id{resource_id}, in_use{false} {
        cout << "Resource " << id << " created\n";
    }
    
    ~Resource() {
        cout << "Resource " << id << " destroyed\n";
    }
    
    void use() {
        if (in_use) {
            throw runtime_error("Resource " + to_string(id) + " already in use");
        }
        in_use = true;
        cout << "Resource " << id << " now in use\n";
    }
    
    void release() {
        in_use = false;
        cout << "Resource " << id << " released\n";
    }
    
    bool is_available() const { return !in_use; }
    int get_id() const { return id; }
};

class ResourcePool {
private:
    vector<unique_ptr<Resource>> resources;
    
public:
    ResourcePool(int pool_size) {
        for (int i = 0; i < pool_size; i++) {
            resources.push_back(make_unique<Resource>(i + 1));
        }
        cout << "Resource pool created with " << pool_size << " resources\n";
    }
    
    Resource* acquire() {
        for (auto& resource : resources) {
            if (resource->is_available()) {
                resource->use();
                return resource.get();
            }
        }
        throw runtime_error("No resources available");
    }
};

// RAII wrapper for automatic resource release
class ResourceGuard {
private:
    Resource* resource;
    
public:
    ResourceGuard(Resource* res) : resource{res} {}
    
    ~ResourceGuard() {
        if (resource) {
            resource->release();
        }
    }
    
    Resource* get() const { return resource; }
    
    // Prevent copying
    ResourceGuard(const ResourceGuard&) = delete;
    ResourceGuard& operator=(const ResourceGuard&) = delete;
};

int main() {
    try {
        ResourcePool pool{3};
        
        // TODO: Test normal resource usage with RAII
        {
            ResourceGuard guard1{pool.acquire()};
            cout << "Using resource " << guard1.get()->get_id() << endl;
            
            {
                ResourceGuard guard2{pool.acquire()};
                cout << "Using resource " << guard2.get()->get_id() << endl;
                
                // guard2 automatically releases here
            }
            
            // guard1 automatically releases here
        }
        
        cout << "\n=== Testing resource exhaustion ===\n";
        
        // TODO: Acquire all resources
        vector<unique_ptr<ResourceGuard>> guards;
        
        for (int i = 0; i < 3; i++) {
            try {
                guards.push_back(make_unique<ResourceGuard>(pool.acquire()));
                cout << "Acquired resource " << i + 1 << endl;
            } catch (const runtime_error& e) {
                cout << "Failed to acquire resource: " << e.what() << endl;
            }
        }
        
        // Try to acquire one more (should fail)
        try {
            ResourceGuard extra_guard{pool.acquire()};
        } catch (const runtime_error& e) {
            cout << "Expected failure: " << e.what() << endl;
        }
        
        // All guards automatically release when going out of scope
        
    } catch (const exception& e) {
        cout << "Unexpected error: " << e.what() << endl;
    }
    
    return 0;
}
```

---

## 🔧 Quick Reference & Troubleshooting

### Control Flow Quick Reference

```cpp
// Conditional statements
if (condition) { /* ... */ }
else if (other_condition) { /* ... */ }
else { /* ... */ }

// C++17: if with initialization
if (auto result = function(); result > 0) { /* ... */ }

// Switch statement
switch (expression) {
    case value1:
        // code
        break;
    case value2:
    case value3:  // Fall-through
        // code
        break;
    default:
        // code
        break;
}

// Loops
for (int i = 0; i < n; i++) { /* ... */ }           // Traditional
for (const auto& item : container) { /* ... */ }    // Range-based
while (condition) { /* ... */ }                     // Pre-test
do { /* ... */ } while (condition);                 // Post-test
```

### Exception Handling Quick Reference

```cpp
// Throwing exceptions
throw std::runtime_error("Error message");
throw std::invalid_argument("Invalid input");

// Catching exceptions
try {
    // Code that might throw
} catch (const std::runtime_error& e) {
    // Handle runtime errors
} catch (const std::exception& e) {
    // Handle all standard exceptions
} catch (...) {
    // Handle any exception
}

// RAII pattern
{
    std::ifstream file{"filename.txt"};  // Constructor acquires
    // Use file
}  // Destructor automatically releases
```

### Common Control Flow Errors

#### 1. Missing Break in Switch
```cpp
switch (value) {
    case 1:
        do_something();    // ❌ Falls through to case 2!
    case 2:
        do_something_else();
        break;
}

switch (value) {
    case 1:
        do_something();
        break;            // ✅ Prevents fall-through
    case 2:
        do_something_else();
        break;
}
```

#### 2. Exception Not Caught by Reference
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

#### 3. Resource Leaks in Exception Paths
```cpp
void bad_function() {
    int* data = new int[100];
    if (error_occurred()) {
        throw std::runtime_error("Error");  // ❌ Memory leak!
    }
    delete[] data;
}

void good_function() {
    std::unique_ptr<int[]> data{new int[100]};  // ✅ RAII
    if (error_occurred()) {
        throw std::runtime_error("Error");  // Automatic cleanup
    }
}
```

---

## ✅ Chapter 8 Success Checklist

### Control Flow Mastery
- [ ] Can use if/else statements with proper syntax and logic
- [ ] Can implement switch statements with proper break handling
- [ ] Can write different types of loops (for, while, do-while, range-based)
- [ ] Understand when to use each type of loop

### Exception Handling
- [ ] Can throw and catch exceptions properly
- [ ] Can create custom exception classes
- [ ] Can use try/catch blocks with multiple exception types
- [ ] Understand exception safety and RAII

### Advanced Patterns
- [ ] Can implement state machines using switch statements
- [ ] Can combine RAII with exception handling
- [ ] Can write exception-safe code using RAII principles
- [ ] Can debug control flow using VS Code effectively

---

## 🚀 What's Next?

**Chapter 9: Functions** will cover:
- Function pointers and lambda expressions
- Function objects (functors) and std::function
- Higher-order functions and callbacks
- Advanced function techniques and patterns

**You've mastered control flow and exception handling!** 🎉 These are fundamental building blocks that make your programs robust and reliable. You now understand how to write code that handles both normal execution paths and error conditions gracefully.

**Key Takeaway**: Good control flow makes programs predictable and maintainable. Exception handling with RAII makes programs robust and resource-safe. These patterns are essential for professional C++ development.

---

*Remember: Control flow determines the logic of your program, while exception handling determines its robustness. RAII ties them together by ensuring resources are managed correctly regardless of how execution flows through your code.*