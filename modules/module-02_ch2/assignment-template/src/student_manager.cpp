// HW_02: Part 2 - Student Management System
// Time: 90 minutes
// Topics: Structs, arrays, pointers, memory safety

#include <cstdio>
#include <cstring>  // For strcpy
#include <cassert>  // For assert debugging

// ============================================================================
// PART A: Student Grade Management System (45 minutes)
// ============================================================================

// TODO 1: Define the Student struct
struct Student {
    char name[50];           // Student name (C-style string)
    int studentId;           // Unique ID
    int grades[10];          // Array of grades (max 10)
    int gradeCount;          // Actual number of grades
    double average;          // Calculated average
};

// TODO 2: Initialize sample data for students
void initializeStudents(Student students[], int count) {
    (void)count;  // Suppress unused parameter warning
    // First student
    strcpy(students[0].name, "Alice Johnson");
    students[0].studentId = 1001;
    students[0].grades[0] = 85;
    students[0].grades[1] = 92;
    students[0].grades[2] = 78;
    students[0].grades[3] = 96;
    students[0].grades[4] = 88;
    students[0].gradeCount = 5;
    
    // TODO: Add at least 2 more students with different numbers of grades
    // Remember to set gradeCount for each!
}

// TODO 3: Calculate average using pointer arithmetic (not array indexing)
double calculateAverage(int* grades, int count) {
    if (count == 0) return 0.0;
    
    int sum = 0;
    // int* end = grades + count;  // TODO: Uncomment and use pointer arithmetic
    
    // TODO: Use pointer arithmetic to sum grades
    // Hint: while (grades < end) { sum += *grades; grades++; }
    (void)grades;  // Suppress unused parameter warning
    
    return static_cast<double>(sum) / count;
}

// TODO 4: Calculate all student averages
void calculateAllAverages(Student students[], int count) {
    (void)students;  // TODO: Remove this line when implementing
    (void)count;     // TODO: Remove this line when implementing
    for (int i = 0; i < count; i++) {
        // TODO: Call calculateAverage for each student
        // Store result in students[i].average
    }
}

// TODO 5: Find class statistics
void displayClassStatistics(Student students[], int count) {
    printf("=== Class Statistics ===\n");
    
    if (count == 0) {
        printf("No students enrolled.\n");
        return;
    }
    
    // TODO: Find highest and lowest average
    double highest = students[0].average;
    double lowest = students[0].average;
    int highestIndex = 0;
    int lowestIndex = 0;
    double classTotal = 0.0;
    
    // TODO: Loop through students to find statistics
    
    printf("  Highest Average: %s (%.1f)\n", 
           students[highestIndex].name, highest);
    printf("  Lowest Average: %s (%.1f)\n", 
           students[lowestIndex].name, lowest);
    printf("  Class Average: %.1f\n", classTotal / count);
    printf("\n");
}

// ============================================================================
// PART B: Advanced Memory Operations and Pointers (45 minutes)
// ============================================================================

// TODO 6: Safe array access with bounds checking
int safeGetGrade(Student* student, int index) {
    (void)student;  // TODO: Remove this line when implementing
    (void)index;    // TODO: Remove this line when implementing
    // TODO: Check if index is valid (0 <= index < gradeCount)
    // Use assert for debugging: assert(index >= 0 && index < student->gradeCount);
    // Return grade if valid, or -1 if invalid
    
    return -1;  // Placeholder
}

// TODO 7: Display student information with memory addresses
void displayStudent(Student* student) {
    printf("Student: %s (ID: %d)\n", student->name, student->studentId);
    printf("  Memory address: %p\n", (void*)student);
    printf("  Grades: [");
    
    // TODO: Display grades using pointer notation
    for (int i = 0; i < student->gradeCount; i++) {
        printf("%d", *(student->grades + i));
        if (i < student->gradeCount - 1) printf(", ");
    }
    printf("]\n");
    printf("  Average: %.1f\n", student->average);
    printf("\n");
}

// TODO 8: Show memory layout of struct
void exploreMemoryLayout(Student* student) {
    printf("=== Memory Layout of Student Struct ===\n");
    
    printf("Base address:        %p\n", (void*)student);
    printf("name field offset:   %p (offset: %ld)\n", 
           (void*)&student->name, 
           (char*)&student->name - (char*)student);
    printf("studentId offset:    %p (offset: %ld)\n", 
           (void*)&student->studentId,
           (char*)&student->studentId - (char*)student);
    printf("grades array offset: %p (offset: %ld)\n", 
           (void*)&student->grades,
           (char*)&student->grades - (char*)student);
    
    // TODO: Calculate and display total struct size
    printf("Total struct size: %zu bytes\n", sizeof(Student));
    printf("\n");
}

// TODO 9: Sort students by average (simple bubble sort)
void sortStudentsByAverage(Student students[], int count) {
    // TODO: Implement bubble sort
    // Remember to swap entire Student structs, not just averages!
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].average < students[j + 1].average) {
                // TODO: Swap students[j] and students[j+1]
                // Hint: Student temp = students[j]; ...
            }
        }
    }
}

// TODO 10: Demonstrate safe vs unsafe array access
void memorySafetyDemo() {
    printf("=== Memory Safety Demo ===\n");
    
    Student student;
    strcpy(student.name, "Test Student");
    student.studentId = 9999;
    student.gradeCount = 3;
    student.grades[0] = 90;
    student.grades[1] = 85;
    student.grades[2] = 88;
    
    // Safe access
    printf("Safe access - grades[1]: %d\n", safeGetGrade(&student, 1));
    
    // Unsafe access (commented out to prevent crash)
    // printf("Unsafe access - grades[10]: %d\n", student.grades[10]);
    
    // TODO: Try accessing with negative index through safeGetGrade
    printf("Safe access - grades[-1]: %d (should return -1)\n", 
           safeGetGrade(&student, -1));
    
    printf("\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("========================================\n");
    printf("    HW_02: Student Management System\n");
    printf("========================================\n\n");
    
    // Create array of students
    const int MAX_STUDENTS = 5;
    Student students[MAX_STUDENTS];
    int studentCount = 3;  // We'll initialize 3 students
    
    // Part A: Basic Operations (45 min)
    initializeStudents(students, studentCount);
    calculateAllAverages(students, studentCount);
    
    // Display all students
    printf("=== Student Records ===\n");
    for (int i = 0; i < studentCount; i++) {
        displayStudent(&students[i]);
    }
    
    // Display statistics
    displayClassStatistics(students, studentCount);
    
    // Part B: Advanced Operations (45 min)
    
    // Sort students by average
    printf("=== Sorted by Average (Highest to Lowest) ===\n");
    sortStudentsByAverage(students, studentCount);
    for (int i = 0; i < studentCount; i++) {
        printf("%d. %s - Average: %.1f\n", 
               i + 1, students[i].name, students[i].average);
    }
    printf("\n");
    
    // Memory layout exploration
    exploreMemoryLayout(&students[0]);
    
    // Memory safety demonstration
    memorySafetyDemo();
    
    printf("========================================\n");
    printf("         Program Complete!\n");
    printf("========================================\n");
    
    return 0;
}