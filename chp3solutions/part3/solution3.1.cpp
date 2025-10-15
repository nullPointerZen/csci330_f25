#include <cstdio>

struct BankAccount {
    double balance;
    int account_number;
};

// Returns a const reference to the balance of a BankAccount
const double& get_balance(const BankAccount& account) {
    return account.balance;
}

// Returns a reference to the BankAccount for update
BankAccount& get_account_for_update(BankAccount accounts[], int account_number) {
    return accounts[account_number - 1]; // Assuming account_number maps directly to index
}

int main() {
    BankAccount accounts[3] = {
        {1000.50, 1},
        {2500.75, 2}, 
        {750.25, 3}
    };

    // Use get_balance to display account 2's balance
    std::printf("Account 2 balance: $%.2f\n", get_balance(accounts[1]));

    // Use get_account_for_update to modify account 1's balance to 1200.00
    get_account_for_update(accounts, 1).balance = 1200.00;

    // Display all account balances
    std::printf("Updated balances:\n");
    for (int i = 0; i < 3; ++i) {
        std::printf("Account %d: $%.2f\n", accounts[i].account_number, accounts[i].balance);
    }

    return 0;
}