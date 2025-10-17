#include <iostream>
#include <string>
using namespace std;

template<typename T>
class SimpleArray {
private:
    T* data;
    size_t array_size;

public:
    // Constructor
    SimpleArray(size_t size) : array_size(size) {
        data = new T[size];
    }

    // Destructor
    ~SimpleArray() {
        delete[] data;
    }

    // Get method with bounds checking
    T get(size_t index) const {
        if (index >= array_size) {
            cerr << "Error: Index " << index << " out of bounds." << endl;
            return T();  // Return default-constructed value
        }
        return data[index];
    }

    // Set method with bounds checking
    void set(size_t index, const T& value) {
        if (index >= array_size) {
            cerr << "Error: Index " << index << " out of bounds." << endl;
            return;
        }
        data[index] = value;
    }

    // Size method
    size_t size() const {
        return array_size;
    }
};

int main() {
    SimpleArray<int> numbers(5);
    numbers.set(0, 100);
    numbers.set(1, 200);
    cout << "numbers[0] = " << numbers.get(0) << endl;
    cout << "Size: " << numbers.size() << endl;

    SimpleArray<string> words(3);
    words.set(0, "apple");
    words.set(1, "banana");
    cout << "words[0] = " << words.get(0) << endl;

    // Optional: test out-of-bounds behavior
    numbers.set(10, 999);  // Should print error
    cout << "numbers[10] = " << numbers.get(10) << endl;  // Should print error

    return 0;
}