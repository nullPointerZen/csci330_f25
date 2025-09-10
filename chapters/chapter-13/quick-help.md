# Chapter 13: STL Containers - Quick Help Guide

## Quick Reference: Python/Java to C++ Container Translation

| Python | Java | C++ | Use Case |
|--------|------|-----|----------|
| `list` | `ArrayList` | `std::vector` | Dynamic array, random access |
| `collections.deque` | `LinkedList` | `std::list` | Frequent insert/delete in middle |
| `dict` | `HashMap` | `std::unordered_map` | Key-value pairs, fast lookup |
| `dict` (ordered) | `TreeMap` | `std::map` | Key-value pairs, sorted keys |
| `set` | `HashSet` | `std::unordered_set` | Unique elements, fast |
| `set` (ordered) | `TreeSet` | `std::set` | Unique elements, sorted |

---

## Essential Headers and Declarations

```cpp
#include <vector>       // for std::vector
#include <list>         // for std::list  
#include <map>          // for std::map
#include <set>          // for std::set
#include <unordered_map> // for std::unordered_map
#include <unordered_set> // for std::unordered_set
#include <algorithm>    // for find, sort, etc.
```

---

## Container Quick Start

### std::vector (like Python list)
```cpp
// Creation
std::vector<int> numbers;           // Empty vector
std::vector<int> nums = {1, 2, 3};  // Initialize with values
std::vector<int> zeros(10, 0);      // 10 elements, all zero

// Common operations
numbers.push_back(42);              // Python: numbers.append(42)
int first = numbers[0];             // Python: first = numbers[0]
int safe = numbers.at(0);           // Bounds-checked access
int size = numbers.size();          // Python: size = len(numbers)
bool empty = numbers.empty();       // Python: empty = len(numbers) == 0

// Iteration
for (const auto& num : numbers) {   // Python: for num in numbers:
    std::cout << num << " ";
}
```

### std::map (like Python dict with sorted keys)
```cpp
// Creation
std::map<std::string, int> ages;           // Python: ages = {}
std::map<std::string, int> scores = {      // Initialize with values
    {"Alice", 95}, {"Bob", 87}
};

// Common operations  
ages["Alice"] = 25;                        // Python: ages["Alice"] = 25
ages.insert({"Bob", 30});                  // Alternative insertion
int alice_age = ages["Alice"];             // Python: alice_age = ages["Alice"]

// Safe access (doesn't create if missing)
auto it = ages.find("Charlie");            // Python: if "Charlie" in ages:
if (it != ages.end()) {
    std::cout << it->second;               // Found!
}

// Iteration
for (const auto& [name, age] : ages) {     // Python: for name, age in ages.items():
    std::cout << name << ": " << age << "\n";
}
```

### std::set (like Python set with sorted elements)
```cpp
// Creation
std::set<int> unique_nums;                 // Python: unique_nums = set()
std::set<int> nums = {3, 1, 4, 1, 5};     // Duplicates automatically removed

// Common operations
unique_nums.insert(42);                    // Python: unique_nums.add(42)
bool found = unique_nums.count(42) > 0;    // Python: found = 42 in unique_nums
auto it = unique_nums.find(42);            // Alternative find method

// Iteration (always in sorted order)
for (const auto& num : unique_nums) {      // Python: for num in sorted(unique_nums):
    std::cout << num << " ";
}
```

### std::unordered_map (like Python dict)
```cpp
// Creation (same syntax as map)
std::unordered_map<std::string, int> scores;

// Operations identical to map, but faster average performance
scores["Alice"] = 95;                      // O(1) average vs O(log n) for map
auto it = scores.find("Alice");            // O(1) average vs O(log n) for map

// Note: No guaranteed iteration order (like Python dict before 3.7)
```

---

## Common Patterns and Idioms

### Safe Element Access
```cpp
// Vector bounds checking
if (i < vec.size()) {
    return vec[i];     // Fast but no bounds check
}
// OR
return vec.at(i);      // Throws exception if out of bounds

// Map safe access
auto it = mymap.find(key);
if (it != mymap.end()) {
    return it->second;  // Found
}
// OR check if key exists before accessing
if (mymap.count(key)) {
    return mymap[key];
}
```

