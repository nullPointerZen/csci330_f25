# Chapter 4: Assignment Helpers - Object Lifecycle

## Purpose
Scaffolding and hints for the object lifecycle assignments. Use when stuck or to verify your approach.

---

## Key Concepts Reminder

### Constructor Types
```cpp
Class();                        // Default constructor
Class(params);                  // Parameterized constructor
Class(const Class& other);      // Copy constructor
Class(Class&& other);           // Move constructor (C++11)
```

### Rule of Three (Classic C++)
If you need one, you probably need all three:
1. **Destructor** - Clean up resources
2. **Copy Constructor** - Deep copy resources
3. **Copy Assignment** - Handle self-assignment, clean old, copy new

### RAII Pattern
```cpp
class Resource {
    void* data;
public:
    Resource() { data = acquire(); }  // Constructor acquires
    ~Resource() { release(data); }    // Destructor releases
    // No manual cleanup needed!
};
```

---

## Problem Set 1: Banking System Helpers

### Account Class Structure
```cpp
class BankAccount {
private:
    static int next_account_number;  // Shared across all accounts
    int account_number;
    double balance;
    char owner_name[100];
    int* transaction_history;         // Dynamic array
    int transaction_count;
    int transaction_capacity;

public:
    // Default constructor
    BankAccount() : account_number(next_account_number++),
                    balance(0.0),
                    transaction_count(0),
                    transaction_capacity(10) {
        strcpy(owner_name, "Unknown");
        transaction_history = new int[transaction_capacity];
        printf("Account %d created\n", account_number);
    }

    // Parameterized constructor
    BankAccount(const char* name, double initial)
        : account_number(next_account_number++),
          balance(initial),
          transaction_count(0),
          transaction_capacity(10) {
        strcpy(owner_name, name);
        transaction_history = new int[transaction_capacity];
        // TODO: Add initial deposit to history
    }

    // Destructor - CRITICAL for dynamic memory!
    ~BankAccount() {
        delete[] transaction_history;
        printf("Account %d destroyed\n", account_number);
    }

    // Copy constructor - DEEP COPY required!
    BankAccount(const BankAccount& other)
        : account_number(next_account_number++),  // New account number!
          balance(other.balance),
          transaction_count(other.transaction_count),
          transaction_capacity(other.transaction_capacity) {
        strcpy(owner_name, other.owner_name);

        // Deep copy the transaction history
        transaction_history = new int[transaction_capacity];
        for (int i = 0; i < transaction_count; i++) {
            transaction_history[i] = other.transaction_history[i];
        }
    }
};

int BankAccount::next_account_number = 1000;  // Initialize static member
```

### Logger Class (RAII Example)
```cpp
class TransactionLogger {
private:
    FILE* log_file;
    char filename[100];

public:
    TransactionLogger(const char* account_name) {
        sprintf(filename, "%s_transactions.log", account_name);
        log_file = fopen(filename, "a");
        if (log_file) {
            fprintf(log_file, "=== Session started ===\n");
        }
    }

    ~TransactionLogger() {
        if (log_file) {
            fprintf(log_file, "=== Session ended ===\n");
            fclose(log_file);
        }
    }

    void log_transaction(const char* type, double amount) {
        if (log_file) {
            fprintf(log_file, "%s: $%.2f\n", type, amount);
        }
    }
};
```

---

## Problem Set 2: RAII Patterns

### Smart Pointer Implementation
```cpp
template<typename T>
class SmartPtr {
private:
    T* ptr;
    int* ref_count;  // Shared reference counter

public:
    // Constructor
    SmartPtr(T* p = nullptr) : ptr(p) {
        ref_count = new int(1);
    }

    // Copy constructor (increase ref count)
    SmartPtr(const SmartPtr& other)
        : ptr(other.ptr), ref_count(other.ref_count) {
        (*ref_count)++;
    }

    // Destructor (decrease ref count, delete if 0)
    ~SmartPtr() {
        (*ref_count)--;
        if (*ref_count == 0) {
            delete ptr;
            delete ref_count;
        }
    }

    // Operators for pointer-like behavior
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
};
```

