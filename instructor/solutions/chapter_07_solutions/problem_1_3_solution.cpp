// Problem 1.3 Solution: Compound Assignment Efficiency
// Using compound assignment operators effectively

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Original inefficient code with rewritten compound assignments
    int score = 100;
    
    // BEFORE: score = score + 50;
    score += 50;      // More efficient and clearer
    cout << "After += 50: " << score << endl;
    
    // BEFORE: score = score * 2;
    score *= 2;       // More efficient 
    cout << "After *= 2: " << score << endl;
    
    // BEFORE: score = score - 25;
    score -= 25;      // More efficient
    cout << "After -= 25: " << score << endl;
    
    // BEFORE: score = score / 3;
    score /= 3;       // More efficient
    cout << "After /= 3: " << score << endl;
    
    // BEFORE: score = score % 10;
    score %= 10;      // More efficient
    cout << "After %= 10: " << score << endl;
    
    cout << "\nString concatenation examples:" << endl;
    string message = "Hello";
    
    // BEFORE: message = message + " ";
    message += " ";   // Much more efficient for strings!
    cout << "After += ' ': '" << message << "'" << endl;
    
    // BEFORE: message = message + "World";
    message += "World";
    cout << "After += 'World': '" << message << "'" << endl;
    
    // BEFORE: message = message + "!";
    message += "!";
    cout << "After += '!': '" << message << "'" << endl;
    
    cout << "\nBoolean operations:" << endl;
    bool flags = true;
    cout << "Initial flags: " << flags << endl;
    
    // BEFORE: flags = flags && false;
    flags &= false;   // Bitwise AND assignment (equivalent for bool)
    cout << "After &= false: " << flags << endl;
    
    // BEFORE: flags = flags || true;
    flags |= true;    // Bitwise OR assignment (equivalent for bool)
    cout << "After |= true: " << flags << endl;
    
    cout << "\nFinal results:" << endl;
    cout << "Final score: " << score << endl;
    cout << "Final message: " << message << endl;
    cout << "Final flags: " << flags << endl;
    
    // Demonstration of why compound assignment is more efficient
    cout << "\nEfficiency demonstration:" << endl;
    string large_string = "This is a potentially large string that we want to modify";
    cout << "Original string length: " << large_string.length() << endl;
    
    // Method 1: Regular assignment (less efficient)
    // large_string = large_string + " - INEFFICIENT";
    // This creates a temporary string, copies both strings, then assigns
    
    // Method 2: Compound assignment (more efficient)
    large_string += " - EFFICIENT";
    // This appends directly to the existing string, no temporary needed
    cout << "Modified string length: " << large_string.length() << endl;
    
    return 0;
}

/*
Expected Output:
After += 50: 150
After *= 2: 300
After -= 25: 275
After /= 3: 91
After %= 10: 1

String concatenation examples:
After += ' ': 'Hello '
After += 'World': 'Hello World'
After += '!': 'Hello World!'

Boolean operations:
Initial flags: 1
After &= false: 0
After |= true: 1

Final results:
Final score: 1
Final message: Hello World!
Final flags: 1

Efficiency demonstration:
Original string length: 56
Modified string length: 67

Key Learning Points:
1. Compound assignment operators (+=, -=, *=, /=, %=) are more efficient
2. For strings, += is MUCH more efficient than + with assignment
3. For booleans, &= and |= work like &&= and ||= (but don't short-circuit)
4. Compound operators are also more readable and less error-prone
5. They avoid creating temporary objects in many cases

Why more efficient?
- Fewer temporary objects created
- For strings: direct modification vs. copy + concatenate + assign
- For user-defined types: can be optimized by the class implementor
- Less typing and clearer intent
*/