### Iteration Patterns
```cpp
// Range-based for loop (C++11+) - Preferred
for (const auto& element : container) {
    // Use element
}

// Traditional iterator
for (auto it = container.begin(); it != container.end(); ++it) {
    // Use *it
}

// Index-based (only for vector, deque)
for (size_t i = 0; i < vec.size(); ++i) {
    // Use vec[i]
}
```

### Insertion and Deletion
```cpp
// Vector
vec.push_back(value);              // Add to end
vec.insert(vec.begin() + pos, value); // Insert at position
vec.erase(vec.begin() + pos);      // Remove at position

// Map
map[key] = value;                  // Insert or update
map.insert({key, value});          // Insert only (won't overwrite)
map.erase(key);                    // Remove by key

// Set
set.insert(value);                 // Add element
set.erase(value);                  // Remove element
```

---

## Performance Cheat Sheet

| Operation | vector | list | map | set | unordered_map | unordered_set |
|-----------|--------|------|-----|-----|---------------|---------------|
| Access by index | O(1) | O(n) | N/A | N/A | N/A | N/A |
| Search | O(n) | O(n) | O(log n) | O(log n) | O(1) avg | O(1) avg |
| Insert at end | O(1)* | O(1) | O(log n) | O(log n) | O(1) avg | O(1) avg |
| Insert at beginning | O(n) | O(1) | O(log n) | O(log n) | O(1) avg | O(1) avg |
| Insert in middle | O(n) | O(1)** | O(log n) | O(log n) | O(1) avg | O(1) avg |
| Delete | O(n) | O(1)** | O(log n) | O(log n) | O(1) avg | O(1) avg |

*Amortized  
**If you have iterator to position

---

## Common Mistakes and Solutions

### 1. Iterator Invalidation
```cpp
// WRONG - iterator becomes invalid after erase
for (auto it = vec.begin(); it != vec.end(); ++it) {
    if (condition) {
        vec.erase(it);  // Undefined behavior!
    }
}

// CORRECT - erase returns next valid iterator
for (auto it = vec.begin(); it != vec.end();) {
    if (condition) {
        it = vec.erase(it);  // Update iterator
    } else {
        ++it;
    }
}
```

### 2. Map [] vs insert vs find
```cpp
// map[key] creates element if it doesn't exist
if (map[key] > 0) {  // BAD: Creates entry with default value if key missing
    // ...  
}

// Use find for checking existence
if (map.find(key) != map.end()) {  // GOOD: Doesn't create entry
    // ...
}

// Or use count
if (map.count(key)) {  // GOOD: Returns 0 or 1 for map
    // ...
}
```

### 3. Choosing Wrong Container
```cpp
// Need frequent insertions in middle? Use list, not vector
std::list<int> data;  // Good for frequent insert/delete anywhere
std::vector<int> data; // Good for random access, append operations

// Need fast lookups? Use unordered_map, not map (unless you need sorting)
std::unordered_map<std::string, int> fast_lookup;  // O(1) average
std::map<std::string, int> sorted_lookup;          // O(log n), but sorted
```

---

## When to Use Each Container

### Choose std::vector when:
- You need random access (indexing)
- You mostly append to the end
- You need the best cache performance
- **Python equivalent**: `list` for most use cases

### Choose std::list when:
- You frequently insert/delete in the middle
- You don't need random access
- Elements are large and expensive to move
- **Python equivalent**: `collections.deque` for double-ended operations

### Choose std::map when:
- You need key-value pairs in sorted order
- You need logarithmic lookup time
- **Python equivalent**: `dict` when you need sorted keys

### Choose std::unordered_map when:
- You need fast key-value lookups
- You don't care about key ordering  
- **Python equivalent**: `dict` (default choice)

### Choose std::set when:
- You need unique elements in sorted order
- **Python equivalent**: `set` when you need sorting

### Choose std::unordered_set when:
- You need unique elements with fast operations
- You don't care about ordering
- **Python equivalent**: `set` (default choice)

---

## Quick Debugging Tips

1. **Use `.at()` instead of `[]` during development** - catches bounds errors
2. **Check `container.empty()` before accessing elements**
3. **Use range-based for loops** - avoids iterator issues
4. **Print container sizes** to verify your assumptions
5. **Remember that `map[key]` creates the key if it doesn't exist**