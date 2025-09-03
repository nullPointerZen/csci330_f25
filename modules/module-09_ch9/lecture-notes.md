# Chapter 9: Functions - Complete Guide

## 📖 Learning Sequence (IMPORTANT!)

**🔄 How This Chapter Works:**
1. **📚 FIRST**: Read Textbook Chapter 9 "Functions" (2-3 hours)
2. **🔍 SECOND**: Work through these lecture notes for Python/Java context and hands-on practice (4-5 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 9 "Functions" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Master** function pointers and understand their use cases vs Python's function objects
2. **Create and use** lambda expressions for inline functions and callbacks
3. **Design** function objects (functors) and understand when to use them
4. **Apply** std::function as a type-erased wrapper for callable objects
5. **Implement** higher-order functions that accept and return other functions
6. **Debug** function calls and lambda captures using VS Code

**⏱️ Time Budget:**
- **📚 Textbook Reading: 2-3 hours** (Chapter 9: "Functions" - REQUIRED FIRST)
- **💻 Hands-on Work: 4-5 hours** (course materials + assignments + debugging)
- **📖 Note: Reading time is separate and must be completed BEFORE hands-on work**

**📝 Integration Note**: This chapter combines many previous concepts - if struggling, re-read relevant textbook sections on pointers and templates.

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](../../setup/DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 🔧 Core Concepts: Advanced Function Features (2.5 hours)

**📖 Bridge to Textbook**: Now that you've read about C++ advanced function features in Chapter 9, let's connect those concepts to the Python/Java knowledge you already have.

### 1. Function Pointers: C++ vs Python/Java

**From Textbook to Context**: The textbook covered function pointers. Here's how they compare to first-class functions in Python and method references in Java:

**Function pointers let you store and call functions like data:**

```cpp
// Basic function pointer syntax
double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }

// Function pointer declaration and usage
double (*operation)(double, double) = add;    // Points to add function
double result = operation(5.0, 3.0);          // Calls add(5.0, 3.0)

operation = subtract;                          // Now points to subtract
result = operation(5.0, 3.0);                // Calls subtract(5.0, 3.0)
```

| Aspect | C++ Function Pointers | Python Functions | Java Method References |
|--------|----------------------|------------------|----------------------|
| **Nature** | Pointers to functions | First-class objects | Method references |
| **Declaration** | `int (*func)(int, int);` | No declaration needed | `Function<Integer, Integer>` |
| **Assignment** | `func = &add;` or `func = add;` | `func = add` | `func = Math::max;` |
| **Calling** | `result = func(5, 3);` | `result = func(5, 3)` | `result = func.apply(5, 3);` |

### 2. Lambda Expressions: Inline Functions with Context

**📖 Bridge to Textbook**: You read about lambda expressions in the textbook. Here's how C++ lambdas compare to Python lambdas and Java lambda expressions:

**Lambdas solve the problem of needing small, context-aware functions without declaring them separately:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Example: Processing employee data with context-sensitive operations
struct Employee {
    string name;
    double salary;
    int years_service;
};

int main() {
    vector<Employee> employees = {
        {"Alice", 75000, 3},
        {"Bob", 85000, 7},
        {"Carol", 65000, 2},
        {"David", 95000, 10}
    };
    
    // Lambda captures context - current company bonus policy
    double bonus_threshold = 80000;
    int service_requirement = 5;
    
    // Find employees eligible for bonus - lambda captures the rules
    auto eligible_for_bonus = [bonus_threshold, service_requirement](const Employee& emp) {
        return emp.salary >= bonus_threshold && emp.years_service >= service_requirement;
    };
    
    cout << "Employees eligible for bonus:\n";
    for (const auto& emp : employees) {
        if (eligible_for_bonus(emp)) {
            cout << "  " << emp.name << " ($" << emp.salary << ", " 
                 << emp.years_service << " years)\n";
        }
    }
    
    // Lambda with mutable capture - track how many we've processed
    int processed_count = 0;
    auto process_and_count = [&processed_count](const Employee& emp) {
        processed_count++;
        cout << "Processing #" << processed_count << ": " << emp.name << "\n";
    };
    
    cout << "\nProcessing all employees:\n";
    for_each(employees.begin(), employees.end(), process_and_count);
    cout << "Total processed: " << processed_count << "\n";
    
    return 0;
}
```

**Lambda Capture Modes - Choose Based on What You Need:**

```cpp
int threshold = 100;
string prefix = "Item: ";
vector<int> data = {50, 150, 75, 200};

// Capture nothing - pure function
auto is_positive = [](int x) { return x > 0; };

// Capture by value - safe copy, original unchanged
auto above_threshold = [threshold](int x) { return x > threshold; };
threshold = 200;  // Won't affect lambda - it captured old value

// Capture by reference - sees changes to original
auto above_current = [&threshold](int x) { return x > threshold; };
threshold = 200;  // Lambda now uses 200, not 100

// Mixed capture - flexible control
auto format_item = [=, &prefix](int value) {  // threshold by value, prefix by ref
    return prefix + to_string(value);  // Uses current prefix, original threshold
};

// Capture all by reference - convenient but be careful!
auto debug_print = [&](int x) {  // Captures everything it uses by reference
    cout << prefix << x << " (threshold: " << threshold << ")\n";
};
```

### 3. Function Objects (Functors)

**📖 Bridge to Textbook**: The textbook introduced function objects (functors). Here's how this C++-unique approach compares to callable objects in Python/Java:

**Function objects are classes that overload operator():**

```cpp
#include <iostream>
using namespace std;

// Function object for comparison
class GreaterThan {
private:
    int threshold;
    
public:
    GreaterThan(int t) : threshold{t} {}
    
    bool operator()(int value) const {
        return value > threshold;
    }
};

// Function object with state
class Counter {
private:
    mutable int count = 0;
    
public:
    int operator()() const {
        return ++count;
    }
    
    int get_count() const { return count; }
};

int main() {
    GreaterThan gt5{5};
    cout << "Is 7 > 5? " << gt5(7) << endl;    // true
    cout << "Is 3 > 5? " << gt5(3) << endl;    // false
    
    Counter counter;
    cout << "Count: " << counter() << endl;    // 1
    cout << "Count: " << counter() << endl;    // 2
    cout << "Total: " << counter.get_count() << endl;  // 2
    
    return 0;
}
```

### 4. std::function: Type-Erased Wrapper

**📖 Bridge to Textbook**: The textbook covered std::function as a unified way to store callable objects. Here's how this relates to Python's flexible function storage:

**std::function can hold any callable object:**

```cpp
#include <iostream>
#include <functional>
using namespace std;

// Regular function
int add(int a, int b) { return a + b; }

// Function object
struct Multiply {
    int operator()(int a, int b) const { return a * b; }
};

int main() {
    // std::function can hold different callable types
    function<int(int, int)> calculator;
    
    // Assign function pointer
    calculator = add;
    cout << "Add: " << calculator(5, 3) << endl;
    
    // Assign function object
    calculator = Multiply{};
    cout << "Multiply: " << calculator(5, 3) << endl;
    
    // Assign lambda
    calculator = [](int a, int b) { return a - b; };
    cout << "Subtract: " << calculator(5, 3) << endl;
    
    return 0;
}
```

### 5. Higher-Order Functions

**📖 Bridge to Textbook**: The textbook discussed higher-order functions. Here's how C++ implements this functional programming concept compared to Python's natural support:

**Functions that take or return other functions:**

```cpp
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

// Function that takes a function as parameter
template<typename Func>
void apply_to_all(vector<int>& vec, Func f) {
    for (auto& item : vec) {
        item = f(item);
    }
}

// Function that returns a function
function<int(int)> make_multiplier(int factor) {
    return [factor](int x) { return x * factor; };
}

// Function composition
template<typename F1, typename F2>
auto compose(F1 f1, F2 f2) {
    return [f1, f2](auto x) { return f1(f2(x)); };
}

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Use higher-order function with lambda
    apply_to_all(numbers, [](int x) { return x * x; });
    cout << "Squared: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Use function factory
    auto times3 = make_multiplier(3);
    cout << "5 * 3 = " << times3(5) << endl;
    
    // Function composition
    auto square = [](int x) { return x * x; };
    auto add_one = [](int x) { return x + 1; };
    auto square_then_add_one = compose(add_one, square);
    
    cout << "Square 4 then add 1: " << square_then_add_one(4) << endl;  // 17
    
    return 0;
}
```

---

## 🧩 Hands-On Problems (2.25 hours)

**📖 Ready to Apply**: You've read the textbook and reviewed the Python/Java connections above. Now let's put that knowledge to work with hands-on practice that prepares you for the assignments.

### Problem Set 1: Function Pointers and Callbacks (45 minutes)

#### Problem 1.1: Calculator with Function Pointers (15 minutes)
**Create a menu-driven calculator using function pointers:**

```cpp
#include <iostream>
using namespace std;

