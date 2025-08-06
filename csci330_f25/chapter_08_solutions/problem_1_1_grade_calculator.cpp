/**
 * Problem 1.1: Grade Calculator with Switch Statement
 * 
 * Demonstrates:
 * - Switch statement usage with ranges
 * - Input validation
 * - Proper break statement placement
 * - Error handling without exceptions
 */

#include <iostream>
#include <limits>

int main() {
    int grade;
    
    std::cout << "Enter numeric grade (0-100): ";
    
    // Input validation
    if (!(std::cin >> grade)) {
        std::cout << "Error: Please enter a valid number" << std::endl;
        return 1;
    }
    
    // Range validation
    if (grade < 0 || grade > 100) {
        std::cout << "Error: Grade must be between 0 and 100" << std::endl;
        return 1;
    }
    
    // Convert to letter grade using switch with calculated ranges
    // We divide by 10 to get decade (0-10), then handle special case for 100
    int decade = (grade == 100) ? 10 : grade / 10;
    
    char letter_grade;
    std::string description;
    
    switch (decade) {
        case 10:  // 100
        case 9:   // 90-99
            letter_grade = 'A';
            description = "Excellent";
            break;
            
        case 8:   // 80-89
            letter_grade = 'B';
            description = "Good";
            break;
            
        case 7:   // 70-79
            letter_grade = 'C';
            description = "Average";
            break;
            
        case 6:   // 60-69
            letter_grade = 'D';
            description = "Below Average";
            break;
            
        default:  // 0-59
            letter_grade = 'F';
            description = "Failing";
            break;
    }
    
    std::cout << "Grade: " << letter_grade << " (" << description << ")" << std::endl;
    
    return 0;
}