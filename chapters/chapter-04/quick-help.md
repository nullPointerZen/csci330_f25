# Chapter 4: Object Lifecycle - Quick Help Guide

## Top 5 Object Lifecycle Errors (Fix These First!)

| Error/Problem | Likely Cause | Quick Fix |
|--------------|--------------|-----------|
| **Memory leak detected** | `new` without `delete` | Every `new` needs a matching `delete` |
| **Segmentation fault** | Using deleted object | Don't use object after `delete` |
| **Constructor not called** | Wrong syntax | Use `ClassName obj{params};` not `ClassName obj();` |
| **Double delete error** | `delete` called twice | Set pointer to `nullptr` after `delete` |
| **Destructor not virtual** | Base class destructor | Add `virtual ~ClassName() {}` for inheritance |

## Constructor/Destructor Quick Reference

```cpp
class MyClass {
public:
    // Default constructor
    MyClass() { /* initialize members */ }
    
    // Parameterized constructor
    MyClass(int value) : member{value} { }
    
    // Destructor (cleanup resources)
    ~MyClass() { /* cleanup code */ }
    
private:
    int member;
};

// Usage
MyClass obj1;           // Stack: automatic cleanup
MyClass obj2{42};       // Stack: with parameter
MyClass* obj3 = new MyClass{42};  // Heap: needs delete
delete obj3;            // Manual cleanup
```

## C++ vs Python/Java Quick Comparison

| Aspect | C++ | Python | Java |
|--------|-----|--------|------|
| **Constructor** | `MyClass() {}` | `def __init__(self):` | `public MyClass() {}` |
| **Destructor** | `~MyClass() {}` | `def __del__(self):` | `finalize()` (deprecated) |
| **Stack Object** | `MyClass obj;` | N/A | N/A |
| **Heap Object** | `new MyClass()` | `MyClass()` | `new MyClass()` |
| **Cleanup** | `delete obj` or automatic | Garbage collector | Garbage collector |

## Stuck? Try This!

**Constructor not working?**
1. Check syntax: `MyClass(params) {}` not `MyClass(params) { return; }`
2. Make sure constructor is in `public:` section
3. Initialize all members in constructor body or initialization list

**Memory leak suspected?**
1. Count your `new` and `delete` statements - should be equal
2. Every `new[]` needs `delete[]` (not just `delete`)
3. Consider using stack objects instead of heap

**Destructor not called?**
1. Stack objects: destructor called automatically at scope end
2. Heap objects: destructor called only when you `delete`
3. Check if you forgot to `delete` a heap object

**Segmentation fault?**
1. Don't use objects after `delete`
2. Don't call `delete` twice on same object
3. Initialize pointers to `nullptr`

## Memory Management Patterns

### RAII Pattern (Recommended)
```cpp
class FileManager {
public:
    FileManager(const char* filename) {
        file = fopen(filename, "w");  // Acquire resource
    }
    
    ~FileManager() {
        if (file) fclose(file);       // Release resource
    }
    
private:
    FILE* file;
};

// Usage: automatic cleanup!
{
    FileManager mgr{"data.txt"};
    // File automatically closed when mgr goes out of scope
}
```

### Safe Heap Management
```cpp
// Create
MyClass* obj = new MyClass{42};

// Use
obj->some_method();

// Clean up
delete obj;
obj = nullptr;  // Prevent accidental reuse
```

## Common Patterns from Python/Java

### Python `with` statement → C++ RAII
```python
# Python
with open("file.txt", "w") as f:
    f.write("Hello")
# File automatically closed
```

```cpp
// C++ equivalent
class FileWrapper {
public:
    FileWrapper(const char* name) : file{fopen(name, "w")} {}
    ~FileWrapper() { if (file) fclose(file); }
    void write(const char* text) { if (file) fprintf(file, "%s", text); }
private:
    FILE* file;
};

{
    FileWrapper f{"file.txt"};
    f.write("Hello");
    // File automatically closed
}
```

### Java try-with-resources → C++ RAII
```java
// Java
try (FileWriter f = new FileWriter("file.txt")) {
    f.write("Hello");
} // File automatically closed
```

C++ RAII provides the same automatic cleanup!

## Debugging Object Lifecycle

### Add Lifecycle Tracing
```cpp
class TrackedClass {
public:
    TrackedClass(int id) : id{id} {
        printf("Constructor: Object %d created\n", id);
    }
    
    ~TrackedClass() {
        printf("Destructor: Object %d destroyed\n", id);
    }
    
private:
    int id;
};
```

### Memory Leak Detection
```bash
# Linux/Mac with valgrind
valgrind --leak-check=full ./your_program

# Windows with Visual Studio
# Use Debug Heap or Application Verifier

# Or manual checking: count new/delete pairs
```

## Time Management Tips

- **Problem Set 1**: 45 minutes (Basic constructors/destructors)
- **Problem Set 2**: 60 minutes (RAII and resources)  
- **Problem Set 3**: 40 minutes (Advanced lifecycle)
- **Total**: 2.25 hours maximum

**Taking longer?** Focus on understanding over perfection. RAII is the key concept.

## Success Checklist

After Chapter 4, you should be able to:
- [ ] Write constructors that initialize object members
- [ ] Write destructors that clean up resources  
- [ ] Use RAII to manage files and memory automatically
- [ ] Create objects on both stack and heap
- [ ] Match every `new` with a `delete`
- [ ] Explain when constructors and destructors are called

**Not there yet?** Focus on RAII - it's the most important concept. Stack objects are safer than heap objects for beginners.

## Emergency Fixes

**Program crashes immediately?**
```cpp
// Check for uninitialized pointers
class Safe {
public:
    Safe() : ptr{nullptr} {}  // Always initialize!
private:
    int* ptr;
};
```

**Memory leak in simple program?**
```cpp
// Every new needs delete
int* data = new int[100];  // Create
// ... use data ...
delete[] data;             // Clean up
data = nullptr;            // Prevent reuse
```

**Constructor confusion?**
```cpp
// Wrong: function declaration
MyClass obj();

// Right: object creation
MyClass obj;        // Default constructor
MyClass obj{42};    // Parameterized constructor
```