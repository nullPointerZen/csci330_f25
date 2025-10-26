#include <iostream>
#include <cmath>  // Needed for round()
using namespace std;

int main() {
    // Bug 1 Fixed: Integer division problem
    int total_items = 17;
    int groups = 5;
    double average = static_cast<double>(total_items) / groups;  // Now gives 3.4
    cout << "Average: " << average << endl;

    // Bug 2 Fixed: Signed/unsigned comparison
    int signed_value = -1;
    int unsigned_value = 1;  // Changed to int to avoid mismatch
    if (signed_value < unsigned_value) {
        cout << "This prints as expected!" << endl;
    }

    // Bug 3 Fixed: Loss of precision
    double precise_value = 3.99999;
    int rounded = static_cast<int>(round(precise_value));  // Proper rounding
    cout << "Rounded value should be 4, got: " << rounded << endl;

    return 0;
}