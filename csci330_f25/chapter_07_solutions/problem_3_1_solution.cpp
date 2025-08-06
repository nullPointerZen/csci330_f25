// Problem 3.1 Solution: Smart Counter with All Comparison Operators
// Implementing complete set of comparison operators using canonical pattern

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
        Counter temp = *this;    // Save current state
        ++value;                 // Increment this object
        return temp;             // Return old state
    }
    
    // Decrement operators (bonus - not in original problem)
    Counter& operator--() {      // prefix --counter
        --value;
        return *this;
    }
    
    Counter operator--(int) {    // postfix counter--
        Counter temp = *this;
        --value;
        return temp;
    }
    
    // CANONICAL COMPARISON OPERATORS
    // Implement these two fundamental operators first:
    
    bool operator==(const Counter& other) const {
        return value == other.value;
    }
    
    bool operator<(const Counter& other) const {
        return value < other.value;
    }
    
    // Then derive all other comparison operators from the fundamental ones:
    
    bool operator!=(const Counter& other) const {
        return !(*this == other);  // Use == and negate
    }
    
    bool operator<=(const Counter& other) const {
        return *this < other || *this == other;  // Less than OR equal
    }
    
    bool operator>(const Counter& other) const {
        return !(*this <= other);  // NOT less-than-or-equal means greater-than
    }
    
    bool operator>=(const Counter& other) const {
        return !(*this < other);   // NOT less-than means greater-than-or-equal
    }
    
    // Utility functions
    int get_value() const { return value; }
    
    void set_value(int new_value) { value = new_value; }
    
    // Addition operators (bonus)
    Counter operator+(int increment) const {
        return Counter(value + increment);
    }
    
    Counter& operator+=(int increment) {
        value += increment;
        return *this;
    }
};

// Non-member operators for different operand orders
Counter operator+(int increment, const Counter& counter) {
    return counter + increment;
}

// Stream output operator
ostream& operator<<(ostream& os, const Counter& counter) {
    os << "Counter(" << counter.get_value() << ")";
    return os;
}

// Test function to verify all operators work correctly
void test_comparisons(const Counter& a, const Counter& b, const string& label) {
    cout << "\n" << label << ":" << endl;
    cout << "a: " << a << ", b: " << b << endl;
    cout << "a == b: " << (a == b) << endl;
    cout << "a != b: " << (a != b) << endl;
    cout << "a <  b: " << (a < b) << endl;
    cout << "a <= b: " << (a <= b) << endl;
    cout << "a >  b: " << (a > b) << endl;
    cout << "a >= b: " << (a >= b) << endl;
}

int main() {
    Counter c1(5);
    Counter c2(10);
    Counter c3(5);
    
    cout << "Initial values:" << endl;
    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;
    cout << "c3: " << c3 << endl;
    
    // Test all comparison operators with different relationships
    test_comparisons(c1, c2, "c1 vs c2 (5 vs 10)");
    test_comparisons(c1, c3, "c1 vs c3 (5 vs 5)");
    test_comparisons(c2, c1, "c2 vs c1 (10 vs 5)");
    
    // Test increment operators
    cout << "\nIncrement tests:" << endl;
    cout << "Original c1: " << c1 << endl;
    
    Counter pre_result = ++c1;
    cout << "After ++c1, c1: " << c1 << ", returned: " << pre_result << endl;
    
    Counter post_result = c1++;
    cout << "After c1++, c1: " << c1 << ", returned: " << post_result << endl;
    
    // Test decrement operators
    cout << "\nDecrement tests:" << endl;
    cout << "Current c1: " << c1 << endl;
    
    Counter pre_dec = --c1;
    cout << "After --c1, c1: " << c1 << ", returned: " << pre_dec << endl;
    
    Counter post_dec = c1--;
    cout << "After c1--, c1: " << c1 << ", returned: " << post_dec << endl;
    
    // Test addition operators
    cout << "\nAddition tests:" << endl;
    Counter c4 = c1 + 10;
    cout << c1 << " + 10 = " << c4 << endl;
    
    c1 += 5;
    cout << "After += 5: " << c1 << endl;
    
    Counter c5 = 3 + c1;  // Non-member operator
    cout << "3 + " << c1 << " = " << c5 << endl;
    
    // Demonstrate use in sorting context
    cout << "\nSorting demonstration:" << endl;
    Counter counters[] = {Counter(15), Counter(3), Counter(8), Counter(1), Counter(12)};
    int size = sizeof(counters) / sizeof(counters[0]);
    
    cout << "Before sorting: ";
    for (int i = 0; i < size; ++i) {
        cout << counters[i].get_value() << " ";
    }
    cout << endl;
    
    // Simple bubble sort using our comparison operators
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (counters[j] > counters[j + 1]) {  // Using our > operator!
                Counter temp = counters[j];
                counters[j] = counters[j + 1];
                counters[j + 1] = temp;
            }
        }
    }
    
    cout << "After sorting:  ";
    for (int i = 0; i < size; ++i) {
        cout << counters[i].get_value() << " ";
    }
    cout << endl;
    
    return 0;
}

/*
Expected Output:
Initial values:
c1: Counter(5)
c2: Counter(10)
c3: Counter(5)

c1 vs c2 (5 vs 10):
a: Counter(5), b: Counter(10)
a == b: 0
a != b: 1
a <  b: 1
a <= b: 1
a >  b: 0
a >= b: 0

c1 vs c3 (5 vs 5):
a: Counter(5), b: Counter(5)
a == b: 1
a != b: 0
a <  b: 0
a <= b: 1
a >  b: 0
a >= b: 1

c2 vs c1 (10 vs 5):
a: Counter(10), b: Counter(5)
a == b: 0
a != b: 1
a <  b: 0
a <= b: 0
a >  b: 1
a >= b: 1

Increment tests:
Original c1: Counter(5)
After ++c1, c1: Counter(6), returned: Counter(6)
After c1++, c1: Counter(7), returned: Counter(6)

Decrement tests:
Current c1: Counter(7)
After --c1, c1: Counter(6), returned: Counter(6)
After c1--, c1: Counter(5), returned: Counter(6)

Addition tests:
Counter(5) + 10 = Counter(15)
After += 5: Counter(10)
3 + Counter(10) = Counter(13)

Sorting demonstration:
Before sorting: 15 3 8 1 12 
After sorting:  1 3 8 12 15 

Key Learning Points:
1. CANONICAL PATTERN: Implement == and < first, derive others from these
2. This reduces code duplication and ensures consistency
3. Prefix increment (++obj) returns reference to modified object
4. Postfix increment (obj++) returns copy of original object
5. All comparison operators should be const member functions
6. Derived operators use existing operators for consistency
7. This pattern makes objects usable with standard algorithms
8. Stream output operator enables easy debugging and display
9. Non-member operators allow different operand orders
10. Well-designed operators enable natural mathematical expressions
*/