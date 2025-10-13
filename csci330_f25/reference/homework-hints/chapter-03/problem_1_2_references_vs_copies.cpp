#include <cstdio>

int main() {
    int original = 100;
    
    // Create a copy of original called 'copy_val'
    int copy_val = original;
    
    // Create a reference to original called 'ref_val'
    int& ref_val = original;
    
    // Modify original to 200
    original = 200;
    
    // Print all three values to show the difference
    printf("Original: %d, Copy: %d, Reference: %d\n", original, copy_val, ref_val);
    
    return 0;
}