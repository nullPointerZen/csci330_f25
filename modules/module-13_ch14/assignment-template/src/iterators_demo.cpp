// HW_14: Iterators and Algorithms
// Time: 2.25 hours (45 minutes per problem set)
// Topics: Iterator categories, STL algorithms, custom iterators

#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <sstream>

// ============================================================================
// PROBLEM SET 1: Iterator Fundamentals (45 minutes)
// ============================================================================

void iterator_categories() {
    printf("=== Iterator Categories ===\n");
    
    // TODO 1: Input Iterator (read-only, single pass)
    printf("Input Iterator - std::istream_iterator:\n");
    
    std::istringstream input("10 20 30 40 50");
    std::istream_iterator<int> input_it(input);
    std::istream_iterator<int> input_end;
    
    printf("  Reading from stream: ");
    while (input_it != input_end) {
        printf("%d ", *input_it);
        ++input_it;  // Single pass, forward only
    }
    printf("\n");
    
    // TODO 2: Output Iterator (write-only)
    printf("\nOutput Iterator - std::ostream_iterator:\n");
    
    std::vector<int> data = {1, 2, 3, 4, 5};
    printf("  Writing to output: ");
    std::copy(data.begin(), data.end(), 
              std::ostream_iterator<int>(std::cout, " "));
    printf("\n");
    
    // TODO 3: Forward Iterator (multi-pass, forward only)
    printf("\nForward Iterator - std::forward_list:\n");
    
    std::vector<int> forward_data = {100, 200, 300};  // Using vector to simulate
    auto forward_it = forward_data.begin();
    
    printf("  Forward iteration: ");
    for (auto it = forward_it; it != forward_data.end(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    // Can make multiple passes
    printf("  Second pass: ");
    for (auto it = forward_it; it != forward_data.end(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    // TODO 4: Bidirectional Iterator (forward and backward)
    printf("\nBidirectional Iterator - std::list:\n");
    
    std::list<int> bidirectional_data = {10, 20, 30, 40};
    
    printf("  Forward: ");
    for (auto it = bidirectional_data.begin(); it != bidirectional_data.end(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    printf("  Backward: ");
    for (auto it = bidirectional_data.rbegin(); it != bidirectional_data.rend(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    // TODO 5: Random Access Iterator (jump to any position)
    printf("\nRandom Access Iterator - std::vector:\n");
    
    std::vector<int> random_data = {5, 15, 25, 35, 45, 55};
    
    printf("  Random access: ");
    printf("data[0]=%d ", random_data[0]);
    printf("data[3]=%d ", random_data[3]);
    printf("data[5]=%d\n", random_data[5]);
    
    auto it = random_data.begin();
    printf("  Iterator arithmetic: ");
    printf("*(it+2)=%d ", *(it + 2));
    printf("*(it+4)=%d ", *(it + 4));
    printf("distance=%ld\n", std::distance(it, it + 4));
    
    printf("\n");
}

void iterator_operations() {
    printf("=== Iterator Operations ===\n");
    
    // TODO 6: std::advance and std::distance
    printf("Iterator Navigation:\n");
    
    std::vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
    auto it = words.begin();
    printf("  Start position: %s\n", it->c_str());
    
    std::advance(it, 2);  // Move iterator forward by 2
    printf("  After advance(2): %s\n", it->c_str());
    
    auto distance = std::distance(words.begin(), it);
    printf("  Distance from begin: %ld\n", distance);
    
    // TODO 7: std::next and std::prev (C++11)
    printf("\nIterator Helper Functions:\n");
    
    auto next_it = std::next(words.begin(), 3);
    printf("  next(begin, 3): %s\n", next_it->c_str());
    
    auto prev_it = std::prev(words.end(), 1);
    printf("  prev(end, 1): %s\n", prev_it->c_str());
    
    // Safe navigation without modifying original iterator
    it = words.begin();
    printf("  Original iterator still at: %s\n", it->c_str());
    
    printf("\n");
}

void range_based_access() {
    printf("=== Range-Based Access ===\n");
    
    // TODO 8: Container range access
    printf("Container Range Functions:\n");
    
    std::deque<int> container = {10, 20, 30, 40, 50};
    
    printf("  Using begin()/end(): ");
    for (auto it = container.begin(); it != container.end(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    printf("  Using cbegin()/cend(): ");
    for (auto it = container.cbegin(); it != container.cend(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    printf("  Using rbegin()/rend(): ");
    for (auto it = container.rbegin(); it != container.rend(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    // TODO 9: Range-based for loop (C++11)
    printf("\nRange-Based For Loops:\n");
    
    printf("  Range-for (read-only): ");
    for (const auto& value : container) {
        printf("%d ", value);
    }
    printf("\n");
    
    printf("  Range-for (modifying): ");
    for (auto& value : container) {
        value *= 2;  // Double each value
        printf("%d ", value);
    }
    printf("\n");
    
    // TODO 10: std::begin/std::end with arrays
    printf("\nStandard begin/end with Arrays:\n");
    
    int array[] = {100, 200, 300, 400};
    
    printf("  Array iteration: ");
    for (auto it = std::begin(array); it != std::end(array); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    printf("  Array size: %ld\n", std::end(array) - std::begin(array));
    
    printf("\n");
}

void problem_set_1_demo() {
    printf("=== Problem Set 1: Iterator Fundamentals ===\n\n");
    
    iterator_categories();
    iterator_operations();
    range_based_access();
}

// ============================================================================
// PROBLEM SET 2: STL Algorithms (45 minutes)
// ============================================================================

void non_modifying_algorithms() {
    printf("=== Non-Modifying Algorithms ===\n");
    
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    
    // TODO 11: Finding algorithms
    printf("Finding Algorithms:\n");
    
    // std::find
    auto found_it = std::find(data.begin(), data.end(), 5);
    if (found_it != data.end()) {
        auto position = std::distance(data.begin(), found_it);
        printf("  find(5): Found at position %ld\n", position);
    }
    
    // std::find_if with predicate
    auto even_it = std::find_if(data.begin(), data.end(), 
                               [](int n) { return n % 2 == 0; });
    if (even_it != data.end()) {
        printf("  find_if(even): First even number is %d\n", *even_it);
    }
    
    // std::count and std::count_if
    auto count_1 = std::count(data.begin(), data.end(), 1);
    printf("  count(1): %ld occurrences\n", count_1);
    
    auto count_odd = std::count_if(data.begin(), data.end(),
                                  [](int n) { return n % 2 == 1; });
    printf("  count_if(odd): %ld odd numbers\n", count_odd);
    
    // TODO 12: Search algorithms
    printf("\nSearch Algorithms:\n");
    
    std::vector<int> pattern = {1, 5};
    auto search_it = std::search(data.begin(), data.end(), 
                                pattern.begin(), pattern.end());
    if (search_it != data.end()) {
        auto pos = std::distance(data.begin(), search_it);
        printf("  search([1,5]): Pattern found at position %ld\n", pos);
    }
    
    // std::adjacent_find
    auto adjacent_it = std::adjacent_find(data.begin(), data.end());
    if (adjacent_it != data.end()) {
        auto pos = std::distance(data.begin(), adjacent_it);
        printf("  adjacent_find: Found adjacent equal at position %ld (%d)\n", 
               pos, *adjacent_it);
    }
    
    // TODO 13: Comparison algorithms
    printf("\nComparison Algorithms:\n");
    
    std::vector<int> data2 = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::vector<int> data3 = {3, 1, 4, 2, 5, 9, 2, 6, 5, 3};
    
    bool equal1 = std::equal(data.begin(), data.end(), data2.begin());
    printf("  equal(data, data2): %s\n", equal1 ? "true" : "false");
    
    bool equal2 = std::equal(data.begin(), data.end(), data3.begin());
    printf("  equal(data, data3): %s\n", equal2 ? "true" : "false");
    
    // Lexicographical comparison
    bool less = std::lexicographical_compare(data.begin(), data.end(),
                                           data3.begin(), data3.end());
    printf("  lexicographical_compare(data < data3): %s\n", less ? "true" : "false");
    
    printf("\n");
}

void modifying_algorithms() {
    printf("=== Modifying Algorithms ===\n");
    
    // TODO 14: Copy algorithms
    printf("Copy Algorithms:\n");
    
    std::vector<int> source = {10, 20, 30, 40, 50};
    std::vector<int> dest(source.size());
    
    std::copy(source.begin(), source.end(), dest.begin());
    printf("  copy result: ");
    for (int val : dest) printf("%d ", val);
    printf("\n");
    
    // Copy with condition
    std::vector<int> large_nums;
    std::copy_if(source.begin(), source.end(), std::back_inserter(large_nums),
                [](int n) { return n > 25; });
    printf("  copy_if(>25): ");
    for (int val : large_nums) printf("%d ", val);
    printf("\n");
    
    // TODO 15: Transform algorithms
    printf("\nTransform Algorithms:\n");
    
    std::vector<int> original = {1, 2, 3, 4, 5};
    std::vector<int> squared(original.size());
    
    std::transform(original.begin(), original.end(), squared.begin(),
                  [](int n) { return n * n; });
    printf("  transform(square): ");
    for (int val : squared) printf("%d ", val);
    printf("\n");
    
    // Binary transform (two input ranges)
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {10, 20, 30, 40, 50};
    std::vector<int> sum(a.size());
    
    std::transform(a.begin(), a.end(), b.begin(), sum.begin(),
                  [](int x, int y) { return x + y; });
    printf("  transform(add): ");
    for (int val : sum) printf("%d ", val);
    printf("\n");
    
    // TODO 16: Modify-in-place algorithms
    printf("\nModify-in-Place Algorithms:\n");
    
    std::vector<int> modify_data = {5, 2, 8, 2, 1, 9, 2, 4};
    
    printf("  Original: ");
    for (int val : modify_data) printf("%d ", val);
    printf("\n");
    
    // Replace all 2s with 99
    std::replace(modify_data.begin(), modify_data.end(), 2, 99);
    printf("  replace(2→99): ");
    for (int val : modify_data) printf("%d ", val);
    printf("\n");
    
    // Replace values greater than 6 with 0
    std::replace_if(modify_data.begin(), modify_data.end(),
                   [](int n) { return n > 6; }, 0);
    printf("  replace_if(>6→0): ");
    for (int val : modify_data) printf("%d ", val);
    printf("\n");
    
    printf("\n");
}

void sorting_algorithms() {
    printf("=== Sorting Algorithms ===\n");
    
    // TODO 17: Basic sorting
    printf("Basic Sorting:\n");
    
    std::vector<int> unsorted = {64, 34, 25, 12, 22, 11, 90};
    
    printf("  Original: ");
    for (int val : unsorted) printf("%d ", val);
    printf("\n");
    
    std::sort(unsorted.begin(), unsorted.end());
    printf("  sort(): ");
    for (int val : unsorted) printf("%d ", val);
    printf("\n");
    
    // Sort in descending order
    std::sort(unsorted.begin(), unsorted.end(), std::greater<int>());
    printf("  sort(descending): ");
    for (int val : unsorted) printf("%d ", val);
    printf("\n");
    
    // TODO 18: Specialized sorting
    printf("\nSpecialized Sorting:\n");
    
    std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // Partial sort - sort first 4 elements
    std::vector<int> partial_data = data;
    std::partial_sort(partial_data.begin(), partial_data.begin() + 4, partial_data.end());
    printf("  partial_sort(4): ");
    for (int val : partial_data) printf("%d ", val);
    printf("\n");
    
    // nth_element - partition around the nth element
    std::vector<int> nth_data = data;
    std::nth_element(nth_data.begin(), nth_data.begin() + 4, nth_data.end());
    printf("  nth_element(4): ");
    for (int val : nth_data) printf("%d ", val);
    printf(" (5th element: %d)\n", nth_data[4]);
    
    // TODO 19: Stable sort (preserves relative order)
    printf("\nStable Sort with Custom Objects:\n");
    
    struct Student {
        std::string name;
        int grade;
    };
    
    std::vector<Student> students = {
        {"Alice", 85}, {"Bob", 90}, {"Carol", 85}, {"Dave", 90}, {"Eve", 85}
    };
    
    printf("  Original order:\n");
    for (const auto& s : students) {
        printf("    %s: %d\n", s.name.c_str(), s.grade);
    }
    
    // Stable sort by grade (preserves original order for equal grades)
    std::stable_sort(students.begin(), students.end(),
                    [](const Student& a, const Student& b) {
                        return a.grade > b.grade;  // Descending by grade
                    });
    
    printf("  After stable_sort by grade (desc):\n");
    for (const auto& s : students) {
        printf("    %s: %d\n", s.name.c_str(), s.grade);
    }
    
    printf("\n");
}

void problem_set_2_demo() {
    printf("=== Problem Set 2: STL Algorithms ===\n\n");
    
    non_modifying_algorithms();
    modifying_algorithms();
    sorting_algorithms();
}

// ============================================================================
// PROBLEM SET 3: Custom Iterators and Advanced Usage (45 minutes)
// ============================================================================

void iterator_adapters() {
    printf("=== Iterator Adapters ===\n");
    
    // TODO 20: Reverse iterators
    printf("Reverse Iterators:\n");
    
    std::vector<int> data = {1, 2, 3, 4, 5};
    
    printf("  Forward: ");
    for (auto it = data.begin(); it != data.end(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    printf("  Reverse: ");
    for (auto it = data.rbegin(); it != data.rend(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    // Manual reverse iterator creation
    printf("  make_reverse_iterator: ");
    for (auto it = std::make_reverse_iterator(data.end()); 
         it != std::make_reverse_iterator(data.begin()); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    // TODO 21: Insert iterators
    printf("\nInsert Iterators:\n");
    
    std::vector<int> source = {10, 20, 30};
    std::vector<int> dest = {1, 2, 3, 4, 5};
    
    printf("  Before insertion - dest: ");
    for (int val : dest) printf("%d ", val);
    printf("\n");
    
    // Back inserter
    std::copy(source.begin(), source.end(), std::back_inserter(dest));
    printf("  back_inserter: ");
    for (int val : dest) printf("%d ", val);
    printf("\n");
    
    // Insert at specific position
    auto insert_pos = dest.begin() + 3;
    std::copy(source.begin(), source.end(), std::inserter(dest, insert_pos));
    printf("  inserter(pos=3): ");
    for (int val : dest) printf("%d ", val);
    printf("\n");
    
    // TODO 22: Stream iterators
    printf("\nStream Iterators:\n");
    
    // Output to stringstream
    std::ostringstream oss;
    std::copy(source.begin(), source.end(), 
              std::ostream_iterator<int>(oss, " "));
    printf("  ostream_iterator: %s\n", oss.str().c_str());
    
    // Input from stringstream
    std::istringstream iss("100 200 300 400");
    std::vector<int> from_stream;
    std::copy(std::istream_iterator<int>(iss), std::istream_iterator<int>(),
              std::back_inserter(from_stream));
    printf("  istream_iterator: ");
    for (int val : from_stream) printf("%d ", val);
    printf("\n");
    
    printf("\n");
}

// TODO 23: Custom iterator implementation
template<typename T>
class SimpleVector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    
public:
    SimpleVector() : data_(nullptr), size_(0), capacity_(0) {}
    
    ~SimpleVector() {
        delete[] data_;
    }
    
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
            T* new_data = new T[capacity_];
            for (size_t i = 0; i < size_; i++) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
        }
        data_[size_++] = value;
    }
    
    // Custom iterator class
    class iterator {
    private:
        T* ptr_;
        
    public:
        // Iterator traits
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator(T* ptr) : ptr_(ptr) {}
        
        // Dereference
        reference operator*() { return *ptr_; }
        pointer operator->() { return ptr_; }
        
        // Increment/Decrement
        iterator& operator++() { ++ptr_; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++ptr_; return tmp; }
        iterator& operator--() { --ptr_; return *this; }
        iterator operator--(int) { iterator tmp = *this; --ptr_; return tmp; }
        
        // Arithmetic
        iterator operator+(difference_type n) { return iterator(ptr_ + n); }
        iterator operator-(difference_type n) { return iterator(ptr_ - n); }
        difference_type operator-(const iterator& other) { return ptr_ - other.ptr_; }
        
        // Comparison
        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }
    };
    
    iterator begin() { return iterator(data_); }
    iterator end() { return iterator(data_ + size_); }
    size_t size() const { return size_; }
};

void custom_iterator_implementation() {
    printf("=== Custom Iterator Implementation ===\n");
    
    // TODO: Test custom iterator
    printf("Custom SimpleVector Iterator:\n");
    
    SimpleVector<int> custom_vec;
    custom_vec.push_back(100);
    custom_vec.push_back(200);
    custom_vec.push_back(300);
    custom_vec.push_back(400);
    
    printf("  Using custom iterator: ");
    for (auto it = custom_vec.begin(); it != custom_vec.end(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    // Test with STL algorithms
    printf("  Using with STL algorithms:\n");
    
    auto found = std::find(custom_vec.begin(), custom_vec.end(), 300);
    if (found != custom_vec.end()) {
        printf("    find(300): Found at position %ld\n", 
               std::distance(custom_vec.begin(), found));
    }
    
    int sum = std::accumulate(custom_vec.begin(), custom_vec.end(), 0);
    printf("    accumulate: Sum = %d\n", sum);
    
    auto max_it = std::max_element(custom_vec.begin(), custom_vec.end());
    if (max_it != custom_vec.end()) {
        printf("    max_element: %d\n", *max_it);
    }
    
    printf("\n");
}

void algorithm_composition() {
    printf("=== Algorithm Composition ===\n");
    
    // TODO 24: Chaining algorithms for complex operations
    printf("Complex Data Processing Pipeline:\n");
    
    std::vector<int> raw_data = {15, 8, 23, 4, 42, 16, 31, 7, 19, 12, 6, 28};
    
    printf("  Original data: ");
    for (int val : raw_data) printf("%d ", val);
    printf("\n");
    
    // Step 1: Remove odd numbers
    std::vector<int> even_numbers;
    std::copy_if(raw_data.begin(), raw_data.end(), std::back_inserter(even_numbers),
                [](int n) { return n % 2 == 0; });
    
    printf("  Even numbers: ");
    for (int val : even_numbers) printf("%d ", val);
    printf("\n");
    
    // Step 2: Transform (square each number)
    std::vector<int> squared;
    std::transform(even_numbers.begin(), even_numbers.end(), std::back_inserter(squared),
                  [](int n) { return n * n; });
    
    printf("  Squared: ");
    for (int val : squared) printf("%d ", val);
    printf("\n");
    
    // Step 3: Sort in ascending order
    std::sort(squared.begin(), squared.end());
    
    printf("  Sorted: ");
    for (int val : squared) printf("%d ", val);
    printf("\n");
    
    // Step 4: Get top 3 largest (using partial_sort)
    if (squared.size() > 3) {
        std::partial_sort(squared.begin(), squared.begin() + 3, squared.end(), 
                         std::greater<int>());
        squared.resize(3);
    }
    
    printf("  Top 3 largest: ");
    for (int val : squared) printf("%d ", val);
    printf("\n");
    
    // TODO 25: Algorithm composition with lambda capture
    printf("\nStateful Algorithm Composition:\n");
    
    std::vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
    // Find words longer than average length
    double avg_length = std::accumulate(words.begin(), words.end(), 0.0,
        [](double sum, const std::string& word) {
            return sum + word.length();
        }) / words.size();
    
    printf("  Average word length: %.1f\n", avg_length);
    
    std::vector<std::string> long_words;
    std::copy_if(words.begin(), words.end(), std::back_inserter(long_words),
                [avg_length](const std::string& word) {
                    return word.length() > avg_length;
                });
    
    printf("  Words longer than average: ");
    for (const auto& word : long_words) {
        printf("%s ", word.c_str());
    }
    printf("\n");
    
    // Transform to uppercase
    std::transform(long_words.begin(), long_words.end(), long_words.begin(),
                  [](std::string word) {
                      std::transform(word.begin(), word.end(), word.begin(), ::toupper);
                      return word;
                  });
    
    printf("  Uppercase: ");
    for (const auto& word : long_words) {
        printf("%s ", word.c_str());
    }
    printf("\n");
    
    printf("\n");
}

void problem_set_3_demo() {
    printf("=== Problem Set 3: Custom Iterators and Advanced Usage ===\n\n");
    
    iterator_adapters();
    custom_iterator_implementation();
    algorithm_composition();
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("       HW_14: Iterators and Algorithms\n");
    printf("==========================================\n\n");
    
    // Problem Set 1: Iterator Fundamentals (45 min)
    problem_set_1_demo();
    
    // Problem Set 2: STL Algorithms (45 min)
    problem_set_2_demo();
    
    // Problem Set 3: Custom Iterators and Advanced Usage (45 min)
    problem_set_3_demo();
    
    printf("==========================================\n");
    printf("           Program Complete!\n");
    printf("==========================================\n");
    
    return 0;
}