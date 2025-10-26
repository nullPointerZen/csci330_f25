#include <iostream>
using namespace std;

class Counter {
private:
    int value;

public:
    Counter(int initial_value = 0) : value(initial_value) {}

    // Increment operators
    Counter& operator++() {      // prefix ++counter
        ++value;
        return *this;
    }

    Counter operator++(int) {    // postfix counter++
        Counter temp = *this;
        ++value;
        return temp;
    }

    // Canonical comparison operators
    bool operator==(const Counter& other) const {
        return value == other.value;
    }

    bool operator!=(const Counter& other) const {
        return !(*this == other);
    }

    bool operator<(const Counter& other) const {
        return value < other.value;
    }

    bool operator<=(const Counter& other) const {
        return *this < other || *this == other;
    }

    bool operator>(const Counter& other) const {
        return !(*this <= other);
    }

    bool operator>=(const Counter& other) const {
        return !(*this < other);
    }

    // For output
    int get_value() const { return value; }
};

int main() {
    Counter c1(5);
    Counter c2(10);
    Counter c3(5);

    cout << "c1: " << c1.get_value() << endl;
    cout << "c2: " << c2.get_value() << endl;
    cout << "c3: " << c3.get_value() << endl;

    // Test all comparison operators
    cout << "\nComparison tests:" << endl;
    cout << "c1 == c3: " << (c1 == c3) << endl;
    cout << "c1 != c2: " << (c1 != c2) << endl;
    cout << "c1 < c2: " << (c1 < c2) << endl;
    cout << "c1 <= c3: " << (c1 <= c3) << endl;
    cout << "c2 > c1: " << (c2 > c1) << endl;
    cout << "c2 >= c1: " << (c2 >= c1) << endl;

    // Test increment
    cout << "\nIncrement tests:" << endl;
    cout << "++c1: " << (++c1).get_value() << endl;
    cout << "c1++ then c1: " << (c1++).get_value() << " then " << c1.get_value() << endl;

    return 0;
}