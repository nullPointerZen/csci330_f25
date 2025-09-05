# Chapter 8: Statements - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 8 "Statements"
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
**Prerequisites**: Chapters 1-7 completed + Chapter 8 lesson  

## Problem Set Structure

- **Problem Set 1**: Control Flow Fundamentals (45 minutes)
- **Problem Set 2**: Exception Handling & RAII (50 minutes) 
- **Problem Set 3**: Advanced Integration Project (40 minutes)

---

## Problem Set 1: Control Flow Fundamentals (45 minutes)

### Problem 1.1: Grade Calculator with Switch (15 minutes)

**Background**: Coming from Python dictionaries or Java if-else chains, learn C++ switch statements.

**Task**: Create a program that converts numeric grades to letter grades using a switch statement.

**Requirements**:
1. Read a numeric grade (0-100) from user input
2. Convert to letter grade using this scale:
   - 90-100: A
   - 80-89: B  
   - 70-79: C
   - 60-69: D
   - Below 60: F
3. Use a switch statement (not if-else)
4. Handle invalid input (negative numbers, > 100)

**Starter Code**:
```cpp
#include <iostream>

int main() {
    std::cout << "Enter numeric grade (0-100): ";
    int grade;
    std::cin >> grade;
    
    // TODO: Validate input
    // TODO: Convert to letter grade using switch
    // TODO: Print result
    
    return 0;
}
```

**Expected Output**:
```
Enter numeric grade (0-100): 87
Grade: B

Enter numeric grade (0-100): 105
Error: Grade must be between 0 and 100

Enter numeric grade (0-100): -5
Error: Grade must be between 0 and 100
```

**Learning Goals**:
- Switch statement syntax and break usage
- Input validation
- Range-based case grouping

---

### Problem 1.2: Number Pattern Generator (15 minutes)

**Background**: Practice nested loops and loop control (break/continue).

**Task**: Generate number patterns using nested for loops.

**Requirements**:
1. Ask user for pattern size (1-10)
2. Generate this pattern for size = 5:
```
1
12
123
1234
12345
```
3. Use nested for loops
4. Validate input range
5. Use continue to skip even-numbered rows if user chooses "odd only" mode

**Starter Code**:
```cpp
#include <iostream>

int main() {
    int size;
    char mode;
    
    std::cout << "Enter pattern size (1-10): ";
    std::cin >> size;
    
    std::cout << "Show all rows (a) or odd rows only (o)? ";
    std::cin >> mode;
    
    // TODO: Validate inputs
    // TODO: Generate pattern with nested loops
    // TODO: Use continue for odd-only mode
    
    return 0;
}
```

**Learning Goals**:
- Nested loop control
- Break and continue statements
- Input validation patterns

---

### Problem 1.3: Range-Based For Loop with Containers (15 minutes)  

**Background**: Transition from Python's for-in loops to C++ range-based for loops.

**Task**: Create a program that processes a list of temperatures.

**Requirements**:
1. Start with a vector of temperatures: `{68.5, 72.1, 69.8, 74.2, 71.5, 73.0, 70.2}`
2. Display all temperatures using range-based for loop
3. Find and display the average temperature
4. Count temperatures above average
5. Modify all temperatures by adding 2.0 degrees (using range-based for with references)

**Starter Code**:
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<double> temperatures = {68.5, 72.1, 69.8, 74.2, 71.5, 73.0, 70.2};
    
    // TODO: Display all temperatures
    // TODO: Calculate average
    // TODO: Count above average
    // TODO: Add 2.0 to all temperatures
    // TODO: Display modified temperatures
    
    return 0;
}
```

**Learning Goals**:
- Range-based for loops
- const auto& vs auto&
- Vector operations
- Accumulation patterns

---

## Problem Set 2: Exception Handling & RAII (50 minutes)

### Problem 2.1: Safe Division Calculator (20 minutes)

**Background**: Learn proper exception handling patterns, transitioning from Python's try/except or Java's try/catch.

**Task**: Create a calculator that safely handles division by zero and invalid input.

**Requirements**:
1. Create a `safe_divide` function that throws appropriate exceptions
2. Handle different types of exceptions with specific catch blocks
3. Use standard exception types (`std::invalid_argument`, `std::runtime_error`)
4. Implement a menu-driven calculator with exception handling

**Starter Code**:
```cpp
#include <iostream>
#include <stdexcept>

double safe_divide(double numerator, double denominator) {
    // TODO: Implement with proper exception throwing
}

int main() {
    double a, b;
    char operation;
    
    while (true) {
        std::cout << "Enter calculation (a op b) or 'q' to quit: ";
        
        if (!(std::cin >> a >> operation >> b)) {
            if (std::cin.eof()) break;
            // TODO: Handle invalid input
        }
        
        try {
            // TODO: Implement calculator with exception handling
        } catch (/* TODO: Add appropriate catch blocks */) {
            // TODO: Handle specific exceptions
        }
    }
    
    return 0;
}
```

**Expected Behavior**:
```
Enter calculation (a op b) or 'q' to quit: 10 / 2
Result: 5

