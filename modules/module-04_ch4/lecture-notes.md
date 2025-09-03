# Chapter 4: Object Lifecycle - Complete Guide

## 📖 Learning Sequence (IMPORTANT!)

**🔄 How This Chapter Works:**
1. **📚 FIRST**: Read Textbook Chapter 4 "Object Lifecycle" (2-3 hours)
2. **🔍 SECOND**: Work through these lecture notes for Python/Java context and hands-on practice (7-8 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.5 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 4 "Object Lifecycle" FIRST**  
**✨ AUTHOR'S STRENGTH**: Josh Lospinoso's explanation of RAII is exceptional - don't skip it!

After completing the textbook reading and this chapter's materials, you will:
1. **Master** the C++ object lifecycle (construction, use, destruction)
2. **Write** constructors to initialize objects with default and custom values
3. **Implement** destructors to clean up object resources
4. **Apply** RAII principles for automatic resource management (textbook explains why this is brilliant)
5. **Use** dynamic memory allocation with new/delete safely
6. **Debug** lifecycle issues using VS Code's debugging tools
7. **Understand** the philosophy behind C++ resource management (from textbook)

**⏱️ Time Budget:**
- **📚 Textbook Reading: 2-3 hours** (Chapter 4: "Object Lifecycle" - REQUIRED FIRST)
- **🔍 Learning: 2.5 hours** (core concepts with Python/Java context)
- **💻 Hands-on Work: 4.5-5.5 hours** (comprehensive banking/RAII projects)
- **✅ Assignments: 2.5 hours** (demonstrate mastery)
- **📖 Note: Reading time is separate and must be completed BEFORE hands-on work**

**📝 Difficulty Note**: Object lifecycle and RAII are new concepts for most students - the textbook reading provides essential conceptual foundation.

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](../../setup/DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 🔄 Core Concepts: Object Lifecycle (2.5 hours)

**📖 Bridge to Textbook**: Now that you've read about constructors, destructors, and RAII in Chapter 4, let's connect those concepts to Python/Java patterns and see them in action with debugging tools.

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

**Smart Pointer Types:**
- `unique_ptr` - Single ownership, cannot be copied
- `shared_ptr` - Shared ownership, reference counted
- `weak_ptr` - Non-owning observer, prevents circular references

**Modern C++ Rule**: Prefer smart pointers over raw `new/delete`.

---

## 🔍 VS Code Debugging for Object Lifecycle (20 minutes)

### Essential Debugging Setup

**Add these breakpoint strategies:**

1. **Constructor Breakpoints**: Set breakpoints in constructors to watch initialization
2. **Destructor Breakpoints**: Set breakpoints in destructors to see cleanup timing
3. **Scope Tracking**: Use the Call Stack panel to see when objects go out of scope

**Launch configuration for lifecycle debugging:**
```json
{
    "name": "Debug Object Lifecycle",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/${fileBasenameNoExtension}",
    "setupCommands": [
        {
            "description": "Show object construction/destruction",
            "text": "-gdb-set print object on"
        }
    ]
}
```

### Key Debugging Techniques

| What to Debug | How to See It |
|---------------|---------------|
| **Constructor calls** | Step into (F11) object creation |
| **Member initialization** | Watch panel: monitor member variables |
| **Destruction timing** | Breakpoints in destructors |
| **Memory leaks** | Variables panel: watch pointer values |
| **RAII behavior** | Step through scope exit |

---

## 🧩 Hands-On Problems (2.25 hours)

**📖 Ready to Apply**: You've read the textbook and reviewed the Python/Java connections above. Now let's put that knowledge to work with hands-on practice that prepares you for the assignments.

### Problem Set 1: Basic Constructors and Destructors (45 minutes)

#### Problem 1.1: Bank Account Lifecycle (15 minutes)
**Create a complete bank account with lifecycle tracking:**

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

#### Problem 1.2: Multiple Constructors (15 minutes)
**Practice constructor overloading:**

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

#### Problem 1.3: Lifecycle Tracing (15 minutes)
**Understand construction and destruction order:**

```cpp
#include <cstdio>

class Counter {
public:
    Counter(int id) : id_{id} {
        printf("Constructor: Counter %d created\n", id_);
    }
    
    ~Counter() {
        printf("Destructor: Counter %d destroyed\n", id_);
    }
    
private:
    int id_;
};

int main() {
    printf("=== Starting main ===\n");
    Counter counter1{1};
    
    {
        printf("=== Entering inner scope ===\n");
        Counter counter2{2};
        Counter counter3{3};
        printf("=== About to leave inner scope ===\n");
    }
    
    printf("=== Back in main ===\n");
    return 0;
}
```

**Predict the output, then run to verify!**

### Problem Set 2: RAII and Resource Management (60 minutes)

#### Problem 2.1: File Logger with RAII (20 minutes)
**Implement automatic file management:**

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

**Verify**: Check that "test.log" contains your messages.

#### Problem 2.2: Dynamic Array Manager (20 minutes)
**Practice RAII with dynamic memory:**

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

#### Problem 2.3: Fix the Memory Leak (20 minutes)
**Identify and fix resource management problems:**

```cpp
#include <cstdio>
#include <cstring>

class StringBuffer {
public:
    StringBuffer(int capacity) : capacity_{capacity} {
        buffer_ = new char[capacity_];
        buffer_[0] = '\0';  // Empty string
        printf("StringBuffer created with capacity %d\n", capacity_);
    }
    
    // TODO: Add destructor here!
    
    void append(const char* text) {
        strcat(buffer_, text);  // Simplified - no bounds checking
    }
    
    void print() const {
        printf("Buffer contents: %s\n", buffer_);
    }
    
private:
    char* buffer_;
    int capacity_;
};

int main() {
    printf("=== Creating buffer ===\n");
    StringBuffer* buf = new StringBuffer{100};
    
    printf("=== Using buffer ===\n");
    buf->append("Hello ");
    buf->append("World!");
    buf->print();
    
    printf("=== Cleaning up ===\n");
    // TODO: What's missing here?
    
    return 0;
}
```

**Your Tasks:**
1. Add the missing destructor
2. Add the missing `delete` statement
3. Verify no memory leaks

### Problem Set 3: Storage Duration and Smart Pointers (50 minutes)

#### Problem 3.1: Storage Duration Comparison (20 minutes)
**Understand automatic, static, and dynamic storage:**

```cpp
#include <cstdio>
#include <memory>

class Counter {
public:
    Counter(const char* name) : name_{name} {
        printf("Counter '%s' created\n", name_);
    }
    
    ~Counter() {
        printf("Counter '%s' destroyed\n", name_);
    }
    
    void show() const {
        printf("Counter '%s' is alive\n", name_);
    }
    
private:
    const char* name_;
};

Counter global_counter{"Global"};  // Static storage duration

void test_function() {
    printf("=== Entering test_function ===\n");
    Counter auto_counter{"Automatic"};  // Automatic storage duration
    
    static Counter static_counter{"Static"};  // Static storage duration
    
    Counter* dynamic_counter = new Counter{"Dynamic"};  // Dynamic storage duration
    
    auto_counter.show();
    static_counter.show();
    dynamic_counter->show();
    
    // TODO: What happens to each counter when function ends?
    delete dynamic_counter;  // Manual cleanup for dynamic
    printf("=== Leaving test_function ===\n");
}

int main() {
    printf("=== Program start ===\n");
    global_counter.show();
    
    printf("\n=== First function call ===\n");
    test_function();
    
    printf("\n=== Second function call ===\n");
    test_function();
    
    printf("\n=== Program end ===\n");
    return 0;
}
```

**Questions to answer:**
- Which counters are destroyed when the function ends?
- Which counter survives multiple function calls?
- What order are the global objects destroyed in?

#### Problem 3.2: Smart Pointer Practice (30 minutes)
**Use modern C++ memory management:**

```cpp
#include <cstdio>
#include <memory>
#include <vector>

class Resource {
public:
    Resource(int id) : id_{id} {
        printf("Resource %d acquired\n", id_);
    }
    
    ~Resource() {
        printf("Resource %d released\n", id_);
    }
    
    void use() const {
        printf("Using resource %d\n", id_);
    }
    
    int get_id() const { return id_; }
    
private:
    int id_;
};

int main() {
    printf("=== Unique Pointer Demo ===\n");
    {
        auto unique_res = std::make_unique<Resource>(1);
        unique_res->use();
        
        // TODO: Try to copy unique_res - what happens?
        // auto copy = unique_res;  // Uncomment to see error
        
        // But you can move it
        auto moved_res = std::move(unique_res);
        if (moved_res) {
            moved_res->use();
        }
        
        if (unique_res == nullptr) {
            printf("unique_res is now null after move\n");
        }
    }  // moved_res automatically destroyed here
    
    printf("\n=== Shared Pointer Demo ===\n");
    {
        auto shared1 = std::make_shared<Resource>(2);
        printf("Reference count: %ld\n", shared1.use_count());
        
        {
            auto shared2 = shared1;  // Can copy shared_ptr
            printf("Reference count: %ld\n", shared1.use_count());
            
            shared1->use();
            shared2->use();
        }  // shared2 destroyed, but resource still alive
        
        printf("Reference count after shared2 destroyed: %ld\n", shared1.use_count());
        shared1->use();
    }  // shared1 destroyed, now resource is destroyed
    
    printf("\n=== Container of Smart Pointers ===\n");
    {
        std::vector<std::unique_ptr<Resource>> resources;
        
        // TODO: Add several resources to the vector
        resources.push_back(std::make_unique<Resource>(10));
        resources.push_back(std::make_unique<Resource>(11));
        resources.push_back(std::make_unique<Resource>(12));
        
        for (const auto& res : resources) {
            res->use();
        }
        
        printf("About to clear vector...\n");
        resources.clear();  // All resources automatically destroyed
    }
    
    return 0;
}
```

### Problem Set 4: Advanced Object Lifecycle (40 minutes)

#### Problem 4.1: Stack vs Heap Comparison (15 minutes)
**Compare automatic vs manual object management:**

```cpp
#include <cstdio>

class Timer {
public:
    Timer(const char* name) : name_{name} {
        printf("Timer '%s' started\n", name_);
    }
    
    ~Timer() {
        printf("Timer '%s' finished\n", name_);
    }
    
    void tick() const {
        printf("Timer '%s' tick\n", name_);
    }
    
private:
    const char* name_;
};

int main() {
    printf("=== Creating stack object ===\n");
    Timer stack_timer{"StackTimer"};
    stack_timer.tick();
    
    printf("\n=== Creating heap object ===\n");
    Timer* heap_timer = new Timer{"HeapTimer"};
    heap_timer->tick();
    
    printf("\n=== Manual cleanup ===\n");
    delete heap_timer;
    
    printf("\n=== About to exit main ===\n");
    return 0;
    // Watch when stack_timer destructor is called!
}
```

**Observe**: When is each destructor called?

#### Problem 4.2: Resource Manager with Error Handling (25 minutes)
**Handle constructor failures gracefully:**

```cpp
#include <cstdio>
#include <cstring>

class ResourceManager {
public:
    ResourceManager(const char* resource_name) : name_{resource_name}, acquired_{false} {
        printf("Attempting to acquire resource '%s'\n", name_);
        
        // Simulate resource acquisition (might fail)
        if (strlen(resource_name) > 0 && resource_name[0] != 'X') {
            acquired_ = true;
            printf("Successfully acquired resource '%s'\n", name_);
        } else {
            acquired_ = false;
            printf("Failed to acquire resource '%s'\n", name_);
        }
    }
    
    ~ResourceManager() {
        if (acquired_) {
            printf("Releasing resource '%s'\n", name_);
        } else {
            printf("No resource to release for '%s'\n", name_);
        }
    }
    
    bool is_acquired() const {
        return acquired_;
    }
    
    void use_resource() const {
        if (acquired_) {
            printf("Using resource '%s'\n", name_);
        } else {
            printf("Cannot use resource '%s' - not acquired\n", name_);
        }
    }
    
private:
    const char* name_;
    bool acquired_;
};

int main() {
    printf("=== Test 1: Successful acquisition ===\n");
    {
        ResourceManager good_resource{"Database"};
        if (good_resource.is_acquired()) {
            good_resource.use_resource();
        }
    }
    
    printf("\n=== Test 2: Failed acquisition ===\n");
    {
        ResourceManager bad_resource{"XInvalidResource"};
        bad_resource.use_resource();  // Should handle gracefully
    }
    
    printf("\n=== Test 3: Heap allocation ===\n");
    ResourceManager* heap_resource = new ResourceManager{"NetworkConnection"};
    heap_resource->use_resource();
    delete heap_resource;
    
    return 0;
}
```

---

## 🔧 Quick Reference & Troubleshooting

### Top 5 Object Lifecycle Errors

#### 1. Memory Leak
```cpp
MyClass* obj = new MyClass{};  // ❌ Missing delete
// Use object...
// Program ends - memory leaked!

MyClass* obj = new MyClass{};  // ✅ With cleanup
// Use object...
delete obj;
```

#### 2. Using Object After Delete
```cpp
MyClass* obj = new MyClass{};
delete obj;
obj->method();                 // ❌ Undefined behavior!

MyClass* obj = new MyClass{};
// Use object...
delete obj;
obj = nullptr;                 // ✅ Prevent accidental use
```

#### 3. Missing Virtual Destructor
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

#### 4. Constructor Initialization
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

#### 5. Double Delete
```cpp
MyClass* obj = new MyClass{};
delete obj;
delete obj;                    // ❌ Undefined behavior!

MyClass* obj = new MyClass{};
delete obj;
obj = nullptr;                 // ✅ Prevent double delete
if (obj) delete obj;           // Safe
```

### Memory Management Best Practices

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

---

## ✅ Chapter 4 Success Checklist

### Constructor Mastery
- [ ] Can write default and parameterized constructors
- [ ] Use initialization lists for member initialization
- [ ] Understand constructor overloading
- [ ] Handle constructor errors gracefully

### Destructor Proficiency  
- [ ] Write destructors that clean up resources
- [ ] Understand when destructors are called
- [ ] Use virtual destructors for inheritance
- [ ] Apply RAII pattern consistently

### Memory Management
- [ ] Understand stack vs heap object creation
- [ ] Know the three storage duration types (automatic, static, dynamic)
- [ ] Match every `new` with corresponding `delete`
- [ ] Prevent memory leaks using RAII
- [ ] Use smart pointers (`unique_ptr`, `shared_ptr`) for automatic memory management
- [ ] Avoid double deletion and use-after-free

### Object Lifecycle Understanding
- [ ] Trace object construction and destruction order
- [ ] Use debugging tools to observe lifecycle
- [ ] Handle resource acquisition failures
- [ ] Design exception-safe resource management

---

## 🚀 What's Next?

**Chapter 5: Runtime Polymorphism** will cover:
- Virtual functions and inheritance
- Abstract base classes and interfaces
- Polymorphic behavior through base class pointers
- Virtual destructors in inheritance hierarchies

**You've mastered object lifecycle!** 🎉 RAII is one of C++'s most powerful features - it makes resource management automatic and exception-safe. The constructor/destructor pattern you've learned is fundamental to modern C++ programming.

**Key Takeaway**: C++ gives you deterministic destruction - use it! RAII makes your programs safer and more predictable than garbage-collected languages for resource management.

---

*Remember: Every resource acquired in a constructor should be released in the destructor. This makes C++ programs robust and predictable. RAII is not just a technique - it's a fundamental design philosophy!*