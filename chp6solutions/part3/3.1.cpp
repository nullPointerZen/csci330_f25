#include <iostream>
#include <string>
using namespace std;

// General template
template<typename T>
class Printer {
public:
    static void print(const T& value) {
        cout << "Value: " << value << endl;
    }
};

// Specialization for bool
template<>
class Printer<bool> {
public:
    static void print(const bool& value) {
        cout << "Boolean: " << (value ? "true" : "false") << endl;
    }
};

// Specialization for string
template<>
class Printer<string> {
public:
    static void print(const string& value) {
        cout << "Text: " << value << endl;
    }
};

int main() {
    Printer<int>::print(42);           // General template
    Printer<bool>::print(true);        // Specialized for bool
    Printer<string>::print("hello world"); // Specialized for string
    Printer<double>::print(3.14);      // General template

    return 0;
}