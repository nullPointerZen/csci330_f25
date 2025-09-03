# Chapter 13: Containers - Quick Help Guide

**For students with Python/Java background learning C++ STL containers and their performance characteristics**

---

## 🚨 Most Common Mistakes

### 1. Wrong Container Choice for Use Case
```cpp
// WRONG - Using vector for frequent front insertion
std::vector<int> vec;
for (int i = 0; i < 1000; ++i) {
    vec.insert(vec.begin(), i);  // O(n) each time - very slow!
}

// RIGHT - Use deque for front insertion
std::deque<int> deq;
for (int i = 0; i < 1000; ++i) {
    deq.push_front(i);  // O(1) each time - fast!
}

// WRONG - Using list for random access
std::list<int> lst;
// ... fill list ...
int value = lst[10];  // Compilation error! No operator[]

// RIGHT - Use vector/deque for random access
std::vector<int> vec;
// ... fill vector ...
int value = vec[10];  // O(1) random access
```

### 2. Iterator Invalidation
```cpp
// DANGEROUS - Iterator invalidation
std::vector<int> vec{1, 2, 3, 4, 5};
for (auto it = vec.begin(); it != vec.end(); ++it) {
    if (*it % 2 == 0) {
        vec.erase(it);  // Invalidates iterator! Undefined behavior!
    }
}

// SAFE - Update iterator after erase
for (auto it = vec.begin(); it != vec.end();) {
    if (*it % 2 == 0) {
        it = vec.erase(it);  // erase returns next valid iterator
    } else {
        ++it;
    }
}

// BETTER - Use std::remove_if + erase
vec.erase(
    std::remove_if(vec.begin(), vec.end(), 
                   [](int x) { return x % 2 == 0; }),
    vec.end()
);
```

### 3. Unnecessary Container Copies
```cpp
// SLOW - Copies entire vector
void process(std::vector<int> vec) {  // Pass by value = copy
    for (int x : vec) { /* ... */ }
}

// FAST - Pass by const reference
void process(const std::vector<int>& vec) {  // No copy
    for (int x : vec) { /* ... */ }
}

// FAST - Pass iterators (most flexible)
template<typename Iterator>
void process(Iterator begin, Iterator end) {
    for (auto it = begin; it != end; ++it) { /* ... */ }
}
```

---

## 📋 Container Selection Guide

### Sequence Containers

| Container | Use When | Strengths | Weaknesses |
|-----------|----------|-----------|------------|
| **std::vector** | Default choice, random access, back insertion | Fast random access, cache-friendly, small overhead | Slow front/middle insertion, reallocation |
| **std::deque** | Front and back insertion, random access | Fast front/back ops, no reallocation, random access | More memory overhead, not cache-friendly |
| **std::list** | Frequent middle insertion/deletion | Fast insertion/deletion anywhere, stable iterators | No random access, high memory overhead |
| **std::forward_list** | Memory-critical singly-linked operations | Minimal memory, fast front operations | No back operations, forward iteration only |
| **std::array** | Fixed-size, stack allocation | No heap allocation, minimal overhead | Fixed size, no dynamic growth |

### Associative Containers

| Container | Use When | Complexity | Ordering |
|-----------|----------|------------|----------|
| **std::set/map** | Ordered unique keys | O(log n) | Sorted by key |
| **std::multiset/multimap** | Ordered duplicate keys | O(log n) | Sorted by key |
| **std::unordered_set/map** | Fast lookup, no ordering | O(1) average | No ordering |
| **std::unordered_multiset/multimap** | Fast lookup, duplicates | O(1) average | No ordering |

### Container Adapters

| Adapter | Underlying | Use When |
|---------|------------|----------|
| **std::stack** | deque, vector, list | LIFO operations |
| **std::queue** | deque, list | FIFO operations |
| **std::priority_queue** | vector, deque | Priority-based access |

---

## ⚡ Performance Characteristics Quick Reference

### Time Complexity Summary
```cpp
// Vector operations
vec.push_back()      // O(1) amortized
vec.insert(begin)    // O(n) - shifts all elements
vec[i]              // O(1) - random access
vec.erase(it)       // O(n) - shifts remaining elements

// Deque operations  
deq.push_front()    // O(1)
deq.push_back()     // O(1)
deq[i]              // O(1) - random access
deq.insert(middle)  // O(n)

// List operations
lst.push_front()    // O(1)
lst.push_back()     // O(1)
lst.insert(it, val) // O(1) - if you have iterator
lst.splice()        // O(1) - move elements between lists

// Set/Map operations (red-black tree)
set.insert()        // O(log n)
set.find()          // O(log n)
set.erase()         // O(log n)

// Unordered Set/Map operations (hash table)
uset.insert()       // O(1) average, O(n) worst case
uset.find()         // O(1) average, O(n) worst case
uset.erase()        // O(1) average
```

