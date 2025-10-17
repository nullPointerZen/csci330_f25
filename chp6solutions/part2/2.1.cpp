#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Pair {
private:
    T first_value;
    T second_value;

public:
    // Constructor
    Pair(T first, T second) : first_value(first), second_value(second) {}

    // Getter methods
    T first() const { return first_value; }
    T second() const { return second_value; }

    // Setter methods
    void set_first(const T& value) { first_value = value; }
    void set_second(const T& value) { second_value = value; }

    // Swap method
    void swap() {
        T temp = first_value;
        first_value = second_value;
        second_value = temp;
    }
};

int main() {
    Pair<int> numbers(10, 20);
    cout << "First: " << numbers.first() << ", Second: " << numbers.second() << endl;

    numbers.swap();
    cout << "After swap - First: " << numbers.first() << ", Second: " << numbers.second() << endl;

    Pair<string> words("hello", "world");
    cout << words.first() << " " << words.second() << endl;

    return 0;
}