Enter calculation (a op b) or 'q' to quit: 10 / 0
Error: Division by zero is not allowed

Enter calculation (a op b) or 'q' to quit: abc
Error: Invalid input format
```

**Learning Goals**:
- Exception throwing and catching
- Standard exception hierarchy
- Input validation with exceptions
- Multiple catch blocks

---

### Problem 2.2: File Processor with RAII (30 minutes)

**Background**: Learn RAII (Resource Acquisition Is Initialization) - a key C++ concept not present in Python/Java garbage collection.

**Task**: Create a file processing class that demonstrates RAII principles.

**Requirements**:
1. Create a `FileProcessor` class that opens a file in constructor
2. Implement RAII: file should auto-close in destructor
3. Add methods to count lines, words, and characters
4. Handle file-related exceptions properly
5. Demonstrate that files close even when exceptions occur

**Starter Code**:
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

class FileProcessor {
private:
    std::ifstream file;
    std::string filename;

public:
    // TODO: Constructor - acquire resource (open file)
    FileProcessor(const std::string& filename) {
        // TODO: Open file and handle errors
    }
    
    // TODO: Destructor - release resource (close file)
    ~FileProcessor() {
        // TODO: Ensure file is closed
    }
    
    // TODO: Delete copy constructor and assignment (RAII best practice)
    
    int count_lines() {
        // TODO: Count lines in file
        // TODO: Reset file position after counting
    }
    
    int count_words() {
        // TODO: Count words in file
    }
    
    int count_characters() {
        // TODO: Count characters in file
    }
};

// Test function that demonstrates RAII even with exceptions
void test_file_processing(const std::string& filename) {
    try {
        FileProcessor processor(filename);
        
        std::cout << "Lines: " << processor.count_lines() << std::endl;
        std::cout << "Words: " << processor.count_words() << std::endl;
        std::cout << "Characters: " << processor.count_characters() << std::endl;
        
        // Simulate an exception
        if (processor.count_lines() > 100) {
            throw std::runtime_error("File too large!");
        }
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        // File should still be properly closed due to RAII
    }
}

int main() {
    // TODO: Create a test file or use existing file
    // TODO: Test with valid and invalid filenames
    // TODO: Demonstrate RAII behavior
    
    return 0;
}
```

**Learning Goals**:
- RAII implementation
- Constructor/destructor patterns
- File stream handling
- Exception safety
- Resource management

---

## Problem Set 3: Advanced Integration Project (40 minutes)

### Problem 3.1: Student Management System (40 minutes)

**Background**: Integrate all Chapter 8 concepts into a comprehensive program that demonstrates control flow, exception handling, and RAII.

**Task**: Create a student management system with robust error handling.

**Requirements**:

**Core Features**:
1. Store student records (ID, name, grades)
2. Menu-driven interface with switch statement
3. Add, remove, search, and display students
4. Calculate GPA with exception handling
5. Save/load data from file using RAII

**Control Flow Requirements**:
- Use switch statement for menu system
- Use range-based for loops for processing collections
- Use traditional for loops where appropriate
- Implement input validation loops

**Exception Handling Requirements**:
- Custom exception classes for domain-specific errors
- File operation exceptions
- Input validation exceptions
- Graceful error recovery

**RAII Requirements**:
- Automatic file handling
- Proper resource cleanup
- Exception-safe operations

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>

// Custom exception classes
class StudentNotFoundException : public std::runtime_error {
public:
    StudentNotFoundException(const std::string& message)
        : std::runtime_error(message) {}
};

class InvalidGradeException : public std::invalid_argument {
public:
    InvalidGradeException(const std::string& message)
        : std::invalid_argument(message) {}
};

// Student class
class Student {
private:
    int id;
    std::string name;
    std::vector<double> grades;

public:
    // TODO: Implement constructors
    Student(int id, const std::string& name) : id(id), name(name) {}
    
    // TODO: Implement getters
    int get_id() const { return id; }
    const std::string& get_name() const { return name; }
    
    // TODO: Implement grade management with validation
    void add_grade(double grade) {
        // TODO: Validate grade (0-100)
        // TODO: Throw InvalidGradeException if invalid
    }
    
    double calculate_gpa() const {
        // TODO: Calculate GPA
        // TODO: Handle empty grades vector
    }
    
    // TODO: Implement display method
    void display() const;
};

// RAII File Manager
class StudentFileManager {
private:
    std::string filename;

public:
    StudentFileManager(const std::string& filename) : filename(filename) {}
    
    // TODO: Implement save_students with RAII file handling
    void save_students(const std::vector<Student>& students) {
        // TODO: Use RAII for file operations
        // TODO: Handle file exceptions
    }
    
