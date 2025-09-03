# HW_03: References and Const Correctness

## Overview
This assignment explores C++ references, const correctness, and the auto keyword as covered in Chapter 3 of "C++ Crash Course".

## Related Module
📚 **[Module 03 - Chapter 3: Reference Types](../)**

## Learning Objectives
- Create and use references as aliases to existing variables
- Master const correctness to prevent accidental modifications
- Distinguish between references and pointers
- Use the auto keyword for type deduction
- Apply references in function parameters for efficiency

## Assignment Tasks
Complete THREE problem sets (2.25 hours total):

### Problem Set 1: Basic References (45 minutes)
1. **Reference Fundamentals**: Create and use basic references
2. **References vs Copies**: Show references are aliases, not copies
3. **Multiple References**: Multiple references to same object

### Problem Set 2: Functions with References (45 minutes)
1. **Swap Function**: Classic swap using references
2. **Efficient Parameter Passing**: Large struct passing
3. **Return by Reference**: Safe reference returns

### Problem Set 3: Const Correctness (45 minutes)
1. **Const References**: Read-only access to data
2. **Const Methods**: Member functions that don't modify
3. **Auto Type Deduction**: Using auto with references

## Building and Testing
```bash
mkdir build && cd build
cmake ..
make
./references_demo
make test
```

## Assignment Rubric (16 Points Total)

This assignment will be evaluated using the following rubric:

| Criteria | Advanced (A) - 4 points | Proficient (P) - 3 points | Developing (D) - 2 points | Incomplete (I) - 1 point |
|----------|-------------------------|---------------------------|--------------------------|-------------------------|
| **Functionality & Requirements** | Code compiles and runs perfectly. All requirements met with edge cases handled. Demonstrates mastery of chapter concepts. | Code compiles and runs correctly. All main requirements met. Minor issues don't affect core functionality. Shows solid understanding. | Code compiles with warnings or has minor runtime issues. Most requirements met but some functionality missing or incomplete. | Code doesn't compile or has major functionality problems. Key requirements not met. Limited understanding evident. |
| **Concept Implementation** | Expertly implements chapter-specific concepts (references, const correctness, auto keyword). Shows deep understanding of when and why to use features. | Correctly implements chapter concepts with good understanding. Appropriate use of language features. Shows clear comprehension of material. | Implements most chapter concepts but with some gaps or inconsistencies. Shows developing understanding but needs refinement. | Limited or incorrect implementation of chapter concepts. Doesn't demonstrate understanding of core material. |
| **Code Quality & Modern C++** | Exceptional organization, clear naming, appropriate modern C++ features. Code is maintainable and follows best practices consistently. | Well-organized code with good structure. Uses modern C++ features appropriately. Clear and readable with reasonable practices. | Code works but organization could improve. Inconsistent use of modern features. Shows understanding but lacks polish. | Poor organization, minimal use of modern C++ features. Difficult to read and understand. Basic functionality only. |
| **Problem-Solving & Verification** | Clear evidence of systematic approach. Handles edge cases and error conditions. Shows thorough verification of results with multiple test scenarios. | Good problem-solving approach with reasonable error handling. Shows evidence of testing and verification of functionality. | Basic problem-solving evident but limited error handling. Some testing done but not comprehensive. Shows developing verification skills. | Little evidence of systematic approach. Minimal error handling or testing. No clear verification strategy demonstrated. |

**Note**: This rubric applies to the entire assignment including all three problem sets (Basic References, Functions with References, Const Correctness).

## Time Allocation
- **Problem Set 1**: 45 minutes
- **Problem Set 2**: 45 minutes  
- **Problem Set 3**: 45 minutes
- **Total**: 2.25 hours