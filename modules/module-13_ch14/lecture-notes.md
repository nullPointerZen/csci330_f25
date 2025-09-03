# Chapter 14: Iterators - Complete Guide

## 📖 Learning Sequence (IMPORTANT!)

**🔄 How This Chapter Works:**
1. **📚 FIRST**: Read Textbook Chapter 14 "Iterators" (2-3 hours)
2. **🔍 SECOND**: Work through these lecture notes for hands-on practice (3-4 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 14 "Iterators" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Master** iterator categories and their capabilities
2. **Apply** STL algorithms with appropriate iterators
3. **Implement** custom iterators for user-defined containers
4. **Design** algorithm composition for complex data processing
5. **Optimize** code using iterator-based algorithms
6. **Debug** iterator-related issues and invalidation problems

**⏱️ Time Budget:**
- **📚 Textbook Reading: 2-3 hours** (Chapter 14: "Iterators" - REQUIRED FIRST)
- **💻 Hands-on Work: 4-5 hours** (course materials + assignments + debugging)
- **📖 Note: Reading time is separate and must be completed BEFORE hands-on work**

## 🧠 Key Concepts Summary

### **1. Iterator Categories**
- **Input Iterator**: Single-pass, read-only (istream_iterator)
- **Output Iterator**: Single-pass, write-only (ostream_iterator)
- **Forward Iterator**: Multi-pass, forward movement (forward_list)
- **Bidirectional Iterator**: Forward and backward (list, set, map)
- **Random Access Iterator**: Jump to any position (vector, deque, array)

### **2. Iterator Operations**
- **std::advance()**: Move iterator by n positions
- **std::distance()**: Calculate distance between iterators
- **std::next()/std::prev()**: Get iterator n positions away
- **Range-based access**: begin(), end(), cbegin(), cend()

### **3. Iterator Adapters**
- **Reverse iterators**: rbegin(), rend() for backward traversal
- **Insert iterators**: back_inserter, front_inserter, inserter
- **Stream iterators**: istream_iterator, ostream_iterator

### **4. STL Algorithms**
- **Non-modifying**: find, count, search, equal, mismatch
- **Modifying**: copy, transform, replace, remove, unique
- **Sorting**: sort, stable_sort, partial_sort, nth_element
- **Binary search**: lower_bound, upper_bound, binary_search

## 💻 Algorithm Categories and Usage

### **Searching Algorithms**
```cpp
// Finding elements
auto it = std::find(vec.begin(), vec.end(), target);
auto count = std::count_if(vec.begin(), vec.end(), predicate);

// Binary search (requires sorted range)
bool found = std::binary_search(sorted_vec.begin(), sorted_vec.end(), target);
auto lower = std::lower_bound(sorted_vec.begin(), sorted_vec.end(), target);
```

### **Transformation Algorithms**
```cpp
// Transform elements
std::transform(input.begin(), input.end(), output.begin(), 
               [](int x) { return x * 2; });

// Copy with condition
std::copy_if(source.begin(), source.end(), std::back_inserter(dest),
             [](int x) { return x > 0; });
```

### **Sorting and Ordering**
```cpp
// Various sorting algorithms
std::sort(vec.begin(), vec.end());  // Fastest general sorting
std::stable_sort(vec.begin(), vec.end(), comparator);  // Stable sorting
std::partial_sort(vec.begin(), vec.begin() + 10, vec.end());  // Top 10 elements
```

## 🔧 Custom Iterator Implementation

### **Basic Iterator Pattern**
```cpp
class SimpleIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    
    // Constructor, copy, assignment
    // Dereference: operator*(), operator->()
    // Increment: operator++() (pre and post)
    // Comparison: operator==(), operator!=()
};
```

### **Iterator Traits**
- Required type definitions for STL compatibility
- Enable algorithm optimization based on iterator category
- Support for generic programming patterns

## 💻 Practical Applications

### **Algorithm Composition**
```cpp
// Complex data processing pipeline
std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Filter even numbers, square them, and sort
std::vector<int> result;
std::copy_if(data.begin(), data.end(), std::back_inserter(result),
             [](int x) { return x % 2 == 0; });
std::transform(result.begin(), result.end(), result.begin(),
               [](int x) { return x * x; });
std::sort(result.begin(), result.end(), std::greater<int>());
```

### **Range-Based Processing**
```cpp
// Modern C++ range-based approaches
for (const auto& element : container) {
    // Process element
}

// Iterator-based equivalent
for (auto it = container.begin(); it != container.end(); ++it) {
    const auto& element = *it;
    // Process element
}
```

## 🔧 Common Patterns and Pitfalls

### **Best Practices**
- Use algorithms instead of manual loops when possible
- Choose most restrictive iterator category that works
- Prefer const iterators when not modifying
- Use range-based for loops for simple iteration

### **Common Mistakes**
- Iterator invalidation after container modification
- Wrong iterator category for algorithms
- Off-by-one errors in iterator arithmetic
- Dereferencing end() iterators

### **Performance Considerations**
- Algorithms are often optimized better than manual loops
- Iterator category affects algorithm efficiency
- Random access iterators enable better algorithms
- Prefer algorithms that minimize iterator operations

### **Iterator Invalidation Rules**
- **vector**: Insert/erase may invalidate all iterators
- **deque**: Insert/erase at ends preserves iterators to other elements
- **list**: Only iterators to erased elements are invalidated
- **set/map**: Only iterators to erased elements are invalidated

## 📝 Before Next Chapter

Ensure you understand:
- Iterator categories and their capabilities
- How to compose algorithms for complex operations
- When to implement custom iterators
- Iterator invalidation rules for different containers

**Next Chapter Preview**: Chapter 15 covers strings and text processing, applying iterator concepts to text manipulation.