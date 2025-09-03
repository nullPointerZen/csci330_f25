# HW_04: Object Lifecycle and RAII

## Overview
This assignment explores constructors, destructors, and Resource Acquisition Is Initialization (RAII) as covered in Chapter 4 of "C++ Crash Course".

## Related Module
📚 **[Module 04 - Chapter 4: Object Lifecycle](../)**

## Learning Objectives
- Master the C++ object lifecycle (construction, use, destruction)
- Write constructors (default, parameterized, copy)
- Implement destructors for resource cleanup
- Apply RAII principles for automatic resource management
- Understand the Rule of Three
- Debug lifecycle issues with proper logging

## Assignment Tasks
Complete TWO comprehensive projects (4 hours total):

### Project 1: Banking System with RAII (2 hours)
1. **Account Class**: Constructors, destructors, transaction logging
2. **Resource Management**: Automatic file handle cleanup
3. **Rule of Three**: Copy constructor and assignment operator
4. **Lifecycle Tracking**: Log object creation and destruction

### Project 2: Resource Management Framework (2 hours)
1. **File Wrapper**: RAII for file handles
2. **Memory Pool**: Custom memory management
3. **Smart Resource**: Template for any resource type
4. **Exception Safety**: Cleanup in all scenarios

## Building and Testing
```bash
mkdir build && cd build
cmake ..
make
./banking_system      # Run project 1
./resource_manager    # Run project 2
make test
```

## Assignment Rubric (16 Points Total)

This assignment will be evaluated using the following rubric:

| Criteria | Advanced (A) - 4 points | Proficient (P) - 3 points | Developing (D) - 2 points | Incomplete (I) - 1 point |
|----------|-------------------------|---------------------------|--------------------------|-------------------------|
| **Functionality & Requirements** | Code compiles and runs perfectly. All requirements met with edge cases handled. Demonstrates mastery of chapter concepts. | Code compiles and runs correctly. All main requirements met. Minor issues don't affect core functionality. Shows solid understanding. | Code compiles with warnings or has minor runtime issues. Most requirements met but some functionality missing or incomplete. | Code doesn't compile or has major functionality problems. Key requirements not met. Limited understanding evident. |
| **Concept Implementation** | Expertly implements chapter-specific concepts (RAII, constructors/destructors, Rule of Three). Shows deep understanding of when and why to use features. | Correctly implements chapter concepts with good understanding. Appropriate use of language features. Shows clear comprehension of material. | Implements most chapter concepts but with some gaps or inconsistencies. Shows developing understanding but needs refinement. | Limited or incorrect implementation of chapter concepts. Doesn't demonstrate understanding of core material. |
| **Code Quality & Modern C++** | Exceptional organization, clear naming, appropriate modern C++ features. Code is maintainable and follows best practices consistently. | Well-organized code with good structure. Uses modern C++ features appropriately. Clear and readable with reasonable practices. | Code works but organization could improve. Inconsistent use of modern features. Shows understanding but lacks polish. | Poor organization, minimal use of modern C++ features. Difficult to read and understand. Basic functionality only. |
| **Problem-Solving & Verification** | Clear evidence of systematic approach. Handles edge cases and error conditions. Shows thorough verification of results with multiple test scenarios. | Good problem-solving approach with reasonable error handling. Shows evidence of testing and verification of functionality. | Basic problem-solving evident but limited error handling. Some testing done but not comprehensive. Shows developing verification skills. | Little evidence of systematic approach. Minimal error handling or testing. No clear verification strategy demonstrated. |

**Note**: This rubric applies to the entire assignment including both projects (Banking System and Resource Management Framework).

## Time Allocation
- **Banking System**: 2 hours
- **Resource Manager**: 2 hours
- **Total**: 4 hours