### Memory Layout and Cache Performance
```cpp
// CACHE-FRIENDLY: Contiguous memory
std::vector<int> vec;      // All elements in one memory block
std::array<int, 100> arr;  // Stack-allocated contiguous block

// LESS CACHE-FRIENDLY: Non-contiguous 
std::deque<int> deq;       // Multiple memory blocks
std::list<int> lst;        // Each element separately allocated
std::set<int> s;           // Tree nodes scattered in memory
```

---

## 🔧 Common Container Patterns

### Vector Best Practices
```cpp
// 1. Reserve capacity when size is known
std::vector<int> vec;
vec.reserve(expected_size);  // Prevents reallocations
for (int i = 0; i < expected_size; ++i) {
    vec.push_back(i);
}

// 2. Use emplace_back for complex objects
std::vector<std::string> strings;
strings.emplace_back("Hello");        // Constructs in place
strings.push_back(std::string("Hi")); // Constructs temporary, then moves

// 3. Shrink to fit after removing many elements
vec.erase(vec.begin() + 100, vec.end());  // Remove many elements
vec.shrink_to_fit();  // Reduce capacity to size

// 4. Use data() for C API interop
int* raw_array = vec.data();
c_function(raw_array, vec.size());
```

### Map/Set Usage Patterns
```cpp
// 1. Use count() to check existence (returns 0 or 1 for unique containers)
if (my_set.count(key)) {
    // key exists
}

// 2. Use find() when you need the element
auto it = my_map.find(key);
if (it != my_map.end()) {
    // Use it->first (key) and it->second (value)
}

// 3. Use insert() return value
auto [iterator, inserted] = my_map.insert({key, value});
if (inserted) {
    // New element was inserted
} else {
    // Element already existed
}

// 4. Use emplace for efficiency
my_map.emplace(key, value);  // Constructs in place
my_set.emplace(args...);     // Constructs object directly in container
```

### Unordered Container Configuration
```cpp
// Custom hash function
struct CustomHash {
    std::size_t operator()(const MyType& obj) const {
        return std::hash<std::string>{}(obj.get_key());
    }
};

// Custom equality
struct CustomEqual {
    bool operator()(const MyType& a, const MyType& b) const {
        return a.get_key() == b.get_key();
    }
};

std::unordered_set<MyType, CustomHash, CustomEqual> my_set;

// Load factor management
std::unordered_map<int, std::string> map;
map.reserve(expected_size);        // Pre-allocate buckets
map.max_load_factor(0.75);         // Control when to rehash
```

---

## 🔍 Iterator Categories and Usage

### Iterator Category Hierarchy
```cpp
// Input Iterator: Can read, single-pass
std::istream_iterator<int> input(std::cin);

// Forward Iterator: Can read/write, multi-pass
std::forward_list<int>::iterator forward_it;

// Bidirectional Iterator: Can go forward/backward
std::list<int>::iterator bidir_it;
--bidir_it;  // Can decrement

// Random Access Iterator: Can jump to any position
std::vector<int>::iterator random_it;
random_it += 5;        // Can add/subtract
random_it[3];          // Can subscript
```

### Iterator Invalidation Rules
```cpp
// Vector iterator invalidation
std::vector<int> vec;
auto it = vec.begin();

vec.push_back(42);     // May invalidate ALL iterators (if reallocation)
vec.insert(it, 10);    // Invalidates iterators from insertion point onward
vec.erase(it);         // Invalidates iterators from erase point onward
vec.clear();           // Invalidates ALL iterators

// List iterator invalidation
std::list<int> lst;
auto it = lst.begin();

lst.push_back(42);     // No iterators invalidated
lst.insert(it, 10);    // No iterators invalidated
lst.erase(it);         // Only the erased iterator invalidated
```

