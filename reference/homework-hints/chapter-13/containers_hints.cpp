#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <chrono>
#include <random>
#include <iomanip>
#include <iterator>

// =============================================================================
// PROBLEM SET 1: CONTAINER BASICS AND SEQUENCE CONTAINERS
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 1.1: Vector Fundamentals - Grade Management System
// -----------------------------------------------------------------------------
namespace problem_1_1 {
    void demonstrate() {
        std::cout << "=== Problem 1.1: Vector Fundamentals ===\n\n";

        // 1. Declare a vector to store grades
        std::vector<double> grades;

        // 2. Add grades using push_back()
        grades.push_back(85.5);
        grades.push_back(92.0);
        grades.push_back(78.5);
        grades.push_back(95.0);
        grades.push_back(88.0);

        std::cout << "Grades added: ";
        for (double grade : grades) {
            std::cout << grade << " ";
        }
        std::cout << "\n";

        // 3. Calculate average
        double sum = 0.0;
        for (double grade : grades) {
            sum += grade;
        }
        double average = sum / grades.size();
        std::cout << "Average grade: " << std::fixed << std::setprecision(2)
                  << average << "\n";

        // 4. Find highest grade
        double highest = *std::max_element(grades.begin(), grades.end());
        std::cout << "Highest grade: " << highest << "\n";

        // 5. Demonstrate [] operator vs at() method
        std::cout << "\nAccessing elements:\n";
        std::cout << "Using []: grades[0] = " << grades[0] << "\n";
        std::cout << "Using at(): grades.at(0) = " << grades.at(0) << "\n";

        // Demonstrate bounds checking with at()
        try {
            std::cout << "Trying to access invalid index with at()...\n";
            double invalid = grades.at(100);  // Will throw exception
            std::cout << "Value: " << invalid << "\n";
        } catch (const std::out_of_range& e) {
            std::cout << "Caught exception: " << e.what() << "\n";
        }

        // Note: Using [] with invalid index would cause undefined behavior
        // std::cout << grades[100];  // DON'T DO THIS - undefined behavior!

        std::cout << "\n";
    }
}

// -----------------------------------------------------------------------------
// Problem 1.2: Dynamic Array Operations - Student Roster
// -----------------------------------------------------------------------------
namespace problem_1_2 {
    class StudentRoster {
    private:
        std::vector<std::string> students;

    public:
        // Add student to the end
        void addStudent(const std::string& name) {
            students.push_back(name);
            std::cout << "Added: " << name << "\n";
        }

        // Insert student at specific position
        void insertStudent(const std::string& name, size_t position) {
            if (position <= students.size()) {
                students.insert(students.begin() + position, name);
                std::cout << "Inserted: " << name << " at position " << position << "\n";
            } else {
                std::cout << "Invalid position!\n";
            }
        }

        // Remove student by name
        void removeStudent(const std::string& name) {
            // Use std::find to locate the student
            auto it = std::find(students.begin(), students.end(), name);
            if (it != students.end()) {
                students.erase(it);
                std::cout << "Removed: " << name << "\n";
            } else {
                std::cout << "Student not found: " << name << "\n";
            }
        }

        // Display all students
        void displayStudents() const {
            std::cout << "\nCurrent roster (" << students.size() << " students):\n";
            for (size_t i = 0; i < students.size(); ++i) {
                std::cout << "  [" << i << "] " << students[i] << "\n";
            }
            std::cout << "\n";
        }
    };

    void demonstrate() {
        std::cout << "=== Problem 1.2: Dynamic Array Operations ===\n\n";

        StudentRoster roster;

        // Add students
        roster.addStudent("Alice Johnson");
        roster.addStudent("Bob Smith");
        roster.addStudent("Charlie Davis");
        roster.displayStudents();

        // Insert a student at position 1
        roster.insertStudent("David Wilson", 1);
        roster.displayStudents();

        // Remove a student
        roster.removeStudent("Bob Smith");
        roster.displayStudents();

        // Try to remove non-existent student
        roster.removeStudent("John Doe");
    }
}

