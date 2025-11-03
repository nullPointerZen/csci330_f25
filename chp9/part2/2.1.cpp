#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

struct Student {
    std::string name;
    int grade;

    Student(const std::string& n, int g) : name(n), grade(g) {}
};

int main() {
    std::vector<Student> students = {
        {"Alice", 92}, {"Bob", 87}, {"Charlie", 78},
        {"Diana", 95}, {"Eve", 82}, {"Frank", 69}
    };

    std::cout << "All students:\n";
    std::for_each(students.begin(), students.end(), [](const Student& s) {
        std::cout << s.name << ": " << s.grade << "\n";
    });

    std::cout << "\nHonor roll students (grade >= 90):\n";
    std::vector<Student> honor_roll;
    std::copy_if(students.begin(), students.end(), std::back_inserter(honor_roll),
        [](const Student& s) { return s.grade >= 90; });
    std::for_each(honor_roll.begin(), honor_roll.end(), [](const Student& s) {
        std::cout << s.name << ": " << s.grade << "\n";
    });

    int passing_count = std::count_if(students.begin(), students.end(),
        [](const Student& s) { return s.grade >= 70; });

    int total = std::accumulate(students.begin(), students.end(), 0,
        [](int sum, const Student& s) { return sum + s.grade; });
    double average = static_cast<double>(total) / students.size();

    int curve_points = 5;
    std::vector<Student> curved_students;
    std::transform(students.begin(), students.end(), std::back_inserter(curved_students),
        [curve_points](const Student& s) {
            return Student(s.name, std::min(s.grade + curve_points, 100));
        });

    std::cout << "\nAfter applying " << curve_points << " point curve:\n";
    std::for_each(curved_students.begin(), curved_students.end(), [](const Student& s) {
        std::cout << s.name << ": " << s.grade << "\n";
    });

    std::cout << "\nStatistics:\n";
    std::cout << "Passing students: " << passing_count << "\n";
    std::cout << "Average grade: " << average << "\n";

    return 0;
}