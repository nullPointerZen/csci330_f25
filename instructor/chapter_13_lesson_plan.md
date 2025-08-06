# Chapter 13: STL Containers - Lesson Plan

**Target Audience**: Students with Python/Java experience  
**Time Budget**: 2.5 hours maximum  
**Prerequisites**: Chapters 1-12 (basic programming, types, references, object lifecycle, polymorphism, templates, expressions, control flow, functions, testing, smart pointers, utility classes)

## Development Environment Setup
**Continue using your chosen workflow from previous chapters:**
- **Option A**: Docker + Command Line
- **Option B**: VS Code + Docker (excellent for STL container visualization)
- **Option C**: VS Code + Local Compiler

**For Chapter 13's containers, debugger shows internal structure and performance characteristics!**

---

## Learning Objectives
By the end of this chapter, students will be able to:
1. Choose appropriate STL containers for different use cases
2. Use vector, list, map, set, and their unordered variants effectively
3. Understand performance characteristics of different containers
4. Apply container operations (insertion, deletion, searching, iteration)
5. Connect C++ containers to familiar Python/Java collections

## Chapter Overview (150 minutes total)

### Part 1: Container Fundamentals (30 minutes)

#### What are STL Containers? (10 minutes)
- Definition: Objects that store collections of other objects
- Comparison to Python lists, dicts, sets and Java ArrayList, HashMap, HashSet
- Key advantages: Type safety, performance, memory management
- Categories: Sequence containers, associative containers, unordered containers

#### Common Container Interface (20 minutes)
- Iterators: C++'s version of Python iterators
- Size operations: `size()`, `empty()`, `max_size()`
- Basic operations all containers share
- RAII and automatic memory management

**Hands-on**: Simple vector creation and basic operations

### Part 2: Sequence Containers (45 minutes)

#### std::vector - The Python List Equivalent (25 minutes)
**Connection to Python/Java**: Like Python's `list` or Java's `ArrayList`

Core concepts:
- Dynamic array with automatic resizing
- Random access: O(1) indexing like `my_list[5]`
- Push/pop operations: `push_back()`, `pop_back()`
- Memory layout: contiguous storage for cache efficiency

```cpp
std::vector<int> numbers;           // Python: numbers = []
numbers.push_back(42);              // Python: numbers.append(42)
numbers[0] = 10;                    // Python: numbers[0] = 10
int size = numbers.size();          // Python: size = len(numbers)
```

Common operations:
- Construction and initialization
- Element access: `at()` vs `[]`
- Insertion and deletion: `insert()`, `erase()`
- Iteration patterns

Performance characteristics:
- Access: O(1)
- Insertion at end: O(1) amortized
- Insertion elsewhere: O(n)

#### std::list - The Linked List (20 minutes)
**Connection to Python/Java**: Similar to Python's collections.deque or Java's LinkedList

When to use:
- Frequent insertions/deletions in middle
- No random access needed
- Better than vector for large objects

```cpp
std::list<std::string> names;
names.push_front("Alice");          // Efficient at both ends
names.push_back("Bob");
```

Performance comparison with vector:
- Access: O(n) vs O(1)
- Insertion: O(1) vs O(n)

**Hands-on**: Implement a simple playlist using vector and list, compare performance

### Part 3: Associative Containers (50 minutes)

#### std::map - The Python Dictionary (25 minutes)
**Connection to Python/Java**: Like Python's `dict` or Java's `TreeMap`

Core concepts:
- Key-value pairs stored in sorted order
- Automatic sorting by key
- Logarithmic operations

```cpp
std::map<std::string, int> ages;    // Python: ages = {}
ages["Alice"] = 25;                 // Python: ages["Alice"] = 25
ages.insert({"Bob", 30});           // Python: ages["Bob"] = 30

if (ages.find("Alice") != ages.end()) {  // Python: if "Alice" in ages:
    std::cout << ages["Alice"];          //     print(ages["Alice"])
}
```

Key operations:
- Insertion: `[]` operator vs `insert()`
- Search: `find()`, `count()`
- iteration: range-based for loops

#### std::set - The Python Set (25 minutes)
**Connection to Python/Java**: Like Python's `set` or Java's `TreeSet`

Unique elements in sorted order:
```cpp
std::set<int> unique_numbers;       // Python: unique_numbers = set()
unique_numbers.insert(5);           // Python: unique_numbers.add(5)
unique_numbers.insert(3);           // Python: unique_numbers.add(3)
unique_numbers.insert(5);           // Duplicate ignored
```

Set operations:
- Union, intersection (using algorithms)
- Fast membership testing

**Hands-on**: Build a word frequency counter using map

### Part 4: Unordered Containers (35 minutes)

#### Hash Tables: unordered_map and unordered_set (35 minutes)
**Connection to Python/Java**: Like Python's `dict`/`set` or Java's `HashMap`/`HashSet`

When to prefer unordered over ordered:
- Don't need sorting
- Want average O(1) operations instead of O(log n)
- Similar performance to Python dictionaries

```cpp
std::unordered_map<std::string, int> scores;  // Python: scores = {}
scores["Alice"] = 95;                         // Same syntax as map
```

Performance comparison:
- map: O(log n) operations, sorted order
- unordered_map: O(1) average operations, no order

Hash function requirements and custom types

**Hands-on**: Compare performance of map vs unordered_map for large datasets

### Part 5: Choosing the Right Container (10 minutes)

#### Decision Matrix
| Need | Container | Python/Java Equivalent |
|------|-----------|----------------------|
| Ordered sequence | vector | list/ArrayList |
| Frequent insert/delete | list | deque/LinkedList |
| Key-value pairs (sorted) | map | OrderedDict/TreeMap |
| Key-value pairs (fast) | unordered_map | dict/HashMap |
| Unique elements (sorted) | set | OrderedSet/TreeSet |
| Unique elements (fast) | unordered_set | set/HashSet |

#### Performance Summary
- Access patterns matter
- Memory usage considerations  
- Cache locality importance

## Practical Exercises Throughout

### Exercise 1: Container Comparison (Part 2)
Students implement the same functionality using vector and list, measure performance differences.

### Exercise 2: Word Analysis (Part 3)  
Build a program that reads text and reports:
- Word frequency (using map)
- Unique words (using set)
- Compare with unordered versions

### Exercise 3: Data Processing Pipeline (Part 5)
Given a realistic scenario, students choose appropriate containers and justify their choices.

## Key Takeaways
1. **Familiarity**: C++ containers are similar to Python/Java collections but with explicit type safety
2. **Performance**: Understanding Big O complexity helps choose the right container
3. **Memory Management**: Containers handle memory automatically via RAII
4. **Iteration**: Range-based for loops make containers easy to use
5. **Choice Matters**: Different containers have different performance characteristics

## Common Gotchas for Python/Java Developers
- Vector vs list performance characteristics
- Iterator invalidation
- Difference between `[]` and `at()` for bounds checking
- Understanding when rehashing occurs in unordered containers

## Assessment Preparation
Students should be comfortable:
- Selecting appropriate containers for given scenarios
- Writing code using all five main container types
- Explaining performance trade-offs
- Converting between Python/Java collections and C++ containers conceptually