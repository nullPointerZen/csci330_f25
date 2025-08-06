# Chapter 14: Iterators - Quick Help Guide

## Top 5 Iterator Errors (Fix These First!)

| Error/Problem | Likely Cause | Quick Fix |
|--------------|--------------|-----------|
| `Segmentation fault` in iterator loop | Using invalidated iterator | Check if container was modified during iteration |
| `it != container.end()` never true | Wrong end iterator or modified container | Use same container for begin() and end() |
| Can't modify elements in range-based for | Using `const auto&` or `auto` (copy) | Use `auto&` to modify elements |
| `operator*` gives wrong type | Iterator pointing to wrong element | Check iterator arithmetic and container type |
| Iterator loop never ends | Forgot to increment iterator | Always have `++it` in traditional iterator loops |

## Iterator Quick Reference

### Basic Iterator Operations
```cpp
// Essential operations (work with all iterators)
*it           // Get current element
++it          // Move to next element  
it1 == it2    // Check if iterators are equal
it1 != it2    // Check if iterators are different

// Container access
container.begin()  // Iterator to first element
container.end()    // Iterator to "one past last" element
```

### Common Iterator Patterns
```cpp
// Pattern 1: Traditional iterator loop
for(auto it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << " ";
}

// Pattern 2: Range-based for (preferred for most cases)
for(const auto& item : vec) {
    std::cout << item << " ";
}

// Pattern 3: Safe modification with erase
for(auto it = vec.begin(); it != vec.end(); ) {
    if(should_remove(*it)) {
        it = vec.erase(it);  // erase returns next iterator
    } else {
        ++it;
    }
}
```

## C++ vs Python/Java Quick Comparison

| Task | C++ (Range-based) | C++ (Traditional) | Python | Java |
|------|------------------|-------------------|--------|------|
| **Read all** | `for(const auto& x : vec)` | `for(auto it = vec.begin(); ...)` | `for x in list:` | `for(String x : list)` |
| **Modify all** | `for(auto& x : vec)` | `for(auto it = vec.begin(); ...)` | `for i, x in enumerate(list)` | `ListIterator<String> it` |
| **Find element** | Use `std::find(vec.begin(), vec.end(), value)` | Iterator loop with if check | `value in list` | `list.contains(value)` |

## Range-Based For Loop Cheat Sheet

| Scenario | Syntax | When to Use |
|----------|--------|-------------|
| **Read-only** | `for(const auto& item : container)` | Just printing/using values |
| **Modify elements** | `for(auto& item : container)` | Changing element values |
| **Copy (less efficient)** | `for(auto item : container)` | When you need a local copy |
| **Specific type** | `for(const std::string& item : container)` | When auto isn't clear enough |

## Iterator Categories Quick Guide

| Container Type | Iterator Category | Can Do | Example |
|---------------|------------------|--------|---------|
| **std::vector** | Random Access | Jump anywhere: `it + 5`, `it - 3` | Array-like access |
| **std::list** | Bidirectional | Move both ways: `++it`, `--it` | No jumping |
| **std::set** | Bidirectional | Move both ways, read-only | Sorted iteration |
| **std::unordered_set** | Forward | Only move forward: `++it` | Hash table iteration |

## Stuck? Try This!

**Iterator won't compile?**
1. Check if you're mixing different container iterators
2. Verify the container type matches iterator expectations
3. Make sure you're using `auto` for complex iterator types

**Infinite loop with iterators?**
1. Ensure you have `++it` in your loop
2. Check that begin() and end() are from the same container
3. Verify you're not modifying container size during iteration

**Segmentation fault?**
1. Never use iterators after container is modified (except with erase patterns)
2. Don't dereference `end()` iterator
3. Check container isn't empty before using iterators

**Range-based for not working?**
1. Use `auto&` to modify elements, `const auto&` to read
2. Remember that `auto` creates a copy (usually not what you want)
3. Container must support begin()/end() methods

## Memory Aids for Python/Java Programmers

### Python Connections
- **Range-based for** ≈ Python's `for item in list:`
- **Traditional iterators** ≈ Python's `iter()` and `next()`
- **Iterator invalidation** ≈ Modifying list while iterating (similar problems)

### Java Connections  
- **C++ iterators** ≈ Java's `Iterator<T>` interface
- **Range-based for** ≈ Java's enhanced for loop (`for(String s : list)`)
- **Iterator categories** ≈ Different Java collection interfaces (List, Set, etc.)

## Time-Saving Tips

### Prefer Range-Based For Loops
```cpp
// Usually prefer this:
for(const auto& item : container) { /* ... */ }

// Over this:
for(auto it = container.begin(); it != container.end(); ++it) { /* ... */ }
```

### Use `const auto&` by Default
- Start with `const auto&` for reading
- Change to `auto&` only when you need to modify
- Avoid plain `auto` (creates expensive copies)

### Iterator Invalidation Safety
- **Never** modify container size during range-based for
- Use traditional iterators with proper erase patterns for removal
- When in doubt, collect items to remove first, then remove them

## Common Gotchas

| Problem | Example | Solution |
|---------|---------|----------|
| **End iterator dereference** | `*vec.end()` | Never dereference end(), it's "one past last" |
| **Empty container** | Iterator loop on empty container | Check `container.empty()` first |
| **Mixed container iterators** | Using vec1.begin() with vec2.end() | Always use iterators from same container |
| **Iterator after modification** | Using iterator after `push_back()` | Get fresh iterators after container changes |

## Success Checklist

After Chapter 14, you should be able to:
- [ ] Use range-based for loops confidently (primary method)
- [ ] Write traditional iterator loops when needed
- [ ] Choose correct reference type (`const auto&` vs `auto&`)
- [ ] Avoid iterator invalidation problems
- [ ] Connect iterator concepts to Python/Java experience
- [ ] Debug common iterator-related errors

**Not there yet?** Focus on range-based for loops first - they're the most practical and Python-like approach!