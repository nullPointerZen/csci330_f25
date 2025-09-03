# HW_11: Smart Pointers and RAII

## Overview
This assignment explores smart pointers and RAII (Resource Acquisition Is Initialization) as covered in Chapter 11 of "C++ Crash Course".

## Related Module
📚 **[Module 10 - Chapter 11: Smart Pointers](../)**

## Learning Objectives
- Master RAII principles for automatic resource management
- Understand unique_ptr for exclusive ownership
- Implement shared_ptr for shared ownership scenarios
- Use weak_ptr to break circular references
- Apply modern C++ memory management best practices

## Assignment Tasks
Complete THREE problem sets (2.25 hours total):

### Problem Set 1: RAII and Resource Management (45 minutes)
1. **RAII Fundamentals**: Resource acquisition and automatic cleanup
2. **Traditional Pointers**: Problems with manual memory management
3. **Smart Pointer Introduction**: Modern C++ approach

### Problem Set 2: Unique and Shared Pointers (45 minutes)
1. **unique_ptr**: Exclusive ownership and move semantics
2. **shared_ptr**: Reference counting and shared ownership
3. **Pointer Operations**: Reset, release, get, and custom deleters

### Problem Set 3: Advanced Smart Pointer Usage (45 minutes)
1. **weak_ptr**: Breaking circular references
2. **Custom Deleters**: Specialized cleanup functions
3. **Performance Considerations**: When to use each pointer type

## Building and Testing
```bash
mkdir build && cd build
cmake ..
make
./smart_pointers_demo
make test
```

## Assignment Rubric (16 Points Total)

This assignment will be evaluated using the following rubric:

| Criteria | Advanced (A) - 4 points | Proficient (P) - 3 points | Developing (D) - 2 points | Incomplete (I) - 1 point |
|----------|-------------------------|---------------------------|--------------------------|-------------------------|
| **Functionality & Requirements** | Code compiles and runs perfectly. All requirements met with edge cases handled. Demonstrates mastery of chapter concepts. | Code compiles and runs correctly. All main requirements met. Minor issues don't affect core functionality. Shows solid understanding. | Code compiles with warnings or has minor runtime issues. Most requirements met but some functionality missing or incomplete. | Code doesn't compile or has major functionality problems. Key requirements not met. Limited understanding evident. |
| **Concept Implementation** | Expertly implements chapter-specific concepts (RAII, unique_ptr, shared_ptr, weak_ptr, smart pointer best practices). Shows deep understanding of when and why to use features. | Correctly implements chapter concepts with good understanding. Appropriate use of language features. Shows clear comprehension of material. | Implements most chapter concepts but with some gaps or inconsistencies. Shows developing understanding but needs refinement. | Limited or incorrect implementation of chapter concepts. Doesn't demonstrate understanding of core material. |
| **Code Quality & Modern C++** | Exceptional organization, clear naming, appropriate modern C++ features. Code is maintainable and follows best practices consistently. | Well-organized code with good structure. Uses modern C++ features appropriately. Clear and readable with reasonable practices. | Code works but organization could improve. Inconsistent use of modern features. Shows understanding but lacks polish. | Poor organization, minimal use of modern C++ features. Difficult to read and understand. Basic functionality only. |
| **Problem-Solving & Verification** | Clear evidence of systematic approach. Handles edge cases and error conditions. Shows thorough verification of results with multiple test scenarios. | Good problem-solving approach with reasonable error handling. Shows evidence of testing and verification of functionality. | Basic problem-solving evident but limited error handling. Some testing done but not comprehensive. Shows developing verification skills. | Little evidence of systematic approach. Minimal error handling or testing. No clear verification strategy demonstrated. |

**Note**: This rubric applies to the entire assignment including all three problem sets (RAII Fundamentals, Smart Pointers, Real-World Applications).

## Time Allocation
- **Problem Set 1**: 45 minutes
- **Problem Set 2**: 45 minutes
- **Problem Set 3**: 45 minutes
- **Total**: 2.25 hours