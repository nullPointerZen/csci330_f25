// Template provided:
#include <cstdio>
#include <cstring>

struct Book {
    char title[100];
    char author[50];
    int pages;
    double price;
};

// TODO: Write a function 'create_book' that takes title, author, pages, price
// and returns a Book (by value)
Book create_book (const char* title, const char* author, int pages, double price) {
	Book new_book;
	strcpy(new_book.title, title);
	strcpy(new_book.author, author);
	new_book.pages = pages;
	new_book.price = price;
	return new_book;
}

// TODO: Write a function 'print_book_info' that takes a const Book reference
// and prints all book information
void print_book_info (const Book& book) {
    printf("Book name: %s\nAuthor: %s\nPages: %d\nPrice: %.2f\n", book.title, book.author, book.pages, book.price);

}
// TODO: Write a function 'apply_discount' that takes a Book reference and 
// discount percentage, then reduces the price

void apply_discount (Book& book, double discount_percentage) {
double discount = book.price * (discount_percentage / 100.0);
book.price = book.price - discount;

}
// TODO: Write a function 'copy_book' that takes a const Book reference and
// returns a new Book with the same information but prefix "Copy of " to title
Book copy_book (Book& book) {
	Book copy_of_book;

	snprintf(copy_of_book.title, sizeof(copy_of_book.title), "Copy of %.91s", book.title);
       	strcpy(copy_of_book.author, book.author);
	copy_of_book.pages = book.pages;
	copy_of_book.price = book.price;
	return copy_of_book;	
}

int main() {
    printf("=== Creating original book ===\n");
    // TODO: Create a book "The C++ Journey" by "Jane Programmer", 300 pages, $49.99
    Book my_book = create_book("The C++ Journey", "Jane Programmer", 300, 49.99);
    
    // TODO: Print the original book info
    printf("\n=== Original book info ===\n");
    print_book_info(my_book);
   
    printf("\n=== Applying 20%%  discount ===\n");
    // TODO: Apply 20% discount to original book
    apply_discount(my_book, 20.0);
    // TODO: Print updated info
    print_book_info(my_book);    

    printf("\n=== Creating a copy ===\n");
    // TODO: Create a copy of the discounted book
    Book copy_of_book = copy_book(my_book);
    // TODO: Print copy info
    print_book_info(copy_of_book);
    
    printf("\n=== Modifying copy only ===\n");
    // TODO: Apply 10% discount to copy only
    apply_discount(copy_of_book, 10.0);
    // TODO: Print both original and copy to show they're different
    printf("\nCopy: \n");
    print_book_info(copy_of_book);
    printf("\nOriginal: \n");
    print_book_info(my_book); 
    return 0;
}
