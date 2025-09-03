# HW_12: Utilities and Move Semantics

## Overview
This assignment explores modern C++ utilities and move semantics as covered in Chapter 12 of "C++ Crash Course".

## Related Module
📚 **[Module 11 - Chapter 12: Utilities](../)**

## Learning Objectives
- Master move semantics and std::move
- Understand perfect forwarding with std::forward
- Implement std::optional for nullable types
- Use std::variant for type-safe unions
- Apply modern C++ utility classes effectively

## Assignment Tasks
Complete THREE problem sets (2.25 hours total):

### Problem Set 1: Move Semantics Fundamentals (45 minutes)
1. **Move Constructors**: Efficient resource transfer
2. **Move Assignment**: Assignment with move semantics
3. **std::move**: Explicit move requests

### Problem Set 2: Modern Utility Types (45 minutes)
1. **std::optional**: Nullable types without pointers
2. **std::variant**: Type-safe discriminated unions
3. **std::any**: Type-erased value storage

### Problem Set 3: Advanced Utilities (45 minutes)
1. **Perfect Forwarding**: std::forward template patterns
2. **std::tuple**: Multi-value containers
3. **Utility Functions**: swap, exchange, and more

## Building and Testing
```bash
mkdir build && cd build
cmake ..
make
./utilities_demo
make test
```

## Assignment Rubric (16 Points Total)

This assignment will be evaluated using the following rubric:

| Criteria | Advanced (A) - 4 points | Proficient (P) - 3 points | Developing (D) - 2 points | Incomplete (I) - 1 point |
|----------|-------------------------|---------------------------|--------------------------|-------------------------|
| **Functionality & Requirements** | Code compiles and runs perfectly. All requirements met with edge cases handled. Demonstrates mastery of chapter concepts. | Code compiles and runs correctly. All main requirements met. Minor issues don't affect core functionality. Shows solid understanding. | Code compiles with warnings or has minor runtime issues. Most requirements met but some functionality missing or incomplete. | Code doesn't compile or has major functionality problems. Key requirements not met. Limited understanding evident. |
| **Concept Implementation** | Expertly implements chapter-specific concepts (move semantics, std::optional, std::variant, perfect forwarding, utility classes). Shows deep understanding of when and why to use features. | Correctly implements chapter concepts with good understanding. Appropriate use of language features. Shows clear comprehension of material. | Implements most chapter concepts but with some gaps or inconsistencies. Shows developing understanding but needs refinement. | Limited or incorrect implementation of chapter concepts. Doesn't demonstrate understanding of core material. |
| **Code Quality & Modern C++** | Exceptional organization, clear naming, appropriate modern C++ features. Code is maintainable and follows best practices consistently. | Well-organized code with good structure. Uses modern C++ features appropriately. Clear and readable with reasonable practices. | Code works but organization could improve. Inconsistent use of modern features. Shows understanding but lacks polish. | Poor organization, minimal use of modern C++ features. Difficult to read and understand. Basic functionality only. |
| **Problem-Solving & Verification** | Clear evidence of systematic approach. Handles edge cases and error conditions. Shows thorough verification of results with multiple test scenarios. | Good problem-solving approach with reasonable error handling. Shows evidence of testing and verification of functionality. | Basic problem-solving evident but limited error handling. Some testing done but not comprehensive. Shows developing verification skills. | Little evidence of systematic approach. Minimal error handling or testing. No clear verification strategy demonstrated. |

**Note**: This rubric applies to the entire assignment including all three problem sets (Move Semantics, Modern Utilities, Advanced Applications).

## Time Allocation
- **Problem Set 1**: 45 minutes
- **Problem Set 2**: 45 minutes
- **Problem Set 3**: 45 minutes
- **Total**: 2.25 hours