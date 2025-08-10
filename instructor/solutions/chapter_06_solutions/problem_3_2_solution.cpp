// Problem 3.2 Solution: Debugging Template Errors
// Fixed version of the buggy template code with explanations

#include <iostream>
using namespace std;

template<typename T>
class Calculator {
private:
    T value;
public:
    Calculator(T initial) : value(initial) {}
    
    void add(T amount) {
        value += amount;
    }
    
    void print() {
        cout << "Result: " << value << endl;
    }
    
    // Fixed: Added proper template declaration for method outside class
    T getValue();
};

// Bug 1 Fix: Method definitions outside template classes need full template syntax
template<typename T>
T Calculator<T>::getValue() {  // Fixed: Added template<typename T> and Calculator<T>::
    return value;
}

// Bug 2 Fix: Template functions should only use operations available for all types
template<typename T>
void processValue(T val) {
    // Original problematic line: val.doSomething();  // Not all types have this method
    
    // Fixed version: Only use operations that work for the types we plan to use
    cout << "Processing value: " << val << endl;
    // If we need specific operations, we should either:
    // 1. Document type requirements clearly
    // 2. Use template specialization
    // 3. Use concepts (C++20) or SFINAE (advanced)
}

int main() {
    Calculator<int> calc(10);
    calc.add(5);
    calc.print();
    cout << "Final value: " << calc.getValue() << endl;
    
    // Bug 3 Fix: This now works because processValue only uses << operator
    processValue(42);  // Now works: int supports << operator
    
    // Additional tests to show the fixes work
    processValue(3.14);           // double works
    processValue(string("hello")); // string works
    
    // Test with different calculator types
    Calculator<double> calc_double(5.5);
    calc_double.add(2.3);
    calc_double.print();
    cout << "Double calculator value: " << calc_double.getValue() << endl;
    
    return 0;
}

/*
EXPLANATION OF BUGS AND FIXES:

Bug 1: "Template parameter not declared"
------
Original: T Calculator::getValue() { return value; }
Problem: Missing template declaration and class scope
Fixed: template<typename T> T Calculator<T>::getValue() { return value; }

Why: Template methods defined outside the class need:
- The template<typename T> declaration
- The full class name with template parameter: Calculator<T>::

Bug 2: "No matching member function"  
------
Original: val.doSomething();
Problem: Not all types have a doSomething() method
Fixed: cout << "Processing value: " << val << endl;

Why: Template functions can only use operations that work for ALL possible types.
The << operator works for int, double, string, etc., but doSomething() doesn't exist.

Bug 3: Compilation error from Bug 2
------
Original: processValue(42); would fail because of Bug 2
Fixed: Now works because we only use << operator

Why: Once we fixed the template to only use valid operations, it works with any
type that supports the << operator.

Expected Output:
Result: 15
Final value: 15
Processing value: 42
Processing value: 3.14
Processing value: hello
Result: 7.8
Double calculator value: 7.8

Key Debugging Lessons:
1. Template methods outside class need full template syntax
2. Only use operations that work for all intended types
3. Template error messages are verbose but usually point to the exact problem
4. Read the first error carefully - later errors often cascade from the first
5. Test templates with multiple types to catch type-specific issues
*/