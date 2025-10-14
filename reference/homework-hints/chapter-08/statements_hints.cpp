#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <sstream>

// =============================================================================
// PROBLEM SET 1: CONTROL FLOW FUNDAMENTALS
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 1.1: Grade Calculator with Switch Statement
// -----------------------------------------------------------------------------

void problem_1_1_grade_calculator() {
    std::cout << "\n=== Problem 1.1: Grade Calculator ===\n";

    std::cout << "Enter numeric grade (0-100): ";
    int grade;
    std::cin >> grade;

    // Validate input
    if (grade < 0 || grade > 100) {
        std::cout << "Error: Grade must be between 0 and 100\n";
        return;
    }

    // Convert to letter grade using switch
    // Key insight: switch works on discrete values, so we divide by 10
    char letter_grade;
    switch (grade / 10) {
        case 10:  // 100
        case 9:   // 90-99
            letter_grade = 'A';
            break;
        case 8:   // 80-89
            letter_grade = 'B';
            break;
        case 7:   // 70-79
            letter_grade = 'C';
            break;
        case 6:   // 60-69
            letter_grade = 'D';
            break;
        default:  // 0-59
            letter_grade = 'F';
            break;
    }

    std::cout << "Grade: " << letter_grade << "\n";
}

// -----------------------------------------------------------------------------
// Problem 1.2: Number Pattern Generator
// -----------------------------------------------------------------------------

void problem_1_2_pattern_generator() {
    std::cout << "\n=== Problem 1.2: Number Pattern Generator ===\n";

    int size;
    char mode;

    std::cout << "Enter pattern size (1-10): ";
    std::cin >> size;

    // Validate size
    if (size < 1 || size > 10) {
        std::cout << "Error: Size must be between 1 and 10\n";
        return;
    }

    std::cout << "Show all rows (a) or odd rows only (o)? ";
    std::cin >> mode;

    // Validate mode
    if (mode != 'a' && mode != 'o') {
        std::cout << "Error: Mode must be 'a' or 'o'\n";
        return;
    }

    // Generate pattern
    for (int row = 1; row <= size; row++) {
        // Skip even rows in odd-only mode
        if (mode == 'o' && row % 2 == 0) {
            continue;  // Skip to next iteration
        }

        // Print numbers from 1 to row
        for (int num = 1; num <= row; num++) {
            std::cout << num;
        }
        std::cout << "\n";
    }
}

// -----------------------------------------------------------------------------
// Problem 1.3: Range-Based For Loop with Containers
// -----------------------------------------------------------------------------

void problem_1_3_range_based_loops() {
    std::cout << "\n=== Problem 1.3: Range-Based For Loops ===\n";

    std::vector<double> temperatures = {68.5, 72.1, 69.8, 74.2, 71.5, 73.0, 70.2};

    // Display all temperatures using range-based for loop
    std::cout << "Original temperatures: ";
    for (const auto& temp : temperatures) {  // const auto& for read-only
        std::cout << temp << " ";
    }
    std::cout << "\n";

    // Calculate average
    double sum = 0.0;
    for (const auto& temp : temperatures) {
        sum += temp;
    }
    double average = sum / temperatures.size();
    std::cout << "Average temperature: " << average << "\n";

    // Count temperatures above average
    int above_average = 0;
    for (const auto& temp : temperatures) {
        if (temp > average) {
            above_average++;
        }
    }
    std::cout << "Temperatures above average: " << above_average << "\n";

    // Modify all temperatures by adding 2.0 degrees
    // Use auto& (not const auto&) to allow modification
    for (auto& temp : temperatures) {
        temp += 2.0;
    }

    // Display modified temperatures
    std::cout << "Modified temperatures (+2.0): ";
    for (const auto& temp : temperatures) {
        std::cout << temp << " ";
    }
    std::cout << "\n";
}

// =============================================================================
// PROBLEM SET 2: EXCEPTION HANDLING & RAII
// =============================================================================

// -----------------------------------------------------------------------------
// Problem 2.1: Safe Division Calculator
// -----------------------------------------------------------------------------

// Safe divide function with exception throwing
double safe_divide(double numerator, double denominator) {
    if (denominator == 0.0) {
        throw std::runtime_error("Division by zero is not allowed");
    }
    return numerator / denominator;
}

