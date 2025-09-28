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
    return new_book;
}

// Function that takes a const Book reference and prints book information
void print_book_info(const Book& book) {
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Pages: %d\n", book.pages);
    printf("Price: $%.2f\n", book.price);
}

// Function that takes a Book reference and applies discount
void apply_discount(Book& book, double discount_percent) {
    book.price = book.price * (1.0 - discount_percent / 100.0);
}

// Function that returns a copy with "Copy of " prefix
Book copy_book(const Book& original) {
    Book copy = original;
    char new_title[100] = "Copy of ";
    strcat(new_title, original.title);
    strcpy(copy.title, new_title);
    return copy;
}

int main() {
    printf("=== Creating original book ===\n");
    Book original = create_book("The C++ Journey", "Jane Programmer", 300, 49.99);
    
    printf("\n=== Original book info ===\n");
    print_book_info(original);
    
    printf("\n=== Applying 20%% discount ===\n");
    apply_discount(original, 20.0);
    print_book_info(original);
    
    printf("\n=== Creating a copy ===\n");
    Book copy = copy_book(original);
    print_book_info(copy);
    
    printf("\n=== Modifying copy only ===\n");
    apply_discount(copy, 10.0);
    
    printf("Original - Title: %s, Price: $%.2f\n", original.title, original.price);
    printf("Copy - Title: %s, Price: $%.2f\n", copy.title, copy.price);
    
    return 0;
}