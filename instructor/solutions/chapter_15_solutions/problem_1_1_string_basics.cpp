/**
 * Chapter 15: Strings - Problem 1.1 Solution
 * Basic string operations and manipulation
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main() {
    // 1. Create a string with your name
    std::string name = "Alice";
    
    // 2. Create a greeting by concatenating "Hello, " with your name
    std::string greeting = "Hello, " + name;
    
    // 3. Add an exclamation mark at the end
    greeting += "!";
    
    // 4. Print the length of the greeting
    std::cout << "Length: " << greeting.length() << std::endl;
    
    // 5. Print the first and last characters
    std::cout << "First: " << greeting.front() << std::endl;  // C++11
    std::cout << "Last: " << greeting.back() << std::endl;    // C++11
    
    // Alternative for older C++ versions:
    // std::cout << "First: " << greeting[0] << std::endl;
    // std::cout << "Last: " << greeting[greeting.length() - 1] << std::endl;
    
    // 6. Convert to uppercase
    std::string uppercase_greeting = greeting;
    std::transform(uppercase_greeting.begin(), uppercase_greeting.end(), 
                   uppercase_greeting.begin(), 
                   [](unsigned char c) { return std::toupper(c); });
    
    std::cout << uppercase_greeting << std::endl;
    
    return 0;
}

/**
 * Expected Output:
 * Length: 13
 * First: H
 * Last: !
 * HELLO, ALICE!
 * 
 * Key Learning Points:
 * 1. String concatenation with + operator
 * 2. Using front() and back() for safe access (C++11)
 * 3. std::transform with lambda for character-by-character operations
 * 4. Lambda with unsigned char parameter to avoid undefined behavior with std::toupper
 */