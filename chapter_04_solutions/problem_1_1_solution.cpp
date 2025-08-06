// Problem 1.1: Simple Bank Account Solution
// Demonstrates basic constructor and destructor

#include <cstdio>

class BankAccount {
public:
    BankAccount(double initial_balance) : balance{initial_balance} {
        printf("Account created with balance: $%.2f\n", balance);
    }
    
    ~BankAccount() {
        printf("Account closed. Final balance was: $%.2f\n", balance);
    }
    
    void display_balance() {
        printf("Current balance: $%.2f\n", balance);
    }
    
private:
    double balance;
};

int main() {
    printf("=== Creating bank account ===\n");
    BankAccount account{100.50};
    account.display_balance();
    printf("=== About to exit main ===\n");
    return 0;
    // Destructor called automatically here
}

/* 
Compilation command:
g++ -o bank_account problem_1_1_solution.cpp

Expected Output:
=== Creating bank account ===
Account created with balance: $100.50
Current balance: $100.50
=== About to exit main ===
Account closed. Final balance was: $100.50

Key Learning Points:
1. Constructor runs when object is created
2. Destructor runs automatically when object goes out of scope
3. Constructor syntax: ClassName(params) : member{value} { }
4. No return type in constructor/destructor
5. Similar to Python __init__ but different syntax
*/