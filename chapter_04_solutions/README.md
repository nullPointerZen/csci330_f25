# Chapter 4: Object Lifecycle - Solution Files

## Overview
This directory contains solution files for Chapter 4 problems, focusing on object lifecycle concepts including constructors, destructors, and RAII (Resource Acquisition Is Initialization).

## File Organization

### Problem 1.1: Simple Bank Account
- **File**: `problem_1_1_solution.cpp`
- **Concepts**: Basic constructor/destructor syntax, automatic cleanup
- **Python/Java Connection**: Similar to `__init__` but with automatic cleanup

### Problem 2.1: File Logger Class  
- **File**: `problem_2_1_solution.cpp`
- **Concepts**: RAII pattern, resource management, error handling
- **Python/Java Connection**: Like Python's `with` statement or Java's try-with-resources

### Problem 3.1: Stack vs Heap Objects
- **File**: `problem_3_1_solution.cpp` 
- **Concepts**: Stack vs heap allocation, manual vs automatic cleanup
- **Python/Java Connection**: C++ exposes what garbage collectors hide

## Compilation Instructions

All solutions can be compiled with standard g++ commands:

```bash
# Individual compilation
g++ -o program_name solution_file.cpp

# Examples:
g++ -o bank_account problem_1_1_solution.cpp
g++ -o file_logger problem_2_1_solution.cpp
g++ -o stack_vs_heap problem_3_1_solution.cpp

# Run the programs
./bank_account
./file_logger
./stack_vs_heap
```

## Key Concepts Demonstrated

### 1. Constructor/Destructor Basics
- **Constructor**: `ClassName(params) : member{value} { }`
- **Destructor**: `~ClassName() { /* cleanup */ }`
- **Automatic calling**: Constructor on creation, destructor on scope exit

### 2. RAII Pattern
- **Resource acquisition** in constructor
- **Resource release** in destructor  
- **Automatic cleanup** when object goes out of scope
- **Exception safety** (resources cleaned up even if exceptions occur)

### 3. Stack vs Heap Management
- **Stack objects**: `ClassName obj;` - automatic cleanup
- **Heap objects**: `new ClassName()` - requires `delete`
- **Prefer stack** objects when possible for safety

## Common Patterns Shown

### Safe Resource Management
```cpp
class ResourceManager {
public:
    ResourceManager() { /* acquire resource */ }
    ~ResourceManager() { /* release resource */ }
};

{
    ResourceManager mgr;  // Stack object
    // Use resource
}  // Automatic cleanup here
```

### Error-Safe Constructor
```cpp
class SafeClass {
public:
    SafeClass() : resource{nullptr} {
        resource = acquire_resource();
        if (!resource) {
            // Mark as invalid but don't throw
            valid = false;
        }
    }
    
    ~SafeClass() {
        if (resource) release_resource();
    }
};
```

## Memory Leak Prevention

All solutions demonstrate proper memory management:

1. **Every `new` has a matching `delete`**
2. **RAII eliminates manual resource management**
3. **Stack objects preferred over heap objects**
4. **Pointers set to `nullptr` after `delete`**

## Testing for Memory Leaks

### Using Valgrind (Linux/Mac)
```bash
# Compile with debug info
g++ -g -o program solution.cpp

# Check for leaks
valgrind --leak-check=full ./program
```

### Manual Verification
- Count `new` and `delete` statements - should be equal
- Every `new[]` should have matching `delete[]`
- Use RAII to avoid manual memory management

## Insights for Python/Java Programmers

### What C++ Makes Explicit
1. **Object lifetime**: When objects are created and destroyed
2. **Resource management**: Who's responsible for cleanup  
3. **Memory allocation**: Stack vs heap decisions
4. **Deterministic cleanup**: Exactly when destructors run

### Similar Concepts
- **Python `with`**: Similar to C++ RAII
- **Java try-with-resources**: Similar to C++ RAII
- **Python `__del__`**: Similar to C++ destructor (but non-deterministic)
- **Java finalize**: Similar to C++ destructor (but deprecated and unreliable)

### Key Differences
- **C++ destructors**: Run immediately when scope ends
- **Python/Java cleanup**: Run eventually when garbage collector decides
- **C++ choice**: Stack (automatic) or heap (manual) allocation
- **Python/Java**: All objects on heap with garbage collection

## Best Practices Demonstrated

1. **Use stack objects by default**
2. **Use RAII for all resource management**
3. **Initialize all members in constructors**
4. **Clean up all resources in destructors**
5. **Handle constructor failures gracefully**
6. **Set pointers to `nullptr` after `delete`**

These solutions provide a foundation for understanding C++ object lifecycle and memory management, essential skills for system programming.