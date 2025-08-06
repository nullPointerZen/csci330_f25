# Chapter 18: Algorithms - Complete Guide (Supplemental)

## 🎯 Learning Objectives (5 minutes)

**This is a supplemental chapter** - master core concepts, containers, and iterators first.

By the end of this chapter, you will:
- **Master STL algorithms** - Use standard algorithms for common operations
- **Understand algorithm categories** - Sorting, searching, transforming, and numeric algorithms
- **Apply functional programming** - Use lambdas and function objects with algorithms
- **Choose the right algorithm** - Performance characteristics and when to use each
- **Create custom algorithms** - Build your own generic algorithms

**Time Commitment**: ~4 hours (supplemental)

---

## 📚 Core Concepts

### Python/Java Developers: Algorithm Comparison

| Operation | Python | Java | C++ STL |
|-----------|---------|------|---------|
| **Sort** | `list.sort()` | `Collections.sort()` | `std::sort()` |
| **Find** | `item in list` | `list.contains()` | `std::find()` |
| **Transform** | `[f(x) for x in list]` | `stream.map()` | `std::transform()` |
| **Filter** | `[x for x in list if p(x)]` | `stream.filter()` | `std::copy_if()` |
| **Reduce** | `sum(list)` | `stream.reduce()` | `std::accumulate()` |

**Key Insight**: STL algorithms work with iterators, making them generic across all container types.

---

## 1. Algorithm Categories

### Non-modifying Sequence Operations

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    
    // Finding elements
    auto it = std::find(numbers.begin(), numbers.end(), 4);
    if (it != numbers.end()) {
        std::cout << "Found 4 at position " << (it - numbers.begin()) << std::endl;
    }
    
    // Counting elements
    int count = std::count(numbers.begin(), numbers.end(), 2);
    std::cout << "Number 2 appears " << count << " times" << std::endl;
    
    // Find with condition
    auto even_it = std::find_if(numbers.begin(), numbers.end(), 
                                [](int n) { return n % 2 == 0; });
    if (even_it != numbers.end()) {
        std::cout << "First even number: " << *even_it << std::endl;
    }
    
    // Check conditions
    bool all_positive = std::all_of(numbers.begin(), numbers.end(),
                                   [](int n) { return n > 0; });
    std::cout << "All positive: " << (all_positive ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

### Modifying Sequence Operations

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> result(numbers.size());
    
    // Transform elements
    std::transform(numbers.begin(), numbers.end(), result.begin(),
                  [](int n) { return n * n; });  // Square each element
    
    // Replace elements
    std::replace(result.begin(), result.end(), 9, 99);  // Replace 9 with 99
    
    // Fill with value
    std::vector<int> zeros(10);
    std::fill(zeros.begin(), zeros.end(), 42);
    
    // Generate sequence
    std::vector<int> sequence(10);
    std::iota(sequence.begin(), sequence.end(), 1);  // 1, 2, 3, ..., 10
    
    return 0;
}
```

---

## 2. Sorting and Related Operations

### Basic Sorting

```cpp
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    // Sort in ascending order
    std::sort(numbers.begin(), numbers.end());
    
    // Sort in descending order
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    
    // Partial sort (get top N elements)
    std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::partial_sort(data.begin(), data.begin() + 3, data.end());
    // First 3 elements are now the smallest 3, in sorted order
    
    // Check if sorted
    bool is_sorted = std::is_sorted(numbers.begin(), numbers.end());
    std::cout << "Is sorted: " << (is_sorted ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

### Custom Sorting

```cpp
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

struct Person {
    std::string name;
    int age;
};

int main() {
    std::vector<Person> people = {
        {"Alice", 30}, {"Bob", 25}, {"Charlie", 35}
    };
    
    // Sort by age
    std::sort(people.begin(), people.end(),
             [](const Person& a, const Person& b) {
                 return a.age < b.age;
             });
    
    // Sort by name length, then alphabetically
    std::sort(people.begin(), people.end(),
             [](const Person& a, const Person& b) {
                 if (a.name.length() != b.name.length()) {
                     return a.name.length() < b.name.length();
                 }
                 return a.name < b.name;
             });
    
    return 0;
}
```

---

## 3. Searching and Binary Operations

### Binary Search (requires sorted range)

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Binary search
    bool found = std::binary_search(numbers.begin(), numbers.end(), 7);
    std::cout << "Found 7: " << (found ? "Yes" : "No") << std::endl;
    
    // Lower bound (first position where element could be inserted)
    auto lower = std::lower_bound(numbers.begin(), numbers.end(), 7);
    std::cout << "Lower bound for 7: position " << (lower - numbers.begin()) << std::endl;
    
    // Upper bound (last position where element could be inserted)
    auto upper = std::upper_bound(numbers.begin(), numbers.end(), 7);
    std::cout << "Upper bound for 7: position " << (upper - numbers.begin()) << std::endl;
    
    // Equal range (both bounds at once)
    auto range = std::equal_range(numbers.begin(), numbers.end(), 7);
    std::cout << "Equal range for 7: [" << (range.first - numbers.begin())
              << ", " << (range.second - numbers.begin()) << ")" << std::endl;
    
    return 0;
}
```

---

## 4. Set Operations

### Working with Sorted Ranges

```cpp
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>

