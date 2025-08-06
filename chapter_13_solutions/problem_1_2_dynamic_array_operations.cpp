/*
 * Problem 1.2: Dynamic Array Operations - Student Roster Management
 * 
 * This solution demonstrates vector modification operations including
 * insertion, deletion, and searching using STL algorithms.
 * 
 * Similar to Python list operations like insert(), remove(), etc.
 */

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class StudentRoster {
private:
    std::vector<std::string> students;

public:
    // Add a student to the end (like Python: students.append(name))
    void addStudent(const std::string& name) {
        students.push_back(name);
        std::cout << "Added '" << name << "' to the roster.\n";
    }
    
    // Insert a student at a specific position (like Python: students.insert(pos, name))
    void insertStudent(const std::string& name, size_t position) {
        if (position > students.size()) {
            std::cout << "Invalid position " << position 
                      << ". Maximum position is " << students.size() << std::endl;
            return;
        }
        
        students.insert(students.begin() + position, name);
        std::cout << "Inserted '" << name << "' at position " << position << std::endl;
    }
    
    // Remove a student by name (like Python: students.remove(name))
    void removeStudent(const std::string& name) {
        // Use std::find to locate the student
        auto it = std::find(students.begin(), students.end(), name);
        
        if (it != students.end()) {
            // Calculate position before erasing (for user feedback)
            size_t position = std::distance(students.begin(), it);
            students.erase(it);
            std::cout << "Removed '" << name << "' from position " << position << std::endl;
        } else {
            std::cout << "Student '" << name << "' not found in roster." << std::endl;
        }
    }
    
    // Display all students with their positions
    void displayStudents() const {
        if (students.empty()) {
            std::cout << "No students in roster.\n";
            return;
        }
        
        std::cout << "\nCurrent Student Roster:\n";
        std::cout << "=======================\n";
        for (size_t i = 0; i < students.size(); ++i) {
            std::cout << "Position " << i << ": " << students[i] << std::endl;
        }
        std::cout << "Total students: " << students.size() << "\n\n";
    }
    
    // Bonus: Search for a student and return their position
    int findStudent(const std::string& name) const {
        auto it = std::find(students.begin(), students.end(), name);
        if (it != students.end()) {
            return static_cast<int>(std::distance(students.begin(), it));
        }
        return -1; // Not found
    }
    
    // Bonus: Check if roster is empty
    bool isEmpty() const {
        return students.empty();
    }
    
    // Bonus: Get number of students
    size_t getSize() const {
        return students.size();
    }
    
    // Bonus: Remove all students (like Python: students.clear())
    void clearRoster() {
        students.clear();
        std::cout << "Roster cleared.\n";
    }
};

// Demonstration function
void demonstrateRosterOperations() {
    StudentRoster roster;
    
    std::cout << "=== Student Roster Management System ===\n\n";
    
    // Test adding students
    std::cout << "1. Adding students:\n";
    roster.addStudent("Alice Johnson");
    roster.addStudent("Bob Smith");
    roster.addStudent("Charlie Brown");
    roster.displayStudents();
    
    // Test inserting at specific positions
    std::cout << "2. Inserting students at specific positions:\n";
    roster.insertStudent("Diana Prince", 1);  // Insert at position 1
    roster.insertStudent("Eve Wilson", 0);    // Insert at beginning
    roster.displayStudents();
    
    // Test finding students
    std::cout << "3. Finding students:\n";
    std::string searchName = "Bob Smith";
    int position = roster.findStudent(searchName);
    if (position != -1) {
        std::cout << "Found '" << searchName << "' at position " << position << std::endl;
    } else {
        std::cout << "'" << searchName << "' not found." << std::endl;
    }
    
    // Test removing students
    std::cout << "\n4. Removing students:\n";
    roster.removeStudent("Charlie Brown");  // Remove existing student
    roster.removeStudent("John Doe");       // Try to remove non-existing student
    roster.displayStudents();
    
    // Test edge cases
    std::cout << "5. Testing edge cases:\n";
    roster.insertStudent("Frank Miller", 100);  // Invalid position
    roster.insertStudent("Grace Lee", roster.getSize());  // Insert at end (valid)
    roster.displayStudents();
}

int main() {
    demonstrateRosterOperations();
    
    // Interactive demo (optional - uncomment to enable)
    /*
    StudentRoster roster;
    std::string command, name;
    size_t position;
    
    std::cout << "\nInteractive Mode (type 'help' for commands):\n";
    
    while (true) {
        std::cout << "\nEnter command: ";
        std::cin >> command;
        
        if (command == "help") {
            std::cout << "Commands: add, insert, remove, display, find, clear, quit\n";
        } else if (command == "add") {
            std::cout << "Enter name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            roster.addStudent(name);
        } else if (command == "insert") {
            std::cout << "Enter name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter position: ";
            std::cin >> position;
            roster.insertStudent(name, position);
        } else if (command == "remove") {
            std::cout << "Enter name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            roster.removeStudent(name);
        } else if (command == "display") {
            roster.displayStudents();
        } else if (command == "find") {
            std::cout << "Enter name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            int pos = roster.findStudent(name);
            if (pos != -1) {
                std::cout << "Found at position " << pos << std::endl;
            } else {
                std::cout << "Not found" << std::endl;
            }
        } else if (command == "clear") {
            roster.clearRoster();
        } else if (command == "quit") {
            break;
        } else {
            std::cout << "Unknown command. Type 'help' for available commands.\n";
        }
    }
    */
    
    return 0;
}

/*
 * Expected Output:
 * === Student Roster Management System ===
 * 
 * 1. Adding students:
 * Added 'Alice Johnson' to the roster.
 * Added 'Bob Smith' to the roster.
 * Added 'Charlie Brown' to the roster.
 * 
 * Current Student Roster:
 * =======================
 * Position 0: Alice Johnson
 * Position 1: Bob Smith
 * Position 2: Charlie Brown
 * Total students: 3
 * 
 * 2. Inserting students at specific positions:
 * Inserted 'Diana Prince' at position 1
 * Inserted 'Eve Wilson' at position 0
 * 
 * Current Student Roster:
 * =======================
 * Position 0: Eve Wilson
 * Position 1: Alice Johnson
 * Position 2: Diana Prince
 * Position 3: Bob Smith
 * Position 4: Charlie Brown
 * Total students: 5
 * 
 * 3. Finding students:
 * Found 'Bob Smith' at position 3
 * 
 * 4. Removing students:
 * Removed 'Charlie Brown' from position 4
 * Student 'John Doe' not found in roster.
 * 
 * Current Student Roster:
 * =======================
 * Position 0: Eve Wilson
 * Position 1: Alice Johnson
 * Position 2: Diana Prince
 * Position 3: Bob Smith
 * Total students: 4
 * 
 * 5. Testing edge cases:
 * Invalid position 100. Maximum position is 4
 * Inserted 'Grace Lee' at position 4
 * 
 * Current Student Roster:
 * =======================
 * Position 0: Eve Wilson
 * Position 1: Alice Johnson
 * Position 2: Diana Prince
 * Position 3: Bob Smith
 * Position 4: Grace Lee
 * Total students: 5
 * 
 * Learning Points:
 * 1. vector.insert() takes an iterator, not an index directly
 * 2. std::find returns an iterator to the found element or end() if not found
 * 3. std::distance calculates position from iterators
 * 4. Always validate positions before insertion
 * 5. erase() invalidates iterators, so use the returned value if continuing to iterate
 * 6. const methods allow calling on const objects
 */