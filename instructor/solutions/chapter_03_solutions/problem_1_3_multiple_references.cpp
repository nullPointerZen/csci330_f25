// Problem 1.3: Multiple References
// Demonstrates multiple references pointing to the same object

#include <cstdio>

int main() {
    int shared_value = 50;
    
    // Create two different references to shared_value
    int& first_ref = shared_value;
    int& second_ref = shared_value;
    
    printf("Initial values:\n");
    printf("Original: %d, First Ref: %d, Second Ref: %d\n", 
           shared_value, first_ref, second_ref);
    
    // Modify shared_value through the first reference
    first_ref = 75;
    
    printf("After modifying through first reference:\n");
    printf("Original: %d, First Ref: %d, Second Ref: %d\n", 
           shared_value, first_ref, second_ref);
    
    // Print the value using the second reference
    printf("Value accessed through second reference: %d\n", second_ref);
    
    // Modify through second reference
    second_ref = 100;
    
    // Show that all three (original + 2 references) have the same value
    printf("After modifying through second reference:\n");
    printf("Original: %d, First Ref: %d, Second Ref: %d\n", 
           shared_value, first_ref, second_ref);
    
    // Verify they all point to the same memory location
    printf("Memory addresses (should all be the same):\n");
    printf("Original: %p, First Ref: %p, Second Ref: %p\n", 
           &shared_value, &first_ref, &second_ref);
    
    return 0;
}