#include <iostream>
#include <iomanip>
#include <cmath>

// Money class with operator overloading
class Money {
private:
    int cents;  // Store as cents to avoid floating-point issues

public:
    Money(int dollars = 0, int cents = 0) : cents(dollars * 100 + cents) {}
    explicit Money(int total_cents) : cents(total_cents) {}

    // Addition
    Money operator+(const Money& other) const {
        return Money(this->cents + other.cents);
    }

    // Subtraction
    Money operator-(const Money& other) const {
        return Money(this->cents - other.cents);
    }

    // Compound addition
    Money& operator+=(const Money& other) {
        this->cents += other.cents;
        return *this;
    }

    // Compound subtraction
    Money& operator-=(const Money& other) {
        this->cents -= other.cents;
        return *this;
    }

    // Equality comparison
    bool operator==(const Money& other) const {
        return this->cents == other.cents;
    }

    // Less than comparison
    bool operator<(const Money& other) const {
        return this->cents < other.cents;
    }

    // Display function
    void print() const {
        std::cout << "$" << cents / 100 << "." << std::setfill('0') << std::setw(2) << cents % 100;
    }

    int get_cents() const { return cents; }
};

// Vector2D class
class Vector2D {
private:
    double x, y;

public:
    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    double get_x() const { return x; }
    double get_y() const { return y; }

    // Vector addition
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // Vector subtraction
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // Scalar multiplication (vector * scalar)
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // Dot product (return scalar)
    double operator*(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }

    // Compound addition
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Equality (be careful with floating-point comparison!)
    bool operator==(const Vector2D& other) const {
        const double EPSILON = 1e-9;
        return std::abs(x - other.x) < EPSILON && std::abs(y - other.y) < EPSILON;
    }

    // Calculate magnitude
    double magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalize vector (make it unit length)
    Vector2D normalize() const {
        double mag = magnitude();
        if (mag == 0.0) return Vector2D(0, 0);
        return Vector2D(x / mag, y / mag);
    }
};

// Scalar multiplication (scalar * vector)
Vector2D operator*(double scalar, const Vector2D& vec) {
    return vec * scalar;  // Reuse existing operator
}

// Stream output operator
std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
    os << "(" << vec.get_x() << ", " << vec.get_y() << ")";
    return os;
}

// Counter class with all comparison operators
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

    // Basic comparison operators
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

    int get_value() const { return value; }
};

void test_expressions() {
    std::cout << "=== Expression Precedence Tests ===\n";

    int a = 10, b = 20, c = 5;

    int result1 = a + b * c;  // 10 + (20 * 5) = 110
    std::cout << "a + b * c = " << result1 << std::endl;

    int result2 = (a + b) * c;  // (10 + 20) * 5 = 150
    std::cout << "(a + b) * c = " << result2 << std::endl;

    bool result3 = a < b && b > c;  // true && true = true
    std::cout << "a < b && b > c = " << result3 << std::endl;

    bool result4 = a < b || b < c && c > a;  // true || (false && false) = true
    std::cout << "a < b || b < c && c > a = " << result4 << std::endl;
}

void test_type_conversions() {
    std::cout << "\n=== Type Conversion Examples ===\n";

    // Fixed integer division
    int total_items = 17;
    int groups = 5;
    double average = static_cast<double>(total_items) / groups;
    std::cout << "Average (fixed): " << average << std::endl;

    // Safe comparison
    int signed_value = -1;
    unsigned int unsigned_value = 1;
    if (signed_value < static_cast<int>(unsigned_value)) {
        std::cout << "Safe comparison works correctly" << std::endl;
    }

    // Proper rounding
    double precise_value = 3.99999;
    int rounded = static_cast<int>(std::round(precise_value));
    std::cout << "Rounded value: " << rounded << std::endl;
}

int main() {
    test_expressions();
    test_type_conversions();

    std::cout << "\n=== Money Class Demo ===\n";

    Money wallet(25, 50);  // $25.50
    Money coffee(4, 75);   // $4.75
    Money lunch(12, 30);   // $12.30

    std::cout << "Starting amount: ";
    wallet.print();
    std::cout << std::endl;

    Money after_coffee = wallet - coffee;
    std::cout << "After buying coffee: ";
    after_coffee.print();
    std::cout << std::endl;

    after_coffee -= lunch;
    std::cout << "After buying lunch: ";
    after_coffee.print();
    std::cout << std::endl;

    Money total_spent = coffee + lunch;
    std::cout << "Total spent: ";
    total_spent.print();
    std::cout << std::endl;

    if (after_coffee < Money(10, 0)) {
        std::cout << "Running low on money!" << std::endl;
    }

    std::cout << "\n=== Vector2D Class Demo ===\n";

    Vector2D v1(3.0, 4.0);
    Vector2D v2(1.0, 2.0);

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;

    Vector2D sum = v1 + v2;
    std::cout << "v1 + v2: " << sum << std::endl;

    Vector2D scaled = v1 * 2.0;
    std::cout << "v1 * 2: " << scaled << std::endl;

    Vector2D scaled2 = 3.0 * v2;
    std::cout << "3 * v2: " << scaled2 << std::endl;

    double dot = v1 * v2;  // dot product
    std::cout << "v1 · v2: " << dot << std::endl;

    std::cout << "Magnitude of v1: " << v1.magnitude() << std::endl;
    std::cout << "v1 normalized: " << v1.normalize() << std::endl;

    std::cout << "\n=== Counter Class Demo ===\n";

    Counter c1(5);
    Counter c2(10);
    Counter c3(5);

    std::cout << "c1: " << c1.get_value() << std::endl;
    std::cout << "c2: " << c2.get_value() << std::endl;
    std::cout << "c3: " << c3.get_value() << std::endl;

    std::cout << "\nComparison tests:" << std::endl;
    std::cout << "c1 == c3: " << (c1 == c3) << std::endl;
    std::cout << "c1 != c2: " << (c1 != c2) << std::endl;
    std::cout << "c1 < c2: " << (c1 < c2) << std::endl;
    std::cout << "c1 <= c3: " << (c1 <= c3) << std::endl;
    std::cout << "c2 > c1: " << (c2 > c1) << std::endl;
    std::cout << "c2 >= c1: " << (c2 >= c1) << std::endl;

    std::cout << "\nIncrement tests:" << std::endl;
    std::cout << "++c1: " << (++c1).get_value() << std::endl;
    std::cout << "c1++ then c1: " << (c1++).get_value() << " then " << c1.get_value() << std::endl;

    return 0;
}