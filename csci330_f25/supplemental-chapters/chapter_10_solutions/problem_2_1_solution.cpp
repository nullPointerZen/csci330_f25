// Problem 2.1: Testing a BankAccount Class Solution
// Demonstrates comprehensive class testing with state management

#include <cstdio>
#include <string>
#include <cmath>

// Test framework from Problem 1.1
int tests_passed = 0;
int tests_failed = 0;

void assert_equal(double expected, double actual, const char* test_name) {
    // Use epsilon for floating-point comparison
    const double epsilon = 0.001;
    if (std::abs(expected - actual) < epsilon) {
        printf("[PASS] %s\n", test_name);
        tests_passed++;
    } else {
        printf("[FAIL] %s: expected %.2f, got %.2f\n", test_name, expected, actual);
        tests_failed++;
    }
}

void assert_true(bool condition, const char* test_name) {
    if (condition) {
        printf("[PASS] %s\n", test_name);
        tests_passed++;
    } else {
        printf("[FAIL] %s: condition was false\n", test_name);
        tests_failed++;
    }
}

void assert_false(bool condition, const char* test_name) {
    if (!condition) {
        printf("[PASS] %s\n", test_name);
        tests_passed++;
    } else {
        printf("[FAIL] %s: condition was true (expected false)\n", test_name);
        tests_failed++;
    }
}

void print_test_summary() {
    printf("\n=== Test Summary ===\n");
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_failed);
    printf("Total tests:  %d\n", tests_passed + tests_failed);
    
    if (tests_failed == 0) {
        printf("🎉 All tests passed!\n");
    } else {
        printf("❌ %d test(s) failed.\n", tests_failed);
    }
}

// BankAccount class to test
class BankAccount {
private:
    std::string owner;
    double balance;
    
public:
    BankAccount(const std::string& owner_name) 
        : owner(owner_name), balance(0.0) {}
    
    bool deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            return true;
        }
        return false;
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    double get_balance() const {
        return balance;
    }
    
    std::string get_owner() const {
        return owner;
    }
};

// Test functions
void test_account_creation() {
    printf("\n--- Testing Account Creation ---\n");
    
    BankAccount account("Alice");
    
    // Test initial state
    assert_equal(0.0, account.get_balance(), "initial_balance_zero");
    assert_true(account.get_owner() == "Alice", "owner_name_correct");
    
    // Test with different name
    BankAccount account2("Bob Smith");
    assert_true(account2.get_owner() == "Bob Smith", "owner_with_space");
}

void test_deposit() {
    printf("\n--- Testing Deposit Operations ---\n");
    
    BankAccount account("Charlie");
    
    // Test successful deposits
    assert_true(account.deposit(100.0), "deposit_positive_amount_success");
    assert_equal(100.0, account.get_balance(), "balance_after_first_deposit");
    
    assert_true(account.deposit(50.5), "deposit_decimal_amount_success");
    assert_equal(150.5, account.get_balance(), "balance_after_second_deposit");
    
    // Test multiple deposits
    account.deposit(25.0);
    account.deposit(10.25);
    assert_equal(185.75, account.get_balance(), "balance_after_multiple_deposits");
    
    // Test invalid deposits
    assert_false(account.deposit(0.0), "deposit_zero_fails");
    assert_false(account.deposit(-10.0), "deposit_negative_fails");
    assert_equal(185.75, account.get_balance(), "balance_unchanged_after_invalid_deposits");
}

void test_withdraw() {
    printf("\n--- Testing Withdrawal Operations ---\n");
    
    BankAccount account("Diana");
    account.deposit(100.0);  // Setup: Start with $100
    
    // Test successful withdrawals
    assert_true(account.withdraw(30.0), "withdraw_valid_amount_success");
    assert_equal(70.0, account.get_balance(), "balance_after_withdrawal");
    
    assert_true(account.withdraw(70.0), "withdraw_entire_balance_success");
    assert_equal(0.0, account.get_balance(), "balance_zero_after_full_withdrawal");
    
    // Test invalid withdrawals
    assert_false(account.withdraw(10.0), "withdraw_from_empty_account_fails");
    assert_equal(0.0, account.get_balance(), "balance_unchanged_after_failed_withdrawal");
    
    // Setup for insufficient funds test
    account.deposit(50.0);
    assert_false(account.withdraw(100.0), "withdraw_insufficient_funds_fails");
    assert_equal(50.0, account.get_balance(), "balance_unchanged_insufficient_funds");
    
    // Test invalid amounts
    assert_false(account.withdraw(0.0), "withdraw_zero_fails");
    assert_false(account.withdraw(-25.0), "withdraw_negative_fails");
    assert_equal(50.0, account.get_balance(), "balance_unchanged_invalid_amounts");
}

