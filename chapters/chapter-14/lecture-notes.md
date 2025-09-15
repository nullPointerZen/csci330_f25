# Chapter 14: Iterators - Complete Guide

## 🎯 Learning Objectives (5 minutes)

By the end of this chapter, you will:
1. **Understand** what iterators are and why they exist in C++
2. **Master** range-based for loops as the primary iteration method
3. **Apply** traditional iterator operations when fine control is needed
4. **Navigate** containers using iterator arithmetic and categories
5. **Handle** iterator invalidation and common iterator errors safely
6. **Connect** C++ iterators to familiar Python/Java iteration patterns

**⏱️ Time Budget: ~4.75 hours total**
- Learning: 2.5 hours  
- Problems: 2.25 hours

**🛠️ Development Environment**: This chapter assumes you've completed the setup in [DEVELOPMENT_SETUP.md](./DEVELOPMENT_SETUP.md). All debugging examples use the standard VS Code + Docker workflow established there.

---

## 🔄 Core Concepts: Iterator Fundamentals (2.5 hours)

### 1. What are Iterators? Think of Them as Smart Bookmarks

**Real-world analogy**: Iterators are like bookmarks in a book - they mark your position and let you move page by page, but they understand the structure of what they're traversing.

| Language | Iteration Approach | Example | Key Feature |
|----------|-------------------|---------|-------------|
| **C++** | Iterator objects | `for(auto it = vec.begin(); it != vec.end(); ++it)` | Direct memory access patterns |
| **Python** | Built-in iteration | `for item in my_list:` | Automatic iterator creation |
| **Java** | Iterator interface | `Iterator<String> it = list.iterator();` | Object-oriented approach |

