// Problem 1.2 Solution: Type Conversion Traps
// Understanding and fixing implicit type conversion issues

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // Bug 1: Integer division problem
    // PROBLEM: Integer division truncates the result
    int total_items = 17;
    int groups = 5;
    
    // WRONG: This gives 3.0 instead of 3.4
    // double average = total_items / groups;
    
    // FIXED: Cast at least one operand to double
    double average = static_cast<double>(total_items) / groups;
    cout << "Average (fixed): " << average << endl;  // Now gives 3.4
    
    // Alternative fixes:
    double average2 = total_items / static_cast<double>(groups);
    double average3 = static_cast<double>(total_items) / static_cast<double>(groups);
    double average4 = 17.0 / groups;  // Using literal
    
    // Bug 2: Signed/unsigned comparison
    // PROBLEM: When comparing signed and unsigned, signed value gets converted
    // to unsigned, causing -1 to become a very large positive number
    int signed_value = -1;
    unsigned int unsigned_value = 1;
    
    cout << "\nSigned/unsigned comparison bug demonstration:" << endl;
    cout << "signed_value: " << signed_value << endl;
    cout << "unsigned_value: " << unsigned_value << endl;
    
    // WRONG: This comparison is dangerous
    if (signed_value < unsigned_value) {
        cout << "WRONG: This might not print when you expect!" << endl;
    } else {
        cout << "WRONG: -1 appears greater than 1 due to conversion!" << endl;
    }
    
    // FIXED: Cast to same type for comparison
    if (signed_value < static_cast<int>(unsigned_value)) {
        cout << "FIXED: -1 is correctly less than 1" << endl;
    }
    
    // Alternative: Cast signed to unsigned if you know it's positive
    if (signed_value >= 0 && static_cast<unsigned int>(signed_value) < unsigned_value) {
        cout << "Alternative fix with safety check" << endl;
    }
    
    // Bug 3: Loss of precision when converting to int
    // PROBLEM: Direct cast to int truncates, doesn't round
    double precise_value = 3.99999;
    
    // WRONG: This truncates to 3
    // int truncated = static_cast<int>(precise_value);
    
    // FIXED: Use round function first
    int rounded = static_cast<int>(std::round(precise_value));
    cout << "\nRounded value should be 4, got: " << rounded << endl;
    
    // Show the difference
    int truncated = static_cast<int>(precise_value);
    cout << "Truncated (wrong): " << truncated << endl;
    cout << "Rounded (correct): " << rounded << endl;
    
    // Additional examples
    cout << "\nMore rounding examples:" << endl;
    cout << "round(2.3) = " << static_cast<int>(std::round(2.3)) << endl;
    cout << "round(2.7) = " << static_cast<int>(std::round(2.7)) << endl;
    cout << "round(-2.3) = " << static_cast<int>(std::round(-2.3)) << endl;
    cout << "round(-2.7) = " << static_cast<int>(std::round(-2.7)) << endl;
    
    return 0;
}

/*
Expected Output:
Average (fixed): 3.4
Signed/unsigned comparison bug demonstration:
signed_value: -1
unsigned_value: 1
WRONG: -1 appears greater than 1 due to conversion!
FIXED: -1 is correctly less than 1
Rounded value should be 4, got: 4
Truncated (wrong): 3
Rounded (correct): 4
More rounding examples:
round(2.3) = 2
round(2.7) = 3
round(-2.3) = -2
round(-2.7) = -3

Key Learning Points:
1. Integer division truncates - cast to double for real division
2. Signed/unsigned comparison can give unexpected results
3. Use static_cast for explicit, safe conversions
4. Use std::round() when you want rounding instead of truncation
5. Always be explicit about type conversions in C++
*/