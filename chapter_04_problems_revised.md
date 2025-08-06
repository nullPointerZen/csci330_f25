# Chapter 4: Object Lifecycle - Problem Sets

## Instructions
- Complete these problems after reading Chapter 4 and working through the lesson
- Each problem builds on previous concepts
- **Time expectation**: 2.25 hours total for all three problem sets
- Test all programs thoroughly and check for memory leaks

---

## Problem Set 1: Basic Constructors and Destructors (45 minutes)

### Problem 1.1: Simple Bank Account
**Objective**: Practice basic constructor and destructor syntax

Create a `BankAccount` class with:
- A constructor that takes an initial balance
- A destructor that prints a goodbye message
- A method to display the current balance

**Template to get you started**:
```cpp
#include <cstdio>

class BankAccount {
public:
    BankAccount(double initial_balance) {
        // Initialize balance here
        printf("Account created with balance: $%.2f\n", balance);
    }
    
    ~BankAccount() {
        // Print goodbye message here
    }
    
    void display_balance() {
        printf("Current balance: $%.2f\n", balance);
    }
    
private:
    double balance;
};

int main() {
    BankAccount account{100.50};
    account.display_balance();
    return 0;
} // Destructor called here automatically
```

**Python/Java Note**: Unlike Python's `__init__` or Java constructors, C++ constructors don't have a return type.

### Problem 1.2: Multiple Constructors
**Objective**: Practice constructor overloading

Extend your `BankAccount` class to have:
1. A default constructor (starts with $0.00)
2. A constructor that takes an initial balance
3. A constructor that takes initial balance and account holder name

Test all three constructors in your main function.

### Problem 1.3: Trace the Lifecycle
**Objective**: Understand when constructors and destructors are called

Create this program and predict when each constructor/destructor will be called:
```cpp
#include <cstdio>

class SimpleCounter {
public:
    SimpleCounter(int id) : id{id} {
        printf("Constructor: Counter %d created\n", id);
    }
    
    ~SimpleCounter() {
        printf("Destructor: Counter %d destroyed\n", id);
    }
    
private:
    int id;
};

int main() {
    printf("=== Starting main ===\n");
    SimpleCounter counter1{1};
    
    {
        printf("=== Entering inner scope ===\n");
        SimpleCounter counter2{2};
        printf("=== About to leave inner scope ===\n");
    }
    
    printf("=== About to leave main ===\n");
    return 0;
}
```

Run the program and verify your predictions!

---

## Problem Set 2: RAII and Resource Management (60 minutes)

### Problem 2.1: File Logger Class
**Objective**: Implement RAII for file handling

Create a `FileLogger` class that:
- Opens a file in the constructor
- Provides a method to write log messages
- Closes the file automatically in the destructor

**Template**:
```cpp
#include <cstdio>

class FileLogger {
public:
    FileLogger(const char* filename) {
        file = fopen(filename, "w");
        if (file) {
            printf("Log file '%s' opened successfully\n", filename);
        } else {
            printf("Error: Could not open log file '%s'\n", filename);
        }
    }
    
    ~FileLogger() {
        if (file) {
            printf("Closing log file\n");
            fclose(file);
        }
    }
    
    void log_message(const char* message) {
        if (file) {
            fprintf(file, "LOG: %s\n", message);
            fflush(file); // Ensure message is written immediately
        }
    }
    
private:
    FILE* file;
};

int main() {
    FileLogger logger{"test.log"};
    logger.log_message("Application started");
    logger.log_message("Processing data");
    logger.log_message("Application ending");
    
    // File automatically closed when logger goes out of scope
    return 0;
}
```

Test your program and verify that "test.log" contains your messages.

### Problem 2.2: Array Manager
**Objective**: Practice RAII with dynamic memory

Create an `IntArray` class that:
- Allocates an array of integers in the constructor
- Provides methods to set and get values
- Automatically deallocates memory in the destructor

**Template**:
```cpp
#include <cstdio>

class IntArray {
public:
    IntArray(int size) : size{size} {
        data = new int[size];
        printf("Array of %d integers allocated\n", size);
        
        // Initialize all elements to 0
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
    
    ~IntArray() {
        delete[] data;
        printf("Array memory deallocated\n");
    }
    
    void set(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }
    
    int get(int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return -1; // Error value
    }
    
    void print() {
        printf("Array contents: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }
    
private:
    int* data;
    int size;
};

int main() {
    IntArray arr{5};
    
    arr.set(0, 10);
    arr.set(1, 20);
    arr.set(2, 30);
    
    arr.print();
    
    // Memory automatically freed when arr goes out of scope
    return 0;
}
```

### Problem 2.3: Fix the Memory Leak
**Objective**: Identify and fix resource management problems

