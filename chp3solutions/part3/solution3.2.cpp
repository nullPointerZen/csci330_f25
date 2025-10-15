#include <cstdio>
#include <cstring>

struct Book {
    char title[100];
    char author[50];
    int pages;
    double price;
};

// Creates a Book by value
Book create_book(const char* title, const char* author, int pages, double price) {
    Book b;
    std::strncpy(b.title, title, sizeof(b.title));
    std::strncpy(b.author, author, sizeof(b.author));
    b.pages = pages;
    b.price = price;
    return b;
}

// Prints book information
void print_book_info(const Book& b) {
    std::printf("Title: %s\n", b.title);
    std::printf("Author: %s\n", b.author);
    std::printf("Pages: %d\n", b.pages);
    std::printf("Price: $%.2f\n", b.price);
}

// Applies a discount to the book's price
void apply_discount(Book& b, double percent) {
    b.price -= b.price * (percent / 100.0);
}

// Returns a copy of the book with "Copy of " prefixed to the title
Book copy_book(const Book& original) {
    Book copy = original;
    char new_title[100] = "Copy of ";
    std::strncat(new_title, original.title, sizeof(new_title) - std::strlen(new_title) - 1);
    std::strncpy(copy.title, new_title, sizeof(copy.title));
    return copy;
}

int main() {
    std::printf("=== Creating original book ===\n");
    Book original = create_book("The C++ Journey", "Jane Programmer", 300, 49.99);

    std::printf("\n=== Original book info ===\n");
    print_book_info(original);

    std::printf("\n=== Applying 20%% discount ===\n");
    apply_discount(original, 20.0);
    print_book_info(original);

    std::printf("\n=== Creating a copy ===\n");
    Book copy = copy_book(original);
    print_book_info(copy);

    std::printf("\n=== Modifying copy only ===\n");
    apply_discount(copy, 10.0);
    std::printf("Original - Title: %s, Price: $%.2f\n", original.title, original.price);
    std::printf("Copy - Title: %s, Price: $%.2f\n", copy.title, copy.price);

    return 0;
}