// TODO: Implement arithmetic functions
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        cout << "Error: Division by zero!" << endl;
        return 0;
    }
    return a / b;
}

int main() {
    // TODO: Create array of function pointers
    double (*operations[])(double, double) = {add, subtract, multiply, divide};
    const char* operation_names[] = {"Add", "Subtract", "Multiply", "Divide"};
    
    double a, b;
    int choice;
    
    cout << "Advanced Calculator" << endl;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    
    cout << "\nSelect operation:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << operation_names[i] << endl;
    }
    cout << "Choice: ";
    cin >> choice;
    
    if (choice >= 1 && choice <= 4) {
        double result = operations[choice - 1](a, b);
        cout << "Result: " << a << " " << operation_names[choice - 1] 
             << " " << b << " = " << result << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }
    
    return 0;
}
```

#### Problem 1.2: Event System with Callbacks (15 minutes)
**Create a simple event system using function pointers:**

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Event handler function type
typedef void (*EventHandler)(const string& message);

// Event handlers
void log_handler(const string& message) {
    cout << "[LOG] " << message << endl;
}

void alert_handler(const string& message) {
    cout << "[ALERT] *** " << message << " ***" << endl;
}

void debug_handler(const string& message) {
    cout << "[DEBUG] " << message << " (timestamp: " << __TIME__ << ")" << endl;
}

class EventSystem {
private:
    vector<EventHandler> handlers;
    
public:
    void add_handler(EventHandler handler) {
        handlers.push_back(handler);
    }
    
    void trigger_event(const string& message) {
        cout << "Triggering event: " << message << endl;
        for (auto handler : handlers) {
            handler(message);
        }
        cout << endl;
    }
};

int main() {
    EventSystem event_system;
    
    // TODO: Add different handlers
    event_system.add_handler(log_handler);
    event_system.add_handler(alert_handler);
    
    // Trigger some events
    event_system.trigger_event("System started");
    event_system.trigger_event("User logged in");
    
    // Add debug handler and trigger more events
    event_system.add_handler(debug_handler);
    event_system.trigger_event("Processing data");
    event_system.trigger_event("System shutdown");
    
    return 0;
}
```

