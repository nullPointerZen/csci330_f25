#include <iostream>
#include <cstdio>

// Basic arithmetic functions
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
    if (b == 0.0) {
        std::cout << "Error: Division by zero!" << std::endl;
        return 0.0;  // Or throw an exception in real code
    }
    return a / b;
}

int main() {
    // Array of function pointers
    double (*operations[])(double, double) = {add, subtract, multiply, divide};
    const char* op_names[] = {"Add", "Subtract", "Multiply", "Divide"};
    const char* op_symbols[] = {"+", "-", "*", "/"};
    
    double a, b;
    int choice;
    
    std::cout << "Function Pointer Calculator" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Enter two numbers: ";
    std::cin >> a >> b;
    
    std::cout << "\nSelect operation:" << std::endl;
    for(int i = 0; i < 4; i++) {
        std::cout << i + 1 << ". " << op_names[i] << std::endl;
    }
    std::cout << "Choice: ";
    std::cin >> choice;
    
    // Validate choice
    if (choice < 1 || choice > 4) {
        std::cout << "Invalid choice! Please select 1-4." << std::endl;
        return 1;
    }
    
    // Call the selected function through function pointer
    int index = choice - 1;
    double result = operations[index](a, b);
    
    // Display result (only if not division by zero)
    if (!(index == 3 && b == 0.0)) {
        std::cout << std::endl;
        std::cout << a << " " << op_symbols[index] << " " << b << " = " << result << std::endl;
    }
    
    return 0;
}

/* Sample Output:
Function Pointer Calculator
==========================
Enter two numbers: 15 3

Select operation:
1. Add
2. Subtract
3. Multiply
4. Divide
Choice: 4

15 / 3 = 5

---

Function Pointer Calculator
==========================
Enter two numbers: 10 0

Select operation:
1. Add
2. Subtract
3. Multiply
4. Divide
Choice: 4
Error: Division by zero!
*/