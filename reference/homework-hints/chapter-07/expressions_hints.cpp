#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

// =============================================================================
// CHAPTER 7: EXPRESSIONS - COMPREHENSIVE HOMEWORK HINTS
// =============================================================================
// This file provides complete working solutions and explanations for all
// Chapter 7 expression and operator overloading concepts.
// =============================================================================

using namespace std;

// =============================================================================
// PROBLEM SET 1: EXPRESSION FUNDAMENTALS
// =============================================================================

namespace problem_set_1 {

// -----------------------------------------------------------------------------
// Problem 1.1: Precedence Detective - Understanding operator precedence
// -----------------------------------------------------------------------------
void precedence_detective() {
    cout << "\n=== Problem 1.1: Precedence Detective ===\n\n";

    int a = 10, b = 20, c = 5;

    // Question 1: Multiplication has higher precedence than addition
    // Evaluates as: a + (b * c) = 10 + 100 = 110
    int result1 = a + b * c;
    cout << "a + b * c = " << result1 << " (expected 110)\n";
    cout << "Explanation: * has higher precedence than +, so b*c is evaluated first\n\n";

    // Question 2: Parentheses force different evaluation order
    // Evaluates as: (a + b) * c = 30 * 5 = 150
    int result2 = (a + b) * c;
    cout << "(a + b) * c = " << result2 << " (expected 150)\n";
    cout << "Explanation: Parentheses have highest precedence\n\n";

    // Question 3: Logical AND with comparison operators
    // Evaluates as: (a < b) && (b > c) = true && true = 1
    int result3 = a < b && b > c;
    cout << "a < b && b > c = " << result3 << " (expected 1/true)\n";
    cout << "Explanation: Comparison operators evaluated before &&\n\n";

    // Question 4: Mixing OR and AND - AND has higher precedence
    // Evaluates as: (a < b) || ((b < c) && (c > a))
    //            = true || (false && true) = true || false = true
    bool result4 = a < b || b < c && c > a;
    cout << "a < b || b < c && c > a = " << result4 << " (expected 1/true)\n";
    cout << "Explanation: && has higher precedence than ||, so (b<c && c>a) groups first\n\n";

    // Question 5: Prefix vs postfix increment
    // ++x increments x first, then returns new value (6)
    // x++ returns current value (6), then increments to 7
    // y = 6 + 6 = 12
    int x = 5;
    int y = ++x + x++;
    cout << "int x = 5; int y = ++x + x++;\n";
    cout << "x = " << x << " (expected 7), y = " << y << " (expected 12)\n";
    cout << "Explanation: ++x makes x=6 and returns 6, then x++ returns 6 and makes x=7\n";
}

// -----------------------------------------------------------------------------
// Problem 1.2: Type Conversion Traps - Handling implicit conversions
// -----------------------------------------------------------------------------
void type_conversion_traps() {
    cout << "\n=== Problem 1.2: Type Conversion Traps ===\n\n";

    // Bug 1: Integer division problem - both operands are int
    // FIX: Cast at least one operand to double before division
    int total_items = 17;
    int groups = 5;

    cout << "Bug 1: Integer division\n";
    double average_wrong = total_items / groups;  // Gets 3.0
    double average_fixed = static_cast<double>(total_items) / groups;  // Gets 3.4
    cout << "Wrong: " << average_wrong << " (integer division gives 3.0)\n";
    cout << "Fixed: " << average_fixed << " (cast to double gives 3.4)\n";
    cout << "Explanation: Casting one operand to double makes the division floating-point\n\n";

    // Bug 2: Signed/unsigned comparison - surprising behavior
    // When comparing signed and unsigned, signed is converted to unsigned
    // -1 as unsigned becomes a very large positive number!
    cout << "Bug 2: Signed/unsigned comparison\n";
    int signed_value = -1;
    unsigned int unsigned_value = 1;

    // This comparison is DANGEROUS - signed_value converts to huge unsigned
    if (signed_value < unsigned_value) {
        cout << "WRONG: This might not print when you expect!\n";
    } else {
        cout << "Due to conversion, -1 becomes huge unsigned value\n";
    }

    // FIX: Cast to same type for safe comparison
    if (signed_value < static_cast<int>(unsigned_value)) {
        cout << "Fixed: Now -1 < 1 works correctly\n";
    }
    cout << "Explanation: Mixed signed/unsigned comparisons are dangerous\n\n";

    // Bug 3: Loss of precision - truncation vs rounding
    cout << "Bug 3: Truncation vs Rounding\n";
    double precise_value = 3.99999;
    int truncated = precise_value;  // Truncates to 3
    int rounded = static_cast<int>(round(precise_value));  // Rounds to 4

    cout << "Truncated: " << truncated << " (just chops off decimal)\n";
    cout << "Rounded: " << rounded << " (proper rounding)\n";
    cout << "Explanation: Use std::round() from <cmath> for proper rounding\n";
}

// -----------------------------------------------------------------------------
// Problem 1.3: Compound Assignment Efficiency
// -----------------------------------------------------------------------------
void compound_assignment() {
    cout << "\n=== Problem 1.3: Compound Assignment Operators ===\n\n";

    // Compound assignment operators are more efficient and clearer
    int score = 100;
    cout << "Starting score: " << score << endl;

    // Instead of: score = score + 50
    score += 50;
    cout << "After += 50: " << score << endl;

    // Instead of: score = score * 2
    score *= 2;
    cout << "After *= 2: " << score << endl;

    // Instead of: score = score - 25
    score -= 25;
    cout << "After -= 25: " << score << endl;

    // Instead of: score = score / 3
    score /= 3;
    cout << "After /= 3: " << score << endl;

    // Instead of: score = score % 10
    score %= 10;
    cout << "After %= 10: " << score << endl;

    // Works with strings too!
    string message = "Hello";
    message += " ";      // Instead of: message = message + " "
    message += "World";  // Instead of: message = message + "World"
    message += "!";      // Instead of: message = message + "!"
    cout << "\nMessage: " << message << endl;

    // Works with boolean operators
    bool flags = true;
    flags = flags && false;  // Could use &&= but rarely seen
    flags = flags || true;   // Could use ||= but rarely seen
    cout << "Flags: " << flags << endl;

    cout << "\nWhy compound operators are better:\n";
    cout << "1. More concise and readable\n";
    cout << "2. Clearly shows intent to modify in place\n";
    cout << "3. Only evaluates left-hand side once (important for complex expressions)\n";
    cout << "4. Can be more efficient for complex objects\n";
}

} // namespace problem_set_1