#### Problem 1.3: Command Pattern with Function Pointers (15 minutes)
**Implement a simple command pattern:**

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Command function type
typedef void (*Command)();

// Command implementations
void save_command() {
    cout << "Saving file..." << endl;
}

void load_command() {
    cout << "Loading file..." << endl;
}

void quit_command() {
    cout << "Quitting application..." << endl;
}

void help_command() {
    cout << "Available commands: save, load, help, quit" << endl;
}

class CommandProcessor {
private:
    struct CommandEntry {
        string name;
        Command command;
    };
    
    vector<CommandEntry> commands;
    
public:
    void register_command(const string& name, Command cmd) {
        commands.push_back({name, cmd});
    }
    
    bool execute_command(const string& name) {
        for (const auto& entry : commands) {
            if (entry.name == name) {
                entry.command();
                return true;
            }
        }
        cout << "Unknown command: " << name << endl;
        return false;
    }
    
    void list_commands() {
        cout << "Registered commands: ";
        for (size_t i = 0; i < commands.size(); i++) {
            cout << commands[i].name;
            if (i < commands.size() - 1) cout << ", ";
        }
        cout << endl;
    }
};

int main() {
    CommandProcessor processor;
    
    // TODO: Register commands
    processor.register_command("save", save_command);
    processor.register_command("load", load_command);
    processor.register_command("help", help_command);
    processor.register_command("quit", quit_command);
    
    string input;
    cout << "Command processor started. Type 'help' for commands." << endl;
    
    while (true) {
        cout << "> ";
        cin >> input;
        
        if (input == "quit") {
            quit_command();
            break;
        }
        
        processor.execute_command(input);
    }
    
    return 0;
}
```

### Problem Set 2: Lambda Expressions (60 minutes)

#### Problem 2.1: Data Processing with Lambdas (20 minutes)
**Use lambdas for data filtering and transformation:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    cout << "Original data: ";
    for (int n : data) cout << n << " ";
    cout << endl;
    
    // TODO: Filter even numbers using lambda
    vector<int> evens;
    copy_if(data.begin(), data.end(), back_inserter(evens),
            [](int n) { return n % 2 == 0; });
    
    cout << "Even numbers: ";
    for (int n : evens) cout << n << " ";
    cout << endl;
    
    // TODO: Transform data (square each number)
    vector<int> squares(data.size());
    transform(data.begin(), data.end(), squares.begin(),
              [](int n) { return n * n; });
    
    cout << "Squares: ";
    for (int n : squares) cout << n << " ";
    cout << endl;
    
    // TODO: Find first number greater than 7
    auto it = find_if(data.begin(), data.end(),
                      [](int n) { return n > 7; });
    
    if (it != data.end()) {
        cout << "First number > 7: " << *it << endl;
    }
    
    // TODO: Calculate sum using lambda with accumulate
    int sum = accumulate(data.begin(), data.end(), 0,
                        [](int total, int n) { return total + n; });
    cout << "Sum: " << sum << endl;
    
    return 0;
}
```

