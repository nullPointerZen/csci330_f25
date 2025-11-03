#include <iostream>
#include <cstdio>

// Implement arithmetic functions
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        std::cerr << "Error: Division by zero!\n";
        return 0; // Return 0 or some sentinel value
    }
    return a / b;
}

int main() {
    // Array of function pointers
    double (*operations[])(double, double) = {add, subtract, multiply, divide};
    const char* op_names[] = {"Add", "Subtract", "Multiply", "Divide"};
    const char op_symbols[] = {'+', '-', '*', '/'};

    double a, b;
    int choice;

    std::cout << "Enter two numbers: ";
    std::cin >> a >> b;

    std::cout << "\nSelect operation:\n";
    for (int i = 0; i < 4; i++) {
        std::cout << i + 1 << ". " << op_names[i] << "\n";
    }
    std::cout << "Choice: ";
    std::cin >> choice;

    if (choice < 1 || choice > 4) {
        std::cerr << "Invalid choice!\n";
        return 1;
    }

    if (choice == 4 && b == 0) {
        divide(a, b); // Will print error
    } else {
        double result = operations[choice - 1](a, b);
        std::printf("%.2f %c %.2f = %.2f\n", a, op_symbols[choice - 1], b, result);
    }

    return 0;
}