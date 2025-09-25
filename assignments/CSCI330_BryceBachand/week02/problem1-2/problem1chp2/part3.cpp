#include <iostream>

// === Global Variables ===
int globalInt;               // auto-initialized to 0
const int globalConst = 100; // must be initialized

// Function to demonstrate local variable address variation
void localAddressDemo() {
    int localVar;
    std::cout << "Address of localVar in this call: " << &localVar << "\n";
}

// Function to demonstrate shadowing and block scope
void scopeDemo() {
    int value = 10;
    std::cout << "Outer scope value: " << value << "\n";

    {
        int value = 20; // shadows outer 'value'
        std::cout << "Inner scope shadowed value: " << value << "\n";
    }

    std::cout << "Back to outer scope value: " << value << "\n";
}

int main() {
    std::cout << "=== Initialization Behavior ===\n";

    int uninitializedLocal; // may contain garbage
    const int constLocal = 50; // must be initialized

    std::cout << "Uninitialized local int (undefined behavior): " << uninitializedLocal << "\n";
    std::cout << "Global int (auto-initialized): " << globalInt << "\n";
    std::cout << "Const global int: " << globalConst << "\n";
    std::cout << "Const local int: " << constLocal << "\n";

    std::cout << "\n=== Scope Investigation ===\n";

    int value = 5; // local variable
    std::cout << "Local value: " << value << "\n";
    std::cout << "Global value (shadowed): " << globalInt << "\n";

    scopeDemo();

    std::cout << "\n=== Lifetime and Memory Layout ===\n";

    int localMain = 1;
    std::cout << "Address of globalInt: " << &globalInt << "\n";
    std::cout << "Address of localMain: " << &localMain << "\n";

    localAddressDemo();
    localAddressDemo(); // different address each time

    std::cout << "\n=== Safety Analysis ===\n";
    std::cout << "Compile with: g++ -Wall -Wuninitialized memory_scope_explorer.cpp\n";
    std::cout << "Compiler catches:\n";
    std::cout << "  - Use of uninitialized local variables (with warning)\n";
    std::cout << "  - Missing const initializations (as error)\n";
    std::cout << "Compiler may miss:\n";
    std::cout << "  - Use of uninitialized variables if value is never read\n";
    std::cout << "  - Logical errors from shadowing or scope confusion\n";

    return 0;
}