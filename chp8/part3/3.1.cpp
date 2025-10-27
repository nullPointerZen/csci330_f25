#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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
    Student(int id, const std::string& name) : id(id), name(name) {}

    int get_id() const { return id; }
    const std::string& get_name() const { return name; }

    void add_grade(double grade) {
        if (grade < 0.0 || grade > 100.0) {
            throw InvalidGradeException("Grade must be between 0 and 100.");
        }
        grades.push_back(grade);
    }

    double calculate_gpa() const {
        if (grades.empty()) {
            throw std::runtime_error("No grades available to calculate GPA.");
        }
        double sum = 0.0;
        for (double g : grades) sum += g;
        return sum / grades.size();
    }

    void display() const {
        std::cout << "ID: " << id << ", Name: " << name << ", Grades: ";
        for (double g : grades) std::cout << g << " ";
        try {
            std::cout << "| GPA: " << calculate_gpa();
        } catch (...) {
            std::cout << "| GPA: N/A";
        }
        std::cout << std::endl;
    }

    const std::vector<double>& get_grades() const { return grades; }
};

// RAII File Manager
class StudentFileManager {
private:
    std::string filename;

public:
    StudentFileManager(const std::string& filename) : filename(filename) {}

    void save_students(const std::vector<Student>& students) {
        std::ofstream out(filename);
        if (!out) throw std::runtime_error("Failed to open file for saving.");

        for (const Student& s : students) {
            out << s.get_id() << "," << s.get_name() << ",";
            for (double g : s.get_grades()) out << g << " ";
            out << "\n";
        }
    }

    std::vector<Student> load_students() {
        std::ifstream in(filename);
        if (!in) throw std::runtime_error("Failed to open file for loading.");

        std::vector<Student> loaded;
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream ss(line);
            std::string id_str, name, grades_str;
            if (!std::getline(ss, id_str, ',')) continue;
            if (!std::getline(ss, name, ',')) continue;
            std::getline(ss, grades_str);

            int id = std::stoi(id_str);
            Student s(id, name);
            std::istringstream gs(grades_str);
            double g;
            while (gs >> g) {
                try { s.add_grade(g); } catch (...) {}
            }
            loaded.push_back(s);
        }
        return loaded;
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
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            try {
                switch (choice) {
                    case 1: add_student(); break;
                    case 2: remove_student(); break;
                    case 3: search_student(); break;
                    case 4: display_all_students(); break;
                    case 5: add_grade_to_student(); break;
                    case 0: std::cout << "Goodbye!" << std::endl; break;
                    default: std::cout << "Invalid choice!" << std::endl;
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

    void add_student() {
        int id;
        std::string name;
        std::cout << "Enter student ID: ";
        while (!(std::cin >> id)) {
            std::cin.clear(); std::cin.ignore(1000, '\n');
            std::cout << "Invalid ID. Try again: ";
        }
        std::cin.ignore();
        std::cout << "Enter student name: ";
        std::getline(std::cin, name);
        students.emplace_back(id, name);
        std::cout << "Student added.\n";
    }

    void remove_student() {
        int id;
        std::cout << "Enter student ID to remove: ";
        std::cin >> id;
        auto it = std::remove_if(students.begin(), students.end(),
            [id](const Student& s) { return s.get_id() == id; });
        if (it == students.end()) throw StudentNotFoundException("Student not found.");
        students.erase(it, students.end());
        std::cout << "Student removed.\n";
    }

    void search_student() {
        int id;
        std::cout << "Enter student ID to search: ";
        std::cin >> id;
        Student* s = find_student_by_id(id);
        if (!s) throw StudentNotFoundException("Student not found.");
        s->display();
    }

    void display_all_students() {
        if (students.empty()) {
            std::cout << "No students available.\n";
            return;
        }
        for (const Student& s : students) s.display();
    }

    void add_grade_to_student() {
        int id;
        double grade;
        std::cout << "Enter student ID: ";
        std::cin >> id;
        Student* s = find_student_by_id(id);
        if (!s) throw StudentNotFoundException("Student not found.");
        std::cout << "Enter grade (0-100): ";
        std::cin >> grade;
        s->add_grade(grade);
        std::cout << "Grade added.\n";
    }

    Student* find_student_by_id(int id) {
        for (Student& s : students) {
            if (s.get_id() == id) return &s;
        }
        return nullptr;
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