    // TODO: Implement load_students with RAII file handling
    std::vector<Student> load_students() {
        // TODO: Use RAII for file operations
        // TODO: Handle file exceptions
        // TODO: Return loaded students
    }
};

// Main application class
class StudentManagementSystem {
private:
    std::vector<Student> students;
    StudentFileManager file_manager;

public:
    StudentManagementSystem(const std::string& data_file)
        : file_manager(data_file) {
        try {
            students = file_manager.load_students();
        } catch (const std::exception& e) {
            std::cout << "Warning: Could not load existing data: " 
                      << e.what() << std::endl;
        }
    }
    
    ~StudentManagementSystem() {
        try {
            file_manager.save_students(students);
        } catch (const std::exception& e) {
            std::cout << "Warning: Could not save data: " 
                      << e.what() << std::endl;
        }
    }
    
    void run() {
        int choice;
        
        do {
            display_menu();
            std::cout << "Enter choice: ";
            
            if (!(std::cin >> choice)) {
                // TODO: Handle invalid input
                continue;
            }
            
            try {
                switch (choice) {
                    case 1:
                        add_student();
                        break;
                    case 2:
                        remove_student();
                        break;
                    case 3:
                        search_student();
                        break;
                    case 4:
                        display_all_students();
                        break;
                    case 5:
                        add_grade_to_student();
                        break;
                    case 0:
                        std::cout << "Goodbye!" << std::endl;
                        break;
                    default:
                        std::cout << "Invalid choice!" << std::endl;
                }
            } catch (const StudentNotFoundException& e) {
                std::cout << "Student Error: " << e.what() << std::endl;
            } catch (const InvalidGradeException& e) {
                std::cout << "Grade Error: " << e.what() << std::endl;
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            
        } while (choice != 0);
    }

private:
    void display_menu() {
        std::cout << "\n=== Student Management System ===" << std::endl;
        std::cout << "1. Add Student" << std::endl;
        std::cout << "2. Remove Student" << std::endl;
        std::cout << "3. Search Student" << std::endl;
        std::cout << "4. Display All Students" << std::endl;
        std::cout << "5. Add Grade to Student" << std::endl;
        std::cout << "0. Exit" << std::endl;
    }
    
    // TODO: Implement menu functions
    void add_student();
    void remove_student();
    void search_student();
    void display_all_students();
    void add_grade_to_student();
    
    // TODO: Helper function to find student by ID
    Student* find_student_by_id(int id);
};

int main() {
    try {
        StudentManagementSystem system("students.txt");
        system.run();
    } catch (const std::exception& e) {
        std::cout << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```

**Expected Features**:
1. **Menu System**: Clean switch-based menu
2. **Data Validation**: All inputs validated with appropriate exceptions
3. **File Operations**: Automatic save/load with RAII
4. **Search Functionality**: Find students by ID with proper error handling
5. **Grade Management**: Add grades with validation
6. **Error Recovery**: System continues running after non-fatal errors

**Learning Goals**:
- Integration of all Chapter 8 concepts
- Custom exception hierarchies
- RAII in complex applications
- Menu-driven program architecture
- File I/O with exception safety
- Real-world error handling patterns

---

## Submission Guidelines

### What to Submit

1. **Source code files** for all problems
2. **Test output** showing your programs working
3. **Brief reflection** (2-3 paragraphs) comparing C++ control flow to Python/Java

### Evaluation Criteria

1. **Correctness** (40%): Programs work as specified
2. **Exception Safety** (25%): Proper exception handling and RAII
3. **Code Quality** (20%): Clean, readable, well-organized code
4. **Best Practices** (15%): Following C++ idioms and conventions

### Time Management Tips

- **Problem Set 1**: Focus on getting syntax right, don't over-engineer
- **Problem Set 2**: Take time to understand RAII - it's crucial for C++
- **Problem Set 3**: Start with basic functionality, add features incrementally

### Common Pitfalls to Avoid

1. **Forgetting `break`** in switch statements
2. **Not using RAII** for resource management
3. **Overusing exceptions** for normal control flow
4. **Forgetting `const auto&`** in range-based for loops
5. **Not handling all exception types**

### Getting Help

- Refer to `chapter_08_quick_help.md` for syntax reminders
- Check solution files if you're completely stuck
- Focus on understanding concepts, not just completing problems

---

## Extension Challenges (Optional)

For students who finish early:

1. **Smart Pointers**: Modify Problem 2.2 to use `std::unique_ptr` or `std::shared_ptr`
2. **Exception Specifications**: Add `noexcept` specifications where appropriate
3. **Performance**: Profile your loops and optimize hot paths
4. **Modern C++**: Use C++17/20 features like structured bindings or `if constexpr`

These extensions are not required but provide additional learning opportunities for advanced students.