// =============================================================================
// PROBLEM SET 2: BASIC OPERATOR OVERLOADING
// =============================================================================

namespace problem_set_2 {

// -----------------------------------------------------------------------------
// Problem 2.1: Money Class with Arithmetic Operators
// -----------------------------------------------------------------------------
class Money {
private:
    int cents;  // Store as cents to avoid floating-point issues

public:
    // Constructor: takes dollars and cents as separate parameters
    Money(int dollars = 0, int cents_param = 0) : cents(dollars * 100 + cents_param) {}

private:
    // Private constructor for internal use with total cents
    explicit Money(int total_cents, bool) : cents(total_cents) {}

public:

    // Addition operator - returns new Money object
    Money operator+(const Money& other) const {
        return Money(cents + other.cents, true);  // Use private constructor
    }

    // Subtraction operator - returns new Money object
    Money operator-(const Money& other) const {
        return Money(cents - other.cents, true);  // Use private constructor
    }

    // Compound addition - modifies this object and returns reference
    Money& operator+=(const Money& other) {
        cents += other.cents;
        return *this;  // Return reference to allow chaining
    }

    // Compound subtraction - modifies this object and returns reference
    Money& operator-=(const Money& other) {
        cents -= other.cents;
        return *this;  // Return reference to allow chaining
    }

