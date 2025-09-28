#include <iostream>
#include <string>
#include <fstream>

// =============================================================================
// Simple RAII Classes (the ones students were confused about)
// =============================================================================

class BankAccount; // Forward declaration

// Simple AccountLock - demonstrates RAII pattern
class AccountLock {
private:
    BankAccount* account;
    bool was_locked;

public:
    AccountLock(BankAccount& acc);  // Constructor locks
    ~AccountLock();                 // Destructor unlocks
};

// Simple BalanceBackup - demonstrates automatic restoration
class BalanceBackup {
private:
    BankAccount& account;
    double original_balance;
    bool committed;

public:
    BalanceBackup(BankAccount& acc);
    ~BalanceBackup();
    void commit() { committed = true; }
};

// Simple AuditTrail - demonstrates automatic logging
class AuditTrail {
private:
    std::string operation;
    std::ofstream log_file;

public:
    AuditTrail(const std::string& op);
    ~AuditTrail();
};

// =============================================================================
// Basic BankAccount Class
// =============================================================================

class BankAccount {
private:
    static int next_account_number;
    int account_number;
    std::string owner_name;
    double balance;
    bool is_locked;

public:
    // Multiple constructors
    BankAccount()
        : account_number(next_account_number++), owner_name("Unknown"),
          balance(0.0), is_locked(false) {
        std::cout << "[Constructor] Account #" << account_number << " created\n";
    }

    BankAccount(const std::string& name, double initial_balance)
        : account_number(next_account_number++), owner_name(name),
          balance(initial_balance), is_locked(false) {
        std::cout << "[Constructor] Account #" << account_number
                  << " created: " << name << ", $" << balance << "\n";
    }

    // Virtual destructor
    virtual ~BankAccount() {
        std::cout << "[Destructor] Account #" << account_number
                  << " destroyed: Final balance $" << balance << "\n";
    }

    // Basic operations
    bool withdraw(double amount) {
        if (is_locked) {
            std::cout << "[Error] Account is locked\n";
            return false;
        }
        if (amount > balance) {
            std::cout << "[Error] Insufficient funds\n";
            return false;
        }
        balance -= amount;
        return true;
    }

    void deposit(double amount) {
        if (!is_locked) {
            balance += amount;
        }
    }

    // Getters for RAII classes
    double get_balance() const { return balance; }
    int get_account_number() const { return account_number; }
    bool get_is_locked() const { return is_locked; }

    // Setters for RAII classes
    void set_balance(double new_balance) { balance = new_balance; }
    void set_locked(bool locked) { is_locked = locked; }

    void display_info() const {
        std::cout << "Account #" << account_number << ": " << owner_name
                  << ", Balance: $" << balance;
        if (is_locked) std::cout << " [LOCKED]";
        std::cout << "\n";
    }
};

// Static member initialization
int BankAccount::next_account_number = 1001;

// =============================================================================
// Simple Specialized Account Types
// =============================================================================

class SavingsAccount : public BankAccount {
private:
    double interest_rate;

public:
    SavingsAccount(const std::string& name, double balance, double rate)
        : BankAccount(name, balance), interest_rate(rate) {
        std::cout << "[Constructor] Savings Account with " << (rate * 100) << "% interest\n";
    }

    ~SavingsAccount() {
        std::cout << "[Destructor] Savings Account destroyed\n";
    }
};

class CheckingAccount : public BankAccount {
private:
    double overdraft_limit;

public:
    CheckingAccount(const std::string& name, double balance, double limit)
        : BankAccount(name, balance), overdraft_limit(limit) {
        std::cout << "[Constructor] Checking Account with $" << limit << " overdraft\n";
    }

    ~CheckingAccount() {
        std::cout << "[Destructor] Checking Account destroyed\n";
    }
};

// =============================================================================
// RAII Classes Implementation
// =============================================================================

AccountLock::AccountLock(BankAccount& acc) : account(&acc), was_locked(acc.get_is_locked()) {
    account->set_locked(true);
    std::cout << "[AccountLock] Account #" << account->get_account_number() << " locked\n";
}

AccountLock::~AccountLock() {
    account->set_locked(was_locked);
    std::cout << "[AccountLock] Account #" << account->get_account_number() << " unlocked\n";
}