#### Problem 2.2: Lambda Captures and State (20 minutes)
**Practice different capture modes:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int multiplier = 3;
    int counter = 0;
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    cout << "Original numbers: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // TODO: Capture by value - multiplier won't change
    auto multiply_by_value = [multiplier](int n) {
        return n * multiplier;
    };
    
    multiplier = 10;  // This won't affect the lambda
    
    cout << "Multiplied by captured value (3): ";
    for (int n : numbers) {
        cout << multiply_by_value(n) << " ";
    }
    cout << endl;
    
    // TODO: Capture by reference - sees current multiplier
    auto multiply_by_reference = [&multiplier](int n) {
        return n * multiplier;
    };
    
    cout << "Multiplied by referenced value (10): ";
    for (int n : numbers) {
        cout << multiply_by_reference(n) << " ";
    }
    cout << endl;
    
    // TODO: Mutable lambda to modify captured value
    auto count_and_process = [counter](int n) mutable {
        counter++;
        cout << "Processing item " << counter << ": " << n << endl;
        return n * 2;
    };
    
    cout << "Counting and doubling:" << endl;
    for (int n : numbers) {
        count_and_process(n);
    }
    cout << "Counter outside lambda: " << counter << endl;  // Still 0
    
    // TODO: Capture by reference to modify external counter
    auto count_externally = [&counter](int n) {
        counter++;
        return n + counter;
    };
    
    cout << "Adding counter value: ";
    for (int n : numbers) {
        cout << count_externally(n) << " ";
    }
    cout << endl;
    cout << "Final counter: " << counter << endl;
    
    return 0;
}
```

#### Problem 2.3: Custom Sorting with Lambdas (20 minutes)
**Use lambdas for complex sorting criteria:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Student {
    string name;
    int age;
    double gpa;
    
    void print() const {
        cout << name << " (age " << age << ", GPA " << gpa << ")";
    }
};

int main() {
    vector<Student> students = {
        {"Alice", 20, 3.8},
        {"Bob", 19, 3.2},
        {"Charlie", 21, 3.9},
        {"Diana", 18, 3.6},
        {"Eve", 20, 3.7}
    };
    
    auto print_students = [](const vector<Student>& students, const string& title) {
        cout << title << ":" << endl;
        for (const auto& student : students) {
            cout << "  ";
            student.print();
            cout << endl;
        }
        cout << endl;
    };
    
    print_students(students, "Original order");
    
    // TODO: Sort by GPA (descending)
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.gpa > b.gpa;  // Higher GPA first
         });
    
    print_students(students, "Sorted by GPA (highest first)");
    
    // TODO: Sort by age, then by name
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             if (a.age != b.age) {
                 return a.age < b.age;  // Younger first
             }
             return a.name < b.name;    // Then alphabetical
         });
    
    print_students(students, "Sorted by age, then name");
    
    // TODO: Custom sort - students with GPA > 3.5, sorted by name
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             bool a_high_gpa = a.gpa > 3.5;
             bool b_high_gpa = b.gpa > 3.5;
             
             if (a_high_gpa != b_high_gpa) {
                 return a_high_gpa > b_high_gpa;  // High GPA students first
             }
             return a.name < b.name;  // Then alphabetical
         });
    
    print_students(students, "High GPA students first, then alphabetical");
    
    return 0;
}
```

