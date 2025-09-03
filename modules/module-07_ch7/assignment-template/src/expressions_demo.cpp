// HW_07: Expressions and Operators
// Time: 2.25 hours (45 minutes per problem set)
// Topics: Operator precedence, overloading, bitwise operations

#include <cstdio>
#include <iostream>
#include <cmath>

// ============================================================================
// PROBLEM SET 1: Operator Basics (45 minutes)  
// ============================================================================

void precedence_lab() {
    printf("=== Operator Precedence Lab ===\n");
    
    // TODO 1: Predict and test expression results
    printf("Expression evaluation (predict first, then verify):\n");
    
    // Mixed arithmetic and logical
    int a = 5, b = 10, c = 3;
    
    // TODO: Predict this result: 5 + 10 * 3
    int result1 = a + b * c;
    printf("  %d + %d * %d = %d\n", a, b, c, result1);
    
    // TODO: Compare with parentheses: (5 + 10) * 3
    int result2 = (a + b) * c;
    printf("  (%d + %d) * %d = %d\n", a, b, c, result2);
    
    // TODO 2: Boolean expressions with mixed precedence
    bool x = true, y = false;
    
    // Predict: true && false || true
    bool result3 = x && y || x;
    printf("  %s && %s || %s = %s\n", 
           x ? "true" : "false", 
           y ? "true" : "false",
           x ? "true" : "false",
           result3 ? "true" : "false");
    
    // TODO 3: Assignment vs equality operators
    int value = 10;
    // Warning: This is assignment in condition!
    if (value = 5) {  // Assignment, not comparison!
        printf("  Assignment in condition: value is now %d\n", value);
    }
    
    // TODO: Fix above to use equality comparison
    value = 10;
    if (value == 5) {
        printf("  This should not print\n");
    } else {
        printf("  Equality comparison: value is %d, not 5\n", value);
    }
    
    printf("\n");
}

void compound_operators() {
    printf("=== Compound Operators ===\n");
    
    // TODO 4: Demonstrate all compound operators
    int num = 100;
    printf("Starting value: %d\n", num);
    
    // TODO: Use +=, -=, *=, /=, %=
    num += 50;    // equivalent to num = num + 50
    printf("  After += 50: %d\n", num);
    
    num -= 30;
    printf("  After -= 30: %d\n", num);
    
    num *= 2;
    printf("  After *= 2: %d\n", num);
    
    num /= 4;
    printf("  After /= 4: %d\n", num);
    
    num %= 10;
    printf("  After %%= 10: %d\n", num);
    
    // TODO 5: Increment and decrement operators
    printf("\nIncrement/Decrement operators:\n");
    int counter = 5;
    
    printf("  counter = %d\n", counter);
    printf("  counter++ returns %d, counter is now %d\n", counter++, counter);
    printf("  ++counter returns %d, counter is now %d\n", ++counter, counter);
    printf("  counter-- returns %d, counter is now %d\n", counter--, counter);
    printf("  --counter returns %d, counter is now %d\n", --counter, counter);
    
    printf("\n");
}

void ternary_operator() {
    printf("=== Ternary Operator ===\n");
    
    // TODO 6: Basic ternary usage
    int age = 20;
    const char* status = (age >= 18) ? "adult" : "minor";
    printf("  Age %d is %s\n", age, status);
    
    // TODO 7: Nested ternary (use sparingly!)
    int score = 85;
    char grade = (score >= 90) ? 'A' : 
                 (score >= 80) ? 'B' : 
                 (score >= 70) ? 'C' : 
                 (score >= 60) ? 'D' : 'F';
    printf("  Score %d gets grade %c\n", score, grade);
    
    // TODO 8: Ternary with different types
    double x = 3.14;
    double abs_x = (x >= 0) ? x : -x;
    printf("  Absolute value of %.2f is %.2f\n", x, abs_x);
    
    printf("\n");
}

void problem_set_1_demo() {
    printf("=== Problem Set 1: Operator Basics ===\n\n");
    
    precedence_lab();
    compound_operators();
    ternary_operator();
}

// ============================================================================
// PROBLEM SET 2: Operator Overloading (45 minutes)
// ============================================================================

// TODO 9: Complex number class with operator overloading
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // TODO: Arithmetic operators
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        // (a+bi)(c+di) = (ac-bd) + (ad+bc)i
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    // TODO 10: Stream operators for easy I/O
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << "+";
        os << c.imag << "i";
        return os;
    }
    
    // Getters for testing
    double getReal() const { return real; }
    double getImag() const { return imag; }
};

// TODO 11: 2D Vector class with operator overloading
class Vector2D {
private:
    double x, y;
    
public:
    Vector2D(double x_val = 0, double y_val = 0) : x(x_val), y(y_val) {}
    
    // TODO: Vector operations
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    // Scalar multiplication
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    // Dot product
    double dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }
    
    double magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    // TODO 12: Comparison operators
    bool operator==(const Vector2D& other) const {
        return (x == other.x) && (y == other.y);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

void problem_set_2_demo() {
    printf("=== Problem Set 2: Operator Overloading ===\n\n");
    
    // Test Complex class
    printf("Complex Number Operations:\n");
    
    Complex c1(3, 4);    // 3 + 4i
    Complex c2(1, -2);   // 1 - 2i
    
    std::cout << "  c1 = " << c1 << "\n";
    std::cout << "  c2 = " << c2 << "\n";
    
    Complex sum = c1 + c2;
    Complex diff = c1 - c2;
    Complex prod = c1 * c2;
    
    std::cout << "  c1 + c2 = " << sum << "\n";
    std::cout << "  c1 - c2 = " << diff << "\n";
    std::cout << "  c1 * c2 = " << prod << "\n";
    
    // Test Vector2D class
    printf("\nVector2D Operations:\n");
    
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);
    
    std::cout << "  v1 = " << v1 << "\n";
    std::cout << "  v2 = " << v2 << "\n";
    
    Vector2D v_sum = v1 + v2;
    Vector2D v_diff = v1 - v2;
    Vector2D v_scaled = v1 * 2.5;
    
    std::cout << "  v1 + v2 = " << v_sum << "\n";
    std::cout << "  v1 - v2 = " << v_diff << "\n";
    std::cout << "  v1 * 2.5 = " << v_scaled << "\n";
    std::cout << "  v1 · v2 = " << v1.dot(v2) << "\n";
    std::cout << "  |v1| = " << v1.magnitude() << "\n";
    
    printf("\n");
}

