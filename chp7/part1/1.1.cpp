// i predicted it would add and multiply the numbers in the order in the specific line of code
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20, c = 5;
    
  
    int result1 = a + b * c;
    cout << "result1: " << result1 << endl;
    
  
    int result2 = (a + b) * c;
    cout << "result2: " << result2 << endl;
    
   
    int result3 = a < b && b > c;
    cout << "result3: " << result3 << endl;
    
  
    bool result4 = a < b || b < c && c > a;
    cout << "result4: " << result4 << endl;
    
   
    int x = 5;
    int y = ++x + x++;
    cout << "x: " << x << ", y: " << y << endl;
    
    return 0;
}