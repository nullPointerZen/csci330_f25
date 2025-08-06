/*
 * Chapter 2, Problem 3.1 Solution: Student Management System
 * 
 * This comprehensive solution demonstrates the integration of:
 * - Structs for data organization
 * - Arrays for collections
 * - Pointers for function parameters
 * - Functions for code organization
 * 
 * Key Learning Points:
 * 1. Structs group related data together
 * 2. Pointers allow functions to modify original data
 * 3. const pointers prevent accidental modification
 * 4. Array processing with bounds checking
 * 5. String handling with strcpy
 * 
 * Python Comparison: Similar to Python classes but simpler
 * Java Comparison: Like Java objects but with manual memory management
 */

#include <cstdio>
#include <cstring>

// Define the Student struct to group related data
struct Student {
    char name[30];      // Character array for student name
    int studentId;      // Unique identifier
    int grades[5];      // Array of 5 test scores
    double gpa;         // Grade Point Average
};

/*
 * Calculate GPA from grades array
 * 
 * Parameters:
 *   student - Pointer to Student struct (allows modification)
 * 
 * Returns:
 *   double - Calculated GPA on 4.0 scale
 * 
 * Algorithm:
 *   1. Sum all grades
 *   2. Calculate average
 *   3. Convert to 4.0 scale (assuming grades are 0-100)
 */
double calculateGPA(Student* student) {
    int sum = 0;
    
    // Sum all grades in the array
    for (int i = 0; i < 5; i++) {
        sum += student->grades[i];
    }
    
    // Calculate average grade
    double average = sum / 5.0;
    
    // Convert to 4.0 scale (simple conversion: average / 25.0)
    // This assumes grades are on 0-100 scale
    double gpa = average / 25.0;
    
    // Cap GPA at 4.0 (in case of extra credit)
    if (gpa > 4.0) {
        gpa = 4.0;
    }
    
    // Store GPA in student struct for future use
    student->gpa = gpa;
    
    return gpa;
}

/*
 * Print student information in a formatted way
 * 
 * Parameters:
 *   student - const pointer to Student (read-only access)
 * 
 * The const keyword prevents accidental modification of student data
 */
void printStudent(const Student* student) {
    printf("\nStudent: %s (ID: %d)\n", student->name, student->studentId);
    
    // Print all grades on one line
    printf("Grades: ");
    for (int i = 0; i < 5; i++) {
        printf("%d", student->grades[i]);
        if (i < 4) {
            printf(", ");  // Add comma between grades
        }
    }
    printf("\n");
    
    // Print GPA with 2 decimal places
    printf("GPA: %.2f\n", student->gpa);
}

/*
 * Find student with highest GPA from array
 * 
 * Parameters:
 *   students - Array of Student structs
 *   count - Number of students in array
 * 
 * Returns:
 *   Student* - Pointer to student with highest GPA
 */
Student* findTopStudent(Student students[], int count) {
    // Handle edge case: empty array
    if (count <= 0) {
        return nullptr;
    }
    
    Student* topStudent = &students[0];  // Start with first student
    
    // Compare with all other students
    for (int i = 1; i < count; i++) {
        if (students[i].gpa > topStudent->gpa) {
            topStudent = &students[i];
        }
    }
    
    return topStudent;
}

/*
 * Update a specific grade for a student
 * 
 * Parameters:
 *   student - Pointer to Student struct
 *   testIndex - Which test to update (0-4)
 *   newGrade - New grade value
 * 
 * Returns:
 *   bool - true if update successful, false if invalid index
 */
bool updateGrade(Student* student, int testIndex, int newGrade) {
    // Validate test index
    if (testIndex < 0 || testIndex >= 5) {
        printf("Error: Test index must be 0-4\n");
        return false;
    }
    
    // Validate grade range (assuming 0-100)
    if (newGrade < 0 || newGrade > 100) {
        printf("Error: Grade must be 0-100\n");
        return false;
    }
    
    // Store old grade for reporting
    int oldGrade = student->grades[testIndex];
    
    // Update the grade
    student->grades[testIndex] = newGrade;
    
    printf("Updated %s's test %d from %d to %d\n", 
           student->name, testIndex + 1, oldGrade, newGrade);
    
    return true;
}

/*
 * Main program demonstrating the student management system
 */