void problem_2_1_exception_handling() {
    std::cout << "\n=== Problem 2.1: Safe Division Calculator ===\n";
    std::cout << "Enter calculations (a op b) or 'q' to quit\n";
    std::cout << "Example: 10 / 2\n";

    double a, b;
    char operation;

    while (true) {
        std::cout << "\nEnter calculation: ";

        // Try to read input
        if (!(std::cin >> a >> operation >> b)) {
            // Check if we hit EOF or 'q' was entered
            if (std::cin.eof()) {
                break;
            }

            // Clear error flag and ignore bad input
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error: Invalid input format\n";
            continue;
        }

        try {
            double result;

            switch (operation) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = safe_divide(a, b);  // May throw exception
                    break;
                default:
                    throw std::invalid_argument("Invalid operation: " + std::string(1, operation));
            }

            std::cout << "Result: " << result << "\n";

        } catch (const std::runtime_error& e) {
            // Catch division by zero and other runtime errors
            std::cout << "Runtime Error: " << e.what() << "\n";
        } catch (const std::invalid_argument& e) {
            // Catch invalid operation errors
            std::cout << "Invalid Argument: " << e.what() << "\n";
        } catch (const std::exception& e) {
            // Catch any other standard exceptions
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

// -----------------------------------------------------------------------------
// Problem 2.2: File Processor with RAII
// -----------------------------------------------------------------------------

class FileProcessor {
private:
    std::ifstream file;
    std::string filename;

public:
    // Constructor - acquire resource (open file)
    FileProcessor(const std::string& fname) : filename(fname) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::cout << "[FileProcessor] File opened: " << filename << "\n";
    }

    // Destructor - release resource (close file)
    ~FileProcessor() {
        if (file.is_open()) {
            file.close();
            std::cout << "[FileProcessor] File closed: " << filename << "\n";
        }
    }

    // Delete copy constructor and assignment (RAII best practice)
    // Files should not be copied - only one object should manage the resource
    FileProcessor(const FileProcessor&) = delete;
    FileProcessor& operator=(const FileProcessor&) = delete;

    // Count lines in file
    int count_lines() {
        if (!file.is_open()) {
            throw std::runtime_error("File is not open");
        }

        int count = 0;
        std::string line;

        // Reset file position to beginning
        file.clear();
        file.seekg(0, std::ios::beg);

        while (std::getline(file, line)) {
            count++;
        }

        return count;
    }

    // Count words in file
    int count_words() {
        if (!file.is_open()) {
            throw std::runtime_error("File is not open");
        }

        int count = 0;
        std::string word;

        // Reset file position to beginning
        file.clear();
        file.seekg(0, std::ios::beg);

        while (file >> word) {
            count++;
        }

        return count;
    }

    // Count characters in file
    int count_characters() {
        if (!file.is_open()) {
            throw std::runtime_error("File is not open");
        }

        int count = 0;
        char ch;

        // Reset file position to beginning
        file.clear();
        file.seekg(0, std::ios::beg);

        while (file.get(ch)) {
            count++;
        }

        return count;
    }
};

// Test function that demonstrates RAII even with exceptions
void test_file_processing(const std::string& filename) {
    std::cout << "\n=== Problem 2.2: File Processing with RAII ===\n";

    try {
        // FileProcessor uses RAII - file will be closed automatically
        FileProcessor processor(filename);

        std::cout << "Lines: " << processor.count_lines() << "\n";
        std::cout << "Words: " << processor.count_words() << "\n";
        std::cout << "Characters: " << processor.count_characters() << "\n";

        // Simulate an exception
        if (processor.count_lines() > 100) {
            throw std::runtime_error("File too large!");
        }

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        // File is still properly closed due to RAII - destructor runs automatically
    }

    std::cout << "File processing complete (file automatically closed)\n";
}

// =============================================================================
// PROBLEM SET 3: ADVANCED INTEGRATION PROJECT
// =============================================================================

// -----------------------------------------------------------------------------
// Custom Exception Classes
// -----------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------
// Student Class
// -----------------------------------------------------------------------------

class Student {
private:
    int id;
    std::string name;
    std::vector<double> grades;

public:
    // Constructors
    Student(int student_id, const std::string& student_name)
        : id(student_id), name(student_name) {}

    // Getters
    int get_id() const { return id; }
    const std::string& get_name() const { return name; }
    const std::vector<double>& get_grades() const { return grades; }

    // Add grade with validation
    void add_grade(double grade) {
        if (grade < 0.0 || grade > 100.0) {
            throw InvalidGradeException("Grade must be between 0 and 100");
        }
        grades.push_back(grade);
    }

    // Calculate GPA (on 4.0 scale)
    double calculate_gpa() const {
        if (grades.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        for (const auto& grade : grades) {
            // Convert percentage to 4.0 scale
            // 90-100 = 4.0, 80-89 = 3.0, 70-79 = 2.0, 60-69 = 1.0, <60 = 0.0
            if (grade >= 90) sum += 4.0;
            else if (grade >= 80) sum += 3.0;
            else if (grade >= 70) sum += 2.0;
            else if (grade >= 60) sum += 1.0;
            else sum += 0.0;
        }

        return sum / grades.size();
    }

    // Display student information
    void display() const {
        std::cout << "ID: " << id << ", Name: " << name;
        std::cout << ", Grades: ";
        if (grades.empty()) {
            std::cout << "None";
        } else {
            for (size_t i = 0; i < grades.size(); i++) {
                std::cout << grades[i];
                if (i < grades.size() - 1) std::cout << ", ";
            }
        }
        std::cout << ", GPA: " << calculate_gpa() << "\n";
    }

    // Serialization for file I/O
    std::string to_string() const {
        std::ostringstream oss;
        oss << id << "," << name;
        for (const auto& grade : grades) {
            oss << "," << grade;
        }
        return oss.str();
    }

    // Deserialization from file
    static Student from_string(const std::string& str) {
        std::istringstream iss(str);
        std::string token;

        // Read ID
        std::getline(iss, token, ',');
        int id = std::stoi(token);

        // Read name
        std::string name;
        std::getline(iss, name, ',');

        Student student(id, name);

        // Read grades
        while (std::getline(iss, token, ',')) {
            double grade = std::stod(token);
            student.add_grade(grade);
        }

        return student;
    }
};

// -----------------------------------------------------------------------------
// RAII File Manager
// -----------------------------------------------------------------------------

class StudentFileManager {
private:
    std::string filename;

public:
    StudentFileManager(const std::string& fname) : filename(fname) {}

    // Save students to file using RAII
    void save_students(const std::vector<Student>& students) {
        // RAII: ofstream automatically closes when it goes out of scope
        std::ofstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for writing: " + filename);
        }

        for (const auto& student : students) {
            file << student.to_string() << "\n";
        }

        // File automatically closed here when 'file' goes out of scope
    }

    // Load students from file using RAII
    std::vector<Student> load_students() {
        std::vector<Student> students;

        // RAII: ifstream automatically closes when it goes out of scope
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for reading: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                try {
                    students.push_back(Student::from_string(line));
                } catch (const std::exception& e) {
                    std::cerr << "Warning: Skipping invalid line: " << e.what() << "\n";
                }
            }
        }

        // File automatically closed here when 'file' goes out of scope
        return students;
    }
};

