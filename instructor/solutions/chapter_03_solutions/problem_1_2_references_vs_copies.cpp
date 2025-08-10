// Problem 1.2: References vs Copies
// Demonstrates the difference between references and copies

#include <cstdio>

int main() {
    int original = 100;
    
    // Create a copy of original called 'copy_val'
    int copy_val = original;
    
    // Create a reference to original called 'ref_val'
    int& ref_val = original;
    
    printf("Before modification:\n");
    printf("Original: %d, Copy: %d, Reference: %d\n", original, copy_val, ref_val);
    
    // Modify original to 200
    original = 200;
    
    printf("After modifying original:\n");
    printf("Original: %d, Copy: %d, Reference: %d\n", original, copy_val, ref_val);
    
    // Demonstrate by modifying through reference
    ref_val = 300;
    
    printf("After modifying through reference:\n");
    printf("Original: %d, Copy: %d, Reference: %d\n", original, copy_val, ref_val);
    
    return 0;
}