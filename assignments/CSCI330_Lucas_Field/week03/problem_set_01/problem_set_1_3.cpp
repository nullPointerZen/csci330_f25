// Template provided:
#include <cstdio>

int main() {
    int shared_value = 50;
    
    // TODO: Create two different references to shared_value
    int& ref_shared = shared_value;
    int& ref_other_shared = shared_value;
    // TODO: Modify shared_value through the first reference
    ref_shared = 60;
    // TODO: Print the value using the second reference
    printf("Second Reference Value: %d\n", ref_other_shared);
    // TODO: Show that all three (original + 2 references) have the same value
    printf("Original Value: %d\n1st Reference: %d\n2nd Reference: %d\n", shared_value, ref_shared, ref_other_shared);
    
    return 0;
}