### Problem Set 3: Function Objects and Integration (30 minutes)

#### Problem 3.1: State-Preserving Function Objects (15 minutes)
**Create function objects that maintain state:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// TODO: Create a function object that counts calls
class CallCounter {
private:
    mutable int call_count = 0;
    string name;
    
public:
    CallCounter(const string& n) : name{n} {}
    
    void operator()() const {
        call_count++;
        cout << name << " called " << call_count << " times" << endl;
    }
    
    int get_count() const { return call_count; }
};

// TODO: Create a function object for running averages
class RunningAverage {
private:
    mutable double sum = 0.0;
    mutable int count = 0;
    
public:
    double operator()(double value) const {
        sum += value;
        count++;
        return sum / count;
    }
    
    void reset() const {
        sum = 0.0;
        count = 0;
    }
    
    int get_count() const { return count; }
};

// TODO: Create a function object for range checking
class RangeChecker {
private:
    double min_val, max_val;
    mutable int in_range_count = 0;
    mutable int total_count = 0;
    
public:
    RangeChecker(double min_v, double max_v) : min_val{min_v}, max_val{max_v} {}
    
    bool operator()(double value) const {
        total_count++;
        bool in_range = (value >= min_val && value <= max_val);
        if (in_range) {
            in_range_count++;
        }
        return in_range;
    }
    
    double get_percentage() const {
        return total_count > 0 ? (100.0 * in_range_count / total_count) : 0.0;
    }
};

int main() {
    // Test CallCounter
    CallCounter timer{"Timer"};
    timer();
    timer();
    timer();
    cout << "Total calls: " << timer.get_count() << "\n" << endl;
    
    // Test RunningAverage
    RunningAverage avg;
    vector<double> data = {10.0, 20.0, 30.0, 40.0, 50.0};
    
    cout << "Running averages:" << endl;
    for (double value : data) {
        double current_avg = avg(value);
        cout << "Value: " << value << ", Average: " << current_avg << endl;
    }
    cout << "Total values processed: " << avg.get_count() << "\n" << endl;
    
    // Test RangeChecker
    RangeChecker checker{20.0, 40.0};
    vector<double> test_values = {15.0, 25.0, 35.0, 45.0, 55.0, 30.0};
    
    cout << "Range checking (20.0 - 40.0):" << endl;
    for (double value : test_values) {
        bool in_range = checker(value);
        cout << "Value: " << value << " -> " << (in_range ? "IN" : "OUT") << endl;
    }
    cout << "Percentage in range: " << checker.get_percentage() << "%" << endl;
    
    return 0;
}
```

#### Problem 3.2: Generic Algorithm Framework (15 minutes)
**Combine all function concepts in a practical framework:**

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

template<typename T>
class DataProcessor {
private:
    vector<T> data;
    
public:
    void add_data(const T& item) {
        data.push_back(item);
    }
    
    void add_data(const vector<T>& items) {
        data.insert(data.end(), items.begin(), items.end());
    }
    
    // Process data with any callable
    template<typename Func>
    void process_all(Func processor) {
        for (auto& item : data) {
            processor(item);
        }
    }
    
    // Filter data with predicate
    template<typename Predicate>
    vector<T> filter(Predicate pred) {
        vector<T> result;
        copy_if(data.begin(), data.end(), back_inserter(result), pred);
        return result;
    }
    
    // Transform data
    template<typename Transformer>
    auto transform_data(Transformer transformer) -> vector<decltype(transformer(T{}))> {
        vector<decltype(transformer(T{}))> result;
        std::transform(data.begin(), data.end(), back_inserter(result), transformer);
        return result;
    }
    
    // Reduce data to single value
    template<typename Reducer>
    T reduce(T initial, Reducer reducer) {
        return accumulate(data.begin(), data.end(), initial, reducer);
    }
    
    void print() const {
        cout << "Data: ";
        for (const auto& item : data) {
            cout << item << " ";
        }
        cout << endl;
    }
    
    size_t size() const { return data.size(); }
};

int main() {
    DataProcessor<int> processor;
    processor.add_data({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    
    cout << "Original ";
    processor.print();
    
    // TODO: Filter even numbers using lambda
    auto evens = processor.filter([](int n) { return n % 2 == 0; });
    cout << "Even numbers: ";
    for (int n : evens) cout << n << " ";
    cout << endl;
    
    // TODO: Transform to squares using lambda
    auto squares = processor.transform_data([](int n) { return n * n; });
    cout << "Squares: ";
    for (int n : squares) cout << n << " ";
    cout << endl;
    
    // TODO: Calculate sum using lambda
    int sum = processor.reduce(0, [](int total, int n) { return total + n; });
    cout << "Sum: " << sum << endl;
    
    // TODO: Use function object for statistics
    class Statistics {
    public:
        mutable int count = 0;
        mutable int sum = 0;
        
        void operator()(int value) const {
            count++;
            sum += value;
        }
        
        double average() const {
            return count > 0 ? static_cast<double>(sum) / count : 0.0;
        }
    };
    
    Statistics stats;
    processor.process_all(stats);
    cout << "Statistics: count=" << stats.count << ", average=" << stats.average() << endl;
    
    return 0;
}
```