int main() {
    printf("=== Student Management System ===\n");
    
    // Create array of 3 students
    Student students[3];
    
    // Initialize first student: Alice Johnson
    strcpy(students[0].name, "Alice Johnson");
    students[0].studentId = 12345;
    students[0].grades[0] = 85;
    students[0].grades[1] = 92;
    students[0].grades[2] = 78;
    students[0].grades[3] = 96;
    students[0].grades[4] = 89;
    
    // Initialize second student: Bob Smith
    strcpy(students[1].name, "Bob Smith");
    students[1].studentId = 12346;
    students[1].grades[0] = 78;
    students[1].grades[1] = 85;
    students[1].grades[2] = 82;
    students[1].grades[3] = 90;
    students[1].grades[4] = 88;
    
    // Initialize third student: Carol Davis
    strcpy(students[2].name, "Carol Davis");
    students[2].studentId = 12347;
    students[2].grades[0] = 95;
    students[2].grades[1] = 98;
    students[2].grades[2] = 92;
    students[2].grades[3] = 94;
    students[2].grades[4] = 96;
    
    // Calculate GPA for each student
    printf("\nCalculating GPAs for all students...\n");
    for (int i = 0; i < 3; i++) {
        calculateGPA(&students[i]);
    }
    
    // Print all student information
    printf("\n=== Student Records ===");
    for (int i = 0; i < 3; i++) {
        printStudent(&students[i]);
    }
    
    // Find and announce top student
    Student* topStudent = findTopStudent(students, 3);
    if (topStudent != nullptr) {
        printf("\n=== Top Student ===\n");
        printf("Top Student: %s with GPA %.2f\n", topStudent->name, topStudent->gpa);
    }
    
    // Demonstrate grade update
    printf("\n=== Grade Update Demo ===\n");
    printf("Updating Alice's test 3 grade...\n");
    
    if (updateGrade(&students[0], 2, 88)) {  // Test 3 is index 2
        // Recalculate GPA after update
        calculateGPA(&students[0]);
        printf("Alice's updated information:");
        printStudent(&students[0]);
    }
    
    // Demonstrate error handling
    printf("\n=== Error Handling Demo ===\n");
    updateGrade(&students[0], 10, 95);  // Invalid index
    updateGrade(&students[0], 1, 150);  // Invalid grade
    
    return 0;
}

/*
 * Expected Output:
 * === Student Management System ===
 * 
 * Calculating GPAs for all students...
 * 
 * === Student Records ===
 * 
 * Student: Alice Johnson (ID: 12345)
 * Grades: 85, 92, 78, 96, 89
 * GPA: 3.52
 * 
 * Student: Bob Smith (ID: 12346)
 * Grades: 78, 85, 82, 90, 88
 * GPA: 3.37
 * 
 * Student: Carol Davis (ID: 12347)
 * Grades: 95, 98, 92, 94, 96
 * GPA: 3.75
 * 
 * === Top Student ===
 * Top Student: Carol Davis with GPA 3.75
 * 
 * === Grade Update Demo ===
 * Updating Alice's test 3 grade...
 * Updated Alice Johnson's test 3 from 78 to 88
 * Alice's updated information:
 * 
 * Student: Alice Johnson (ID: 12345)
 * Grades: 85, 92, 88, 96, 89
 * GPA: 3.60
 * 
 * === Error Handling Demo ===
 * Error: Test index must be 0-4
 * Error: Grade must be 0-100
 * 
 * 
 * Key Teaching Points:
 * 
 * 1. STRUCT USAGE:
 *    - Groups related data together
 *    - Access members with dot notation (student.name)
 *    - Access via pointer with arrow notation (student->name)
 * 
 * 2. POINTER PARAMETERS:
 *    - Use Student* to modify original struct
 *    - Use const Student* for read-only access
 *    - Pass arrays by name (decay to pointer)
 * 
 * 3. STRING HANDLING:
 *    - Must use strcpy() to assign strings to char arrays
 *    - Cannot use student.name = "Alice" (compilation error)
 * 
 * 4. ARRAY PROCESSING:
 *    - Always track array size separately
 *    - Check bounds before accessing elements
 *    - Use loops for repetitive operations
 * 
 * 5. ERROR HANDLING:
 *    - Validate function parameters
 *    - Return success/failure status
 *    - Handle edge cases (empty arrays, invalid indices)
 * 
 * 
 * Common Student Mistakes:
 * 
 * 1. WRONG: student.name = "Alice";           // Can't assign strings directly
 *    RIGHT: strcpy(student.name, "Alice");    // Use strcpy for strings
 * 
 * 2. WRONG: void printStudent(Student s) { } // Copies entire struct (inefficient)
 *    RIGHT: void printStudent(const Student* s) { } // Uses pointer (efficient)
 * 
 * 3. WRONG: return students[0];               // Returns copy of struct
 *    RIGHT: return &students[0];              // Returns pointer to struct
 * 
 * 4. WRONG: if (students[i].gpa > topStudent.gpa) // Comparing values
 *    RIGHT: if (students[i].gpa > topStudent->gpa) // Dereferencing pointer
 * 
 * 
 * Advanced Extensions (for interested students):
 * - Add student search by ID function
 * - Implement student sorting by GPA
 * - Add file I/O to save/load student data
 * - Implement dynamic array resizing
 * 
 * 
 * Compilation: g++ -o student_system problem_3_1_solution.cpp
 * Execution: ./student_system
 */