// Problem 2.2: Modifying Through Non-Const References
// Demonstrates using non-const references to modify objects in functions

#include <cstdio>
#include <cstring>

struct Student {
    char name[50];
    int age;
    double gpa;
};

// Function that takes a const Student reference and prints student information
void display_student(const Student& student) {
    printf("Student: %s, Age: %d, GPA: %.2f\n", 
           student.name, student.age, student.gpa);
}

// Function that takes a const Student reference and returns true if GPA >= 3.5
bool is_honor_student(const Student& student) {
    return student.gpa >= 3.5;
}

// Function that takes a Student reference (non-const) and updates the GPA
void update_gpa(Student& student, double new_gpa) {
    student.gpa = new_gpa;
    printf("Updated %s's GPA to %.2f\n", student.name, new_gpa);
}

// Function that takes a Student reference and increments their age by 1
void celebrate_birthday(Student& student) {
    student.age++;
    printf("Happy birthday %s! Now %d years old.\n", student.name, student.age);
}

int main() {
    Student bob = {"Bob Smith", 19, 3.2};
    
    // Display Bob's initial info
    printf("=== Initial Information ===\n");
    display_student(bob);
    printf("Bob is an honor student: %s\n", 
           is_honor_student(bob) ? "Yes" : "No");
    
    // Update Bob's GPA to 3.6
    printf("\n=== Updating GPA ===\n");
    update_gpa(bob, 3.6);
    
    // Celebrate Bob's birthday
    printf("\n=== Birthday Celebration ===\n");
    celebrate_birthday(bob);
    
    // Display Bob's updated info
    printf("\n=== Updated Information ===\n");
    display_student(bob);
    
    // Check if Bob is now an honor student
    printf("Bob is an honor student: %s\n", 
           is_honor_student(bob) ? "Yes" : "No");
    
    return 0;
}