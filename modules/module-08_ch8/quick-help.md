# Chapter 8: Statements - Quick Help Reference

**For Students with Python/Java Background**  
**Quick syntax lookups and common patterns**

---

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

**Python → C++ Translation:**
```python
# Python
if x > 0:
    print("positive")
```
```cpp
// C++
if (x > 0) {
    std::cout << "positive\n";
}
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

**⚠️ Common Mistake**: Forgetting `break` causes fall-through!

---

## Loops Quick Reference

### For Loops

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
```

### While Loops

```cpp
// While loop (same as Python/Java)
while (condition) {
    // statements
}

// Do-while (Java-style, not in Python)
do {
    // statements
} while (condition);
```

### Loop Control

```cpp
// Same as Python/Java
break;     // exit loop
continue;  // skip to next iteration
```

---

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

### Standard Exception Types

```cpp
#include <stdexcept>

std::logic_error          // Programming errors
  std::invalid_argument   // Bad function argument
  std::out_of_range      // Array/vector bounds
  
std::runtime_error       // Runtime problems  
  std::system_error      // System-related
  std::bad_alloc         // Memory allocation failed
```

---

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

---

## Common Patterns

### Input Validation Loop

```cpp
int get_valid_input(int min, int max) {
    int value;
    
    while (true) {
        std::cout << "Enter value (" << min << "-" << max << "): ";
        
        if (std::cin >> value) {
            if (value >= min && value <= max) {
                return value;  // Valid input
            } else {
                std::cout << "Value out of range!" << std::endl;
            }
        } else {
            std::cout << "Invalid input!" << std::endl;
            std::cin.clear();  // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
```

### Menu System Pattern

```cpp
void show_menu() {
    int choice;
    
    do {
        std::cout << "1. Option 1\n2. Option 2\n0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                handle_option1();
                break;
            case 2:
                handle_option2();
                break;
            case 0:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}
```

### Container Processing

```cpp
// Read-only processing
void process_data(const std::vector<int>& data) {
    for (const auto& item : data) {
        std::cout << item << " ";
    }
}

// Modifying elements
void double_values(std::vector<int>& data) {
    for (auto& item : data) {
        item *= 2;
    }
}

// Traditional indexing when you need the index
void process_with_index(const std::vector<int>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "data[" << i << "] = " << data[i] << std::endl;
    }
}
```

---

## Python → C++ Quick Translations

### Dictionary to Switch

```python
# Python dictionary approach
grade_map = {
    'A': 4.0,
    'B': 3.0,
    'C': 2.0,
    'D': 1.0,
    'F': 0.0
}
gpa = grade_map.get(letter_grade, 0.0)
```

```cpp
// C++ switch approach
double get_gpa(char letter_grade) {
    switch (letter_grade) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        case 'F': return 0.0;
        default: return 0.0;
    }
}
```

### List Comprehension to Range-For

```python
# Python list comprehension
doubled = [x * 2 for x in numbers if x > 0]
```

```cpp
// C++ equivalent
std::vector<int> doubled;
for (const auto& x : numbers) {
    if (x > 0) {
        doubled.push_back(x * 2);
    }
}
```

### Exception Handling

```python
# Python
try:
    result = risky_operation()
except ValueError as e:
    print(f"Bad value: {e}")
except Exception as e:
    print(f"Error: {e}")
```

```cpp
// C++
try {
    auto result = risky_operation();
} catch (const std::invalid_argument& e) {
    std::cout << "Bad value: " << e.what() << std::endl;
} catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
}
```

---

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

### 4. Overusing Exceptions

```cpp
// ❌ Wrong - exceptions for control flow
int find_item(const std::vector<int>& vec, int target) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            return i;
        }
    }
    throw std::runtime_error("Item not found");  // Too heavy!
}

// ✅ Better - return optional or special value
int find_item(const std::vector<int>& vec, int target) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            return static_cast<int>(i);
        }
    }
    return -1;  // Indicates not found
}
```

---

## Performance Tips

### Loop Performance

```cpp
// ✅ Prefer pre-increment
for (int i = 0; i < n; ++i) {  // Not i++
    // ...
}

// ✅ Cache size() calls
const size_t size = vec.size();
for (size_t i = 0; i < size; ++i) {
    // ...
}

// ✅ Use range-for when possible (cleaner and often faster)
for (const auto& item : container) {
    // ...
}
```

### Exception Performance

- Exceptions are expensive - use for truly exceptional cases
- Use `noexcept` when functions won't throw:

```cpp
void safe_function() noexcept {
    // Promise this won't throw
}
```

---

## Debugging Tips

### Print Debugging

```cpp
#include <iostream>
#include <typeinfo>

// Print variable type
auto x = some_expression;
std::cout << "Type: " << typeid(x).name() << std::endl;

// Print with line info
#define DEBUG_PRINT(x) std::cout << __FILE__ << ":" << __LINE__ << " " << #x << " = " << x << std::endl

int value = 42;
DEBUG_PRINT(value);  // Prints: file.cpp:123 value = 42
```

### Exception Information

```cpp
try {
    // risky code
} catch (const std::exception& e) {
    std::cout << "Exception type: " << typeid(e).name() << std::endl;
    std::cout << "What: " << e.what() << std::endl;
}
```

---

## Quick Compilation Commands

```bash
# Basic compilation
g++ -std=c++17 -Wall -Wextra program.cpp -o program

# Debug build
g++ -std=c++17 -Wall -Wextra -g -O0 program.cpp -o program

# Release build  
g++ -std=c++17 -Wall -Wextra -O2 -DNDEBUG program.cpp -o program
```

---

## Need More Help?

1. **Compiler errors**: Read from bottom up, look for the actual error location
2. **Runtime crashes**: Use debugger (`gdb`) or add print statements
3. **Memory issues**: Use valgrind (Linux/Mac) or address sanitizer
4. **Best practices**: Refer to C++ Core Guidelines
5. **Reference**: [cppreference.com](https://cppreference.com) for detailed documentation