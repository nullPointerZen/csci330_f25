// Problem 1.2 Solution: Multiple Template Parameters
// safe_divide function template with division by zero handling

#include <iostream>
using namespace std;

template<typename T1, typename T2>
auto safe_divide(T1 numerator, T2 denominator) -> decltype(numerator/denominator) {
    // Check for division by zero
    if (denominator == 0) {
        return 0;  // Return 0 for division by zero
    }
    return numerator / denominator;
}

int main() {
    cout << "10 / 2 = " << safe_divide(10, 2) << endl;
    cout << "10.5 / 2 = " << safe_divide(10.5, 2) << endl;
    cout << "10 / 0 = " << safe_divide(10, 0) << " (division by zero)" << endl;
    
    // Additional test cases showing mixed types
    cout << "15 / 3.0 = " << safe_divide(15, 3.0) << endl;
    cout << "9.6 / 3 = " << safe_divide(9.6, 3) << endl;
    cout << "0 / 5 = " << safe_divide(0, 5) << endl;
    cout << "7.5 / 0.0 = " << safe_divide(7.5, 0.0) << " (division by zero)" << endl;
    
    return 0;
}

/*
Expected Output:
10 / 2 = 5
10.5 / 2 = 5.25
10 / 0 = 0 (division by zero)
15 / 3.0 = 5
9.6 / 3 = 3.2
0 / 5 = 0
7.5 / 0.0 = 0 (division by zero)

Key Learning Points:
1. Multiple template parameters: T1, T2
2. auto return type with trailing return type
3. decltype determines the result type of the division
4. Mixed types work seamlessly (int/double, double/int)
5. Division by zero handling with simple comparison
*/