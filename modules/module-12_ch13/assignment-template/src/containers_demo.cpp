// HW_13: Containers and STL
// Time: 2.25 hours (45 minutes per problem set)
// Topics: vector, deque, list, set, map, unordered containers

#include <cstdio>
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <chrono>

// ============================================================================
// PROBLEM SET 1: Sequence Containers (45 minutes)
// ============================================================================

void vector_operations() {
    printf("=== std::vector - Dynamic Arrays ===\n");
    
    // TODO 1: Basic vector operations
    printf("Basic Vector Operations:\n");
    
    std::vector<int> numbers;
    printf("  Initial size: %zu, capacity: %zu\n", numbers.size(), numbers.capacity());
    
    // Add elements
    for (int i = 1; i <= 5; i++) {
        numbers.push_back(i * 10);
        printf("  Added %d - Size: %zu, Capacity: %zu\n", 
               i * 10, numbers.size(), numbers.capacity());
    }
    
    // Access elements
    printf("  Elements: ");
    for (size_t i = 0; i < numbers.size(); i++) {
        printf("%d ", numbers[i]);  // Operator[] access
    }
    printf("\n");
    
    printf("  Using at(): ");
    for (size_t i = 0; i < numbers.size(); i++) {
        printf("%d ", numbers.at(i));  // Bounds-checked access
    }
    printf("\n");
    
    // TODO 2: Vector memory management
    printf("\nVector Memory Management:\n");
    
    std::vector<int> vec;
    vec.reserve(10);  // Pre-allocate capacity
    printf("  After reserve(10) - Size: %zu, Capacity: %zu\n", 
           vec.size(), vec.capacity());
    
    for (int i = 0; i < 15; i++) {
        vec.push_back(i);
        if (i < 12) {  // Don't spam output
            printf("  Added %d - Size: %zu, Capacity: %zu\n", 
                   i, vec.size(), vec.capacity());
        }
    }
    
    vec.shrink_to_fit();
    printf("  After shrink_to_fit() - Size: %zu, Capacity: %zu\n", 
           vec.size(), vec.capacity());
    
    // TODO 3: Vector with custom objects
    printf("\nVector with Custom Objects:\n");
    
    struct Student {
        std::string name;
        int grade;
        
        Student(const std::string& n, int g) : name(n), grade(g) {
            printf("    Student '%s' created\n", name.c_str());
        }
    };
    
    std::vector<Student> students;
    students.emplace_back("Alice", 95);  // Construct in-place
    students.emplace_back("Bob", 87);
    students.emplace_back("Carol", 92);
    
    printf("  Students:\n");
    for (const auto& student : students) {
        printf("    %s: %d\n", student.name.c_str(), student.grade);
    }
    
    printf("\n");
}