    // Equality comparison
    bool operator==(const Money& other) const {
        return cents == other.cents;
    }

    // Not equal comparison (implemented in terms of ==)
    bool operator!=(const Money& other) const {
        return !(*this == other);
    }

    // Less than comparison
    bool operator<(const Money& other) const {
        return cents < other.cents;
    }

    // Greater than comparison (implemented in terms of <)
    bool operator>(const Money& other) const {
        return other < *this;
    }

    // Less than or equal (implemented in terms of < and ==)
    bool operator<=(const Money& other) const {
        return !(other < *this);
    }

    // Greater than or equal (implemented in terms of <)
    bool operator>=(const Money& other) const {
        return !(*this < other);
    }

    // Display function
    void print() const {
        cout << "$" << cents / 100 << "."
             << setfill('0') << setw(2) << cents % 100;
    }

    // Getter for testing
    int get_cents() const { return cents; }
};

void money_class_demo() {
    cout << "\n=== Problem 2.1: Money Class with Arithmetic ===\n\n";

    Money wallet(25, 50);  // $25.50
    Money coffee(4, 75);   // $4.75
    Money lunch(12, 30);   // $12.30

    cout << "Starting amount: ";
    wallet.print();
    cout << endl;

    // Test subtraction operator
    Money after_coffee = wallet - coffee;
    cout << "After buying coffee ($4.75): ";
    after_coffee.print();
    cout << endl;

    // Test compound subtraction
    after_coffee -= lunch;
    cout << "After buying lunch ($12.30): ";
    after_coffee.print();
    cout << endl;

    // Test addition operator
    Money total_spent = coffee + lunch;
    cout << "Total spent: ";
    total_spent.print();
    cout << endl;

    // Test comparison operators
    if (after_coffee < Money(10, 0)) {
        cout << "Running low on money!" << endl;
    }

    // Demonstrate operator chaining
    Money account(100, 0);
    account += Money(50, 0) += Money(25, 0);  // Chaining works!
    cout << "\nAfter chained additions: ";
    account.print();
    cout << endl;

    cout << "\nKey Points:\n";
    cout << "1. Store money as cents (integer) to avoid floating-point errors\n";
    cout << "2. Binary operators (+, -) return new objects by value\n";
    cout << "3. Compound operators (+=, -=) modify object and return reference\n";
    cout << "4. Implement comparison operators in terms of < and ==\n";
}

// -----------------------------------------------------------------------------
// Problem 2.2: Vector2D with Mathematical Operations
// -----------------------------------------------------------------------------
class Vector2D {
private:
    double x, y;

public:
    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    // Getters
    double get_x() const { return x; }
    double get_y() const { return y; }

    // Vector addition - component-wise
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // Vector subtraction - component-wise
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // Scalar multiplication (vector * scalar)
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // Dot product (vector * vector) - returns scalar!
    // Note: Same operator symbol, different meaning based on parameter type
    double operator*(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }

    // Compound addition
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Equality comparison (careful with floating-point!)
    bool operator==(const Vector2D& other) const {
        const double EPSILON = 1e-9;
        return abs(x - other.x) < EPSILON && abs(y - other.y) < EPSILON;
    }

    // Calculate magnitude (length of vector)
    double magnitude() const {
        return sqrt(x * x + y * y);
    }

