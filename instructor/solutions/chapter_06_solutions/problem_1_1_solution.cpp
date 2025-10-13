// Problem 1.1 Solution: Basic Function Templates
// absolute_value function template

#include <iostream>
using namespace std;

template<typename T>
T absolute_value(T value) {
    if (value < 0) {
        return -value;  // Return the negative of negative value
    }
    return value;       // Return positive value as-is
}

int main() {
    cout << "absolute_value(-5) = " << absolute_value(-5) << endl;
    cout << "absolute_value(-3.14) = " << absolute_value(-3.14) << endl;
    cout << "absolute_value(42) = " << absolute_value(42) << endl;
    
    // Additional test cases to show it works with different types
    cout << "absolute_value(-2.5f) = " << absolute_value(-2.5f) << endl;
    cout << "absolute_value(100) = " << absolute_value(100) << endl;
    
    return 0;
}

/*
Expected Output:
absolute_value(-5) = 5
absolute_value(-3.14) = 3.14
absolute_value(42) = 42
absolute_value(-2.5f) = 2.5
absolute_value(100) = 100

Key Learning Points:
1. Template syntax: template<typename T>
2. The compiler creates separate functions for each type used
3. The same logic works for int, double, float, etc.
4. Type deduction happens automatically
*/