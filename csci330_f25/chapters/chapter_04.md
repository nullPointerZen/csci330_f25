# Chapter 4: Object Lifecycle

Welcome to object lifecycle management! This chapter covers one of C++'s most powerful features: deterministic construction and destruction. You'll learn RAII (Resource Acquisition Is Initialization), which makes C++ programs safer and more predictable than garbage-collected languages.

## 📖 How This Chapter Works

**🔄 Learning Sequence (IMPORTANT!):**
1. **📚 FIRST**: Read Textbook Chapter 4 "Object Lifecycle" (2-3 hours)
2. **🔍 SECOND**: Work through the lecture notes below for Python/Java context and hands-on practice (7-8 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.5 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 4 "Object Lifecycle" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Master** the C++ object lifecycle (construction, use, destruction)
2. **Write** constructors to initialize objects with default and custom values
3. **Implement** destructors to clean up object resources
4. **Apply** RAII principles for automatic resource management
5. **Use** dynamic memory allocation with new/delete safely
6. **Debug** lifecycle issues using VS Code's debugging tools

**⏱️ Time Budget:**
- **📚 Textbook Reading: 2-3 hours** (Chapter 4: "Object Lifecycle" - REQUIRED FIRST)
- **🛠️ Setup: Included in Chapter 1** (VS Code + debugger setup)
- **💻 Hands-on Work: 7-8 hours** (lecture notes + assignments)

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](../DEVELOPMENT_SETUP.md). All debugging examples use VS Code + Docker.

---

# Lecture Notes

## 🔄 Core Concepts: Object Lifecycle

**📖 Bridge to Textbook**: Now that you've read about constructors, destructors, and RAII in Chapter 4, let's connect those concepts to Python/Java patterns.

### 1. The C++ Object Lifecycle

**Every C++ object follows this pattern: Construction → Use → Destruction**

```cpp
{
    BankAccount account{100.0};  // 1. Construction
    account.display_balance();   // 2. Use
    account.deposit(50.0);       // 2. More use
}  // 3. Destruction (automatic for stack objects)
```

| Language | Construction | Destruction | When Destroyed |
|----------|-------------|-------------|----------------|
| **C++** | Constructor called | Destructor called | Scope exit/delete |
| **Python** | `__init__` called | `__del__` maybe called | Garbage collection |
| **Java** | Constructor called | `finalize()` maybe called | Garbage collection |

**Key Difference**: C++ destruction is **deterministic** - you know exactly when it happens!

### 2. Constructors: Setting Up Objects

**Constructors initialize objects when they're created:**

```cpp
class BankAccount {
public:
    // Default constructor
    BankAccount() : balance{0.0} {
        printf("Account created with $0.00\n");
    }
    
    // Parameterized constructor
    BankAccount(double initial) : balance{initial} {
        printf("Account created with $%.2f\n", balance);
    }
    
private:
    double balance;
};

// Usage
BankAccount account1;        // Calls default constructor
BankAccount account2{100.0}; // Calls parameterized constructor
```

| Type | C++ | Python | Java |
|------|-----|--------|------|
| **Default** | `BankAccount() {}` | `def __init__(self):` | `public BankAccount() {}` |
| **Parameterized** | `BankAccount(double amt) {}` | `def __init__(self, amt):` | `public BankAccount(double amt) {}` |
| **Initialization List** | `: balance{amt}` | `self.balance = amt` | `this.balance = amt;` |

### 3. Destructors: Cleaning Up Objects

**Destructors clean up when objects are destroyed:**

```cpp
class FileLogger {
public:
    FileLogger(const char* filename) {
        file = fopen(filename, "w");
        printf("File opened: %s\n", filename);
    }
    
    ~FileLogger() {  // Destructor - note the ~
        if (file) {
            fclose(file);
            printf("File closed\n");
        }
    }
    
private:
    FILE* file;
};
```

**Python/Java Bridge**: C++ destructors are like Python's `with` statement or Java's try-with-resources, but automatic!

### 4. RAII: Resource Management Made Safe

**RAII = Resource Acquisition Is Initialization**

The pattern: Acquire resources in constructor, release in destructor.

```cpp
class SafeArray {
public:
    SafeArray(int size) : size_{size} {
        data_ = new int[size_];     // Acquire resource
        printf("Array allocated\n");
    }
    
    ~SafeArray() {
        delete[] data_;             // Release resource
        printf("Array deallocated\n");
    }
    
    int& operator[](int index) { return data_[index]; }
    
private:
    int* data_;
    int size_;
};

// Usage - automatic cleanup!
{
    SafeArray arr{100};
    arr[0] = 42;
    // Destructor automatically called here - no memory leak!
}
```

