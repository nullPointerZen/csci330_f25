// Problem 3.2 Solution: Design Challenge - When NOT to Overload
// Analysis of good vs. bad operator overloading decisions

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ORIGINAL DESIGNS WITH ANALYSIS

// Design 1: Student class - MIXED (some good, some bad)
class Student {
private:
    string name;
    double gpa;
    
public:
    Student(const string& name, double gpa) : name(name), gpa(gpa) {}
    
    // BAD: operator+ for combining students is confusing
    // What does it mean to "add" two students?
    Student operator+(const Student& other) const {
        return Student(name + " & " + other.name, (gpa + other.gpa) / 2);
    }
    
    // GOOD: operator< for comparison makes sense for sorting
    bool operator<(const Student& other) const {
        return gpa < other.gpa;  // Sort by GPA
    }
    
    // BAD: operator<< abuse - this should be for output, not enrollment
    Student& operator<<(const string& course) {
        cout << name << " enrolled in " << course << endl;
        return *this;
    }
    
    string get_name() const { return name; }
    double get_gpa() const { return gpa; }
    
    // BETTER ALTERNATIVES:
    
    // Instead of operator+, use descriptive function
    Student create_study_group_with(const Student& other) const {
        return Student(name + " & " + other.name, (gpa + other.gpa) / 2);
    }
    
    // Instead of operator<<, use descriptive function
    void enroll_in(const string& course) {
        cout << name << " enrolled in " << course << endl;
    }
};

// GOOD: Proper stream output operator
ostream& operator<<(ostream& os, const Student& student) {
    os << student.get_name() << " (GPA: " << student.get_gpa() << ")";
    return os;
}

// Design 2: BankAccount class - MIXED
class BankAccount {
private:
    string account_number;
    double balance;
    
public:
    BankAccount(const string& account_number, double initial_balance = 0.0) 
        : account_number(account_number), balance(initial_balance) {}
    
    // QUESTIONABLE: operator+ for adding money might be confusing
    // Does this modify the account or create a new one?
    BankAccount operator+(double amount) const {
        return BankAccount(account_number, balance + amount);
    }
    
    // BAD: operator- between accounts doesn't make intuitive sense
    // What does "account1 - account2" mean? Transfer? Difference?
    BankAccount operator-(const BankAccount& other) const {
        return BankAccount(account_number, balance - other.balance);
    }
    
    // GOOD: operator> for comparing balances makes sense
    bool operator>(const BankAccount& other) const {
        return balance > other.balance;
    }
    
    double get_balance() const { return balance; }
    string get_account_number() const { return account_number; }
    
    // BETTER ALTERNATIVES:
    
    // Instead of operator+, use descriptive functions
    void deposit(double amount) {
        balance += amount;
    }
    
    BankAccount create_account_with_balance(double new_balance) const {
        return BankAccount(account_number, new_balance);
    }
    
    // Instead of confusing operator-, use clear function names
    double get_balance_difference(const BankAccount& other) const {
        return balance - other.balance;
    }
    
    bool transfer_to(BankAccount& other, double amount) {
        if (balance >= amount) {
            balance -= amount;
            other.balance += amount;
            return true;
        }
        return false;
    }
};

// GOOD: Stream output operator
ostream& operator<<(ostream& os, const BankAccount& account) {
    os << "Account " << account.get_account_number() 
       << " (Balance: $" << account.get_balance() << ")";
    return os;
}

// IMPROVED DESIGNS

// Improved Student class - only appropriate operators
class ImprovedStudent {
private:
    string name;
    double gpa;
    vector<string> courses;
    
public:
    ImprovedStudent(const string& name, double gpa) : name(name), gpa(gpa) {}
    
    // GOOD: Comparison operators for sorting
    bool operator<(const ImprovedStudent& other) const {
        return gpa < other.gpa;
    }
    