// -----------------------------------------------------------------------------
// Problem 1.3: Performance Comparison - Vector vs List
// -----------------------------------------------------------------------------
namespace problem_1_3 {
    // Helper function to measure time
    template<typename Func>
    long long measureTime(Func func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    void demonstrate() {
        std::cout << "=== Problem 1.3: Performance Comparison ===\n\n";

        const int SIZE = 10000;
        std::vector<int> vec;
        std::list<int> lst;

        // Pre-populate containers
        for (int i = 0; i < SIZE; ++i) {
            vec.push_back(i);
            lst.push_back(i);
        }

        // Test 1: Adding to front
        std::cout << "Test 1: Adding 1000 elements to FRONT\n";
        long long vecFrontTime = measureTime([&]() {
            for (int i = 0; i < 1000; ++i) {
                vec.insert(vec.begin(), i);
            }
        });

        long long lstFrontTime = measureTime([&]() {
            for (int i = 0; i < 1000; ++i) {
                lst.push_front(i);
            }
        });

        std::cout << "  Vector: " << vecFrontTime << " microseconds\n";
        std::cout << "  List: " << lstFrontTime << " microseconds\n";
        std::cout << "  Winner: " << (lstFrontTime < vecFrontTime ? "List" : "Vector") << "\n\n";

        // Test 2: Adding to back
        std::cout << "Test 2: Adding 1000 elements to BACK\n";
        long long vecBackTime = measureTime([&]() {
            for (int i = 0; i < 1000; ++i) {
                vec.push_back(i);
            }
        });

        long long lstBackTime = measureTime([&]() {
            for (int i = 0; i < 1000; ++i) {
                lst.push_back(i);
            }
        });

        std::cout << "  Vector: " << vecBackTime << " microseconds\n";
        std::cout << "  List: " << lstBackTime << " microseconds\n";
        std::cout << "  Winner: " << (vecBackTime < lstBackTime ? "Vector" : "List") << "\n\n";

        // Test 3: Random access (only vector supports this efficiently)
        std::cout << "Test 3: Random access to middle element (1000 times)\n";
        int middle = vec.size() / 2;
        long long vecAccessTime = measureTime([&]() {
            for (int i = 0; i < 1000; ++i) {
                volatile int val = vec[middle];  // volatile prevents optimization
                (void)val;  // Suppress unused variable warning
            }
        });

        std::cout << "  Vector: " << vecAccessTime << " microseconds\n";
        std::cout << "  List: N/A (no random access support)\n\n";

        std::cout << "Key Takeaway:\n";
        std::cout << "  - Use vector for: random access, back insertion, most use cases\n";
        std::cout << "  - Use list for: frequent front insertion/deletion, no random access needed\n\n";
    }
}

// =============================================================================
// PROBLEM SET 2: ASSOCIATIVE CONTAINERS
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 2.1: Word Frequency Counter
// -----------------------------------------------------------------------------
namespace problem_2_1 {
    void demonstrate() {
        std::cout << "=== Problem 2.1: Word Frequency Counter ===\n\n";

        // Create a map to count word frequencies
        std::map<std::string, int> wordCount;

        // Sample words (in real program, read from user input)
        std::vector<std::string> words = {
            "apple", "banana", "apple", "cherry", "banana",
            "apple", "date", "cherry", "apple", "banana"
        };

        std::cout << "Processing words: ";
        for (const auto& word : words) {
            std::cout << word << " ";
            wordCount[word]++;  // Increment count (initializes to 0 if not present)
        }
        std::cout << "\n\n";

        // Display all words and their counts (automatically sorted alphabetically)
        std::cout << "Word frequencies:\n";
        for (const auto& pair : wordCount) {
            std::cout << "  " << pair.first << ": " << pair.second << "\n";
        }

        // Find the most frequent word
        auto maxElement = std::max_element(
            wordCount.begin(),
            wordCount.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            }
        );

        std::cout << "\nMost frequent word: " << maxElement->first
                  << " (" << maxElement->second << " times)\n\n";

        // Demonstrate safe access with find()
        std::string searchWord = "elderberry";
        auto it = wordCount.find(searchWord);
        if (it != wordCount.end()) {
            std::cout << searchWord << " appears " << it->second << " times\n";
        } else {
            std::cout << searchWord << " not found in word list\n";
        }

        std::cout << "\n";
    }
}

// -----------------------------------------------------------------------------
// Problem 2.2: Set Operations
// -----------------------------------------------------------------------------
namespace problem_2_2 {
    // Union: elements in either set
    std::set<int> setUnion(const std::set<int>& set1, const std::set<int>& set2) {
        std::set<int> result;
        std::set_union(
            set1.begin(), set1.end(),
            set2.begin(), set2.end(),
            std::inserter(result, result.begin())
        );
        return result;
    }

