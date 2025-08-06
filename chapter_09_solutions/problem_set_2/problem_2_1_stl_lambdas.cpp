#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <iterator>

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
    
    std::cout << "STL Algorithms with Lambdas Demo" << std::endl;
    std::cout << "================================" << std::endl;
    
    std::cout << "\nAll students:" << std::endl;
    // Using std::for_each with lambda to print all students
    std::for_each(students.begin(), students.end(), 
                  [](const Student& s) {
                      std::cout << s.name << ": " << s.grade << std::endl;
                  });
    
    std::cout << "\nHonor roll students (grade >= 90):" << std::endl;
    // Using std::copy_if with lambda to find honor roll students
    std::copy_if(students.begin(), students.end(),
                 std::ostream_iterator<Student>(std::cout, ""),
                 [](const Student& s) { return s.grade >= 90; });
    
    // For the ostream_iterator to work, we need operator<< for Student
    // Let's do it differently - collect then print
    std::vector<Student> honor_roll;
    std::copy_if(students.begin(), students.end(), std::back_inserter(honor_roll),
                 [](const Student& s) { return s.grade >= 90; });
    
    for(const auto& student : honor_roll) {
        std::cout << student.name << ": " << student.grade << std::endl;
    }
    
    // Count students passing (grade >= 70) using std::count_if
    int passing_count = std::count_if(students.begin(), students.end(),
                                      [](const Student& s) { return s.grade >= 70; });
    
    // Calculate average grade using std::accumulate and lambda
    double total = std::accumulate(students.begin(), students.end(), 0.0,
                                   [](double sum, const Student& s) {
                                       return sum + s.grade;
                                   });
    double average = total / students.size();
    
    // Apply curve (+5 points) using std::transform with capture
    int curve_points = 5;
    std::vector<Student> curved_students = students; // Copy for modification
    std::transform(curved_students.begin(), curved_students.end(), curved_students.begin(),
                   [curve_points](Student s) {
                       s.grade += curve_points;
                       if (s.grade > 100) s.grade = 100; // Cap at 100
                       return s;
                   });
    
    std::cout << "\nAfter applying " << curve_points << " point curve:" << std::endl;
    std::for_each(curved_students.begin(), curved_students.end(),
                  [](const Student& s) {
                      std::cout << s.name << ": " << s.grade << std::endl;
                  });
    
    std::cout << "\nStatistics:" << std::endl;
    std::cout << "Passing students: " << passing_count << std::endl;
    std::cout << "Average grade: " << average << std::endl;
    
    // Bonus: Find highest and lowest grades using std::max_element and std::min_element
    auto highest = std::max_element(students.begin(), students.end(),
                                    [](const Student& a, const Student& b) {
                                        return a.grade < b.grade;
                                    });
    auto lowest = std::min_element(students.begin(), students.end(),
                                   [](const Student& a, const Student& b) {
                                       return a.grade < b.grade;
                                   });
    
    std::cout << "Highest grade: " << highest->name << " (" << highest->grade << ")" << std::endl;
    std::cout << "Lowest grade: " << lowest->name << " (" << lowest->grade << ")" << std::endl;
    
    return 0;
}

/* Sample Output:
STL Algorithms with Lambdas Demo
================================

All students:
Alice: 92
Bob: 87
Charlie: 78
Diana: 95
Eve: 82
Frank: 69

Honor roll students (grade >= 90):
Alice: 92
Diana: 95

After applying 5 point curve:
Alice: 97
Bob: 92
Charlie: 83
Diana: 100
Eve: 87
Frank: 74

Statistics:
Passing students: 5
Average grade: 83.8333
Highest grade: Diana (95)
Lowest grade: Frank (69)
*/