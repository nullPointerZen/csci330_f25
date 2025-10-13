// Template provided:
#include <cstdio>

struct BankAccount {
    double balance;
    int account_number;
};

// TODO: Write a function 'get_balance' that takes a const BankAccount reference
// and returns a const reference to the balance
const double& get_balance (const BankAccount& account) {
	return account.balance;
}
// TODO: Write a function 'get_account_for_update' that takes an array of BankAccount
// and an account number, then returns a reference to the matching account
// (For simplicity, assume the account exists and is at index = account_number - 1)g

BankAccount& get_account_for_update(BankAccount accounts[], int account_number) {
	return accounts[account_number  - 1];	
}
int main() {
    BankAccount accounts[3] = {
        {1000.50, 1},
        {2500.75, 2}, 
        {750.25, 3}
    };
    get_account_for_update(accounts, 1).balance = 1200.00;

    printf("Account 2 Balance: %.2f\n", get_balance(accounts[1]));
    printf("Updated Balances:\n");
    for (int i = 0; i < 3; i++) {
	printf("Account %d balance: %.2f\n", accounts[i].account_number, accounts[i].balance);
    }
    // TODO: Use get_balance to display account 2's balance
    // TODO: Use get_account_for_update to modify account 1's balance to 1200.00
    // TODO: Display all account balances
    
    return 0;
}
