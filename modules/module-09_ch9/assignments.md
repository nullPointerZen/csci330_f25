# Chapter 9: Functions - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 9 "Functions"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 1.5 hours total for both problem sets
- Test all programs thoroughly before submission

**Target Audience**: Students with Python/Java background  
**Total Time**: 1.5 hours (90 minutes)  
**Prerequisites**: Chapters 1-8 completed + Chapter 9 lesson  

## Problem Set Structure

- **Problem Set 1**: Function Pointers and Callbacks (45 minutes)
- **Problem Set 2**: Lambda Expressions and Captures (60 minutes) 
- **Problem Set 3**: Function Objects and Integration Project (30 minutes)

---

## Problem Set 1: Function Pointers and Callbacks (45 minutes)

### Problem 1.1: Calculator with Function Pointers (15 minutes)

**Background**: Coming from Python's first-class functions or Java method references, learn C++ function pointer syntax and usage.

**Task**: Create a simple calculator using function pointers for operations.

**Requirements**:
1. Implement basic arithmetic functions: add, subtract, multiply, divide
2. Use function pointers to store and call operations
3. Create a menu system that selects operations via function pointer array
4. Handle division by zero appropriately

**Starter Code**:
```cpp
#include <iostream>
#include <cstdio>

// TODO: Implement these functions
double add(double a, double b) {
    // Your implementation here
}

double subtract(double a, double b) {
    // Your implementation here
}

double multiply(double a, double b) {
    // Your implementation here
}

double divide(double a, double b) {
    // Your implementation here - handle division by zero
}

int main() {
    // TODO: Create array of function pointers
    double (*operations[])(double, double) = {add, subtract, multiply, divide};
    const char* op_names[] = {"Add", "Subtract", "Multiply", "Divide"};
    
    double a, b;
    int choice;
    
    std::cout << "Enter two numbers: ";
    std::cin >> a >> b;
    
    std::cout << "\nSelect operation:\n";
    for(int i = 0; i < 4; i++) {
        std::cout << i + 1 << ". " << op_names[i] << "\n";
    }
    std::cout << "Choice: ";
    std::cin >> choice;
    
    // TODO: Validate choice and call appropriate function
    // TODO: Display result
    
    return 0;
}
```

**Expected Output**:
```
Enter two numbers: 15 3
Select operation:
1. Add
2. Subtract  
3. Multiply
4. Divide
Choice: 4
15 / 3 = 5

Enter two numbers: 10 0
Select operation:
1. Add
2. Subtract
3. Multiply
4. Divide
Choice: 4
Error: Division by zero!
```

**Learning Goals**:
- Function pointer declaration and initialization
- Array of function pointers
- Dereferencing and calling through function pointers
- Error handling in function pointer context

---

### Problem 1.2: Event System with Callbacks (20 minutes)

**Background**: Implement a callback pattern similar to Python decorators or Java listeners.

**Task**: Create a simple event system that notifies multiple listeners using callbacks.

**Requirements**:
1. Create different types of event handlers as regular functions
2. Implement an event system that can register multiple callbacks
3. Use function pointers to store and call event handlers
4. Demonstrate with at least 3 different event types

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <string>

// Event handler function type
typedef void (*EventHandler)(const std::string& event_data);

// TODO: Implement different event handlers
void log_handler(const std::string& event_data) {
    // Print log message with timestamp simulation
}

void alert_handler(const std::string& event_data) {
    // Print alert message
}

void debug_handler(const std::string& event_data) {
    // Print debug information
}

class EventSystem {
private:
    std::vector<EventHandler> handlers;
    
public:
    // TODO: Add method to register handlers
    void register_handler(EventHandler handler) {
        // Your implementation here
    }
    
    // TODO: Add method to fire events to all handlers
    void fire_event(const std::string& event_data) {
        // Your implementation here
    }
    
    // TODO: Add method to show registered handler count
    size_t get_handler_count() const {
        // Your implementation here
    }
};

int main() {
    EventSystem event_system;
    
    // TODO: Register handlers
    // TODO: Fire some test events
    // TODO: Show system working with multiple handlers
    
    return 0;
}
```

**Expected Behavior**:
```
Registering event handlers...
Handlers registered: 3

Firing event: "User logged in"
[LOG] User logged in
[ALERT] Critical event: User logged in  
[DEBUG] Event details: User logged in

