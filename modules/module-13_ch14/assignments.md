# Chapter 14: Iterators - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 14 "Iterators"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 1.5 hours total for both problem sets
- Test all programs thoroughly before submission

**Target Audience**: Students with Python/Java background  
**Total Time**: 1.5 hours (90 minutes)  
**Prerequisites**: Chapters 1-13 completed + Chapter 14 lesson  

## Problem Set Structure

- **Problem Set 1**: Iterator Categories and STL Algorithms (45 minutes)
- **Problem Set 2**: Custom Iterator Implementation (60 minutes) 
- **Problem Set 3**: Advanced Iterator Patterns (30 minutes)

---

## Problem Set 1: Iterator Categories and STL Algorithms (45 minutes)

### Problem 1.1: Iterator Categories Deep Dive (20 minutes)

**Background**: Coming from Python's simple iteration or Java's Iterator interface, understand C++ iterator hierarchy and capabilities.

**Task**: Explore different iterator categories and their specific capabilities.

**Requirements**:
1. Demonstrate operations available for each iterator category
2. Show algorithm requirements for different iterator types
3. Understand iterator trait system
4. Implement functions that work with specific iterator categories

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <iterator>
#include <algorithm>
#include <type_traits>

// TODO: Template function to identify iterator category
template<typename Iterator>
void print_iterator_category(const std::string& container_name) {
    using IterCategory = typename std::iterator_traits<Iterator>::iterator_category;
    
    std::cout << container_name << " uses ";
    
    if constexpr (std::is_same_v<IterCategory, std::input_iterator_tag>) {
        std::cout << "input iterators";
    } else if constexpr (std::is_same_v<IterCategory, std::output_iterator_tag>) {
        std::cout << "output iterators";
    } else if constexpr (std::is_same_v<IterCategory, std::forward_iterator_tag>) {
        std::cout << "forward iterators";
    } else if constexpr (std::is_same_v<IterCategory, std::bidirectional_iterator_tag>) {
        std::cout << "bidirectional iterators";
    } else if constexpr (std::is_same_v<IterCategory, std::random_access_iterator_tag>) {
        std::cout << "random access iterators";
    }
    std::cout << "\n";
}

// TODO: Function that requires input iterators (minimum requirement)
template<typename InputIt>
typename std::iterator_traits<InputIt>::value_type
sum_elements(InputIt first, InputIt last) {
    using ValueType = typename std::iterator_traits<InputIt>::value_type;
    ValueType sum{};
    
    std::cout << "Summing elements using input iterator operations:\n";
    for (auto it = first; it != last; ++it) {
        sum += *it;
        std::cout << "  Adding: " << *it << " (running sum: " << sum << ")\n";
    }
    
    return sum;
}

// TODO: Function that requires forward iterators
template<typename ForwardIt>
void find_and_count_duplicates(ForwardIt first, ForwardIt last) {
    std::cout << "Finding duplicates using forward iterator operations:\n";
    
    int duplicate_count = 0;
    
    for (auto it1 = first; it1 != last; ++it1) {
        for (auto it2 = std::next(it1); it2 != last; ++it2) {
            if (*it1 == *it2) {
                std::cout << "  Found duplicate: " << *it1 << "\n";
                duplicate_count++;
                break;  // Count each value only once
            }
        }
    }
    
    std::cout << "Total unique values with duplicates: " << duplicate_count << "\n";
}

// TODO: Function that requires bidirectional iterators
template<typename BidirIt>
void print_reverse_with_bidirectional(BidirIt first, BidirIt last) {
    std::cout << "Printing in reverse using bidirectional iterator operations:\n";
    
    if (first == last) {
        std::cout << "  (empty range)\n";
        return;
    }
    
    // Move to the last valid element
    auto it = std::prev(last);
    
    std::cout << "  Reverse: ";
    do {
        std::cout << *it << " ";
        if (it == first) break;
        --it;
    } while (true);
    std::cout << "\n";
}

// TODO: Function that requires random access iterators
template<typename RandomIt>
void quick_access_demo(RandomIt first, RandomIt last) {
    std::cout << "Random access iterator operations:\n";
    
    auto size = std::distance(first, last);
    if (size == 0) {
        std::cout << "  (empty range)\n";
        return;
    }
    
    std::cout << "  Size: " << size << "\n";
    std::cout << "  First element: " << *first << "\n";
    std::cout << "  Last element: " << *(last - 1) << "\n";
    
    if (size >= 3) {
        std::cout << "  Middle element: " << *(first + size / 2) << "\n";
        
        // TODO: Random access in constant time
        std::cout << "  Elements at positions 0, 1, " << (size-1) << ": ";
        std::cout << first[0] << ", " << first[1] << ", " << first[size-1] << "\n";
    }
}