    // Intersection: elements in both sets
    std::set<int> setIntersection(const std::set<int>& set1, const std::set<int>& set2) {
        std::set<int> result;
        std::set_intersection(
            set1.begin(), set1.end(),
            set2.begin(), set2.end(),
            std::inserter(result, result.begin())
        );
        return result;
    }

    // Difference: elements in first set but not second
    std::set<int> setDifference(const std::set<int>& set1, const std::set<int>& set2) {
        std::set<int> result;
        std::set_difference(
            set1.begin(), set1.end(),
            set2.begin(), set2.end(),
            std::inserter(result, result.begin())
        );
        return result;
    }

    // Helper to print a set
    void printSet(const std::string& name, const std::set<int>& s) {
        std::cout << name << ": {";
        bool first = true;
        for (int val : s) {
            if (!first) std::cout << ", ";
            std::cout << val;
            first = false;
        }
        std::cout << "}\n";
    }

    void demonstrate() {
        std::cout << "=== Problem 2.2: Set Operations ===\n\n";

        std::set<int> set1 = {1, 2, 3, 4, 5};
        std::set<int> set2 = {3, 4, 5, 6, 7};

        printSet("Set 1", set1);
        printSet("Set 2", set2);
        std::cout << "\n";

        // Union
        std::set<int> unionSet = setUnion(set1, set2);
        printSet("Union", unionSet);

        // Intersection
        std::set<int> intersectionSet = setIntersection(set1, set2);
        printSet("Intersection", intersectionSet);

        // Difference
        std::set<int> differenceSet = setDifference(set1, set2);
        printSet("Difference (Set1 - Set2)", differenceSet);

        std::cout << "\nSet properties:\n";
        std::cout << "  - Automatically sorted\n";
        std::cout << "  - No duplicates allowed\n";
        std::cout << "  - Fast lookup (O(log n))\n\n";
    }
}

// -----------------------------------------------------------------------------
// Problem 2.3: Student Database
// -----------------------------------------------------------------------------
namespace problem_2_3 {
    class StudentDatabase {
    private:
        std::map<int, std::string> idToName;      // ID -> Name
        std::map<std::string, double> nameToGPA;  // Name -> GPA
        std::set<std::string> honorRoll;          // Honor roll students

        const double HONOR_ROLL_THRESHOLD = 3.5;

    public:
        // Add a student with ID, name, and GPA
        void addStudent(int id, const std::string& name, double gpa) {
            idToName[id] = name;
            nameToGPA[name] = gpa;

            if (gpa >= HONOR_ROLL_THRESHOLD) {
                honorRoll.insert(name);
            }

            std::cout << "Added: " << name << " (ID: " << id << ", GPA: "
                      << std::fixed << std::setprecision(2) << gpa << ")\n";
        }

        // Find student's GPA by ID
        bool findGPAByID(int id, double& gpa) const {
            auto nameIt = idToName.find(id);
            if (nameIt == idToName.end()) {
                return false;
            }

            auto gpaIt = nameToGPA.find(nameIt->second);
            if (gpaIt == nameToGPA.end()) {
                return false;
            }

            gpa = gpaIt->second;
            return true;
        }

        // List all honor roll students
        void listHonorRoll() const {
            std::cout << "\nHonor Roll Students (GPA >= " << HONOR_ROLL_THRESHOLD << "):\n";
            if (honorRoll.empty()) {
                std::cout << "  (none)\n";
            } else {
                for (const auto& name : honorRoll) {
                    std::cout << "  - " << name << " (GPA: "
                              << std::fixed << std::setprecision(2)
                              << nameToGPA.at(name) << ")\n";
                }
            }
        }

        // Display all students
        void displayAllStudents() const {
            std::cout << "\nAll Students:\n";
            for (const auto& pair : idToName) {
                int id = pair.first;
                std::string name = pair.second;
                double gpa = nameToGPA.at(name);
                std::cout << "  ID: " << id << " | " << name << " | GPA: "
                          << std::fixed << std::setprecision(2) << gpa << "\n";
            }
        }
    };

