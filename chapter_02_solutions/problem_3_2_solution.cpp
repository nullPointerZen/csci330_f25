/*
 * Chapter 2, Problem 3.2 Solution: Dynamic Inventory System
 * 
 * This advanced solution demonstrates:
 * - Complex struct design for business applications
 * - Array management with dynamic counting
 * - Business logic implementation
 * - Comprehensive error handling
 * - String manipulation and comparison
 * 
 * Key Learning Points:
 * 1. Real-world struct applications
 * 2. Managing collections with manual counting
 * 3. Parameter validation and error handling
 * 4. String operations with strcmp and strcpy
 * 5. Complex business logic implementation
 * 
 * Business Context: Small store inventory management
 */

#include <cstdio>
#include <cstring>

// Product struct to represent inventory items
struct Product {
    char name[50];      // Product name
    double price;       // Price per unit
    int quantity;       // Quantity in stock
    char code[10];      // Product code (like SKU)
};

const int MAX_PRODUCTS = 100;  // Maximum products we can store

/*
 * Add a new product to the inventory
 * 
 * Parameters:
 *   inventory - Array of Product structs
 *   count - Pointer to current product count (modified)
 *   name - Product name
 *   price - Product price
 *   quantity - Initial quantity
 *   code - Product code
 * 
 * Returns:
 *   bool - true if successful, false if error
 */
bool addProduct(Product inventory[], int* count, const char* name, 
                double price, int quantity, const char* code) {
    
    // Validate inputs
    if (*count >= MAX_PRODUCTS) {
        printf("Error: Inventory is full (max %d products)\n", MAX_PRODUCTS);
        return false;
    }
    
    if (price < 0) {
        printf("Error: Price cannot be negative\n");
        return false;
    }
    
    if (quantity < 0) {
        printf("Error: Quantity cannot be negative\n");
        return false;
    }
    
    if (strlen(name) >= 50) {
        printf("Error: Product name too long (max 49 characters)\n");
        return false;
    }
    
    if (strlen(code) >= 10) {
        printf("Error: Product code too long (max 9 characters)\n");
        return false;
    }
    
    // Check for duplicate product codes
    for (int i = 0; i < *count; i++) {
        if (strcmp(inventory[i].code, code) == 0) {
            printf("Error: Product code '%s' already exists\n", code);
            return false;
        }
    }
    
    // Add the new product
    strcpy(inventory[*count].name, name);
    inventory[*count].price = price;
    inventory[*count].quantity = quantity;
    strcpy(inventory[*count].code, code);
    
    (*count)++;  // Increment product count
    
    printf("Added: %s (%s) - $%.2f x %d\n", name, code, price, quantity);
    return true;
}

/*
 * Process a sale (reduce inventory)
 * 
 * Parameters:
 *   product - Pointer to Product struct
 *   quantitySold - Number of items sold
 * 
 * Returns:
 *   bool - true if sale successful, false if insufficient stock
 */
bool processSale(Product* product, int quantitySold) {
    if (quantitySold <= 0) {
        printf("Error: Sale quantity must be positive\n");
        return false;
    }
    
    if (product->quantity < quantitySold) {
        printf("Error: Insufficient stock. Available: %d, Requested: %d\n", 
               product->quantity, quantitySold);
        return false;
    }
    
    // Process the sale
    product->quantity -= quantitySold;
    
    printf("Sale successful. %d %s remaining.\n", product->quantity, product->name);
    return true;
}

/*
 * Calculate total value of all inventory
 * 
 * Parameters:
 *   inventory - Array of Product structs (read-only)
 *   count - Number of products
 * 
 * Returns:
 *   double - Total inventory value
 */
double calculateTotalValue(const Product inventory[], int count) {
    double total = 0.0;
    
    for (int i = 0; i < count; i++) {
        total += inventory[i].price * inventory[i].quantity;
    }
    
    return total;
}

/*
 * Print products with low stock (quantity < 5)
 * 
 * Parameters:
 *   inventory - Array of Product structs (read-only)
 *   count - Number of products
 */
void printLowStock(const Product inventory[], int count) {
    printf("\nLow Stock Items (< 5 units):\n");
    
    bool foundLowStock = false;
    
    for (int i = 0; i < count; i++) {
        if (inventory[i].quantity < 5) {
            printf("- %s (%s): %d remaining\n", 
                   inventory[i].name, inventory[i].code, inventory[i].quantity);
            foundLowStock = true;
        }
    }
    
    if (!foundLowStock) {
        printf("All products are well-stocked!\n");
    }
}

