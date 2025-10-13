#include <iostream>
#include <climits>
#include <cfloat>
#include <iomanip>

int main() {
    std::cout << "=== C++ Type System Analysis ===\n\n";

    // Part A: Basic Type Analysis (30 minutes)
    std::cout << "Fundamental Types:\n";
    std::cout << "------------------\n";

    // Declare and initialize variables of each fundamental type
    int myInt = 42;
    double myDouble = 3.14159;
    char myChar = 'A';
    bool myBool = true;
    long myLong = 2147483647L;
    float myFloat = 3.14f;

    // Display sizes and basic info
    std::cout << "int: " << myInt << " (size: " << sizeof(int) << " bytes)\n";
    std::cout << "double: " << myDouble << " (size: " << sizeof(double) << " bytes)\n";
    std::cout << "char: '" << myChar << "' (size: " << sizeof(char) << " byte)\n";
    std::cout << "bool: " << std::boolalpha << myBool << " (size: " << sizeof(bool) << " byte)\n";
    std::cout << "long: " << myLong << " (size: " << sizeof(long) << " bytes)\n";
    std::cout << "float: " << myFloat << " (size: " << sizeof(float) << " bytes)\n\n";

    // Show some ranges
    std::cout << "Type Ranges:\n";
    std::cout << "int range: " << INT_MIN << " to " << INT_MAX << "\n";
    std::cout << "char ASCII: " << static_cast<int>(myChar) << "\n\n";

    // Type Conversions
    std::cout << "Type Conversions:\n";
    std::cout << "-----------------\n";

    // Implicit conversions
    double intToDouble = myInt;
    int doubleToInt = myDouble;
    int charToInt = myChar;

    std::cout << "int(" << myInt << ") -> double: " << intToDouble << "\n";
    std::cout << "double(" << myDouble << ") -> int: " << doubleToInt << " (precision lost!)\n";
    std::cout << "char('" << myChar << "') -> int: " << charToInt << " (ASCII value)\n";

    // Explicit casting
    double preciseValue = 3.99;
    int truncated = static_cast<int>(preciseValue);
    std::cout << "static_cast<int>(" << preciseValue << ") = " << truncated << "\n\n";

    // Part B: Simple Unit Converter (30 minutes)
    std::cout << "Temperature Converter:\n";
    std::cout << "----------------------\n";

    double celsius = 25.0;
    double fahrenheit = (celsius * 9.0/5.0) + 32.0;
    double kelvin = celsius + 273.15;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << celsius << "°C = " << fahrenheit << "°F = " << kelvin << "K\n";

    // Show integer vs floating-point arithmetic
    int intCelsius = 25;
    int wrongFahrenheit = (intCelsius * 9/5) + 32;  // Integer division problem
    double rightFahrenheit = (intCelsius * 9.0/5.0) + 32;

    std::cout << "\nInteger vs Floating arithmetic:\n";
    std::cout << intCelsius << "°C with integer math: " << wrongFahrenheit << "°F (WRONG!)\n";
    std::cout << intCelsius << "°C with floating math: " << rightFahrenheit << "°F (correct)\n\n";

    // Distance conversion
    std::cout << "Distance Converter:\n";
    std::cout << "-------------------\n";
    double miles = 5.0;
    double kilometers = miles * 1.60934;
    std::cout << miles << " miles = " << kilometers << " km\n\n";

    // Part C: Basic Scope Demonstration
    std::cout << "Scope and Initialization:\n";
    std::cout << "-------------------------\n";

    int globalScope = 100;
    std::cout << "Outer scope variable: " << globalScope << "\n";

    {
        int localScope = 200;
        std::cout << "Inner scope variable: " << localScope << "\n";

        // Variable shadowing
        int globalScope = 300;  // Shadows outer variable
        std::cout << "Shadowed variable: " << globalScope << "\n";
    }

    std::cout << "Back to outer scope: " << globalScope << "\n";

    return 0;
}