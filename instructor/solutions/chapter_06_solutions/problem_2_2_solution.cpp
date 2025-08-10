// Problem 2.2 Solution: Template Container with Dynamic Storage
// SimpleArray template that manages dynamic memory for any type

#include <iostream>
#include <string>
using namespace std;

template<typename T>
class SimpleArray {
private:
    T* data;
    size_t array_size;
    
public:
    // Constructor allocates dynamic memory
    SimpleArray(size_t size) : array_size(size) {
        data = new T[size];
        // Initialize array elements to default values
        for (size_t i = 0; i < size; i++) {
            data[i] = T();  // Default constructor for type T
        }
    }
    
    // Destructor prevents memory leaks
    ~SimpleArray() {
        delete[] data;
    }
    
    // Get method with bounds checking
    T get(size_t index) const {
        if (index >= array_size) {
            cout << "Error: Index " << index << " out of bounds (size: " << array_size << ")" << endl;
            return T();  // Return default value for type T
        }
        return data[index];
    }
    
    // Set method with bounds checking
    void set(size_t index, const T& value) {
        if (index >= array_size) {
            cout << "Error: Index " << index << " out of bounds (size: " << array_size << ")" << endl;
            return;
        }
        data[index] = value;
    }
    
    // Size method returns the array size
    size_t size() const {
        return array_size;
    }
    
    // Bonus: Display all elements
    void display() const {
        cout << "[";
        for (size_t i = 0; i < array_size; i++) {
            cout << data[i];
            if (i < array_size - 1) cout << ", ";
        }
        cout << "]";
    }
    
    // Copy constructor and assignment operator should be deleted or properly implemented
    // For simplicity, we'll delete them to prevent accidental copying
    SimpleArray(const SimpleArray&) = delete;
    SimpleArray& operator=(const SimpleArray&) = delete;
};

int main() {
    // Test with integers
    SimpleArray<int> numbers(5);
    numbers.set(0, 100);
    numbers.set(1, 200);
    numbers.set(2, 300);
    
    cout << "numbers[0] = " << numbers.get(0) << endl;
    cout << "numbers[1] = " << numbers.get(1) << endl;
    cout << "Size: " << numbers.size() << endl;
    cout << "All numbers: ";
    numbers.display();
    cout << endl << endl;
    
    // Test with strings
    SimpleArray<string> words(3);
    words.set(0, "apple");
    words.set(1, "banana");
    words.set(2, "cherry");
    
    cout << "words[0] = " << words.get(0) << endl;
    cout << "words[1] = " << words.get(1) << endl;
    cout << "All words: ";
    words.display();
    cout << endl << endl;
    
    // Test bounds checking
    cout << "Testing bounds checking:" << endl;
    numbers.set(10, 999);  // Should print error
    cout << "Invalid get: " << numbers.get(15) << endl;  // Should print error
    cout << endl;
    
    // Test with doubles
    SimpleArray<double> prices(4);
    prices.set(0, 19.99);
    prices.set(1, 29.95);
    prices.set(2, 9.50);
    prices.set(3, 45.00);
    
    cout << "Prices: ";
    prices.display();
    cout << endl;
    cout << "Price at index 2: $" << prices.get(2) << endl;
    
    return 0;
}

/*
Expected Output:
numbers[0] = 100
numbers[1] = 200
Size: 5
All numbers: [100, 200, 300, 0, 0]

words[0] = apple
words[1] = banana
All words: [apple, banana, cherry]

Testing bounds checking:
Error: Index 10 out of bounds (size: 5)
Error: Index 15 out of bounds (size: 5)
Invalid get: 0

Prices: [19.99, 29.95, 9.5, 45]
Price at index 2: $9.5

Key Learning Points:
1. Dynamic memory allocation with templates: new T[size]
2. Proper destructor prevents memory leaks: delete[] data
3. Bounds checking prevents array access errors
4. T() creates a default value for any type T
5. Copy operations are deleted to prevent shallow copy problems
6. Template works with built-in types (int, double) and classes (string)
7. Each type creates a completely separate class with separate memory management
*/