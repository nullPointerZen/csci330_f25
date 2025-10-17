#include <iostream>

template <typename T>
T absolute_value(T value) {
    return (value < 0) ? -value : value;
}

int main() {
    std::cout << "absolute_value(-5) = " << absolute_value(-5) << std::endl;
    std::cout << "absolute_value(-3.14) = " << absolute_value(-3.14) << std::endl;
    std::cout << "absolute_value(42) = " << absolute_value(42) << std::endl;

    return 0;
}