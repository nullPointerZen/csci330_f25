/**
 * Problem 3.1: Student Management System
 * 
 * Demonstrates:
 * - Integration of all Chapter 8 concepts
 * - Custom exception hierarchies
 * - RAII in complex applications
 * - Menu-driven program architecture
 * - File I/O with exception safety
 * - Real-world error handling patterns
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <limits>
#include <sstream>

// Custom exception classes
class StudentNotFoundException : public std::runtime_error {
public:
    explicit StudentNotFoundException(const std::string& message)
        : std::runtime_error("Student not found: " + message) {}
};

class InvalidGradeException : public std::invalid_argument {
public:
    explicit InvalidGradeException(const std::string& message)
        : std::invalid_argument("Invalid grade: " + message) {}
};

class FileOperationException : public std::runtime_error {
public:
    explicit FileOperationException(const std::string& message)
        : std::runtime_error("File operation failed: " + message) {}
};

// Student class
class Student {
private:
    int id;
    std::string name;
    std::vector<double> grades;

public:
    // Constructor
    Student(int id, const std::string& name) : id(id), name(name) {
        if (id <= 0) {
            throw std::invalid_argument("Student ID must be positive");
        }
        if (name.empty()) {
            throw std::invalid_argument("Student name cannot be empty");
        }
    }
    
    // Getters
    int get_id() const { return id; }
    const std::string& get_name() const { return name; }
    const std::vector<double>& get_grades() const { return grades; }
    
    // Grade management with validation
    void add_grade(double grade) {
        if (grade < 0.0 || grade > 100.0) {
            throw InvalidGradeException("Grade must be between 0 and 100, got: " + std::to_string(grade));
        }
        grades.push_back(grade);
    }
    
    // Calculate GPA (assuming 4.0 scale)
    double calculate_gpa() const {
        if (grades.empty()) {
            return 0.0;  // No grades recorded
        }
        
        // Calculate average grade first
        double average = std::accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
        
        // Convert to 4.0 scale
        if (average >= 97) return 4.0;
        if (average >= 93) return 3.7;
        if (average >= 90) return 3.3;
        if (average >= 87) return 3.0;
        if (average >= 83) return 2.7;
        if (average >= 80) return 2.3;
        if (average >= 77) return 2.0;
        if (average >= 73) return 1.7;
        if (average >= 70) return 1.3;
        if (average >= 67) return 1.0;
        if (average >= 65) return 0.7;
        return 0.0;
    }
    
    // Display student information
    void display() const {
        std::cout << "ID: " << id << ", Name: " << name;
        
        if (!grades.empty()) {
            std::cout << ", Grades: ";
            for (size_t i = 0; i < grades.size(); ++i) {
                std::cout << grades[i];
                if (i < grades.size() - 1) std::cout << ", ";
            }
            std::cout << ", GPA: " << std::fixed << std::setprecision(2) << calculate_gpa();
        } else {
            std::cout << ", No grades recorded";
        }
        std::cout << std::endl;
    }
    
    // Serialization for file I/O
    std::string to_string() const {
        std::ostringstream oss;
        oss << id << "|" << name << "|";
        for (size_t i = 0; i < grades.size(); ++i) {
            oss << grades[i];
            if (i < grades.size() - 1) oss << ",";
        }
        return oss.str();
    }
    
    // Deserialization from file
    static Student from_string(const std::string& str) {
        std::istringstream iss(str);
        std::string token;
        
        // Parse ID
        if (!std::getline(iss, token, '|')) {
            throw std::invalid_argument("Invalid student data format");
        }
        int id = std::stoi(token);
        
        // Parse name
        if (!std::getline(iss, token, '|')) {
            throw std::invalid_argument("Invalid student data format");
        }
        std::string name = token;
        
        Student student(id, name);
        
        // Parse grades (optional)
        if (std::getline(iss, token, '|')) {
            std::istringstream grade_stream(token);
            std::string grade_str;
            
            while (std::getline(grade_stream, grade_str, ',')) {
                if (!grade_str.empty()) {
                    double grade = std::stod(grade_str);
                    student.add_grade(grade);
                }
            }
        }
        
        return student;
    }
};

// RAII File Manager
class StudentFileManager {
private:
    std::string filename;

public:
    explicit StudentFileManager(const std::string& filename) : filename(filename) {}
    
    // Save students with RAII file handling
    void save_students(const std::vector<Student>& students) {
        std::ofstream file(filename);  // RAII: opens file
        
        if (!file.is_open()) {
            throw FileOperationException("Cannot open file for writing: " + filename);
        }
        
        try {
            for (const auto& student : students) {
                file << student.to_string() << std::endl;
            }
            
            if (file.fail()) {
                throw FileOperationException("Error writing to file: " + filename);
            }
            
        } catch (...) {
            // File automatically closed by RAII, even if exception occurs
            throw;
        }
        
        // File automatically closed here due to RAII
    }
    
    // Load students with RAII file handling
    std::vector<Student> load_students() {
        std::ifstream file(filename);  // RAII: opens file
        
        if (!file.is_open()) {
            throw FileOperationException("Cannot open file for reading: " + filename);
        }
        
        std::vector<Student> students;
        std::string line;
        int line_number = 0;
        
        try {
            while (std::getline(file, line)) {
                ++line_number;
                
                if (!line.empty()) {
                    try {
                        students.push_back(Student::from_string(line));
                    } catch (const std::exception& e) {
                        throw FileOperationException("Error parsing line " + std::to_string(line_number) + ": " + e.what());
                    }
                }
            }
            
        } catch (...) {
            // File automatically closed by RAII, even if exception occurs
            throw;
        }
        
        return students;
        // File automatically closed here due to RAII
    }
};

// Main application class
class StudentManagementSystem {
private:
    std::vector<Student> students;
    StudentFileManager file_manager;

public:
    explicit StudentManagementSystem(const std::string& data_file)
        : file_manager(data_file) {
        try {
            students = file_manager.load_students();
            std::cout << "Loaded " << students.size() << " students from file." << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Warning: Could not load existing data: " 
                      << e.what() << std::endl;
            std::cout << "Starting with empty student database." << std::endl;
        }
    }
    
    ~StudentManagementSystem() {
        try {
            file_manager.save_students(students);
            std::cout << "Data saved successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Warning: Could not save data: " 
                      << e.what() << std::endl;
        }
    }
    
    void run() {
        int choice;
        
        std::cout << "\n=== Student Management System ===" << std::endl;
        
        do {
            display_menu();
            std::cout << "Enter choice: ";
            
            if (!(std::cin >> choice)) {
                std::cout << "Invalid input! Please enter a number." << std::endl;
                clear_input_buffer();
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
                    case 6:
                        save_data_manually();
                        break;
                    case 0:
                        std::cout << "Goodbye!" << std::endl;
                        break;
                    default:
                        std::cout << "Invalid choice! Please try again." << std::endl;
                }
            } catch (const StudentNotFoundException& e) {
                std::cout << "Student Error: " << e.what() << std::endl;
            } catch (const InvalidGradeException& e) {
                std::cout << "Grade Error: " << e.what() << std::endl;
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            
            if (choice != 0) {
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
            }
            
        } while (choice != 0);
    }

private:
    void display_menu() {
        std::cout << "\n=== Menu ===" << std::endl;
        std::cout << "1. Add Student" << std::endl;
        std::cout << "2. Remove Student" << std::endl;
        std::cout << "3. Search Student" << std::endl;
        std::cout << "4. Display All Students" << std::endl;
        std::cout << "5. Add Grade to Student" << std::endl;
        std::cout << "6. Save Data Now" << std::endl;
        std::cout << "0. Exit" << std::endl;
    }
    
    void clear_input_buffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    void add_student() {
        int id;
        std::string name;
        
        std::cout << "Enter student ID: ";
        if (!(std::cin >> id)) {
            throw std::invalid_argument("Invalid ID format");
        }
        
        // Check for duplicate ID
        if (find_student_by_id(id) != nullptr) {
            throw std::invalid_argument("Student with ID " + std::to_string(id) + " already exists");
        }
        
        std::cout << "Enter student name: ";
        clear_input_buffer();  // Clear buffer before getline
        std::getline(std::cin, name);
        
        students.emplace_back(id, name);
        std::cout << "Student added successfully!" << std::endl;
    }
    
    void remove_student() {
        int id;
        std::cout << "Enter student ID to remove: ";
        
        if (!(std::cin >> id)) {
            throw std::invalid_argument("Invalid ID format");
        }
        
        auto it = std::find_if(students.begin(), students.end(),
                              [id](const Student& s) { return s.get_id() == id; });
        
        if (it == students.end()) {
            throw StudentNotFoundException("ID " + std::to_string(id));
        }
        
        std::cout << "Removing student: ";
        it->display();
        students.erase(it);
        std::cout << "Student removed successfully!" << std::endl;
    }
    
    void search_student() {
        int id;
        std::cout << "Enter student ID to search: ";
        
        if (!(std::cin >> id)) {
            throw std::invalid_argument("Invalid ID format");
        }
        
        Student* student = find_student_by_id(id);
        if (student == nullptr) {
            throw StudentNotFoundException("ID " + std::to_string(id));
        }
        
        std::cout << "Student found:" << std::endl;
        student->display();
    }
    
    void display_all_students() {
        if (students.empty()) {
            std::cout << "No students in database." << std::endl;
            return;
        }
        
        std::cout << "All students (" << students.size() << " total):" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        
        for (const auto& student : students) {
            student.display();
        }
    }
    
    void add_grade_to_student() {
        int id;
        double grade;
        
        std::cout << "Enter student ID: ";
        if (!(std::cin >> id)) {
            throw std::invalid_argument("Invalid ID format");
        }
        
        Student* student = find_student_by_id(id);
        if (student == nullptr) {
            throw StudentNotFoundException("ID " + std::to_string(id));
        }
        
        std::cout << "Enter grade (0-100): ";
        if (!(std::cin >> grade)) {
            throw std::invalid_argument("Invalid grade format");
        }
        
        student->add_grade(grade);
        std::cout << "Grade added successfully!" << std::endl;
        std::cout << "Updated student info:" << std::endl;
        student->display();
    }
    
    void save_data_manually() {
        file_manager.save_students(students);
        std::cout << "Data saved to file successfully!" << std::endl;
    }
    
    // Helper function to find student by ID
    Student* find_student_by_id(int id) {
        auto it = std::find_if(students.begin(), students.end(),
                              [id](const Student& s) { return s.get_id() == id; });
        
        return (it != students.end()) ? &(*it) : nullptr;
    }
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