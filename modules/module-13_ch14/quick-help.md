# Chapter 14: Iterators - Quick Help Guide

**For students with Python/Java background learning C++ iterator concepts and STL algorithm integration**

---

## 🚨 Most Common Mistakes

### 1. Iterator Invalidation After Container Modification
```cpp
// DANGEROUS - Iterator becomes invalid after erase
std::vector<int> vec{1, 2, 3, 4, 5};
auto it = vec.begin() + 2;  // Points to element 3
vec.erase(vec.begin());     // Removes first element
// it now points to invalid memory! Using it = undefined behavior

// SAFE - Get new iterator after modification
std::vector<int> vec{1, 2, 3, 4, 5};
auto index = 2;
vec.erase(vec.begin());
auto it = vec.begin() + index - 1;  // Adjust for removed element
```

### 2. Mixing Iterator Types Incorrectly
```cpp
// WRONG - Can't use random access operations on list iterators
std::list<int> lst{1, 2, 3, 4, 5};
auto it = lst.begin();
it += 3;  // Compilation error! list has bidirectional iterators only

// RIGHT - Use std::advance for non-random-access iterators
auto it = lst.begin();
std::advance(it, 3);  // Works with any iterator type

// WRONG - Using algorithms requiring random access on list
std::list<int> lst{5, 2, 8, 1, 9};
std::sort(lst.begin(), lst.end());  // Error! sort needs random access

// RIGHT - Use list member function
lst.sort();  // Works correctly
```

### 3. Off-by-One Errors with Iterator Ranges
```cpp
// WRONG - Including end() iterator in range
std::vector<int> vec{1, 2, 3};
for (auto it = vec.begin(); it <= vec.end(); ++it) {  // <= is wrong!
    std::cout << *it;  // Undefined behavior when it == vec.end()
}

// RIGHT - Use != end() for termination
for (auto it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it;  // Safe
}
```

---

## 📋 Iterator Categories Quick Reference

### Iterator Hierarchy (from weakest to strongest)

#### Input Iterator
```cpp
// Characteristics: Read-only, single-pass
// Examples: std::istream_iterator

std::istream_iterator<int> input_it(std::cin);
std::istream_iterator<int> end_it;

// Operations available:
*input_it           // Dereference (read)
++input_it          // Pre-increment
input_it++          // Post-increment
input_it == end_it  // Equality comparison
input_it != end_it  // Inequality comparison
```

#### Output Iterator
```cpp
// Characteristics: Write-only, single-pass
// Examples: std::ostream_iterator, std::back_insert_iterator

std::ostream_iterator<int> output_it(std::cout, " ");

// Operations available:
*output_it = value  // Dereference (write)
++output_it         // Pre-increment
output_it++         // Post-increment
```

#### Forward Iterator
```cpp
// Characteristics: Read/write, multi-pass
// Examples: std::forward_list iterators

std::forward_list<int> flist{1, 2, 3};
auto it = flist.begin();

// All Input/Output operations plus:
// - Can traverse multiple times
// - Can store and reuse iterator positions
auto saved_it = it;  // Save position
++it;                // Move forward
it = saved_it;       // Return to saved position
```

#### Bidirectional Iterator
```cpp
// Characteristics: Forward + backward movement
// Examples: std::list, std::set, std::map iterators

std::list<int> lst{1, 2, 3};
auto it = lst.end();

// All Forward operations plus:
--it;               // Pre-decrement
it--;               // Post-decrement
```

#### Random Access Iterator
```cpp
// Characteristics: Bidirectional + jump to any position
// Examples: std::vector, std::deque, std::array iterators

std::vector<int> vec{1, 2, 3, 4, 5};
auto it = vec.begin();

// All Bidirectional operations plus:
it += 3;            // Compound assignment
it -= 2;            // Compound assignment
auto it2 = it + 3;  // Arithmetic
auto it3 = it - 2;  // Arithmetic
auto diff = it2 - it3;  // Distance
bool less = it < it2;   // Comparison
it[3];              // Subscript access
```

---

## ⚡ Iterator Usage Patterns

### Safe Container Modification
```cpp
// Pattern 1: Erase-remove idiom
std::vector<int> vec{1, 2, 3, 2, 4, 2, 5};
vec.erase(
    std::remove(vec.begin(), vec.end(), 2),
    vec.end()
);

// Pattern 2: Update iterator after erase
std::vector<int> vec{1, 2, 3, 4, 5};
for (auto it = vec.begin(); it != vec.end();) {
    if (*it % 2 == 0) {
        it = vec.erase(it);  // erase returns next valid iterator
    } else {
        ++it;
    }
}

// Pattern 3: Reverse iteration for safe deletion
for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    if (*it % 2 == 0) {
        // Convert reverse iterator to forward iterator for erase
        vec.erase(std::next(it).base());
    }
}
```

