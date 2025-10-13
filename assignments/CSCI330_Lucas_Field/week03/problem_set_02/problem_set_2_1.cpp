// Template provided:
#include <cstdio>

struct Student {
    char name[50];
    int age;
    double gpa;
};

// TODO: Write a function 'display_student' that takes a const Student reference
// and prints the student's information
bool is_honor_student(const Student& student) {
        if (student.gpa >= 3.5) {
                return true;
        }
        else {
                return false;
                }
}

void display_student(const Student& student) {
        printf("Student Name: %s\n", student.name);
        printf("%s Age: %d\n", student.name, student.age);
        printf("%s GPA: %.1f\n", student.name, student.gpa);
        printf("%s is an honor student: %s\n", student.name, is_honor_student(student) ? "Yes" : "No");
};
// TODO: Write a function 'is_honor_student' that takes a const Student reference
// and returns true if GPA >= 3.5


int main() {
    Student alice = {"Alice Johnson", 20, 3.8};

    display_student(alice);

    return 0;
}