Firing event: "File uploaded"
[LOG] File uploaded
[ALERT] Critical event: File uploaded
[DEBUG] Event details: File uploaded
```

**Learning Goals**:
- Callback pattern implementation
- Function pointer storage in containers
- Multiple function pointer management
- Real-world event system design

---

### Problem 1.3: Sorting with Custom Comparators (10 minutes)

**Background**: Use function pointers for customizable comparison, similar to Python's key parameter or Java's Comparator.

**Task**: Implement a simple sorting function that accepts different comparison strategies.

**Requirements**:
1. Create comparison functions for ascending and descending order
2. Implement a sort function that accepts a comparison function pointer
3. Test with different data sets and comparison strategies

**Starter Code**:
```cpp
#include <iostream>
#include <vector>

// Comparison function type - returns true if first should come before second
typedef bool (*Comparator)(int a, int b);

// TODO: Implement comparison functions
bool ascending(int a, int b) {
    // Your implementation here
}

bool descending(int a, int b) {
    // Your implementation here
}

// TODO: Implement simple bubble sort with custom comparator
void sort_with_comparator(std::vector<int>& data, Comparator comp) {
    // Your implementation here - use bubble sort for simplicity
}

void print_vector(const std::vector<int>& data) {
    for(int n : data) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};
    
    std::cout << "Original: ";
    print_vector(numbers);
    
    // TODO: Sort ascending
    // TODO: Sort descending  
    // TODO: Show results
    
    return 0;
}
```

**Learning Goals**:
- Function pointers as algorithm parameters
- Strategy pattern with function pointers
- Comparison function design

---

## Problem Set 2: Lambda Expressions and Captures (60 minutes)

### Problem 2.1: STL Algorithm Integration (20 minutes)

**Background**: Use lambdas with STL algorithms, similar to Python's list comprehensions or Java streams.

**Task**: Process a list of student data using various STL algorithms with lambda expressions.

**Requirements**:
1. Use lambdas with std::for_each, std::find_if, std::transform, std::count_if
2. Demonstrate different capture modes (by value, by reference)
3. Process student grades and generate statistics

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

struct Student {
    std::string name;
    int grade;
    
    Student(const std::string& n, int g) : name(n), grade(g) {}
};

int main() {
    std::vector<Student> students = {
        {"Alice", 92}, {"Bob", 87}, {"Charlie", 78}, 
        {"Diana", 95}, {"Eve", 82}, {"Frank", 69}
    };
    
    std::cout << "All students:\n";
    // TODO: Use std::for_each with lambda to print all students
    
    std::cout << "\nHonor roll students (grade >= 90):\n";
    // TODO: Use std::copy_if with lambda to find honor roll students
    
    // TODO: Count students passing (grade >= 70)
    int passing_count = 0; // Use std::count_if
    
    // TODO: Calculate average grade using std::accumulate and lambda
    double average = 0.0;
    
    // TODO: Apply curve (+5 points) using std::transform with capture
    int curve_points = 5;
    
    std::cout << "\nAfter applying " << curve_points << " point curve:\n";
    // TODO: Print curved grades
    
    std::cout << "\nStatistics:\n";
    std::cout << "Passing students: " << passing_count << "\n";
    std::cout << "Average grade: " << average << "\n";
    
    return 0;
}
```

**Expected Output**:
```
All students:
Alice: 92
Bob: 87
Charlie: 78
Diana: 95
Eve: 82
Frank: 69

Honor roll students (grade >= 90):
Alice: 92
Diana: 95

After applying 5 point curve:
Alice: 97
Bob: 92
Charlie: 83
Diana: 100
Eve: 87
Frank: 74

Statistics:
Passing students: 5
Average grade: 85.5
```

**Learning Goals**:
- Lambda integration with STL algorithms  
- Capture by value vs reference
- Predicate lambdas
- Transform lambdas

---

### Problem 2.2: Advanced Lambda Captures (25 minutes)

**Background**: Master different capture modes and understand when to use each.

**Task**: Create a data processing class that uses lambdas with various capture modes.

**Requirements**:
1. Implement lambdas with capture by value, by reference, and mixed captures
2. Create a processing pipeline using lambda chains
3. Handle member variable captures correctly
4. Demonstrate lambda lifetime and scope issues

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <string>

