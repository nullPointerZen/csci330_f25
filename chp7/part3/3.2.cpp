#include <iostream>
#include <string>
using namespace std;

// Design 1: Student class
class Student {
private:
    string name;
    double gpa;

public:
    Student(const string& name, double gpa) : name(name), gpa(gpa) {}

    // Merge two students (e.g., for group projects or GPA averaging)
    Student merge_with(const Student& other) const {
        return Student(name + " & " + other.name, (gpa + other.gpa) / 2);
    }

    // Compare students by GPA
    bool operator<(const Student& other) const {
        return gpa < other.gpa;
    }

    // Enroll student in a course
    void enroll_in(const string& course) const {
        cout << name << " enrolled in " << course << endl;
    }

    string get_name() const { return name; }
    double get_gpa() const { return gpa; }
};

// Design 2: BankAccount class
class BankAccount {
private:
    string account_number;
    double balance;

public:
    BankAccount(const string& account_number, double initial_balance = 0.0)
        : account_number(account_number), balance(initial_balance) {}

    // Deposit money
    BankAccount operator+(double amount) const {
        return BankAccount(account_number, balance + amount);
    }

    // Withdraw money
    BankAccount operator-(double amount) const {
        return BankAccount(account_number, balance - amount);
    }

    // Compare account balances
    bool operator>(const BankAccount& other) const {
        return balance > other.balance;
    }

    double get_balance() const { return balance; }
    string get_account_number() const { return account_number; }
};

int main() {
    // Student tests
    Student alice("Alice", 3.8);
    Student bob("Bob", 3.2);

    Student combined = alice.merge_with(bob);
    cout << "Combined student: " << combined.get_name()
         << " with GPA: " << combined.get_gpa() << endl;

    alice.enroll_in("Mathematics");
    alice.enroll_in("Physics");

    // BankAccount tests
    BankAccount account1("12345", 1000.0);
    BankAccount account2("67890", 500.0);

    BankAccount after_deposit = account1 + 200.0;
    cout << "After deposit: $" << after_deposit.get_balance() << endl;

    BankAccount after_withdrawal = account1 - 300.0;
    cout << "After withdrawal: $" << after_withdrawal.get_balance() << endl;

    cout << "Account1 > Account2: " << (account1 > account2) << endl;

    return 0;
}