This program has a memory leak. Find and fix it:
```cpp
#include <cstdio>

class StringBuffer {
public:
    StringBuffer(int capacity) {
        buffer = new char[capacity];
        this->capacity = capacity;
        buffer[0] = '\0'; // Empty string
        printf("StringBuffer created with capacity %d\n", capacity);
    }
    
    void append(const char* text) {
        // Simplified append - doesn't check capacity
        sprintf(buffer, "%s%s", buffer, text);
    }
    
    void print() {
        printf("Buffer contents: %s\n", buffer);
    }
    
private:
    char* buffer;
    int capacity;
};

int main() {
    StringBuffer* buf = new StringBuffer(100);
    buf->append("Hello ");
    buf->append("World!");
    buf->print();
    
    // What's missing here?
    
    return 0;
}
```

**Hint**: What should happen to objects created with `new`?

---

## Problem Set 3: Advanced Object Lifecycle (40 minutes)

### Problem 3.1: Stack vs Heap Objects
**Objective**: Compare automatic vs manual object management

Complete this program that creates the same class both on the stack and heap:
```cpp
#include <cstdio>

class Timer {
public:
    Timer(const char* name) : name{name} {
        printf("Timer '%s' started\n", name);
    }
    
    ~Timer() {
        printf("Timer '%s' finished\n", name);
    }
    
    void tick() {
        printf("Timer '%s' tick\n", name);
    }
    
private:
    const char* name;
};

int main() {
    printf("=== Creating stack object ===\n");
    Timer stack_timer{"StackTimer"};
    stack_timer.tick();
    
    printf("\n=== Creating heap object ===\n");
    Timer* heap_timer = new Timer{"HeapTimer"};
    heap_timer->tick();
    
    // TODO: Clean up heap object properly
    
    printf("\n=== About to exit main ===\n");
    return 0;
}
```

Complete the program and observe the difference in when destructors are called.

### Problem 3.2: Constructor Error Handling
**Objective**: Handle constructor failures gracefully

Create a `SafeFileLogger` that handles file opening errors:
```cpp
#include <cstdio>

class SafeFileLogger {
public:
    SafeFileLogger(const char* filename) {
        file = fopen(filename, "w");
        if (file) {
            printf("Successfully opened log file '%s'\n", filename);
            is_valid = true;
        } else {
            printf("Failed to open log file '%s'\n", filename);
            is_valid = false;
        }
    }
    
    ~SafeFileLogger() {
        if (file) {
            printf("Closing log file\n");
            fclose(file);
        }
    }
    
    bool is_open() const {
        return is_valid;
    }
    
    void log_message(const char* message) {
        if (is_valid && file) {
            fprintf(file, "LOG: %s\n", message);
            fflush(file);
        } else {
            printf("Cannot log: file not open\n");
        }
    }
    
private:
    FILE* file;
    bool is_valid;
};

int main() {
    // Test with a valid filename
    SafeFileLogger logger1{"good.log"};
    if (logger1.is_open()) {
        logger1.log_message("This should work");
    }
    
    // Test with an invalid filename (like a directory that doesn't exist)
    SafeFileLogger logger2{"/nonexistent/bad.log"};
    if (logger2.is_open()) {
        logger2.log_message("This won't be reached");
    } else {
        printf("Logger2 failed to open, but program continues safely\n");
    }
    
    return 0;
}
```

### Problem 3.3: Complete Resource Manager
**Objective**: Bring everything together

Create a complete `ResourceManager` class that:
1. Takes a resource name in the constructor
2. Simulates acquiring the resource (print message)
3. Provides methods to use the resource
4. Releases the resource in the destructor
5. Handles both stack and heap allocation

Test it thoroughly with both allocation methods.

---

## Submission Guidelines

**For each problem set**:
1. Include source code with comments explaining the lifecycle
2. Show sample output demonstrating constructor/destructor calls
3. For memory problems, indicate how you verified no leaks
4. Note any insights about C++ vs Python/Java object management

**File organization**:
```
chapter04_solutions/
├── problem_set_1/
│   ├── problem_1_1.cpp
│   ├── problem_1_2.cpp
│   └── problem_1_3.cpp
├── problem_set_2/
│   ├── problem_2_1.cpp
│   ├── problem_2_2.cpp
│   └── problem_2_3.cpp
├── problem_set_3/
│   ├── problem_3_1.cpp
│   ├── problem_3_2.cpp
│   └── problem_3_3.cpp
└── README.md (with compilation notes and insights)
```

**Memory leak checking** (if available):
```bash
# Linux/Mac with valgrind
valgrind --leak-check=full ./your_program

# Or just careful code review for new/delete pairs
```

**Expected time commitment**: 2.25 hours total. If you're spending much longer, focus on understanding the concepts rather than perfect implementation.