class DataProcessor {
private:
    std::string processor_name;
    int processing_count;
    std::vector<int> results;
    
public:
    DataProcessor(const std::string& name) 
        : processor_name(name), processing_count(0) {}
    
    // TODO: Create a lambda that captures member variables appropriately
    auto create_filter(int threshold) {
        // Return lambda that filters values above threshold
        // Should increment processing_count for each item processed
        // Should capture processor_name by value and processing_count by reference
    }
    
    // TODO: Create a lambda factory for transformations
    auto create_transformer(int multiplier, int offset) {
        // Return lambda that applies: value * multiplier + offset
        // Use init captures to store multiplier and offset
    }
    
    // TODO: Create a stateful lambda for accumulation
    auto create_accumulator() {
        // Return lambda that keeps running sum
        // Should store sum in capture and return current total each time
    }
    
    void process_data(const std::vector<int>& input_data) {
        std::cout << "Processing with " << processor_name << ":\n";
        
        // TODO: Use the lambdas created above to:
        // 1. Filter data (threshold = 10)
        // 2. Transform filtered data (multiply by 2, add 5)  
        // 3. Accumulate results
        
        std::cout << "Items processed: " << processing_count << "\n";
    }
    
    // TODO: Create a lambda that demonstrates capture lifetime issues
    auto create_problematic_lambda() {
        int local_var = 42;
        // Return lambda that captures local_var by reference
        // This will demonstrate dangling reference problem
        return [&local_var]() { return local_var; };
    }
    
    // TODO: Fixed version of the above
    auto create_safe_lambda() {
        int local_var = 42;
        // Return lambda that captures local_var safely
    }
};

int main() {
    DataProcessor processor("NumberCruncher");
    std::vector<int> test_data = {5, 15, 8, 22, 3, 18, 12, 7};
    
    processor.process_data(test_data);
    
    // TODO: Demonstrate the problematic vs safe lambda
    std::cout << "\nTesting lambda lifetime:\n";
    
    return 0;
}
```

**Learning Goals**:
- Different capture modes (=, &, mixed)
- Init captures (C++14)
- Member variable captures
- Lambda lifetime and scope safety
- Stateful lambdas

---

### Problem 2.3: Generic Lambdas and Function Templates (15 minutes)

**Background**: Use generic lambdas (C++14) for flexible, reusable code.

**Task**: Create utility functions using generic lambdas that work with different data types.

**Requirements**:
1. Create generic lambdas that work with multiple types
2. Use auto parameters effectively
3. Combine with STL algorithms for flexible processing
4. Handle type deduction correctly

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    // TODO: Create a generic lambda for printing with custom format
    auto printer = [](const auto& item, const std::string& prefix = "") {
        // Your implementation here
    };
    
    // TODO: Create a generic lambda for comparison
    auto less_than = [](const auto& a, const auto& b) {
        // Your implementation here
    };
    
    // TODO: Create a generic lambda for transformation
    auto doubler = [](auto item) {
        // Your implementation here - should work for numbers and strings
    };
    
    // Test with integers
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Original numbers: ";
    std::for_each(numbers.begin(), numbers.end(), 
                  [&printer](const auto& n) { printer(n, ""); });
    std::cout << "\n";
    
    // TODO: Use doubler with transform on numbers
    
    // Test with strings  
    std::vector<std::string> words = {"hello", "world", "cpp", "lambda"};
    std::cout << "Original words: ";
    // TODO: Print words using generic printer
    
    // TODO: Use doubler with transform on strings (should concatenate with itself)
    
    // Test comparison with different types
    std::cout << "5 < 10: " << less_than(5, 10) << "\n";
    std::cout << "hello < world: " << less_than(std::string("hello"), std::string("world")) << "\n";
    
    // TODO: Use generic comparison with std::sort
    
    return 0;
}
```

**Expected Output**:
```
Original numbers: 1 2 3 4 5
Doubled numbers: 2 4 6 8 10
Original words: hello world cpp lambda  
Doubled words: hellohello worldworld cppcpp lambdalambda
5 < 10: 1
hello < world: 1
Sorted numbers: 1 2 3 4 5
Sorted words: cpp hello lambda world
```

