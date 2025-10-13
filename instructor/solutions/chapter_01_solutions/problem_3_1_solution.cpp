// Problem 3.1: Calculator Functions Solution
// Demonstrates functions, parameters, and return values

#include <cstdio>

// Function to add two numbers
int add(int a, int b) {
    return a + b;
}

// Function to subtract two numbers  
int subtract(int a, int b) {
    return a - b;
}

// Function to multiply two numbers
int multiply(int a, int b) {
    return a * b;
}

// Function to divide with error checking
void divide(int a, int b) {
    if (b == 0) {
        printf("Error: Cannot divide by zero!\n");
    } else {
        printf("%d / %d = %d\n", a, b, a / b);
    }
}

int main() {
    // Test values
    int x = 10;
    int y = 3;
    
    // Test all operations
    printf("Calculator Testing:\n");
    printf("%d + %d = %d\n", x, y, add(x, y));
    printf("%d - %d = %d\n", x, y, subtract(x, y));
    printf("%d * %d = %d\n", x, y, multiply(x, y));
    divide(x, y);
    
    // Test division by zero
    printf("\nTesting division by zero:\n");
    divide(x, 0);
    
    return 0;
}

/*
Compilation: g++ -o calculator problem_3_1_solution.cpp

Expected Output:
Calculator Testing:
10 + 3 = 13
10 - 3 = 7
10 * 3 = 30
10 / 3 = 3

Testing division by zero:
Error: Cannot divide by zero!

Key Learning Points:
1. Functions take parameters and can return values
2. Function names should be descriptive (add, subtract, etc.)
3. Error checking prevents crashes (division by zero)
4. int division truncates decimal results (10/3 = 3, not 3.33)
5. Use void functions when you don't need to return a value
*/