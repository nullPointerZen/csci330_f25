#include <iostream>

int main() {
    int size;
    char mode;

    std::cout << "Enter pattern size (1-10): ";
    std::cin >> size;

    // Validate size input
    if (size < 1 || size > 10) {
        std::cout << "Invalid size. Must be between 1 and 10.\n";
        return 1;
    }

    std::cout << "Show all rows (a) or odd rows only (o)? ";
    std::cin >> mode;

    // Validate mode input
    if (mode != 'a' && mode != 'o') {
        std::cout << "Invalid mode. Enter 'a' for all or 'o' for odd only.\n";
        return 1;
    }

    // Generate pattern
    for (int row = 1; row <= size; ++row) {
        if (mode == 'o' && row % 2 == 0) {
            continue; // Skip even rows in odd-only mode
        }

        for (int num = 1; num <= row; ++num) {
            std::cout << num;
        }
        std::cout << "\n";
    }

    return 0;
}