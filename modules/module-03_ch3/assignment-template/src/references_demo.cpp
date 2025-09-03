// HW_03: References and Const Correctness
// Time: 2.25 hours (45 minutes per problem set)
// Topics: References, const correctness, auto keyword

#include <cstdio>
#include <cstring>

// ============================================================================
// PROBLEM SET 1: Basic References (45 minutes)
// ============================================================================

void problem_1_1_reference_fundamentals() {
    printf("=== Problem 1.1: Reference Fundamentals ===\n");
    
    // TODO 1: Create an integer variable 'score' with value 85
    int score = 85;
    
    // TODO 2: Create a reference 'score_ref' that refers to 'score'
    // int& score_ref = ...;
    
    // TODO 3: Print both score and score_ref
    printf("Original score: %d, Reference: [TODO]\n", score);
    
    // TODO 4: Modify score through score_ref to 92
    // score_ref = ...;
    
    // TODO 5: Print both values again to show they're the same
    printf("Modified score: %d, Reference: [TODO]\n", score);
    
    printf("\n");
}

void problem_1_2_references_vs_copies() {
    printf("=== Problem 1.2: References vs Copies ===\n");
    
    int original = 100;
    
    // TODO 6: Create a copy of original
    // int copy = ...;
    
    // TODO 7: Create a reference to original
    // int& ref = ...;
    
    // TODO 8: Modify the copy - should NOT affect original
    // copy = ...;
    
    // TODO 9: Modify through reference - SHOULD affect original
    // ref = ...;
    
    // TODO 10: Print all three to show the difference
    printf("Original: %d, Copy: [TODO], Reference: [TODO]\n", original);
    
    printf("\n");
}

void problem_1_3_multiple_references() {
    printf("=== Problem 1.3: Multiple References ===\n");
    
    int value = 42;
    
    // TODO 11: Create three references to the same variable
    // int& ref1 = ...;
    // int& ref2 = ...;
    // int& ref3 = ...;
    
    // TODO 12: Modify through ref1 and show all change
    // ref1 = 100;
    
    // TODO 13: Print addresses to show they're all the same object
    printf("Addresses - value: %p, ref1: [TODO], ref2: [TODO], ref3: [TODO]\n",
           (void*)&value);
    
    printf("\n");
}

// ============================================================================
// PROBLEM SET 2: Functions with References (45 minutes)
// ============================================================================

// TODO 14: Implement swap function using references
void swap_by_reference(int& a, int& b) {
    // TODO: Swap the values of a and b
    // Remember: No pointers needed!
}

// TODO 15: Implement swap using pointers for comparison
void swap_by_pointer(int* a, int* b) {
    // TODO: Swap using pointer dereferencing
}

// Large struct for demonstrating efficient parameter passing
struct LargeData {
    char description[1000];
    int values[100];
    double measurements[50];
};

// TODO 16: Function that takes large struct by value (inefficient)
void process_by_value(LargeData data) {
    // This copies the entire struct!
    printf("  Processing by value (size of parameter: %zu bytes)\n", sizeof(data));
    // TODO: Access and print first value
}

// TODO 17: Function that takes large struct by reference (efficient)
void process_by_reference(const LargeData& data) {
    // No copy - just an alias!
    printf("  Processing by reference (size of reference: %zu bytes)\n", sizeof(&data));
    // TODO: Access and print first value
}

// TODO 18: Function that returns a reference (careful!)
int& get_array_element(int array[], int index) {
    // TODO: Return reference to array element
    // WARNING: Make sure array outlives the reference!
    return array[0];  // Placeholder - fix this
}