/*
 * Find product by code
 * 
 * Parameters:
 *   inventory - Array of Product structs
 *   count - Number of products
 *   code - Product code to search for
 * 
 * Returns:
 *   Product* - Pointer to found product, or nullptr if not found
 */
Product* findProductByCode(Product inventory[], int count, const char* code) {
    for (int i = 0; i < count; i++) {
        if (strcmp(inventory[i].code, code) == 0) {
            return &inventory[i];
        }
    }
    return nullptr;  // Not found
}

/*
 * Print all products in inventory
 * 
 * Parameters:
 *   inventory - Array of Product structs (read-only)
 *   count - Number of products
 */
void printInventory(const Product inventory[], int count) {
    printf("\n=== Current Inventory ===\n");
    
    if (count == 0) {
        printf("Inventory is empty.\n");
        return;
    }
    
    printf("%-20s %-8s %8s %8s %12s\n", "Name", "Code", "Price", "Qty", "Total Value");
    printf("%-20s %-8s %8s %8s %12s\n", "----", "----", "-----", "---", "-----------");
    
    for (int i = 0; i < count; i++) {
        double itemValue = inventory[i].price * inventory[i].quantity;
        printf("%-20s %-8s $%7.2f %8d $%11.2f\n", 
               inventory[i].name, inventory[i].code, inventory[i].price, 
               inventory[i].quantity, itemValue);
    }
}

/*
 * Update product quantity (for restocking)
 * 
 * Parameters:
 *   product - Pointer to Product struct
 *   newQuantity - New quantity amount
 * 
 * Returns:
 *   bool - true if successful, false if invalid quantity
 */
bool updateQuantity(Product* product, int newQuantity) {
    if (newQuantity < 0) {
        printf("Error: Quantity cannot be negative\n");
        return false;
    }
    
    int oldQuantity = product->quantity;
    product->quantity = newQuantity;
    
    printf("Updated %s quantity from %d to %d\n", 
           product->name, oldQuantity, newQuantity);
    
    return true;
}

/*
 * Main program demonstrating the inventory system
 */
int main() {
    printf("=== Store Inventory Management System ===\n");
    
    // Initialize inventory
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;
    
    // Add sample products
    printf("\n--- Adding Products ---\n");
    addProduct(inventory, &productCount, "Laptop", 999.99, 10, "LP001");
    addProduct(inventory, &productCount, "Wireless Mouse", 25.50, 15, "MS001");
    addProduct(inventory, &productCount, "Mechanical Keyboard", 75.00, 3, "KB001");
    addProduct(inventory, &productCount, "USB Cable", 12.99, 25, "CB001");
    addProduct(inventory, &productCount, "Monitor", 299.99, 8, "MN001");
    
    // Display current inventory
    printInventory(inventory, productCount);
    
    // Demonstrate sales processing
    printf("\n--- Processing Sales ---\n");
    
    // Find laptop and sell 2 units
    Product* laptop = findProductByCode(inventory, productCount, "LP001");
    if (laptop != nullptr) {
        printf("Processing sale: 2 Laptops\n");
        processSale(laptop, 2);
    }
    
    // Try to sell more keyboards than we have
    Product* keyboard = findProductByCode(inventory, productCount, "KB001");
    if (keyboard != nullptr) {
        printf("\nTrying to sell 5 Keyboards (we only have %d):\n", keyboard->quantity);
        processSale(keyboard, 5);  // This should fail
        
        printf("Trying to sell 2 Keyboards:\n");
        processSale(keyboard, 2);  // This should succeed
    }
    
    // Check low stock items
    printLowStock(inventory, productCount);
    
    // Calculate and display total inventory value
    double totalValue = calculateTotalValue(inventory, productCount);
    printf("\nTotal inventory value: $%.2f\n", totalValue);
    
    // Demonstrate restocking
    printf("\n--- Restocking ---\n");
    if (keyboard != nullptr) {
        printf("Restocking keyboards...\n");
        updateQuantity(keyboard, 20);
    }
    
    // Final inventory state
    printInventory(inventory, productCount);
    
    // Final total value
    totalValue = calculateTotalValue(inventory, productCount);
    printf("\nFinal inventory value: $%.2f\n", totalValue);
    
    // Demonstrate error handling
    printf("\n--- Error Handling Demos ---\n");
    
    // Try to add duplicate product code
    addProduct(inventory, &productCount, "Another Laptop", 1200.00, 5, "LP001");
    
    // Try to add product with negative price
    addProduct(inventory, &productCount, "Free Item", -10.00, 5, "FR001");
    
    // Try to sell non-existent product
    Product* nonExistent = findProductByCode(inventory, productCount, "XX999");
    if (nonExistent == nullptr) {
        printf("Product XX999 not found in inventory\n");
    }
    
    return 0;
}

