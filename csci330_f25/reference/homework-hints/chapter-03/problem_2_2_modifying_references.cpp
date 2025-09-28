#include <cstdio>

struct Student {
    char name[50];
    int age;
    double gpa;
};

// Functions from Problem 2.1 (const references for read-only)
void display_student(const Student& student) {
    printf("Student: %s, Age: %d, GPA: %.2f\n", 
           student.name, student.age, student.gpa);
}

bool is_honor_student(const Student& student) {
    return student.gpa >= 3.5;
}

// Function that takes a Student reference (non-const) and updates GPA
void update_gpa(Student& student, double new_gpa) {
    student.gpa = new_gpa;
}

// Function that takes a Student reference and increments their age
void celebrate_birthday(Student& student) {
    student.age++;
}

int main() {
    Student bob = {"Bob Smith", 19, 3.2};
    
    // Display Bob's initial info
    printf("Initial - ");
    display_student(bob);
    printf("Bob is an honor student: %s\n", 
           is_honor_student(bob) ? "Yes" : "No");
    
    // Update Bob's GPA to 3.6
    update_gpa(bob, 3.6);
    
    // Celebrate Bob's birthday
    celebrate_birthday(bob);
    
    // Display Bob's updated info
    printf("Updated - ");
    display_student(bob);
    printf("Bob is an honor student: %s\n", 
           is_honor_student(bob) ? "Yes" : "No");
    
    return 0;
}