    void demonstrate() {
        std::cout << "=== Problem 2.3: Student Database ===\n\n";

        StudentDatabase db;

        // Add students
        db.addStudent(1001, "Alice Johnson", 3.8);
        db.addStudent(1002, "Bob Smith", 3.2);
        db.addStudent(1003, "Charlie Davis", 3.9);
        db.addStudent(1004, "Diana Wilson", 3.4);
        db.addStudent(1005, "Eve Martinez", 3.7);

        // Display all students
        db.displayAllStudents();

        // Find GPA by ID
        std::cout << "\nLooking up student by ID:\n";
        int searchId = 1003;
        double gpa;
        if (db.findGPAByID(searchId, gpa)) {
            std::cout << "  Student ID " << searchId << " has GPA: "
                      << std::fixed << std::setprecision(2) << gpa << "\n";
        } else {
            std::cout << "  Student ID " << searchId << " not found\n";
        }

        // List honor roll
        db.listHonorRoll();

        std::cout << "\n";
    }
}

// =============================================================================
// PROBLEM SET 3: UNORDERED CONTAINERS AND INTEGRATION
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 3.1: Hash Performance Comparison
// -----------------------------------------------------------------------------
namespace problem_3_1 {
    void demonstrate() {
        std::cout << "=== Problem 3.1: Hash Performance Comparison ===\n\n";

        const int ELEMENTS = 100000;
        const int LOOKUPS = 10000;

        std::map<int, int> orderedMap;
        std::unordered_map<int, int> unorderedMap;

        // Generate random numbers for testing
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000000);

        std::vector<int> testData;
        for (int i = 0; i < ELEMENTS; ++i) {
            testData.push_back(dis(gen));
        }

        // Measure insertion time for ordered map
        auto start = std::chrono::high_resolution_clock::now();
        for (int val : testData) {
            orderedMap[val] = val * 2;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto orderedInsertTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Measure insertion time for unordered map
        start = std::chrono::high_resolution_clock::now();
        for (int val : testData) {
            unorderedMap[val] = val * 2;
        }
        end = std::chrono::high_resolution_clock::now();
        auto unorderedInsertTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "Insertion of " << ELEMENTS << " elements:\n";
        std::cout << "  std::map: " << orderedInsertTime << " ms\n";
        std::cout << "  std::unordered_map: " << unorderedInsertTime << " ms\n";
        std::cout << "  Speedup: " << (double)orderedInsertTime / unorderedInsertTime << "x\n\n";

        // Generate lookup keys
        std::vector<int> lookupKeys;
        for (int i = 0; i < LOOKUPS; ++i) {
            lookupKeys.push_back(testData[dis(gen) % testData.size()]);
        }

        // Measure lookup time for ordered map
        start = std::chrono::high_resolution_clock::now();
        for (int key : lookupKeys) {
            volatile auto it = orderedMap.find(key);
            (void)it;  // Suppress unused variable warning
        }
        end = std::chrono::high_resolution_clock::now();
        auto orderedLookupTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Measure lookup time for unordered map
        start = std::chrono::high_resolution_clock::now();
        for (int key : lookupKeys) {
            volatile auto it = unorderedMap.find(key);
            (void)it;  // Suppress unused variable warning
        }
        end = std::chrono::high_resolution_clock::now();
        auto unorderedLookupTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "Lookup of " << LOOKUPS << " elements:\n";
        std::cout << "  std::map: " << orderedLookupTime << " microseconds\n";
        std::cout << "  std::unordered_map: " << unorderedLookupTime << " microseconds\n";
        std::cout << "  Speedup: " << (double)orderedLookupTime / unorderedLookupTime << "x\n\n";

        std::cout << "Conclusion:\n";
        std::cout << "  - unordered_map is faster for large datasets\n";
        std::cout << "  - Use map when you need sorted order\n";
        std::cout << "  - Use unordered_map for raw performance\n\n";
    }
}

// -----------------------------------------------------------------------------
// Problem 3.2: Custom Hash Function
// -----------------------------------------------------------------------------
namespace problem_3_2 {
    struct Student {
        std::string name;
        int id;
        std::string major;

        // Equality operator required for unordered_set
        bool operator==(const Student& other) const {
            return id == other.id;  // Two students are equal if IDs match
        }
    };

    // Custom hash function
    struct StudentHash {
        std::size_t operator()(const Student& s) const {
            // Combine hash of ID and name
            // This is a simple hash combination technique
            std::size_t h1 = std::hash<int>{}(s.id);
            std::size_t h2 = std::hash<std::string>{}(s.name);
            return h1 ^ (h2 << 1);  // XOR and bit shift for combination
        }
    };