**Key Insight**: RAII makes resource management automatic and exception-safe.

### 5. Storage Duration: Where Objects Live

**C++ has three main storage durations:**

#### Automatic Storage (Stack)
```cpp
void function() {
    BankAccount account{100.0};  // Automatic storage
    // Destroyed when leaving scope
}
```

#### Static Storage (Global/Static)
```cpp
BankAccount global_account{500.0};      // Global - entire program lifetime

void function() {
    static BankAccount static_account{200.0};  // Static local - survives function calls
}
```

#### Dynamic Storage (Heap)
```cpp
BankAccount* heap_account = new BankAccount{100.0};  // Manual lifetime management
// Must call delete heap_account;
```

| Storage Type | When Created | When Destroyed | Use Cases |
|--------------|--------------|----------------|-----------|
| **Automatic** | Entering scope | Leaving scope | Most objects |
| **Static** | First access | Program end | Singletons, caches |
| **Dynamic** | `new` called | `delete` called | Variable lifetime needs |

### 6. Smart Pointers: Modern C++ Memory Management

**Smart pointers provide automatic memory management:**

```cpp
#include <memory>

// unique_ptr - single ownership
std::unique_ptr<BankAccount> account = std::make_unique<BankAccount>(100.0);
// No delete needed - automatic cleanup!

// shared_ptr - shared ownership
std::shared_ptr<BankAccount> shared1 = std::make_shared<BankAccount>(200.0);
std::shared_ptr<BankAccount> shared2 = shared1;  // Both point to same object
// Object destroyed when last shared_ptr is destroyed
```

**Modern C++ Rule**: Prefer smart pointers over raw `new/delete`.

## 🧩 Hands-On Practice Problems

### Problem Set 1: Basic Constructors and Destructors (45 minutes)

#### Problem 1.1: Bank Account Lifecycle
Create a complete bank account with lifecycle tracking:

```cpp
#include <cstdio>

class BankAccount {
public:
    BankAccount(double initial_balance) : balance{initial_balance} {
        printf("Account created with balance: $%.2f\n", balance);
    }
    
    ~BankAccount() {
        printf("Account destroyed. Final balance: $%.2f\n", balance);
    }
    
    void display_balance() const {
        printf("Current balance: $%.2f\n", balance);
    }
    
    void deposit(double amount) {
        balance += amount;
        printf("Deposited $%.2f\n", amount);
    }
    
private:
    double balance;
};

int main() {
    printf("=== Creating account ===\n");
    BankAccount account{100.50};
    
    printf("=== Using account ===\n");
    account.display_balance();
    account.deposit(25.00);
    account.display_balance();
    
    printf("=== About to exit main ===\n");
    return 0;
}
```

**Expected Output:**
```
=== Creating account ===
Account created with balance: $100.50
=== Using account ===
Current balance: $100.50
Deposited $25.00
Current balance: $125.50
=== About to exit main ===
Account destroyed. Final balance: $125.50
```

#### Problem 1.2: Multiple Constructors
Practice constructor overloading:

```cpp
class Student {
public:
    // Default constructor
    Student() : name{"Unknown"}, age{0}, gpa{0.0} {
        printf("Default student created\n");
    }
    
    // Name-only constructor
    Student(const char* student_name) : name{student_name}, age{0}, gpa{0.0} {
        printf("Student '%s' created\n", name);
    }
    
    // Full constructor
    Student(const char* student_name, int student_age, double student_gpa) 
        : name{student_name}, age{student_age}, gpa{student_gpa} {
        printf("Student '%s' (age %d, GPA %.2f) created\n", name, age, gpa);
    }
    
    ~Student() {
        printf("Student '%s' destroyed\n", name);
    }
    
    void display() const {
        printf("Student: %s, Age: %d, GPA: %.2f\n", name, age, gpa);
    }
    
private:
    const char* name;
    int age;
    double gpa;
};

int main() {
    Student s1;                          // Default
    Student s2{"Alice"};                 // Name only
    Student s3{"Bob", 20, 3.7};         // Full info
    
    s1.display();
    s2.display();
    s3.display();
    
    return 0;
}
```

### Problem Set 2: RAII and Resource Management (60 minutes)

#### Problem 2.1: File Logger with RAII
Implement automatic file management:

