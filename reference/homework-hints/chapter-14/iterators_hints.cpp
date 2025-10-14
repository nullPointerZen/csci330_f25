#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <string>
#include <algorithm>
#include <iterator>

// =============================================================================
// PROBLEM SET 1: ITERATOR BASICS
// =============================================================================

namespace problem_set_1 {

// Problem 1.1: First Steps with Iterators
void problem_1_1_iterator_basics() {
    std::cout << "\n=== Problem 1.1: Iterator Basics ===\n";

    std::vector<int> numbers{10, 20, 30, 40, 50};

    // Task 1: Print the first element using an iterator
    // begin() returns an iterator pointing to the first element
    // Dereference with * to get the value
    auto first_it = numbers.begin();
    std::cout << "First: " << *first_it << "\n";

    // Task 2: Print the last element using an iterator
    // end() returns an iterator ONE PAST the last element
    // So we need to go back one position using -- or (end() - 1)
    auto last_it = numbers.end() - 1;  // Or: auto last_it = std::prev(numbers.end());
    std::cout << "Last: " << *last_it << "\n";

    // Task 3: Print all elements using a traditional iterator loop
    // This is the classic C++ iterator pattern:
    // - Start at begin()
    // - Continue while not at end()
    // - Increment iterator with ++
    std::cout << "All: ";
    for(auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // KEY CONCEPTS:
    // - begin() points to first element
    // - end() points ONE PAST the last element (never dereference end()!)
    // - Use * to dereference iterator and get the value
    // - Use ++ to move iterator forward
}

// Problem 1.2: Iterator vs Index Comparison
void problem_1_2_iterator_comparison() {
    std::cout << "\n=== Problem 1.2: Iterator vs Index Comparison ===\n";

    std::vector<std::string> languages{"Python", "Java", "C++", "JavaScript"};

    // Version 1: Traditional index-based approach (like Java)
    // This works with containers that support random access (vector, array)
    std::cout << "Index-based:\n";
    for(size_t i = 0; i < languages.size(); ++i) {
        std::cout << "  " << i << ": " << languages[i] << "\n";
    }

    // Version 2: Iterator-based approach
    // This works with ALL containers (vector, list, set, etc.)
    // More flexible than index-based approach
    std::cout << "Iterator-based:\n";
    int index = 0;
    for(auto it = languages.begin(); it != languages.end(); ++it) {
        std::cout << "  " << index++ << ": " << *it << "\n";
    }

    // Version 3: Range-based for loop (like Python's "for item in list")
    // Cleanest and most modern approach when you just need to access each element
    std::cout << "Range-based:\n";
    index = 0;
    for(const auto& lang : languages) {
        std::cout << "  " << index++ << ": " << lang << "\n";
    }

    // COMPARISON:
    // Index-based: Familiar to Java programmers, but only works with random-access containers
    // Iterator-based: Works with all containers, but more verbose
    // Range-based: Most readable, works with all containers, preferred in modern C++
}

// Problem 1.3: Iterator Arithmetic
void problem_1_3_iterator_arithmetic() {
    std::cout << "\n=== Problem 1.3: Iterator Arithmetic ===\n";

    std::vector<int> data{1, 3, 5, 7, 9, 11, 13, 15};

    // Task 1: Print the element at position 3 (should be 7)
    // You can add an integer to an iterator to move it forward
    // This is called "random access" and only works with vector, array, deque
    auto it_pos_3 = data.begin() + 3;
    std::cout << "Element at position 3: " << *it_pos_3 << "\n";

    // Task 2: Print every other element starting from the beginning
    // We can increment by 2 in the loop to skip elements
    std::cout << "Every other element: ";
    for(auto it = data.begin(); it != data.end(); it += 2) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Task 3: Print the last 3 elements
    // Method 1: Use end() - n to go back n positions
    std::cout << "Last 3 elements: ";
    for(auto it = data.end() - 3; it != data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // ITERATOR ARITHMETIC (only for random-access iterators):
    // it + n        : Move forward n positions
    // it - n        : Move backward n positions
    // it += n       : Move iterator forward n positions in place
    // it1 - it2     : Distance between two iterators
    // it[n]         : Same as *(it + n)

    // Example: Distance between iterators
    auto first = data.begin();
    auto last = data.end();
    std::cout << "Distance from begin to end: " << (last - first) << " elements\n";
}

void run_all() {
    std::cout << "\n********* PROBLEM SET 1: ITERATOR BASICS *********\n";
    problem_1_1_iterator_basics();
    problem_1_2_iterator_comparison();
    problem_1_3_iterator_arithmetic();
}

} // namespace problem_set_1

// =============================================================================
// PROBLEM SET 2: RANGE-BASED FOR LOOPS AND PRACTICAL USAGE
// =============================================================================

namespace problem_set_2 {

// Problem 2.1: Modernizing Loops
void old_style_examples() {
    std::vector<double> grades{85.5, 92.0, 78.5, 96.0, 88.5};

    // Old style 1: Index-based
    std::cout << "Grades: ";
    for(size_t i = 0; i < grades.size(); ++i) {
        std::cout << grades[i] << " ";
    }
    std::cout << "\n";

    // Old style 2: Iterator-based
    double total = 0.0;
    for(auto it = grades.begin(); it != grades.end(); ++it) {
        total += *it;
    }
    std::cout << "Average: " << total / grades.size() << "\n";
}

void modern_style_examples() {
    std::vector<double> grades{85.5, 92.0, 78.5, 96.0, 88.5};

    // Modern style 1: Range-based for reading
    // Use const auto& for read-only access (no copying)
    std::cout << "Grades: ";
    for(const auto& grade : grades) {
        std::cout << grade << " ";
    }
    std::cout << "\n";

    // Modern style 2: Range-based for accumulation
    // Much cleaner and easier to read!
    double total = 0.0;
    for(const auto& grade : grades) {
        total += grade;
    }
    std::cout << "Average: " << total / grades.size() << "\n";

    // Alternative: Use standard algorithms (even more modern!)
    // std::accumulate from <numeric> header could also be used here
}

void problem_2_1_modernizing() {
    std::cout << "\n=== Problem 2.1: Modernizing Loops ===\n";

    std::cout << "Old style:\n";
    old_style_examples();

    std::cout << "\nModern style:\n";
    modern_style_examples();

    // KEY INSIGHT: Range-based for loops are:
    // 1. More readable (less boilerplate)
    // 2. Safer (no off-by-one errors)
    // 3. Work with all containers
    // 4. Similar to Python's "for item in list"
}

// Problem 2.2: Modifying Elements
void problem_2_2_modifying() {
    std::cout << "\n=== Problem 2.2: Modifying Elements ===\n";

    // Task 1: Double all numbers
    std::vector<int> numbers{1, 2, 3, 4, 5};

    // KEY: Use auto& (non-const reference) to modify elements
    for(auto& num : numbers) {
        num *= 2;  // Modifies the actual element in the vector
    }

    std::cout << "Doubled numbers: ";
    for(const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Task 2: Convert strings to uppercase (first character only)
    std::vector<std::string> words{"hello", "world", "cpp", "iterators"};

    for(auto& word : words) {
        if(!word.empty() && word[0] >= 'a' && word[0] <= 'z') {
            word[0] = word[0] - 'a' + 'A';  // Convert to uppercase
        }
    }

    std::cout << "Capitalized words: ";
    for(const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";

    // Task 3: Count positive numbers
    std::vector<int> mixed{-5, 3, -1, 8, 0, -2, 7};
    int positive_count = 0;

    // For counting, we only read, so use const auto&
    for(const auto& num : mixed) {
        if(num > 0) {
            ++positive_count;
        }
    }

    std::cout << "Positive numbers count: " << positive_count << "\n";

    // REFERENCE TYPES IN RANGE-BASED FOR:
    // auto         : Makes a copy of each element (modifications don't affect container)
    // auto&        : Reference to element (modifications DO affect container)
    // const auto&  : Read-only reference (can't modify, no copy made)
}

// Problem 2.3: Reference Semantics Practice
void problem_2_3_references() {
    std::cout << "\n=== Problem 2.3: Reference Semantics Practice ===\n";

    std::vector<std::string> names{"Alice", "Bob", "Charlie", "Diana"};

    // Scenario 1: Just reading/printing (most efficient)
    // Use const auto& to avoid copying and prevent modification
    std::cout << "Names: ";
    for(const auto& name : names) {
        std::cout << name << " ";
    }
    std::cout << "\n";

    // Scenario 2: Modifying each element
    // Use auto& to get a reference that allows modification
    std::cout << "Adding exclamation marks:\n";
    for(auto& name : names) {
        name += "!";
        std::cout << name << "\n";
    }

    // Scenario 3: Efficient reading (names already have ! from previous step)
    // Use const auto& for read-only access to large objects
    std::cout << "Efficient reading:\n";
    for(const auto& name : names) {
        std::cout << "Hello, " << name << "\n";
    }

    // PERFORMANCE COMPARISON:
    // auto         : Copies each string (expensive for large strings)
    // auto&        : No copy, can modify (use when you need to change elements)
    // const auto&  : No copy, read-only (BEST for reading large objects)
    //
    // For small types (int, char, etc.), the difference is negligible
    // For large types (string, vector, custom classes), const auto& is much faster
}

void run_all() {
    std::cout << "\n********* PROBLEM SET 2: RANGE-BASED FOR LOOPS *********\n";
    problem_2_1_modernizing();
    problem_2_2_modifying();
    problem_2_3_references();
}

} // namespace problem_set_2

// =============================================================================
// PROBLEM SET 3: ADVANCED ITERATOR PATTERNS
// =============================================================================

namespace problem_set_3 {

// Problem 3.1: Custom Iterator Functions

// Function to check if container contains a value
template<typename Container, typename T>
bool contains(const Container& container, const T& value) {
    // Traditional iterator approach
    for(auto it = container.begin(); it != container.end(); ++it) {
        if(*it == value) {
            return true;
        }
    }
    return false;

    // Alternative: Use std::find from <algorithm>
    // return std::find(container.begin(), container.end(), value) != container.end();
}

// Function to count occurrences of a value
template<typename Container, typename T>
size_t count_occurrences(const Container& container, const T& value) {
    size_t count = 0;

    // Iterate through container and count matches
    for(auto it = container.begin(); it != container.end(); ++it) {
        if(*it == value) {
            ++count;
        }
    }
    return count;

    // Alternative: Use std::count from <algorithm>
    // return std::count(container.begin(), container.end(), value);
}

// Function to print container in reverse
template<typename Container>
void print_reverse(const Container& container) {
    // Use reverse iterators: rbegin() and rend()
    // rbegin() points to the last element
    // rend() points to one before the first element
    for(auto it = container.rbegin(); it != container.rend(); ++it) {
        std::cout << *it << " ";
    }
}

void problem_3_1_custom_functions() {
    std::cout << "\n=== Problem 3.1: Custom Iterator Functions ===\n";

    std::vector<int> data{1, 3, 7, 3, 9, 3, 5};

    // Test contains function
    std::cout << "Contains 7: " << (contains(data, 7) ? "true" : "false") << "\n";
    std::cout << "Contains 4: " << (contains(data, 4) ? "true" : "false") << "\n";

    // Test count_occurrences function
    std::cout << "Count of 3: " << count_occurrences(data, 3) << "\n";

    // Test print_reverse function
    std::cout << "Reverse: ";
    print_reverse(data);
    std::cout << "\n";

    // These functions work with different container types!
    std::cout << "\nTesting with std::list:\n";
    std::list<std::string> words{"apple", "banana", "apple", "cherry"};
    std::cout << "Contains 'banana': " << (contains(words, std::string("banana")) ? "true" : "false") << "\n";
    std::cout << "Count of 'apple': " << count_occurrences(words, std::string("apple")) << "\n";
    std::cout << "Reverse: ";
    print_reverse(words);
    std::cout << "\n";

    // KEY CONCEPTS:
    // - Template functions work with any container type
    // - Iterators provide uniform interface across containers
    // - Reverse iterators (rbegin/rend) traverse backwards
}

// Problem 3.2: Safe Container Modification
void problem_3_2_safe_modification() {
    std::cout << "\n=== Problem 3.2: Safe Container Modification ===\n";

    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Original numbers: ";
    for(const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // BUGGY VERSION (DON'T USE THIS!):
    // for(auto it = numbers.begin(); it != numbers.end(); ++it) {
    //     if(*it % 2 == 0) {
    //         numbers.erase(it);  // BUG! This invalidates the iterator
    //                             // Next ++it will cause undefined behavior
    //     }
    // }

    // CORRECT VERSION:
    // erase() returns an iterator to the element after the erased one
    // We need to handle this carefully in our loop
    auto it = numbers.begin();
    while(it != numbers.end()) {
        if(*it % 2 == 0) {
            // erase returns iterator to next element
            // So we DON'T increment manually
            it = numbers.erase(it);
        } else {
            // Only increment if we didn't erase
            ++it;
        }
    }

    std::cout << "Odd numbers remaining: ";
    for(const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // ITERATOR INVALIDATION RULES:
    // - erase() invalidates the iterator pointing to the erased element
    // - insert() may invalidate all iterators (for vector)
    // - push_back() may invalidate all iterators (for vector)
    // - Always use the iterator returned by erase()!

    // ALTERNATIVE APPROACH: Use remove-erase idiom with algorithms
    std::vector<int> numbers2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    numbers2.erase(
        std::remove_if(numbers2.begin(), numbers2.end(),
                      [](int n) { return n % 2 == 0; }),
        numbers2.end()
    );
    // This is more efficient and safer for vectors
}

// Problem 3.3: Multi-Container Iterator Project
struct Student {
    std::string name;
    std::vector<double> grades;

    // Calculate average grade using iterators
    double calculate_average() const {
        if(grades.empty()) {
            return 0.0;
        }

        // Method 1: Traditional iterator loop
        double sum = 0.0;
        for(auto it = grades.begin(); it != grades.end(); ++it) {
            sum += *it;
        }
        return sum / grades.size();

        // Method 2: Range-based for (cleaner)
        // double sum = 0.0;
        // for(const auto& grade : grades) {
        //     sum += grade;
        // }
        // return sum / grades.size();
    }
};

void problem_3_3_gradebook() {
    std::cout << "\n=== Problem 3.3: Multi-Container Iterator Project ===\n";

    std::vector<Student> class_roster{
        {"Alice", {85.0, 92.0, 78.0, 95.0}},
        {"Bob", {88.0, 76.0, 92.0, 85.0}},
        {"Charlie", {92.0, 88.0, 95.0, 90.0}}
    };

    // Task 1: Print each student's name and average grade
    std::cout << "Student Averages:\n";
    for(const auto& student : class_roster) {
        std::cout << "  " << student.name << ": "
                  << student.calculate_average() << "\n";
    }

    // Task 2: Find the student with the highest average
    auto best_student = class_roster.begin();
    double highest_avg = best_student->calculate_average();

    for(auto it = class_roster.begin(); it != class_roster.end(); ++it) {
        double avg = it->calculate_average();
        if(avg > highest_avg) {
            highest_avg = avg;
            best_student = it;
        }
    }

    std::cout << "\nHighest average: " << best_student->name
              << " with " << highest_avg << "\n";

    // Task 3: Count students with average above 85.0
    int count_above_85 = 0;
    for(const auto& student : class_roster) {
        if(student.calculate_average() > 85.0) {
            ++count_above_85;
        }
    }

    std::cout << "Students with average > 85.0: " << count_above_85 << "\n";

    // INTEGRATION CONCEPTS:
    // - Iterating over vector of custom objects
    // - Each object contains its own vector (nested iteration)
    // - Combining different iteration patterns
    // - Using -> operator with iterators to access members
}

void run_all() {
    std::cout << "\n********* PROBLEM SET 3: ADVANCED ITERATOR PATTERNS *********\n";
    problem_3_1_custom_functions();
    problem_3_2_safe_modification();
    problem_3_3_gradebook();
}

} // namespace problem_set_3

// =============================================================================
// ADDITIONAL EXAMPLES: ITERATOR CATEGORIES AND ADVANCED CONCEPTS
// =============================================================================

namespace advanced_concepts {

// Iterator Categories Demonstration
void iterator_categories_demo() {
    std::cout << "\n=== Iterator Categories Demo ===\n";

    // 1. INPUT ITERATORS (read-only, single-pass)
    // Example: istream_iterator
    std::cout << "\n1. Input Iterators (reading from stream):\n";
    // std::istream_iterator<int> in_iter(std::cin);  // Would read from stdin
    // Single-pass: once you advance, can't go back

    // 2. OUTPUT ITERATORS (write-only, single-pass)
    std::cout << "\n2. Output Iterators (writing to stream):\n";
    std::vector<int> nums{1, 2, 3, 4, 5};
    std::ostream_iterator<int> out_iter(std::cout, " ");
    std::copy(nums.begin(), nums.end(), out_iter);
    std::cout << "\n";

    // 3. FORWARD ITERATORS (read/write, multi-pass, forward only)
    // Example: std::forward_list iterators
    std::cout << "\n3. Forward Iterators (forward_list):\n";
    std::forward_list<int> flist{10, 20, 30};
    for(auto it = flist.begin(); it != flist.end(); ++it) {
        std::cout << *it << " ";
        *it += 1;  // Can read and write
    }
    std::cout << "\n";

    // 4. BIDIRECTIONAL ITERATORS (forward + backward)
    // Example: std::list, std::set
    std::cout << "\n4. Bidirectional Iterators (list):\n";
    std::list<int> mylist{10, 20, 30, 40};
    auto it = mylist.end();
    --it;  // Can move backward!
    std::cout << "Last element: " << *it << "\n";

    // 5. RANDOM ACCESS ITERATORS (+ arbitrary jumps)
    // Example: std::vector, std::deque, arrays
    std::cout << "\n5. Random Access Iterators (vector):\n";
    std::vector<int> vec{10, 20, 30, 40, 50};
    auto vec_it = vec.begin();
    vec_it += 3;  // Jump forward by 3
    std::cout << "Element at begin+3: " << *vec_it << "\n";
    std::cout << "Element at begin+1 using []: " << vec.begin()[1] << "\n";
    std::cout << "Distance from begin to end: " << (vec.end() - vec.begin()) << "\n";

    // CAPABILITIES SUMMARY:
    // Input:         read, ++
    // Output:        write, ++
    // Forward:       read, write, ++, multi-pass
    // Bidirectional: Forward + --
    // Random Access: Bidirectional + arithmetic (+, -, +=, -=, [])
}

// Custom Iterator Example
class Range {
private:
    int start;
    int stop;
    int step;

public:
    Range(int start, int stop, int step = 1)
        : start(start), stop(stop), step(step) {}

    // Custom iterator class
    class Iterator {
    private:
        int current;
        int step;

    public:
        Iterator(int value, int step) : current(value), step(step) {}

        // Dereference operator
        int operator*() const { return current; }

        // Pre-increment operator
        Iterator& operator++() {
            current += step;
            return *this;
        }

        // Equality comparison
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        // For proper range checking
        bool operator<(const Iterator& other) const {
            return current < other.current;
        }
    };

    Iterator begin() const { return Iterator(start, step); }
    Iterator end() const { return Iterator(stop, step); }
};

void custom_iterator_demo() {
    std::cout << "\n=== Custom Iterator Demo ===\n";
    std::cout << "Python-style range in C++:\n";

    // Works like Python's range(0, 10, 2)
    std::cout << "Range(0, 10, 2): ";
    for(int i : Range(0, 10, 2)) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::cout << "Range(5, 20, 3): ";
    for(int i : Range(5, 20, 3)) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // KEY CONCEPTS:
    // - Custom iterators must implement:
    //   * operator* (dereference)
    //   * operator++ (increment)
    //   * operator!= (comparison)
    // - The class must provide begin() and end() methods
    // - Then it can be used with range-based for loops!
}

// Iterator Adaptors
void iterator_adaptors_demo() {
    std::cout << "\n=== Iterator Adaptors Demo ===\n";

    std::vector<int> numbers{1, 2, 3, 4, 5};

    // 1. Reverse Iterators
    std::cout << "\n1. Reverse Iterator:\n";
    std::cout << "Forward: ";
    for(auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\nReverse: ";
    for(auto it = numbers.rbegin(); it != numbers.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // 2. Insert Iterators (back_inserter, front_inserter, inserter)
    std::cout << "\n2. Insert Iterators:\n";
    std::vector<int> dest;
    std::copy(numbers.begin(), numbers.end(), std::back_inserter(dest));
    std::cout << "Copied using back_inserter: ";
    for(const auto& n : dest) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // 3. Move Iterators (C++11)
    std::cout << "\n3. Move Iterator:\n";
    std::vector<std::string> strings{"hello", "world", "cpp"};
    std::vector<std::string> moved;
    std::copy(std::make_move_iterator(strings.begin()),
              std::make_move_iterator(strings.end()),
              std::back_inserter(moved));
    std::cout << "After move, source is empty/moved-from: ";
    for(const auto& s : strings) {
        std::cout << "'" << s << "' ";
    }
    std::cout << "\n";
    std::cout << "Destination has values: ";
    for(const auto& s : moved) {
        std::cout << "'" << s << "' ";
    }
    std::cout << "\n";
}

// Common Iterator Patterns
void common_patterns() {
    std::cout << "\n=== Common Iterator Patterns ===\n";

    std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Pattern 1: Finding an element
    std::cout << "\n1. Finding an element:\n";
    auto found = std::find(data.begin(), data.end(), 5);
    if(found != data.end()) {
        std::cout << "Found: " << *found << "\n";
        std::cout << "Position: " << (found - data.begin()) << "\n";
    }

    // Pattern 2: Conditional finding
    std::cout << "\n2. Finding first element > 5:\n";
    auto found_if = std::find_if(data.begin(), data.end(),
                                  [](int n) { return n > 5; });
    if(found_if != data.end()) {
        std::cout << "Found: " << *found_if << "\n";
    }

    // Pattern 3: Transforming elements
    std::cout << "\n3. Transforming (squaring) elements:\n";
    std::vector<int> squared;
    std::transform(data.begin(), data.end(), std::back_inserter(squared),
                   [](int n) { return n * n; });
    std::cout << "Squared: ";
    for(const auto& n : squared) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // Pattern 4: Filtering (copying only matching elements)
    std::cout << "\n4. Filtering (only even numbers):\n";
    std::vector<int> evens;
    std::copy_if(data.begin(), data.end(), std::back_inserter(evens),
                 [](int n) { return n % 2 == 0; });
    std::cout << "Evens: ";
    for(const auto& n : evens) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // Pattern 5: Accumulating/reducing
    std::cout << "\n5. Sum of all elements:\n";
    int sum = 0;
    for(auto it = data.begin(); it != data.end(); ++it) {
        sum += *it;
    }
    std::cout << "Sum: " << sum << "\n";
    // Or use: std::accumulate(data.begin(), data.end(), 0);
}

void run_all() {
    std::cout << "\n********* ADVANCED ITERATOR CONCEPTS *********\n";
    iterator_categories_demo();
    custom_iterator_demo();
    iterator_adaptors_demo();
    common_patterns();
}

} // namespace advanced_concepts

// =============================================================================
// COMMON MISTAKES AND DEBUGGING
// =============================================================================

namespace debugging {

void common_mistakes() {
    std::cout << "\n=== Common Iterator Mistakes ===\n";

    // Mistake 1: Off-by-one Error
    std::cout << "\n1. Off-by-one Error (FIXED):\n";
    std::vector<int> vec{1, 2, 3, 4, 5};
    // WRONG: for(auto it = vec.begin(); it <= vec.end(); ++it)
    // CORRECT:
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    // WHY: end() points ONE PAST the last element
    //      Using <= would try to access invalid memory
    //      end() should NEVER be dereferenced!

    // Mistake 2: Iterator Invalidation
    std::cout << "\n2. Iterator Invalidation (FIXED):\n";
    std::vector<int> vec2{1, 2, 3, 4, 5};
    std::cout << "Original: ";
    for(const auto& n : vec2) std::cout << n << " ";
    std::cout << "\n";

    // WRONG:
    // for(auto it = vec2.begin(); it != vec2.end(); ++it) {
    //     vec2.push_back(*it * 2);  // Invalidates ALL iterators!
    // }

    // CORRECT: Make a copy first or use indices
    std::vector<int> to_add;
    for(auto it = vec2.begin(); it != vec2.end(); ++it) {
        to_add.push_back(*it * 2);
    }
    vec2.insert(vec2.end(), to_add.begin(), to_add.end());

    std::cout << "After safe append: ";
    for(const auto& n : vec2) std::cout << n << " ";
    std::cout << "\n";

    // Mistake 3: Mismatched Iterator Types
    std::cout << "\n3. Mismatched Iterator Types (EXPLAINED):\n";
    std::vector<int> vec_a{1, 2, 3};
    std::vector<double> vec_b{4.0, 5.0, 6.0};

    // WRONG:
    // auto it = vec_a.begin();
    // auto end = vec_b.end();
    // for(; it != end; ++it) { /* ... */ }
    // This compares iterators from DIFFERENT containers!
    // Will not compile (type error) or cause undefined behavior

    // CORRECT: Use iterators from the SAME container
    for(auto it = vec_a.begin(); it != vec_a.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "\nKEY LESSONS:\n";
    std::cout << "  - Always use != (not <=) with end()\n";
    std::cout << "  - Never dereference end()\n";
    std::cout << "  - Modifying containers can invalidate iterators\n";
    std::cout << "  - Don't mix iterators from different containers\n";
    std::cout << "  - Use the iterator returned by erase()\n";
}

void run_all() {
    std::cout << "\n********* DEBUGGING AND COMMON MISTAKES *********\n";
    common_mistakes();
}

} // namespace debugging

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {
    std::cout << "=============================================================\n";
    std::cout << "           CHAPTER 14: ITERATORS - COMPREHENSIVE HINTS       \n";
    std::cout << "=============================================================\n";

    // Run all problem sets
    problem_set_1::run_all();
    problem_set_2::run_all();
    problem_set_3::run_all();

    // Run advanced concepts
    advanced_concepts::run_all();

    // Run debugging examples
    debugging::run_all();

    std::cout << "\n=============================================================\n";
    std::cout << "KEY TAKEAWAYS:\n";
    std::cout << "=============================================================\n";
    std::cout << "1. ITERATOR BASICS:\n";
    std::cout << "   - begin() points to first element\n";
    std::cout << "   - end() points ONE PAST last element (never dereference!)\n";
    std::cout << "   - Use * to dereference, ++ to advance\n\n";

    std::cout << "2. RANGE-BASED FOR LOOPS:\n";
    std::cout << "   - auto        : Makes a copy\n";
    std::cout << "   - auto&       : Reference (can modify)\n";
    std::cout << "   - const auto& : Read-only reference (most efficient)\n\n";

    std::cout << "3. ITERATOR CATEGORIES:\n";
    std::cout << "   - Input/Output: Single-pass, read/write only\n";
    std::cout << "   - Forward: Multi-pass, forward only\n";
    std::cout << "   - Bidirectional: Forward + backward (--)\n";
    std::cout << "   - Random Access: All operations + arithmetic\n\n";

    std::cout << "4. COMMON PATTERNS:\n";
    std::cout << "   - Use range-based for when possible (cleanest)\n";
    std::cout << "   - Use traditional iterators when you need control\n";
    std::cout << "   - Use reverse iterators (rbegin/rend) for backward iteration\n";
    std::cout << "   - Use algorithms (find, copy, transform) for common operations\n\n";

    std::cout << "5. SAFETY:\n";
    std::cout << "   - Container modifications can invalidate iterators\n";
    std::cout << "   - Always use iterator returned by erase()\n";
    std::cout << "   - Never compare iterators from different containers\n";
    std::cout << "   - Never dereference end() iterator\n\n";

    std::cout << "6. PYTHON/JAVA CONNECTION:\n";
    std::cout << "   - Range-based for is like Python's 'for item in list'\n";
    std::cout << "   - Iterators are like Java's Iterator interface\n";
    std::cout << "   - But C++ iterators are more powerful and flexible\n";
    std::cout << "=============================================================\n";

    return 0;
}

/*
=============================================================================
COMPILATION INSTRUCTIONS:
=============================================================================

Compile with:
  g++ -std=c++17 -Wall -Wextra -g -o iterators_hints iterators_hints.cpp

Run with:
  ./iterators_hints

=============================================================================
ADDITIONAL NOTES FOR STUDENTS:
=============================================================================

1. This file demonstrates ALL concepts from Chapter 14 assignments
2. Each section corresponds to a problem set in the assignments
3. Code includes detailed comments explaining WHY, not just HOW
4. Compare this to your own solutions to understand different approaches
5. Try modifying the examples to experiment with different behaviors

STUDY TIPS:
- Run the program and observe the output
- Try commenting out different sections to understand each part
- Modify values and see how behavior changes
- Debug with VS Code to watch iterator values change
- Practice writing your own iterator-based functions

CONNECTIONS TO OTHER LANGUAGES:
- Python's iterators: next(), iter(), for loops
- Java's Iterator: hasNext(), next()
- C++ combines both patterns and adds more flexibility

This is a LEARNING RESOURCE - use it to understand concepts, then apply
them in your own code!
=============================================================================
*/
