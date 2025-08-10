# Chapter 18: Algorithms - Quick Help (Supplemental)

## Top 3 Algorithm Errors

### 1. Using Wrong Iterator Range
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
// ❌ Wrong: past-the-end iterator
std::sort(vec.begin(), vec.end() + 1);  // Undefined behavior

// ✅ Correct: valid range
std::sort(vec.begin(), vec.end());
```

### 2. Forgetting Prerequisites
```cpp
std::vector<int> unsorted = {5, 2, 8, 1, 9};
// ❌ Wrong: binary_search requires sorted range
bool found = std::binary_search(unsorted.begin(), unsorted.end(), 5);

// ✅ Correct: sort first
std::sort(unsorted.begin(), unsorted.end());
bool found = std::binary_search(unsorted.begin(), unsorted.end(), 5);
```

### 3. Iterator Invalidation
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
auto it = vec.begin();
vec.push_back(6);  // May invalidate iterators
// ❌ Wrong: using potentially invalid iterator
std::cout << *it << std::endl;
```

## Quick Fixes
- Always use correct iterator ranges: `[begin, end)`
- Check algorithm prerequisites (sorted, valid range)
- Be aware of iterator invalidation rules

---

*This is a supplemental chapter - focus on core concepts first.*