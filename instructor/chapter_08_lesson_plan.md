# Chapter 8: Statements - Lesson Plan

**Target Audience**: Students with Python/Java background (NOT hardcore CS majors)  
**Time Budget**: 2.5 hours maximum  
**Prerequisites**: Chapters 1-7 (basic programming, types, references, object lifecycle, polymorphism, templates, expressions)  

## Development Environment Setup
**Continue using your chosen workflow from previous chapters:**
- **Option A**: Docker + Command Line
- **Option B**: VS Code + Docker (great for exception flow debugging)
- **Option C**: VS Code + Local Compiler

**For Chapter 8's control flow, step-through debugging shows execution paths clearly!**

---

## Learning Objectives

By the end of this chapter, students will be able to:
1. Use C++ control flow statements (if/else, switch, loops) with proper syntax
2. Handle exceptions using try/catch blocks and throw statements
3. Apply RAII principles to resource management in control structures
4. Write robust programs using appropriate error handling patterns
5. Compare and contrast C++ control flow with Python/Java equivalents

---

## Session Structure Overview

**Total Time: 2.5 hours (150 minutes)**

1. **Introduction & Motivation** (10 minutes)
2. **Conditional Statements** (30 minutes)
3. **Loop Statements** (35 minutes)
4. **Exception Handling** (45 minutes)
5. **Advanced Topics & Best Practices** (25 minutes)
6. **Wrap-up & Review** (5 minutes)

---

## 1. Introduction & Motivation (10 minutes)

### Why Control Flow Matters in C++

Unlike Python and Java, C++ gives you more direct control over:
- **Memory management** during loops and conditions
- **Resource cleanup** through RAII
- **Performance optimization** through compile-time decisions
- **Type safety** with stronger compile-time checking

### Key Differences from Python/Java

| Aspect | Python/Java | C++ |
|--------|------------|-----|
| Braces | Optional (Python) / Required (Java) | Always required for multi-statement blocks |
| Variable scope | Function/block level | Block level with RAII cleanup |
| Exception handling | Ubiquitous | More selective, performance-focused |
| Switch statements | Limited (Python dict) / Java switch | Powerful with fall-through control |

---

## 2. Conditional Statements (30 minutes)

### 2.1 If Statements (10 minutes)

**Familiar Territory**: The basic syntax is nearly identical to Java.

```cpp
// Basic if statement - just like Java
if (condition) {
    // statements
}

// C++-specific: Initialization in if statement (C++17)
if (auto result = expensive_calculation(); result > threshold) {
    use_result(result);
}
// result goes out of scope here
```

**Python → C++ Translation:**
```python
# Python
if x > 0:
    print("Positive")
elif x < 0:
    print("Negative")
else:
    print("Zero")
```

```cpp
// C++
if (x > 0) {
    std::cout << "Positive\n";
} else if (x < 0) {
    std::cout << "Negative\n";
} else {
    std::cout << "Zero\n";
}
```

**Key Differences:**
- Always use braces `{}` for safety
- Boolean conditions don't auto-convert everything (like Python)
- Parentheses around condition are required

### 2.2 Switch Statements (20 minutes)

**Major Upgrade from Python**: C++ switch is much more powerful than Python's match or dictionary approaches.

```cpp
// Basic switch - similar to Java
switch (value) {
    case 1:
        std::cout << "One\n";
        break;  // Don't forget break!
    case 2:
        std::cout << "Two\n";
        break;
    default:
        std::cout << "Other\n";
        break;
}
```

**Fall-through behavior** (different from Python, similar to Java):
```cpp
switch (grade) {
    case 'A':
    case 'B':
        std::cout << "Good grade\n";
        break;  // Without this, continues to next case
    case 'C':
        std::cout << "Average grade\n";
        break;
    case 'D':
    case 'F':
        std::cout << "Poor grade\n";
        break;
}
```

**C++17 Enhancement - Switch with initialization:**
```cpp
switch (auto result = get_status(); result) {
    case Status::SUCCESS:
        handle_success();
        break;
    case Status::ERROR:
        handle_error();
        break;
}
```

**Best Practices:**
- Always include `break` statements (unless intentional fall-through)
- Use `default` case for completeness
- Consider `enum class` for better type safety

---

## 3. Loop Statements (35 minutes)

### 3.1 For Loops (15 minutes)

**C-style for loops** (different from Python, similar to Java):
```cpp
// Traditional for loop
for (int i = 0; i < 10; ++i) {
    std::cout << i << " ";
}
```

**Range-based for loops** (C++11) - similar to Python's for-in:
```cpp
// Python: for item in container:
// C++:
std::vector<int> numbers = {1, 2, 3, 4, 5};
for (const auto& num : numbers) {
    std::cout << num << " ";
}

// Modifying elements
for (auto& num : numbers) {
    num *= 2;  // Double each number
}
```

**Key Differences from Python/Java:**
- Use `++i` instead of `i++` for efficiency (good habit)
- `const auto&` for read-only access to avoid copies
- `auto&` for modifying elements

### 3.2 While and Do-While Loops (10 minutes)

**While loops** - same as Python/Java:
```cpp
int count = 0;
while (count < 10) {
    std::cout << count << " ";
    ++count;
}
```

**Do-while loops** - available in C++ and Java, not Python:
```cpp
int input;
do {
    std::cout << "Enter a positive number: ";
    std::cin >> input;
} while (input <= 0);
```

### 3.3 Loop Control (10 minutes)

**Break and Continue** - same as Python/Java:
```cpp
for (int i = 0; i < 100; ++i) {
    if (i % 2 == 0) {
        continue;  // Skip even numbers
    }
    if (i > 50) {
        break;     // Exit loop
    }
    std::cout << i << " ";
}
```

