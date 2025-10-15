#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdexcept>

class TransactionLogger {
    std::ofstream logFile;

public:
    TransactionLogger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
        if (!logFile) throw std::runtime_error("Failed to open log file");
        std::cout << "[RAII Logger] Transaction log opened: " << filename << "\n";
    }

    ~TransactionLogger() {
        if (logFile.is_open()) {
            logFile.close();
            std::cout << "[RAII Logger] Transaction log closed automatically\n";
        }
    }

    void log(const std::string& message) {
        if (logFile.is_open()) logFile << message << "\n";
    }
};

class AccountLock {
public:
    AccountLock(int accountId) {
        std::cout << "[Lock] Account #" << accountId << " locked\n";
    }
    ~AccountLock() {
        std::cout << "[Unlock] Account unlocked\n";
    }
};

class BalanceBackup {
    double& balanceRef;
    double originalBalance;

public:
    BalanceBackup(double& balance) : balanceRef(balance), originalBalance(balance) {}
    ~BalanceBackup() {
        balanceRef = originalBalance;
        std::cout << "[Rollback] Balance restored to $" << std::fixed << std::setprecision(2) << originalBalance << "\n";
    }

    void commit() {
        originalBalance = balanceRef; 
    }
};

class AuditTrail {
public:
    AuditTrail(const std::string& event) {
        std::cout << "[AuditTrail] " << event << "\n";
    }
    ~AuditTrail() {
        std::cout << "[AuditTrail] Event finalized\n";
    }
};

class BankAccount {
protected:
    static int nextAccountNumber;
    static int totalAccountsCreated;
    static int totalAccountsDestroyed;

    int accountNumber;
    std::string ownerName;
    double balance;

public:
    BankAccount(const std::string& name, double initialBalance)
        : accountNumber(nextAccountNumber++), ownerName(name), balance(initialBalance) {
        totalAccountsCreated++;
        std::cout << "[Constructor] Account #" << accountNumber << " created: " << ownerName
                  << ", $" << std::fixed << std::setprecision(2) << balance << "\n";
    }

    virtual ~BankAccount() {
        totalAccountsDestroyed++;
        std::cout << "[Destructor] Account #" << accountNumber << " destroyed: Final balance $"
                  << std::fixed << std::setprecision(2) << balance << "\n";
    }

    int getId() const { return accountNumber; }
    double& getBalanceRef() { return balance; }
    void display() const {
        std::cout << "Account #" << accountNumber << " (" << ownerName << ") Balance: $"
                  << std::fixed << std::setprecision(2) << balance << "\n";
    }

    static void showStats() {
        std::cout << "\nSummary: " << totalAccountsCreated << " accounts created, "
                  << totalAccountsDestroyed << " accounts destroyed\n";
    }
};

int BankAccount::nextAccountNumber = 1001;
int BankAccount::totalAccountsCreated = 0;
int BankAccount::totalAccountsDestroyed = 0;

class BusinessAccount : public BankAccount {
public:
    BusinessAccount(const std::string& name, double initialBalance)
        : BankAccount(name, initialBalance) {
        std::cout << "[Constructor] Business Account #" << getId() << ": " << name
                  << ", $" << std::fixed << std::setprecision(2) << initialBalance << "\n";
    }
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    TransactionLogger logger("bank_transactions.log");
    logger.log("[Transaction Log] Transfer initiated: #" + std::to_string(from.getId()) +
               " -> #" + std::to_string(to.getId()) + ", $" + std::to_string(amount));

    AccountLock lockFrom(from.getId());
    AccountLock lockTo(to.getId());
    AuditTrail audit("Transfer compliance check");

    BalanceBackup backupFrom(from.getBalanceRef());
    BalanceBackup backupTo(to.getBalanceRef());

    if (amount <= 0) {
        throw std::invalid_argument("Invalid transfer amount");
    }

    if (from.getBalanceRef() < amount) {
        throw std::runtime_error("Insufficient funds");
    }

    from.getBalanceRef() -= amount;
    to.getBalanceRef() += amount;

    backupFrom.commit();
    backupTo.commit();

    logger.log("[Success] Transfer completed successfully");
    std::cout << "[Success] Transfer completed successfully\n";
    return true;
}
int main() {
    std::cout << "=== Banking System with RAII Demo ===\n";

    try {
        BankAccount john("John Doe", 1000.0);
        BankAccount jane("Jane Smith", 1500.0);
        BusinessAccount acme("Acme Corp", 10000.0);

        transfer(john, jane, 200.0);
    } catch (const std::exception& ex) {
        std::cerr << "[Error] Transaction failed: " << ex.what() << "\n";
    }

    BankAccount::showStats();
    return 0;
}