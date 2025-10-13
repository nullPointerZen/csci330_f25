# Chapter 9: Functions - Solutions

This directory contains complete solutions for all Chapter 9 problem sets, demonstrating function pointers, lambda expressions, function objects, and std::function usage.

## Compilation Instructions

All solutions are written in standard C++14 and can be compiled with:

```bash
g++ -std=c++14 -Wall -Wextra -O2 filename.cpp -o output_name
```

Or with clang:
```bash
clang++ -std=c++14 -Wall -Wextra -O2 filename.cpp -o output_name
```

## Problem Set 1: Function Pointers and Callbacks

### Problem 1.1: Calculator with Function Pointers
**File**: `problem_set_1/problem_1_1_calculator.cpp`

**Key Concepts Demonstrated**:
- Function pointer declaration and initialization
- Array of function pointers for menu systems
- Safe function pointer dereferencing
- Error handling in callback contexts

**Compilation and Execution**:
```bash
g++ -std=c++14 problem_set_1/problem_1_1_calculator.cpp -o calculator
./calculator
```

### Problem 1.2: Event System with Callbacks
**File**: `problem_set_1/problem_1_2_event_system.cpp`

**Key Concepts Demonstrated**:
- Typedef for function pointer clarity
- Vector storage of function pointers
- Multiple callback pattern implementation
- Real-world event handling design

### Problem 1.3: Sorting with Custom Comparators
**File**: `problem_set_1/problem_1_3_sorting.cpp`

**Key Concepts Demonstrated**:
- Function pointers as algorithm parameters
- Strategy pattern with function pointers
- Comparison function design
- Bubble sort with custom comparator

## Problem Set 2: Lambda Expressions and Captures

### Problem 2.1: STL Algorithm Integration
**File**: `problem_set_2/problem_2_1_stl_lambdas.cpp`

**Key Concepts Demonstrated**:
- Lambda integration with STL algorithms (for_each, copy_if, count_if, accumulate)
- Different capture modes (by value, by reference)
- Predicate and transform lambdas
- Modern C++ algorithm usage patterns

**Compilation and Execution**:
```bash
g++ -std=c++14 problem_set_2/problem_2_1_stl_lambdas.cpp -o stl_lambdas
./stl_lambdas
```

### Problem 2.2: Advanced Lambda Captures
**File**: `problem_set_2/problem_2_2_lambda_captures.cpp`

**Key Concepts Demonstrated**:
- Mixed capture modes ([=, &var])
- Init captures (C++14)
- Member variable captures
- Lambda lifetime and scope safety
- Stateful lambda creation

### Problem 2.3: Generic Lambdas
**File**: `problem_set_2/problem_2_3_generic_lambdas.cpp`

**Key Concepts Demonstrated**:
- Generic lambdas with auto parameters
- Template-like behavior without explicit templates
- Type deduction in lambda expressions
- STL integration with generic callables

## Problem Set 3: Function Objects and Integration

### Problem 3.1: Custom Function Objects
**File**: `problem_set_3/problem_3_1_function_objects.cpp`

**Key Concepts Demonstrated**:
- Stateful function object design
- operator() implementation
- State management in functors
- When to use functors vs lambdas
- Statistical processing with function objects

### Problem 3.2: Complete Function Integration Project
**File**: `problem_set_3/problem_3_2_integration_project.cpp`

**Key Concepts Demonstrated**:
- Integration of all function types (pointers, lambdas, functors, std::function)
- std::function for type erasure
- Composable pipeline architecture
- Real-world data processing design
- Performance considerations

**Compilation and Execution**:
```bash
g++ -std=c++14 problem_set_3/problem_3_2_integration_project.cpp -o integration_project
./integration_project
```

## Key Learning Outcomes

After working through these solutions, students should understand:

1. **Function Pointers**: When and how to use C-style function pointers for callbacks and configurable behavior
2. **Lambda Expressions**: Modern C++ closures with various capture modes and their applications
3. **Function Objects**: Stateful callable objects and their advantages over lambdas in certain scenarios
4. **std::function**: Type erasure for storing different callable types uniformly
5. **Integration**: How to combine different function types in flexible, maintainable designs

## Common Patterns Demonstrated

### 1. Strategy Pattern with Functions
Using function pointers, lambdas, or functors to implement configurable algorithms.

### 2. Pipeline Architecture
Chaining multiple processing stages using std::function for flexibility.

### 3. Event Systems
Callback-based architectures using various callable types.

### 4. STL Integration
Using lambdas effectively with standard algorithms for functional programming patterns.

## Performance Notes

- **Function Pointers**: Minimal overhead, but prevent some optimizations
- **Lambdas**: Often inlined by compiler, zero overhead in many cases
- **Function Objects**: Can be optimized very well, similar to lambdas
- **std::function**: Has call overhead due to type erasure, use judiciously

## Best Practices Illustrated

1. **Prefer lambdas** for modern C++ code unless you need the specific features of other approaches
2. **Use function objects** when you need complex state management
3. **Use std::function** when you need to store different callable types together
4. **Use function pointers** for C interop or when performance is absolutely critical
5. **Always validate** function pointers before calling
6. **Be careful with lambda captures**, especially reference captures and lifetime issues

## Extension Ideas

For students who want to explore further:

1. **Perfect Forwarding**: Implement function wrappers using perfect forwarding
2. **Recursive Lambdas**: Create self-referencing lambdas using std::function
3. **Template Metaprogramming**: Use SFINAE with callable types
4. **Performance Benchmarking**: Compare call overhead of different function types
5. **Functional Programming**: Implement map, reduce, filter using C++ callables

## Python/Java Connections

These solutions demonstrate how C++ function concepts relate to:

- **Python**: First-class functions, lambdas, decorators, closures
- **Java**: Functional interfaces, method references, lambda expressions, streams API

The key difference is that C++ requires more explicit type information but offers better performance and more control over memory and calling conventions.