**Why C++ uses iterators (vs Python's simpler approach):**

**The problem**: Different containers store data differently:
- `vector`: Elements in a continuous array
- `list`: Elements scattered in memory, connected by pointers  
- `map`: Elements in a tree structure

**The solution**: Iterators provide a common "bookmark" interface:
```cpp
// This code works with ANY container type!
template<typename Container>
void print_all(const Container& container) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
}

// Works with vectors, lists, maps, sets, etc.!
std::vector<int> vec = {1, 2, 3};
std::list<int> lst = {4, 5, 6};
print_all(vec);  // Optimized for vector's memory layout
print_all(lst);  // Optimized for list's pointer structure
```

### 2. Range-Based For Loops - The Modern Approach

**Range-based for loops (C++11) are the preferred way to iterate, similar to Python's natural syntax:**

```cpp
#include <vector>
#include <iostream>
#include <string>

void demonstrate_playlist_management() {
    std::cout << "=== Music Playlist Management ===\n";
    
    struct Song {
        std::string title;
        std::string artist;
        int duration_seconds;
    };
    
    std::vector<Song> playlist = {
        {"Bohemian Rhapsody", "Queen", 355},
        {"Hotel California", "Eagles", 391},
        {"Stairway to Heaven", "Led Zeppelin", 482},
        {"Sweet Child O' Mine", "Guns N' Roses", 356}
    };
    
    // Read-only iteration - display playlist (like Python: for song in playlist)
    std::cout << "Current Playlist:\n";
    int track_number = 1;
    for (const auto& song : playlist) {  // const auto& = read-only reference
        std::cout << track_number++ << ". " << song.title 
                  << " by " << song.artist 
                  << " (" << song.duration_seconds << "s)\n";
    }
    
    // Modifying elements - apply volume fade effect
    std::cout << "\nApplying fade effect to all songs...\n";
    for (auto& song : playlist) {  // auto& = reference for modification
        song.duration_seconds -= 5;  // Reduce each song by 5 seconds for fade
    }
    
    // Calculate total playlist time (copying is fine for simple calculations)
    int total_duration = 0;
    for (auto song : playlist) {  // auto = copy (duration_seconds is just an int)
        total_duration += song.duration_seconds;
    }
    
    int minutes = total_duration / 60;
    int seconds = total_duration % 60;
    std::cout << "Total playlist time: " << minutes << ":" 
              << (seconds < 10 ? "0" : "") << seconds << "\n";
}
```

**Range-based for loop syntax patterns:**

| C++ Syntax | When to Use | Python Equivalent | Memory Impact |
|-----------|-------------|-------------------|---------------|
| `for(const auto& item : container)` | Reading data (most common) | `for item in container:` | No copying - fastest |
| `for(auto& item : container)` | Modifying elements | No direct equivalent | No copying - fast |
| `for(auto item : container)` | Need independent copy | `for item in container:` | Copies each element - slower |

### 3. Traditional Iterator Operations

**When you need fine control, traditional iterators provide pointer-like behavior:**

```cpp
#include <vector>
#include <iostream>
#include <algorithm>

void demonstrate_precise_playlist_control() {
    std::cout << "\n=== Precise Playlist Navigation ===\n";
    
    std::vector<std::string> songs = {
        "Track 1: Intro", "Track 2: Verse", "Track 3: Chorus", 
        "Track 4: Bridge", "Track 5: Outro"
    };
    
    // Traditional iterator - like having precise control over your position
    auto current_track = songs.begin();    // Start at first track
    auto playlist_end = songs.end();       // "One past last" - like end of playlist
    
    std::cout << "Now playing: " << *current_track << "\n";  // Dereference to get value
    
    // Skip to next track
    ++current_track;
    std::cout << "Skipped to: " << *current_track << "\n";
    
    // Jump forward 2 tracks (only works with random access iterators like vector)
    current_track += 2;
    std::cout << "Jumped to: " << *current_track << "\n";
    
    // Go back one track
    --current_track;
    std::cout << "Went back to: " << *current_track << "\n";
    
    // Traditional iterator loop
    std::cout << "All elements: ";
    for (auto it = data.begin(); it != data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Finding elements using iterators
    auto found = std::find(data.begin(), data.end(), 30);
    if (found != data.end()) {
        std::cout << "Found 30 at position: " << (found - data.begin()) << std::endl;
    }
}
```

**Essential iterator operations:**
- `*it` - Dereference: get current element (like Python's `next()`)
- `++it` - Increment: move to next element
- `it1 == it2` - Comparison: check if iterators point to same location
- `container.begin()` - Iterator to first element
- `container.end()` - Iterator to "one past last" element

### 4. Iterator Categories and Container Support

**Different containers support different iterator capabilities:**

| Container | Iterator Category | Supported Operations | Python/Java Equivalent |
|-----------|------------------|---------------------|------------------------|
| **std::vector** | Random Access | `it + n`, `it - n`, `it[n]` | `list[i]` indexing |
| **std::list** | Bidirectional | `++it`, `--it` | No direct equivalent |
| **std::set** | Bidirectional | `++it`, `--it` (sorted order) | `sorted(set)` iteration |
| **std::unordered_set** | Forward | `++it` only | `set` iteration |

```cpp
#include <vector>
#include <list>
#include <set>
#include <iostream>

void demonstrate_iterator_categories() {
    // Random Access Iterator (vector)
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto vec_it = vec.begin();
    
    vec_it += 3;                    // Jump to position 3
    std::cout << "Element at position 3: " << *vec_it << std::endl;
    vec_it -= 2;                    // Jump back 2 positions
    std::cout << "Element at position 1: " << *vec_it << std::endl;
    
    // Bidirectional Iterator (list)
    std::list<int> lst = {10, 20, 30, 40, 50};
    auto lst_it = lst.begin();
    
    ++lst_it; ++lst_it;             // Move forward 2 steps
    std::cout << "List element: " << *lst_it << std::endl;
    --lst_it;                       // Move backward 1 step
    std::cout << "Previous element: " << *lst_it << std::endl;
    
    // Note: lst_it += 3; would NOT compile - list doesn't support random access
    
    // Forward Iterator (unordered_set)
    std::set<int> sorted_set = {30, 10, 40, 20, 50};  // Will be sorted
    std::cout << "Set elements (sorted): ";
    for (auto it = sorted_set.begin(); it != sorted_set.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

### 5. Iterator Arithmetic and Navigation

**Working with iterator positions and distances:**

```cpp
#include <vector>
#include <iostream>
#include <algorithm>

void demonstrate_iterator_arithmetic() {
    std::vector<int> data = {5, 10, 15, 20, 25, 30, 35, 40};
    
    // Finding the middle element
    auto middle = data.begin() + data.size() / 2;
    std::cout << "Middle element: " << *middle << std::endl;
    
    // Distance between iterators
    auto start = data.begin();
    auto end = data.end();
    std::cout << "Container size: " << (end - start) << std::endl;
    
    // Finding position of an element
    auto found = std::find(data.begin(), data.end(), 20);
    if (found != data.end()) {
        size_t position = found - data.begin();
        std::cout << "Found 20 at position: " << position << std::endl;
    }
    
    // Working with ranges
    auto first_half_end = data.begin() + data.size() / 2;
    std::cout << "First half: ";
    for (auto it = data.begin(); it != first_half_end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Reverse iteration (if supported)
    std::cout << "Reverse order: ";
    for (auto it = data.rbegin(); it != data.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

### 6. Iterator Invalidation and Safety

**Critical concept: iterators can become invalid when containers are modified:**

```cpp
#include <vector>
#include <iostream>

void demonstrate_iterator_safety() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // DANGEROUS: Iterator invalidation
    /*
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it % 2 == 0) {
            numbers.erase(it);  // DANGER: invalidates iterator!
        }
    }
    */
    
    // SAFE: Proper erase pattern
    std::cout << "Removing even numbers safely:" << std::endl;
    for (auto it = numbers.begin(); it != numbers.end(); ) {
        if (*it % 2 == 0) {
            std::cout << "Erasing: " << *it << std::endl;
            it = numbers.erase(it);  // erase returns next valid iterator
        } else {
            ++it;  // Only increment if we didn't erase
        }
    }
    
    std::cout << "Remaining numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
```

**Iterator invalidation rules:**
- **vector**: Invalidated by any operation that changes size or capacity
- **list**: Only invalidated when the specific element is removed
- **map/set**: Only invalidated when the specific element is removed
- **Always**: Get fresh iterators after container modification

### 7. Practical Iterator Patterns

**Common patterns you'll use in real code:**

```cpp
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

// Pattern 1: Safe element removal
template<typename Container, typename Predicate>
void remove_if_safe(Container& container, Predicate pred) {
    for (auto it = container.begin(); it != container.end(); ) {
        if (pred(*it)) {
            it = container.erase(it);
        } else {
            ++it;
        }
    }
}

// Pattern 2: Finding and processing elements  
template<typename Container, typename T>
bool find_and_process(Container& container, const T& target) {
    auto found = std::find(container.begin(), container.end(), target);
    if (found != container.end()) {
        // Process the found element
        *found = target * 2;  // Example: double the value
        return true;
    }
    return false;
}

// Pattern 3: Processing elements in ranges
template<typename Container>
void process_range(Container& container, size_t start, size_t count) {
    auto begin_it = container.begin() + start;
    auto end_it = begin_it + count;
    
    for (auto it = begin_it; it != end_it; ++it) {
        *it *= 10;  // Example processing
    }
}

void demonstrate_patterns() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Remove even numbers
    remove_if_safe(data, [](int n) { return n % 2 == 0; });
    
    std::cout << "After removing evens: ";
    for (const auto& num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Find and double the value 5
    if (find_and_process(data, 5)) {
        std::cout << "Found and processed 5" << std::endl;
    }
    
    // Process first 3 elements
    if (data.size() >= 3) {
        process_range(data, 0, 3);
    }
    
    std::cout << "Final data: ";
    for (const auto& num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
```

---

## 💻 VS Code Debugging Iterators (20 minutes)

### Iterator Debugging Configuration

**Enhanced debugging setup for iterator visualization:**

1. **Configure `launch.json` for iterator debugging:**
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug Iterators",
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

2. **Useful watch expressions for iterators:**
```cpp
// Add these to VS Code Watch panel
*iterator_name              // See current element value
iterator_name._M_current    // Internal iterator position (GDB)
container.size()            // Container size
distance(begin_it, end_it)  // Distance between iterators
```

### Iterator Debugging Techniques

```cpp
// Debug helper functions
template<typename Iterator>
void debug_iterator_position(Iterator it, Iterator begin, Iterator end, const std::string& name) {
    if (it == end) {
        std::cout << name << " is at end()" << std::endl;
    } else {
        std::cout << name << " points to: " << *it 
                  << " (position: " << std::distance(begin, it) << ")" << std::endl;
    }
    // Set breakpoint here to inspect iterator state
}

void debug_iteration_example() {
    std::vector<int> data = {10, 20, 30, 40, 50};
    
    auto it = data.begin();
    debug_iterator_position(it, data.begin(), data.end(), "it");
    
    std::advance(it, 2);
    debug_iterator_position(it, data.begin(), data.end(), "it after advance(2)");
    
    ++it;
    debug_iterator_position(it, data.begin(), data.end(), "it after ++");
}
```

---

## 🧩 Hands-On Problems (2.25 hours)

### Problem Set 1: Iterator Basics (45 minutes)

#### Problem 1.1: First Steps with Iterators (15 minutes)

**Master basic iterator operations:**

```cpp
#include <vector>
#include <iostream>

void test_basic_iterators() {
    std::vector<int> numbers{10, 20, 30, 40, 50};
    
    // Task 1: Print the first element using an iterator
    auto first_it = numbers.begin();
    std::cout << "First: " << *first_it << std::endl;
    
    // Task 2: Print the last element using an iterator
    auto last_it = numbers.end();
    --last_it;  // Move back one from "one past end"
    std::cout << "Last: " << *last_it << std::endl;
    
    // Task 3: Print all elements using traditional iterator loop
    std::cout << "All: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

#### Problem 1.2: Comparing Iteration Methods (15 minutes)

**Compare different ways to iterate:**

```cpp
#include <vector>
#include <iostream>
#include <string>

void compare_iteration_methods() {
    std::vector<std::string> languages{"Python", "Java", "C++", "JavaScript"};
    
    // Version 1: Index-based approach (like traditional Java)
    std::cout << "Index-based:" << std::endl;
    for (size_t i = 0; i < languages.size(); ++i) {
        std::cout << i << ": " << languages[i] << std::endl;
    }
    
    // Version 2: Iterator-based approach
    std::cout << "Iterator-based:" << std::endl;
    size_t index = 0;
    for (auto it = languages.begin(); it != languages.end(); ++it, ++index) {
        std::cout << index << ": " << *it << std::endl;
    }
    
    // Version 3: Range-based for loop (like Python)
    std::cout << "Range-based:" << std::endl;
    index = 0;
    for (const auto& lang : languages) {
        std::cout << index++ << ": " << lang << std::endl;
    }
}
```

#### Problem 1.3: Iterator Arithmetic Practice (15 minutes)

**Practice moving through containers with iterators:**

```cpp
#include <vector>
#include <iostream>

void practice_iterator_arithmetic() {
    std::vector<int> data{1, 3, 5, 7, 9, 11, 13, 15};
    
    // Task 1: Print element at position 3 (should be 7)
    auto pos3_it = data.begin() + 3;
    std::cout << "Element at position 3: " << *pos3_it << std::endl;
    
    // Task 2: Print every other element starting from beginning
    std::cout << "Every other element: ";
    for (auto it = data.begin(); it < data.end(); it += 2) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Task 3: Print the last 3 elements
    std::cout << "Last 3 elements: ";
    auto last3_start = data.end() - 3;
    for (auto it = last3_start; it != data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

### Problem Set 2: Range-Based For Loops (45 minutes)

#### Problem 2.1: Modernizing Traditional Loops (15 minutes)

**Convert traditional loops to range-based for loops:**

```cpp
#include <vector>
#include <iostream>
#include <numeric>

void old_style_examples() {
    std::vector<double> grades{85.5, 92.0, 78.5, 96.0, 88.5};
    
    // Old style 1: Index-based
    std::cout << "Grades: ";
    for (size_t i = 0; i < grades.size(); ++i) {
        std::cout << grades[i] << " ";
    }
    std::cout << std::endl;
    
    // Old style 2: Iterator-based
    double total = 0.0;
    for (auto it = grades.begin(); it != grades.end(); ++it) {
        total += *it;
    }
    std::cout << "Average: " << total / grades.size() << std::endl;
}

void modern_style_examples() {
    std::vector<double> grades{85.5, 92.0, 78.5, 96.0, 88.5};
    
    // Modern style 1: Range-based for display
    std::cout << "Grades: ";
    for (const auto& grade : grades) {
        std::cout << grade << " ";
    }
    std::cout << std::endl;
    
    // Modern style 2: Range-based for calculation
    double total = 0.0;
    for (const auto& grade : grades) {
        total += grade;
    }
    std::cout << "Average: " << total / grades.size() << std::endl;
    
    // Even more modern: use standard library
    double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
    std::cout << "Average (STL): " << sum / grades.size() << std::endl;
}
```

#### Problem 2.2: Element Modification Practice (15 minutes)

**Use range-based for loops to modify container contents:**

```cpp
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

void practice_modification() {
    // Task 1: Double all numbers
    std::vector<int> numbers{1, 2, 3, 4, 5};
    for (auto& num : numbers) {  // Use auto& to modify
        num *= 2;
    }
    
    // Task 2: Capitalize first letter of each word
    std::vector<std::string> words{"hello", "world", "cpp", "iterators"};
    for (auto& word : words) {  // Use auto& to modify
        if (!word.empty()) {
            word[0] = std::toupper(word[0]);
        }
    }
    
    // Task 3: Count positive numbers
    std::vector<int> mixed{-5, 3, -1, 8, 0, -2, 7};
    int positive_count = 0;
    for (const auto& num : mixed) {  // const auto& for read-only
        if (num > 0) {
            positive_count++;
        }
    }
    
    // Display results
    std::cout << "Doubled numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Capitalized words: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Positive count: " << positive_count << std::endl;
}
```

#### Problem 2.3: Reference Semantics Mastery (15 minutes)

**Understand when to use different reference types:**

```cpp
#include <vector>
#include <iostream>
#include <string>

void practice_reference_semantics() {
    std::vector<std::string> names{"Alice", "Bob", "Charlie", "Diana"};
    
    // Scenario 1: Just reading/printing (most efficient)
    std::cout << "Names: ";
    for (const auto& name : names) {  // const auto& - no copying, no modification
        std::cout << name << " ";
    }
    std::cout << std::endl;
    
    // Scenario 2: Modifying each element
    std::cout << "Adding exclamation marks:" << std::endl;
    for (auto& name : names) {  // auto& - can modify original elements
        name += "!";
        std::cout << name << std::endl;
    }
    
    // Scenario 3: Need local copies for processing
    std::cout << "Processing copies (originals unchanged):" << std::endl;
    for (auto name : names) {  // auto - creates copies
        name += " [processed]";  // Only modifies the copy
        std::cout << name << std::endl;
    }
    
    // Show original names are modified only by scenario 2
    std::cout << "Original names after all operations: ";
    for (const auto& name : names) {
        std::cout << name << " ";
    }
    std::cout << std::endl;
}
```

### Problem Set 3: Advanced Iterator Patterns (55 minutes)

#### Problem 3.1: Custom Iterator Functions (20 minutes)

**Implement utility functions using iterators:**

```cpp
#include <vector>
#include <iostream>
#include <algorithm>

// Generic function to check if container contains value
template<typename Container, typename T>
bool contains(const Container& container, const T& value) {
    return std::find(container.begin(), container.end(), value) != container.end();
}

// Count occurrences of value in container
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

// Print container in reverse order
template<typename Container>
void print_reverse(const Container& container) {
    // Use reverse iterators
    for (auto it = container.rbegin(); it != container.rend(); ++it) {
        std::cout << *it << " ";
    }
}

// Alternative reverse print using regular iterators
template<typename Container>
void print_reverse_manual(const Container& container) {
    if (container.empty()) return;
    
    auto it = container.end();
    --it;  // Move to last element
    
    while (true) {
        std::cout << *it << " ";
        if (it == container.begin()) break;
        --it;
    }
}

void test_custom_functions() {
    std::vector<int> data{1, 3, 7, 3, 9, 3, 5};
    
    std::cout << "Data: ";
    for (const auto& item : data) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Contains 7: " << (contains(data, 7) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 4: " << (contains(data, 4) ? "Yes" : "No") << std::endl;
    std::cout << "Count of 3: " << count_occurrences(data, 3) << std::endl;
    
    std::cout << "Reverse (using rbegin/rend): ";
    print_reverse(data);
    std::cout << std::endl;
    
    std::cout << "Reverse (manual): ";
    print_reverse_manual(data);
    std::cout << std::endl;
}
```

#### Problem 3.2: Safe Container Modification (15 minutes)

**Handle iterator invalidation correctly:**

```cpp
#include <vector>
#include <iostream>

void demonstrate_safe_modification() {
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "Original numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Safe removal pattern using traditional iterators
    std::cout << "Removing even numbers:" << std::endl;
    for (auto it = numbers.begin(); it != numbers.end(); ) {
        if (*it % 2 == 0) {
            std::cout << "Erasing: " << *it << std::endl;
            it = numbers.erase(it);  // erase returns iterator to next element
        } else {
            ++it;  // Only increment if we didn't erase
        }
    }
    
    std::cout << "Remaining numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Alternative approach: collect items to remove first
void safe_removal_alternative() {
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Collect positions of items to remove
    std::vector<std::vector<int>::iterator> to_remove;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it % 2 == 0) {
            to_remove.push_back(it);
        }
    }
    
    // Remove in reverse order to maintain iterator validity
    for (auto it = to_remove.rbegin(); it != to_remove.rend(); ++it) {
        numbers.erase(*it);
    }
    
    std::cout << "Alternative method result: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
```

#### Problem 3.3: Multi-Container Student System (20 minutes)

**Integrate multiple containers with iterators:**

```cpp
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>

struct Student {
    std::string name;
    std::vector<double> grades;
    
    double calculate_average() const {
        if (grades.empty()) return 0.0;
        
        // Use iterators to sum grades
        double sum = 0.0;
        for (auto it = grades.begin(); it != grades.end(); ++it) {
            sum += *it;
        }
        return sum / grades.size();
        
        // Alternative using std::accumulate
        // return std::accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
    }
};

class ClassAnalyzer {
private:
    std::vector<Student> students;
    
public:
    void add_student(const Student& student) {
        students.push_back(student);
    }
    
    void print_all_students() const {
        std::cout << "Class Roster:" << std::endl;
        size_t position = 1;
        for (const auto& student : students) {
            std::cout << position++ << ". " << student.name 
                      << " (Average: " << student.calculate_average() << ")" << std::endl;
        }
    }
    
    Student* find_highest_average() {
        if (students.empty()) return nullptr;
        
        auto highest_it = students.begin();
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->calculate_average() > highest_it->calculate_average()) {
                highest_it = it;
            }
        }
        return &(*highest_it);
    }
    
    size_t count_above_average(double threshold) const {
        size_t count = 0;
        for (const auto& student : students) {
            if (student.calculate_average() > threshold) {
                count++;
            }
        }
        return count;
    }
    
    void print_grade_distribution() const {
        std::cout << "\nGrade Distribution:" << std::endl;
        for (const auto& student : students) {
            std::cout << student.name << "'s grades: ";
            for (const auto& grade : student.grades) {
                std::cout << grade << " ";
            }
            std::cout << std::endl;
        }
    }
};

void test_student_system() {
    ClassAnalyzer analyzer;
    
    // Add students with grades
    analyzer.add_student({"Alice Johnson", {85.0, 92.0, 78.0, 95.0}});
    analyzer.add_student({"Bob Smith", {88.0, 76.0, 92.0, 85.0}});
    analyzer.add_student({"Charlie Brown", {92.0, 88.0, 95.0, 90.0}});
    analyzer.add_student({"Diana Prince", {76.0, 82.0, 79.0, 84.0}});
    
    // Display results
    analyzer.print_all_students();
    
    // Find highest average
    Student* top_student = analyzer.find_highest_average();
    if (top_student) {
        std::cout << "\nHighest average: " << top_student->name 
                  << " (" << top_student->calculate_average() << ")" << std::endl;
    }
    
    // Count students above threshold
    double threshold = 85.0;
    size_t above_threshold = analyzer.count_above_average(threshold);
    std::cout << "Students with average above " << threshold 
              << ": " << above_threshold << std::endl;
    
    analyzer.print_grade_distribution();
}

int main() {
    test_student_system();
    return 0;
}
```

---

## 🔧 Quick Reference & Troubleshooting

### Iterator Error Solutions

#### Top 5 Iterator Errors and Fixes

| Error | Cause | Fix |
|-------|-------|-----|
| **Segmentation fault** | Using invalidated iterator | Check if container was modified during iteration |
| **Infinite loop** | Forgot to increment iterator | Always have `++it` in traditional loops |
| **Wrong element accessed** | Iterator arithmetic error | Double-check `begin() + n` calculations |
| **Compilation error with range-based for** | Wrong reference type | Use `auto&` to modify, `const auto&` to read |
| **Iterator comparison fails** | Mixed iterators from different containers | Use iterators from same container |

#### Common Iterator Invalidation Scenarios

```cpp
// ❌ DANGEROUS - Iterator invalidation
std::vector<int> vec = {1, 2, 3, 4, 5};
for (auto it = vec.begin(); it != vec.end(); ++it) {
    vec.push_back(*it);  // Invalidates all iterators!
}

// ✅ SAFE - Collect operations first
std::vector<int> to_add;
for (const auto& value : vec) {
    to_add.push_back(value);
}
vec.insert(vec.end(), to_add.begin(), to_add.end());
```

### Iterator Selection Guide

```
Need to iterate through container?
├─ Just reading elements? → Range-based for with const auto&
├─ Need to modify elements? → Range-based for with auto&
├─ Need element positions? → Traditional iterator with distance()
├─ Need to remove elements? → Traditional iterator with erase pattern
└─ Need complex navigation? → Traditional iterator with arithmetic
```

### Performance Guidelines

1. **Range-based for loops** - Fastest and safest for most cases
2. **Traditional iterators** - Use when you need fine control
3. **Iterator arithmetic** - Only available with random access iterators (vector, array)
4. **Iterator invalidation** - Avoid by not modifying container during iteration

---

## ✅ Chapter 14 Success Checklist

### Range-Based For Loop Mastery
- [ ] Can use `const auto&` for read-only iteration
- [ ] Can use `auto&` for element modification
- [ ] Understand when to use `auto` (copy) vs references
- [ ] Prefer range-based for loops for most iteration tasks

### Traditional Iterator Skills
- [ ] Can use basic iterator operations (`*it`, `++it`, comparisons)
- [ ] Understand `begin()` and `end()` concepts
- [ ] Can navigate containers with iterator arithmetic
- [ ] Know the limitations of different iterator categories

### Iterator Safety
- [ ] Understand iterator invalidation and how to avoid it
- [ ] Can safely remove elements using proper erase patterns
- [ ] Know when iterators become invalid for different containers
- [ ] Can debug common iterator-related errors

### Integration with Containers
- [ ] Can choose appropriate iteration method for different containers
- [ ] Understand performance implications of different approaches
- [ ] Can connect iterator concepts to Python/Java iteration experience
- [ ] Ready to use iterators with STL algorithms

---

## 🚀 What's Next?

**Chapter 15: STL Algorithms** will cover:
- STL algorithms (find, sort, transform, etc.)
- Using iterators with algorithms effectively
- Function objects and lambda integration
- Algorithm performance and best practices

**You've mastered C++ iteration!** 🎉 Iterators provide the bridge between containers and algorithms, giving you fine control over data traversal while maintaining safety and performance. You now understand both the modern range-based approach and the traditional iterator approach.

**Key Takeaway**: Range-based for loops should be your default choice for iteration - they're safe, readable, and efficient. Use traditional iterators when you need fine control over the iteration process, such as when removing elements or working with complex navigation patterns.

---

*Remember: Iterators are like smart pointers for container traversal. They give you the performance of direct memory access with the safety of bounds checking and type safety. Range-based for loops hide the iterator complexity while giving you Python-like syntax with C++ performance!*