**RAII in Loops** - unique to C++:
```cpp
for (int i = 0; i < files.size(); ++i) {
    std::ifstream file(files[i]);  // RAII: file opens
    // ... process file ...
}  // RAII: file automatically closes when out of scope
```

---

## 4. Exception Handling (45 minutes)

### 4.1 Exception Basics (15 minutes)

**Philosophy Difference:**
- **Python**: Exceptions are common and expected ("EAFP" - Easier to Ask for Forgiveness than Permission)
- **Java**: Checked exceptions force handling
- **C++**: Exceptions for truly exceptional cases, performance matters

**Basic Syntax** (similar to Java, different from Python):
```cpp
try {
    // Code that might throw
    risky_operation();
} catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
} catch (...) {  // Catch all
    std::cout << "Unknown error occurred" << std::endl;
}
```

**Throwing Exceptions:**
```cpp
void divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}
```

### 4.2 Standard Exception Types (15 minutes)

**Common Standard Exceptions:**
```cpp
#include <stdexcept>

// Logic errors (programming mistakes)
std::logic_error        // Base class
std::invalid_argument   // Invalid argument passed
std::out_of_range      // Array/vector index out of bounds

// Runtime errors (external conditions)
std::runtime_error     // Base class
std::system_error      // System-related errors
std::bad_alloc         // Memory allocation failure
```

**Example Usage:**
```cpp
class BankAccount {
    private:
        double balance;
    
    public:
        void withdraw(double amount) {
            if (amount < 0) {
                throw std::invalid_argument("Amount cannot be negative");
            }
            if (amount > balance) {
                throw std::runtime_error("Insufficient funds");
            }
            balance -= amount;
        }
};
```

### 4.3 RAII and Exception Safety (15 minutes)

**Critical C++ Concept**: RAII ensures cleanup even during exceptions.

```cpp
void process_file(const std::string& filename) {
    std::ifstream file(filename);  // RAII: opens file
    
    if (!file) {
        throw std::runtime_error("Cannot open file");
    }
    
    std::vector<std::string> data;
    std::string line;
    
    // If exception occurs here, file still closes automatically
    while (std::getline(file, line)) {
        if (line.empty()) {
            throw std::invalid_argument("Empty line not allowed");
        }
        data.push_back(line);
    }
    
    // File automatically closes when going out of scope
    // Even if exception was thrown above
}
```

**Smart Pointers with Exceptions:**
```cpp
void risky_operation() {
    auto ptr = std::make_unique<ExpensiveResource>();
    
    // Even if this throws, ptr is automatically cleaned up
    dangerous_function();
    
    // No memory leak!
}
```

---

## 5. Advanced Topics & Best Practices (25 minutes)

### 5.1 Exception Specifications (10 minutes)

**Modern C++ Approach:**
```cpp
// C++11 and later: noexcept specifier
void safe_function() noexcept {
    // Promise this won't throw
}

void might_throw() {
    // May throw exceptions (default)
}
```

**Benefits of noexcept:**
- Enables compiler optimizations
- Required for move constructors to be used in containers
- Documents your intent

### 5.2 Error Handling Patterns (15 minutes)

**When to Use Exceptions vs. Error Codes:**

```cpp
// Good for exceptions: Truly exceptional cases
class FileReader {
public:
    std::string read_file(const std::string& path) {
        std::ifstream file(path);
        if (!file) {
            throw std::runtime_error("Cannot open file: " + path);
        }
        // ... read file ...
    }
};

// Good for error codes: Expected failure cases
enum class ValidationResult {
    SUCCESS,
    INVALID_EMAIL,
    PASSWORD_TOO_SHORT,
    USERNAME_TAKEN
};

ValidationResult validate_user_input(const UserData& data);
```

**Resource Management Pattern:**
```cpp
// RAII ensures cleanup
class DatabaseConnection {
    // Constructor acquires resource
    // Destructor releases resource
public:
    DatabaseConnection(const std::string& connection_string);
    ~DatabaseConnection();  // Always called, even during exceptions
    
    // Delete copy to prevent accidental copies
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    
    // Enable move semantics
    DatabaseConnection(DatabaseConnection&&) = default;
    DatabaseConnection& operator=(DatabaseConnection&&) = default;
};
```

---

## 6. Wrap-up & Review (5 minutes)

### Key Takeaways for Python/Java Developers

1. **Syntax Similarities**: Control flow syntax is very similar to Java
2. **RAII is King**: Unlike Python/Java, C++ automatically manages resources through destructors
3. **Exceptions are Heavier**: Use exceptions for truly exceptional cases, not control flow
4. **Scope Matters**: Variable scope and lifetime are more explicit in C++
5. **Performance Awareness**: Every control structure has performance implications

### Common Pitfalls to Avoid

1. **Forgetting break in switch statements**
2. **Not using RAII for resource management**
3. **Overusing exceptions (coming from Python)**
4. **Forgetting const correctness in range-based for loops**
5. **Not handling all exception types**

### Next Steps

- Practice with the provided exercises
- Focus on RAII patterns in your own code
- Experiment with different exception handling strategies
- Compare C++ solutions with your Python/Java equivalents

---

## Additional Resources

- **Reference**: [cppreference.com - Statements](https://en.cppreference.com/w/cpp/language/statements)
- **RAII**: [RAII on cppreference](https://en.cppreference.com/w/cpp/language/raii)
- **Exception Safety**: [Exception Safety Guarantees](https://en.cppreference.com/w/cpp/language/exceptions)
- **Best Practices**: Modern C++ guidelines on exception handling

## Assessment Strategy

Students will be evaluated on:
1. **Correct syntax** usage of control structures
2. **Appropriate exception handling** for different scenarios
3. **RAII implementation** in resource management
4. **Code organization** and readability
5. **Performance considerations** in control flow design