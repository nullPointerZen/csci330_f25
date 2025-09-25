#include <iostream>
#include <climits>
#include <cfloat>
#include <iomanip>

int main() {
    std::cout << "=== C++ Type System Analysis ===\n";

    // Fundamental Type Declarations
    int i = 42;
    double d = 3.14159;
    char c = 'A';
    bool b = true;
    long l = -9876543210L;
    float f = -2.718f;

    std::cout << "Fundamental Types:\n";
    std::cout << "  int: " << i << " (size: " << sizeof(i) << " bytes, range: " << INT_MIN << " to " << INT_MAX << ")\n";
    std::cout << "  double: " << d << " (size: " << sizeof(d) << " bytes, precision: ~15-17 digits)\n";
    std::cout << "  char: '" << c << "' (size: " << sizeof(c) << " byte, ASCII: " << static_cast<int>(c) << ")\n";
    std::cout << "  bool: " << std::boolalpha << b << " (size: " << sizeof(b) << " byte, values: 0 or 1)\n";
    std::cout << "  long: " << l << " (size: " << sizeof(l) << " bytes, range: " << LONG_MIN << " to " << LONG_MAX << ")\n";
    std::cout << "  float: " << f << " (size: " << sizeof(f) << " bytes, precision: ~6-9 digits)\n";

    std::cout << "\nSigned Type Values:\n";
    std::cout << "  int: " << i << ", " << -i << "\n";
    std::cout << "  long: " << l << ", " << -l << "\n";
    std::cout << "  float: " << f << ", " << -f << "\n";
    std::cout << "  double: " << d << ", " << -d << "\n";

    std::cout << "\nType Conversions:\n";

    // Implicit conversions
    double i_to_d = i;
    int d_to_i = d;
    int c_to_i = c;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "  int(" << i << ") -> double: " << i_to_d << " (no loss)\n";
    std::cout << "  double(" << d << ") -> int: " << d_to_i << " (precision lost!)\n";
    std::cout << "  char('" << c << "') -> int: " << c_to_i << " (ASCII value)\n";

    std::cout << "\nExplicit vs Implicit:\n";

    // Implicit promotion
    double implicit_sum = i + d;
    std::cout << "  Implicit: " << i << " + " << d << " = " << implicit_sum << " (int promoted to double)\n";

    // Explicit cast
    int explicit_cast = static_cast<int>(d);
    std::cout << "  Explicit: static_cast<int>(" << d << ") = " << explicit_cast << "\n";

    std::cout << "\nInformation Loss in Narrowing Conversions:\n";
    double big_double = 1e10;
    int narrowed = static_cast<int>(big_double);
    std::cout << "  double(" << big_double << ") -> int: " << narrowed << " (overflow risk!)\n";

    return 0;
}