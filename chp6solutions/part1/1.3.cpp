#include <iostream>

// 1. Absolute Value Template
template <typename T>
T absolute_value(T value) {
    return (value < 0) ? -value : value;
}

// 2. Safe Divide Template (handles mixed types and division by zero)
template <typename T1, typename T2>
auto safe_divide(T1 numerator, T2 denominator) -> decltype(numerator / denominator) {
    if (denominator == 0) {
        return static_cast<decltype(numerator / denominator)>(0);
    }
    return numerator / denominator;
}

// 3. Swap Template (modifies original variables)
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    // Test absolute_value
    std::cout << "absolute_value(-5) = " << absolute_value(-5) << std::endl;
    std::cout << "absolute_value(-3.14) = " << absolute_value(-3.14) << std::endl;
    std::cout << "absolute_value(42) = " << absolute_value(42) << std::endl;

    std::cout << std::endl;

    // Test safe_divide
    std::cout << "10 / 2 = " << safe_divide(10, 2) << std::endl;
    std::cout << "10.5 / 2 = " << safe_divide(10.5, 2) << std::endl;
    std::cout << "10 / 0 = " << safe_divide(10, 0) << std::endl;

    std::cout << std::endl;

    // Test swap with explicit and automatic deduction
    int x = 1, y = 2;
    double p = 3.14, q = 2.71;

    std::cout << "Before swap<int>: x = " << x << ", y = " << y << std::endl;
    swap<int>(x, y);  // Explicit template argument
    std::cout << "After swap<int>: x = " << x << ", y = " << y << std::endl;

    std::cout << "\nBefore swap: p = " << p << ", q = " << q << std::endl;
    swap(p, q);       // Automatic type deduction
    std::cout << "After swap: p = " << p << ", q = " << q << std::endl;

    return 0;
}