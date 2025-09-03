# HW_14: Iterators and Algorithms

## Overview
This assignment explores iterators and STL algorithms as covered in Chapter 14 of "C++ Crash Course".

## Related Module
📚 **[Module 13 - Chapter 14: Iterators](../)**

## Learning Objectives
- Master iterator categories and their capabilities
- Understand iterator adapters and ranges
- Implement custom iterators for user-defined containers
- Apply STL algorithms with different iterator types
- Use algorithm composition for complex data processing

## Assignment Tasks
Complete THREE problem sets (2.25 hours total):

### Problem Set 1: Iterator Fundamentals (45 minutes)
1. **Iterator Categories**: Input, output, forward, bidirectional, random access
2. **Iterator Operations**: Advance, distance, and navigation
3. **Range-Based Access**: begin(), end(), and range loops

### Problem Set 2: STL Algorithms (45 minutes)
1. **Non-Modifying Algorithms**: find, count, search, equal
2. **Modifying Algorithms**: copy, transform, replace, remove
3. **Sorting Algorithms**: sort, stable_sort, partial_sort, nth_element

### Problem Set 3: Custom Iterators and Advanced Usage (45 minutes)
1. **Iterator Adapters**: reverse, insert, stream iterators
2. **Custom Iterator Implementation**: For user-defined containers
3. **Algorithm Composition**: Combining algorithms for complex operations

## Building and Testing
```bash
mkdir build && cd build
cmake ..
make
./iterators_demo
make test
```

## Grading Criteria
- [ ] Correct iterator usage for different container types
- [ ] Effective STL algorithm application
- [ ] Custom iterator implementation
- [ ] Understanding of iterator categories
- [ ] Algorithm composition and chaining

## Time Allocation
- **Problem Set 1**: 45 minutes
- **Problem Set 2**: 45 minutes
- **Problem Set 3**: 45 minutes
- **Total**: 2.25 hours