#include <iostream>
#include <iomanip>
#include <cstring>

// Simple constants
const int MAX_NAME_LENGTH = 50;
const int MAX_GRADES = 5;
const int MAX_STUDENTS = 3;

// Student structure
struct Student {
    char name[MAX_NAME_LENGTH];
    int student_id;
    double grades[MAX_GRADES];
    int grade_count;
};

// Simple function to calculate average using pointer arithmetic
double calculateAverage(const double* grades, int count) {
    if (count == 0) return 0.0;

    double sum = 0.0;
    for (int i = 0; i < count; ++i) {
        sum += *(grades + i);  // Using pointer arithmetic
    }
    return sum / count;
}

// Display student info
void displayStudent(const Student& student) {
    std::cout << "Student: " << student.name << " (ID: " << student.student_id << ")\n";
    std::cout << "  Grades: [";
    for (int i = 0; i < student.grade_count; ++i) {
        std::cout << student.grades[i];
        if (i < student.grade_count - 1) std::cout << ", ";
    }
    std::cout << "]\n";

    double avg = calculateAverage(student.grades, student.grade_count);
    std::cout << "  Average: " << std::fixed << std::setprecision(1) << avg << "\n\n";
}

// Safe array access demonstration
void demonstrateSafeAccess(const double grades[], int size) {
    std::cout << "Safe Array Access:\n";

    // Safe access with bounds checking
    for (int i = 0; i < size; ++i) {
        std::cout << "  grades[" << i << "] = " << grades[i] << "\n";
    }

    // Demonstrate bounds checking
    int badIndex = 10;
    if (badIndex >= 0 && badIndex < size) {
        std::cout << "  grades[" << badIndex << "] = " << grades[badIndex] << "\n";
    } else {
        std::cout << "  Index " << badIndex << " is out of bounds!\n";
    }
}

int main() {
    std::cout << "=== Student Grade Management System ===\n\n";

    // Create and initialize students
    Student students[MAX_STUDENTS];

    // Student 1: Alice
    strcpy(students[0].name, "Alice Johnson");
    students[0].student_id = 1001;
    students[0].grades[0] = 85.0;
    students[0].grades[1] = 92.0;
    students[0].grades[2] = 78.0;
    students[0].grades[3] = 96.0;
    students[0].grades[4] = 88.0;
    students[0].grade_count = 5;

    // Student 2: Bob
    strcpy(students[1].name, "Bob Smith");
    students[1].student_id = 1002;
    students[1].grades[0] = 90.0;
    students[1].grades[1] = 87.0;
    students[1].grades[2] = 93.0;
    students[1].grade_count = 3;

    // Student 3: Charlie
    strcpy(students[2].name, "Charlie Davis");
    students[2].student_id = 1003;
    students[2].grades[0] = 72.0;
    students[2].grades[1] = 68.0;
    students[2].grades[2] = 75.0;
    students[2].grades[3] = 71.0;
    students[2].grade_count = 4;

    // Display all students
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        displayStudent(students[i]);
    }

    // Find class statistics
    double classSum = 0.0;
    double highest = 0.0;
    double lowest = 100.0;
    int highestIndex = 0;
    int lowestIndex = 0;

    for (int i = 0; i < MAX_STUDENTS; ++i) {
        double avg = calculateAverage(students[i].grades, students[i].grade_count);
        classSum += avg;

        if (avg > highest) {
            highest = avg;
            highestIndex = i;
        }
        if (avg < lowest) {
            lowest = avg;
            lowestIndex = i;
        }
    }

    double classAverage = classSum / MAX_STUDENTS;

    std::cout << "Class Statistics:\n";
    std::cout << "-----------------\n";
    std::cout << "Highest Average: " << students[highestIndex].name
              << " (" << std::fixed << std::setprecision(1) << highest << ")\n";
    std::cout << "Lowest Average: " << students[lowestIndex].name
              << " (" << lowest << ")\n";
    std::cout << "Class Average: " << classAverage << "\n\n";

    // Demonstrate pointer arithmetic
    std::cout << "Pointer Arithmetic Example:\n";
    std::cout << "---------------------------\n";

    Student* ptr = students;
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        std::cout << "Student " << i << " at address " << ptr
                  << ": " << ptr->name << "\n";
        ptr++;  // Move to next student
    }
    std::cout << "\n";

    // Memory layout demonstration
    std::cout << "Memory Layout:\n";
    std::cout << "--------------\n";
    std::cout << "students[0] at: " << &students[0] << "\n";
    std::cout << "students[1] at: " << &students[1] << "\n";
    std::cout << "students[2] at: " << &students[2] << "\n";
    std::cout << "Size of Student struct: " << sizeof(Student) << " bytes\n\n";

    // Safe access demonstration
    demonstrateSafeAccess(students[0].grades, students[0].grade_count);

    return 0;
}