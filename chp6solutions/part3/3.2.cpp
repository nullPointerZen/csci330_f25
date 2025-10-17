#include <iostream>
using namespace std;

// Template class definition
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

    // Declaration of getValue
    T getValue();
};

// ✅ Bug 1 Fix: Proper template syntax for method definition outside the class
template<typename T>
T Calculator<T>::getValue() {
    return value;
}

// ✅ Bug 2 Fix: Use SFINAE or static_assert to restrict usage, or remove unsafe call
template<typename T>
void processValue(T val) {
    cout << "Processing value: " << val << endl;
    // Removed val.doSomething(); — not all types support this
}

int main() {
    Calculator<int> calc(10);
    calc.add(5);
    calc.print();
    cout << "Final value: " << calc.getValue() << endl;

    // ✅ Bug 3 Fix: Now safe — no invalid method call
    processValue(42);

    return 0;
}