BalanceBackup::BalanceBackup(BankAccount& acc)
    : account(acc), original_balance(acc.get_balance()), committed(false) {
    std::cout << "[BalanceBackup] Backup created: $" << original_balance << "\n";
}

BalanceBackup::~BalanceBackup() {
    if (!committed) {
        account.set_balance(original_balance);
        std::cout << "[BalanceBackup] Balance restored to $" << original_balance << "\n";
    } else {
        std::cout << "[BalanceBackup] Backup released (transaction succeeded)\n";
    }
}

AuditTrail::AuditTrail(const std::string& op) : operation(op), log_file("bank_log.txt", std::ios::app) {
    if (log_file.is_open()) {
        log_file << "STARTED: " << operation << std::endl;
        std::cout << "[AuditTrail] Transaction logged: " << operation << "\n";
    }
}

AuditTrail::~AuditTrail() {
    if (log_file.is_open()) {
        log_file << "COMPLETED: " << operation << std::endl;
        std::cout << "[AuditTrail] Transaction log closed\n";
    }
}

// =============================================================================
// Simple Transfer Function using RAII
// =============================================================================

bool simple_transfer(BankAccount& from, BankAccount& to, double amount) {
    AuditTrail audit("Transfer $" + std::to_string(amount));
    AccountLock from_lock(from);
    BalanceBackup from_backup(from);

    if (from.withdraw(amount)) {
        to.deposit(amount);
        from_backup.commit();  // Success - don't restore balance
        std::cout << "[Success] Transfer completed\n";
        return true;
    } else {
        std::cout << "[Failed] Transfer failed - balance will be restored\n";
        return false;  // BalanceBackup will restore automatically
    }
}

// =============================================================================
// Main Function - Simple Demonstration
// =============================================================================

int main() {
    std::cout << "=== Banking System with RAII Demo ===\n\n";

    // Create accounts and show constructor/destructor order
    {
        std::cout << "Creating accounts...\n";
        BankAccount basic("John Doe", 1000.0);
        SavingsAccount savings("Jane Smith", 1500.0, 0.03);
        CheckingAccount checking("Bob Wilson", 800.0, 200.0);

        std::cout << "\nAccount information:\n";
        basic.display_info();
        savings.display_info();
        checking.display_info();

        std::cout << "\n--- Testing RAII Transfer ---\n";
        // Test successful transfer
        simple_transfer(basic, savings, 200.0);

        std::cout << "\nAfter successful transfer:\n";
        basic.display_info();
        savings.display_info();

        // Test failed transfer (insufficient funds)
        std::cout << "\n--- Testing Failed Transfer ---\n";
        simple_transfer(basic, savings, 2000.0);  // Should fail

        std::cout << "\nAfter failed transfer (balances should be unchanged):\n";
        basic.display_info();
        savings.display_info();

        std::cout << "\n--- Individual RAII Demos ---\n";

        // AccountLock demo
        {
            std::cout << "\nAccountLock demo:\n";
            AccountLock lock(basic);
            basic.withdraw(50.0);  // Should fail due to lock
        } // Lock released here
        basic.withdraw(50.0);  // Should succeed now

        // BalanceBackup demo
        {
            std::cout << "\nBalanceBackup demo:\n";
            BalanceBackup backup(basic);
            basic.set_balance(999999.0);  // Corrupt balance
            std::cout << "Temporarily corrupted balance\n";
            basic.display_info();
            // Don't call commit() - let destructor restore
        } // Balance restored here
        std::cout << "Balance restored:\n";
        basic.display_info();

        std::cout << "\nLeaving scope - accounts will be destroyed...\n";
    } // All accounts destroyed here - observe destructor order!

    std::cout << "\nDemo complete. Check 'bank_log.txt' for audit trail.\n";

    return 0;
}

/*
KEY LEARNING POINTS:

1. RAII ensures cleanup happens automatically
2. Destructors run even when things go wrong
3. Each RAII class has ONE responsibility
4. They compose together naturally
5. Exception-safe by design

This demonstrates the concepts without overwhelming complexity.
Students can understand why RAII is better than manual cleanup methods.
*/