### File Handler with RAII
```cpp
class FileHandler {
private:
    FILE* file;
    char mode[10];
    bool owns_file;  // Track ownership

public:
    FileHandler(const char* filename, const char* m)
        : owns_file(true) {
        strcpy(mode, m);
        file = fopen(filename, mode);
        if (!file) {
            throw std::runtime_error("Failed to open file");
        }
    }

    ~FileHandler() {
        if (file && owns_file) {
            fclose(file);
        }
    }

    // Prevent copying (or implement deep copy)
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;

    // Allow moving (C++11)
    FileHandler(FileHandler&& other)
        : file(other.file), owns_file(other.owns_file) {
        other.file = nullptr;
        other.owns_file = false;
    }
};
```

---

## Problem Set 3: Move Semantics Helpers

### Basic Move Constructor Pattern
```cpp
class Buffer {
private:
    char* data;
    size_t size;

public:
    // Regular constructor
    Buffer(size_t s) : size(s) {
        data = new char[size];
    }

    // Move constructor
    Buffer(Buffer&& other) noexcept
        : data(other.data), size(other.size) {
        // Steal resources
        other.data = nullptr;
        other.size = 0;
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;  // Clean up existing

            // Steal resources
            data = other.data;
            size = other.size;

            // Leave other in valid state
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~Buffer() {
        delete[] data;
    }
};
```

### String Class with Move
```cpp
class MyString {
private:
    char* str;
    size_t len;

public:
    // Constructor
    MyString(const char* s) {
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
        printf("Constructed: %s\n", str);
    }

    // Copy constructor (expensive)
    MyString(const MyString& other) {
        len = other.len;
        str = new char[len + 1];
        strcpy(str, other.str);
        printf("Copy constructed: %s\n", str);
    }

    // Move constructor (cheap)
    MyString(MyString&& other) noexcept {
        str = other.str;
        len = other.len;
        other.str = nullptr;
        other.len = 0;
        printf("Move constructed: %s\n", str);
    }

    ~MyString() {
        if (str) printf("Destroying: %s\n", str);
        delete[] str;
    }
};

// Factory function that benefits from move
MyString create_string(const char* s) {
    MyString temp(s);
    return temp;  // Move semantics avoid copy!
}
```

---

## Common Pitfalls and Solutions

### Pitfall 1: Shallow Copy with Pointers
```cpp
// BAD: Default copy constructor does shallow copy
class Bad {
    int* data;
public:
    Bad() { data = new int[10]; }
    ~Bad() { delete[] data; }
    // Missing copy constructor - DANGER!
};

// GOOD: Implement deep copy
class Good {
    int* data;
public:
    Good() { data = new int[10]; }
    Good(const Good& other) {
        data = new int[10];
        memcpy(data, other.data, 10 * sizeof(int));
    }
    ~Good() { delete[] data; }
};
```

### Pitfall 2: Self-Assignment
```cpp
Class& operator=(const Class& other) {
    if (this == &other) return *this;  // Check for self-assignment!
    // ... rest of assignment
}
```

### Pitfall 3: Exception Safety
```cpp
// Use copy-and-swap idiom
Class& operator=(Class other) {  // Pass by value (makes copy)
    swap(*this, other);  // Swap with copy
    return *this;        // Old data destroyed with 'other'
}
```

---

## Debugging Strategies

### Track Object Lifecycle
```cpp
class Tracked {
    static int count;
    int id;
public:
    Tracked() : id(++count) {
        printf("Object %d created\n", id);
    }
    Tracked(const Tracked& other) : id(++count) {
        printf("Object %d copied from %d\n", id, other.id);
    }
    ~Tracked() {
        printf("Object %d destroyed\n", id);
    }
};
```

### Memory Leak Detection
```cpp
// Simple allocation tracker
static int allocations = 0;

void* operator new(size_t size) {
    allocations++;
    printf("Allocation #%d: %zu bytes\n", allocations, size);
    return malloc(size);
}

void operator delete(void* ptr) {
    allocations--;
    printf("Deallocation. Remaining: %d\n", allocations);
    free(ptr);
}
```

---

## Checklist Before Submission

- [ ] All dynamic memory properly deleted in destructors
- [ ] Copy constructors perform deep copies
- [ ] Self-assignment handled in assignment operators
- [ ] No memory leaks (allocations match deallocations)
- [ ] RAII pattern used for resource management
- [ ] Move semantics implemented where beneficial
- [ ] Rule of Three/Five followed consistently