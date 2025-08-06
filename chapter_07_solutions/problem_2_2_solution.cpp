// Problem 2.2 Solution: Vector2D with Mathematical Operations
// Implementing vector arithmetic with member and non-member operators

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Vector2D {
private:
    double x, y;
    
public:
    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    
    // Getters
    double get_x() const { return x; }
    double get_y() const { return y; }
    
    // Vector addition - returns new vector
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    // Vector subtraction - returns new vector
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    // Scalar multiplication (vector * scalar) - returns new vector
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    // Dot product (vector * vector) - returns scalar
    // Note: This overloads the * operator for two different operations
    double operator*(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }
    
    // Compound addition - modifies this vector
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    // Compound subtraction - modifies this vector
    Vector2D& operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    
    // Compound scalar multiplication
    Vector2D& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    
    // Equality comparison (careful with floating-point!)
    bool operator==(const Vector2D& other) const {
        const double EPSILON = 1e-9;
        return abs(x - other.x) < EPSILON && abs(y - other.y) < EPSILON;
    }
    
    // Inequality
    bool operator!=(const Vector2D& other) const {
        return !(*this == other);
    }
    
    // Calculate magnitude (length of vector)
    double magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    // Normalize vector (make it unit length)
    Vector2D normalize() const {
        double mag = magnitude();
        if (mag == 0.0) return Vector2D(0, 0);  // Avoid division by zero
        return Vector2D(x / mag, y / mag);
    }
    
    // Unary minus (negate vector)
    Vector2D operator-() const {
        return Vector2D(-x, -y);
    }
};

// Non-member function: Scalar multiplication (scalar * vector)
// This allows expressions like: 3.0 * vector
Vector2D operator*(double scalar, const Vector2D& vec) {
    return vec * scalar;  // Reuse the member operator
}

// Stream output operator (must be non-member)
ostream& operator<<(ostream& os, const Vector2D& vec) {
    os << "(" << fixed << setprecision(1) << vec.get_x() 
       << ", " << vec.get_y() << ")";
    return os;
}

int main() {
    Vector2D v1(3.0, 4.0);
    Vector2D v2(1.0, 2.0);
    
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;
    
    // Test vector addition
    Vector2D sum = v1 + v2;
    cout << "v1 + v2: " << sum << endl;
    
    // Test scalar multiplication (member function)
    Vector2D scaled = v1 * 2.0;
    cout << "v1 * 2: " << scaled << endl;
    
    // Test scalar multiplication (non-member function)
    Vector2D scaled2 = 3.0 * v2;
    cout << "3 * v2: " << scaled2 << endl;
    
    // Test dot product
    double dot = v1 * v2;
    cout << "v1 · v2: " << dot << endl;
    
    // Test magnitude
    cout << "Magnitude of v1: " << fixed << setprecision(1) << v1.magnitude() << endl;
    
    // Test normalization
    cout << "v1 normalized: " << v1.normalize() << endl;
    
    // Additional tests
    cout << "\nAdditional tests:" << endl;
    
    // Test vector subtraction
    Vector2D diff = v1 - v2;
    cout << "v1 - v2: " << diff << endl;
    
    // Test compound operations
    Vector2D v3 = v1;  // Copy v1
    v3 += v2;
    cout << "v1 += v2 result: " << v3 << endl;
    
    v3 -= v2;
    cout << "After -= v2: " << v3 << endl;
    
    v3 *= 0.5;
    cout << "After *= 0.5: " << v3 << endl;
    
    // Test equality
    Vector2D v4(3.0, 4.0);
    if (v1 == v4) {
        cout << "v1 equals v4: " << v1 << " == " << v4 << endl;
    }
    
    // Test unary minus
    Vector2D negated = -v1;
    cout << "Negated v1: " << negated << endl;
    
    // Test zero vector normalization
    Vector2D zero(0.0, 0.0);
    Vector2D zero_normalized = zero.normalize();
    cout << "Zero vector normalized: " << zero_normalized << endl;
    
    // Demonstrate vector operations
    cout << "\nVector physics example:" << endl;
    Vector2D velocity(10.0, 5.0);
    Vector2D acceleration(2.0, -1.0);
    double time = 2.0;
    
    cout << "Initial velocity: " << velocity << endl;
    cout << "Acceleration: " << acceleration << endl;
    cout << "Time: " << time << endl;
    
    // v = v0 + a*t
    Vector2D final_velocity = velocity + acceleration * time;
    cout << "Final velocity: " << final_velocity << endl;
    
    // Calculate angle between vectors
    Vector2D a(1.0, 0.0);  // Unit vector along x-axis
    Vector2D b(1.0, 1.0);  // Vector at 45 degrees
    double dot_product = a * b;
    double angle_radians = acos(dot_product / (a.magnitude() * b.magnitude()));
    double angle_degrees = angle_radians * 180.0 / M_PI;
    cout << "\nAngle between " << a << " and " << b << ": " 
         << fixed << setprecision(1) << angle_degrees << " degrees" << endl;
    
    return 0;
}

/*
Expected Output:
v1: (3.0, 4.0)
v2: (1.0, 2.0)
v1 + v2: (4.0, 6.0)
v1 * 2: (6.0, 8.0)
3 * v2: (3.0, 6.0)
v1 · v2: 11.0
Magnitude of v1: 5.0
v1 normalized: (0.6, 0.8)

Additional tests:
v1 - v2: (2.0, 2.0)
v1 += v2 result: (4.0, 6.0)
After -= v2: (3.0, 4.0)
After *= 0.5: (1.5, 2.0)
v1 equals v4: (3.0, 4.0) == (3.0, 4.0)
Negated v1: (-3.0, -4.0)
Zero vector normalized: (0.0, 0.0)

Vector physics example:
Initial velocity: (10.0, 5.0)
Acceleration: (2.0, -1.0)
Time: 2.0
Final velocity: (14.0, 3.0)

Angle between (1.0, 0.0) and (1.0, 1.0): 45.0 degrees

Key Learning Points:
1. Member operators work when the left operand is your class type
2. Non-member operators needed when left operand is different type (scalar * vector)
3. Can overload same operator for different operations (vector*scalar vs vector*vector)
4. Be careful with floating-point equality - use epsilon comparison
5. Stream output operator must be non-member and return stream reference
6. Compound operators should modify the object and return reference
7. Handle special cases (like zero vector normalization)
8. Mathematical operations should follow mathematical conventions
9. Use const member functions for operations that don't modify the object
10. Vector arithmetic enables intuitive mathematical expressions in code
*/