#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

// Basic iterator operations
void iterator_basics_demo() {
    std::cout << "=== Iterator Basics Demo ===\n";

    std::vector<int> numbers{10, 20, 30, 40, 50};

    // Print first element using iterator
    auto first_it = numbers.begin();
    std::cout << "First: " << *first_it << std::endl;

    // Print last element using iterator
    auto last_it = numbers.end() - 1;  // end() points one past the last element
    std::cout << "Last: " << *last_it << std::endl;

    // Print all elements using traditional iterator loop
    std::cout << "All: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Compare different iteration approaches
void iteration_comparison_demo() {
    std::cout << "\n=== Iteration Comparison Demo ===\n";

    std::vector<std::string> languages{"Python", "Java", "C++", "JavaScript"};

    // Version 1: Traditional index-based approach (like Java)
    std::cout << "Index-based:\n";
    for (size_t i = 0; i < languages.size(); ++i) {
        std::cout << "  " << i << ": " << languages[i] << std::endl;
    }

    // Version 2: Iterator-based approach
    std::cout << "Iterator-based:\n";
    size_t index = 0;
    for (auto it = languages.begin(); it != languages.end(); ++it) {
        std::cout << "  " << index++ << ": " << *it << std::endl;
    }

    // Version 3: Range-based for loop (like Python)
    std::cout << "Range-based:\n";
    index = 0;
    for (const auto& language : languages) {
        std::cout << "  " << index++ << ": " << language << std::endl;
    }
}

// Iterator arithmetic examples
void iterator_arithmetic_demo() {
    std::cout << "\n=== Iterator Arithmetic Demo ===\n";

    std::vector<int> data{1, 3, 5, 7, 9, 11, 13, 15};

    // Print element at position 3
    auto it = data.begin() + 3;
    std::cout << "Element at position 3: " << *it << std::endl;

    // Print every other element starting from beginning
    std::cout << "Every other element: ";
    for (auto it = data.begin(); it < data.end(); it += 2) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Print last 3 elements
    std::cout << "Last 3 elements: ";
    for (auto it = data.end() - 3; it != data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Modernize traditional loops with range-based for
void modernized_loops_demo() {
    std::cout << "\n=== Modernized Loops Demo ===\n";

    std::vector<double> grades{85.5, 92.0, 78.5, 96.0, 88.5};

    // Modern style: Print grades
    std::cout << "Grades: ";
    for (const auto& grade : grades) {
        std::cout << grade << " ";
    }
    std::cout << "\n";

    // Modern style: Calculate average
    double total = 0.0;
    for (const auto& grade : grades) {
        total += grade;
    }
    std::cout << "Average: " << total / grades.size() << "\n";
}

// Modifying elements with range-based for loops
void modifying_elements_demo() {
    std::cout << "\n=== Modifying Elements Demo ===\n";

    // Task 1: Double all numbers
    std::vector<int> numbers{1, 2, 3, 4, 5};
    std::cout << "Original numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    for (auto& num : numbers) {  // Note: auto& to modify
        num *= 2;
    }

    std::cout << "Doubled numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Task 2: Capitalize first letter of each word
    std::vector<std::string> words{"hello", "world", "cpp", "iterators"};
    std::cout << "Original words: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";

    for (auto& word : words) {  // Note: auto& to modify
        if (!word.empty()) {
            word[0] = std::toupper(word[0]);
        }
    }

    std::cout << "Capitalized words: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";

    // Task 3: Count positive numbers
    std::vector<int> mixed{-5, 3, -1, 8, 0, -2, 7};
    int positive_count = 0;
    for (const auto& num : mixed) {  // Note: const auto& for read-only
        if (num > 0) {
            positive_count++;
        }
    }
    std::cout << "Positive numbers: " << positive_count << "\n";
}

// Reference semantics practice
void reference_semantics_demo() {
    std::cout << "\n=== Reference Semantics Demo ===\n";

    std::vector<std::string> names{"Alice", "Bob", "Charlie", "Diana"};

    // Scenario 1: Just reading/printing (most efficient)
    std::cout << "Names: ";
    for (const auto& name : names) {  // const auto& - efficient read-only access
        std::cout << name << " ";
    }
    std::cout << "\n";

    // Scenario 2: Modifying each element
    std::cout << "Adding exclamation marks:\n";
    for (auto& name : names) {  // auto& - allows modification
        name += "!";
        std::cout << name << "\n";
    }

    // Scenario 3: Reset names and efficient reading again
    names = {"Alice", "Bob", "Charlie", "Diana"};
    std::cout << "Efficient reading:\n";
    for (const auto& name : names) {  // const auto& - no unnecessary copying
        std::cout << "Hello, " << name << "\n";
    }
}

// Custom iterator utility functions
template<typename Container, typename T>
bool contains(const Container& container, const T& value) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (*it == value) {
            return true;
        }
    }
    return false;
}

template<typename Container, typename T>
size_t count_occurrences(const Container& container, const T& value) {
    size_t count = 0;
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (*it == value) {
            count++;
        }
    }
    return count;
}

template<typename Container>
void print_reverse(const Container& container) {
    // Use reverse iterators for containers that support them
    for (auto it = container.rbegin(); it != container.rend(); ++it) {
        std::cout << *it << " ";
    }
}

