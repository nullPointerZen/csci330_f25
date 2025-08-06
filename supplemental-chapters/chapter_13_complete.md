# Chapter 13: STL Containers - Complete Guide

## 🎯 Learning Objectives (5 minutes)

By the end of this chapter, you will:
1. **Choose** appropriate STL containers for different programming scenarios
2. **Master** sequence containers (`vector`, `list`) and their performance characteristics
3. **Apply** associative containers (`map`, `set`) for key-value and unique element storage
4. **Utilize** unordered containers for hash-based fast operations
5. **Understand** performance trade-offs between different container types
6. **Connect** C++ containers to familiar Python/Java collections

**⏱️ Time Budget: ~4.75 hours total**
- Learning: 2.5 hours
- Problems: 2.25 hours

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](./DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 🗂️ Core Concepts: STL Containers (2.5 hours)

### 1. Container Fundamentals and Python/Java Connections

**What are STL Containers?**
STL containers are objects that store collections of other objects with automatic memory management and type safety.

| Python Collection | Java Collection | C++ STL Container | Primary Use Case |
|------------------|-----------------|-------------------|------------------|
| `list` | `ArrayList` | `std::vector` | Dynamic array, random access |
| `collections.deque` | `LinkedList` | `std::list` | Frequent insert/delete in middle |
| `dict` | `HashMap` | `std::unordered_map` | Key-value pairs, fast lookup |
| `dict` (ordered) | `TreeMap` | `std::map` | Key-value pairs, sorted keys |
| `set` | `HashSet` | `std::unordered_set` | Unique elements, fast operations |
| `set` (ordered) | `TreeSet` | `std::set` | Unique elements, sorted |

### 2. Sequence Containers

#### `std::vector` - The Dynamic Array

**`std::vector` is C++'s equivalent to Python's `list` or Java's `ArrayList`:**

```cpp
#include <vector>
#include <iostream>
#include <algorithm>

void demonstrate_vector() {
    // Creation (similar to Python list creation)
    std::vector<int> numbers;                    // Python: numbers = []
    std::vector<int> scores = {85, 92, 78, 96}; // Python: scores = [85, 92, 78, 96]
    std::vector<int> zeros(10, 0);              // Python: zeros = [0] * 10
    
    // Basic operations
    numbers.push_back(42);                      // Python: numbers.append(42)
    numbers.push_back(17);                      // Python: numbers.append(17)
    numbers.push_back(33);                      // Python: numbers.append(33)
    
    // Access elements
    int first = numbers[0];                     // Python: first = numbers[0]
    int safe_access = numbers.at(1);            // Bounds-checked access (throws if invalid)
    
    // Size and capacity
    std::cout << "Size: " << numbers.size() << std::endl;        // Python: len(numbers)
    std::cout << "Capacity: " << numbers.capacity() << std::endl; // Not available in Python
    
    // Iteration patterns
    std::cout << "Elements: ";
    for (const auto& num : numbers) {           // Python: for num in numbers:
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Finding elements
    auto it = std::find(numbers.begin(), numbers.end(), 17);
    if (it != numbers.end()) {
        std::cout << "Found 17 at position: " << (it - numbers.begin()) << std::endl;
    }
    
    // Insertion and deletion
    numbers.insert(numbers.begin() + 1, 25);   // Insert 25 at position 1
    numbers.erase(numbers.begin() + 2);        // Remove element at position 2
    
    // Sorting
    std::sort(numbers.begin(), numbers.end()); // Python: numbers.sort()
}
```

**Vector Performance Characteristics:**
- **Access**: O(1) - Direct indexing like arrays
- **Push back**: O(1) amortized - Efficient appending
- **Insert middle**: O(n) - Must shift elements
- **Search**: O(n) - Linear search unless sorted

#### `std::list` - The Doubly Linked List

**`std::list` is similar to Python's `collections.deque` or Java's `LinkedList`:**

```cpp
#include <list>
#include <iostream>

void demonstrate_list() {
    std::list<std::string> playlist;
    
    // Efficient operations at both ends
    playlist.push_back("Song 1");     // Add to end
    playlist.push_back("Song 2");     
    playlist.push_front("Intro");     // Add to beginning - efficient!
    
    std::cout << "Playlist: ";
    for (const auto& song : playlist) {
        std::cout << song << " -> ";
    }
    std::cout << "END" << std::endl;
    
    // Efficient insertion in middle (if you have iterator)
    auto it = playlist.begin();
    std::advance(it, 1);              // Move to position 1
    playlist.insert(it, "Interlude"); // O(1) insertion!
    
    // No random access - this won't compile:
    // std::cout << playlist[1];       // ERROR: no [] operator
    
    // Must use iterators for access
    auto second = playlist.begin();
    std::advance(second, 1);
    std::cout << "Second song: " << *second << std::endl;
}
```

**List Performance Characteristics:**
- **Access**: O(n) - Must traverse from beginning or end
- **Insert anywhere**: O(1) - If you have iterator to position
- **Push front/back**: O(1) - Efficient at both ends
- **Search**: O(n) - Must traverse sequentially

### 3. Associative Containers

#### `std::map` - Sorted Key-Value Storage

**`std::map` is like Python's `dict` but keeps keys sorted:**

```cpp
#include <map>
#include <iostream>
#include <string>

void demonstrate_map() {
    // Creation and initialization
    std::map<std::string, int> ages;                    // Python: ages = {}
    std::map<std::string, int> scores = {               // Initialize with data
        {"Alice", 95}, {"Bob", 87}, {"Charlie", 92}
    };
    
    // Adding elements
    ages["Alice"] = 25;                                 // Python: ages["Alice"] = 25
    ages["Bob"] = 30;                                   // Creates if doesn't exist
    ages.insert({"Charlie", 28});                      // Alternative insertion
    ages.insert(std::make_pair("Diana", 22));          // Another way
    
    // Safe access patterns
    // Method 1: Use find (doesn't create entry)
    auto it = ages.find("Alice");                       // Python: if "Alice" in ages:
    if (it != ages.end()) {
        std::cout << "Alice is " << it->second << " years old" << std::endl;
    }
    
    // Method 2: Use count (returns 0 or 1 for map)
    if (ages.count("Bob")) {                           // Python: if "Bob" in ages:
        std::cout << "Bob is " << ages["Bob"] << " years old" << std::endl;
    }
    
    // Iteration (always in sorted key order)
    std::cout << "All ages:" << std::endl;
    for (const auto& [name, age] : ages) {             // Python: for name, age in ages.items():
        std::cout << name << ": " << age << std::endl;
    }
    
    // Update existing value
    ages["Alice"] = 26;                                // Birthday!
    
    // Remove elements
    ages.erase("Bob");                                 // Python: del ages["Bob"]
    
    // Size operations
    std::cout << "Number of people: " << ages.size() << std::endl;
}
```

#### `std::set` - Sorted Unique Elements

**`std::set` is like Python's `set` but keeps elements sorted:**

```cpp
#include <set>
#include <iostream>
#include <algorithm>

void demonstrate_set() {
    // Creation
    std::set<int> unique_numbers;                      // Python: unique_numbers = set()
    std::set<int> primes = {2, 3, 5, 7, 11, 13};     // Initialize with values
    
    // Adding elements (duplicates ignored)
    unique_numbers.insert(5);                         // Python: unique_numbers.add(5)
    unique_numbers.insert(3);
    unique_numbers.insert(5);                         // Duplicate - ignored
    unique_numbers.insert(1);
    
    // Check membership
    bool has_five = unique_numbers.count(5) > 0;      // Python: 5 in unique_numbers
    // Alternative:
    bool has_three = unique_numbers.find(3) != unique_numbers.end();
    
    // Iteration (always sorted)
    std::cout << "Unique numbers: ";
    for (const auto& num : unique_numbers) {          // Python: for num in sorted(unique_numbers):
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Set operations using algorithms
    std::set<int> other_numbers = {3, 4, 5, 6};
    std::set<int> union_result;
    std::set<int> intersection_result;
    
    // Union: elements in either set
    std::set_union(unique_numbers.begin(), unique_numbers.end(),
                   other_numbers.begin(), other_numbers.end(),
                   std::inserter(union_result, union_result.begin()));
    
    // Intersection: elements in both sets
    std::set_intersection(unique_numbers.begin(), unique_numbers.end(),
                         other_numbers.begin(), other_numbers.end(),
                         std::inserter(intersection_result, intersection_result.begin()));
    
    std::cout << "Union size: " << union_result.size() << std::endl;
    std::cout << "Intersection size: " << intersection_result.size() << std::endl;
}
```

### 4. Unordered Containers (Hash Tables)

#### `std::unordered_map` and `std::unordered_set`

**These are like Python's default `dict` and `set` - fast but unordered:**

```cpp
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>

void demonstrate_unordered_containers() {
    // unordered_map: fast key-value storage
    std::unordered_map<std::string, int> word_count;   // Python: word_count = {}
    
    // Fast O(1) average operations
    word_count["hello"] = 3;                           // Python: word_count["hello"] = 3
    word_count["world"] = 2;
    word_count["cpp"] = 1;
    
    // Fast lookup
    if (word_count.find("hello") != word_count.end()) { // O(1) average
        std::cout << "Found 'hello' with count: " << word_count["hello"] << std::endl;
    }
    
    // unordered_set: fast unique element storage
    std::unordered_set<std::string> unique_words;     // Python: unique_words = set()
    unique_words.insert("hello");                     // Python: unique_words.add("hello")
    unique_words.insert("world");
    unique_words.insert("hello");                     // Duplicate ignored
    
    // Fast membership test
    if (unique_words.count("hello")) {                // O(1) average
        std::cout << "Contains 'hello'" << std::endl;
    }
    
    // Iteration (no guaranteed order)
    std::cout << "Unique words: ";
    for (const auto& word : unique_words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}
```

### 5. Performance Comparison and Container Selection

**Big O Performance Summary:**

| Operation | vector | list | map | set | unordered_map | unordered_set |
|-----------|--------|------|-----|-----|---------------|---------------|
| Access by index | O(1) | O(n) | N/A | N/A | N/A | N/A |
| Search | O(n) | O(n) | O(log n) | O(log n) | O(1) avg | O(1) avg |
| Insert at end | O(1)* | O(1) | O(log n) | O(log n) | O(1) avg | O(1) avg |
| Insert at beginning | O(n) | O(1) | O(log n) | O(log n) | O(1) avg | O(1) avg |
| Insert in middle | O(n) | O(1)** | O(log n) | O(log n) | O(1) avg | O(1) avg |
| Delete | O(n) | O(1)** | O(log n) | O(log n) | O(1) avg | O(1) avg |

*Amortized, **If you have iterator to position

**Container Selection Guide:**

```cpp
// Choose based on your primary operations:

// Need random access and mostly append? -> vector
std::vector<int> scores;  // Like Python list for most cases

// Need frequent insert/delete in middle? -> list  
std::list<Task> task_queue;  // Like Python deque for both ends

// Need key-value pairs with sorted keys? -> map
std::map<std::string, Player> leaderboard;  // Sorted by name

// Need fast key-value lookup, don't care about order? -> unordered_map
std::unordered_map<int, std::string> id_to_name;  // Like Python dict

// Need unique elements, sorted? -> set
std::set<std::string> sorted_categories;

// Need unique elements, fast operations? -> unordered_set
std::unordered_set<int> processed_ids;  // Like Python set
```

### 6. Advanced Container Usage

#### Custom Hash Functions for unordered_containers

```cpp
#include <unordered_set>
#include <functional>

struct Student {
    std::string name;
    int id;
    std::string major;
    
    bool operator==(const Student& other) const {
        return id == other.id;  // Students equal if same ID
    }
};

// Custom hash function
struct StudentHash {
    std::size_t operator()(const Student& s) const {
        return std::hash<int>{}(s.id);  // Hash based on ID
    }
};

void demonstrate_custom_hash() {
    std::unordered_set<Student, StudentHash> students;
    
    students.insert({"Alice", 12345, "CS"});
    students.insert({"Bob", 67890, "Math"});
    students.insert({"Alice", 12345, "Physics"});  // Duplicate ID - ignored
    
    std::cout << "Number of unique students: " << students.size() << std::endl;
}
```

#### Container of Containers

```cpp
#include <vector>
#include <map>
#include <string>

void demonstrate_nested_containers() {
    // 2D vector (like Python list of lists)
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    // Map of vectors (like Python dict with list values)
    std::map<std::string, std::vector<int>> student_grades;
    student_grades["Alice"] = {95, 87, 92};
    student_grades["Bob"] = {78, 85, 90};
    
    // Access nested elements
    int center = matrix[1][1];  // Gets 5
    int alice_first_grade = student_grades["Alice"][0];  // Gets 95
    
    std::cout << "Center of matrix: " << center << std::endl;
    std::cout << "Alice's first grade: " << alice_first_grade << std::endl;
}
```

---

## 💻 VS Code Debugging STL Containers (20 minutes)

### Container Visualization in VS Code

**Enhanced debugging configuration for containers:**

1. **Configure `launch.json` for container debugging:**
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug STL Containers",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

2. **Useful watch expressions:**
```cpp
// Add these to VS Code Watch panel
container.size()           // Check current size
container.capacity()       // For vector - allocated capacity
container.empty()          // Check if empty
*iterator_name            // Dereference iterator to see value
```

### Container Debugging Techniques

```cpp
// Debug helper functions
template<typename Container>
void debug_container(const Container& c, const std::string& name) {
    std::cout << name << " size: " << c.size() << std::endl;
    std::cout << name << " contents: ";
    for (const auto& item : c) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    // Set breakpoint here to inspect container state
}

// For maps specifically
template<typename K, typename V>
void debug_map(const std::map<K, V>& m, const std::string& name) {
    std::cout << name << " size: " << m.size() << std::endl;
    for (const auto& [key, value] : m) {
        std::cout << key << " -> " << value << std::endl;
    }
    // Set breakpoint here to inspect map state
}
```

---

## 🧩 Hands-On Problems (2.25 hours)

### Problem Set 1: Container Basics and Sequence Containers (45 minutes)

#### Problem 1.1: Grade Management System (15 minutes)

**Build a grade management system using `std::vector`:**

```cpp
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

class GradeManager {
private:
    std::vector<double> grades;

public:
    void add_grade(double grade) {
        grades.push_back(grade);
    }
    
    double calculate_average() const {
        if (grades.empty()) return 0.0;
        double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
        return sum / grades.size();
    }
    
    double find_highest() const {
        if (grades.empty()) return 0.0;
        return *std::max_element(grades.begin(), grades.end());
    }
    
    double find_lowest() const {
        if (grades.empty()) return 0.0;
        return *std::min_element(grades.begin(), grades.end());
    }
    
    void display_grades() const {
        std::cout << "Grades: ";
        for (size_t i = 0; i < grades.size(); ++i) {
            std::cout << grades[i];  // Using [] operator
            if (i < grades.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
        
        // Alternative using at() for bounds checking
        std::cout << "First grade (safe access): ";
        try {
            std::cout << grades.at(0) << std::endl;
        } catch (const std::out_of_range& e) {
            std::cout << "No grades available" << std::endl;
        }
    }
};

// Test the implementation
void test_grade_manager() {
    GradeManager manager;
    
    // Add grades
    manager.add_grade(85.5);
    manager.add_grade(92.0);
    manager.add_grade(78.5);
    manager.add_grade(88.0);
    manager.add_grade(95.5);
    
    // Display results
    manager.display_grades();
    std::cout << "Average: " << manager.calculate_average() << std::endl;
    std::cout << "Highest: " << manager.find_highest() << std::endl;
    std::cout << "Lowest: " << manager.find_lowest() << std::endl;
}
```

#### Problem 1.2: Student Roster Management (15 minutes)

**Manage a dynamic list of students with insertions and deletions:**

```cpp
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class StudentRoster {
private:
    std::vector<std::string> students;

public:
    void add_student(const std::string& name) {
        students.push_back(name);
    }
    
    void insert_student(const std::string& name, size_t position) {
        if (position <= students.size()) {
            students.insert(students.begin() + position, name);
        }
    }
    
    void remove_student(const std::string& name) {
        auto it = std::find(students.begin(), students.end(), name);
        if (it != students.end()) {
            students.erase(it);
            std::cout << "Removed " << name << std::endl;
        } else {
            std::cout << name << " not found" << std::endl;
        }
    }
    
    void display_students() const {
        std::cout << "Student Roster:" << std::endl;
        for (size_t i = 0; i < students.size(); ++i) {
            std::cout << i + 1 << ". " << students[i] << std::endl;
        }
    }
    
    size_t get_count() const {
        return students.size();
    }
};

// Test the implementation
void test_student_roster() {
    StudentRoster roster;
    
    // Add students
    roster.add_student("Alice");
    roster.add_student("Bob");
    roster.add_student("Charlie");
    
    roster.display_students();
    
    // Insert in middle
    roster.insert_student("Diana", 1);  // Insert at position 1
    roster.display_students();
    
    // Remove student
    roster.remove_student("Bob");
    roster.display_students();
    
    std::cout << "Total students: " << roster.get_count() << std::endl;
}
```

#### Problem 1.3: Performance Comparison (15 minutes)

**Compare vector vs list performance:**

```cpp
#include <vector>
#include <list>
#include <chrono>
#include <iostream>
#include <random>

class PerformanceTester {
public:
    template<typename Container>
    static double time_front_insertions(Container& container, int count) {
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < count; ++i) {
            if constexpr (std::is_same_v<Container, std::vector<int>>) {
                container.insert(container.begin(), i);
            } else {
                container.push_front(i);
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        return duration.count();
    }
    
    template<typename Container>
    static double time_back_insertions(Container& container, int count) {
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < count; ++i) {
            container.push_back(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        return duration.count();
    }
};

void test_performance_comparison() {
    const int test_size = 10000;
    
    std::vector<int> vec;
    std::list<int> lst;
    
    // Test back insertions
    std::vector<int> vec_back;
    std::list<int> lst_back;
    
    double vec_back_time = PerformanceTester::time_back_insertions(vec_back, test_size);
    double lst_back_time = PerformanceTester::time_back_insertions(lst_back, test_size);
    
    std::cout << "Back insertion performance (microseconds):" << std::endl;
    std::cout << "Vector: " << vec_back_time << std::endl;
    std::cout << "List: " << lst_back_time << std::endl;
    
    // Test front insertions
    std::vector<int> vec_front;
    std::list<int> lst_front;
    
    double vec_front_time = PerformanceTester::time_front_insertions(vec_front, 1000);  // Smaller test for vector
    double lst_front_time = PerformanceTester::time_front_insertions(lst_front, 1000);
    
    std::cout << "\nFront insertion performance (microseconds):" << std::endl;
    std::cout << "Vector: " << vec_front_time << std::endl;
    std::cout << "List: " << lst_front_time << std::endl;
    
    if (lst_front_time < vec_front_time) {
        std::cout << "List is " << (vec_front_time / lst_front_time) << "x faster for front insertion" << std::endl;
    }
}
```

### Problem Set 2: Associative Containers (50 minutes)

#### Problem 2.1: Word Frequency Counter (20 minutes)

**Build a word frequency analyzer using `std::map`:**

```cpp
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

class WordFrequencyCounter {
private:
    std::map<std::string, int> word_counts;

public:
    void add_text(const std::string& text) {
        std::stringstream ss(text);
        std::string word;
        
        while (ss >> word) {
            // Convert to lowercase for consistent counting
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            
            // Remove punctuation (simple version)
            word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
            
            if (!word.empty()) {
                word_counts[word]++;  // Increment count (creates if doesn't exist)
            }
        }
    }
    
    void display_all_words() const {
        std::cout << "Word frequencies (alphabetical order):" << std::endl;
        for (const auto& [word, count] : word_counts) {
            std::cout << word << ": " << count << std::endl;
        }
    }
    
    void find_most_frequent() const {
        if (word_counts.empty()) {
            std::cout << "No words to analyze" << std::endl;
            return;
        }
        
        auto max_pair = std::max_element(word_counts.begin(), word_counts.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            });
        
        std::cout << "Most frequent word: " << max_pair->first 
                  << " (" << max_pair->second << " times)" << std::endl;
    }
    
    int get_word_count(const std::string& word) const {
        auto it = word_counts.find(word);
        return (it != word_counts.end()) ? it->second : 0;
    }
};

// Test the implementation
void test_word_frequency_counter() {
    WordFrequencyCounter counter;
    
    std::cout << "Enter text (type 'DONE' on a new line to finish):" << std::endl;
    std::string line;
    while (std::getline(std::cin, line) && line != "DONE") {
        counter.add_text(line);
    }
    
    counter.display_all_words();
    counter.find_most_frequent();
    
    // Test specific word lookup
    std::cout << "\nEnter a word to check its frequency: ";
    std::string test_word;
    std::cin >> test_word;
    std::transform(test_word.begin(), test_word.end(), test_word.begin(), ::tolower);
    
    int count = counter.get_word_count(test_word);
    std::cout << "'" << test_word << "' appears " << count << " times" << std::endl;
}
```

#### Problem 2.2: Set Operations (15 minutes)

**Implement mathematical set operations:**

```cpp
#include <set>
#include <algorithm>
#include <iterator>
#include <iostream>

class SetOperations {
public:
    static std::set<int> set_union(const std::set<int>& set1, const std::set<int>& set2) {
        std::set<int> result;
        std::set_union(set1.begin(), set1.end(),
                      set2.begin(), set2.end(),
                      std::inserter(result, result.begin()));
        return result;
    }
    
    static std::set<int> set_intersection(const std::set<int>& set1, const std::set<int>& set2) {
        std::set<int> result;
        std::set_intersection(set1.begin(), set1.end(),
                             set2.begin(), set2.end(),
                             std::inserter(result, result.begin()));
        return result;
    }
    
    static std::set<int> set_difference(const std::set<int>& set1, const std::set<int>& set2) {
        std::set<int> result;
        std::set_difference(set1.begin(), set1.end(),
                           set2.begin(), set2.end(),
                           std::inserter(result, result.begin()));
        return result;
    }
    
    static void display_set(const std::set<int>& s, const std::string& name) {
        std::cout << name << ": {";
        bool first = true;
        for (int element : s) {
            if (!first) std::cout << ", ";
            std::cout << element;
            first = false;
        }
        std::cout << "}" << std::endl;
    }
};

// Test the implementation
void test_set_operations() {
    std::set<int> set1 = {1, 2, 3, 4, 5};
    std::set<int> set2 = {4, 5, 6, 7, 8};
    
    SetOperations::display_set(set1, "Set 1");
    SetOperations::display_set(set2, "Set 2");
    
    auto union_result = SetOperations::set_union(set1, set2);
    auto intersection_result = SetOperations::set_intersection(set1, set2);
    auto difference_result = SetOperations::set_difference(set1, set2);
    
    SetOperations::display_set(union_result, "Union");
    SetOperations::display_set(intersection_result, "Intersection");
    SetOperations::display_set(difference_result, "Set1 - Set2");
    
    // Test membership
    std::cout << "\nMembership tests:" << std::endl;
    std::cout << "Is 3 in Set1? " << (set1.count(3) ? "Yes" : "No") << std::endl;
    std::cout << "Is 6 in Set1? " << (set1.count(6) ? "Yes" : "No") << std::endl;
}
```

#### Problem 2.3: Student Database (15 minutes)

**Coordinate multiple associative containers:**

```cpp
#include <map>
#include <set>
#include <string>
#include <iostream>

class StudentDatabase {
private:
    std::map<int, std::string> id_to_name;        // ID -> Name
    std::map<std::string, double> name_to_gpa;    // Name -> GPA
    std::set<std::string> honor_roll;             // Honor roll students (GPA >= 3.5)

public:
    void add_student(int id, const std::string& name, double gpa) {
        id_to_name[id] = name;
        name_to_gpa[name] = gpa;
        
        if (gpa >= 3.5) {
            honor_roll.insert(name);
        } else {
            honor_roll.erase(name);  // Remove if GPA dropped
        }
    }
    
    double find_gpa_by_id(int id) const {
        auto it = id_to_name.find(id);
        if (it != id_to_name.end()) {
            const std::string& name = it->second;
            auto gpa_it = name_to_gpa.find(name);
            if (gpa_it != name_to_gpa.end()) {
                return gpa_it->second;
            }
        }
        return -1.0;  // Not found
    }
    
    void list_honor_roll_students() const {
        std::cout << "Honor Roll Students (GPA >= 3.5):" << std::endl;
        if (honor_roll.empty()) {
            std::cout << "No students on honor roll" << std::endl;
            return;
        }
        
        for (const auto& name : honor_roll) {
            auto gpa_it = name_to_gpa.find(name);
            if (gpa_it != name_to_gpa.end()) {
                std::cout << name << " (GPA: " << gpa_it->second << ")" << std::endl;
            }
        }
    }
    
    void display_all_students() const {
        std::cout << "All Students:" << std::endl;
        for (const auto& [id, name] : id_to_name) {
            auto gpa_it = name_to_gpa.find(name);
            double gpa = (gpa_it != name_to_gpa.end()) ? gpa_it->second : 0.0;
            std::cout << "ID: " << id << ", Name: " << name << ", GPA: " << gpa << std::endl;
        }
    }
};

// Test the implementation
void test_student_database() {
    StudentDatabase db;
    
    // Add students
    db.add_student(12345, "Alice Johnson", 3.8);
    db.add_student(67890, "Bob Smith", 3.2);
    db.add_student(11111, "Charlie Brown", 3.9);
    db.add_student(22222, "Diana Prince", 3.4);
    
    db.display_all_students();
    std::cout << std::endl;
    
    db.list_honor_roll_students();
    std::cout << std::endl;
    
    // Test GPA lookup by ID
    int test_id = 12345;
    double gpa = db.find_gpa_by_id(test_id);
    if (gpa >= 0) {
        std::cout << "Student " << test_id << " has GPA: " << gpa << std::endl;
    } else {
        std::cout << "Student " << test_id << " not found" << std::endl;
    }
}
```

### Problem Set 3: Unordered Containers and Integration (50 minutes)

#### Problem 3.1: Performance Comparison (15 minutes)

**Compare map vs unordered_map performance:**

```cpp
#include <map>
#include <unordered_map>
#include <chrono>
#include <random>
#include <iostream>

class ContainerPerformanceTest {
public:
    template<typename MapType>
    static double time_insertions(MapType& container, const std::vector<int>& data) {
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int value : data) {
            container[value] = value * 2;  // Store value -> value*2
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        return duration.count();
    }
    
    template<typename MapType>
    static double time_lookups(const MapType& container, const std::vector<int>& search_keys) {
        auto start = std::chrono::high_resolution_clock::now();
        
        volatile int found_count = 0;  // volatile to prevent optimization
        for (int key : search_keys) {
            if (container.find(key) != container.end()) {
                found_count++;
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        return duration.count();
    }
};

void test_container_performance() {
    const int data_size = 100000;
    const int search_size = 10000;
    
    // Generate test data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    
    std::vector<int> test_data;
    test_data.reserve(data_size);
    for (int i = 0; i < data_size; ++i) {
        test_data.push_back(dis(gen));
    }
    
    std::vector<int> search_keys;
    search_keys.reserve(search_size);
    for (int i = 0; i < search_size; ++i) {
        search_keys.push_back(test_data[dis(gen) % data_size]);
    }
    
    // Test std::map
    std::map<int, int> ordered_map;
    double map_insert_time = ContainerPerformanceTest::time_insertions(ordered_map, test_data);
    double map_lookup_time = ContainerPerformanceTest::time_lookups(ordered_map, search_keys);
    
    // Test std::unordered_map
    std::unordered_map<int, int> unordered_map;
    double unordered_insert_time = ContainerPerformanceTest::time_insertions(unordered_map, test_data);
    double unordered_lookup_time = ContainerPerformanceTest::time_lookups(unordered_map, search_keys);
    
    // Report results
    std::cout << "Performance Comparison (microseconds):" << std::endl;
    std::cout << "Data size: " << data_size << ", Search operations: " << search_size << std::endl;
    std::cout << std::endl;
    
    std::cout << "Insertion time:" << std::endl;
    std::cout << "  std::map: " << map_insert_time << std::endl;
    std::cout << "  std::unordered_map: " << unordered_insert_time << std::endl;
    std::cout << "  Speedup: " << (map_insert_time / unordered_insert_time) << "x" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Lookup time:" << std::endl;
    std::cout << "  std::map: " << map_lookup_time << std::endl;
    std::cout << "  std::unordered_map: " << unordered_lookup_time << std::endl;
    std::cout << "  Speedup: " << (map_lookup_time / unordered_lookup_time) << "x" << std::endl;
}
```

#### Problem 3.2: Custom Hash Function (20 minutes)

**Create hash functions for custom objects:**

```cpp
#include <unordered_set>
#include <functional>
#include <string>
#include <iostream>

struct Student {
    std::string name;
    int id;
    std::string major;
    
    // Equality operator required for unordered containers
    bool operator==(const Student& other) const {
        return id == other.id;  // Students are equal if they have same ID
    }
};

// Custom hash function
struct StudentHash {
    std::size_t operator()(const Student& s) const {
        // Combine hash of ID and name for better distribution
        std::size_t h1 = std::hash<int>{}(s.id);
        std::size_t h2 = std::hash<std::string>{}(s.name);
        return h1 ^ (h2 << 1);  // Simple hash combination
    }
};

class StudentRegistry {
private:
    std::unordered_set<Student, StudentHash> students;

public:
    void register_student(const Student& student) {
        auto [it, inserted] = students.insert(student);
        if (inserted) {
            std::cout << "Registered: " << student.name 
                      << " (ID: " << student.id << ", Major: " << student.major << ")" << std::endl;
        } else {
            std::cout << "Student with ID " << student.id << " already exists" << std::endl;
        }
    }
    
    bool is_registered(int student_id) const {
        // Create a temporary student with just the ID for lookup
        Student temp{"", student_id, ""};
        return students.find(temp) != students.end();
    }
    
    void display_all_students() const {
        std::cout << "Registered Students:" << std::endl;
        for (const auto& student : students) {
            std::cout << "  " << student.name << " (ID: " << student.id 
                      << ", Major: " << student.major << ")" << std::endl;
        }
    }
    
    size_t get_student_count() const {
        return students.size();
    }
};

// Test the implementation
void test_custom_hash() {
    StudentRegistry registry;
    
    // Register students
    registry.register_student({"Alice Johnson", 12345, "Computer Science"});
    registry.register_student({"Bob Smith", 67890, "Mathematics"});
    registry.register_student({"Charlie Brown", 11111, "Physics"});
    
    // Try to register duplicate (same ID, different details)
    registry.register_student({"Alice Williams", 12345, "Engineering"});
    
    registry.display_all_students();
    
    // Test lookup
    std::cout << "\nLookup tests:" << std::endl;
    std::cout << "Is student 12345 registered? " << (registry.is_registered(12345) ? "Yes" : "No") << std::endl;
    std::cout << "Is student 99999 registered? " << (registry.is_registered(99999) ? "Yes" : "No") << std::endl;
    
    std::cout << "Total registered students: " << registry.get_student_count() << std::endl;
}
```

#### Problem 3.3: Library Management System (15 minutes)

**Integrate multiple container types in a realistic system:**

```cpp
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>

struct Book {
    std::string title;
    std::string author;
    std::string category;
    bool is_available = true;
};

class LibrarySystem {
private:
    std::map<std::string, Book> books;                      // ISBN -> Book
    std::unordered_set<std::string> authors;               // Unique authors
    std::set<std::string> categories;                      // Sorted categories
    std::unordered_map<std::string, std::string> checked_out; // ISBN -> Borrower

public:
    void add_book(const std::string& isbn, const std::string& title, 
                  const std::string& author, const std::string& category) {
        books[isbn] = {title, author, category, true};
        authors.insert(author);
        categories.insert(category);
        std::cout << "Added book: " << title << " by " << author << std::endl;
    }
    
    bool check_out_book(const std::string& isbn, const std::string& borrower) {
        auto it = books.find(isbn);
        if (it != books.end() && it->second.is_available) {
            it->second.is_available = false;
            checked_out[isbn] = borrower;
            std::cout << borrower << " checked out: " << it->second.title << std::endl;
            return true;
        }
        std::cout << "Book not available for checkout" << std::endl;
        return false;
    }
    
    bool return_book(const std::string& isbn) {
        auto it = books.find(isbn);
        auto checkout_it = checked_out.find(isbn);
        
        if (it != books.end() && checkout_it != checked_out.end()) {
            it->second.is_available = true;
            std::cout << checkout_it->second << " returned: " << it->second.title << std::endl;
            checked_out.erase(checkout_it);
            return true;
        }
        std::cout << "Book was not checked out" << std::endl;
        return false;
    }
    
    std::vector<Book> find_books_by_author(const std::string& author) const {
        std::vector<Book> result;
        for (const auto& [isbn, book] : books) {
            if (book.author == author) {
                result.push_back(book);
            }
        }
        return result;
    }
    
    void list_categories() const {
        std::cout << "Available categories (alphabetical):" << std::endl;
        for (const auto& category : categories) {
            std::cout << "  " << category << std::endl;
        }
    }
    
    void show_checked_out_books() const {
        std::cout << "Currently checked out books:" << std::endl;
        if (checked_out.empty()) {
            std::cout << "  No books currently checked out" << std::endl;
            return;
        }
        
        for (const auto& [isbn, borrower] : checked_out) {
            auto it = books.find(isbn);
            if (it != books.end()) {
                std::cout << "  " << it->second.title << " by " << it->second.author 
                          << " (borrowed by " << borrower << ")" << std::endl;
            }
        }
    }
    
    void show_library_stats() const {
        std::cout << "\nLibrary Statistics:" << std::endl;
        std::cout << "Total books: " << books.size() << std::endl;
        std::cout << "Unique authors: " << authors.size() << std::endl;
        std::cout << "Categories: " << categories.size() << std::endl;
        std::cout << "Books checked out: " << checked_out.size() << std::endl;
    }
};

// Test the complete system
void test_library_system() {
    LibrarySystem library;
    
    // Add books
    library.add_book("978-0123456789", "The C++ Programming Language", "Bjarne Stroustrup", "Programming");
    library.add_book("978-0987654321", "Effective C++", "Scott Meyers", "Programming");
    library.add_book("978-1111111111", "1984", "George Orwell", "Fiction");
    library.add_book("978-2222222222", "Animal Farm", "George Orwell", "Fiction");
    library.add_book("978-3333333333", "Clean Code", "Robert Martin", "Programming");
    
    library.show_library_stats();
    library.list_categories();
    
    // Check out some books
    std::cout << "\n--- Checking out books ---" << std::endl;
    library.check_out_book("978-0123456789", "Alice");
    library.check_out_book("978-1111111111", "Bob");
    library.check_out_book("978-0123456789", "Charlie");  // Should fail - already checked out
    
    library.show_checked_out_books();
    
    // Find books by author
    std::cout << "\n--- Books by George Orwell ---" << std::endl;
    auto orwell_books = library.find_books_by_author("George Orwell");
    for (const auto& book : orwell_books) {
        std::cout << "  " << book.title << " (Available: " << (book.is_available ? "Yes" : "No") << ")" << std::endl;
    }
    
    // Return a book
    std::cout << "\n--- Returning books ---" << std::endl;
    library.return_book("978-0123456789");
    library.show_checked_out_books();
    
    library.show_library_stats();
}

int main() {
    test_library_system();
    return 0;
}
```

---

## 🔧 Quick Reference & Troubleshooting

### Container Selection Decision Tree

```
What do you need?

Dynamic array with random access?
├─ Mostly append operations? → std::vector
└─ Frequent middle insertions? → std::list

Key-value storage?
├─ Need sorted keys? → std::map
└─ Just fast lookup? → std::unordered_map

Unique element storage?
├─ Need sorted elements? → std::set
└─ Just fast operations? → std::unordered_set
```

### Common Error Solutions

#### 1. Iterator Invalidation
```cpp
// ❌ Wrong - iterator becomes invalid
for (auto it = vec.begin(); it != vec.end(); ++it) {
    if (condition) {
        vec.erase(it);  // Undefined behavior!
    }
}

// ✅ Correct - get new iterator from erase
for (auto it = vec.begin(); it != vec.end();) {
    if (condition) {
        it = vec.erase(it);  // erase returns next valid iterator
    } else {
        ++it;
    }
}
```

#### 2. Map Key Creation
```cpp
// ❌ Wrong - creates entry if key doesn't exist
if (my_map[key] > 0) {  // Creates default value if key missing!
    // Process...
}

// ✅ Correct - use find or count
if (my_map.find(key) != my_map.end()) {  // Doesn't create entry
    // Process...
}
```

#### 3. Vector Bounds Checking
```cpp
// ❌ Risky - no bounds checking
int value = vec[index];  // Can access invalid memory

// ✅ Safe - throws exception if out of bounds
int value = vec.at(index);  // Throws std::out_of_range if invalid
```

---

## ✅ Chapter 13 Success Checklist

### Container Fundamentals
- [ ] Can explain the relationship between C++ containers and Python/Java collections
- [ ] Understand RAII and automatic memory management in containers
- [ ] Know when to use different container types based on performance needs
- [ ] Can iterate through containers using range-based for loops

### Sequence Containers
- [ ] Can use `std::vector` for dynamic arrays with random access
- [ ] Understand when `std::list` is better than `std::vector`
- [ ] Can measure and compare container performance
- [ ] Know the Big O complexity of common operations

### Associative Containers
- [ ] Can use `std::map` for sorted key-value storage
- [ ] Can use `std::set` for unique sorted elements
- [ ] Can implement set operations (union, intersection, difference)
- [ ] Understand the performance implications of tree-based containers

### Unordered Containers
- [ ] Can use `std::unordered_map` and `std::unordered_set` effectively
- [ ] Can create custom hash functions for user-defined types
- [ ] Understand when to prefer unordered containers over ordered ones
- [ ] Can handle hash collision and performance considerations

---

## 🚀 What's Next?

**Chapter 14: STL Algorithms** will cover:
- STL algorithms (sort, find, transform, etc.)
- Iterator concepts and categories
- Function objects and lambda integration
- Algorithm performance and best practices

**You've mastered STL containers!** 🎉 You now understand how to choose and use the right container for any data storage need. These containers provide the foundation for efficient C++ programs while maintaining the automatic memory management you're familiar with from Python and Java.

**Key Takeaway**: STL containers give you the best of both worlds - the performance and control of C++ with the convenience and safety of high-level language collections. Each container is optimized for specific use patterns, so choosing the right one can dramatically improve your program's performance.

---

*Remember: Containers are just tools - the key is understanding your data access patterns. Need random access? Use vector. Need fast lookups? Use unordered_map. Need sorted iteration? Use map or set. The STL provides the right tool for every job, and now you know how to choose wisely!*