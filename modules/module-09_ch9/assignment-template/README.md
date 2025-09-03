# HW_09: Functions and Lambdas

## Overview
This assignment explores functions, lambda expressions, and modern function design as covered in Chapter 9 of "C++ Crash Course".

## Related Module
📚 **[Module 09 - Chapter 9: Functions](../)**

## Learning Objectives
- Master function declaration, definition, and calling
- Implement function overloading and default parameters
- Create and use lambda expressions effectively
- Understand function pointers and std::function
- Apply modern C++ function features (constexpr, auto)

## Assignment Tasks
Complete THREE problem sets (2.25 hours total):

### Problem Set 1: Function Fundamentals (45 minutes)
1. **Function Basics**: Declaration, definition, parameters, return types
2. **Function Overloading**: Same name, different signatures
3. **Default Parameters**: Optional function arguments

### Problem Set 2: Lambda Expressions (45 minutes)
1. **Basic Lambdas**: Syntax, captures, and usage
2. **Capture Modes**: By value [=], by reference [&], explicit captures
3. **Lambda Applications**: STL algorithms, callbacks, utilities

### Problem Set 3: Advanced Function Concepts (45 minutes)
1. **Function Pointers**: Traditional C-style function pointers
2. **std::function**: Modern C++ callable wrapper
3. **Constexpr Functions**: Compile-time function evaluation

## Building and Testing
```bash
mkdir build && cd build
cmake ..
make
./functions_demo
make test
```

## Grading Criteria
- [ ] Proper function design and implementation
- [ ] Correct function overloading usage
- [ ] Effective lambda expression creation
- [ ] Understanding of capture mechanisms
- [ ] Modern C++ function features applied

## Time Allocation
- **Problem Set 1**: 45 minutes
- **Problem Set 2**: 45 minutes
- **Problem Set 3**: 45 minutes
- **Total**: 2.25 hours