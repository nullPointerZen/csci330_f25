// Problem 3.1 Solution: Template Specialization Introduction
// Printer template with specializations for different types

#include <iostream>
#include <string>
using namespace std;

// General template - works for most types
template<typename T>
class Printer {
public:
    static void print(const T& value) {
        cout << "Value: " << value << endl;
    }
};

// Specialization for bool type
template<>
class Printer<bool> {
public:
    static void print(const bool& value) {
        cout << "Boolean: " << (value ? "true" : "false") << endl;
    }
};

// Specialization for string type
template<>
class Printer<string> {
public:
    static void print(const string& value) {
        cout << "Text: " << value << endl;
    }
};

int main() {
    // Test with different types
    Printer<int>::print(42);
    Printer<bool>::print(true);
    Printer<bool>::print(false);
    Printer<string>::print("hello world");
    Printer<double>::print(3.14);
    
    cout << endl << "Additional tests:" << endl;
    
    // Test with more types to show the general template works
    Printer<float>::print(2.5f);
    Printer<char>::print('A');
    Printer<string>::print("C++ templates are powerful!");
    
    // Test variables instead of literals
    int number = 100;
    bool flag = false;
    string message = "Good job on templates!";
    double pi = 3.14159;
    
    cout << endl << "Testing with variables:" << endl;
    Printer<int>::print(number);
    Printer<bool>::print(flag);
    Printer<string>::print(message);
    Printer<double>::print(pi);
    
    return 0;
}

/*
Expected Output:
Value: 42
Boolean: true
Boolean: false
Text: hello world
Value: 3.14

Additional tests:
Value: 2.5
Value: A
Text: C++ templates are powerful!

Testing with variables:
Value: 100
Boolean: false
Text: Good job on templates!
Value: 3.14159

Key Learning Points:
1. Template specialization syntax: template<> class Printer<bool>
2. Specializations override the general template for specific types
3. Static methods work the same way in specialized templates
4. The compiler chooses the most specific template available
5. General template handles all unspecialized types (int, double, char, float)
6. Specializations can have completely different behavior
7. Each specialization is essentially a separate class definition
*/