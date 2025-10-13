// Template provided (build on Problem 2.1):
#include <cstdio>
#include <cstring>

struct Student {
    char name[50];
    int age;
    double gpa;
};

bool is_honor_student(const Student& student) {
        if (student.gpa >= 3.5) {
                return true;
        }
        else {
                return false;
                }
}

void update_gpa (Student& student) {
	student.gpa = 3.6;

}

void celebrate_birthday (Student& student) {
	student.age += 1;
	printf("Happy Birthday %s!\n", student.name);
}



void display_student(const Student& student) {
        printf("\nStudent Name: %s\n", student.name);
        printf("%s Age: %d\n", student.name, student.age);
        printf("%s GPA: %.1f\n", student.name, student.gpa);
        printf("%s is an honor student: %s\n", student.name, is_honor_student(student) ? "Yes" : "No");
};

// TODO: Keep your display_student and is_honor_student functions from 2.1

// TODO: Write a function 'update_gpa' that takes a Student reference (non-const)
// and a new GPA value, then updates the student's GPA

// TODO: Write a function 'celebrate_birthday' that takes a Student reference
// and increments their age by 1

int main() {
    Student bob = {"Bob Smith", 19, 3.2};
   
    display_student(bob);
    update_gpa(bob);
    celebrate_birthday(bob);
    printf("\nUpdated Information after birthday and updated GPA.\n");
    display_student(bob);

    // TODO: Display Bob's initial info
    // TODO: Update Bob's GPA to 3.6
    // TODO: Celebrate Bob's birthday
    // TODO: Display Bob's updated info
    // TODO: Check if Bob is now an honor student
    
    return 0;
}
