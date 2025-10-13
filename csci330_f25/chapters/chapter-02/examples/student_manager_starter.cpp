// student_manager_starter.cpp
// Starter code for Assignment 2: Memory and Data Structures
// TODO markers indicate where you need to add code

#include <cstdio>
#include <cstring>
#include <cassert>

// ============================================
// CONSTANTS AND STRUCTURES
// ============================================

const int MAX_NAME_LENGTH = 50;
const int MAX_GRADES = 10;
const int MAX_STUDENTS = 5;

struct Student {
    char name[MAX_NAME_LENGTH];
    int student_id;
    int grades[MAX_GRADES];
    int grade_count;  // Number of grades for this student
    double average;   // Calculated average grade
};

// ============================================
// PART A: Core Functionality
// ============================================

// Calculate average for a single student
void calculate_average(Student* student) {
    assert(student != nullptr);  // Safety check

    if (student->grade_count == 0) {
        student->average = 0.0;
        return;
    }

    // TODO: Calculate the sum of all grades
    int total = 0;
    for (int i = 0; i < student->grade_count; i++) {
        // Add each grade to total
        // total += ...
    }

    // TODO: Calculate average (watch out for integer division!)
    // student->average = ...
}

// Print a single student's information
void print_student(const Student* student) {
    assert(student != nullptr);

    printf("Student: %s (ID: %d)\n", student->name, student->student_id);

    // Print grades
    printf("  Grades: [");
    for (int i = 0; i < student->grade_count; i++) {
        // TODO: Print each grade
        // printf("%d", ...);
        // if (i < student->grade_count - 1) printf(", ");
    }
    printf("]\n");

    printf("  Average: %.1f\n", student->average);
}

// Find student with highest average
int find_top_student(Student students[], int count) {
    assert(count > 0);

    int top_index = 0;
    double highest_avg = students[0].average;

    // TODO: Find student with highest average
    for (int i = 1; i < count; i++) {
        // if (students[i].average > highest_avg) {
        //     ...
        // }
    }

    return top_index;
}

// Calculate class-wide average
double calculate_class_average(Student students[], int count) {
    assert(count > 0);

    double total = 0.0;

    // TODO: Sum all student averages
    // for (int i = 0; i < count; i++) {
    //     ...
    // }

    // TODO: Return class average
    return 0.0;  // Replace with actual calculation
}

// Simple bubble sort by average grade
void sort_students_by_average(Student students[], int count) {
    // TODO: Implement bubble sort
    // Hint: Compare students[i].average with students[i+1].average
    // Swap entire Student structs if needed

    // for (int i = 0; i < count - 1; i++) {
    //     for (int j = 0; j < count - i - 1; j++) {
    //         if (students[j].average < students[j + 1].average) {
    //             // Swap students[j] and students[j + 1]
    //             Student temp = students[j];
    //             ...
    //         }
    //     }
    // }
}

// ============================================
// PART A: Memory Safety Demonstrations
// ============================================

// Safe array access with bounds checking
bool safe_get_grade(const Student* student, int index, int* result) {
    assert(student != nullptr);
    assert(result != nullptr);

    // TODO: Check if index is valid
    // if (index < 0 || index >= ...) {
    //     return false;  // Invalid index
    // }

    // TODO: Set the result and return true
    // *result = ...
    return true;  // Replace with actual implementation
}

// Demonstrate what happens with unsafe access (educational purpose only!)
void demonstrate_array_bounds() {
    printf("\n=== Memory Safety Demo ===\n");

    int test_array[5] = {10, 20, 30, 40, 50};

    // Safe access
    printf("Safe access:\n");
    for (int i = 0; i < 5; i++) {
        printf("  test_array[%d] = %d\n", i, test_array[i]);
    }

    // TODO: Demonstrate bounds checking
    printf("\nBounds checking:\n");
    int indices[] = {0, 2, 4, 5, -1};  // Some valid, some invalid
    for (int i = 0; i < 5; i++) {
        int idx = indices[i];
        // Check if idx is valid before accessing
        // if (idx >= 0 && idx < 5) {
        //     printf("  test_array[%d] = %d (valid)\n", idx, test_array[idx]);
        // } else {
        //     printf("  Index %d is out of bounds!\n", idx);
        // }
    }
}

// ============================================
// PART B: Pointer Operations
// ============================================

// Calculate average using pointer arithmetic instead of array indexing
double calculate_average_with_pointers(int* grades, int count) {
    assert(grades != nullptr);
    assert(count > 0);

    int total = 0;
    int* end = grades + count;  // Pointer to one past the last element

    // TODO: Use pointer arithmetic to sum grades
    // for (int* ptr = grades; ptr < end; ptr++) {
    //     total += *ptr;  // Dereference pointer to get value
    // }

    // TODO: Return average
    return 0.0;  // Replace with actual calculation
}

