#include <cstdio>

int main() {
    int shared_value = 50;
    
    // Create two different references to shared_value
    int& first_ref = shared_value;
    int& second_ref = shared_value;
    
    // Modify shared_value through the first reference
    first_ref = 75;
    
    // Print the value using the second reference
    printf("Value accessed through second_ref: %d\n", second_ref);
    
    // Show that all three (original + 2 references) have the same value
    printf("shared_value: %d, first_ref: %d, second_ref: %d\n", 
           shared_value, first_ref, second_ref);
    
    return 0;
}