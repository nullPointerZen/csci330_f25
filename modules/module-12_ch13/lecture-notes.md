# Chapter 13: Containers - Complete Guide

## 📖 Learning Sequence (IMPORTANT!)

**🔄 How This Chapter Works:**
1. **📚 FIRST**: Read Textbook Chapter 13 "Containers" (2-3 hours)
2. **🔍 SECOND**: Work through these lecture notes for hands-on practice (3-4 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 13 "Containers" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Master** STL sequence containers (vector, deque, list) and their use cases
2. **Apply** associative containers (set, map) for sorted data
3. **Implement** unordered containers (unordered_set, unordered_map) for performance
4. **Choose** optimal containers based on operation requirements
5. **Understand** iterator invalidation and container-specific behaviors
6. **Optimize** container usage for different performance scenarios

**⏱️ Time Budget:**
- **📚 Textbook Reading: 2-3 hours** (Chapter 13: "Containers" - REQUIRED FIRST)
- **💻 Hands-on Work: 4-5 hours** (course materials + assignments + debugging)
- **📖 Note: Reading time is separate and must be completed BEFORE hands-on work**

## 🧠 Key Concepts Summary

### **1. Sequence Containers**
- **std::vector**: Dynamic array, best general-purpose container
- **std::deque**: Double-ended queue, efficient front/back insertion
- **std::list**: Doubly-linked list, efficient insertion/deletion anywhere
- **std::array**: Fixed-size array, compile-time bounds

### **2. Associative Containers**
- **std::set**: Sorted unique elements, O(log n) operations
- **std::multiset**: Sorted elements with duplicates allowed
- **std::map**: Sorted key-value pairs, O(log n) lookup
- **std::multimap**: Sorted key-value pairs with duplicate keys

### **3. Unordered Containers**
- **std::unordered_set**: Hash table for unique elements, O(1) average
- **std::unordered_map**: Hash table for key-value pairs, O(1) average
- **Hash functions**: Custom hashing for user-defined types
- **Load factor**: Performance tuning for hash containers

### **4. Container Adapters**
- **std::stack**: LIFO container adapter
- **std::queue**: FIFO container adapter
- **std::priority_queue**: Heap-based priority container

## 💻 Performance Characteristics

### **Operation Complexity Guide**
```
Container         | Insert Front | Insert Back | Insert Middle | Random Access | Search
------------------|--------------|-------------|---------------|---------------|--------
vector            | O(n)         | O(1)        | O(n)         | O(1)         | O(n)
deque             | O(1)         | O(1)        | O(n)         | O(1)         | O(n)
list              | O(1)         | O(1)        | O(1)         | O(n)         | O(n)
set/map           | O(log n)     | O(log n)    | O(log n)     | O(log n)     | O(log n)
unordered_set/map | O(1) avg     | O(1) avg    | O(1) avg     | O(1) avg     | O(1) avg
```

### **Memory Characteristics**
- **vector**: Contiguous memory, good cache locality
- **deque**: Segmented memory, good for front/back operations
- **list**: Scattered memory, overhead for node pointers
- **set/map**: Tree structure, moderate memory overhead
- **unordered**: Hash table, rehashing can cause temporary spikes

## 🔧 Container Selection Guidelines

### **Choose std::vector when:**
- General-purpose storage needed
- Random access required
- Cache performance is important
- Container size is relatively stable

### **Choose std::deque when:**
- Need efficient front and back insertion
- Random access still needed
- Don't need iterator/reference stability

### **Choose std::list when:**
- Frequent insertion/deletion in middle
- Iterator/reference stability required
- Don't need random access

### **Choose std::set/map when:**
- Need sorted data
- Frequent searching required
- Moderate insertion/deletion

### **Choose std::unordered_set/map when:**
- Fast lookup is critical
- Don't need sorted order
- Have good hash function

## 💻 Practical Applications

### **Container Usage Patterns**
```cpp
// Efficient container operations
std::vector<int> numbers;
numbers.reserve(1000);  // Avoid reallocations

// Custom comparators
std::set<Person, PersonComparator> people;
std::map<std::string, int, std::greater<std::string>> reverse_map;

// Unordered containers with custom hash
std::unordered_map<Person, int, PersonHash> person_ages;
```

### **Iterator Safety**
```cpp
// Safe iteration with modification
for (auto it = container.begin(); it != container.end(); ) {
    if (should_remove(*it)) {
        it = container.erase(it);  // Update iterator
    } else {
        ++it;
    }
}
```

## 🔧 Common Patterns and Pitfalls

### **Best Practices**
- Reserve capacity for vectors when size is known
- Use emplace operations for in-place construction
- Prefer range-based for loops when possible
- Choose appropriate container for your use case

### **Common Mistakes**
- Using vector when frequent front insertion needed
- Not reserving vector capacity for known sizes
- Iterator invalidation after container modifications
- Using wrong container for performance-critical code

### **Memory Management**
- Containers automatically manage element memory
- shrink_to_fit() to reduce memory usage
- clear() vs. container assignment for reuse

## 📝 Before Next Chapter

Ensure you understand:
- Performance characteristics of each container type
- When to use ordered vs. unordered containers
- Iterator invalidation rules
- Custom comparators and hash functions

**Next Chapter Preview**: Chapter 14 covers iterators and STL algorithms, building on container knowledge.