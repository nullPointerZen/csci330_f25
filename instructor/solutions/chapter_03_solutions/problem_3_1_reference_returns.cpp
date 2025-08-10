// Problem 3.1: Reference Return Types
// Demonstrates functions that return references

#include <cstdio>

struct BankAccount {
    double balance;
    int account_number;
};

// Function that takes a const BankAccount reference and returns a const reference to the balance
const double& get_balance(const BankAccount& account) {
    return account.balance;
}

// Function that takes an array of BankAccount and an account number,
// then returns a reference to the matching account
BankAccount& get_account_for_update(BankAccount accounts[], int account_number) {
    // For simplicity, assume the account exists and is at index = account_number - 1
    return accounts[account_number - 1];
}

// Helper function to display account information
void display_account(const BankAccount& account) {
    printf("Account %d: $%.2f\n", account.account_number, account.balance);
}

int main() {
    BankAccount accounts[3] = {
        {1000.50, 1},
        {2500.75, 2}, 
        {750.25, 3}
    };
    
    // Use get_balance to display account 2's balance
    printf("Account 2 balance: $%.2f\n", get_balance(accounts[1]));
    
    // Use get_account_for_update to modify account 1's balance to 1200.00
    BankAccount& account_to_update = get_account_for_update(accounts, 1);
    account_to_update.balance = 1200.00;
    printf("Updated account 1 balance to $%.2f\n", account_to_update.balance);
    
    // Display all account balances
    printf("\nUpdated balances:\n");
    for (int i = 0; i < 3; i++) {
        display_account(accounts[i]);
    }
    
    // Demonstrate that the reference return is a true alias
    printf("\n=== Demonstrating Reference Return Behavior ===\n");
    BankAccount& account_ref = get_account_for_update(accounts, 2);
    printf("Before modification through reference: $%.2f\n", accounts[1].balance);
    
    account_ref.balance += 100.00;  // Add $100 to account 2
    printf("After modification through reference: $%.2f\n", accounts[1].balance);
    printf("Direct access to account 2: $%.2f\n", get_balance(accounts[1]));
    
    return 0;
}