int main() {
    std::vector<int> set1 = {1, 2, 3, 4, 5};
    std::vector<int> set2 = {4, 5, 6, 7, 8};
    std::vector<int> result;
    
    // Union
    std::set_union(set1.begin(), set1.end(),
                   set2.begin(), set2.end(),
                   std::back_inserter(result));
    // Result: {1, 2, 3, 4, 5, 6, 7, 8}
    
    result.clear();
    
    // Intersection
    std::set_intersection(set1.begin(), set1.end(),
                          set2.begin(), set2.end(),
                          std::back_inserter(result));
    // Result: {4, 5}
    
    result.clear();
    
    // Difference
    std::set_difference(set1.begin(), set1.end(),
                        set2.begin(), set2.end(),
                        std::back_inserter(result));
    // Result: {1, 2, 3}
    
    return 0;
}
```

---

## 5. Numeric Algorithms

### Mathematical Operations

```cpp
#include <numeric>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Accumulate (sum)
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
    
    // Product
    int product = std::accumulate(numbers.begin(), numbers.end(), 1,
                                 std::multiplies<int>());
    std::cout << "Product: " << product << std::endl;
    
    // Inner product (dot product)
    std::vector<int> weights = {2, 3, 1, 4, 2};
    int dot_product = std::inner_product(numbers.begin(), numbers.end(),
                                        weights.begin(), 0);
    std::cout << "Dot product: " << dot_product << std::endl;
    
    // Partial sums (cumulative sum)
    std::vector<int> partial_sums(numbers.size());
    std::partial_sum(numbers.begin(), numbers.end(), partial_sums.begin());
    // Result: {1, 3, 6, 10, 15}
    
    // Adjacent differences
    std::vector<int> differences(numbers.size());
    std::adjacent_difference(numbers.begin(), numbers.end(), differences.begin());
    // Result: {1, 1, 1, 1, 1} (difference between consecutive elements)
    
    return 0;
}
```

---

## 6. Advanced Algorithm Patterns

### Using Function Objects and Lambdas

```cpp
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>

// Custom function object
struct Multiply {
    int factor;
    Multiply(int f) : factor(f) {}
    int operator()(int x) const { return x * factor; }
};

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> result(numbers.size());
    
    // Using custom function object
    std::transform(numbers.begin(), numbers.end(), result.begin(), Multiply(3));
    
    // Using lambda with capture
    int multiplier = 4;
    std::transform(numbers.begin(), numbers.end(), result.begin(),
                  [multiplier](int x) { return x * multiplier; });
    
    // Using standard function objects
    std::transform(numbers.begin(), numbers.end(), result.begin(),
                  std::bind(std::multiplies<int>(), std::placeholders::_1, 5));
    
    return 0;
}
```

### Custom Algorithms

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

// Custom algorithm: find the index of maximum element
template<typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
find_max_index(Iterator first, Iterator last) {
    if (first == last) return -1;
    
    auto max_it = std::max_element(first, last);
    return std::distance(first, max_it);
}

// Custom algorithm: apply function to every nth element
template<typename Iterator, typename Function>
void for_every_nth(Iterator first, Iterator last, size_t n, Function f) {
    size_t count = 0;
    for (auto it = first; it != last; ++it, ++count) {
        if (count % n == 0) {
            f(*it);
        }
    }
}

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    
    // Find index of maximum element
    auto max_idx = find_max_index(numbers.begin(), numbers.end());
    std::cout << "Max element at index: " << max_idx << std::endl;
    
    // Apply function to every 3rd element
    std::cout << "Every 3rd element: ";
    for_every_nth(numbers.begin(), numbers.end(), 3,
                  [](int n) { std::cout << n << " "; });
    std::cout << std::endl;
    
    return 0;
}
```

---

## 7. Performance Considerations

### Choosing the Right Algorithm

```cpp
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <chrono>
#include <iostream>

void performance_comparison() {
    std::vector<int> vec(10000);
    std::iota(vec.begin(), vec.end(), 1);
    
    // For unsorted containers: O(n)
    auto start = std::chrono::high_resolution_clock::now();
    auto it1 = std::find(vec.begin(), vec.end(), 5000);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "std::find time: " 
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;
    
    // For sorted containers: O(log n)
    start = std::chrono::high_resolution_clock::now();
    bool found = std::binary_search(vec.begin(), vec.end(), 5000);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::binary_search time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;
              
    // Using appropriate container for frequent searches
    std::unordered_set<int> hash_set(vec.begin(), vec.end());
    start = std::chrono::high_resolution_clock::now();
    auto it3 = hash_set.find(5000);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "unordered_set::find time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;
}
```

---

## 🧩 Quick Problems

### Problem 1: Data Analysis Pipeline
Use algorithms to process a dataset (filter, transform, analyze).

### Problem 2: String Processing Algorithms
Implement text processing using STL algorithms.

### Problem 3: Custom Algorithm Library
Build reusable algorithms for common tasks.

See [chapter_18_problems.md](chapter_18_problems.md) for detailed problems.

---

## ✅ Success Checklist

- [ ] Understand algorithm categories and when to use each
- [ ] Can apply common algorithms (sort, find, transform)
- [ ] Use lambdas and function objects with algorithms
- [ ] Choose appropriate algorithms for performance
- [ ] Build custom generic algorithms
- [ ] Combine algorithms to solve complex problems

---

## 🚀 What's Next

**STL algorithms are powerful tools** that make C++ code more expressive and efficient. Combined with containers and iterators, they form the foundation of modern C++ programming.

**Apply these skills** to build efficient data processing applications and solve algorithmic challenges.

---

*This is a supplemental chapter - master core concepts and containers before diving deep into algorithms.*