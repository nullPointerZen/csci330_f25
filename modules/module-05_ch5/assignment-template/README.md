# HW_05: Runtime Polymorphism

## Overview
This assignment explores inheritance, virtual functions, and runtime polymorphism as covered in Chapter 5 of "C++ Crash Course".

## Related Module
📚 **[Module 05 - Chapter 5: Runtime Polymorphism](../)**

## Learning Objectives
- Create polymorphic class hierarchies using virtual functions
- Implement abstract base classes with pure virtual functions
- Use the override keyword for safe function overriding
- Apply polymorphism through base class pointers and references
- Design flexible systems using runtime polymorphism

## Assignment Tasks
Complete THREE problem sets (2.25 hours total):

### Problem Set 1: Basic Inheritance (45 minutes)
1. **Animal Hierarchy**: Base Animal class with virtual functions
2. **Shape System**: Abstract Shape with Circle, Rectangle, Triangle
3. **Virtual Destructors**: Proper cleanup in hierarchies

### Problem Set 2: Advanced Polymorphism (45 minutes)
1. **Game Characters**: RPG character system with abilities
2. **UI Components**: Button, TextBox, Slider with events
3. **Plugin System**: Dynamic loading of behaviors

### Problem Set 3: Practical Applications (45 minutes)
1. **Employee Management**: Different employee types with salary calculation
2. **Drawing Application**: Polymorphic shapes with rendering
3. **Command Pattern**: Undo/redo with virtual execute()

## Building and Testing
```bash
mkdir build && cd build
cmake ..
make
./polymorphism_demo
make test
```

## Assignment Rubric (16 Points Total)

This assignment will be evaluated using the following rubric:

| Criteria | Advanced (A) - 4 points | Proficient (P) - 3 points | Developing (D) - 2 points | Incomplete (I) - 1 point |
|----------|-------------------------|---------------------------|--------------------------|-------------------------|
| **Functionality & Requirements** | Code compiles and runs perfectly. All requirements met with edge cases handled. Demonstrates mastery of chapter concepts. | Code compiles and runs correctly. All main requirements met. Minor issues don't affect core functionality. Shows solid understanding. | Code compiles with warnings or has minor runtime issues. Most requirements met but some functionality missing or incomplete. | Code doesn't compile or has major functionality problems. Key requirements not met. Limited understanding evident. |
| **Concept Implementation** | Expertly implements chapter-specific concepts (virtual functions, polymorphism, inheritance, abstract classes). Shows deep understanding of when and why to use features. | Correctly implements chapter concepts with good understanding. Appropriate use of language features. Shows clear comprehension of material. | Implements most chapter concepts but with some gaps or inconsistencies. Shows developing understanding but needs refinement. | Limited or incorrect implementation of chapter concepts. Doesn't demonstrate understanding of core material. |
| **Code Quality & Modern C++** | Exceptional organization, clear naming, appropriate modern C++ features. Code is maintainable and follows best practices consistently. | Well-organized code with good structure. Uses modern C++ features appropriately. Clear and readable with reasonable practices. | Code works but organization could improve. Inconsistent use of modern features. Shows understanding but lacks polish. | Poor organization, minimal use of modern C++ features. Difficult to read and understand. Basic functionality only. |
| **Problem-Solving & Verification** | Clear evidence of systematic approach. Handles edge cases and error conditions. Shows thorough verification of results with multiple test scenarios. | Good problem-solving approach with reasonable error handling. Shows evidence of testing and verification of functionality. | Basic problem-solving evident but limited error handling. Some testing done but not comprehensive. Shows developing verification skills. | Little evidence of systematic approach. Minimal error handling or testing. No clear verification strategy demonstrated. |

**Note**: This rubric applies to the entire assignment including all three problem sets (Shape Hierarchy, Advanced Polymorphism, Real-World Applications).

## Time Allocation
- **Problem Set 1**: 45 minutes
- **Problem Set 2**: 45 minutes
- **Problem Set 3**: 45 minutes
- **Total**: 2.25 hours