```cpp
#include <cstdio>

class FileLogger {
public:
    FileLogger(const char* filename) : filename_{filename} {
        file_ = fopen(filename_, "w");
        if (file_) {
            printf("Log file '%s' opened successfully\n", filename_);
        } else {
            printf("Error: Could not open log file '%s'\n", filename_);
        }
    }
    
    ~FileLogger() {
        if (file_) {
            printf("Closing log file '%s'\n", filename_);
            fclose(file_);
        }
    }
    
    void log_message(const char* message) {
        if (file_) {
            fprintf(file_, "LOG: %s\n", message);
            fflush(file_);  // Ensure immediate write
            printf("Logged: %s\n", message);
        }
    }
    
    bool is_open() const {
        return file_ != nullptr;
    }
    
private:
    FILE* file_;
    const char* filename_;
};

int main() {
    printf("=== Creating logger ===\n");
    FileLogger logger{"test.log"};
    
    if (logger.is_open()) {
        printf("=== Logging messages ===\n");
        logger.log_message("Application started");
        logger.log_message("Processing data");
        logger.log_message("Application ending");
    }
    
    printf("=== About to exit ===\n");
    return 0;
    // File automatically closed here!
}
```

#### Problem 2.2: Dynamic Array Manager
Practice RAII with dynamic memory:

```cpp
#include <cstdio>

class IntArray {
public:
    IntArray(int size) : size_{size} {
        data_ = new int[size_];
        printf("Array of %d integers allocated\n", size_);
        
        // Initialize to zero
        for (int i = 0; i < size_; i++) {
            data_[i] = 0;
        }
    }
    
    ~IntArray() {
        delete[] data_;
        printf("Array memory deallocated\n");
    }
    
    void set(int index, int value) {
        if (index >= 0 && index < size_) {
            data_[index] = value;
        } else {
            printf("Index %d out of bounds!\n", index);
        }
    }
    
    int get(int index) const {
        if (index >= 0 && index < size_) {
            return data_[index];
        }
        return -1;  // Error value
    }
    
    void print() const {
        printf("Array contents: ");
        for (int i = 0; i < size_; i++) {
            printf("%d ", data_[i]);
        }
        printf("\n");
    }
    
private:
    int* data_;
    int size_;
};

int main() {
    printf("=== Creating array ===\n");
    IntArray arr{5};
    
    printf("=== Using array ===\n");
    arr.set(0, 10);
    arr.set(1, 20);
    arr.set(2, 30);
    arr.print();
    
    printf("=== About to exit ===\n");
    return 0;
    // Memory automatically freed here!
}
```

---

# Assignments

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 4 "Object Lifecycle"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Assignment Structure
- **Core Assignment 1**: Banking System with RAII (2 hours) - REQUIRED
- **Core Assignment 2**: Resource Management Framework (2 hours) - REQUIRED
- **Total Time**: 4 hours for both core assignments

## 🎯 Core Assignment 1: Banking System with RAII (2 hours)

### Part A: Account Hierarchy and Lifecycle (60 minutes)
**Objective**: Master constructor/destructor patterns through a complete banking system

Create a program called `banking_system.cpp` that implements:

**Base Account Class:**
1. Create a `BankAccount` base class with:
   - Multiple constructors (default, balance, full account info)
   - Virtual destructor with logging
   - Account number generation (static counter)
   - Balance management with validation

**Specialized Account Types:**
2. Implement derived classes:
   - `SavingsAccount` (with interest rate)
   - `CheckingAccount` (with overdraft protection)
   - `BusinessAccount` (with transaction limits)

**Lifecycle Demonstration:**
3. Create accounts using different constructors
4. Show object creation/destruction order in nested scopes
5. Track total accounts created/destroyed (static members)

### Part B: Transaction Management and RAII (60 minutes)
**Objective**: Apply RAII principles for transaction safety and logging

Extend your banking system with automatic resource management:

**Transaction Logger (RAII):**
1. Create a `TransactionLogger` class that:
   - Opens log file in constructor
   - Automatically closes file in destructor
   - Ensures all transactions are logged even if exceptions occur

**Safe Transaction Operations:**
2. Implement transaction safety:
   - Atomic transfer operations (all-or-nothing)
   - Automatic rollback on failure
   - Exception-safe balance updates

**Expected Output** (partial):
```
=== Banking System with RAII Demo ===
[Constructor] Account #1001 created: John Doe, $1000.00
[Constructor] Account #1002 created: Jane Smith, $1500.00
[Constructor] Business Account #1003: Acme Corp, $10000.00

[Transaction Log] Transfer initiated: #1001 -> #1002, $200.00
[RAII Logger] Transaction log opened: bank_transactions.log
[Success] Transfer completed successfully
[RAII Logger] Transaction log closed automatically

[Destructor] Account #1003 destroyed: Final balance $9800.00
[Destructor] Account #1002 destroyed: Final balance $1700.00  
[Destructor] Account #1001 destroyed: Final balance $800.00

Summary: 3 accounts created, 3 accounts destroyed, 1 transfer completed
```

## 🎯 Core Assignment 2: Resource Management Framework (2 hours)