    bool operator==(const ImprovedStudent& other) const {
        return name == other.name && gpa == other.gpa;
    }
    
    // GOOD: Use descriptive function names for complex operations
    void enroll_in_course(const string& course) {
        courses.push_back(course);
        cout << name << " enrolled in " << course << endl;
    }
    
    ImprovedStudent merge_study_data_with(const ImprovedStudent& other) const {
        ImprovedStudent result(name + " & " + other.name, (gpa + other.gpa) / 2);
        return result;
    }
    
    string get_name() const { return name; }
    double get_gpa() const { return gpa; }
};

// Improved BankAccount class - minimal, clear operators
class ImprovedBankAccount {
private:
    string account_number;
    double balance;
    
public:
    ImprovedBankAccount(const string& account_number, double initial_balance = 0.0) 
        : account_number(account_number), balance(initial_balance) {}
    
    // GOOD: Comparison operators for account balances
    bool operator>(const ImprovedBankAccount& other) const {
        return balance > other.balance;
    }
    
    bool operator<(const ImprovedBankAccount& other) const {
        return balance < other.balance;
    }
    
    bool operator==(const ImprovedBankAccount& other) const {
        return account_number == other.account_number;  // Same account
    }
    
    // GOOD: Clear, descriptive function names
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    bool transfer_to(ImprovedBankAccount& other, double amount) {
        if (withdraw(amount)) {
            other.deposit(amount);
            return true;
        }
        return false;
    }
    
    double get_balance() const { return balance; }
    string get_account_number() const { return account_number; }
};

int main() {
    cout << "=== ANALYSIS OF ORIGINAL DESIGNS ===" << endl;
    
    // Test original Student design
    Student alice("Alice", 3.8);
    Student bob("Bob", 3.2);
    
    cout << "\nOriginal Student class issues:" << endl;
    
    // This feels unnatural - what does "adding" students mean?
    Student combined = alice + bob;
    cout << "alice + bob = " << combined.get_name() 
         << " with GPA: " << combined.get_gpa() << endl;
    cout << "PROBLEM: operator+ doesn't have clear meaning for students" << endl;
    
    // This abuses the << operator
    cout << "\nAbusing << operator:" << endl;
    alice << "Mathematics" << "Physics";
    cout << "PROBLEM: << should be for output, not enrollment" << endl;
    
    // This is actually good - sorting students by GPA makes sense
    cout << "\nGood use of < operator:" << endl;
    if (alice < bob) {
        cout << "Alice has lower GPA than Bob" << endl;
    } else {
        cout << "Alice has higher GPA than Bob" << endl;
    }
    
    // Test original BankAccount design
    cout << "\nOriginal BankAccount class issues:" << endl;
    BankAccount account1("12345", 1000.0);
    BankAccount account2("67890", 500.0);
    
    // This is confusing - does it modify account1 or create new account?
    BankAccount after_deposit = account1 + 200.0;
    cout << "account1 + 200 creates new account with balance: $" 
         << after_deposit.get_balance() << endl;
    cout << "PROBLEM: Unclear if this modifies account or creates new one" << endl;
    
    // This is very confusing - what does account1 - account2 mean?
    BankAccount after_transfer = account1 - account2;
    cout << "account1 - account2 creates account with balance: $" 
         << after_transfer.get_balance() << endl;
    cout << "PROBLEM: What does subtracting accounts mean?" << endl;
    
    cout << "\n=== IMPROVED DESIGNS ===" << endl;
    
    // Test improved Student design
    ImprovedStudent alice_v2("Alice", 3.8);
    ImprovedStudent bob_v2("Bob", 3.2);
    
    cout << "\nImproved Student class:" << endl;
    alice_v2.enroll_in_course("Mathematics");  // Clear function name
    alice_v2.enroll_in_course("Physics");
    
    ImprovedStudent study_group = alice_v2.merge_study_data_with(bob_v2);
    cout << "Study group: " << study_group.get_name() << endl;
    cout << "IMPROVEMENT: Clear function names express intent" << endl;
    
    // Test improved BankAccount design
    cout << "\nImproved BankAccount class:" << endl;
    ImprovedBankAccount acc1("12345", 1000.0);
    ImprovedBankAccount acc2("67890", 500.0);
    
    acc1.deposit(200.0);  // Clear operation
    cout << "After deposit: " << acc1.get_balance() << endl;
    
    if (acc1.transfer_to(acc2, 100.0)) {  // Clear operation
        cout << "Transfer successful" << endl;
        cout << "acc1 balance: $" << acc1.get_balance() << endl;
        cout << "acc2 balance: $" << acc2.get_balance() << endl;
    }
    cout << "IMPROVEMENT: Operations are explicit and clear" << endl;
    
    cout << "\n=== DESIGN PRINCIPLES ===" << endl;
    cout << "GOOD operator overloading:" << endl;
    cout << "- Mathematical types (Vector, Matrix, Complex numbers)" << endl;
    cout << "- Comparison operators for sorting" << endl;
    cout << "- Stream operators for I/O" << endl;
    cout << "- Operators where meaning is obvious and intuitive" << endl;
    
    cout << "\nBAD operator overloading:" << endl;
    cout << "- Operations where meaning is unclear" << endl;
    cout << "- Surprising or non-intuitive behavior" << endl;
    cout << "- Repurposing operators for unrelated functionality" << endl;
    cout << "- When a descriptive function name would be clearer" << endl;
    
    return 0;
}

