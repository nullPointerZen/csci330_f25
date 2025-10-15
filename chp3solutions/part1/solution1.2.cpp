#include <cstdio>

int main() {
    // Create an integer variable 'original' with value 100
    int original = 100;

    // Create a copy of original called 'copy_val'
    int copy_val = original;

    // Create a reference to original called 'ref_val'
    int& ref_val = original;

    // Modify original to 200
    original = 200;

    // Print all three values to show the difference
    std::printf("original = %d\n", original);   // 200
    std::printf("copy_val = %d\n", copy_val);   // 100 (unchanged)
    std::printf("ref_val = %d\n", ref_val);     // 200 (reflects original)

    return 0;
}