// ============================================================================
// PROBLEM SET 3: Bitwise Operations (45 minutes)
// ============================================================================

// TODO 13: Flag system using bitwise operations
enum FilePermissions {
    READ    = 1,      // 001
    WRITE   = 2,      // 010  
    EXECUTE = 4       // 100
};

void demonstrate_flags() {
    printf("=== Flag Management with Bitwise Operators ===\n");
    
    // TODO 14: Setting, checking, and clearing flags
    unsigned int permissions = 0;  // No permissions initially
    
    printf("Initial permissions: %d (binary: ", permissions);
    for (int i = 2; i >= 0; i--) {
        printf("%d", (permissions >> i) & 1);
    }
    printf(")\n");
    
    // Set READ permission
    permissions |= READ;
    printf("After adding READ: %d\n", permissions);
    
    // Set WRITE permission  
    permissions |= WRITE;
    printf("After adding WRITE: %d\n", permissions);
    
    // Check if WRITE permission exists
    if (permissions & WRITE) {
        printf("WRITE permission is set\n");
    }
    
    // Remove WRITE permission
    permissions &= ~WRITE;
    printf("After removing WRITE: %d\n", permissions);
    
    // Toggle EXECUTE permission
    permissions ^= EXECUTE;
    printf("After toggling EXECUTE: %d\n", permissions);
    
    permissions ^= EXECUTE;  // Toggle again
    printf("After toggling EXECUTE again: %d\n", permissions);
    
    printf("\n");
}

void bit_manipulation_lab() {
    printf("=== Bit Manipulation Laboratory ===\n");
    
    // TODO 15: Individual bit operations
    unsigned char byte = 0;  // Start with all bits clear
    
    printf("Starting byte: %d (0x%02X)\n", byte, byte);
    
    // Set specific bits
    byte |= (1 << 3);  // Set bit 3
    printf("After setting bit 3: %d (0x%02X)\n", byte, byte);
    
    byte |= (1 << 0);  // Set bit 0
    printf("After setting bit 0: %d (0x%02X)\n", byte, byte);
    
    // Check if a bit is set
    int bit_position = 3;
    bool is_set = (byte & (1 << bit_position)) != 0;
    printf("Bit %d is %s\n", bit_position, is_set ? "set" : "clear");
    
    // Clear a specific bit
    byte &= ~(1 << 3);  // Clear bit 3
    printf("After clearing bit 3: %d (0x%02X)\n", byte, byte);
    
    // Toggle a bit
    byte ^= (1 << 1);   // Toggle bit 1
    printf("After toggling bit 1: %d (0x%02X)\n", byte, byte);
    
    printf("\n");
}

void efficient_arithmetic() {
    printf("=== Efficient Arithmetic with Bit Shifts ===\n");
    
    // TODO 16: Multiplication and division using shifts
    int number = 12;
    printf("Original number: %d\n", number);
    
    // Multiplication by powers of 2 using left shift
    int mult_by_2 = number << 1;   // Same as number * 2
    int mult_by_4 = number << 2;   // Same as number * 4  
    int mult_by_8 = number << 3;   // Same as number * 8
    
    printf("  %d << 1 = %d (multiply by 2)\n", number, mult_by_2);
    printf("  %d << 2 = %d (multiply by 4)\n", number, mult_by_4);
    printf("  %d << 3 = %d (multiply by 8)\n", number, mult_by_8);
    
    // Division by powers of 2 using right shift
    number = 32;
    int div_by_2 = number >> 1;    // Same as number / 2
    int div_by_4 = number >> 2;    // Same as number / 4
    int div_by_8 = number >> 3;    // Same as number / 8
    
    printf("  %d >> 1 = %d (divide by 2)\n", number, div_by_2);
    printf("  %d >> 2 = %d (divide by 4)\n", number, div_by_4);
    printf("  %d >> 3 = %d (divide by 8)\n", number, div_by_8);
    
    // TODO 17: Check if number is power of 2
    auto is_power_of_2 = [](int n) {
        return n > 0 && (n & (n - 1)) == 0;
    };
    
    printf("\nPower of 2 check:\n");
    for (int test : {1, 2, 3, 4, 5, 8, 15, 16}) {
        printf("  %d is %s power of 2\n", test, 
               is_power_of_2(test) ? "a" : "not a");
    }
    
    printf("\n");
}

void problem_set_3_demo() {
    printf("=== Problem Set 3: Bitwise Operations ===\n\n");
    
    demonstrate_flags();
    bit_manipulation_lab();
    efficient_arithmetic();
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("      HW_07: Expressions and Operators\n");
    printf("==========================================\n\n");
    
    // Problem Set 1: Operator Basics (45 min)
    problem_set_1_demo();
    
    // Problem Set 2: Operator Overloading (45 min)
    problem_set_2_demo();
    
    // Problem Set 3: Bitwise Operations (45 min)
    problem_set_3_demo();
    
    printf("==========================================\n");
    printf("           Program Complete!\n");
    printf("==========================================\n");
    
    return 0;
}