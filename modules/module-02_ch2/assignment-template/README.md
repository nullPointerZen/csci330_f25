# HW_02: Types and Memory

## Overview
This assignment explores C++ fundamental types, arrays, structs, and basic pointer operations as covered in Chapter 2 of "C++ Crash Course".

## Related Module
📚 **[Module 02 - Chapter 2: Types](../)**

## Learning Objectives
- Master fundamental C++ types and their sizes
- Understand type conversions (implicit and explicit)
- Work with arrays and demonstrate safe indexing
- Create and use structs to group data
- Explore basic pointer operations and memory addresses

## Assignment Tasks
Complete TWO comprehensive programs (3 hours total):

### Program 1: Type Explorer (90 minutes)
1. **Type Analysis**: Display sizes and ranges of fundamental types
2. **Type Conversions**: Demonstrate implicit/explicit conversions
3. **Practical Application**: Multi-unit converter (temperature, distance)
4. **Memory Behavior**: Show initialization and scope differences

### Program 2: Student Manager (90 minutes)
1. **Struct Design**: Create Student struct with multiple fields
2. **Array Operations**: Manage array of students with grades
3. **Pointer Arithmetic**: Process arrays using pointers
4. **Statistics**: Calculate averages and find min/max

## Building and Testing
```bash
mkdir build && cd build
cmake ..
make
./type_explorer    # Run first program
./student_manager  # Run second program
make test
```

## Submission Guidelines
1. Complete all TODO items in the source code
2. Ensure your program compiles without warnings
3. Test your program with various inputs
4. Follow the naming convention: `CSCI330_FirstName_LastName`

## Assignment Rubric (16 Points Total)

This assignment will be evaluated using the following rubric:

| Criteria | Advanced (A) - 4 points | Proficient (P) - 3 points | Developing (D) - 2 points | Incomplete (I) - 1 point |
|----------|-------------------------|---------------------------|--------------------------|-------------------------|
| **Functionality & Requirements** | Code compiles and runs perfectly. All requirements met with edge cases handled. Demonstrates mastery of chapter concepts. | Code compiles and runs correctly. All main requirements met. Minor issues don't affect core functionality. Shows solid understanding. | Code compiles with warnings or has minor runtime issues. Most requirements met but some functionality missing or incomplete. | Code doesn't compile or has major functionality problems. Key requirements not met. Limited understanding evident. |
| **Concept Implementation** | Expertly implements chapter-specific concepts (types, arrays, structs, pointers). Shows deep understanding of when and why to use features. | Correctly implements chapter concepts with good understanding. Appropriate use of language features. Shows clear comprehension of material. | Implements most chapter concepts but with some gaps or inconsistencies. Shows developing understanding but needs refinement. | Limited or incorrect implementation of chapter concepts. Doesn't demonstrate understanding of core material. |
| **Code Quality & Modern C++** | Exceptional organization, clear naming, appropriate modern C++ features. Code is maintainable and follows best practices consistently. | Well-organized code with good structure. Uses modern C++ features appropriately. Clear and readable with reasonable practices. | Code works but organization could improve. Inconsistent use of modern features. Shows understanding but lacks polish. | Poor organization, minimal use of modern C++ features. Difficult to read and understand. Basic functionality only. |
| **Problem-Solving & Verification** | Clear evidence of systematic approach. Handles edge cases and error conditions. Shows thorough verification of results with multiple test scenarios. | Good problem-solving approach with reasonable error handling. Shows evidence of testing and verification of functionality. | Basic problem-solving evident but limited error handling. Some testing done but not comprehensive. Shows developing verification skills. | Little evidence of systematic approach. Minimal error handling or testing. No clear verification strategy demonstrated. |

**Note**: This rubric applies to the entire assignment including both programs (Type Explorer and Student Manager).

## Time Allocation
- **Type Explorer**: 90 minutes
- **Student Manager**: 90 minutes
- **Total**: 3 hours