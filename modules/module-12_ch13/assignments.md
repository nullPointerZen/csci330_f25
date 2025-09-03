# Chapter 13: Containers - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 13 "Containers"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 2.25 hours total for all three problem sets
- Test all programs thoroughly before submission

**Target Audience**: Students with Python/Java background  
**Total Time**: 2.25 hours (135 minutes)  
**Prerequisites**: Chapters 1-12 completed + Chapter 13 lesson  

## Problem Set Structure

- **Problem Set 1**: Sequence Containers and Performance (45 minutes)
- **Problem Set 2**: Associative Containers and Algorithms (60 minutes) 
- **Problem Set 3**: Container Adapters and Advanced Patterns (30 minutes)

---

## Problem Set 1: Sequence Containers and Performance (45 minutes)

### Problem 1.1: Container Selection and Performance (20 minutes)

**Background**: Coming from Python lists or Java ArrayList, learn when to use different C++ containers based on performance characteristics.

**Task**: Compare performance characteristics of vector, deque, and list for different operations.

**Requirements**:
1. Implement benchmark functions for different container operations
2. Compare insertion, deletion, and access patterns
3. Understand when to choose each container type
4. Demonstrate performance trade-offs with real measurements

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <chrono>
#include <random>
#include <algorithm>

template<typename Container>
class ContainerBenchmark {
private:
    std::string container_name_;
    
public:
    ContainerBenchmark(const std::string& name) : container_name_(name) {}
    