    void demonstrate() {
        std::cout << "=== Problem 3.2: Custom Hash Function ===\n\n";

        // Create unordered_set with custom hash function
        std::unordered_set<Student, StudentHash> students;

        // Add students
        students.insert({"Alice Johnson", 1001, "Computer Science"});
        students.insert({"Bob Smith", 1002, "Mathematics"});
        students.insert({"Charlie Davis", 1003, "Physics"});
        students.insert({"Alice Johnson", 1001, "Engineering"});  // Duplicate ID - won't be added
        students.insert({"Alice Johnson", 1004, "Engineering"});  // Same name, different ID - will be added

        std::cout << "Students in set: " << students.size() << "\n\n";

        std::cout << "All unique students:\n";
        for (const auto& student : students) {
            std::cout << "  ID: " << student.id << " | " << student.name
                      << " | " << student.major << "\n";
        }

        std::cout << "\nKey points:\n";
        std::cout << "  - Custom hash function combines multiple fields\n";
        std::cout << "  - Equality operator determines uniqueness\n";
        std::cout << "  - Hash function should distribute values evenly\n\n";
    }
}

// -----------------------------------------------------------------------------
// Problem 3.3: Library Management System (Integration Project)
// -----------------------------------------------------------------------------
namespace problem_3_3 {
    struct Book {
        std::string title;
        std::string author;
        std::string category;
        bool isAvailable = true;
    };

    class LibraryManagementSystem {
    private:
        std::map<std::string, Book> books;                    // ISBN -> Book
        std::unordered_set<std::string> authors;              // Unique authors
        std::set<std::string> categories;                     // Categories (sorted)
        std::unordered_map<std::string, std::string> checkedOut;  // ISBN -> Borrower

    public:
        // Add a new book
        void addBook(const std::string& isbn, const std::string& title,
                     const std::string& author, const std::string& category) {
            Book book{title, author, category, true};
            books[isbn] = book;
            authors.insert(author);
            categories.insert(category);

            std::cout << "Added book: " << title << " by " << author << "\n";
        }

        // Check out a book
        bool checkOutBook(const std::string& isbn, const std::string& borrower) {
            auto it = books.find(isbn);
            if (it == books.end()) {
                std::cout << "Book not found: " << isbn << "\n";
                return false;
            }

            if (!it->second.isAvailable) {
                std::cout << "Book already checked out: " << it->second.title << "\n";
                return false;
            }

            it->second.isAvailable = false;
            checkedOut[isbn] = borrower;
            std::cout << "Checked out: " << it->second.title << " to " << borrower << "\n";
            return true;
        }

        // Return a book
        bool returnBook(const std::string& isbn) {
            auto it = books.find(isbn);
            if (it == books.end()) {
                std::cout << "Book not found: " << isbn << "\n";
                return false;
            }

            if (it->second.isAvailable) {
                std::cout << "Book was not checked out: " << it->second.title << "\n";
                return false;
            }

            it->second.isAvailable = true;
            checkedOut.erase(isbn);
            std::cout << "Returned: " << it->second.title << "\n";
            return true;
        }

        // Find books by author
        std::vector<Book> findBooksByAuthor(const std::string& author) const {
            std::vector<Book> result;
            for (const auto& pair : books) {
                if (pair.second.author == author) {
                    result.push_back(pair.second);
                }
            }
            return result;
        }

        // List all categories
        void listCategories() const {
            std::cout << "\nBook Categories (" << categories.size() << "):\n";
            for (const auto& category : categories) {
                std::cout << "  - " << category << "\n";
            }
        }

        // Show checked out books
        void showCheckedOutBooks() const {
            std::cout << "\nCurrently Checked Out (" << checkedOut.size() << " books):\n";
            if (checkedOut.empty()) {
                std::cout << "  (none)\n";
            } else {
                for (const auto& pair : checkedOut) {
                    const auto& book = books.at(pair.first);
                    std::cout << "  - " << book.title << " (borrowed by "
                              << pair.second << ")\n";
                }
            }
        }

