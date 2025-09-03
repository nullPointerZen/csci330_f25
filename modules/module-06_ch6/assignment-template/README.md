# HW_06: Compile-Time Polymorphism (Templates)

## Overview
This assignment explores templates and generic programming as covered in Chapter 6 of "C++ Crash Course".

## Related Module
📚 **[Module 06 - Chapter 6: Compile-Time Polymorphism](../)**

## Learning Objectives
- Create function templates for generic operations
- Implement class templates for reusable containers
- Understand template instantiation and specialization
- Apply SFINAE and type traits basics
- Compare compile-time vs runtime polymorphism

## Assignment Tasks
Complete THREE problem sets (2.25 hours total):

### Problem Set 1: Function Templates (45 minutes)
1. **Generic Min/Max**: Template functions for any comparable type
2. **Array Operations**: Generic sum, average, find functions
3. **Type Safety**: Demonstrate compile-time type checking

### Problem Set 2: Class Templates (45 minutes)
1. **Generic Container**: Simple vector-like container template
2. **Pair/Triple**: Multi-value holder templates
3. **Stack Template**: Generic stack implementation

### Problem Set 3: Advanced Templates (45 minutes)
1. **Template Specialization**: Special behavior for specific types
2. **Variadic Templates**: Functions with variable arguments
3. **Type Traits**: Basic compile-time type checking

## Building and Testing
```bash
mkdir build && cd build
cmake ..
make
./templates_demo
make test
```

## Assignment Rubric (16 Points Total)

This assignment will be evaluated using the following rubric:

| Criteria | Advanced (A) - 4 points | Proficient (P) - 3 points | Developing (D) - 2 points | Incomplete (I) - 1 point |
|----------|-------------------------|---------------------------|--------------------------|-------------------------|
| **Functionality & Requirements** | Code compiles and runs perfectly. All requirements met with edge cases handled. Demonstrates mastery of chapter concepts. | Code compiles and runs correctly. All main requirements met. Minor issues don't affect core functionality. Shows solid understanding. | Code compiles with warnings or has minor runtime issues. Most requirements met but some functionality missing or incomplete. | Code doesn't compile or has major functionality problems. Key requirements not met. Limited understanding evident. |
| **Concept Implementation** | Expertly implements chapter-specific concepts (function templates, class templates, specialization, variadic templates). Shows deep understanding of when and why to use features. | Correctly implements chapter concepts with good understanding. Appropriate use of language features. Shows clear comprehension of material. | Implements most chapter concepts but with some gaps or inconsistencies. Shows developing understanding but needs refinement. | Limited or incorrect implementation of chapter concepts. Doesn't demonstrate understanding of core material. |
| **Code Quality & Modern C++** | Exceptional organization, clear naming, appropriate modern C++ features. Code is maintainable and follows best practices consistently. | Well-organized code with good structure. Uses modern C++ features appropriately. Clear and readable with reasonable practices. | Code works but organization could improve. Inconsistent use of modern features. Shows understanding but lacks polish. | Poor organization, minimal use of modern C++ features. Difficult to read and understand. Basic functionality only. |
| **Problem-Solving & Verification** | Clear evidence of systematic approach. Handles edge cases and error conditions. Shows thorough verification of results with multiple test scenarios. | Good problem-solving approach with reasonable error handling. Shows evidence of testing and verification of functionality. | Basic problem-solving evident but limited error handling. Some testing done but not comprehensive. Shows developing verification skills. | Little evidence of systematic approach. Minimal error handling or testing. No clear verification strategy demonstrated. |

**Note**: This rubric applies to the entire assignment including all three problem sets (Function Templates, Class Templates, Advanced Templates).

## Time Allocation
- **Problem Set 1**: 45 minutes
- **Problem Set 2**: 45 minutes
- **Problem Set 3**: 45 minutes
- **Total**: 2.25 hours
