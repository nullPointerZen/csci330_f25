#include <cstdio>

struct Student {
    char name[50];
    int age;
    double gpa;
};

// Function that takes a const Student reference and prints the student's information
void display_student(const Student& s) {
    std::printf("Name: %s\n", s.name);
    std::printf("Age: %d\n", s.age);
    std::printf("GPA: %.2f\n", s.gpa);
}

// Function that takes a const Student reference and returns true if GPA >= 3.5
bool is_honor_student(const Student& s) {
    return s.gpa >= 3.5;
}

int main() {
    Student alice = {"Alice Johnson", 20, 3.8};

    // Call both functions with alice
    display_student(alice);

    if (is_honor_student(alice)) {
        std::printf("Alice is an honor student.\n");
    } else {
        std::printf("Alice is not an honor student.\n");
    }

    return 0;
}