// Show memory addresses of array elements
void show_array_memory_layout(int arr[], int size) {
    printf("\n=== Array Memory Layout ===\n");

    for (int i = 0; i < size; i++) {
        // TODO: Print address and value of each element
        // printf("arr[%d]: value=%d, address=%p\n", i, arr[i], (void*)&arr[i]);
    }

    // TODO: Calculate and show the size of gaps between elements
    // if (size > 1) {
    //     size_t element_size = (char*)&arr[1] - (char*)&arr[0];
    //     printf("Bytes between elements: %zu\n", element_size);
    // }
}

// Show memory layout of Student struct
void show_struct_memory_layout(Student* s) {
    printf("\n=== Struct Memory Layout ===\n");

    // TODO: Print base address and field addresses
    printf("Student struct at: %p\n", (void*)s);
    // printf("  name field at: %p (offset: %ld bytes)\n",
    //        (void*)&s->name, (char*)&s->name - (char*)s);
    // printf("  student_id at: %p (offset: %ld bytes)\n",
    //        (void*)&s->student_id, (char*)&s->student_id - (char*)s);
    // Continue for other fields...

    printf("Total struct size: %zu bytes\n", sizeof(Student));
}

// ============================================
// MAIN FUNCTION
// ============================================

int main() {
    printf("=== Student Grade Management System ===\n\n");

    // Create array of students
    Student students[MAX_STUDENTS];
    int student_count = 0;

    // Initialize first student (Alice)
    strcpy(students[0].name, "Alice Johnson");
    students[0].student_id = 1001;
    students[0].grades[0] = 85;
    students[0].grades[1] = 92;
    students[0].grades[2] = 78;
    students[0].grades[3] = 96;
    students[0].grades[4] = 88;
    students[0].grade_count = 5;
    calculate_average(&students[0]);
    student_count++;

    // TODO: Initialize second student (Bob)
    // strcpy(students[1].name, "Bob Smith");
    // students[1].student_id = 1002;
    // students[1].grades[0] = 90;
    // students[1].grades[1] = 87;
    // students[1].grades[2] = 93;
    // students[1].grade_count = 3;
    // calculate_average(&students[1]);
    // student_count++;

    // TODO: Initialize third student (Charlie)
    // Add at least one more student with different grades

    // Print all students
    printf("All Students:\n");
    printf("--------------\n");
    for (int i = 0; i < student_count; i++) {
        print_student(&students[i]);
        printf("\n");
    }

    // Calculate and display class statistics
    printf("Class Statistics:\n");
    printf("-----------------\n");

    // TODO: Find and print highest average
    // int top_idx = find_top_student(students, student_count);
    // printf("Highest Average: %s (%.1f)\n",
    //        students[top_idx].name, students[top_idx].average);

    // TODO: Find and print lowest average
    // (Similar to finding highest, but look for minimum)

    // TODO: Calculate and print class average
    // double class_avg = calculate_class_average(students, student_count);
    // printf("Class Average: %.1f\n", class_avg);

    // TODO: Sort students by average and display
    // printf("\nStudents Sorted by Average:\n");
    // printf("----------------------------\n");
    // sort_students_by_average(students, student_count);
    // for (int i = 0; i < student_count; i++) {
    //     printf("%d. %s: %.1f\n", i+1, students[i].name, students[i].average);
    // }

    // Part A: Memory Safety Demonstrations
    demonstrate_array_bounds();

    // TODO: Test safe_get_grade function
    // int grade;
    // if (safe_get_grade(&students[0], 2, &grade)) {
    //     printf("\nSafe access: Student 0, Grade 2 = %d\n", grade);
    // }

    // Part B: Pointer Operations
    // TODO: Test pointer arithmetic functions
    // double avg = calculate_average_with_pointers(students[0].grades,
    //                                               students[0].grade_count);
    // printf("\nAverage using pointers: %.1f\n", avg);

    // TODO: Show memory layouts
    // show_array_memory_layout(students[0].grades, students[0].grade_count);
    // show_struct_memory_layout(&students[0]);

    printf("\n=== Program Complete ===\n");
    return 0;
}

/*
 * COMPILATION INSTRUCTIONS:
 * -------------------------
 * g++ -Wall -Wextra -o student_manager student_manager_starter.cpp
 * ./student_manager
 *
 * DEBUGGING TIPS:
 * --------------
 * 1. Use printf to trace values during calculation
 * 2. Check array bounds before every access
 * 3. Initialize all variables before use
 * 4. Use assert() to catch logic errors early
 *
 * COMMON MISTAKES TO AVOID:
 * ------------------------
 * - Forgetting to use strcpy() for string assignment
 * - Integer division when calculating averages
 * - Off-by-one errors in loops
 * - Not checking for null pointers
 * - Accessing arrays out of bounds
 */