### Algorithm Selection Based on Iterator Category
```cpp
template<typename Iterator>
void advance_iterator(Iterator& it, int n) {
    using Category = typename std::iterator_traits<Iterator>::iterator_category;
    
    if constexpr (std::is_same_v<Category, std::random_access_iterator_tag>) {
        it += n;  // O(1) for random access
    } else {
        std::advance(it, n);  // O(n) for other categories
    }
}

template<typename Iterator>
auto distance_between(Iterator first, Iterator last) {
    using Category = typename std::iterator_traits<Iterator>::iterator_category;
    
    if constexpr (std::is_same_v<Category, std::random_access_iterator_tag>) {
        return last - first;  // O(1) for random access
    } else {
        return std::distance(first, last);  // O(n) for other categories
    }
}
```

### Iterator Adapters
```cpp
// Reverse iterators
std::vector<int> vec{1, 2, 3, 4, 5};
for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    std::cout << *it << " ";  // Prints: 5 4 3 2 1
}

// Insert iterators
std::vector<int> source{1, 2, 3};
std::vector<int> dest;

std::copy(source.begin(), source.end(), 
          std::back_inserter(dest));     // Uses push_back

std::list<int> lst;
std::copy(source.begin(), source.end(),
          std::front_inserter(lst));     // Uses push_front

// Stream iterators
std::vector<int> numbers{1, 2, 3, 4, 5};
std::copy(numbers.begin(), numbers.end(),
          std::ostream_iterator<int>(std::cout, " "));

std::istream_iterator<int> input(std::cin);
std::istream_iterator<int> eof;
std::vector<int> input_numbers(input, eof);
```

---

## 🔧 Custom Iterator Implementation

### Basic Iterator Template
```cpp
template<typename T>
class my_iterator {
public:
    // Iterator traits (required for STL compatibility)
    using iterator_category = std::forward_iterator_tag;  // or appropriate category
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    
private:
    T* ptr_;  // Pointer to current element
    
public:
    // Constructor
    explicit my_iterator(T* ptr) : ptr_(ptr) {}
    
    // Dereference operators
    reference operator*() const { return *ptr_; }
    pointer operator->() const { return ptr_; }
    
    // Increment operators
    my_iterator& operator++() {      // Pre-increment
        ++ptr_;
        return *this;
    }
    
    my_iterator operator++(int) {    // Post-increment
        my_iterator temp = *this;
        ++ptr_;
        return temp;
    }
    
    // Comparison operators
    bool operator==(const my_iterator& other) const {
        return ptr_ == other.ptr_;
    }
    
    bool operator!=(const my_iterator& other) const {
        return !(*this == other);
    }
    
    // Additional operators for higher categories
    // (decrement for bidirectional, arithmetic for random access)
};
```

### Iterator Traits Usage
```cpp
template<typename Iterator>
void process_iterator(Iterator it) {
    using ValueType = typename std::iterator_traits<Iterator>::value_type;
    using Category = typename std::iterator_traits<Iterator>::iterator_category;
    
    std::cout << "Value type: " << typeid(ValueType).name() << "\n";
    
    if constexpr (std::is_same_v<Category, std::random_access_iterator_tag>) {
        std::cout << "Random access iterator\n";
    } else if constexpr (std::is_same_v<Category, std::bidirectional_iterator_tag>) {
        std::cout << "Bidirectional iterator\n";
    } else if constexpr (std::is_same_v<Category, std::forward_iterator_tag>) {
        std::cout << "Forward iterator\n";
    }
}
```

---

## 💡 STL Algorithm Categories

### Non-modifying Algorithms
```cpp
std::vector<int> vec{1, 2, 3, 4, 5};

// Finding
auto it = std::find(vec.begin(), vec.end(), 3);
auto it = std::find_if(vec.begin(), vec.end(), 
                       [](int x) { return x > 3; });

// Counting
auto count = std::count(vec.begin(), vec.end(), 2);
auto count_if = std::count_if(vec.begin(), vec.end(),
                              [](int x) { return x % 2 == 0; });

// Testing conditions
bool all_positive = std::all_of(vec.begin(), vec.end(),
                                [](int x) { return x > 0; });
bool any_even = std::any_of(vec.begin(), vec.end(),
                           [](int x) { return x % 2 == 0; });

// Comparing ranges
std::vector<int> other{1, 2, 3, 4, 5};
bool equal = std::equal(vec.begin(), vec.end(), other.begin());
```

### Modifying Algorithms
```cpp
std::vector<int> vec{1, 2, 3, 4, 5};

// Transform
std::transform(vec.begin(), vec.end(), vec.begin(),
               [](int x) { return x * 2; });

// Replace
std::replace(vec.begin(), vec.end(), 2, 20);
std::replace_if(vec.begin(), vec.end(),
                [](int x) { return x % 2 == 0; }, 0);

// Fill
std::fill(vec.begin(), vec.end(), 42);
std::fill_n(vec.begin(), 3, 42);  // Fill first 3 elements

// Generate
std::generate(vec.begin(), vec.end(), 
              []() { return rand() % 100; });
```