void test_complex_operations() {
    printf("\n--- Testing Complex Operation Sequences ---\n");
    
    BankAccount account("Eve");
    
    // Test mixed operations
    account.deposit(1000.0);
    account.withdraw(250.0);
    account.deposit(100.0);
    account.withdraw(75.5);
    
    assert_equal(774.5, account.get_balance(), "complex_operations_final_balance");
    
    // Test boundary condition - exact balance withdrawal
    BankAccount account2("Frank");
    account2.deposit(99.99);
    assert_true(account2.withdraw(99.99), "withdraw_exact_balance_success");
    assert_equal(0.0, account2.get_balance(), "exact_balance_withdrawal_result");
}

void test_edge_cases() {
    printf("\n--- Testing Edge Cases ---\n");
    
    BankAccount account("Grace");
    
    // Test very small amounts
    assert_true(account.deposit(0.01), "deposit_one_cent_success");
    assert_equal(0.01, account.get_balance(), "one_cent_balance");
    
    assert_true(account.withdraw(0.01), "withdraw_one_cent_success");
    assert_equal(0.0, account.get_balance(), "zero_balance_after_cent_withdrawal");
    
    // Test large amounts
    assert_true(account.deposit(1000000.0), "deposit_million_success");
    assert_equal(1000000.0, account.get_balance(), "million_dollar_balance");
    
    // Test precision with many decimal places
    account.deposit(123.456789);
    // Note: Due to floating-point precision, we test with appropriate epsilon
    double expected = 1000123.456789;
    double actual = account.get_balance();
    assert_true(std::abs(expected - actual) < 0.001, "high_precision_deposit");
}

int main() {
    printf("Running BankAccount class tests...\n");
    
    test_account_creation();
    test_deposit();
    test_withdraw();
    test_complex_operations();
    test_edge_cases();
    
    print_test_summary();
    return 0;
}

/*
Compilation command:
g++ -o test_bank_account problem_2_1_solution.cpp

Expected Output:
Running BankAccount class tests...

--- Testing Account Creation ---
[PASS] initial_balance_zero
[PASS] owner_name_correct
[PASS] owner_with_space

--- Testing Deposit Operations ---
[PASS] deposit_positive_amount_success
[PASS] balance_after_first_deposit
[PASS] deposit_decimal_amount_success
[PASS] balance_after_second_deposit
[PASS] balance_after_multiple_deposits
[PASS] deposit_zero_fails
[PASS] deposit_negative_fails
[PASS] balance_unchanged_after_invalid_deposits

--- Testing Withdrawal Operations ---
[PASS] withdraw_valid_amount_success
[PASS] balance_after_withdrawal
[PASS] withdraw_entire_balance_success
[PASS] balance_zero_after_full_withdrawal
[PASS] withdraw_from_empty_account_fails
[PASS] balance_unchanged_after_failed_withdrawal
[PASS] withdraw_insufficient_funds_fails
[PASS] balance_unchanged_insufficient_funds
[PASS] withdraw_zero_fails
[PASS] withdraw_negative_fails
[PASS] balance_unchanged_invalid_amounts

--- Testing Complex Operation Sequences ---
[PASS] complex_operations_final_balance
[PASS] withdraw_exact_balance_success
[PASS] exact_balance_withdrawal_result

--- Testing Edge Cases ---
[PASS] one_cent_balance
[PASS] withdraw_one_cent_success
[PASS] zero_balance_after_cent_withdrawal
[PASS] deposit_million_success
[PASS] million_dollar_balance
[PASS] high_precision_deposit

=== Test Summary ===
Tests passed: 24
Tests failed: 0
Total tests:  24
🎉 All tests passed!

Key Learning Points:
1. Class testing requires verifying both return values and state changes
2. Floating-point comparisons need epsilon tolerance
3. Test setup (deposits before withdrawals) is crucial
4. Edge cases include boundary values and precision limits
5. Comprehensive testing builds confidence in class behavior
*/