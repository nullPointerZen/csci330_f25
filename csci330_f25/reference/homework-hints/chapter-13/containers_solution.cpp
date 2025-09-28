#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <chrono>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

// Vector fundamentals
void vector_basics_demo() {
    std::cout << "=== Vector Basics Demo ===\n";

    std::vector<double> grades;
    grades.push_back(85.5);
    grades.push_back(92.0);
    grades.push_back(78.5);
    grades.push_back(96.0);
    grades.push_back(88.5);

    // Calculate average
    double sum = 0.0;
    for (const auto& grade : grades) {
        sum += grade;
    }
    double average = sum / grades.size();
    std::cout << "Average grade: " << average << std::endl;

    // Find highest grade
    auto highest = *std::max_element(grades.begin(), grades.end());
    std::cout << "Highest grade: " << highest << std::endl;

    // Demonstrate both access methods
    std::cout << "Grade at index 2 (using []): " << grades[2] << std::endl;
    std::cout << "Grade at index 2 (using at()): " << grades.at(2) << std::endl;

    // Show size and capacity
    std::cout << "Size: " << grades.size() << ", Capacity: " << grades.capacity() << std::endl;
}

// Student Roster class demonstrating dynamic operations
class StudentRoster {
private:
    std::vector<std::string> students;

public:
    void addStudent(const std::string& name) {
        students.push_back(name);
        std::cout << "Added student: " << name << std::endl;
    }

    void insertStudent(const std::string& name, size_t position) {
        if (position <= students.size()) {
            students.insert(students.begin() + position, name);
            std::cout << "Inserted " << name << " at position " << position << std::endl;
        } else {
            std::cout << "Position " << position << " is out of bounds" << std::endl;
        }
    }

    void removeStudent(const std::string& name) {
        auto it = std::find(students.begin(), students.end(), name);
        if (it != students.end()) {
            students.erase(it);
            std::cout << "Removed student: " << name << std::endl;
        } else {
            std::cout << "Student " << name << " not found" << std::endl;
        }
    }

    void displayStudents() const {
        std::cout << "Student roster (" << students.size() << " students):\n";
        for (size_t i = 0; i < students.size(); ++i) {
            std::cout << "  " << i << ": " << students[i] << std::endl;
        }
    }
};

