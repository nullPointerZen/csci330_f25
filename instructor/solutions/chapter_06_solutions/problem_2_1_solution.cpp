// Problem 2.1 Solution: Simple Template Container
// Pair template class that holds two values of the same type

#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Pair {
private:
    T first_value;
    T second_value;
    
public:
    // Constructor to initialize both values
    Pair(const T& first, const T& second) 
        : first_value(first), second_value(second) {}
    
    // Getter methods
    T first() const {
        return first_value;
    }
    
    T second() const {
        return second_value;
    }
    
    // Setter methods
    void set_first(const T& value) {
        first_value = value;
    }
    
    void set_second(const T& value) {
        second_value = value;
    }
    
    // Swap method that exchanges the two values
    void swap() {
        T temp = first_value;
        first_value = second_value;
        second_value = temp;
    }
    
    // Bonus: Display method for easy printing
    void display() const {
        cout << "(" << first_value << ", " << second_value << ")";
    }
};

int main() {
    // Test with integers
    Pair<int> numbers(10, 20);
    cout << "First: " << numbers.first() << ", Second: " << numbers.second() << endl;
    
    numbers.swap();
    cout << "After swap - First: " << numbers.first() << ", Second: " << numbers.second() << endl;
    cout << endl;
    
    // Test with strings
    Pair<string> words("hello", "world");
    cout << words.first() << " " << words.second() << endl;
    
    // Test setter methods
    words.set_first("goodbye");
    cout << "After changing first: " << words.first() << " " << words.second() << endl;
    cout << endl;
    
    // Test with doubles
    Pair<double> coordinates(3.14, 2.71);
    cout << "Coordinates: ";
    coordinates.display();
    cout << endl;
    
    coordinates.swap();
    cout << "After swap: ";
    coordinates.display();
    cout << endl;
    
    // Test with characters
    Pair<char> letters('A', 'Z');
    cout << "Letters: " << letters.first() << " and " << letters.second() << endl;
    letters.set_second('B');
    cout << "After change: " << letters.first() << " and " << letters.second() << endl;
    
    return 0;
}

/*
Expected Output:
First: 10, Second: 20
After swap - First: 20, Second: 10

hello world
After changing first: goodbye world

Coordinates: (3.14, 2.71)
After swap: (2.71, 3.14)
Letters: A and Z
After change: A and B

Key Learning Points:
1. Template class syntax: template<typename T> class Pair
2. Constructor initialization list works with template types
3. Const methods for getters (don't modify the object)
4. Template classes work with any type (int, string, double, char)
5. Each instantiation (Pair<int>, Pair<string>) is a completely separate class
6. Template classes can have any methods that make sense for the type
*/