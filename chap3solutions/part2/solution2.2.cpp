#include <cstdio>
#include <cstring>

struct Student {
    char name[50];
    int age;
    double gpa;
};

// Display student information
void display_student(const Student& s) {
    std::printf("Name: %s\n", s.name);
    std::printf("Age: %d\n", s.age);
    std::printf("GPA: %.2f\n", s.gpa);
}

// Check if student is an honor student
bool is_honor_student(const Student& s) {
    return s.gpa >= 3.5;
}

// Update student's GPA
void update_gpa(Student& s, double new_gpa) {
    s.gpa = new_gpa;
}

// Increment student's age by 1
void celebrate_birthday(Student& s) {
    s.age += 1;
}

int main() {
    Student bob = {"Bob Smith", 19, 3.2};

    // Display Bob's initial info
    std::printf("Initial Info:\n");
    display_student(bob);

    // Update Bob's GPA to 3.6
    update_gpa(bob, 3.6);

    // Celebrate Bob's birthday
    celebrate_birthday(bob);

    // Display Bob's updated info
    std::printf("\nUpdated Info:\n");
    display_student(bob);

    // Check if Bob is now an honor student
    if (is_honor_student(bob)) {
        std::printf("\nBob is now an honor student.\n");
    } else {
        std::printf("\nBob is not an honor student.\n");
    }

    return 0;
}