### Safe Iterator Usage
```cpp
// Pattern 1: Update iterator after modification
for (auto it = container.begin(); it != container.end();) {
    if (should_remove(*it)) {
        it = container.erase(it);  // Get next valid iterator
    } else {
        ++it;
    }
}

// Pattern 2: Use algorithms
container.erase(
    std::remove_if(container.begin(), container.end(), predicate),
    container.end()
);

// Pattern 3: Reverse iteration for safe deletion
for (auto it = container.rbegin(); it != container.rend(); ++it) {
    if (should_remove(*it)) {
        container.erase(std::next(it).base());  // Convert reverse to forward
    }
}
```

---

## 💡 Algorithm Integration

### Common STL Algorithms with Containers
```cpp
#include <algorithm>

std::vector<int> vec{5, 2, 8, 1, 9};

// Sorting
std::sort(vec.begin(), vec.end());
std::sort(vec.begin(), vec.end(), std::greater<int>{});  // Descending

// Searching  
auto it = std::find(vec.begin(), vec.end(), 5);
auto it = std::binary_search(vec.begin(), vec.end(), 5);  // Sorted containers only

// Modifying
std::transform(vec.begin(), vec.end(), vec.begin(), 
               [](int x) { return x * 2; });
               
std::replace(vec.begin(), vec.end(), 5, 50);

// Removing
vec.erase(std::unique(vec.begin(), vec.end()), vec.end());  // Remove duplicates

// Counting and conditions
auto count = std::count_if(vec.begin(), vec.end(), 
                          [](int x) { return x > 5; });
                          
bool all_positive = std::all_of(vec.begin(), vec.end(),
                               [](int x) { return x > 0; });
```

### Container-Specific Optimizations
```cpp
// For lists: use member functions instead of algorithms
std::list<int> lst;
lst.sort();           // Better than std::sort (which requires random access)
lst.unique();         // Better than std::unique + erase
lst.remove_if(pred);  // Better than std::remove_if + erase

// For sets/maps: use member functions
std::set<int> s;
s.erase(value);       // Better than std::remove + erase
auto count = s.count(value);  // Better than std::count

// For vectors: prefer algorithms
std::vector<int> vec;
std::sort(vec.begin(), vec.end());  // Efficient for random access iterators
```

---

## ⚠️ Performance Tips

### Vector Optimization
```cpp
// 1. Reserve capacity
std::vector<Type> vec;
vec.reserve(estimated_size);  // Prevent reallocations

// 2. Use emplace operations
vec.emplace_back(constructor_args);  // Better than push_back for complex types

// 3. Consider data() for performance-critical code
Type* raw_ptr = vec.data();  // Direct memory access
// Use with caution - no bounds checking!

// 4. Minimize reallocations
if (vec.size() == vec.capacity()) {
    vec.reserve(vec.capacity() * 2);  // Explicit growth strategy
}
```

### Map vs Unordered_Map
```cpp
// Use std::map when:
// - Need ordered iteration
// - Stable performance (guaranteed O(log n))
// - Small datasets (< 100 elements)

// Use std::unordered_map when:
// - Only need lookup, not ordering
// - Large datasets (> 1000 elements)
// - Can provide good hash function
// - Acceptable worst-case O(n) behavior

// Benchmark when in doubt!
```

---

## 🆘 Emergency Syntax Reference

### Container Creation
```cpp
// Vector
std::vector<int> vec{1, 2, 3};
std::vector<int> vec(size, value);
std::vector<int> vec(other.begin(), other.end());

// Map
std::map<int, std::string> map{{1, "one"}, {2, "two"}};
std::unordered_map<int, std::string> umap{{1, "one"}, {2, "two"}};

// Set
std::set<int> s{1, 2, 3};
std::unordered_set<int> us{1, 2, 3};
```

### Common Operations
```cpp
// Size and capacity
container.size()        // Current number of elements
container.empty()       // True if size() == 0
container.max_size()    // Maximum possible size

// Vector specific
vec.capacity()          // Allocated space
vec.reserve(n)          // Ensure capacity >= n
vec.shrink_to_fit()     // Reduce capacity to size

// Access
container.front()       // First element
container.back()        // Last element
container[index]        // Direct access (vector/deque/array only)
container.at(index)     // Bounds-checked access

// Modification
container.push_back(val)     // Add to end
container.emplace_back(args) // Construct at end
container.pop_back()         // Remove from end
container.insert(it, val)    // Insert at iterator
container.erase(it)          // Remove at iterator
container.clear()            // Remove all elements
```

**Remember**: Choose containers based on your access patterns and performance requirements. When in doubt, profile your code to make informed decisions!