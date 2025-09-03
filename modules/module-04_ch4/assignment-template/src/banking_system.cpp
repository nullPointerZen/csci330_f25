// HW_04: Project 1 - Banking System with RAII
// Time: 2 hours
// Topics: Constructors, destructors, RAII, Rule of Three

#include <cstdio>
#include <cstring>
#include <ctime>

// ============================================================================
// PART A: Basic Account Class with Lifecycle (60 minutes)
// ============================================================================

class BankAccount {
private:
    static int totalAccounts;  // Track total accounts created
    char accountHolder[100];
    int accountNumber;
    double balance;
    FILE* logFile;  // Resource that needs cleanup
    
public:
    // TODO 1: Default constructor
    BankAccount() {
        // TODO: Initialize with default values
        // Set accountNumber to next available (use totalAccounts)
        // Set balance to 0
        // Open log file for this account
        // Log creation
        
        totalAccounts++;
        printf("[Constructor] Default BankAccount #%d created\n", accountNumber);
    }
    
    // TODO 2: Parameterized constructor
    BankAccount(const char* name, double initialDeposit) {
        // TODO: Initialize with provided values
        // Set accountNumber, copy name, set balance
        // Open log file
        // Log creation with details
        
        totalAccounts++;
        printf("[Constructor] BankAccount for %s created with $%.2f\n", name, initialDeposit);
    }
    
    // TODO 3: Copy constructor (Rule of Three - part 1)
    BankAccount(const BankAccount& other) {
        // TODO: Deep copy all members
        // Create new log file (don't share file handles!)
        // Log the copy operation
        
        printf("[Copy Constructor] Copying account #%d\n", other.accountNumber);
    }
    
    // TODO 4: Destructor - CRITICAL for RAII
    ~BankAccount() {
        // TODO: Clean up resources
        // Close log file if open
        // Log destruction
        // Decrement totalAccounts
        
        printf("[Destructor] BankAccount #%d destroyed\n", accountNumber);
    }
    
    // TODO 5: Copy assignment operator (Rule of Three - part 2)
    BankAccount& operator=(const BankAccount& other) {
        // TODO: Check for self-assignment
        // Clean up existing resources
        // Deep copy from other
        // Return *this
        
        printf("[Assignment] Assigning account #%d to account #%d\n", 
               other.accountNumber, this->accountNumber);
        return *this;
    }
    
    // TODO 6: Deposit method
    void deposit(double amount) {
        // TODO: Add to balance
        // Log transaction to file
        // Print confirmation
    }
    
    // TODO 7: Withdraw method
    void withdraw(double amount) {
        // TODO: Check sufficient funds
        // Subtract from balance if possible
        // Log transaction
        // Print result
    }
    
    // TODO 8: Display account info
    void display() const {
        printf("Account #%d - %s: $%.2f\n", accountNumber, accountHolder, balance);
    }
    
    // Static method to show total accounts
    static int getTotalAccounts() {
        return totalAccounts;
    }
};

// Initialize static member
int BankAccount::totalAccounts = 0;

// ============================================================================
// PART B: Transaction Logger with RAII (30 minutes)
// ============================================================================

class TransactionLogger {
private:
    FILE* file;
    char filename[100];
    
public:
    // TODO 9: Constructor opens file
    TransactionLogger(const char* logname) {
        strcpy(filename, logname);
        // TODO: Open file for append
        // Log that logger started
        
        printf("[Logger] Transaction logger '%s' started\n", filename);
    }
    
    // TODO 10: Destructor ensures file is closed
    ~TransactionLogger() {
        // TODO: Close file if open
        // This ensures cleanup even if exception occurs!
        
        printf("[Logger] Transaction logger '%s' closed\n", filename);
    }
    
    // TODO 11: Log a transaction
    void log(const char* transaction) {
        // TODO: Write timestamp and transaction to file
        // Also print to console
    }
    
    // Delete copy operations to prevent file handle sharing
    TransactionLogger(const TransactionLogger&) = delete;
    TransactionLogger& operator=(const TransactionLogger&) = delete;
};

// ============================================================================
// PART C: Demonstration of Lifecycle (30 minutes)
// ============================================================================

void demonstrate_scope_and_lifetime() {
    printf("\n=== Scope and Lifetime Demo ===\n");
    
    {
        printf("Entering inner scope...\n");
        // TODO 12: Create account in inner scope
        BankAccount tempAccount("Temporary User", 100.00);
        tempAccount.display();
        // Account will be destroyed when leaving scope
        printf("Leaving inner scope...\n");
    }
    // TODO 13: Verify destructor was called
    
    printf("Back in outer scope\n");
}

void demonstrate_array_lifecycle() {
    printf("\n=== Array Lifecycle Demo ===\n");
    
    // TODO 14: Create array of accounts
    // Watch constructors being called
    printf("Creating array of 3 accounts...\n");
    BankAccount accounts[3];
    
    // TODO 15: Initialize accounts
    // Note: They were already constructed!
    
    printf("Array going out of scope...\n");
    // Destructors will be called in reverse order
}

void demonstrate_copy_operations() {
    printf("\n=== Copy Operations Demo ===\n");
    
    // TODO 16: Test copy constructor
    BankAccount original("Alice", 1000.00);
    BankAccount copy = original;  // Copy constructor
    
    // TODO 17: Test assignment operator
    BankAccount another("Bob", 500.00);
    another = original;  // Assignment operator
    
    // TODO 18: Verify both work correctly
    original.display();
    copy.display();
    another.display();
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("    HW_04: Banking System with RAII\n");
    printf("==========================================\n\n");
    
    // Show initial account count
    printf("Initial total accounts: %d\n\n", BankAccount::getTotalAccounts());
    
    // Part A: Basic lifecycle operations
    printf("=== Part A: Basic Account Operations ===\n");
    
    // TODO 19: Create accounts with different constructors
    BankAccount account1;  // Default constructor
    BankAccount account2("John Doe", 1500.00);  // Parameterized
    
    // TODO 20: Perform transactions
    account2.deposit(200.00);
    account2.withdraw(50.00);
    account2.display();
    
    // Part B: RAII demonstration
    printf("\n=== Part B: RAII with Transaction Logger ===\n");
    {
        TransactionLogger logger("transactions.log");
        logger.log("System started");
        logger.log("Account created");
        // Logger will be automatically closed when leaving scope
    }
    
    // Part C: Lifecycle demonstrations
    demonstrate_scope_and_lifetime();
    demonstrate_array_lifecycle();
    demonstrate_copy_operations();
    
    // Final account count
    printf("\n=== Final Statistics ===\n");
    printf("Total accounts created: %d\n", BankAccount::getTotalAccounts());
    
    printf("\n==========================================\n");
    printf("         Program Complete!\n");
    printf("   Watch destructors fire on exit...\n");
    printf("==========================================\n");
    
    return 0;
    // All remaining accounts will be destroyed here
}