### Removing and Reordering
```cpp
std::vector<int> vec{1, 2, 3, 2, 4, 2, 5};

// Remove (doesn't actually remove, returns new end)
auto new_end = std::remove(vec.begin(), vec.end(), 2);
vec.erase(new_end, vec.end());  // Actually remove

// Remove if
vec.erase(std::remove_if(vec.begin(), vec.end(),
                        [](int x) { return x % 2 == 0; }),
          vec.end());

// Unique (remove consecutive duplicates)
std::sort(vec.begin(), vec.end());  // Sort first for all duplicates
vec.erase(std::unique(vec.begin(), vec.end()), vec.end());

// Reverse
std::reverse(vec.begin(), vec.end());

// Rotate
std::rotate(vec.begin(), vec.begin() + 2, vec.end());  // Move first 2 to end
```

---

## 🔍 Algorithm Requirements and Performance

### Iterator Requirements by Algorithm
```cpp
// Input Iterator required
std::find(first, last, value)
std::count(first, last, value)
std::accumulate(first, last, init)

// Forward Iterator required
std::adjacent_find(first, last)
std::unique(first, last)
std::rotate(first, middle, last)

// Bidirectional Iterator required
std::reverse(first, last)
std::next_permutation(first, last)

// Random Access Iterator required
std::sort(first, last)
std::binary_search(first, last, value)  // Also requires sorted range
std::nth_element(first, nth, last)
```

### Performance Considerations
```cpp
// O(1) operations
vec.begin(), vec.end()          // Iterator creation
*it, it++, it--                 // Basic iterator operations
it += n (random access only)    // Iterator arithmetic

// O(log n) operations
std::binary_search()            // On sorted range
std::lower_bound(), std::upper_bound()  // On sorted range

// O(n) operations
std::find(), std::count()       // Linear search
std::advance(it, n)             // For non-random-access iterators

// O(n log n) operations
std::sort()                     // Comparison-based sorting
std::stable_sort()              // Stable comparison-based sorting
```

---

## ⚠️ Iterator Safety Tips

### Avoiding Iterator Invalidation
```cpp
// Safe patterns for vector modification
std::vector<int> vec{1, 2, 3, 4, 5};

// Pattern 1: Use indices instead of iterators
for (size_t i = 0; i < vec.size();) {
    if (vec[i] % 2 == 0) {
        vec.erase(vec.begin() + i);  // Don't increment i
    } else {
        ++i;  // Only increment when not erasing
    }
}

// Pattern 2: Collect indices, then erase in reverse order
std::vector<size_t> to_erase;
for (size_t i = 0; i < vec.size(); ++i) {
    if (vec[i] % 2 == 0) {
        to_erase.push_back(i);
    }
}
// Erase in reverse order to maintain valid indices
for (auto it = to_erase.rbegin(); it != to_erase.rend(); ++it) {
    vec.erase(vec.begin() + *it);
}
```

### Range-Based for Loop Limitations
```cpp
// DANGER - Modifying container during range-based for loop
std::vector<int> vec{1, 2, 3, 4, 5};
for (int x : vec) {
    if (x % 2 == 0) {
        vec.erase(/* ... */);  // Undefined behavior!
    }
}

// SAFE - Use traditional for loop or algorithms
for (auto it = vec.begin(); it != vec.end();) {
    if (*it % 2 == 0) {
        it = vec.erase(it);
    } else {
        ++it;
    }
}
```

---

## 🆘 Emergency Syntax Reference

### Iterator Creation
```cpp
// Container iterators
auto begin = container.begin();
auto end = container.end();
auto cbegin = container.cbegin();  // const iterator
auto cend = container.cend();

// Reverse iterators
auto rbegin = container.rbegin();
auto rend = container.rend();
auto crbegin = container.crbegin();  // const reverse
auto crend = container.crend();
```

### Iterator Operations
```cpp
// All iterators
*it                    // Dereference
it->member            // Arrow operator
++it, it++            // Increment
it1 == it2, it1 != it2  // Equality

// Bidirectional and Random Access
--it, it--            // Decrement

// Random Access only
it += n, it -= n      // Compound assignment
it + n, it - n        // Arithmetic
it1 - it2            // Distance
it[n]                // Subscript
it1 < it2, it1 <= it2  // Comparison
```

### Algorithm Common Patterns
```cpp
// Find and process
auto it = std::find_if(container.begin(), container.end(), predicate);
if (it != container.end()) {
    // Found, process *it
}

// Transform and copy
std::transform(src.begin(), src.end(), 
               std::back_inserter(dest), 
               transform_function);

// Filter and copy
std::copy_if(src.begin(), src.end(),
             std::back_inserter(dest),
             predicate);

// Erase-remove idiom
container.erase(
    std::remove_if(container.begin(), container.end(), predicate),
    container.end()
);
```

**Remember**: Iterators are the glue between containers and algorithms. Understanding their categories helps you choose the right algorithms and avoid common pitfalls!