void custom_iterator_functions_demo() {
    std::cout << "\n=== Custom Iterator Functions Demo ===\n";

    std::vector<int> data{1, 3, 7, 3, 9, 3, 5};

    std::cout << "Contains 7: " << (contains(data, 7) ? "true" : "false") << "\n";
    std::cout << "Contains 4: " << (contains(data, 4) ? "true" : "false") << "\n";
    std::cout << "Count of 3: " << count_occurrences(data, 3) << "\n";
    std::cout << "Reverse: ";
    print_reverse(data);
    std::cout << "\n";
}

// Safe container modification - fixing iterator invalidation
void safe_modification_demo() {
    std::cout << "\n=== Safe Container Modification Demo ===\n";

    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Original numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Safe way to remove even numbers
    auto it = numbers.begin();
    while (it != numbers.end()) {
        if (*it % 2 == 0) {
            it = numbers.erase(it);  // erase returns iterator to next element
        } else {
            ++it;  // Only increment if we didn't erase
        }
    }

    std::cout << "Odd numbers remaining: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

// Multi-container iterator project - gradebook system
struct Student {
    std::string name;
    std::vector<double> grades;

    double calculate_average() const {
        if (grades.empty()) return 0.0;

        double sum = 0.0;
        for (auto it = grades.begin(); it != grades.end(); ++it) {
            sum += *it;
        }
        return sum / grades.size();
    }
};

void gradebook_demo() {
    std::cout << "\n=== Gradebook System Demo ===\n";

    std::vector<Student> class_roster{
        {"Alice", {85.0, 92.0, 78.0, 95.0}},
        {"Bob", {88.0, 76.0, 92.0, 85.0}},
        {"Charlie", {92.0, 88.0, 95.0, 90.0}}
    };

    // 1. Print each student's name and average grade
    std::cout << "Student Averages:\n";
    for (const auto& student : class_roster) {
        std::cout << "  " << student.name << ": " << student.calculate_average() << "\n";
    }

    // 2. Find the student with the highest average
    auto highest_it = class_roster.begin();
    for (auto it = class_roster.begin(); it != class_roster.end(); ++it) {
        if (it->calculate_average() > highest_it->calculate_average()) {
            highest_it = it;
        }
    }

    std::cout << "Highest average: " << highest_it->name
              << " (" << highest_it->calculate_average() << ")\n";

    // 3. Count students with average above 85.0
    int high_performers = 0;
    for (const auto& student : class_roster) {
        if (student.calculate_average() > 85.0) {
            high_performers++;
        }
    }

    std::cout << "Students with average above 85.0: " << high_performers << "\n";

    // Additional: Show all grades for each student using iterators
    std::cout << "\nDetailed grades:\n";
    for (const auto& student : class_roster) {
        std::cout << "  " << student.name << ": ";
        for (auto grade_it = student.grades.begin(); grade_it != student.grades.end(); ++grade_it) {
            std::cout << *grade_it;
            if (grade_it + 1 != student.grades.end()) {
                std::cout << ", ";
            }
        }
        std::cout << " (avg: " << student.calculate_average() << ")\n";
    }
}

// Advanced example: STL algorithm integration
void stl_algorithm_integration() {
    std::cout << "\n=== STL Algorithm Integration Demo ===\n";

    std::vector<int> data{5, 2, 8, 1, 9, 3, 7, 4, 6};

    std::cout << "Original data: ";
    for (const auto& num : data) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Sort using iterators
    std::sort(data.begin(), data.end());
    std::cout << "Sorted data: ";
    for (const auto& num : data) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Find using iterators
    auto target = 7;
    auto found_it = std::find(data.begin(), data.end(), target);
    if (found_it != data.end()) {
        auto position = std::distance(data.begin(), found_it);
        std::cout << "Found " << target << " at position " << position << "\n";
    }

    // Transform using iterators (square all values)
    std::transform(data.begin(), data.end(), data.begin(),
                   [](int x) { return x * x; });

    std::cout << "Squared data: ";
    for (const auto& num : data) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Accumulate using iterators
    auto sum = std::accumulate(data.begin(), data.end(), 0);
    std::cout << "Sum of squared values: " << sum << "\n";
}

int main() {
    iterator_basics_demo();
    iteration_comparison_demo();
    iterator_arithmetic_demo();
    modernized_loops_demo();
    modifying_elements_demo();
    reference_semantics_demo();
    custom_iterator_functions_demo();
    safe_modification_demo();
    gradebook_demo();
    stl_algorithm_integration();

    std::cout << "\n=== Common Iterator Mistakes Demo ===\n";

    // Example 1: Off-by-one error (commented out as it would cause issues)
    // for(auto it = vec.begin(); it <= vec.end(); ++it) {  // WRONG: should be !=
    //     std::cout << *it << " ";
    // }

    std::cout << "Mistake 1: Using <= instead of != with end() iterator\n";
    std::cout << "Correct: for(auto it = vec.begin(); it != vec.end(); ++it)\n";

    std::cout << "\nMistake 2: Iterator invalidation during modification\n";
    std::cout << "Wrong: erase in loop without updating iterator\n";
    std::cout << "Correct: it = container.erase(it) to get next valid iterator\n";

    std::cout << "\nMistake 3: Mismatched iterator types\n";
    std::cout << "Wrong: using iterators from different containers in same loop\n";
    std::cout << "Correct: ensure begin() and end() are from same container\n";

    return 0;
}