// -----------------------------------------------------------------------------
// Student Management System
// -----------------------------------------------------------------------------

class StudentManagementSystem {
private:
    std::vector<Student> students;
    StudentFileManager file_manager;

public:
    StudentManagementSystem(const std::string& data_file)
        : file_manager(data_file) {
        try {
            students = file_manager.load_students();
            std::cout << "Loaded " << students.size() << " students from file.\n";
        } catch (const std::exception& e) {
            std::cout << "Warning: Could not load existing data: "
                      << e.what() << "\n";
            std::cout << "Starting with empty student list.\n";
        }
    }

    ~StudentManagementSystem() {
        try {
            file_manager.save_students(students);
            std::cout << "Saved " << students.size() << " students to file.\n";
        } catch (const std::exception& e) {
            std::cout << "Warning: Could not save data: "
                      << e.what() << "\n";
        }
    }

    void run() {
        int choice;

        do {
            display_menu();
            std::cout << "Enter choice: ";

            if (!(std::cin >> choice)) {
                // Handle invalid input
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input! Please enter a number.\n";
                continue;
            }

            std::cin.ignore(10000, '\n');  // Clear input buffer

            try {
                // Switch statement for menu handling
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
                        std::cout << "Goodbye!\n";
                        break;
                    default:
                        std::cout << "Invalid choice! Please try again.\n";
                }
            } catch (const StudentNotFoundException& e) {
                std::cout << "Student Error: " << e.what() << "\n";
            } catch (const InvalidGradeException& e) {
                std::cout << "Grade Error: " << e.what() << "\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }

        } while (choice != 0);
    }

private:
    void display_menu() {
        std::cout << "\n=== Student Management System ===\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Remove Student\n";
        std::cout << "3. Search Student\n";
        std::cout << "4. Display All Students\n";
        std::cout << "5. Add Grade to Student\n";
        std::cout << "0. Exit\n";
    }

    void add_student() {
        int id;
        std::string name;

        std::cout << "Enter student ID: ";
        std::cin >> id;
        std::cin.ignore(10000, '\n');

        // Check if ID already exists
        for (const auto& student : students) {
            if (student.get_id() == id) {
                throw std::invalid_argument("Student with ID " + std::to_string(id) + " already exists");
            }
        }

        std::cout << "Enter student name: ";
        std::getline(std::cin, name);

        students.push_back(Student(id, name));
        std::cout << "Student added successfully!\n";
    }