void problem_2_functions_with_references() {
    printf("=== Problem Set 2: Functions with References ===\n");
    
    // Test swap functions
    printf("Swap Functions:\n");
    int x = 10, y = 20;
    printf("  Before swap: x=%d, y=%d\n", x, y);
    
    // TODO 19: Call swap_by_reference
    // swap_by_reference(x, y);
    printf("  After ref swap: x=%d, y=%d\n", x, y);
    
    // Reset and test pointer version
    x = 10; y = 20;
    // TODO 20: Call swap_by_pointer
    // swap_by_pointer(&x, &y);
    printf("  After ptr swap: x=%d, y=%d\n", x, y);
    
    // Test efficient parameter passing
    printf("\nEfficient Parameter Passing:\n");
    LargeData bigData;
    strcpy(bigData.description, "Large dataset");
    bigData.values[0] = 42;
    
    // TODO 21: Call both functions to compare
    // process_by_value(bigData);
    // process_by_reference(bigData);
    
    // Test reference return
    printf("\nReference Return:\n");
    int numbers[5] = {10, 20, 30, 40, 50};
    
    // TODO 22: Get reference to element and modify it
    // int& elem = get_array_element(numbers, 2);
    // elem = 999;
    printf("  Array after modification: [TODO: print array]\n");
    
    printf("\n");
}

// ============================================================================
// PROBLEM SET 3: Const Correctness and Auto (45 minutes)
// ============================================================================

// TODO 23: Function with const reference parameter
void print_data(const int& value) {
    printf("  Value: %d\n", value);
    // TODO: Try to modify value - should cause compilation error!
    // value = 100;  // Uncomment to see error
}

// TODO 24: Function that demonstrates const with references
void demonstrate_const_references() {
    printf("Const References:\n");
    
    int mutable_value = 42;
    const int const_value = 100;
    
    // TODO 25: Create const reference to mutable value
    // const int& const_ref = mutable_value;
    
    // TODO 26: Try to create non-const reference to const value
    // int& bad_ref = const_value;  // This should error!
    
    // TODO 27: Create const reference to const value
    // const int& good_ref = const_value;
    
    print_data(mutable_value);
    print_data(const_value);
}

// Class for demonstrating const member functions
class Counter {
private:
    int count;
    
public:
    Counter(int initial) : count(initial) {}
    
    // TODO 28: Const member function - doesn't modify object
    int get_count() const {
        // TODO: Return count
        return 0;  // Placeholder
    }
    
    // TODO 29: Non-const member function - can modify object
    void increment() {
        // TODO: Increment count
    }
    
    // TODO 30: Try to modify in const function - should error!
    void bad_const_function() const {
        // count++;  // Uncomment to see error
    }
};

// TODO 31: Demonstrate auto with references
void demonstrate_auto() {
    printf("Auto Type Deduction:\n");
    
    int value = 42;
    int& ref = value;
    const int& const_ref = value;
    
    // TODO 32: Use auto to deduce types
    // auto auto_value = value;        // Type: int (copy)
    // auto auto_ref = ref;           // Type: int (copy, not ref!)
    // auto& auto_ref2 = value;       // Type: int& (reference)
    // const auto& auto_const = value; // Type: const int&
    
    // TODO 33: Print types and values
    printf("  [TODO: Print deduced types and values]\n");
    
    // TODO 34: Show that auto drops reference by default
    // auto_value = 100;  // Doesn't affect original
    // auto_ref2 = 200;   // DOES affect original
    
    printf("  Original value after modifications: %d\n", value);
}

void problem_3_const_and_auto() {
    printf("=== Problem Set 3: Const Correctness and Auto ===\n");
    
    // Test const references
    demonstrate_const_references();
    printf("\n");
    
    // Test const member functions
    printf("Const Member Functions:\n");
    Counter counter(10);
    
    // TODO 35: Test const member function
    printf("  Count: %d\n", counter.get_count());
    
    // TODO 36: Test non-const member function
    counter.increment();
    printf("  After increment: %d\n", counter.get_count());
    
    printf("\n");
    
    // Test auto type deduction
    demonstrate_auto();
    
    printf("\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("   HW_03: References and Const Correctness\n");
    printf("==========================================\n\n");
    
    // Problem Set 1: Basic References (45 min)
    problem_1_1_reference_fundamentals();
    problem_1_2_references_vs_copies();
    problem_1_3_multiple_references();
    
    // Problem Set 2: Functions with References (45 min)
    problem_2_functions_with_references();
    
    // Problem Set 3: Const Correctness and Auto (45 min)
    problem_3_const_and_auto();
    
    printf("==========================================\n");
    printf("           Program Complete!\n");
    printf("==========================================\n");
    
    return 0;
}