    // Normalize vector (make it unit length)
    Vector2D normalize() const {
        double mag = magnitude();
        if (mag == 0.0) return Vector2D(0, 0);
        return Vector2D(x / mag, y / mag);
    }
};

// Non-member function: Scalar multiplication (scalar * vector)
// Must be non-member because scalar is on the left side
Vector2D operator*(double scalar, const Vector2D& vec) {
    return vec * scalar;  // Reuse the member function
}

// Non-member function: Stream output operator
// Must be non-member because ostream is on the left side
ostream& operator<<(ostream& os, const Vector2D& vec) {
    os << "(" << vec.get_x() << ", " << vec.get_y() << ")";
    return os;
}

void vector2d_demo() {
    cout << "\n=== Problem 2.2: Vector2D with Mathematical Operations ===\n\n";

    Vector2D v1(3.0, 4.0);
    Vector2D v2(1.0, 2.0);

    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;

    // Vector addition
    Vector2D sum = v1 + v2;
    cout << "\nv1 + v2: " << sum << endl;

    // Scalar multiplication (vector * scalar)
    Vector2D scaled = v1 * 2.0;
    cout << "v1 * 2: " << scaled << endl;

    // Scalar multiplication (scalar * vector) - uses non-member function
    Vector2D scaled2 = 3.0 * v2;
    cout << "3 * v2: " << scaled2 << endl;

    // Dot product (different meaning of operator* based on parameter type!)
    double dot = v1 * v2;
    cout << "\nv1 · v2 (dot product): " << dot << endl;

    // Magnitude and normalization
    cout << "\nMagnitude of v1: " << v1.magnitude() << endl;
    cout << "v1 normalized: " << v1.normalize() << endl;

    // Verify normalized vector has magnitude 1
    Vector2D normalized = v1.normalize();
    cout << "Magnitude of normalized v1: " << normalized.magnitude() << endl;

    cout << "\nKey Points:\n";
    cout << "1. Same operator (*) can have different meanings based on parameter types\n";
    cout << "2. Non-member functions needed when left operand is not our class\n";
    cout << "3. Stream operators (<<) must be non-member functions\n";
    cout << "4. Be careful with floating-point comparisons - use epsilon\n";
}

} // namespace problem_set_2

// =============================================================================
// PROBLEM SET 3: ADVANCED OPERATORS AND BEST PRACTICES
// =============================================================================

namespace problem_set_3 {

// -----------------------------------------------------------------------------
// Problem 3.1: Smart Counter with All Comparison Operators
// -----------------------------------------------------------------------------
class Counter {
private:
    int value;

public:
    Counter(int initial_value = 0) : value(initial_value) {}

    // Prefix increment (++counter) - increment then return new value
    Counter& operator++() {
        ++value;
        return *this;  // Return reference to allow chaining
    }

    // Postfix increment (counter++) - return old value then increment
    // The int parameter distinguishes this from prefix version
    Counter operator++(int) {
        Counter temp = *this;  // Save current state
        ++value;               // Increment
        return temp;           // Return old state
    }

    // Primary comparison operators - implement these first
    bool operator==(const Counter& other) const {
        return value == other.value;
    }

    bool operator<(const Counter& other) const {
        return value < other.value;
    }

    // Derived comparison operators - implement in terms of == and <
    // This ensures consistency and reduces code duplication

    bool operator!=(const Counter& other) const {
        return !(*this == other);  // Not equal is opposite of equal
    }

    bool operator<=(const Counter& other) const {
        return *this < other || *this == other;  // Less or equal
    }

    bool operator>(const Counter& other) const {
        return !(*this <= other);  // Greater is opposite of less-or-equal
    }

    bool operator>=(const Counter& other) const {
        return !(*this < other);  // Greater-or-equal is opposite of less
    }

