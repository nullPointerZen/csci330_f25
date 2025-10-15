#include <cstdio>

int main() {
    int shared_value = 50;

    // Create two different references to shared_value
    int& ref1 = shared_value;
    int& ref2 = shared_value;

    // Modify shared_value through the first reference
    ref1 = 75;

    // Print the value using the second reference
    std::printf("ref2 = %d\n", ref2);

    // Show that all three (original + 2 references) have the same value
    std::printf("shared_value = %d\n", shared_value);
    std::printf("ref1 = %d\n", ref1);
    std::printf("ref2 = %d\n", ref2);

    return 0;
}