void demonstrate_iterator_categories() {
    std::cout << "=== Iterator Categories Demo ===\n";
    
    std::vector<int> vec = {1, 2, 3, 2, 4, 5, 3};
    std::list<int> lst = {1, 2, 3, 2, 4, 5, 3};
    std::forward_list<int> flist = {1, 2, 3, 2, 4, 5, 3};
    
    // TODO: Print iterator categories
    print_iterator_category<std::vector<int>::iterator>("std::vector");
    print_iterator_category<std::list<int>::iterator>("std::list");
    print_iterator_category<std::forward_list<int>::iterator>("std::forward_list");
    
    std::cout << "\n--- Input Iterator Functions (work with all) ---\n";
    std::cout << "Vector sum: " << sum_elements(vec.begin(), vec.end()) << "\n";
    std::cout << "List sum: " << sum_elements(lst.begin(), lst.end()) << "\n";
    std::cout << "Forward list sum: " << sum_elements(flist.begin(), flist.end()) << "\n";
    
    std::cout << "\n--- Forward Iterator Functions (not for input-only) ---\n";
    find_and_count_duplicates(vec.begin(), vec.end());
    find_and_count_duplicates(lst.begin(), lst.end());
    find_and_count_duplicates(flist.begin(), flist.end());
    
    std::cout << "\n--- Bidirectional Iterator Functions (not for forward-only) ---\n";
    print_reverse_with_bidirectional(vec.begin(), vec.end());
    print_reverse_with_bidirectional(lst.begin(), lst.end());
    // forward_list doesn't support bidirectional iteration
    
    std::cout << "\n--- Random Access Iterator Functions (vector only) ---\n";
    quick_access_demo(vec.begin(), vec.end());
    // list and forward_list don't support random access
}

int main() {
    demonstrate_iterator_categories();
    return 0;
}
```

**Learning Goals**:
- Understanding iterator category hierarchy
- Iterator trait system usage
- Algorithm requirements for different iterator types
- Writing functions that work with specific iterator categories

---

### Problem 1.2: STL Algorithm Composition (15 minutes)

**Background**: Compose STL algorithms effectively using iterators to create powerful data processing pipelines.

**Task**: Chain STL algorithms together to solve complex data processing problems.

**Requirements**:
1. Use algorithm composition for data transformation
2. Apply predicates and projections effectively
3. Combine multiple algorithms in pipelines
4. Handle different iterator requirements

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <string>

struct Student {
    std::string name;
    int age;
    double gpa;
    std::string major;
    
    Student(std::string n, int a, double g, std::string m)
        : name(std::move(n)), age(a), gpa(g), major(std::move(m)) {}
};

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << s.name << " (age " << s.age << ", GPA " << s.gpa << ", " << s.major << ")";
    return os;
}

class DataProcessor {
public:
    // TODO: Complex data processing pipeline
    static void analyze_student_data(const std::vector<Student>& students) {
        std::cout << "=== Student Data Analysis ===\n";
        
        // TODO: Find all CS majors with GPA > 3.5
        std::vector<Student> high_performing_cs;
        std::copy_if(students.begin(), students.end(),
                    std::back_inserter(high_performing_cs),
                    [](const Student& s) {
                        return s.major == "CS" && s.gpa > 3.5;
                    });
        
        std::cout << "\nHigh-performing CS students:\n";
        std::for_each(high_performing_cs.begin(), high_performing_cs.end(),
                     [](const Student& s) {
                         std::cout << "  " << s << "\n";
                     });
        
        // TODO: Calculate average GPA by major
        std::vector<std::string> majors = {"CS", "Math", "Physics", "Biology"};
        
        for (const auto& major : majors) {
            auto gpa_sum = std::accumulate(students.begin(), students.end(), 0.0,
                                         [&major](double sum, const Student& s) {
                                             return s.major == major ? sum + s.gpa : sum;
                                         });
            
            auto count = std::count_if(students.begin(), students.end(),
                                     [&major](const Student& s) {
                                         return s.major == major;
                                     });
            
            if (count > 0) {
                std::cout << major << " average GPA: " << (gpa_sum / count) << "\n";
            }
        }
        
        // TODO: Find age distribution
        std::vector<int> ages;
        std::transform(students.begin(), students.end(),
                      std::back_inserter(ages),
                      [](const Student& s) { return s.age; });
        
        auto [min_age, max_age] = std::minmax_element(ages.begin(), ages.end());
        std::cout << "Age range: " << *min_age << " to " << *max_age << "\n";
        
        // TODO: Sort students by GPA (descending)
        std::vector<Student> sorted_students = students;  // Copy for sorting
        std::sort(sorted_students.begin(), sorted_students.end(),
                 [](const Student& a, const Student& b) {
                     return a.gpa > b.gpa;  // Descending order
                 });
        
        std::cout << "\nTop 3 students by GPA:\n";
        std::for_each(sorted_students.begin(), 
                     sorted_students.begin() + std::min(3UL, sorted_students.size()),
                     [](const Student& s) {
                         std::cout << "  " << s << "\n";
                     });
    }
    
    // TODO: Numeric processing pipeline
    static void process_numeric_data(const std::vector<int>& numbers) {
        std::cout << "\n=== Numeric Data Processing ===\n";
        
        std::cout << "Original data: ";
        std::copy(numbers.begin(), numbers.end(),
                 std::ostream_iterator<int>(std::cout, " "));
        std::cout << "\n";
        
        // TODO: Pipeline: filter even numbers -> square them -> accumulate
        std::vector<int> even_numbers;
        std::copy_if(numbers.begin(), numbers.end(),
                    std::back_inserter(even_numbers),
                    [](int n) { return n % 2 == 0; });
        
        std::cout << "Even numbers: ";
        std::copy(even_numbers.begin(), even_numbers.end(),
                 std::ostream_iterator<int>(std::cout, " "));
        std::cout << "\n";
        
        std::vector<int> squared_evens;
        std::transform(even_numbers.begin(), even_numbers.end(),
                      std::back_inserter(squared_evens),
                      [](int n) { return n * n; });
        
        std::cout << "Squared evens: ";
        std::copy(squared_evens.begin(), squared_evens.end(),
                 std::ostream_iterator<int>(std::cout, " "));
        std::cout << "\n";
        
        int sum_squared_evens = std::accumulate(squared_evens.begin(), 
                                              squared_evens.end(), 0);
        std::cout << "Sum of squared evens: " << sum_squared_evens << "\n";
        
        // TODO: Alternative: single-pass pipeline using inner_product
        int result = std::inner_product(numbers.begin(), numbers.end(),
                                       numbers.begin(), 0,
                                       std::plus<>(),
                                       [](int a, int b) {
                                           return (a % 2 == 0) ? a * a : 0;
                                       });
        std::cout << "Same result using inner_product: " << result << "\n";
    }
    
    // TODO: String processing pipeline
    static void process_text_data(const std::vector<std::string>& words) {
        std::cout << "\n=== Text Data Processing ===\n";
        
        std::cout << "Original words: ";
        std::copy(words.begin(), words.end(),
                 std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << "\n";
        
        // TODO: Find words longer than 5 characters, convert to uppercase
        std::vector<std::string> long_words_upper;
        
        std::for_each(words.begin(), words.end(),
                     [&long_words_upper](const std::string& word) {
                         if (word.length() > 5) {
                             std::string upper_word = word;
                             std::transform(upper_word.begin(), upper_word.end(),
                                          upper_word.begin(), ::toupper);
                             long_words_upper.push_back(upper_word);
                         }
                     });
        
        std::cout << "Long words (uppercase): ";
        std::copy(long_words_upper.begin(), long_words_upper.end(),
                 std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << "\n";
        
        // TODO: Count vowels in all words
        int total_vowels = std::accumulate(words.begin(), words.end(), 0,
                                         [](int count, const std::string& word) {
                                             return count + std::count_if(word.begin(), word.end(),
                                                                         [](char c) {
                                                                             return std::string("aeiouAEIOU").find(c) != std::string::npos;
                                                                         });
                                         });
        
        std::cout << "Total vowels in all words: " << total_vowels << "\n";
    }
};

int main() {
    // TODO: Test with student data
    std::vector<Student> students = {
        {"Alice Johnson", 20, 3.8, "CS"},
        {"Bob Smith", 22, 3.2, "Math"},
        {"Charlie Brown", 19, 3.9, "CS"},
        {"Diana Prince", 21, 3.6, "Physics"},
        {"Eve Wilson", 20, 3.4, "CS"},
        {"Frank Miller", 23, 3.7, "Math"},
        {"Grace Lee", 19, 3.95, "Physics"},
        {"Henry Davis", 22, 3.1, "Biology"}
    };
    
    DataProcessor::analyze_student_data(students);
    
    // TODO: Test with numeric data
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    DataProcessor::process_numeric_data(numbers);
    
    // TODO: Test with text data
    std::vector<std::string> words = {"hello", "world", "programming", "iterator", "algorithm", "cpp", "beautiful"};
    DataProcessor::process_text_data(words);
    
    return 0;
}
```