**Learning Goals**:
- Generic lambda syntax with auto
- Type deduction in lambdas
- Template-like behavior without explicit templates
- STL integration with generic lambdas

---

## Problem Set 3: Function Objects and Integration Project (30 minutes)

### Problem 3.1: Custom Function Objects (15 minutes)

**Background**: Create stateful function objects (functors) for scenarios where lambdas aren't sufficient.

**Task**: Implement function objects for statistical analysis that maintain state across calls.

**Requirements**:
1. Create function objects with meaningful state
2. Implement operator() correctly
3. Provide methods to access accumulated state
4. Compare with equivalent lambda approaches

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// TODO: Implement a statistics accumulator function object
class StatisticsAccumulator {
private:
    // TODO: Add member variables for count, sum, sum_squares, min, max
    
public:
    StatisticsAccumulator() {
        // TODO: Initialize state
    }
    
    // TODO: Implement function call operator
    void operator()(double value) {
        // TODO: Update statistics with new value
    }
    
    // TODO: Implement getter methods
    double get_mean() const {
        // TODO: Calculate and return mean
    }
    
    double get_variance() const {
        // TODO: Calculate and return variance
    }
    
    double get_std_dev() const {
        // TODO: Calculate and return standard deviation
    }
    
    double get_min() const { /* TODO */ }
    double get_max() const { /* TODO */ }
    int get_count() const { /* TODO */ }
    
    void reset() {
        // TODO: Reset all statistics
    }
};

// TODO: Implement a histogram function object
class HistogramBuilder {
private:
    // TODO: Add data structure to store bins and counts
    
public:
    HistogramBuilder(double min_val, double max_val, int num_bins) {
        // TODO: Initialize histogram bins
    }
    
    void operator()(double value) {
        // TODO: Add value to appropriate bin
    }
    
    void print_histogram() const {
        // TODO: Print histogram bars
    }
};

int main() {
    std::vector<double> data = {
        23.5, 45.2, 12.8, 67.1, 34.6, 89.3, 56.7, 78.9, 
        43.2, 29.1, 65.4, 87.6, 54.3, 32.8, 76.5
    };
    
    std::cout << "Processing " << data.size() << " data points:\n";
    
    // TODO: Use StatisticsAccumulator with std::for_each
    StatisticsAccumulator stats;
    
    // TODO: Print statistics
    
    // TODO: Use HistogramBuilder
    HistogramBuilder histogram(0, 100, 10);
    
    std::cout << "\nHistogram:\n";
    // TODO: Print histogram
    
    return 0;
}
```

**Learning Goals**:
- Stateful function object design
- operator() implementation
- State management in functors
- When to use functors vs lambdas

---

### Problem 3.2: Complete Function Integration Project (15 minutes)

**Background**: Integrate all Chapter 9 concepts in a practical application.

**Task**: Create a flexible data processing pipeline that uses function pointers, lambdas, functors, and std::function.

**Requirements**:
1. Create a processing pipeline that can accept different types of callables
2. Use std::function for type erasure
3. Implement pipeline stages using different function types
4. Demonstrate composability and flexibility

**Starter Code**:
```cpp
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <map>

// Function pointer type for simple transformations
typedef double (*SimpleTransform)(double);

// TODO: Implement some simple transform functions
double square(double x) { /* TODO */ }
double cube(double x) { /* TODO */ }
double negate(double x) { /* TODO */ }

// TODO: Implement a pipeline stage function object
class ScaleAndOffset {
private:
    double scale, offset;
    
public:
    ScaleAndOffset(double s, double o) : scale(s), offset(o) {}
    double operator()(double x) const { /* TODO */ }
};

class DataPipeline {
private:
    std::vector<std::function<double(double)>> stages;
    std::string pipeline_name;
    
public:
    DataPipeline(const std::string& name) : pipeline_name(name) {}
    
    // TODO: Add method to register processing stages
    void add_stage(std::function<double(double)> stage) {
        // TODO: Add stage to pipeline
    }
    
    // TODO: Process a single value through all stages
    double process(double input) {
        // TODO: Apply all stages in sequence
    }
    
    // TODO: Process a vector of values
    std::vector<double> process_batch(const std::vector<double>& inputs) {
        // TODO: Process all inputs and return results
    }
    
