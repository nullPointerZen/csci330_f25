#include <iostream>
#include <iomanip>
#include <cstring>
#include <cassert>
#include <vector>

const int MAX_GRADES = 10;
const int MAX_STUDENTS = 3;

enum ErrorCode {
    SUCCESS = 0,
    OUT_OF_BOUNDS = 1,
    NOT_FOUND = 2
};

struct Student {
    char name[50];
    int student_id;
    int grades[MAX_GRADES];
    int grade_count;
    double average;
};

// === Pointer Arithmetic: Calculate Average ===
double calculate_average(int* grades, size_t count) {
    double sum = 0;
    for (size_t i = 0; i < count; ++i) {
        sum += *(grades + i);
    }
    return count > 0 ? sum / count : 0.0;
}

// === Generic Safe Access Template ===
template <typename T>
ErrorCode safe_access(T* array, size_t index, size_t count, T& out) {
    if (index >= count) return OUT_OF_BOUNDS;
    out = *(array + index);
    return SUCCESS;
}

// === Copy Array Using Pointers ===
void copy_array(int* src, int* dest, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        *(dest + i) = *(src + i);
    }
}

// === Linear Search Using Pointers ===
int search_grade(int* grades, size_t count, int target) {
    for (size_t i = 0; i < count; ++i) {
        if (*(grades + i) == target) return static_cast<int>(i);
    }
    return -1;
}

// === Query System ===
Student* find_by_id(Student* students, size_t count, int id) {
    for (size_t i = 0; i < count; ++i) {
        if ((students + i)->student_id == id) return (students + i);
    }
    return nullptr;
}

std::vector<Student*> find_by_grade_range(Student* students, size_t count, double min, double max) {
    std::vector<Student*> result;
    for (size_t i = 0; i < count; ++i) {
        double avg = (students + i)->average;
        if (avg >= min && avg <= max) result.push_back(students + i);
    }
    return result;
}

// === Memory Layout Investigation ===
void print_struct_layout(const Student& s) {
    std::cout << "\n[Memory Layout of Student Struct]\n";
    std::cout << "Address of name:       " << static_cast<const void*>(s.name) << "\n";
    std::cout << "Address of student_id: " << &s.student_id << "\n";
    std::cout << "Address of grades:     " << s.grades << "\n";
    std::cout << "Address of grade_count:" << &s.grade_count << "\n";
    std::cout << "Address of average:    " << &s.average << "\n";
    std::cout << "Size of struct:        " << sizeof(Student) << " bytes\n";
}

void print_array_addresses(int* array, size_t count) {
    std::cout << "\n[Array Element Addresses]\n";
    for (size_t i = 0; i < count; ++i) {
        std::cout << "grades[" << i << "] @ " << (array + i) << "\n";
    }
}

int main() {
    Student students[MAX_STUDENTS];

    // Initialize sample data
    strcpy(students[0].name, "Alice Johnson");
    students[0].student_id = 1001;
    int alice_grades[] = {85, 92, 78, 96, 88};
    copy_array(alice_grades, students[0].grades, 5);
    students[0].grade_count = 5;

    strcpy(students[1].name, "Bob Smith");
    students[1].student_id = 1002;
    int bob_grades[] = {90, 87, 93};
    copy_array(bob_grades, students[1].grades, 3);
    students[1].grade_count = 3;

    strcpy(students[2].name, "Charlie Rose");
    students[2].student_id = 1003;
    int charlie_grades[] = {70, 75, 80, 85};
    copy_array(charlie_grades, students[2].grades, 4);
    students[2].grade_count = 4;

    // Calculate averages
    for (size_t i = 0; i < MAX_STUDENTS; ++i) {
        students[i].average = calculate_average(students[i].grades, students[i].grade_count);
    }

    std::cout << "=== Student Grade Management System ===\n";
    for (size_t i = 0; i < MAX_STUDENTS; ++i) {
        Student* s = students + i;
        std::cout << "Student: " << s->name << " (ID: " << s->student_id << ")\n  Grades: [";
        for (int j = 0; j < s->grade_count; ++j) {
            std::cout << *(s->grades + j);
            if (j < s->grade_count - 1) std::cout << ", ";
        }
        std::cout << "]\n  Average: " << std::fixed << std::setprecision(1) << s->average << "\n\n";
    }

    // Memory layout demo
    print_struct_layout(students[0]);
    print_array_addresses(students[0].grades, students[0].grade_count);

    // Safe access demo
    int value;
    ErrorCode code = safe_access(students[0].grades, 2, students[0].grade_count, value);
    std::cout << "\nSafe access grades[2]: ";
    if (code == SUCCESS) std::cout << value << "\n";
    else std::cout << "[Error: Out of bounds]\n";

    code = safe_access(students[0].grades, 10, students[0].grade_count, value);
    std::cout << "Unsafe access grades[10]: ";
    if (code == SUCCESS) std::cout << value << "\n";
    else std::cout << "[Error: Out of bounds]\n";

    // Search demo
    int index = search_grade(students[0].grades, students[0].grade_count, 78);
    std::cout << "\nSearch for grade 78 in Alice's record: ";
    if (index != -1) std::cout << "Found at index " << index << "\n";
    else std::cout << "Not found\n";

    // Query demo
    Student* found = find_by_id(students, MAX_STUDENTS, 1002);
    std::cout << "\nQuery by ID 1002: ";
    if (found) std::cout << found->name << " found\n";
    else std::cout << "Student not found\n";

    auto range_results = find_by_grade_range(students, MAX_STUDENTS, 80.0, 90.0);
    std::cout << "Query by grade range [80.0 - 90.0]:\n";
    for (Student* s : range_results) {
        std::cout << "  " << s->name << " (" << s->average << ")\n";
    }

    return 0;
}