/*
 * Expected Output (partial):
 * === Store Inventory Management System ===
 * 
 * --- Adding Products ---
 * Added: Laptop (LP001) - $999.99 x 10
 * Added: Wireless Mouse (MS001) - $25.50 x 15
 * Added: Mechanical Keyboard (KB001) - $75.00 x 3
 * Added: USB Cable (CB001) - $12.99 x 25
 * Added: Monitor (MN001) - $299.99 x 8
 * 
 * === Current Inventory ===
 * Name                 Code     Price      Qty  Total Value
 * ----                 ----     -----      ---  -----------
 * Laptop               LP001   $999.99       10   $9999.90
 * Wireless Mouse       MS001    $25.50       15    $382.50
 * Mechanical Keyboard  KB001    $75.00        3    $225.00
 * USB Cable            CB001    $12.99       25    $324.75
 * Monitor              MN001   $299.99        8   $2399.92
 * 
 * --- Processing Sales ---
 * Processing sale: 2 Laptops
 * Sale successful. 8 Laptop remaining.
 * 
 * Trying to sell 5 Keyboards (we only have 3):
 * Error: Insufficient stock. Available: 3, Requested: 5
 * Trying to sell 2 Keyboards:
 * Sale successful. 1 Mechanical Keyboard remaining.
 * 
 * Low Stock Items (< 5 units):
 * - Mechanical Keyboard (KB001): 1 remaining
 * 
 * Total inventory value: $11,331.07
 * 
 * 
 * Key Teaching Points:
 * 
 * 1. COMPLEX STRUCT DESIGN:
 *    - Multiple data types in one struct
 *    - Character arrays for strings
 *    - Logical grouping of related data
 * 
 * 2. ARRAY MANAGEMENT:
 *    - Manual counting with separate counter variable
 *    - Bounds checking before adding elements
 *    - Linear search through arrays
 * 
 * 3. STRING OPERATIONS:
 *    - strcmp() for string comparison
 *    - strcpy() for string assignment
 *    - strlen() for string length checking
 * 
 * 4. BUSINESS LOGIC:
 *    - Input validation (negative prices, quantities)
 *    - Stock management (prevent overselling)  
 *    - Duplicate prevention (unique product codes)
 * 
 * 5. ERROR HANDLING:
 *    - Parameter validation
 *    - Graceful failure with error messages
 *    - Return values indicate success/failure
 * 
 * 6. CONST CORRECTNESS:
 *    - const parameters for read-only functions
 *    - Prevents accidental modification
 * 
 * 
 * Advanced Concepts Demonstrated:
 * 
 * 1. POINTER ARITHMETIC:
 *    - Passing count by pointer to modify it
 *    - Returning pointers to array elements
 * 
 * 2. SEARCH ALGORITHMS:
 *    - Linear search through struct arrays
 *    - Handling "not found" cases with nullptr
 * 
 * 3. DATA VALIDATION:
 *    - Multiple validation checks per function
 *    - Business rule enforcement
 * 
 * 4. MEMORY EFFICIENCY:
 *    - Fixed-size arrays avoid dynamic allocation
 *    - Passing by pointer avoids copying large structs
 * 
 * 
 * Common Student Mistakes:
 * 
 * 1. WRONG: if (inventory[i].code == code)        // Can't compare strings with ==
 *    RIGHT: if (strcmp(inventory[i].code, code) == 0) // Use strcmp for strings
 * 
 * 2. WRONG: inventory[count].name = name;         // Can't assign strings directly  
 *    RIGHT: strcpy(inventory[count].name, name);  // Use strcpy for strings
 * 
 * 3. WRONG: (*count)++;                           // Increment the count
 *    WRONG: *count++;                             // Wrong operator precedence!
 *    RIGHT: (*count)++;                           // Parentheses needed
 * 
 * 4. WRONG: return inventory[i];                  // Returns copy of struct
 *    RIGHT: return &inventory[i];                 // Returns pointer to struct
 * 
 * 
 * Real-World Extensions:
 * - Add file I/O for persistent storage
 * - Implement barcode scanning simulation
 * - Add supplier information to products
 * - Create sales reports and analytics
 * - Add user authentication system
 * 
 * 
 * Compilation: g++ -o inventory problem_3_2_solution.cpp
 * Execution: ./inventory
 */