---

## 🔧 Quick Reference & Troubleshooting

### Function Pointer Syntax

```cpp
// Function pointer declaration
return_type (*pointer_name)(parameter_types);

// Examples
int (*func_ptr)(int, int);                    // Points to function taking 2 ints, returning int
double (*math_op)(double, double);            // Mathematical operation
void (*callback)(const string&);             // Callback function

// Assignment and calling
func_ptr = function_name;                     // Assign function
int result = func_ptr(5, 3);                 // Call through pointer
```

### Lambda Expression Syntax

```cpp
// Basic lambda syntax
[capture](parameters) -> return_type { body }

// Examples
[](int x) { return x * 2; }                  // No capture, simple lambda
[x](int y) { return x + y; }                 // Capture x by value
[&x](int y) { x += y; return x; }            // Capture x by reference
[=](int y) { return x + y; }                 // Capture all by value
[&](int y) { x += y; return x; }             // Capture all by reference
```

### Common Function Errors

#### 1. Function Pointer Syntax Mistakes
```cpp
int *func_ptr(int, int);                     // ❌ Function returning int*
int (*func_ptr)(int, int);                   // ✅ Pointer to function

func_ptr = &function_name;                   // ✅ Explicit address
func_ptr = function_name;                    // ✅ Implicit conversion
```

#### 2. Lambda Capture Confusion
```cpp
int x = 10;
auto bad = [x]() mutable { x = 20; };       // ❌ Only modifies copy
auto good = [&x]() { x = 20; };             // ✅ Modifies original
```

#### 3. std::function Performance
```cpp
// Direct lambda - fastest
auto fast = [](int x) { return x * 2; };

// std::function - type erasure overhead
function<int(int)> slower = [](int x) { return x * 2; };
```

---

## ✅ Chapter 9 Success Checklist

### Function Pointer Mastery
- [ ] Can declare and use function pointers correctly
- [ ] Can create arrays of function pointers
- [ ] Can implement callback systems using function pointers
- [ ] Understand when to use function pointers vs alternatives

### Lambda Expression Skills
- [ ] Can write lambdas with different capture modes
- [ ] Can use lambdas with STL algorithms
- [ ] Understand the difference between capture by value and reference
- [ ] Can create stateful lambdas with mutable keyword

### Advanced Function Techniques
- [ ] Can create and use function objects (functors)
- [ ] Can use std::function for type erasure
- [ ] Can implement higher-order functions
- [ ] Can combine different callable types in unified interfaces

---

## 🚀 What's Next?

**Chapter 10: Testing** will cover:
- Unit testing frameworks and methodologies
- Test-driven development (TDD) in C++
- Debugging and coverage analysis
- Professional testing practices

**You've mastered advanced function features!** 🎉 Function pointers, lambdas, and function objects are powerful tools that enable flexible, reusable code design. You now understand how to create callbacks, event systems, and functional programming patterns in C++.

**Key Takeaway**: C++ provides multiple ways to work with functions as first-class entities. Each approach has trade-offs: function pointers are fast but limited, lambdas are convenient and capture-aware, function objects are stateful, and std::function provides type erasure at the cost of some performance.

---

*Remember: Functions are not just code to execute - they're data you can store, pass around, and manipulate. This opens up powerful design patterns and makes your code more flexible and reusable!*