    // For output
    int get_value() const { return value; }
};

void counter_demo() {
    cout << "\n=== Problem 3.1: Smart Counter with All Comparison Operators ===\n\n";

    Counter c1(5);
    Counter c2(10);
    Counter c3(5);

    cout << "c1: " << c1.get_value() << endl;
    cout << "c2: " << c2.get_value() << endl;
    cout << "c3: " << c3.get_value() << endl;

    // Test all comparison operators
    cout << "\nComparison tests:" << endl;
    cout << "c1 == c3: " << (c1 == c3) << " (expected 1/true)" << endl;
    cout << "c1 != c2: " << (c1 != c2) << " (expected 1/true)" << endl;
    cout << "c1 < c2: " << (c1 < c2) << " (expected 1/true)" << endl;
    cout << "c1 <= c3: " << (c1 <= c3) << " (expected 1/true)" << endl;
    cout << "c2 > c1: " << (c2 > c1) << " (expected 1/true)" << endl;
    cout << "c2 >= c1: " << (c2 >= c1) << " (expected 1/true)" << endl;

    // Test increment operators
    cout << "\nIncrement tests:" << endl;
    cout << "++c1: " << (++c1).get_value() << " (expected 6)" << endl;
    cout << "c1 value after prefix: " << c1.get_value() << endl;

    cout << "c1++ (returns old): " << (c1++).get_value() << " (expected 6)" << endl;
    cout << "c1 value after postfix: " << c1.get_value() << " (expected 7)" << endl;

    // Demonstrate chaining with prefix increment
    Counter c4(0);
    ++++c4;  // Can chain prefix operators!
    cout << "\nAfter ++++c4: " << c4.get_value() << " (expected 2)" << endl;

    cout << "\nKey Points:\n";
    cout << "1. Implement == and < first, derive others from these\n";
    cout << "2. Prefix ++ returns reference (allows chaining)\n";
    cout << "3. Postfix ++ takes dummy int parameter and returns by value\n";
    cout << "4. Postfix is less efficient due to copy\n";
}

// -----------------------------------------------------------------------------
// Problem 3.2: Design Challenge - When NOT to Overload
// -----------------------------------------------------------------------------

// BAD EXAMPLES - These operators don't make intuitive sense

class StudentBad {
private:
    string name;
    double gpa;

public:
    StudentBad(const string& name, double gpa) : name(name), gpa(gpa) {}

    // BAD: What does "adding" students mean? Not intuitive!
    StudentBad operator+(const StudentBad& other) const {
        return StudentBad(name + " & " + other.name, (gpa + other.gpa) / 2);
    }

    // ACCEPTABLE: Comparing by GPA for sorting is reasonable
    bool operator<(const StudentBad& other) const {
        return gpa < other.gpa;
    }

    // BAD: << should be for output, not enrollment!
    StudentBad& operator<<(const string& course) {
        cout << name << " enrolled in " << course << endl;
        return *this;
    }

    string get_name() const { return name; }
    double get_gpa() const { return gpa; }
};

// GOOD EXAMPLE - Better design with clear method names

class StudentGood {
private:
    string name;
    double gpa;

public:
    StudentGood(const string& name, double gpa) : name(name), gpa(gpa) {}

    // GOOD: Use clear method names instead of confusing operators
    static StudentGood create_study_group(const StudentGood& s1, const StudentGood& s2) {
        return StudentGood(s1.name + " & " + s2.name, (s1.gpa + s2.gpa) / 2);
    }

    // GOOD: Comparison for sorting is fine
    bool operator<(const StudentGood& other) const {
        return gpa < other.gpa;
    }

    // GOOD: Clear method name
    void enroll_in(const string& course) {
        cout << name << " enrolled in " << course << endl;
    }

    string get_name() const { return name; }
    double get_gpa() const { return gpa; }
};

// Stream output operator - GOOD use of <<
ostream& operator<<(ostream& os, const StudentGood& student) {
    os << student.get_name() << " (GPA: " << student.get_gpa() << ")";
    return os;
}

class BankAccountBad {
private:
    string account_number;
    double balance;

public:
    BankAccountBad(const string& account_number, double initial_balance = 0.0)
        : account_number(account_number), balance(initial_balance) {}

    // QUESTIONABLE: Creates new account instead of modifying existing one
    BankAccountBad operator+(double amount) const {
        return BankAccountBad(account_number, balance + amount);
    }

