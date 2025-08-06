// Problem 1.3 Solution: Template Argument Deduction
// swap function template demonstrating both explicit and deduced usage

#include <iostream>
#include <string>
using namespace std;

template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    // Test with integers using automatic deduction
    int x = 10, y = 20;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swap(x, y);  // Template argument deduction
    cout << "After swap: x = " << x << ", y = " << y << endl;
    cout << endl;
    
    // Test with doubles using explicit template arguments
    double a = 3.14, b = 2.71;
    cout << "Before swap: a = " << a << ", b = " << b << endl;
    swap<double>(a, b);  // Explicit template argument
    cout << "After swap: a = " << a << ", b = " << b << endl;
    cout << endl;
    
    // Test with strings using automatic deduction
    string first = "hello", second = "world";
    cout << "Before swap: first = \"" << first << "\", second = \"" << second << "\"" << endl;
    swap(first, second);  // Template argument deduction
    cout << "After swap: first = \"" << first << "\", second = \"" << second << "\"" << endl;
    cout << endl;
    
    // Demonstrate that both approaches work the same way
    char c1 = 'A', c2 = 'Z';
    cout << "Before swap: c1 = " << c1 << ", c2 = " << c2 << endl;
    swap<char>(c1, c2);  // Explicit (unnecessary but valid)
    cout << "After explicit swap: c1 = " << c1 << ", c2 = " << c2 << endl;
    swap(c1, c2);        // Deduced (back to original)
    cout << "After deduced swap: c1 = " << c1 << ", c2 = " << c2 << endl;
    
    return 0;
}

/*
Expected Output:
Before swap: x = 10, y = 20
After swap: x = 20, y = 10

Before swap: a = 3.14, b = 2.71
After swap: a = 2.71, b = 3.14

Before swap: first = "hello", second = "world"
After swap: first = "world", second = "hello"

Before swap: c1 = A, c2 = Z
After explicit swap: c1 = Z, c2 = A
After deduced swap: c1 = A, c2 = Z

Key Learning Points:
1. Template argument deduction: swap(a, b) - compiler figures out type
2. Explicit template arguments: swap<int>(a, b) - you specify type
3. Both approaches produce identical results
4. References are essential for swapping (T& parameters)
5. Works with any type that supports copy construction and assignment
*/