    void remove_student() {
        int id;
        std::cout << "Enter student ID to remove: ";
        std::cin >> id;

        // Find and remove student
        auto it = std::find_if(students.begin(), students.end(),
            [id](const Student& s) { return s.get_id() == id; });

        if (it != students.end()) {
            students.erase(it);
            std::cout << "Student removed successfully!\n";
        } else {
            throw StudentNotFoundException("Student with ID " + std::to_string(id) + " not found");
        }
    }

    void search_student() {
        int id;
        std::cout << "Enter student ID to search: ";
        std::cin >> id;

        Student* student = find_student_by_id(id);
        if (student) {
            student->display();
        } else {
            throw StudentNotFoundException("Student with ID " + std::to_string(id) + " not found");
        }
    }

    void display_all_students() {
        if (students.empty()) {
            std::cout << "No students in the system.\n";
            return;
        }

        std::cout << "\n=== All Students ===\n";
        // Use range-based for loop to iterate
        for (const auto& student : students) {
            student.display();
        }
    }

    void add_grade_to_student() {
        int id;
        double grade;

        std::cout << "Enter student ID: ";
        std::cin >> id;

        std::cout << "Enter grade (0-100): ";
        std::cin >> grade;

        Student* student = find_student_by_id(id);
        if (student) {
            student->add_grade(grade);  // May throw InvalidGradeException
            std::cout << "Grade added successfully!\n";
        } else {
            throw StudentNotFoundException("Student with ID " + std::to_string(id) + " not found");
        }
    }

    // Helper function to find student by ID
    Student* find_student_by_id(int id) {
        for (auto& student : students) {
            if (student.get_id() == id) {
                return &student;
            }
        }
        return nullptr;
    }
};

// =============================================================================
// MAIN FUNCTION - DEMONSTRATES ALL PROBLEMS
// =============================================================================

void create_sample_file() {
    std::ofstream file("sample.txt");
    file << "This is a sample file.\n";
    file << "It has multiple lines.\n";
    file << "We will use it to test file processing.\n";
    file.close();
}

int main() {
    std::cout << "=== Chapter 8: Statements - Homework Hints ===\n";
    std::cout << "This file demonstrates solutions to all problem sets.\n";

    int demo_choice;

    do {
        std::cout << "\n=== Select Demo ===\n";
        std::cout << "1. Problem 1.1: Grade Calculator\n";
        std::cout << "2. Problem 1.2: Pattern Generator\n";
        std::cout << "3. Problem 1.3: Range-Based Loops\n";
        std::cout << "4. Problem 2.1: Exception Handling\n";
        std::cout << "5. Problem 2.2: File Processing with RAII\n";
        std::cout << "6. Problem 3.1: Student Management System\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> demo_choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input!\n";
            continue;
        }

        std::cin.ignore(10000, '\n');

        switch (demo_choice) {
            case 1:
                problem_1_1_grade_calculator();
                break;
            case 2:
                problem_1_2_pattern_generator();
                break;
            case 3:
                problem_1_3_range_based_loops();
                break;
            case 4:
                problem_2_1_exception_handling();
                break;
            case 5:
                create_sample_file();
                test_file_processing("sample.txt");
                break;
            case 6: {
                StudentManagementSystem system("students_demo.txt");
                system.run();
                break;
            }
            case 0:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    } while (demo_choice != 0);

    return 0;
}

/*
=============================================================================
KEY LEARNING POINTS FROM CHAPTER 8
=============================================================================

1. CONTROL FLOW:
   - Switch statements are efficient for discrete values
   - Use break to prevent fall-through
   - Range-based for loops are cleaner than traditional loops
   - Use const auto& for read-only iteration, auto& for modification

2. EXCEPTION HANDLING:
   - Use standard exception types (std::runtime_error, std::invalid_argument)
   - Create custom exception classes for domain-specific errors
   - Multiple catch blocks handle different exception types
   - Catch by const reference: catch (const std::exception& e)
   - Order catch blocks from most specific to most general

3. RAII (Resource Acquisition Is Initialization):
   - Resources are acquired in constructor
   - Resources are released in destructor
   - Automatic cleanup even when exceptions occur
   - Delete copy constructor/assignment for unique resources
   - File streams use RAII automatically

4. BEST PRACTICES:
   - Validate all user input
   - Use exceptions for exceptional conditions, not control flow
   - Let RAII handle resource management
   - Use switch for menu systems and discrete value handling
   - Prefer range-based for loops for container iteration

5. COMMON PATTERNS:
   - Menu-driven applications with switch
   - Input validation loops with continue
   - Exception hierarchies for different error types
   - File I/O with automatic cleanup
   - Container iteration with range-based for

=============================================================================
COMPILATION AND RUNNING:
=============================================================================

To compile:
    g++ -std=c++17 -Wall -Wextra statements_hints.cpp -o statements_hints

To run:
    ./statements_hints

This demonstrates complete, working solutions for all Chapter 8 problems.
*/
