#include <iostream>
#include <iomanip>
#include <cstring>
#include <cassert>

const int MAX_GRADES = 10;
const int MAX_STUDENTS = 3;

struct Student {
    char name[50];
    int student_id;
    int grades[MAX_GRADES];
    int grade_count;
    double average;
};

// Calculate average using pointer arithmetic
double calculateAverage(const int* grades, int count) {
    double sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += *(grades + i); // pointer arithmetic
    }
    return count > 0 ? sum / count : 0.0;
}

// Safe access with bounds checking
int safeAccess(const int* grades, int index, int count) {
    assert(index >= 0 && index < count); // Debug safety
    return grades[index];
}

// Bubble sort students by average
void sortByAverage(Student* students, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (students[j].average < students[j + 1].average) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int main() {
    Student students[MAX_STUDENTS];

    // Initialize sample data
    strcpy(students[0].name, "Alice Johnson");
    students[0].student_id = 1001;
    students[0].grades[0] = 85;
    students[0].grades[1] = 92;
    students[0].grades[2] = 78;
    students[0].grades[3] = 96;
    students[0].grades[4] = 88;
    students[0].grade_count = 5;

    strcpy(students[1].name, "Bob Smith");
    students[1].student_id = 1002;
    students[1].grades[0] = 90;
    students[1].grades[1] = 87;
    students[1].grades[2] = 93;
    students[1].grade_count = 3;

    strcpy(students[2].name, "Charlie Rose");
    students[2].student_id = 1003;
    students[2].grades[0] = 70;
    students[2].grades[1] = 75;
    students[2].grades[2] = 80;
    students[2].grades[3] = 85;
    students[2].grade_count = 4;

    // Calculate averages
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        students[i].average = calculateAverage(students[i].grades, students[i].grade_count);
    }

    // Sort students by average
    sortByAverage(students, MAX_STUDENTS);

    std::cout << "=== Student Grade Management System ===\n";
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        std::cout << "Student: " << students[i].name << " (ID: " << students[i].student_id << ")\n  Grades: [";
        for (int j = 0; j < students[i].grade_count; ++j) {
            std::cout << students[i].grades[j];
            if (j < students[i].grade_count - 1) std::cout << ", ";
        }
        std::cout << "]\n  Average: " << std::fixed << std::setprecision(1) << students[i].average << "\n\n";
    }

    // Class statistics
    double total = 0;
    double highest = students[0].average;
    double lowest = students[0].average;
    int highestIndex = 0;
    int lowestIndex = 0;

    for (int i = 0; i < MAX_STUDENTS; ++i) {
        total += students[i].average;
        if (students[i].average > highest) {
            highest = students[i].average;
            highestIndex = i;
        }
        if (students[i].average < lowest) {
            lowest = students[i].average;
            lowestIndex = i;
        }
    }

    std::cout << "Class Statistics:\n";
    std::cout << "  Highest Average: " << students[highestIndex].name << " (" << students[highestIndex].average << ")\n";
    std::cout << "  Lowest Average: " << students[lowestIndex].name << " (" << students[lowestIndex].average << ")\n";
    std::cout << "  Class Average: " << std::fixed << std::setprecision(1) << total / MAX_STUDENTS << "\n";

    // Memory Safety Demo
    std::cout << "\n[Memory Safety Demo]\n";
    std::cout << "  Safe access: grades[2] = " << safeAccess(students[0].grades, 2, students[0].grade_count) << "\n";

    std::cout << "  Unsafe access: grades[10] = ";
    // Controlled unsafe access (commented out to avoid crash)
    // std::cout << students[0].grades[10] << "\n"; // Undefined behavior
    std::cout << "[undefined/crash]\n";

    return 0;
}