# HW_01: Introduction to C++ - Problem Sets

## Overview
Complete the problem sets from Module 1 Chapter 1, demonstrating basic C++ programming concepts including program structure, functions, and control flow.

## Related Module
📚 **[Module 01 - Chapter 1: Up and Running](../)**

## Assignment Requirements
Complete all problem sets as detailed in the module assignments:

### Problem Set 1: Getting Started (30 minutes)
- **Problem 1.1**: Your First Program - Basic program structure
- **Problem 1.2**: Fix the Errors - Understanding compilation
- **Problem 1.3**: Compilation Practice - Compile-run cycle

### Problem Set 2: Basic Programming (45 minutes)  
- **Problem 2.1**: Temperature Converter - Variables and arithmetic
- **Problem 2.2**: Simple Function - Function creation and calling
- **Problem 2.3**: Basic Decisions - If-else statements

### Problem Set 3: Mini Calculator Project (60 minutes)
- **Problem 3.1**: Calculator Functions - Combining concepts
- **Problem 3.2**: Add Error Checking - Handle edge cases  
- **Problem 3.3**: Test Your Calculator - Verification

## File Organization
Organize your solutions in this structure:
```
CSCI330_FirstName_LastName/
└── week01/
    ├── problem_set_1/
    │   ├── problem_1_1.cpp
    │   ├── problem_1_2.cpp
    │   └── problem_1_3.cpp
    ├── problem_set_2/
    │   ├── problem_2_1.cpp
    │   ├── problem_2_2.cpp
    │   └── problem_2_3.cpp
    ├── problem_set_3/
    │   ├── problem_3_1.cpp
    │   ├── problem_3_2.cpp
    │   └── problem_3_3.cpp
    └── README.md (with compilation notes)
```

## Building and Testing
```bash
# Copy template to your directory first
mkdir -p assignments/CSCI330_FirstName_LastName/week01
cp -r modules/module-01_ch1/assignment-template/* assignments/CSCI330_FirstName_LastName/week01/

# Navigate to your directory
cd assignments/CSCI330_FirstName_LastName/week01

# Build (if using the starter template structure)
mkdir build && cd build
cmake ..
make
make test
```

## Submission Process

### Step 1: Complete Your Work
- Follow the file organization above
- Include compilation notes in your README.md
- Test all programs thoroughly

### Step 2: Create Branch and Submit
```bash
# Create feature branch for this assignment
git checkout -b week01-submission

# Add your completed work
git add assignments/CSCI330_FirstName_LastName/week01/
git commit -m "Complete HW_01: Chapter 1 Problem Sets"

# Push and create Pull Request
git push -u origin week01-submission
```

### Step 3: Submit to Canvas
**Canvas Submission**: Submit the link to your completed assignment directory:
```
https://github.com/YourUsername/csci330_f25/tree/main/assignments/CSCI330_FirstName_LastName/week01
```

**Example**: `https://github.com/jsmith/csci330_f25/tree/main/assignments/CSCI330_John_Smith/week01`

## Assignment Rubric (16 Points Total)

This assignment will be evaluated using the following rubric:

| Criteria | Advanced (A) - 4 points | Proficient (P) - 3 points | Developing (D) - 2 points | Incomplete (I) - 1 point |
|----------|-------------------------|---------------------------|--------------------------|-------------------------|
| **Functionality & Requirements** | Code compiles and runs perfectly. All requirements met with edge cases handled. Demonstrates mastery of chapter concepts. | Code compiles and runs correctly. All main requirements met. Minor issues don't affect core functionality. Shows solid understanding. | Code compiles with warnings or has minor runtime issues. Most requirements met but some functionality missing or incomplete. | Code doesn't compile or has major functionality problems. Key requirements not met. Limited understanding evident. |
| **Concept Implementation** | Expertly implements chapter-specific concepts (environment setup, basic C++). Shows deep understanding of when and why to use features. | Correctly implements chapter concepts with good understanding. Appropriate use of language features. Shows clear comprehension of material. | Implements most chapter concepts but with some gaps or inconsistencies. Shows developing understanding but needs refinement. | Limited or incorrect implementation of chapter concepts. Doesn't demonstrate understanding of core material. |
| **Code Quality & Modern C++** | Exceptional organization, clear naming, appropriate modern C++ features. Code is maintainable and follows best practices consistently. | Well-organized code with good structure. Uses modern C++ features appropriately. Clear and readable with reasonable practices. | Code works but organization could improve. Inconsistent use of modern features. Shows understanding but lacks polish. | Poor organization, minimal use of modern C++ features. Difficult to read and understand. Basic functionality only. |
| **Problem-Solving & Verification** | Clear evidence of systematic approach. Handles edge cases and error conditions. Shows thorough verification of results with multiple test scenarios. | Good problem-solving approach with reasonable error handling. Shows evidence of testing and verification of functionality. | Basic problem-solving evident but limited error handling. Some testing done but not comprehensive. Shows developing verification skills. | Little evidence of systematic approach. Minimal error handling or testing. No clear verification strategy demonstrated. |

**Note**: This rubric applies to the entire assignment including all three problem sets.
- [ ] Professional Git commit messages

## Time Expectation
**Total: 2.25 hours** for all three problem sets. If taking significantly longer, ask for help!