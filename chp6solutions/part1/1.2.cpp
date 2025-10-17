#include <iostream>
#include <type_traits>

template <typename T1, typename T2>
auto safe_divide(T1 numerator, T2 denominator) -> decltype(numerator / denominator) {
    if (denominator == 0) {
        return static_cast<decltype(numerator / denominator)>(0);
    }
    return numerator / denominator;
}

int main() {
    std::cout << "10 / 2 = " << safe_divide(10, 2) << std::endl;
    std::cout << "10.5 / 2 = " << safe_divide(10.5, 2) << std::endl;
    std::cout << "10 / 0 = " << safe_divide(10, 0) << std::endl;
    std::cout << "10.0 / 0 = " << safe_divide(10.0, 0) << std::endl;
    std::cout << "10 / 2.5 = " << safe_divide(10, 2.5) << std::endl;

    return 0;
}