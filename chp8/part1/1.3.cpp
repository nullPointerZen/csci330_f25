#include <iostream>
#include <vector>

int main() {
    std::vector<double> temperatures = {68.5, 72.1, 69.8, 74.2, 71.5, 73.0, 70.2};

    // Display all temperatures
    std::cout << "Original temperatures:\n";
    for (double temp : temperatures) {
        std::cout << temp << " ";
    }
    std::cout << "\n";

    // Calculate average
    double sum = 0.0;
    for (double temp : temperatures) {
        sum += temp;
    }
    double average = sum / temperatures.size();
    std::cout << "Average temperature: " << average << "\n";

    // Count temperatures above average
    int countAbove = 0;
    for (double temp : temperatures) {
        if (temp > average) {
            ++countAbove;
        }
    }
    std::cout << "Temperatures above average: " << countAbove << "\n";

    // Add 2.0 to all temperatures
    for (double& temp : temperatures) {
        temp += 2.0;
    }

    // Display modified temperatures
    std::cout << "Modified temperatures (+2.0):\n";
    for (double temp : temperatures) {
        std::cout << temp << " ";
    }
    std::cout << "\n";

    return 0;
}