    void print_info() const {
        std::cout << "Pipeline '" << pipeline_name 
                  << "' has " << stages.size() << " stages\n";
    }
};

int main() {
    std::vector<double> test_data = {1.0, 2.0, 3.0, 4.0, 5.0};
    
    // TODO: Create pipeline and add different types of stages
    DataPipeline pipeline("MathProcessor");
    
    // Add function pointer stage
    pipeline.add_stage(square);
    
    // Add lambda stage  
    double multiplier = 0.5;
    pipeline.add_stage([multiplier](double x) { return x * multiplier; });
    
    // Add function object stage
    pipeline.add_stage(ScaleAndOffset(2.0, 10.0));
    
    // Add generic lambda stage
    pipeline.add_stage([](auto x) { return x < 0 ? 0 : x; }); // ReLU-like
    
    pipeline.print_info();
    
    std::cout << "\nProcessing data through pipeline:\n";
    // TODO: Process test data and show results
    
    std::cout << "\nOriginal -> Processed:\n";
    for(double value : test_data) {
        double result = pipeline.process(value);
        std::cout << value << " -> " << result << "\n";
    }
    
    return 0;
}
```

**Expected Output**:
```
Pipeline 'MathProcessor' has 4 stages

Processing data through pipeline:

Original -> Processed:
1 -> 11
2 -> 14  
3 -> 19
4 -> 26
5 -> 35
```

**Learning Goals**:
- Integration of all function types
- std::function for type erasure
- Composable design patterns
- Real-world pipeline architecture

---

## Submission Guidelines

### What to Submit

1. **Source code files** for all problems with clear comments
2. **Compilation and execution output** showing your programs working
3. **Brief reflection** (2-3 paragraphs) comparing C++ function features to Python/Java

### File Organization
```
chapter09_solutions/
├── problem_set_1/
│   ├── problem_1_1_calculator.cpp
│   ├── problem_1_2_event_system.cpp
│   └── problem_1_3_sorting.cpp
├── problem_set_2/
│   ├── problem_2_1_stl_lambdas.cpp
│   ├── problem_2_2_lambda_captures.cpp
│   └── problem_2_3_generic_lambdas.cpp
├── problem_set_3/
│   ├── problem_3_1_function_objects.cpp
│   └── problem_3_2_integration_project.cpp
└── README.md (with compilation notes and reflection)
```

### Evaluation Criteria

1. **Correctness** (40%): Programs compile and work as specified
2. **Function Usage** (25%): Appropriate use of function pointers, lambdas, functors
3. **Code Quality** (20%): Clean, readable, well-organized code  
4. **Best Practices** (15%): Following C++ idioms and avoiding common pitfalls

### Time Management Tips

- **Problem Set 1**: Focus on getting function pointer syntax right
- **Problem Set 2**: Spend time understanding capture modes - this is crucial
- **Problem Set 3**: Start simple and build complexity incrementally

### Common Pitfalls to Avoid

1. **Function Pointer Syntax**: Remember the parentheses in declarations
2. **Lambda Captures**: Distinguish between capture by value [=] and reference [&]
3. **Lifetime Issues**: Be careful with reference captures and local variables
4. **std::function Overhead**: Understand when the type erasure cost is worth it
5. **Generic Lambdas**: Remember they're template-like, not truly generic

### Getting Help

- Refer to `chapter_09_quick_help.md` for syntax reminders
- Check solution files if completely stuck on syntax
- Focus on understanding when to use each function type

---

## Extension Challenges (Optional)

For students who finish early:

1. **Perfect Forwarding**: Implement function wrappers using perfect forwarding
2. **Recursive Lambdas**: Create self-referencing lambdas using std::function
3. **Currying**: Implement automatic currying for multi-parameter functions
4. **Performance**: Compare performance of different callable types in tight loops

These extensions provide additional learning opportunities for advanced students but are not required for course completion.

## Success Criteria

You've mastered Chapter 9 function concepts when you can:
- Choose the appropriate function type (pointer, lambda, functor, std::function) for different scenarios
- Implement lambdas with correct capture modes for various use cases  
- Create stateful function objects when lambdas aren't sufficient
- Design flexible systems using std::function for type erasure
- Apply functional programming concepts effectively in C++

Remember: Modern C++ favors lambdas for most cases, but understanding all options helps you write more effective and maintainable code!