    // BAD: Subtracting accounts doesn't make sense
    BankAccountBad operator-(const BankAccountBad& other) const {
        return BankAccountBad(account_number, balance - other.balance);
    }

    // ACCEPTABLE: Comparing balances for sorting might be okay
    bool operator>(const BankAccountBad& other) const {
        return balance > other.balance;
    }

    double get_balance() const { return balance; }
};

class BankAccountGood {
private:
    string account_number;
    double balance;

public:
    BankAccountGood(const string& account_number, double initial_balance = 0.0)
        : account_number(account_number), balance(initial_balance) {}

    // GOOD: Clear method names that express intent
    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    bool transfer_to(BankAccountGood& other, double amount) {
        if (withdraw(amount)) {
            other.deposit(amount);
            return true;
        }
        return false;
    }

    // GOOD: Comparison for sorting is fine
    bool operator<(const BankAccountGood& other) const {
        return balance < other.balance;
    }

    double get_balance() const { return balance; }
    string get_account_number() const { return account_number; }
};

// Stream output operator - GOOD use of <<
ostream& operator<<(ostream& os, const BankAccountGood& account) {
    os << "Account " << account.get_account_number()
       << ": $" << fixed << setprecision(2) << account.get_balance();
    return os;
}

void design_challenge_demo() {
    cout << "\n=== Problem 3.2: Design Challenge - When NOT to Overload ===\n\n";

    cout << "BAD DESIGN EXAMPLES:\n";
    cout << "-------------------\n\n";

    StudentBad alice_bad("Alice", 3.8);
    StudentBad bob_bad("Bob", 3.2);

    cout << "Student operator+ (BAD): ";
    StudentBad combined = alice_bad + bob_bad;
    cout << combined.get_name() << " with GPA " << combined.get_gpa() << endl;
    cout << "Problem: What does 'adding' students mean? Confusing!\n\n";

    cout << "Student operator<< for enrollment (BAD): ";
    alice_bad << "Mathematics" << "Physics";
    cout << "Problem: << should be for output, not side effects!\n\n";

    BankAccountBad account1("12345", 1000.0);
    BankAccountBad account2("67890", 500.0);

    cout << "BankAccount operator+ (QUESTIONABLE): ";
    BankAccountBad after_deposit = account1 + 200.0;
    cout << "$" << after_deposit.get_balance() << endl;
    cout << "Problem: Creates new account instead of modifying existing one\n\n";

    cout << "BankAccount operator- (BAD): ";
    BankAccountBad after_subtract = account1 - account2;
    cout << "$" << after_subtract.get_balance() << endl;
    cout << "Problem: What does 'subtracting accounts' mean? Nonsense!\n\n";

    cout << "\nGOOD DESIGN EXAMPLES:\n";
    cout << "--------------------\n\n";

    StudentGood alice_good("Alice", 3.8);
    StudentGood bob_good("Bob", 3.2);

    cout << "Using clear method names:\n";
    StudentGood group = StudentGood::create_study_group(alice_good, bob_good);
    cout << "Study group: " << group << endl;

    alice_good.enroll_in("Mathematics");
    alice_good.enroll_in("Physics");

    cout << "\nOutput operator (GOOD use of <<): " << alice_good << endl;

    BankAccountGood checking("12345", 1000.0);
    BankAccountGood savings("67890", 500.0);

    cout << "\nBankAccount with clear methods:\n";
    cout << "Before: " << checking << endl;
    checking.deposit(200.0);
    cout << "After deposit: " << checking << endl;

    cout << "\nTransferring $300 from checking to savings:\n";
    cout << "Before: " << checking << " | " << savings << endl;
    checking.transfer_to(savings, 300.0);
    cout << "After:  " << checking << " | " << savings << endl;

    cout << "\n=== GUIDELINES FOR OPERATOR OVERLOADING ===\n";
    cout << "\nGOOD uses of operator overloading:\n";
    cout << "1. Mathematical operations (Vector, Complex, Matrix)\n";
    cout << "2. Container operations (indexing with [])\n";
    cout << "3. Comparisons for sorting (operator<, operator==)\n";
    cout << "4. Stream I/O (operator<<, operator>>)\n";
    cout << "5. Smart pointers (operator*, operator->)\n\n";

    cout << "BAD uses of operator overloading:\n";
    cout << "1. Operations with unclear meaning (Student + Student)\n";
    cout << "2. Side effects with << instead of output\n";
    cout << "3. Operations that don't match intuition\n";
    cout << "4. Creating new objects when modification is expected\n\n";

    cout << "GOLDEN RULE:\n";
    cout << "If the operation doesn't have a clear, intuitive meaning,\n";
    cout << "use a named member function instead!\n";
}

} // namespace problem_set_3

