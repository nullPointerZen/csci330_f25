// Problem 3.2: Object Lifecycle with References
// Demonstrates object creation, copying, and references

#include <cstdio>
#include <cstring>

struct Book {
    char title[100];
    char author[50];
    int pages;
    double price;
};

// Function that creates and returns a Book by value
Book create_book(const char* title, const char* author, int pages, double price) {
    Book new_book;
    strcpy(new_book.title, title);
    strcpy(new_book.author, author);
    new_book.pages = pages;
    new_book.price = price;
    return new_book;  // Returns by value (creates a copy)
}

// Function that takes a const Book reference and prints all book information
void print_book_info(const Book& book) {
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Pages: %d\n", book.pages);
    printf("Price: $%.2f\n", book.price);
}

// Function that takes a Book reference and discount percentage, then reduces the price
void apply_discount(Book& book, double discount_percent) {
    double discount_amount = book.price * (discount_percent / 100.0);
    book.price -= discount_amount;
    printf("Applied %.0f%% discount ($%.2f off)\n", discount_percent, discount_amount);
}

// Function that takes a const Book reference and returns a new Book with 
// the same information but prefix "Copy of " to title
Book copy_book(const Book& original) {
    Book copy;
    strcpy(copy.title, "Copy of ");
    strcat(copy.title, original.title);
    strcpy(copy.author, original.author);
    copy.pages = original.pages;
    copy.price = original.price;
    return copy;  // Returns by value (creates a copy)
}

int main() {
    printf("=== Creating original book ===\n");
    // Create a book "The C++ Journey" by "Jane Programmer", 300 pages, $49.99
    Book original_book = create_book("The C++ Journey", "Jane Programmer", 300, 49.99);
    
    printf("\n=== Original book info ===\n");
    // Print the original book info
    print_book_info(original_book);
    
    printf("\n=== Applying 20%% discount ===\n");
    // Apply 20% discount to original book
    apply_discount(original_book, 20.0);
    // Print updated info
    print_book_info(original_book);
    
    printf("\n=== Creating a copy ===\n");
    // Create a copy of the discounted book
    Book book_copy = copy_book(original_book);
    // Print copy info
    print_book_info(book_copy);
    
    printf("\n=== Modifying copy only ===\n");
    // Apply 10% discount to copy only
    apply_discount(book_copy, 10.0);
    
    // Print both original and copy to show they're different
    printf("\nOriginal book:\n");
    printf("Title: %s, Price: $%.2f\n", original_book.title, original_book.price);
    
    printf("Copy book:\n");
    printf("Title: %s, Price: $%.2f\n", book_copy.title, book_copy.price);
    
    // Demonstrate reference behavior vs copying
    printf("\n=== Demonstrating Reference vs Copy Behavior ===\n");
    Book& original_ref = original_book;  // Reference to original
    Book another_copy = original_book;   // Another copy
    
    printf("Before modification:\n");
    printf("Original: $%.2f, Reference: $%.2f, Copy: $%.2f\n", 
           original_book.price, original_ref.price, another_copy.price);
    
    // Modify through reference
    original_ref.price = 25.00;
    
    printf("After modifying through reference:\n");
    printf("Original: $%.2f, Reference: $%.2f, Copy: $%.2f\n", 
           original_book.price, original_ref.price, another_copy.price);
    
    return 0;
}