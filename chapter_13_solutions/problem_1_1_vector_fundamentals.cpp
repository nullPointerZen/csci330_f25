/*
 * Problem 1.1: Vector Fundamentals - Grade Management System
 * 
 * This solution demonstrates basic vector operations similar to Python lists.
 * 
 * Python equivalent:
 * grades = []
 * grades.append(85.5)
 * average = sum(grades) / len(grades)
 * highest = max(grades)
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>

int main() {
    // 1. Declare a vector to store student grades (like Python: grades = [])
    std::vector<double> grades;
    
    // 2. Add at least 5 grades using push_back (like Python: grades.append())
    grades.push_back(85.5);
    grades.push_back(92.0);
    grades.push_back(78.5);
    grades.push_back(96.5);
    grades.push_back(88.0);
    grades.push_back(91.5);  // Adding a 6th grade for good measure
    
    std::cout << "Grade Management System\n";
    std::cout << "======================\n";
    
    // Display all grades with their positions
    std::cout << "Grades entered:\n";
    for (size_t i = 0; i < grades.size(); ++i) {
        std::cout << "Grade " << (i + 1) << ": " << grades[i] << std::endl;
    }
    
    // 3. Calculate and display the average grade
    // Using std::accumulate (like Python: sum(grades) / len(grades))
    double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
    double average = sum / grades.size();
    
    std::cout << "\nStatistics:\n";
    std::cout << "Number of grades: " << grades.size() << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average grade: " << average << std::endl;
    
    // 4. Find and display the highest grade
    // Using std::max_element (like Python: max(grades))
    auto max_it = std::max_element(grades.begin(), grades.end());
    if (max_it != grades.end()) {
        std::cout << "Highest grade: " << *max_it << std::endl;
        
        // Show position of highest grade (bonus)
        size_t max_position = std::distance(grades.begin(), max_it);
        std::cout << "Position of highest grade: " << (max_position + 1) << std::endl;
    }
    
    // Find lowest grade too (bonus feature)
    auto min_it = std::min_element(grades.begin(), grades.end());
    if (min_it != grades.end()) {
        std::cout << "Lowest grade: " << *min_it << std::endl;
    }
    
    // 5. Demonstrate both [] operator and at() method
    std::cout << "\nAccess Methods Demonstration:\n";
    
    // Using [] operator (fast, no bounds checking)
    std::cout << "First grade using []: " << grades[0] << std::endl;
    std::cout << "Last grade using []: " << grades[grades.size() - 1] << std::endl;
    
    // Using at() method (bounds checked, throws exception if out of bounds)
    try {
        std::cout << "First grade using at(): " << grades.at(0) << std::endl;
        std::cout << "Second grade using at(): " << grades.at(1) << std::endl;
        
        // This would throw an exception if uncommented:
        // std::cout << "Invalid access: " << grades.at(100) << std::endl;
        
    } catch (const std::out_of_range& e) {
        std::cout << "Out of range error: " << e.what() << std::endl;
    }
    
    // Bonus: Show different ways to iterate (like Python for loops)
    std::cout << "\nIteration Methods:\n";
    
    // Range-based for loop (C++11) - most Pythonic
    std::cout << "Range-based for: ";
    for (const auto& grade : grades) {
        std::cout << grade << " ";
    }
    std::cout << std::endl;
    
    // Traditional for loop with index
    std::cout << "Index-based for: ";
    for (size_t i = 0; i < grades.size(); ++i) {
        std::cout << grades[i] << " ";
    }
    std::cout << std::endl;
    
    // Iterator-based (more advanced)
    std::cout << "Iterator-based: ";
    for (auto it = grades.begin(); it != grades.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    return 0;
}

/*
 * Expected Output:
 * Grade Management System
 * ======================
 * Grades entered:
 * Grade 1: 85.5
 * Grade 2: 92
 * Grade 3: 78.5
 * Grade 4: 96.5
 * Grade 5: 88
 * Grade 6: 91.5
 * 
 * Statistics:
 * Number of grades: 6
 * Average grade: 88.67
 * Highest grade: 96.50
 * Position of highest grade: 4
 * Lowest grade: 78.50
 * 
 * Access Methods Demonstration:
 * First grade using []: 85.50
 * Last grade using []: 91.50
 * First grade using at(): 85.50
 * Second grade using at(): 92.00
 * 
 * Iteration Methods:
 * Range-based for: 85.5 92 78.5 96.5 88 91.5 
 * Index-based for: 85.5 92 78.5 96.5 88 91.5 
 * Iterator-based: 85.5 92 78.5 96.5 88 91.5 
 * 
 * Learning Points:
 * 1. Vector is like Python list but with explicit types
 * 2. push_back() is like Python's append()
 * 3. size() is like Python's len()
 * 4. STL algorithms (accumulate, max_element) replace manual loops
 * 5. Range-based for loops are the most readable (like Python for loops)
 * 6. at() provides bounds checking, [] is faster but unsafe
 */