void deque_operations() {
    printf("=== std::deque - Double-Ended Queue ===\n");
    
    // TODO 4: Deque front/back operations
    printf("Double-Ended Operations:\n");
    
    std::deque<int> dq;
    
    // Add to both ends
    dq.push_back(3);
    dq.push_back(4);
    dq.push_front(2);
    dq.push_front(1);
    dq.push_back(5);
    
    printf("  After mixed insertions: ");
    for (int val : dq) {
        printf("%d ", val);
    }
    printf("\n");
    
    // Remove from both ends
    printf("  Removing from ends:\n");
    while (!dq.empty()) {
        printf("    Front: %d, Back: %d\n", dq.front(), dq.back());
        
        if (dq.size() > 1) {
            dq.pop_front();
            if (!dq.empty()) dq.pop_back();
        } else {
            dq.pop_front();
        }
        
        printf("    Remaining: ");
        for (int val : dq) {
            printf("%d ", val);
        }
        printf("(size: %zu)\n", dq.size());
    }
    
    // TODO 5: Deque vs vector performance
    printf("\nDeque vs Vector - Front Insertion Performance:\n");
    
    const int n = 1000;
    
    // Vector front insertion (inefficient)
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> vec;
    for (int i = 0; i < n; i++) {
        vec.insert(vec.begin(), i);  // Insert at front
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto vector_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Deque front insertion (efficient)
    start = std::chrono::high_resolution_clock::now();
    std::deque<int> deq;
    for (int i = 0; i < n; i++) {
        deq.push_front(i);  // Insert at front
    }
    end = std::chrono::high_resolution_clock::now();
    auto deque_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    printf("  Vector front insertion (%d elements): %ld µs\n", n, vector_time.count());
    printf("  Deque front insertion (%d elements): %ld µs\n", n, deque_time.count());
    printf("  Deque is ~%.1fx faster\n", 
           static_cast<double>(vector_time.count()) / deque_time.count());
    
    printf("\n");
}

void list_operations() {
    printf("=== std::list - Doubly-Linked List ===\n");
    
    // TODO 6: List insertion and removal
    printf("List Insertion and Removal:\n");
    
    std::list<int> lst = {10, 20, 30, 40, 50};
    
    printf("  Initial list: ");
    for (int val : lst) {
        printf("%d ", val);
    }
    printf("\n");
    
    // Insert at specific position
    auto it = lst.begin();
    std::advance(it, 2);  // Move to 3rd position
    lst.insert(it, 25);   // Insert before 3rd element
    
    printf("  After inserting 25: ");
    for (int val : lst) {
        printf("%d ", val);
    }
    printf("\n");
    
    // Remove specific values
    lst.remove(20);  // Remove all occurrences of 20
    printf("  After removing 20: ");
    for (int val : lst) {
        printf("%d ", val);
    }
    printf("\n");
    
    // TODO 7: List splice operations
    printf("\nList Splice Operations:\n");
    
    std::list<int> list1 = {1, 3, 5};
    std::list<int> list2 = {2, 4, 6};
    
    printf("  List1: ");
    for (int val : list1) printf("%d ", val);
    printf("\n");
    
    printf("  List2: ");
    for (int val : list2) printf("%d ", val);
    printf("\n");
    
    // Splice list2 into list1
    auto splice_pos = list1.begin();
    std::advance(splice_pos, 1);  // After first element
    list1.splice(splice_pos, list2);
    
    printf("  After splicing list2 into list1: ");
    for (int val : list1) {
        printf("%d ", val);
    }
    printf("\n");
    
    printf("  List2 after splice: ");
    for (int val : list2) {
        printf("%d ", val);
    }
    printf("(empty: %s)\n", list2.empty() ? "yes" : "no");
    
    // TODO 8: List sorting and merging
    printf("\nList Sorting and Merging:\n");
    
    std::list<int> unsorted = {30, 10, 40, 20, 50};
    printf("  Before sort: ");
    for (int val : unsorted) printf("%d ", val);
    printf("\n");
    
    unsorted.sort();
    printf("  After sort: ");
    for (int val : unsorted) printf("%d ", val);
    printf("\n");
    
    printf("\n");
}

void problem_set_1_demo() {
    printf("=== Problem Set 1: Sequence Containers ===\n\n");
    
    vector_operations();
    deque_operations();
    list_operations();
}

// ============================================================================
// PROBLEM SET 2: Associative Containers (45 minutes)
// ============================================================================

void set_operations() {
    printf("=== std::set - Ordered Unique Elements ===\n");
    
    // TODO 9: Basic set operations
    printf("Basic Set Operations:\n");
    
    std::set<int> numbers = {5, 2, 8, 1, 9, 2, 5};  // Duplicates ignored
    
    printf("  Set contents: ");
    for (int val : numbers) {
        printf("%d ", val);  // Automatically sorted
    }
    printf("(size: %zu)\n", numbers.size());
    
    // Insert operations
    auto [it1, inserted1] = numbers.insert(7);
    printf("  Insert 7: %s (position: %d)\n", 
           inserted1 ? "success" : "failed", *it1);
    
    auto [it2, inserted2] = numbers.insert(5);  // Duplicate
    printf("  Insert 5: %s (position: %d)\n", 
           inserted2 ? "success" : "failed", *it2);
    
    // Find operations
    auto find_it = numbers.find(8);
    if (find_it != numbers.end()) {
        printf("  Found 8 in set\n");
    }
    
    if (numbers.count(10) > 0) {
        printf("  Found 10 in set\n");
    } else {
        printf("  10 not found in set\n");
    }
    
    // TODO 10: Set with custom comparator
    printf("\nSet with Custom Comparator:\n");
    
    // Sort strings by length instead of alphabetically
    auto length_compare = [](const std::string& a, const std::string& b) {
        if (a.length() != b.length()) {
            return a.length() < b.length();
        }
        return a < b;  // Alphabetical for same length
    };
    
    std::set<std::string, decltype(length_compare)> word_set(length_compare);
    
    word_set.insert("cat");
    word_set.insert("elephant");
    word_set.insert("dog");
    word_set.insert("a");
    word_set.insert("bird");
    
    printf("  Words sorted by length: ");
    for (const auto& word : word_set) {
        printf("%s ", word.c_str());
    }
    printf("\n");
    
    // TODO 11: multiset for duplicates
    printf("\nMultiset for Duplicate Elements:\n");
    
    std::multiset<int> scores = {85, 92, 78, 85, 95, 78, 88};
    
    printf("  All scores: ");
    for (int score : scores) {
        printf("%d ", score);
    }
    printf("\n");
    
    printf("  Score 85 appears %zu times\n", scores.count(85));
    printf("  Score 78 appears %zu times\n", scores.count(78));
    
    // Range of equal elements
    auto range = scores.equal_range(85);
    printf("  All instances of 85: ");
    for (auto it = range.first; it != range.second; ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    
    printf("\n");
}

void map_operations() {
    printf("=== std::map - Key-Value Pairs ===\n");
    
    // TODO 12: Basic map operations
    printf("Basic Map Operations:\n");
    
    std::map<std::string, int> student_grades;
    
    // Insert methods
    student_grades["Alice"] = 95;  // Operator[] insertion
    student_grades.insert({"Bob", 87});  // insert method
    student_grades.emplace("Carol", 92);  // emplace method
    
    printf("  Student grades:\n");
    for (const auto& [name, grade] : student_grades) {
        printf("    %s: %d\n", name.c_str(), grade);
    }
    
    // Access and modification
    printf("  Alice's grade: %d\n", student_grades["Alice"]);
    student_grades["Alice"] = 98;  // Modify existing
    printf("  Alice's updated grade: %d\n", student_grades["Alice"]);
    
    // Safe access with find
    auto it = student_grades.find("Dave");
    if (it != student_grades.end()) {
        printf("  Dave's grade: %d\n", it->second);
    } else {
        printf("  Dave not found in gradebook\n");
    }
    
    // TODO 13: Map iteration and algorithms
    printf("\nMap Iteration and Algorithms:\n");
    
    // Find highest grade
    auto max_grade = std::max_element(student_grades.begin(), student_grades.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    
    if (max_grade != student_grades.end()) {
        printf("  Highest grade: %s with %d\n", 
               max_grade->first.c_str(), max_grade->second);
    }
    
    // Count students with A grades (90+)
    auto a_students = std::count_if(student_grades.begin(), student_grades.end(),
        [](const auto& pair) {
            return pair.second >= 90;
        });
    printf("  Students with A grades: %ld\n", a_students);
    
    // TODO 14: multimap for one-to-many relationships
    printf("\nMultimap for One-to-Many Relationships:\n");
    
    std::multimap<std::string, std::string> department_employees;
    
    department_employees.emplace("Engineering", "Alice");
    department_employees.emplace("Engineering", "Bob");
    department_employees.emplace("Marketing", "Carol");
    department_employees.emplace("Engineering", "Dave");
    department_employees.emplace("Marketing", "Eve");
    
    printf("  Department employees:\n");
    for (const auto& [dept, employee] : department_employees) {
        printf("    %s: %s\n", dept.c_str(), employee.c_str());
    }
    
    // Find all employees in Engineering
    printf("  Engineering employees: ");
    auto eng_range = department_employees.equal_range("Engineering");
    for (auto it = eng_range.first; it != eng_range.second; ++it) {
        printf("%s ", it->second.c_str());
    }
    printf("\n");
    
    printf("\n");
}

void container_operations() {
    printf("=== Container Operations: Insert, Find, Erase ===\n");
    
    // TODO 15: Comprehensive operations demo
    printf("Comprehensive Operations:\n");
    
    std::map<int, std::string> id_to_name;
    
    // Batch insertion
    std::vector<std::pair<int, std::string>> data = {
        {101, "Alice"}, {102, "Bob"}, {103, "Carol"}, 
        {104, "Dave"}, {105, "Eve"}
    };
    
    for (const auto& [id, name] : data) {
        id_to_name[id] = name;
    }
    
    printf("  Initial data:\n");
    for (const auto& [id, name] : id_to_name) {
        printf("    ID %d: %s\n", id, name.c_str());
    }
    
    // Conditional operations
    printf("  Conditional operations:\n");
    
    // Insert only if key doesn't exist
    auto [it, inserted] = id_to_name.try_emplace(103, "Charlie");
    printf("    try_emplace(103, 'Charlie'): %s\n", 
           inserted ? "inserted" : "key existed");
    
    // Insert or assign (always succeeds)
    auto [it2, was_new] = id_to_name.insert_or_assign(106, "Frank");
    printf("    insert_or_assign(106, 'Frank'): %s\n", 
           was_new ? "new key" : "updated existing");
    
    // Erase operations
    printf("  Erase operations:\n");
    
    auto erase_count = id_to_name.erase(102);  // Erase by key
    printf("    Erased key 102: %zu elements removed\n", erase_count);
    
    auto erase_it = id_to_name.find(104);
    if (erase_it != id_to_name.end()) {
        id_to_name.erase(erase_it);  // Erase by iterator
        printf("    Erased key 104 by iterator\n");
    }
    
    printf("  Final data:\n");
    for (const auto& [id, name] : id_to_name) {
        printf("    ID %d: %s\n", id, name.c_str());
    }
    
    printf("\n");
}

void problem_set_2_demo() {
    printf("=== Problem Set 2: Associative Containers ===\n\n");
    
    set_operations();
    map_operations();
    container_operations();
}

// ============================================================================
// PROBLEM SET 3: Unordered Containers and Performance (45 minutes)
// ============================================================================

void unordered_containers() {
    printf("=== Unordered Containers - Hash-Based ===\n");
    
    // TODO 16: unordered_set operations
    printf("Unordered Set Operations:\n");
    
    std::unordered_set<std::string> unique_words;
    
    std::vector<std::string> text = {
        "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog", "the"
    };
    
    for (const auto& word : text) {
        auto [it, inserted] = unique_words.insert(word);
        if (inserted) {
            printf("  Added: %s\n", word.c_str());
        } else {
            printf("  Duplicate: %s\n", word.c_str());
        }
    }
    
    printf("  Unique words (%zu): ", unique_words.size());
    for (const auto& word : unique_words) {
        printf("%s ", word.c_str());
    }
    printf("\n");
    
    printf("  Load factor: %.2f, Bucket count: %zu\n", 
           unique_words.load_factor(), unique_words.bucket_count());
    
    // TODO 17: unordered_map operations  
    printf("\nUnordered Map - Word Frequency:\n");
    
    std::unordered_map<std::string, int> word_count;
    
    for (const auto& word : text) {
        word_count[word]++;  // Auto-initialize to 0 if not present
    }
    
    printf("  Word frequencies:\n");
    for (const auto& [word, count] : word_count) {
        printf("    %s: %d\n", word.c_str(), count);
    }
    
    // Find most frequent word
    auto max_word = std::max_element(word_count.begin(), word_count.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    
    if (max_word != word_count.end()) {
        printf("  Most frequent: '%s' (%d times)\n", 
               max_word->first.c_str(), max_word->second);
    }
    
    printf("\n");
}

void performance_comparison() {
    printf("=== Performance Comparison: Ordered vs Unordered ===\n");
    
    const int n = 10000;
    std::vector<int> test_data;
    
    // Generate random test data
    for (int i = 0; i < n; i++) {
        test_data.push_back(rand() % (n * 2));
    }
    
    // TODO 18: Insertion performance
    printf("Insertion Performance (%d elements):\n", n);
    
    // std::set insertion
    auto start = std::chrono::high_resolution_clock::now();
    std::set<int> ordered_set;
    for (int val : test_data) {
        ordered_set.insert(val);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto set_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // std::unordered_set insertion
    start = std::chrono::high_resolution_clock::now();
    std::unordered_set<int> unordered_set;
    for (int val : test_data) {
        unordered_set.insert(val);
    }
    end = std::chrono::high_resolution_clock::now();
    auto uset_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    printf("  std::set: %ld µs\n", set_time.count());
    printf("  std::unordered_set: %ld µs\n", uset_time.count());
    printf("  Unordered is %.1fx faster for insertion\n", 
           static_cast<double>(set_time.count()) / uset_time.count());
    
    // TODO 19: Lookup performance
    printf("\nLookup Performance:\n");
    
    std::vector<int> search_keys;
    for (int i = 0; i < 1000; i++) {
        search_keys.push_back(rand() % (n * 2));
    }
    
    // std::set lookup
    start = std::chrono::high_resolution_clock::now();
    int set_found = 0;
    for (int key : search_keys) {
        if (ordered_set.find(key) != ordered_set.end()) {
            set_found++;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto set_lookup_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // std::unordered_set lookup
    start = std::chrono::high_resolution_clock::now();
    int uset_found = 0;
    for (int key : search_keys) {
        if (unordered_set.find(key) != unordered_set.end()) {
            uset_found++;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto uset_lookup_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    printf("  std::set: %ld µs (%d found)\n", set_lookup_time.count(), set_found);
    printf("  std::unordered_set: %ld µs (%d found)\n", uset_lookup_time.count(), uset_found);
    printf("  Unordered is %.1fx faster for lookup\n", 
           static_cast<double>(set_lookup_time.count()) / uset_lookup_time.count());
    
    printf("\n");
}

// TODO 20: Custom hash and comparator
struct Person {
    std::string name;
    int age;
    
    Person(const std::string& n, int a) : name(n), age(a) {}
    
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
};

// Custom hash function for Person
struct PersonHash {
    std::size_t operator()(const Person& p) const {
        std::size_t h1 = std::hash<std::string>{}(p.name);
        std::size_t h2 = std::hash<int>{}(p.age);
        return h1 ^ (h2 << 1);  // Combine hashes
    }
};

// Custom comparator for Person (for ordered containers)
struct PersonCompare {
    bool operator()(const Person& a, const Person& b) const {
        if (a.name != b.name) {
            return a.name < b.name;
        }
        return a.age < b.age;
    }
};

void custom_comparators() {
    printf("=== Custom Comparators and Hash Functions ===\n");
    
    // TODO: Custom comparator with set
    printf("Custom Comparator with std::set:\n");
    
    std::set<Person, PersonCompare> ordered_people;
    
    ordered_people.emplace("Alice", 25);
    ordered_people.emplace("Bob", 30);
    ordered_people.emplace("Alice", 30);  // Different age, so different person
    ordered_people.emplace("Carol", 28);
    
    printf("  Ordered people (by name, then age):\n");
    for (const auto& person : ordered_people) {
        printf("    %s, age %d\n", person.name.c_str(), person.age);
    }
    
    // TODO: Custom hash with unordered_set
    printf("\nCustom Hash with std::unordered_set:\n");
    
    std::unordered_set<Person, PersonHash> unordered_people;
    
    unordered_people.emplace("Dave", 35);
    unordered_people.emplace("Eve", 25);
    unordered_people.emplace("Dave", 35);  // Duplicate - won't be added
    unordered_people.emplace("Frank", 40);
    
    printf("  Unordered people (with custom hash):\n");
    for (const auto& person : unordered_people) {
        printf("    %s, age %d\n", person.name.c_str(), person.age);
    }
    
    printf("  Hash table stats - Load factor: %.2f, Bucket count: %zu\n", 
           unordered_people.load_factor(), unordered_people.bucket_count());
    
    printf("\n");
}

void problem_set_3_demo() {
    printf("=== Problem Set 3: Unordered Containers and Performance ===\n\n");
    
    unordered_containers();
    performance_comparison();
    custom_comparators();
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("        HW_13: Containers and STL\n");
    printf("==========================================\n\n");
    
    // Problem Set 1: Sequence Containers (45 min)
    problem_set_1_demo();
    
    // Problem Set 2: Associative Containers (45 min)
    problem_set_2_demo();
    
    // Problem Set 3: Unordered Containers and Performance (45 min)
    problem_set_3_demo();
    
    printf("==========================================\n");
    printf("           Program Complete!\n");
    printf("==========================================\n");
    
    return 0;
}