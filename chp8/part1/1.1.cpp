#include <iostream>

int main() {
    std::cout << "Enter numeric grade (0-100): ";
    int grade;
    std::cin >> grade;

    // Validate input
    if (grade < 0 || grade > 100) {
        std::cout << "Invalid input. Grade must be between 0 and 100.\n";
        return 1;
    }

    // Convert to letter grade using switch
    char letter;
    switch (grade / 10) {
        case 10: // for grade == 100
        case 9:
            letter = 'A';
            break;
        case 8:
            letter = 'B';
            break;
        case 7:
            letter = 'C';
            break;
        case 6:
            letter = 'D';
            break;
        default:
            letter = 'F';
            break;
    }

    // Print result
    std::cout << "Letter grade: " << letter << "\n";

    return 0;
}