### Part A: Dynamic Memory Manager (60 minutes)
**Objective**: Build a comprehensive memory management system with proper cleanup

Create `resource_manager.cpp` implementing:

**Resource Manager Class:**
1. Design a `ResourceManager` template class that:
   - Manages dynamic arrays of any type
   - Provides safe allocation/deallocation
   - Prevents memory leaks through RAII
   - Supports resizing and copying

**Dynamic Student Database:**
2. Apply the resource manager to build:
   - Dynamic student record system
   - Automatic capacity expansion
   - Safe copying and assignment
   - Memory usage tracking and reporting

### Part B: Advanced Lifecycle Patterns (60 minutes)
**Objective**: Master complex object relationships and lifecycle dependencies

Extend your resource manager with advanced patterns:

**Dependency Management:**
1. Implement objects with dependencies:
   - Parent objects that own child objects
   - Shared resources with reference counting
   - Ordered destruction based on dependencies

**Factory Pattern with RAII:**
2. Create object factories that:
   - Manage object creation and registration
   - Provide automatic cleanup on program exit
   - Handle creation failures gracefully

## Submission Guidelines

**For each assignment**:
1. Include source code with clear comments
2. Show compilation method used
3. Provide sample output
4. Document any challenges faced

**File organization**:
```
chapter04_solutions/
├── banking_system.cpp
├── resource_manager.cpp
└── README.md (with compilation notes)
```

---

# Quick Reference

## Top 5 Object Lifecycle Errors

### 1. Memory Leak
```cpp
MyClass* obj = new MyClass{};  // ❌ Missing delete
// Use object...
// Program ends - memory leaked!

MyClass* obj = new MyClass{};  // ✅ With cleanup
// Use object...
delete obj;
```

### 2. Using Object After Delete
```cpp
MyClass* obj = new MyClass{};
delete obj;
obj->method();                 // ❌ Undefined behavior!

MyClass* obj = new MyClass{};
// Use object...
delete obj;
obj = nullptr;                 // ✅ Prevent accidental use
```

### 3. Constructor Initialization
```cpp
class MyClass {
public:
    MyClass() {
        member = 42;           // ❌ Assignment, not initialization
    }
private:
    const int member;          // const members must be initialized!
};

class MyClass {
public:
    MyClass() : member{42} {}  // ✅ Initialization list
private:
    const int member;
};
```

### 4. Missing Virtual Destructor
```cpp
struct Base {
    ~Base() {}                 // ❌ Not virtual
};
struct Derived : Base {
    ~Derived() { /* cleanup */ }
};
Base* obj = new Derived{};
delete obj;                    // Only ~Base() called!

struct Base {
    virtual ~Base() = default; // ✅ Virtual destructor
};
```

### 5. Double Delete
```cpp
MyClass* obj = new MyClass{};
delete obj;
delete obj;                    // ❌ Undefined behavior!

MyClass* obj = new MyClass{};
delete obj;
obj = nullptr;                 // ✅ Prevent double delete
if (obj) delete obj;           // Safe
```

## Memory Management Best Practices

```cpp
// Prefer stack objects
MyClass obj{};                 // Automatic cleanup

// If you need heap, use RAII
class Container {
public:
    Container() : data_{new int[100]} {}
    ~Container() { delete[] data_; }
private:
    int* data_;
};

// Or modern C++ smart pointers
std::unique_ptr<MyClass> obj = std::make_unique<MyClass>();
// Automatic cleanup!
```

## Success Checklist

After Chapter 4, you should be able to:
- [ ] Write constructors that initialize object members
- [ ] Write destructors that clean up resources  
- [ ] Use RAII to manage files and memory automatically
- [ ] Create objects on both stack and heap
- [ ] Match every `new` with a `delete`
- [ ] Explain when constructors and destructors are called
- [ ] Use virtual destructors for inheritance
- [ ] Prevent memory leaks using RAII

**Not there yet?** Focus on RAII - it's the most important concept. Stack objects are safer than heap objects for beginners.

**Ready to move on?** Great! Chapter 5 will cover runtime polymorphism with virtual functions.

---

## What's Next?

**Chapter 5: Runtime Polymorphism** will cover:
- Virtual functions and inheritance
- Abstract base classes and interfaces
- Polymorphic behavior through base class pointers
- Virtual destructors in inheritance hierarchies

**You've mastered object lifecycle!** RAII is one of C++'s most powerful features - it makes resource management automatic and exception-safe. This foundation will serve you well throughout your C++ journey.

---

*Remember: Every resource acquired in a constructor should be released in the destructor. This makes C++ programs robust and predictable. RAII is not just a technique - it's a fundamental design philosophy!*