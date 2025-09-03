# HW_13: Containers and STL

## Overview
This assignment explores STL containers and their usage patterns as covered in Chapter 13 of "C++ Crash Course".

## Related Module
📚 **[Module 12 - Chapter 13: Containers](../)**

## Learning Objectives
- Master sequence containers (vector, deque, list)
- Understand associative containers (set, map, multiset, multimap)
- Use unordered containers (unordered_set, unordered_map)
- Apply container selection criteria for performance
- Implement iterator usage with containers

## Assignment Tasks
Complete THREE problem sets (2.25 hours total):

### Problem Set 1: Sequence Containers (45 minutes)
1. **std::vector**: Dynamic arrays and memory management
2. **std::deque**: Double-ended queues for efficient insertion
3. **std::list**: Doubly-linked lists for splice operations

### Problem Set 2: Associative Containers (45 minutes)
1. **std::set/multiset**: Ordered unique/duplicate elements
2. **std::map/multimap**: Key-value pairs with ordering
3. **Container Operations**: Insert, find, erase, and iteration

### Problem Set 3: Unordered Containers and Performance (45 minutes)
1. **std::unordered_set/map**: Hash-based containers
2. **Performance Comparison**: When to use each container type
3. **Custom Comparators**: Sorting and hashing customization

## Building and Testing
```bash
mkdir build && cd build
cmake ..
make
./containers_demo
make test
```

## Grading Criteria
- [ ] Correct container selection for different use cases
- [ ] Efficient container operations
- [ ] Proper iterator usage
- [ ] Understanding of performance characteristics
- [ ] Custom comparator implementation

## Time Allocation
- **Problem Set 1**: 45 minutes
- **Problem Set 2**: 45 minutes
- **Problem Set 3**: 45 minutes
- **Total**: 2.25 hours