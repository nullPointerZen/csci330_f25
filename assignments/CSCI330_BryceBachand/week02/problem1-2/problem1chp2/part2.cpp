#include <iostream>
#include <iomanip>
#include <climits>
#include <cfloat>

void typeAnalysis() {
    std::cout << "=== C++ Type System Analysis ===\n";

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
    double i_to_d = i;
    int d_to_i = d;
    int c_to_i = c;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "  int(" << i << ") -> double: " << i_to_d << " (no loss)\n";
    std::cout << "  double(" << d << ") -> int: " << d_to_i << " (precision lost!)\n";
    std::cout << "  char('" << c << "') -> int: " << c_to_i << " (ASCII value)\n";

    std::cout << "\nExplicit vs Implicit:\n";
    double implicit_sum = i + d;
    int explicit_cast = static_cast<int>(d);
    std::cout << "  Implicit: " << i << " + " << d << " = " << implicit_sum << " (int promoted to double)\n";
    std::cout << "  Explicit: static_cast<int>(" << d << ") = " << explicit_cast << "\n";

    std::cout << "\nInformation Loss in Narrowing Conversions:\n";
    double big_double = 1e10;
    int narrowed = static_cast<int>(big_double);
    std::cout << "  double(" << big_double << ") -> int: " << narrowed << " (overflow risk!)\n";
}

void temperatureConversions(int celsius) {
    std::cout << "\n=== Temperature Conversions ===\n";
    std::cout << "Input (int): " << celsius << "°C\n";

    double fahrenheit_fp = celsius * 9.0 / 5.0 + 32.0;
    double kelvin_fp = celsius + 273.15;

    int fahrenheit_int = celsius * 9 / 5 + 32;
    int kelvin_int = celsius + 273;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Floating-point: " << celsius << "°C = " << fahrenheit_fp << "°F, " << kelvin_fp << "K\n";
    std::cout << "Integer math:   " << celsius << "°C = " << fahrenheit_int << "°F, " << kelvin_int << "K (precision lost!)\n";
}

void distanceConversions(int miles, int feet) {
    std::cout << "\n=== Distance Conversions ===\n";

    double km_fp = miles * 1.60934;
    double m_fp = miles * 1609.34;

    int km_int = miles * 1;
    int m_int = miles * 1609;

    std::cout << "Miles input (int): " << miles << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Floating-point: " << miles << " mi = " << km_fp << " km, " << m_fp << " m\n";
    std::cout << "Integer math:   " << miles << " mi = " << km_int << " km, " << m_int << " m (precision lost!)\n";

    double meters_fp = feet * 0.3048;
    double inches_fp = feet * 12.0;

    int meters_int = feet * 0;
    int inches_int = feet * 12;

    std::cout << "\nFeet input (int): " << feet << "\n";
    std::cout << "Floating-point: " << feet << " ft = " << meters_fp << " m, " << inches_fp << " in\n";
    std::cout << "Integer math:   " << feet << " ft = " << meters_int << " m, " << inches_int << " in (precision lost!)\n";
}

int main() {
    typeAnalysis();

    // Conversion test cases
    temperatureConversions(25);   // Room temperature
    temperatureConversions(-10);  // Cold day

    distanceConversions(5, 6);    // 5 miles, 6 feet
    distanceConversions(0, 100);  // 0 miles, 100 feet

    return 0;
}