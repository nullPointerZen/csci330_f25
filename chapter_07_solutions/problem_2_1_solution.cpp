// Problem 2.1 Solution: Money Class with Arithmetic
// Implementing basic arithmetic operators for a currency class

#include <iostream>
#include <iomanip>
using namespace std;

class Money {
private:
    int cents;  // Store as cents to avoid floating-point issues
    
public:
    // Constructor: Money(dollars, cents) or Money(total_cents)
    Money(int dollars = 0, int cents = 0) : cents(dollars * 100 + cents) {}
    explicit Money(int total_cents) : cents(total_cents) {}
    
    // Addition - returns new Money object
    Money operator+(const Money& other) const {
        return Money(cents + other.cents);
    }
    
    // Subtraction - returns new Money object
    Money operator-(const Money& other) const {
        return Money(cents - other.cents);
    }
    
    // Compound addition - modifies this object, returns reference
    Money& operator+=(const Money& other) {
        cents += other.cents;
        return *this;  // Return reference for chaining
    }
    
    // Compound subtraction - modifies this object, returns reference
    Money& operator-=(const Money& other) {
        cents -= other.cents;
        return *this;
    }
    
    // Equality comparison
    bool operator==(const Money& other) const {
        return cents == other.cents;
    }
    
    // Inequality (derived from equality)
    bool operator!=(const Money& other) const {
        return !(*this == other);
    }
    
    // Less than comparison
    bool operator<(const Money& other) const {
        return cents < other.cents;
    }
    
    // Other comparison operators (derived from < and ==)
    bool operator<=(const Money& other) const {
        return *this < other || *this == other;
    }
    
    bool operator>(const Money& other) const {
        return !(*this <= other);
    }
    
    bool operator>=(const Money& other) const {
        return !(*this < other);
    }
    
    // Display function
    void print() const {
        // Handle negative amounts
        if (cents < 0) {
            cout << "-$" << (-cents) / 100 << "." << setfill('0') << setw(2) << (-cents) % 100;
        } else {
            cout << "$" << cents / 100 << "." << setfill('0') << setw(2) << cents % 100;
        }
    }
    
    // Getter for testing
    int get_cents() const { return cents; }
};

// Stream output operator (non-member function)
ostream& operator<<(ostream& os, const Money& money) {
    int cents = money.get_cents();
    if (cents < 0) {
        os << "-$" << (-cents) / 100 << "." << setfill('0') << setw(2) << (-cents) % 100;
    } else {
        os << "$" << cents / 100 << "." << setfill('0') << setw(2) << cents % 100;
    }
    return os;
}

int main() {
    Money wallet(25, 50);  // $25.50
    Money coffee(4, 75);   // $4.75
    Money lunch(12, 30);   // $12.30
    
    cout << "Starting amount: " << wallet << endl;
    
    // Test subtraction
    Money after_coffee = wallet - coffee;
    cout << "After buying coffee: " << after_coffee << endl;
    
    // Test compound subtraction
    after_coffee -= lunch;
    cout << "After buying lunch: " << after_coffee << endl;
    
    // Test addition
    Money total_spent = coffee + lunch;
    cout << "Total spent: " << total_spent << endl;
    
    // Test comparisons
    if (after_coffee < Money(10, 0)) {
        cout << "Running low on money!" << endl;
    }
    
    // Additional tests
    cout << "\nAdditional tests:" << endl;
    
    // Test compound addition
    Money savings(100, 0);
    savings += Money(25, 50);
    cout << "Savings after deposit: " << savings << endl;
    
    // Test equality
    Money amount1(50, 0);
    Money amount2(49, 100);  // Same as $50.00
    if (amount1 == amount2) {
        cout << "Equal amounts: " << amount1 << " == " << amount2 << endl;
    }
    
    // Test all comparison operators
    Money small(5, 0);
    Money large(10, 0);
    cout << "\nComparison tests:" << endl;
    cout << small << " < " << large << ": " << (small < large) << endl;
    cout << small << " <= " << large << ": " << (small <= large) << endl;
    cout << large << " > " << small << ": " << (large > small) << endl;
    cout << large << " >= " << small << ": " << (large >= small) << endl;
    cout << small << " != " << large << ": " << (small != large) << endl;
    
    // Test negative amounts (overdraft)
    Money account(10, 0);
    Money big_purchase(15, 0);
    Money overdraft = account - big_purchase;
    cout << "\nOverdraft test: " << account << " - " << big_purchase << " = " << overdraft << endl;
    
    return 0;
}

/*
Expected Output:
Starting amount: $25.50
After buying coffee: $20.75
After buying lunch: $8.45
Total spent: $17.05
Running low on money!

Additional tests:
Savings after deposit: $125.50
Equal amounts: $50.00 == $50.00

Comparison tests:
$5.00 < $10.00: 1
$5.00 <= $10.00: 1
$10.00 > $5.00: 1
$10.00 >= $5.00: 1
$5.00 != $10.00: 1

Overdraft test: $10.00 - $15.00 = -$5.00

Key Learning Points:
1. Store money as integer cents to avoid floating-point precision issues
2. Arithmetic operators (+, -) return new objects by value
3. Compound operators (+=, -=) modify the object and return reference
4. Implement == and < first, then derive other comparison operators
5. Stream output operator must be non-member function
6. Handle negative amounts properly in display functions
7. Use const member functions for operations that don't modify the object
8. Return references from compound operators to enable chaining
*/