// Performance comparison between vector and list
void performance_comparison() {
    std::cout << "\n=== Performance Comparison: Vector vs List ===\n";

    const int SIZE = 10000;
    const int OPERATIONS = 1000;

    // Create containers
    std::vector<int> vec(SIZE);
    std::list<int> lst(SIZE);

    // Fill with data
    std::iota(vec.begin(), vec.end(), 0);
    std::iota(lst.begin(), lst.end(), 0);

    // Test front insertion
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < OPERATIONS; ++i) {
        vec.insert(vec.begin(), i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto vec_front_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < OPERATIONS; ++i) {
        lst.push_front(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto list_front_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Front insertion (" << OPERATIONS << " operations):\n";
    std::cout << "  Vector: " << vec_front_time.count() << " microseconds\n";
    std::cout << "  List: " << list_front_time.count() << " microseconds\n";

    // Test back insertion
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < OPERATIONS; ++i) {
        vec.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto vec_back_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < OPERATIONS; ++i) {
        lst.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto list_back_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Back insertion (" << OPERATIONS << " operations):\n";
    std::cout << "  Vector: " << vec_back_time.count() << " microseconds\n";
    std::cout << "  List: " << list_back_time.count() << " microseconds\n";

    // Test random access (only for vector)
    start = std::chrono::high_resolution_clock::now();
    int sum = 0;
    for (int i = 0; i < OPERATIONS; ++i) {
        sum += vec[SIZE / 2];  // Access middle element
    }
    end = std::chrono::high_resolution_clock::now();
    auto vec_access_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Random access (" << OPERATIONS << " operations):\n";
    std::cout << "  Vector: " << vec_access_time.count() << " microseconds\n";
    std::cout << "  List: Not supported (would require linear traversal)\n";
}

// Word frequency counter using map
void word_frequency_demo() {
    std::cout << "\n=== Word Frequency Counter Demo ===\n";

    std::vector<std::string> words = {"apple", "banana", "apple", "cherry", "banana", "apple", "date"};

    std::map<std::string, int> frequency;
    for (const auto& word : words) {
        frequency[word]++;
    }

    std::cout << "Word frequencies (alphabetical order):\n";
    for (const auto& [word, count] : frequency) {
        std::cout << "  " << word << ": " << count << std::endl;
    }

    // Find most frequent word
    auto most_frequent = std::max_element(frequency.begin(), frequency.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

    if (most_frequent != frequency.end()) {
        std::cout << "Most frequent word: " << most_frequent->first
                  << " (" << most_frequent->second << " times)" << std::endl;
    }
}

// Set operations
std::set<int> setUnion(const std::set<int>& set1, const std::set<int>& set2) {
    std::set<int> result;
    std::set_union(set1.begin(), set1.end(),
                   set2.begin(), set2.end(),
                   std::inserter(result, result.begin()));
    return result;
}

std::set<int> setIntersection(const std::set<int>& set1, const std::set<int>& set2) {
    std::set<int> result;
    std::set_intersection(set1.begin(), set1.end(),
                          set2.begin(), set2.end(),
                          std::inserter(result, result.begin()));
    return result;
}

std::set<int> setDifference(const std::set<int>& set1, const std::set<int>& set2) {
    std::set<int> result;
    std::set_difference(set1.begin(), set1.end(),
                        set2.begin(), set2.end(),
                        std::inserter(result, result.begin()));
    return result;
}

void print_set(const std::set<int>& s, const std::string& name) {
    std::cout << name << ": {";
    bool first = true;
    for (int element : s) {
        if (!first) std::cout << ", ";
        std::cout << element;
        first = false;
    }
    std::cout << "}\n";
}

void set_operations_demo() {
    std::cout << "\n=== Set Operations Demo ===\n";

    std::set<int> set1 = {1, 2, 3, 4, 5};
    std::set<int> set2 = {4, 5, 6, 7, 8};

    print_set(set1, "Set 1");
    print_set(set2, "Set 2");

    auto union_set = setUnion(set1, set2);
    auto intersection_set = setIntersection(set1, set2);
    auto difference_set = setDifference(set1, set2);

    print_set(union_set, "Union");
    print_set(intersection_set, "Intersection");
    print_set(difference_set, "Difference (Set1 - Set2)");
}

// Student database using multiple associative containers
class StudentDatabase {
private:
    std::map<int, std::string> id_to_name;
    std::map<std::string, double> name_to_gpa;
    std::set<std::string> honor_roll;

public:
    void addStudent(int id, const std::string& name, double gpa) {
        id_to_name[id] = name;
        name_to_gpa[name] = gpa;

        if (gpa >= 3.5) {
            honor_roll.insert(name);
        }

        std::cout << "Added student: " << name << " (ID: " << id << ", GPA: " << gpa << ")" << std::endl;
    }

    std::optional<double> findGpaById(int id) {
        auto it = id_to_name.find(id);
        if (it != id_to_name.end()) {
            const std::string& name = it->second;
            auto gpa_it = name_to_gpa.find(name);
            if (gpa_it != name_to_gpa.end()) {
                return gpa_it->second;
            }
        }
        return std::nullopt;
    }

    void listHonorRoll() const {
        std::cout << "Honor Roll Students (GPA >= 3.5):\n";
        for (const auto& name : honor_roll) {
            auto gpa_it = name_to_gpa.find(name);
            if (gpa_it != name_to_gpa.end()) {
                std::cout << "  " << name << " (GPA: " << gpa_it->second << ")" << std::endl;
            }
        }
    }

    void displayAllStudents() const {
        std::cout << "All Students:\n";
        for (const auto& [id, name] : id_to_name) {
            auto gpa_it = name_to_gpa.find(name);
            double gpa = (gpa_it != name_to_gpa.end()) ? gpa_it->second : 0.0;
            std::cout << "  ID: " << id << ", Name: " << name << ", GPA: " << gpa << std::endl;
        }
    }
};

// Hash performance comparison
void hash_performance_comparison() {
    std::cout << "\n=== Hash Performance Comparison ===\n";

    const int SIZE = 100000;
    const int LOOKUPS = 10000;

    std::vector<int> test_data(SIZE);
    std::iota(test_data.begin(), test_data.end(), 0);
    std::random_shuffle(test_data.begin(), test_data.end());

    // Test map insertion
    std::map<int, int> ordered_map;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        ordered_map[test_data[i]] = i;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto map_insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Test unordered_map insertion
    std::unordered_map<int, int> hash_map;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        hash_map[test_data[i]] = i;
    }
    end = std::chrono::high_resolution_clock::now();
    auto hash_insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Insertion of " << SIZE << " elements:\n";
    std::cout << "  std::map: " << map_insert_time.count() << " ms\n";
    std::cout << "  std::unordered_map: " << hash_insert_time.count() << " ms\n";

    // Test lookup performance
    std::vector<int> lookup_keys(LOOKUPS);
    for (int i = 0; i < LOOKUPS; ++i) {
        lookup_keys[i] = test_data[i % SIZE];
    }

    // Map lookup
    start = std::chrono::high_resolution_clock::now();
    int map_found = 0;
    for (int key : lookup_keys) {
        if (ordered_map.find(key) != ordered_map.end()) {
            map_found++;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto map_lookup_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Hash map lookup
    start = std::chrono::high_resolution_clock::now();
    int hash_found = 0;
    for (int key : lookup_keys) {
        if (hash_map.find(key) != hash_map.end()) {
            hash_found++;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto hash_lookup_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Lookup of " << LOOKUPS << " elements:\n";
    std::cout << "  std::map: " << map_lookup_time.count() << " μs (found: " << map_found << ")\n";
    std::cout << "  std::unordered_map: " << hash_lookup_time.count() << " μs (found: " << hash_found << ")\n";
}

// Custom hash function example
struct Student {
    std::string name;
    int id;
    std::string major;

    bool operator==(const Student& other) const {
        return id == other.id;  // Students are equal if they have the same ID
    }
};

struct StudentHash {
    std::size_t operator()(const Student& s) const {
        // Combine hash of name and id
        return std::hash<std::string>{}(s.name) ^ (std::hash<int>{}(s.id) << 1);
    }
};

void custom_hash_demo() {
    std::cout << "\n=== Custom Hash Function Demo ===\n";

    std::unordered_set<Student, StudentHash> students;

    students.insert({"Alice Smith", 12345, "Computer Science"});
    students.insert({"Bob Jones", 67890, "Mathematics"});
    students.insert({"Alice Johnson", 11111, "Physics"});  // Different Alice
    students.insert({"Alice Smith", 12345, "Computer Science"});  // Duplicate (same ID)

    std::cout << "Unique students in set: " << students.size() << std::endl;

    std::cout << "Students:\n";
    for (const auto& student : students) {
        std::cout << "  " << student.name << " (ID: " << student.id << ", Major: " << student.major << ")" << std::endl;
    }

    // Test lookup
    Student search_student{"Alice Smith", 12345, ""};
    if (students.find(search_student) != students.end()) {
        std::cout << "Found Alice Smith with ID 12345" << std::endl;
    }
}

// Library Management System - Integration project
struct Book {
    std::string title;
    std::string author;
    std::string category;
    bool isAvailable = true;
};

class LibraryManagement {
private:
    std::map<std::string, Book> books;  // ISBN -> Book
    std::unordered_set<std::string> authors;
    std::set<std::string> categories;
    std::unordered_map<std::string, std::string> checked_out;  // ISBN -> borrower

public:
    void addBook(const std::string& isbn, const std::string& title,
                 const std::string& author, const std::string& category) {
        books[isbn] = {title, author, category, true};
        authors.insert(author);
        categories.insert(category);
        std::cout << "Added book: " << title << " by " << author << std::endl;
    }

    bool checkOutBook(const std::string& isbn, const std::string& borrower) {
        auto it = books.find(isbn);
        if (it != books.end() && it->second.isAvailable) {
            it->second.isAvailable = false;
            checked_out[isbn] = borrower;
            std::cout << borrower << " checked out: " << it->second.title << std::endl;
            return true;
        }
        std::cout << "Book not available for checkout" << std::endl;
        return false;
    }

    bool returnBook(const std::string& isbn) {
        auto it = books.find(isbn);
        if (it != books.end() && !it->second.isAvailable) {
            it->second.isAvailable = true;
            checked_out.erase(isbn);
            std::cout << "Returned: " << it->second.title << std::endl;
            return true;
        }
        std::cout << "Book was not checked out" << std::endl;
        return false;
    }

    std::vector<Book> findBooksByAuthor(const std::string& author) {
        std::vector<Book> result;
        for (const auto& [isbn, book] : books) {
            if (book.author == author) {
                result.push_back(book);
            }
        }
        return result;
    }

    void listCategories() {
        std::cout << "Available categories:\n";
        for (const auto& category : categories) {
            std::cout << "  " << category << std::endl;
        }
    }

    void showCheckedOutBooks() {
        std::cout << "Currently checked out books:\n";
        for (const auto& [isbn, borrower] : checked_out) {
            auto it = books.find(isbn);
            if (it != books.end()) {
                std::cout << "  " << it->second.title << " -> " << borrower << std::endl;
            }
        }
    }

    void showLibraryStats() {
        std::cout << "Library Statistics:\n";
        std::cout << "  Total books: " << books.size() << std::endl;
        std::cout << "  Unique authors: " << authors.size() << std::endl;
        std::cout << "  Categories: " << categories.size() << std::endl;
        std::cout << "  Books checked out: " << checked_out.size() << std::endl;
    }
};

int main() {
    vector_basics_demo();

    std::cout << "\n=== Student Roster Demo ===\n";
    StudentRoster roster;
    roster.addStudent("Alice");
    roster.addStudent("Bob");
    roster.addStudent("Charlie");
    roster.displayStudents();
    roster.insertStudent("Diana", 1);
    roster.displayStudents();
    roster.removeStudent("Bob");
    roster.displayStudents();

    performance_comparison();
    word_frequency_demo();
    set_operations_demo();

    std::cout << "\n=== Student Database Demo ===\n";
    StudentDatabase db;
    db.addStudent(1001, "Alice Johnson", 3.8);
    db.addStudent(1002, "Bob Smith", 3.2);
    db.addStudent(1003, "Charlie Brown", 3.9);
    db.addStudent(1004, "Diana Prince", 3.6);

    auto gpa = db.findGpaById(1002);
    if (gpa) {
        std::cout << "Student 1002 GPA: " << *gpa << std::endl;
    }

    db.listHonorRoll();
    db.displayAllStudents();

    hash_performance_comparison();
    custom_hash_demo();

    std::cout << "\n=== Library Management System Demo ===\n";
    LibraryManagement library;

    library.addBook("978-0134685991", "Effective Modern C++", "Scott Meyers", "Programming");
    library.addBook("978-0321563842", "The C++ Programming Language", "Bjarne Stroustrup", "Programming");
    library.addBook("978-0201633610", "Design Patterns", "Gang of Four", "Software Engineering");
    library.addBook("978-0135166307", "Tour of C++", "Bjarne Stroustrup", "Programming");

    library.showLibraryStats();
    library.listCategories();

    library.checkOutBook("978-0134685991", "Alice");
    library.checkOutBook("978-0201633610", "Bob");
    library.showCheckedOutBooks();

    auto meyers_books = library.findBooksByAuthor("Scott Meyers");
    std::cout << "Books by Scott Meyers: " << meyers_books.size() << std::endl;

    auto stroustrup_books = library.findBooksByAuthor("Bjarne Stroustrup");
    std::cout << "Books by Bjarne Stroustrup:\n";
    for (const auto& book : stroustrup_books) {
        std::cout << "  " << book.title << " (" << (book.isAvailable ? "Available" : "Checked out") << ")" << std::endl;
    }

    library.returnBook("978-0134685991");
    library.showCheckedOutBooks();

    return 0;
}