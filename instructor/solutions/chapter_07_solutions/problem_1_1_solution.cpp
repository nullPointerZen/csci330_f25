// Problem 1.1 Solution: Precedence Detective
// Understanding operator precedence and associativity

#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20, c = 5;
    
    // Question 1: What is the value of result1?
    // a + b * c = 10 + (20 * 5) = 10 + 100 = 110
    int result1 = a + b * c;
    cout << "result1: " << result1 << endl;  // Output: 110
    
    // Question 2: What is the value of result2?
    // (a + b) * c = (10 + 20) * 5 = 30 * 5 = 150
    int result2 = (a + b) * c;
    cout << "result2: " << result2 << endl;  // Output: 150
    
    // Question 3: What is the value of result3?
    // a < b && b > c = (10 < 20) && (20 > 5) = true && true = true = 1
    int result3 = a < b && b > c;
    cout << "result3: " << result3 << endl;  // Output: 1
    
    // Question 4: What is the value of result4?
    // a < b || b < c && c > a
    // Due to precedence: a < b || (b < c && c > a)
    // = (10 < 20) || ((20 < 5) && (5 > 10))
    // = true || (false && false)
    // = true || false = true
    bool result4 = a < b || b < c && c > a;
    cout << "result4: " << result4 << endl;  // Output: 1
    
    // Question 5: What are the final values of x and y?
    // int y = ++x + x++;
    // Step by step:
    // 1. ++x increments x to 6, returns 6
    // 2. x++ returns current value (6), then increments x to 7
    // 3. y = 6 + 6 = 12
    // Final: x = 7, y = 12
    int x = 5;
    int y = ++x + x++;
    cout << "x: " << x << ", y: " << y << endl;  // Output: x: 7, y: 12
    
    cout << "\nExplanation:" << endl;
    cout << "1. * has higher precedence than +" << endl;
    cout << "2. Parentheses override precedence" << endl;
    cout << "3. && has higher precedence than ||" << endl;
    cout << "4. Increment operators: ++x increments first, x++ increments after" << endl;
    
    return 0;
}

/*
Expected Output:
result1: 110
result2: 150  
result3: 1
result4: 1
x: 7, y: 12

Key Learning Points:
- Multiplication (*) has higher precedence than addition (+)
- Logical AND (&&) has higher precedence than logical OR (||)  
- Prefix increment (++x) increments then returns new value
- Postfix increment (x++) returns current value then increments
- Use parentheses when precedence is unclear
*/