**Learning Goals**:
- Algorithm composition and chaining
- Using predicates and projections effectively
- Single-pass vs multi-pass processing
- Complex data transformations with STL

---

### Problem 1.3: Iterator Adapters (10 minutes)

**Background**: Use STL iterator adapters like reverse_iterator, insert_iterator, and stream_iterator.

**Task**: Implement solutions using various iterator adapters.

**Requirements**:
1. Use reverse iterators for backward processing
2. Apply insert iterators for flexible insertion
3. Use stream iterators for I/O operations
4. Combine adapters for complex operations

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

void demonstrate_reverse_iterators() {
    std::cout << "=== Reverse Iterator Demo ===\n";
    
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "Original: ";
    std::copy(numbers.begin(), numbers.end(),
             std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    // TODO: Print in reverse using reverse iterators
    std::cout << "Reversed: ";
    std::copy(numbers.rbegin(), numbers.rend(),
             std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    // TODO: Find last occurrence of a value
    auto rit = std::find(numbers.rbegin(), numbers.rend(), 5);
    if (rit != numbers.rend()) {
        // Convert reverse iterator to forward iterator
        auto it = rit.base() - 1;  // base() points one past the element
        std::cout << "Last occurrence of 5 at position: " 
                  << std::distance(numbers.begin(), it) << "\n";
    }
    
    // TODO: Process from end, stop at condition
    std::cout << "Processing from end until value < 6: ";
    for (auto rit = numbers.rbegin(); rit != numbers.rend(); ++rit) {
        if (*rit < 6) break;
        std::cout << *rit << " ";
    }
    std::cout << "\n";
}

void demonstrate_insert_iterators() {
    std::cout << "\n=== Insert Iterator Demo ===\n";
    
    std::vector<int> source = {10, 20, 30, 40, 50};
    
    // TODO: back_insert_iterator
    std::vector<int> vec1;
    std::cout << "Using back_insert_iterator:\n";
    std::copy(source.begin(), source.end(), std::back_inserter(vec1));
    
    std::cout << "vec1: ";
    std::copy(vec1.begin(), vec1.end(),
             std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    // TODO: front_insert_iterator
    std::list<int> list1;  // Use list because vector doesn't have push_front
    std::cout << "Using front_insert_iterator:\n";
    std::copy(source.begin(), source.end(), std::front_inserter(list1));
    
    std::cout << "list1: ";
    std::copy(list1.begin(), list1.end(),
             std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    // TODO: insert_iterator
    std::vector<int> vec2 = {1, 2, 3, 7, 8, 9};
    std::cout << "Using insert_iterator at position 3:\n";
    std::cout << "Before: ";
    std::copy(vec2.begin(), vec2.end(),
             std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    auto insert_pos = vec2.begin() + 3;
    std::copy(source.begin(), source.begin() + 2,  // Copy first 2 elements
             std::inserter(vec2, insert_pos));
    
    std::cout << "After: ";
    std::copy(vec2.begin(), vec2.end(),
             std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

void demonstrate_stream_iterators() {
    std::cout << "\n=== Stream Iterator Demo ===\n";
    
    // TODO: istream_iterator for reading
    std::string input_data = "100 200 300 400 500";
    std::istringstream iss(input_data);
    
    std::cout << "Reading numbers from string stream:\n";
    std::vector<int> numbers;
    
    // Read all numbers using istream_iterator
    std::copy(std::istream_iterator<int>(iss),
             std::istream_iterator<int>(),  // End-of-stream iterator
             std::back_inserter(numbers));
    
    std::cout << "Read " << numbers.size() << " numbers: ";
    std::copy(numbers.begin(), numbers.end(),
             std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    // TODO: ostream_iterator for writing
    std::ostringstream oss;
    std::cout << "Writing transformed numbers to string stream:\n";
    
    std::transform(numbers.begin(), numbers.end(),
                  std::ostream_iterator<int>(oss, ", "),
                  [](int n) { return n * 2; });
    
    std::string output = oss.str();
    std::cout << "Output string: " << output << "\n";
    
    // TODO: istreambuf_iterator for character-level reading
    std::string text_input = "Hello, World!";
    std::istringstream text_stream(text_input);
    
    std::cout << "Reading characters using istreambuf_iterator:\n";
    std::string chars;
    std::copy(std::istreambuf_iterator<char>(text_stream),
             std::istreambuf_iterator<char>(),
             std::back_inserter(chars));
    
    std::cout << "Read characters: \"" << chars << "\"\n";
}

// TODO: Combining multiple iterator adapters
void demonstrate_combined_adapters() {
    std::cout << "\n=== Combined Iterator Adapters Demo ===\n";
    
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // TODO: Use reverse iterator with stream output
    std::cout << "Reverse output to stream:\n";
    std::ostringstream oss;
    std::copy(numbers.rbegin(), numbers.rend(),
             std::ostream_iterator<int>(oss, "-"));
    std::cout << "Result: " << oss.str() << "\n";
    
    // TODO: Filter even numbers in reverse order to new container
    std::list<int> even_reversed;
    std::copy_if(numbers.rbegin(), numbers.rend(),
                std::front_inserter(even_reversed),
                [](int n) { return n % 2 == 0; });
    
    std::cout << "Even numbers in reverse, inserted at front: ";
    std::copy(even_reversed.begin(), even_reversed.end(),
             std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    // TODO: Transform and insert at specific position
    std::vector<int> result = {100, 200};
    auto middle_pos = result.begin() + 1;
    
    std::transform(numbers.begin(), numbers.begin() + 3,
                  std::inserter(result, middle_pos),
                  [](int n) { return n * 10; });
    
    std::cout << "After transform and insert: ";
    std::copy(result.begin(), result.end(),
             std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

int main() {
    demonstrate_reverse_iterators();
    demonstrate_insert_iterators();
    demonstrate_stream_iterators();
    demonstrate_combined_adapters();
    
    return 0;
}
```

**Learning Goals**:
- Reverse iterator usage and base() conversion
- Insert iterator variations and use cases
- Stream iterators for I/O operations
- Combining multiple iterator adapters

---

## Problem Set 2: Custom Iterator Implementation (60 minutes)

### Problem 2.1: Basic Custom Iterator (25 minutes)

**Background**: Implement your own iterator class to understand iterator requirements and enable range-based for loops.

**Task**: Create a custom container with its own iterator.

**Requirements**:
1. Implement all required iterator operations
2. Support range-based for loops
3. Meet iterator concept requirements
4. Handle edge cases properly

**Starter Code**:
```cpp
#include <iostream>
#include <iterator>
#include <algorithm>

template<typename T>
class SimpleVector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    
public:
    SimpleVector() : data_(nullptr), size_(0), capacity_(0) {}
    
    explicit SimpleVector(size_t initial_capacity) 
        : size_(0), capacity_(initial_capacity) {
        data_ = new T[capacity_];
    }
    
    ~SimpleVector() {
        delete[] data_;
    }
    
    // Copy constructor
    SimpleVector(const SimpleVector& other) 
        : size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    
    // Copy assignment
    SimpleVector& operator=(const SimpleVector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }
    
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize();
        }
        data_[size_++] = value;
    }
    
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }
    
    // TODO: Iterator class
    class iterator {
    private:
        T* ptr_;
        
    public:
        // TODO: Iterator traits - required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        // TODO: Constructor
        explicit iterator(T* ptr) : ptr_(ptr) {}
        
        // TODO: Dereference operators
        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }
        
        // TODO: Prefix increment
        iterator& operator++() {
            ++ptr_;
            return *this;
        }
        
        // TODO: Postfix increment
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr_;
            return temp;
        }
        
        // TODO: Prefix decrement
        iterator& operator--() {
            --ptr_;
            return *this;
        }
        
        // TODO: Postfix decrement
        iterator operator--(int) {
            iterator temp = *this;
            --ptr_;
            return temp;
        }
        
        // TODO: Random access operations
        iterator& operator+=(difference_type n) {
            ptr_ += n;
            return *this;
        }
        
        iterator& operator-=(difference_type n) {
            ptr_ -= n;
            return *this;
        }
        
        iterator operator+(difference_type n) const {
            return iterator(ptr_ + n);
        }
        
        iterator operator-(difference_type n) const {
            return iterator(ptr_ - n);
        }
        
        difference_type operator-(const iterator& other) const {
            return ptr_ - other.ptr_;
        }
        
        reference operator[](difference_type n) const {
            return ptr_[n];
        }
        
        // TODO: Comparison operators
        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }
        bool operator<=(const iterator& other) const { return ptr_ <= other.ptr_; }
        bool operator>(const iterator& other) const { return ptr_ > other.ptr_; }
        bool operator>=(const iterator& other) const { return ptr_ >= other.ptr_; }
    };
    
    // TODO: Const iterator
    class const_iterator {
    private:
        const T* ptr_;
        
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        explicit const_iterator(const T* ptr) : ptr_(ptr) {}
        
        // TODO: Allow conversion from iterator to const_iterator
        const_iterator(const iterator& it) : ptr_(&(*it)) {}
        
        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }
        
        const_iterator& operator++() {
            ++ptr_;
            return *this;
        }
        
        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++ptr_;
            return temp;
        }
        
        const_iterator& operator--() {
            --ptr_;
            return *this;
        }
        
        const_iterator operator--(int) {
            const_iterator temp = *this;
            --ptr_;
            return temp;
        }
        
        const_iterator& operator+=(difference_type n) {
            ptr_ += n;
            return *this;
        }
        
        const_iterator& operator-=(difference_type n) {
            ptr_ -= n;
            return *this;
        }
        
        const_iterator operator+(difference_type n) const {
            return const_iterator(ptr_ + n);
        }
        
        const_iterator operator-(difference_type n) const {
            return const_iterator(ptr_ - n);
        }
        
        difference_type operator-(const const_iterator& other) const {
            return ptr_ - other.ptr_;
        }
        
        reference operator[](difference_type n) const {
            return ptr_[n];
        }
        
        bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const const_iterator& other) const { return ptr_ < other.ptr_; }
        bool operator<=(const const_iterator& other) const { return ptr_ <= other.ptr_; }
        bool operator>(const const_iterator& other) const { return ptr_ > other.ptr_; }
        bool operator>=(const const_iterator& other) const { return ptr_ >= other.ptr_; }
    };
    
    // TODO: Begin and end methods
    iterator begin() { return iterator(data_); }
    iterator end() { return iterator(data_ + size_); }
    const_iterator begin() const { return const_iterator(data_); }
    const_iterator end() const { return const_iterator(data_ + size_); }
    const_iterator cbegin() const { return const_iterator(data_); }
    const_iterator cend() const { return const_iterator(data_ + size_); }
    
private:
    void resize() {
        size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        T* new_data = new T[new_capacity];
        
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
        
        std::cout << "Resized to capacity: " << capacity_ << "\n";
    }
};

// TODO: Global operators for iterator arithmetic
template<typename T>
typename SimpleVector<T>::iterator operator+(
    typename SimpleVector<T>::iterator::difference_type n,
    const typename SimpleVector<T>::iterator& it) {
    return it + n;
}

void test_custom_iterator() {
    std::cout << "=== Custom Iterator Test ===\n";
    
    SimpleVector<int> vec(5);
    
    // TODO: Fill vector
    for (int i = 1; i <= 10; ++i) {
        vec.push_back(i * i);
    }
    
    std::cout << "Vector contents using iterator:\n";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // TODO: Test range-based for loop
    std::cout << "Vector contents using range-based for:\n";
    for (const auto& value : vec) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    
    // TODO: Test STL algorithms
    std::cout << "Using STL find:\n";
    auto it = std::find(vec.begin(), vec.end(), 25);
    if (it != vec.end()) {
        std::cout << "Found 25 at position: " << (it - vec.begin()) << "\n";
    }
    
    // TODO: Test random access
    std::cout << "Random access test:\n";
    auto middle = vec.begin() + vec.size() / 2;
    std::cout << "Middle element: " << *middle << "\n";
    std::cout << "Element [2]: " << vec.begin()[2] << "\n";
    
    // TODO: Test const iterator
    std::cout << "Using const iterator:\n";
    const auto& const_vec = vec;
    for (auto cit = const_vec.cbegin(); cit != const_vec.cend(); ++cit) {
        std::cout << *cit << " ";
    }
    std::cout << "\n";
    
    // TODO: Test with STL sort
    std::cout << "Sorting with STL:\n";
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    for (const auto& value : vec) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}

int main() {
    test_custom_iterator();
    return 0;
}
```

**Learning Goals**:
- Iterator trait requirements
- Implementing all required iterator operations
- Supporting STL algorithm compatibility
- Const vs non-const iterator design

---

### Problem 2.2: Advanced Iterator Patterns (20 minutes)

**Background**: Implement specialized iterators for unique data access patterns.

**Task**: Create iterators with filtering, transformation, and other advanced behaviors.

**Requirements**:
1. Implement a filtering iterator that skips certain elements
2. Create a transform iterator that modifies values on access
3. Build a counting iterator for generating sequences
4. Handle iterator composition and chaining

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include <algorithm>

// TODO: Filtering iterator - skips elements that don't match predicate
template<typename Iterator, typename Predicate>
class filter_iterator {
private:
    Iterator current_;
    Iterator end_;
    Predicate pred_;
    
    void advance_to_valid() {
        while (current_ != end_ && !pred_(*current_)) {
            ++current_;
        }
    }
    
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using pointer = typename std::iterator_traits<Iterator>::pointer;
    using reference = typename std::iterator_traits<Iterator>::reference;
    
    filter_iterator(Iterator current, Iterator end, Predicate pred)
        : current_(current), end_(end), pred_(pred) {
        advance_to_valid();
    }
    
    reference operator*() const { return *current_; }
    pointer operator->() const { return current_.operator->(); }
    
    filter_iterator& operator++() {
        ++current_;
        advance_to_valid();
        return *this;
    }
    
    filter_iterator operator++(int) {
        filter_iterator temp = *this;
        ++(*this);
        return temp;
    }
    
    bool operator==(const filter_iterator& other) const {
        return current_ == other.current_;
    }
    
    bool operator!=(const filter_iterator& other) const {
        return !(*this == other);
    }
    
    Iterator base() const { return current_; }
};

// TODO: Helper function to create filter iterators
template<typename Iterator, typename Predicate>
filter_iterator<Iterator, Predicate> make_filter_iterator(
    Iterator current, Iterator end, Predicate pred) {
    return filter_iterator<Iterator, Predicate>(current, end, pred);
}

// TODO: Transform iterator - applies function to elements on access
template<typename Iterator, typename Function>
class transform_iterator {
private:
    Iterator current_;
    Function func_;
    
public:
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using value_type = std::invoke_result_t<Function, typename std::iterator_traits<Iterator>::reference>;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using pointer = void;  // Not meaningful for transform iterator
    using reference = value_type;  // Return by value
    
    transform_iterator(Iterator current, Function func)
        : current_(current), func_(func) {}
    
    reference operator*() const { return func_(*current_); }
    
    transform_iterator& operator++() {
        ++current_;
        return *this;
    }
    
    transform_iterator operator++(int) {
        transform_iterator temp = *this;
        ++current_;
        return temp;
    }
    
    transform_iterator& operator--() {
        --current_;
        return *this;
    }
    
    transform_iterator operator--(int) {
        transform_iterator temp = *this;
        --current_;
        return temp;
    }
    
    // TODO: Random access operations (if base iterator supports them)
    template<typename Iter = Iterator>
    auto operator+=(difference_type n) 
        -> std::enable_if_t<std::is_same_v<
            typename std::iterator_traits<Iter>::iterator_category,
            std::random_access_iterator_tag>, transform_iterator&> {
        current_ += n;
        return *this;
    }
    
    template<typename Iter = Iterator>
    auto operator+(difference_type n) const
        -> std::enable_if_t<std::is_same_v<
            typename std::iterator_traits<Iter>::iterator_category,
            std::random_access_iterator_tag>, transform_iterator> {
        return transform_iterator(current_ + n, func_);
    }
    
    bool operator==(const transform_iterator& other) const {
        return current_ == other.current_;
    }
    
    bool operator!=(const transform_iterator& other) const {
        return !(*this == other);
    }
    
    Iterator base() const { return current_; }
};

// TODO: Helper function to create transform iterators
template<typename Iterator, typename Function>
transform_iterator<Iterator, Function> make_transform_iterator(
    Iterator current, Function func) {
    return transform_iterator<Iterator, Function>(current, func);
}

// TODO: Counting iterator - generates sequence of numbers
template<typename T>
class counting_iterator {
private:
    T value_;
    
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;
    
    explicit counting_iterator(T start_value = T{}) : value_(start_value) {}
    
    reference operator*() const { return value_; }
    pointer operator->() const { return &value_; }
    
    counting_iterator& operator++() {
        ++value_;
        return *this;
    }
    
    counting_iterator operator++(int) {
        counting_iterator temp = *this;
        ++value_;
        return temp;
    }
    
    counting_iterator& operator--() {
        --value_;
        return *this;
    }
    
    counting_iterator operator--(int) {
        counting_iterator temp = *this;
        --value_;
        return temp;
    }
    
    counting_iterator& operator+=(difference_type n) {
        value_ += n;
        return *this;
    }
    
    counting_iterator& operator-=(difference_type n) {
        value_ -= n;
        return *this;
    }
    
    counting_iterator operator+(difference_type n) const {
        return counting_iterator(value_ + n);
    }
    
    counting_iterator operator-(difference_type n) const {
        return counting_iterator(value_ - n);
    }
    
    difference_type operator-(const counting_iterator& other) const {
        return value_ - other.value_;
    }
    
    reference operator[](difference_type n) const {
        return *((*this) + n);
    }
    
    bool operator==(const counting_iterator& other) const {
        return value_ == other.value_;
    }
    
    bool operator!=(const counting_iterator& other) const {
        return !(*this == other);
    }
    
    bool operator<(const counting_iterator& other) const {
        return value_ < other.value_;
    }
    
    bool operator<=(const counting_iterator& other) const {
        return value_ <= other.value_;
    }
    
    bool operator>(const counting_iterator& other) const {
        return value_ > other.value_;
    }
    
    bool operator>=(const counting_iterator& other) const {
        return value_ >= other.value_;
    }
};

void test_advanced_iterators() {
    std::cout << "=== Advanced Iterator Patterns Test ===\n";
    
    // TODO: Test filter iterator
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    
    std::cout << "Original numbers: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    
    // Filter even numbers
    auto even_predicate = [](int n) { return n % 2 == 0; };
    auto even_begin = make_filter_iterator(numbers.begin(), numbers.end(), even_predicate);
    auto even_end = make_filter_iterator(numbers.end(), numbers.end(), even_predicate);
    
    std::cout << "Even numbers (filtered): ";
    for (auto it = even_begin; it != even_end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // TODO: Test transform iterator
    auto square_transform = [](int n) { return n * n; };
    auto square_begin = make_transform_iterator(numbers.begin(), square_transform);
    auto square_end = make_transform_iterator(numbers.end(), square_transform);
    
    std::cout << "Squared numbers (transformed): ";
    for (auto it = square_begin; it != square_end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // TODO: Test counting iterator
    std::cout << "Counting iterator (0 to 10): ";
    counting_iterator<int> count_begin(0);
    counting_iterator<int> count_end(11);
    
    for (auto it = count_begin; it != count_end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // TODO: Combine iterators - filter evens and then square them
    std::cout << "Combined: filter evens then square: ";
    auto combined_begin = make_transform_iterator(
        make_filter_iterator(numbers.begin(), numbers.end(), even_predicate),
        square_transform);
    auto combined_end = make_transform_iterator(
        make_filter_iterator(numbers.end(), numbers.end(), even_predicate),
        square_transform);
    
    for (auto it = combined_begin; it != combined_end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // TODO: Use with STL algorithms
    std::cout << "Using filter iterator with STL accumulate: ";
    int sum = std::accumulate(even_begin, even_end, 0);
    std::cout << "Sum of even numbers: " << sum << "\n";
}

int main() {
    test_advanced_iterators();
    return 0;
}
```

**Learning Goals**:
- Specialized iterator implementation
- Iterator composition and chaining
- SFINAE for conditional operations
- Advanced iterator trait usage

---

### Problem 2.3: Iterator Concepts and Validation (15 minutes)

**Background**: Understand and validate iterator concepts, ensuring your iterators meet C++ standard requirements.

**Task**: Create iterator concept checking and validation utilities.

**Requirements**:
1. Implement concept checking for iterator categories
2. Create validation functions for iterator requirements
3. Test iterator behavior with edge cases
4. Ensure STL algorithm compatibility

**Starter Code**:
```cpp
#include <iostream>
#include <type_traits>
#include <iterator>
#include <vector>
#include <concepts>

// TODO: Concept checking utilities for C++20 (or SFINAE for C++17)
#if __cplusplus >= 202002L
// C++20 concepts
template<typename I>
concept InputIterator = std::input_iterator<I>;

template<typename I>
concept ForwardIterator = std::forward_iterator<I>;

template<typename I> 
concept BidirectionalIterator = std::bidirectional_iterator<I>;

template<typename I>
concept RandomAccessIterator = std::random_access_iterator<I>;

#else
// C++17 SFINAE-based checking
template<typename I>
struct is_input_iterator : std::is_base_of<
    std::input_iterator_tag,
    typename std::iterator_traits<I>::iterator_category> {};

template<typename I>
struct is_forward_iterator : std::is_base_of<
    std::forward_iterator_tag,
    typename std::iterator_traits<I>::iterator_category> {};

template<typename I>
struct is_bidirectional_iterator : std::is_base_of<
    std::bidirectional_iterator_tag,
    typename std::iterator_traits<I>::iterator_category> {};

template<typename I>
struct is_random_access_iterator : std::is_base_of<
    std::random_access_iterator_tag,
    typename std::iterator_traits<I>::iterator_category> {};

template<typename I>
constexpr bool InputIterator = is_input_iterator<I>::value;

template<typename I>
constexpr bool ForwardIterator = is_forward_iterator<I>::value;

template<typename I>
constexpr bool BidirectionalIterator = is_bidirectional_iterator<I>::value;

template<typename I>
constexpr bool RandomAccessIterator = is_random_access_iterator<I>::value;
#endif

// TODO: Iterator validation class
class IteratorValidator {
public:
    template<typename Iterator>
    static void validate_input_iterator(Iterator begin, Iterator end, 
                                      const std::string& name) {
        std::cout << "\n--- Validating " << name << " as Input Iterator ---\n";
        
        static_assert(InputIterator<Iterator>, 
                     "Iterator must satisfy InputIterator requirements");
        
        std::cout << "✓ Iterator category check passed\n";
        
        // TODO: Test basic operations
        if (begin != end) {
            std::cout << "✓ Inequality comparison works\n";
            
            auto value = *begin;  // Dereference
            std::cout << "✓ Dereference works: " << value << "\n";
            
            ++begin;  // Pre-increment
            std::cout << "✓ Pre-increment works\n";
            
            if (begin != end) {
                begin++;  // Post-increment
                std::cout << "✓ Post-increment works\n";
            }
        }
        
        std::cout << "✓ Input iterator validation complete\n";
    }
    
    template<typename Iterator>
    static void validate_forward_iterator(Iterator begin, Iterator end,
                                        const std::string& name) {
        std::cout << "\n--- Validating " << name << " as Forward Iterator ---\n";
        
        static_assert(ForwardIterator<Iterator>,
                     "Iterator must satisfy ForwardIterator requirements");
        
        validate_input_iterator(begin, end, name + " (input part)");
        
        // TODO: Test forward iterator specific requirements
        if (begin != end) {
            Iterator copy = begin;  // Copy construction
            std::cout << "✓ Copy construction works\n";
            
            if (*copy == *begin) {
                std::cout << "✓ Multi-pass guarantee works\n";
            }
            
            Iterator assigned;
            assigned = begin;  // Assignment
            std::cout << "✓ Assignment works\n";
        }
        
        std::cout << "✓ Forward iterator validation complete\n";
    }
    
    template<typename Iterator>
    static void validate_bidirectional_iterator(Iterator begin, Iterator end,
                                              const std::string& name) {
        std::cout << "\n--- Validating " << name << " as Bidirectional Iterator ---\n";
        
        static_assert(BidirectionalIterator<Iterator>,
                     "Iterator must satisfy BidirectionalIterator requirements");
        
        validate_forward_iterator(begin, end, name + " (forward part)");
        
        // TODO: Test bidirectional operations
        if (begin != end) {
            auto it = begin;
            ++it;  // Move forward
            
            if (it != end) {
                --it;  // Pre-decrement
                std::cout << "✓ Pre-decrement works\n";
                
                if (it == begin) {
                    std::cout << "✓ Bidirectional consistency verified\n";
                }
                
                ++it;
                it--;  // Post-decrement
                std::cout << "✓ Post-decrement works\n";
            }
        }
        
        std::cout << "✓ Bidirectional iterator validation complete\n";
    }
    
    template<typename Iterator>
    static void validate_random_access_iterator(Iterator begin, Iterator end,
                                              const std::string& name) {
        std::cout << "\n--- Validating " << name << " as Random Access Iterator ---\n";
        
        static_assert(RandomAccessIterator<Iterator>,
                     "Iterator must satisfy RandomAccessIterator requirements");
        
        validate_bidirectional_iterator(begin, end, name + " (bidirectional part)");
        
        // TODO: Test random access operations
        auto size = std::distance(begin, end);
        if (size > 0) {
            // Arithmetic operations
            auto middle = begin + size / 2;
            std::cout << "✓ Iterator + integer works\n";
            
            auto back_to_begin = middle - size / 2;
            std::cout << "✓ Iterator - integer works\n";
            
            auto difference = middle - begin;
            std::cout << "✓ Iterator difference works: " << difference << "\n";
            
            // Compound assignment
            auto it = begin;
            it += size / 2;
            std::cout << "✓ Compound += works\n";
            
            it -= size / 2;
            std::cout << "✓ Compound -= works\n";
            
            // Subscript operator
            if (size > 1) {
                auto value = begin[0];
                std::cout << "✓ Subscript operator works: " << value << "\n";
            }
            
            // Comparison operators
            if (size > 1) {
                std::cout << "✓ Less than: " << (begin < (begin + 1)) << "\n";
                std::cout << "✓ Less equal: " << (begin <= begin) << "\n";
                std::cout << "✓ Greater than: " << ((begin + 1) > begin) << "\n";
                std::cout << "✓ Greater equal: " << (begin >= begin) << "\n";
            }
        }
        
        std::cout << "✓ Random access iterator validation complete\n";
    }
    
    // TODO: Test iterator with STL algorithms
    template<typename Iterator>
    static void test_stl_compatibility(Iterator begin, Iterator end,
                                     const std::string& name) {
        std::cout << "\n--- Testing STL Compatibility for " << name << " ---\n";
        
        // TODO: Test algorithms that work with this iterator category
        if constexpr (InputIterator<Iterator>) {
            auto count = std::distance(begin, end);
            std::cout << "✓ std::distance works: " << count << " elements\n";
            
            if (begin != end) {
                auto found = std::find(begin, end, *begin);
                if (found != end) {
                    std::cout << "✓ std::find works\n";
                }
            }
        }
        
        if constexpr (ForwardIterator<Iterator>) {
            if (begin != end) {
                auto adjacent = std::adjacent_find(begin, end);
                std::cout << "✓ std::adjacent_find works (found: " 
                          << (adjacent != end) << ")\n";
            }
        }
        
        if constexpr (BidirectionalIterator<Iterator>) {
            // Test reverse operations
            std::cout << "✓ Reverse iterator operations supported\n";
        }
        
        if constexpr (RandomAccessIterator<Iterator>) {
            if (std::distance(begin, end) > 1) {
                // Create a copy to sort
                std::vector<typename std::iterator_traits<Iterator>::value_type> 
                    temp(begin, end);
                
                std::sort(temp.begin(), temp.end());
                std::cout << "✓ Compatible with std::sort (tested on copy)\n";
            }
        }
    }
};

void test_iterator_validation() {
    std::cout << "=== Iterator Validation Tests ===\n";
    
    // TODO: Test with standard containers
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::list<int> lst = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::forward_list<int> flist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Validate vector iterators (random access)
    IteratorValidator::validate_random_access_iterator(
        vec.begin(), vec.end(), "std::vector<int>::iterator");
    IteratorValidator::test_stl_compatibility(
        vec.begin(), vec.end(), "std::vector<int>::iterator");
    
    // Validate list iterators (bidirectional)
    IteratorValidator::validate_bidirectional_iterator(
        lst.begin(), lst.end(), "std::list<int>::iterator");
    IteratorValidator::test_stl_compatibility(
        lst.begin(), lst.end(), "std::list<int>::iterator");
    
    // Validate forward_list iterators (forward)
    IteratorValidator::validate_forward_iterator(
        flist.begin(), flist.end(), "std::forward_list<int>::iterator");
    IteratorValidator::test_stl_compatibility(
        flist.begin(), flist.end(), "std::forward_list<int>::iterator");
}

int main() {
    test_iterator_validation();
    return 0;
}
```

**Learning Goals**:
- Iterator concept requirements
- Validation and testing techniques
- STL algorithm compatibility
- Edge case handling

---

## Problem Set 3: Advanced Iterator Patterns (30 minutes)

[Rest of Problem Set 3 content following similar pattern...]

## Success Criteria

You've mastered Chapter 14 iterator concepts when you can:
- Understand and use different iterator categories appropriately
- Implement custom iterators that meet C++ standard requirements
- Create specialized iterators for advanced data access patterns
- Compose STL algorithms effectively using iterators
- Validate iterator implementations for correctness

Remember: Iterators are the bridge between containers and algorithms. Mastering them unlocks the full power of the STL!