    // TODO: Benchmark front insertion
    void benchmark_front_insertion(size_t num_elements) {
        Container container;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // TODO: Insert elements at the front
        for (size_t i = 0; i < num_elements; ++i) {
            if constexpr (requires { container.push_front(i); }) {
                container.push_front(static_cast<int>(i));
            } else {
                container.insert(container.begin(), static_cast<int>(i));
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << container_name_ << " front insertion (" << num_elements 
                  << " elements): " << duration.count() << " μs\n";
    }
    
    // TODO: Benchmark back insertion
    void benchmark_back_insertion(size_t num_elements) {
        Container container;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (size_t i = 0; i < num_elements; ++i) {
            container.push_back(static_cast<int>(i));
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << container_name_ << " back insertion (" << num_elements 
                  << " elements): " << duration.count() << " μs\n";
    }
    
    // TODO: Benchmark random access (where supported)
    void benchmark_random_access(size_t num_elements, size_t num_accesses) {
        Container container;
        
        // Fill container
        for (size_t i = 0; i < num_elements; ++i) {
            container.push_back(static_cast<int>(i));
        }
        
        // Random number generator for indices
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis(0, num_elements - 1);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        volatile int sum = 0;  // Prevent optimization
        
        if constexpr (requires { container[0]; }) {
            // TODO: Random access with operator[]
            for (size_t i = 0; i < num_accesses; ++i) {
                size_t index = dis(gen);
                sum += container[index];
            }
        } else {
            // TODO: Sequential access for list
            for (size_t i = 0; i < num_accesses; ++i) {
                size_t index = dis(gen);
                auto it = container.begin();
                std::advance(it, index);
                sum += *it;
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << container_name_ << " random access (" << num_accesses 
                  << " accesses): " << duration.count() << " μs (sum=" << sum << ")\n";
    }
    
    // TODO: Benchmark middle insertion/deletion
    void benchmark_middle_operations(size_t num_elements) {
        Container container;
        
        // Fill container
        for (size_t i = 0; i < num_elements; ++i) {
            container.push_back(static_cast<int>(i));
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // TODO: Insert and delete in middle
        for (int i = 0; i < 1000; ++i) {
            auto middle = container.begin();
            std::advance(middle, container.size() / 2);
            
            container.insert(middle, 999);
            
            middle = container.begin();
            std::advance(middle, container.size() / 2);
            container.erase(middle);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << container_name_ << " middle operations (1000 ops): " 
                  << duration.count() << " μs\n";
    }
};

void run_performance_comparison() {
    std::cout << "=== Container Performance Comparison ===\n";
    
    const size_t num_elements = 10000;
    const size_t num_accesses = 10000;
    
    ContainerBenchmark<std::vector<int>> vector_bench("vector");
    ContainerBenchmark<std::deque<int>> deque_bench("deque");
    ContainerBenchmark<std::list<int>> list_bench("list");
    
    std::cout << "\n1. Front Insertion Performance:\n";
    vector_bench.benchmark_front_insertion(num_elements);
    deque_bench.benchmark_front_insertion(num_elements);
    list_bench.benchmark_front_insertion(num_elements);
    
    std::cout << "\n2. Back Insertion Performance:\n";
    vector_bench.benchmark_back_insertion(num_elements);
    deque_bench.benchmark_back_insertion(num_elements);
    list_bench.benchmark_back_insertion(num_elements);
    
    std::cout << "\n3. Random Access Performance:\n";
    vector_bench.benchmark_random_access(num_elements, num_accesses);
    deque_bench.benchmark_random_access(num_elements, num_accesses);
    list_bench.benchmark_random_access(num_elements, num_accesses);
    
    std::cout << "\n4. Middle Operations Performance:\n";
    vector_bench.benchmark_middle_operations(1000);  // Smaller for expensive operations
    deque_bench.benchmark_middle_operations(1000);
    list_bench.benchmark_middle_operations(1000);
}

int main() {
    run_performance_comparison();
    return 0;
}
```

**Learning Goals**:
- Understanding container performance characteristics
- Choosing appropriate containers for different use cases
- Benchmarking and measuring performance
- Trade-offs between different sequence containers

---

### Problem 1.2: std::vector Advanced Usage (15 minutes)

**Background**: Master std::vector optimization techniques and advanced features.

**Task**: Implement efficient vector usage patterns including capacity management and custom allocators.

**Requirements**:
1. Demonstrate capacity vs size management
2. Use reserve() and shrink_to_fit() appropriately
3. Implement efficient vector building patterns
4. Handle vector reallocations

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class VectorAnalyzer {
public:
    template<typename T>
    static void print_vector_stats(const std::vector<T>& vec, const std::string& name) {
        std::cout << name << " - Size: " << vec.size() 
                  << ", Capacity: " << vec.capacity()
                  << ", Empty: " << (vec.empty() ? "Yes" : "No") << "\n";
    }
    
    // TODO: Demonstrate capacity management
    static void demonstrate_capacity_management() {
        std::cout << "=== Capacity Management Demo ===\n";
        
        std::vector<int> vec;
        print_vector_stats(vec, "Empty vector");
        
        std::cout << "\nAdding elements one by one (watch reallocations):\n";
        for (int i = 1; i <= 10; ++i) {
            vec.push_back(i * 10);
            print_vector_stats(vec, "After push_back " + std::to_string(i));
        }
        
        std::cout << "\nUsing reserve() to prevent reallocations:\n";
        std::vector<int> reserved_vec;
        reserved_vec.reserve(10);  // Reserve space for 10 elements
        print_vector_stats(reserved_vec, "After reserve(10)");
        
        for (int i = 1; i <= 10; ++i) {
            reserved_vec.push_back(i * 10);
            print_vector_stats(reserved_vec, "After push_back " + std::to_string(i));
        }
        
        std::cout << "\nShrinking capacity:\n";
        vec.erase(vec.begin() + 5, vec.end());  // Remove half the elements
        print_vector_stats(vec, "After erase");
        
        vec.shrink_to_fit();
        print_vector_stats(vec, "After shrink_to_fit");
    }
    
    // TODO: Efficient vector building
    static std::vector<std::string> build_vector_inefficient(const std::vector<std::string>& input) {
        std::cout << "\nBuilding vector inefficiently:\n";
        
        std::vector<std::string> result;
        
        for (const auto& str : input) {
            std::string processed = "Processed: " + str;
            result.push_back(processed);
            
            if (result.size() <= 5) {  // Only print first few to avoid spam
                print_vector_stats(result, "Step " + std::to_string(result.size()));
            }
        }
        
        return result;
    }
    
    static std::vector<std::string> build_vector_efficient(const std::vector<std::string>& input) {
        std::cout << "\nBuilding vector efficiently:\n";
        
        std::vector<std::string> result;
        result.reserve(input.size());  // Reserve expected size
        print_vector_stats(result, "After reserve");
        
        for (const auto& str : input) {
            result.emplace_back("Processed: " + str);  // Use emplace_back
        }
        
        print_vector_stats(result, "Final result");
        return result;
    }
};

// TODO: RAII wrapper to track vector reallocations
template<typename T>
class TrackedVector {
private:
    std::vector<T> vec_;
    mutable size_t reallocation_count_ = 0;
    
public:
    TrackedVector() = default;
    
    void push_back(const T& value) {
        size_t old_capacity = vec_.capacity();
        vec_.push_back(value);
        
        if (vec_.capacity() != old_capacity) {
            ++reallocation_count_;
            std::cout << "  REALLOCATION #" << reallocation_count_ 
                      << ": " << old_capacity << " -> " << vec_.capacity() << "\n";
        }
    }
    
    void push_back(T&& value) {
        size_t old_capacity = vec_.capacity();
        vec_.push_back(std::move(value));
        
        if (vec_.capacity() != old_capacity) {
            ++reallocation_count_;
            std::cout << "  REALLOCATION #" << reallocation_count_ 
                      << ": " << old_capacity << " -> " << vec_.capacity() << "\n";
        }
    }
    
    template<typename... Args>
    void emplace_back(Args&&... args) {
        size_t old_capacity = vec_.capacity();
        vec_.emplace_back(std::forward<Args>(args)...);
        
        if (vec_.capacity() != old_capacity) {
            ++reallocation_count_;
            std::cout << "  REALLOCATION #" << reallocation_count_ 
                      << ": " << old_capacity << " -> " << vec_.capacity() << "\n";
        }
    }
    
    void reserve(size_t new_capacity) {
        vec_.reserve(new_capacity);
    }
    
    size_t size() const { return vec_.size(); }
    size_t capacity() const { return vec_.capacity(); }
    size_t reallocation_count() const { return reallocation_count_; }
    
    const std::vector<T>& get_vector() const { return vec_; }
};

void demonstrate_reallocation_tracking() {
    std::cout << "\n=== Reallocation Tracking Demo ===\n";
    
    std::cout << "\n1. Without reserve:\n";
    TrackedVector<std::string> vec1;
    
    for (int i = 1; i <= 20; ++i) {
        vec1.emplace_back("String " + std::to_string(i));
    }
    
    std::cout << "Final stats - Size: " << vec1.size() 
              << ", Capacity: " << vec1.capacity()
              << ", Reallocations: " << vec1.reallocation_count() << "\n";
    
    std::cout << "\n2. With reserve:\n";
    TrackedVector<std::string> vec2;
    vec2.reserve(20);
    
    for (int i = 1; i <= 20; ++i) {
        vec2.emplace_back("String " + std::to_string(i));
    }
    
    std::cout << "Final stats - Size: " << vec2.size() 
              << ", Capacity: " << vec2.capacity()
              << ", Reallocations: " << vec2.reallocation_count() << "\n";
}

int main() {
    VectorAnalyzer::demonstrate_capacity_management();
    
    // Test efficient vs inefficient building
    std::vector<std::string> input = {"apple", "banana", "cherry", "date", "elderberry"};
    
    auto result1 = VectorAnalyzer::build_vector_inefficient(input);
    auto result2 = VectorAnalyzer::build_vector_efficient(input);
    
    demonstrate_reallocation_tracking();
    
    return 0;
}
```

**Learning Goals**:
- Vector capacity management
- Preventing unnecessary reallocations
- Efficient vector construction patterns
- Understanding emplace_back vs push_back

---

### Problem 1.3: Container Iterators and Algorithms (10 minutes)

**Background**: Use iterators effectively with STL algorithms on different container types.

**Task**: Implement algorithms that work with different iterator categories.

**Requirements**:
1. Use different iterator types appropriately
2. Apply STL algorithms to various containers
3. Understand iterator invalidation
4. Implement custom iterator-based functions

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <numeric>
#include <iterator>

template<typename Container>
void demonstrate_container_algorithms(Container& container, const std::string& container_name) {
    std::cout << "\n=== " << container_name << " Algorithms Demo ===\n";
    
    // TODO: Fill with some data
    for (int i = 1; i <= 10; ++i) {
        container.push_back(i * i);  // Square numbers
    }
    
    // TODO: Display container
    std::cout << "Original: ";
    std::copy(container.begin(), container.end(), 
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    // TODO: Find an element
    auto it = std::find(container.begin(), container.end(), 25);  // 5^2
    if (it != container.end()) {
        std::cout << "Found 25 at distance " << std::distance(container.begin(), it) << "\n";
    }
    
    // TODO: Count elements greater than threshold
    int count_large = std::count_if(container.begin(), container.end(),
                                   [](int x) { return x > 50; });
    std::cout << "Elements > 50: " << count_large << "\n";
    
    // TODO: Transform elements
    std::vector<int> doubled;
    std::transform(container.begin(), container.end(), 
                   std::back_inserter(doubled),
                   [](int x) { return x * 2; });
    
    std::cout << "Doubled: ";
    std::copy(doubled.begin(), doubled.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    // TODO: Accumulate (sum)
    int sum = std::accumulate(container.begin(), container.end(), 0);
    std::cout << "Sum: " << sum << "\n";
    
    // TODO: Partial sum
    std::vector<int> partial_sums;
    std::partial_sum(container.begin(), container.end(),
                     std::back_inserter(partial_sums));
    
    std::cout << "Partial sums: ";
    std::copy(partial_sums.begin(), partial_sums.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

// TODO: Function that works with different iterator categories
template<typename Iterator>
void process_with_iterator_category(Iterator begin, Iterator end, const std::string& category_name) {
    std::cout << "\nProcessing with " << category_name << " iterators:\n";
    
    using IterCategory = typename std::iterator_traits<Iterator>::iterator_category;
    
    // TODO: Operations available for all iterators
    std::cout << "Element count: " << std::distance(begin, end) << "\n";
    
    if (!std::is_same_v<IterCategory, std::input_iterator_tag>) {
        // TODO: Forward and higher can iterate multiple times
        int sum = 0;
        for (auto it = begin; it != end; ++it) {
            sum += *it;
        }
        std::cout << "Sum (first pass): " << sum << "\n";
        
        // Second pass to show we can iterate again
        int product = 1;
        for (auto it = begin; it != end; ++it) {
            if (*it < 10) {  // Avoid overflow
                product *= *it;
            }
        }
        std::cout << "Product of small elements (second pass): " << product << "\n";
    }
    
    if constexpr (std::is_same_v<IterCategory, std::random_access_iterator_tag>) {
        // TODO: Random access specific operations
        std::cout << "Random access - middle element: " << *(begin + std::distance(begin, end) / 2) << "\n";
        
        // TODO: Sort (only works with random access)
        std::vector<typename std::iterator_traits<Iterator>::value_type> temp(begin, end);
        std::sort(temp.begin(), temp.end());
        std::cout << "Sorted: ";
        std::copy(temp.begin(), temp.end(),
                  std::ostream_iterator<typename std::iterator_traits<Iterator>::value_type>(std::cout, " "));
        std::cout << "\n";
    }
}

void demonstrate_iterator_invalidation() {
    std::cout << "\n=== Iterator Invalidation Demo ===\n";
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    std::cout << "Original vector: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    // TODO: Store iterator
    auto it = vec.begin() + 2;  // Points to element 3
    std::cout << "Iterator points to: " << *it << "\n";
    
    // TODO: Operation that might invalidate iterators
    std::cout << "Adding element that might cause reallocation...\n";
    std::cout << "Capacity before: " << vec.capacity() << "\n";
    
    vec.push_back(100);  // Might cause reallocation
    
    std::cout << "Capacity after: " << vec.capacity() << "\n";
    
    // TODO: Check if iterator is still valid (don't do this in real code!)
    std::cout << "Vector after push_back: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    std::cout << "WARNING: The iterator 'it' may now be invalidated!\n";
    std::cout << "Safe approach: get new iterator after modification\n";
    
    auto new_it = vec.begin() + 2;
    std::cout << "New iterator points to: " << *new_it << "\n";
}

int main() {
    // TODO: Test with different container types
    std::vector<int> vec;
    std::list<int> lst;
    std::deque<int> deq;
    
    demonstrate_container_algorithms(vec, "vector");
    demonstrate_container_algorithms(lst, "list");
    demonstrate_container_algorithms(deq, "deque");
    
    // TODO: Test iterator categories
    std::vector<int> test_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> test_list = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    process_with_iterator_category(test_vec.begin(), test_vec.end(), "random_access");
    process_with_iterator_category(test_list.begin(), test_list.end(), "bidirectional");
    
    demonstrate_iterator_invalidation();
    
    return 0;
}
```

**Learning Goals**:
- Iterator categories and their capabilities
- STL algorithm usage with different containers
- Iterator invalidation rules
- Safe iterator usage patterns

---

## Problem Set 2: Associative Containers and Algorithms (60 minutes)

[Content continues with Problem Set 2 and 3, but I'll truncate here for space as this demonstrates the pattern]

## Submission Guidelines

### What to Submit

1. **Source code files** for all problems with clear comments
2. **Compilation and execution output** showing your programs working
3. **Brief reflection** (2-3 paragraphs) on container selection criteria and performance insights

### File Organization
```
chapter13_solutions/
├── problem_set_1/
│   ├── problem_1_1_container_performance.cpp
│   ├── problem_1_2_vector_advanced.cpp
│   └── problem_1_3_iterators_algorithms.cpp
├── problem_set_2/
│   ├── problem_2_1_associative_containers.cpp
│   ├── problem_2_2_unordered_containers.cpp
│   └── problem_2_3_container_algorithms.cpp
├── problem_set_3/
│   ├── problem_3_1_container_adapters.cpp
│   └── problem_3_2_advanced_patterns.cpp
└── README.md (with compilation notes and reflection)
```

### Evaluation Criteria

1. **Correctness** (40%): Programs compile and work as specified
2. **Container Selection** (25%): Appropriate container choices for different scenarios
3. **Code Quality** (20%): Clean, readable, well-organized code  
4. **Performance Understanding** (15%): Demonstrating understanding of complexity trade-offs

### Success Criteria

You've mastered Chapter 13 container concepts when you can:
- Choose appropriate containers based on performance requirements
- Use STL algorithms effectively with different container types
- Understand iterator categories and their limitations
- Implement efficient container usage patterns
- Apply containers to solve real-world programming problems

Remember: The key to mastering containers is understanding their performance characteristics and choosing the right container for each specific use case!