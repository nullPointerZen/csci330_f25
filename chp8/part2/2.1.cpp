#include <iostream>
#include <stdexcept>
#include <limits> // for std::numeric_limits

double safe_divide(double numerator, double denominator) {
    if (denominator == 0.0) {
        throw std::runtime_error("Division by zero is not allowed");
    }
    return numerator / denominator;
}

int main() {
    double a, b;
    char operation;

    while (true) {
        std::cout << "Enter calculation (a op b) or 'q' to quit: ";

        if (!(std::cin >> a >> operation)) {
            if (std::cin.eof()) break;

            std::cin.clear(); // clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Error: Invalid input format\n";
            continue;
        }

        if (operation == 'q') break;

        if (!(std::cin >> b)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Invalid input format\n";
            continue;
        }

        try {
            double result;
            switch (operation) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = safe_divide(a, b);
                    break;
                default:
                    throw std::invalid_argument("Unsupported operation");
            }
            std::cout << "Result: " << result << "\n";
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << "\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Error: Unknown exception occurred\n";
        }
    }

    return 0;
}