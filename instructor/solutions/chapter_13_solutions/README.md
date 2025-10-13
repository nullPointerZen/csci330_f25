# Chapter 13 Solutions: STL Containers

This directory contains complete solutions for all Chapter 13 problems.

## Solution Files

### Problem Set 1: Container Basics and Sequence Containers
- `problem_1_1_vector_fundamentals.cpp` - Grade management system with vector operations
- `problem_1_2_dynamic_array_operations.cpp` - Student roster with insertions and deletions
- `problem_1_3_performance_comparison.cpp` - Vector vs list performance analysis

### Problem Set 2: Associative Containers  
- `problem_2_1_word_frequency.cpp` - Word frequency counter using map
- `problem_2_2_set_operations.cpp` - Set union, intersection, and difference operations
- `problem_2_3_student_database.cpp` - Multi-container student information system

### Problem Set 3: Unordered Containers and Integration
- `problem_3_1_hash_performance.cpp` - Performance comparison of map vs unordered_map
- `problem_3_2_custom_hash.cpp` - Custom hash function for Student objects
- `problem_3_3_library_system.cpp` - Complete library management system integration project

### Extra Credit Debugging Challenges
- `debug_challenge_solutions.cpp` - Fixed versions of the buggy code with explanations

## Compilation Instructions

All solutions can be compiled with:
```bash
g++ -std=c++17 -Wall -Wextra -O2 filename.cpp -o executable_name
```

Or using the provided Makefile:
```bash
make all          # Compile all solutions
make problem_1_1  # Compile specific problem
make clean        # Remove executables
```

## Learning Notes

Each solution includes:
- Detailed comments explaining the approach
- Performance analysis where relevant
- Connections to Python/Java equivalents
- Best practices and common pitfalls avoided