        // Display all books
        void displayAllBooks() const {
            std::cout << "\nLibrary Catalog (" << books.size() << " books):\n";
            for (const auto& pair : books) {
                const Book& book = pair.second;
                std::cout << "  ISBN: " << pair.first << "\n";
                std::cout << "    Title: " << book.title << "\n";
                std::cout << "    Author: " << book.author << "\n";
                std::cout << "    Category: " << book.category << "\n";
                std::cout << "    Status: " << (book.isAvailable ? "Available" : "Checked Out") << "\n\n";
            }
        }
    };

    void demonstrate() {
        std::cout << "=== Problem 3.3: Library Management System ===\n\n";

        LibraryManagementSystem library;

        // Add books
        std::cout << "Adding books to library:\n";
        library.addBook("978-0134685991", "Effective Modern C++", "Scott Meyers", "Programming");
        library.addBook("978-0321334879", "Effective C++", "Scott Meyers", "Programming");
        library.addBook("978-0596809485", "The C++ Programming Language", "Bjarne Stroustrup", "Programming");
        library.addBook("978-0201633610", "Design Patterns", "Gang of Four", "Software Engineering");
        library.addBook("978-0132350884", "Clean Code", "Robert Martin", "Software Engineering");
        std::cout << "\n";

        // Display all books
        library.displayAllBooks();

        // List categories (automatically sorted)
        library.listCategories();

        // Check out some books
        std::cout << "\nChecking out books:\n";
        library.checkOutBook("978-0134685991", "Alice Johnson");
        library.checkOutBook("978-0596809485", "Bob Smith");
        std::cout << "\n";

        // Show checked out books
        library.showCheckedOutBooks();

        // Try to check out already borrowed book
        std::cout << "\nTrying to check out already borrowed book:\n";
        library.checkOutBook("978-0134685991", "Charlie Davis");

        // Return a book
        std::cout << "\nReturning book:\n";
        library.returnBook("978-0134685991");

        // Show checked out books again
        library.showCheckedOutBooks();

        // Find books by author
        std::cout << "\nBooks by Scott Meyers:\n";
        auto meyersBooks = library.findBooksByAuthor("Scott Meyers");
        for (const auto& book : meyersBooks) {
            std::cout << "  - " << book.title << "\n";
        }

        std::cout << "\n";
    }
}

// =============================================================================
// DEBUGGING CHALLENGES
// =============================================================================

namespace debugging_challenges {
    void challenge1_bug() {
        std::cout << "=== Challenge 1: Iterator Invalidation Bug ===\n\n";
        std::cout << "BUGGY CODE:\n";
        std::cout << "std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};\n";
        std::cout << "for (auto it = numbers.begin(); it != numbers.end(); ++it) {\n";
        std::cout << "    if (*it % 2 == 0) {\n";
        std::cout << "        numbers.erase(it);  // BUG: Iterator invalidated!\n";
        std::cout << "    }\n";
        std::cout << "}\n\n";

        std::cout << "PROBLEM:\n";
        std::cout << "  - erase() invalidates the iterator\n";
        std::cout << "  - Incrementing invalidated iterator causes undefined behavior\n\n";
    }

    void challenge1_fixed() {
        std::cout << "FIXED CODE:\n";
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        std::cout << "Original: ";
        for (int n : numbers) std::cout << n << " ";
        std::cout << "\n";

        // Solution: Use the iterator returned by erase()
        for (auto it = numbers.begin(); it != numbers.end(); /* no increment */) {
            if (*it % 2 == 0) {
                it = numbers.erase(it);  // erase() returns iterator to next element
            } else {
                ++it;  // Only increment if we didn't erase
            }
        }

        std::cout << "After removing even numbers: ";
        for (int n : numbers) std::cout << n << " ";
        std::cout << "\n\n";

        std::cout << "FIX: Use iterator returned by erase()\n\n";
    }

    void challenge2_bug() {
        std::cout << "=== Challenge 2: Map Access Bug ===\n\n";
        std::cout << "BUGGY CODE:\n";
        std::cout << "std::map<std::string, int> scores;\n";
        std::cout << "// ... add some scores\n";
        std::cout << "std::string name = \"John\";\n";
        std::cout << "if (scores[name] > 0) {  // BUG: Creates entry if not present!\n";
        std::cout << "    std::cout << name << \" has a positive score\\n\";\n";
        std::cout << "}\n\n";

        std::cout << "PROBLEM:\n";
        std::cout << "  - operator[] creates a new entry if key doesn't exist\n";
        std::cout << "  - Default-initializes value (0 for int)\n";
        std::cout << "  - Changes map unintentionally\n\n";
    }