/*
Expected Output:
=== ANALYSIS OF ORIGINAL DESIGNS ===

Original Student class issues:
alice + bob = Alice & Bob with GPA: 3.5
PROBLEM: operator+ doesn't have clear meaning for students

Abusing << operator:
Alice enrolled in Mathematics
Alice enrolled in Physics
PROBLEM: << should be for output, not enrollment

Good use of < operator:
Alice has higher GPA than Bob

Original BankAccount class issues:
account1 + 200 creates new account with balance: $1200
PROBLEM: Unclear if this modifies account or creates new one
account1 - account2 creates account with balance: $500
PROBLEM: What does subtracting accounts mean?

=== IMPROVED DESIGNS ===

Improved Student class:
Alice enrolled in Mathematics
Alice enrolled in Physics
Study group: Alice & Bob
IMPROVEMENT: Clear function names express intent

Improved BankAccount class:
After deposit: 1200
Transfer successful
acc1 balance: $1100
acc2 balance: $600
IMPROVEMENT: Operations are explicit and clear

=== DESIGN PRINCIPLES ===
GOOD operator overloading:
- Mathematical types (Vector, Matrix, Complex numbers)
- Comparison operators for sorting
- Stream operators for I/O
- Operators where meaning is obvious and intuitive

BAD operator overloading:
- Operations where meaning is unclear
- Surprising or non-intuitive behavior
- Repurposing operators for unrelated functionality
- When a descriptive function name would be clearer

ANALYSIS SUMMARY:

Design 1 (Student class):
- operator+(): BAD - "Adding" students has no clear meaning
- operator<(): GOOD - Comparing for sorting by GPA makes sense
- operator<<(): BAD - Abuses stream operator for enrollment
- Better alternatives: create_study_group_with(), enroll_in_course()

Design 2 (BankAccount class):
- operator+(): BAD - Unclear if it modifies account or creates new one
- operator-(): BAD - Subtracting accounts has no intuitive meaning
- operator>(): GOOD - Comparing balances makes sense
- Better alternatives: deposit(), withdraw(), transfer_to()

Key Principles:
1. Only overload operators when the meaning is immediately obvious
2. Don't surprise users - operators should behave as expected
3. Use descriptive function names when operations are complex
4. Mathematical operations are usually good candidates
5. Comparison operators are often appropriate
6. Stream operators should be for I/O only
*/