// =============================================================================
// MAIN FUNCTION - Run all demonstrations
// =============================================================================

int main() {
    cout << "============================================\n";
    cout << "CHAPTER 7: EXPRESSIONS - HOMEWORK HINTS\n";
    cout << "============================================\n";

    // Problem Set 1: Expression Fundamentals
    problem_set_1::precedence_detective();
    problem_set_1::type_conversion_traps();
    problem_set_1::compound_assignment();

    // Problem Set 2: Basic Operator Overloading
    problem_set_2::money_class_demo();
    problem_set_2::vector2d_demo();

    // Problem Set 3: Advanced Operators and Best Practices
    problem_set_3::counter_demo();
    problem_set_3::design_challenge_demo();

    cout << "\n============================================\n";
    cout << "END OF HOMEWORK HINTS\n";
    cout << "============================================\n";

    return 0;
}

/*
=============================================================================
KEY LEARNING POINTS FOR CHAPTER 7
=============================================================================

1. OPERATOR PRECEDENCE:
   - Multiplication/division before addition/subtraction
   - && before ||
   - Use parentheses when in doubt
   - Prefix vs postfix increment have different semantics

2. TYPE CONVERSIONS:
   - Integer division truncates - cast to double for real division
   - Signed/unsigned mixing is dangerous
   - Use static_cast for explicit, safe conversions
   - Use std::round() for proper rounding, not truncation

3. COMPOUND OPERATORS:
   - More concise than expanded form (x += 5 vs x = x + 5)
   - Only evaluates left-hand side once
   - Shows clear intent to modify in place
   - Can be more efficient for complex types

4. OPERATOR OVERLOADING BASICS:
   - Binary operators (+, -, *) typically return new object by value
   - Compound operators (+=, -=) modify object and return reference
   - Mark operators const if they don't modify the object
   - Pass parameters by const reference when appropriate

5. COMPARISON OPERATORS:
   - Implement == and < first
   - Derive all others from these two
   - Ensures consistency across all comparisons
   - Reduces code duplication

6. INCREMENT/DECREMENT:
   - Prefix (++x): increment then return reference
   - Postfix (x++): return copy then increment
   - Postfix is less efficient due to copy
   - Dummy int parameter distinguishes postfix from prefix

7. MEMBER VS NON-MEMBER:
   - Member when left operand is your class (v * 2)
   - Non-member when left operand is not your class (2 * v)
   - Stream operators must be non-member (ostream is on left)
   - Non-member can often call member version

8. DESIGN PRINCIPLES:
   - Only overload when meaning is clear and intuitive
   - Use named functions when operation is non-obvious
   - Don't surprise users with unexpected behavior
   - Follow conventions from standard library

9. BEST PRACTICES:
   - Return reference from compound operators for chaining
   - Return by value from binary operators
   - Use const for operators that don't modify object
   - Be careful with floating-point comparisons (use epsilon)
   - Store money as integers (cents) to avoid floating-point errors

This comprehensive hints file covers all major concepts from Chapter 7
with complete, working, well-commented examples that students can learn from.
=============================================================================
*/