    void challenge2_fixed() {
        std::cout << "FIXED CODE:\n";
        std::map<std::string, int> scores;
        scores["Alice"] = 95;
        scores["Bob"] = 87;

        std::string name = "John";

        std::cout << "Before check - map size: " << scores.size() << "\n";

        // Solution: Use find() instead of operator[]
        auto it = scores.find(name);
        if (it != scores.end() && it->second > 0) {
            std::cout << name << " has a positive score: " << it->second << "\n";
        } else {
            std::cout << name << " not found or has non-positive score\n";
        }

        std::cout << "After check - map size: " << scores.size() << "\n";
        std::cout << "  (size unchanged because we used find())\n\n";

        std::cout << "FIX: Use find() for safe lookup without modification\n\n";
    }

    void demonstrate() {
        challenge1_bug();
        challenge1_fixed();
        challenge2_bug();
        challenge2_fixed();
    }
}

// =============================================================================
// MAIN FUNCTION - RUN ALL DEMONSTRATIONS
// =============================================================================

int main() {
    std::cout << "===============================================\n";
    std::cout << "  CHAPTER 13: STL CONTAINERS - HOMEWORK HINTS\n";
    std::cout << "===============================================\n\n";

    // Problem Set 1
    std::cout << "\n********** PROBLEM SET 1 **********\n\n";
    problem_1_1::demonstrate();
    problem_1_2::demonstrate();
    problem_1_3::demonstrate();

    // Problem Set 2
    std::cout << "\n********** PROBLEM SET 2 **********\n\n";
    problem_2_1::demonstrate();
    problem_2_2::demonstrate();
    problem_2_3::demonstrate();

    // Problem Set 3
    std::cout << "\n********** PROBLEM SET 3 **********\n\n";
    problem_3_1::demonstrate();
    problem_3_2::demonstrate();
    problem_3_3::demonstrate();

    // Debugging Challenges
    std::cout << "\n********** DEBUGGING CHALLENGES **********\n\n";
    debugging_challenges::demonstrate();

    std::cout << "===============================================\n";
    std::cout << "  All demonstrations complete!\n";
    std::cout << "===============================================\n";

    return 0;
}

/*
===============================================================================
KEY LEARNING POINTS
===============================================================================

1. SEQUENCE CONTAINERS:
   - vector: Dynamic array, fast random access, use for most cases
   - list: Doubly-linked list, fast insertion/deletion at any position
   - deque: Double-ended queue, fast insertion/deletion at both ends

2. ASSOCIATIVE CONTAINERS:
   - map: Sorted key-value pairs, O(log n) lookup
   - set: Sorted unique elements, O(log n) operations
   - Use when you need sorted order

3. UNORDERED CONTAINERS:
   - unordered_map: Hash table for key-value pairs, O(1) average lookup
   - unordered_set: Hash table for unique elements, O(1) average operations
   - Use for maximum performance when order doesn't matter

4. CONTAINER SELECTION GUIDE:
   - Need random access? -> vector
   - Frequent insertion at front? -> list or deque
   - Key-value lookup with order? -> map
   - Key-value lookup, maximum speed? -> unordered_map
   - Unique elements with order? -> set
   - Unique elements, maximum speed? -> unordered_set

5. COMMON PITFALLS:
   - Iterator invalidation after erase()
   - Using operator[] on map creates entries
   - Forgetting to include <algorithm> for algorithms
   - Not using const& for large objects in range-for loops

6. BEST PRACTICES:
   - Use range-based for loops when you don't need iterators
   - Use const& for read-only access
   - Use emplace() instead of push() for efficiency
   - Reserve space with reserve() when size is known
   - Use at() for bounds-checked access
   - Use find() instead of operator[] for safe map lookup

7. PYTHON EQUIVALENTS:
   - std::vector ~ list
   - std::map ~ dict (but sorted)
   - std::unordered_map ~ dict
   - std::set ~ set (but sorted)
   - std::unordered_set ~ set

===============================================================================
COMPILATION:
===============================================================================
g++ -std=c++17 -Wall -Wextra -g -o containers_hints containers_hints.cpp
./containers_hints

Or in VS Code: Ctrl+Shift+B (Cmd+Shift+B on macOS)
===============================================================================
*/
