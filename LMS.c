#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_TITLE_LENGTH 50
#define MAX_AUTHOR_LENGTH 50

// Book structure
typedef struct {
    int id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    int isAvailable;
} Book;

Book library[MAX_BOOKS];
int bookCount = 0;

// Function declarations
void addBook();
void displayBooks();
void searchBook();
void borrowBook();
void returnBook();
void menu();

int main() {
    menu();
    return 0;
}

// Function to display the menu
void menu() {
    int choice;
    while (1) {
        printf("\n====== Library Management System ======\n");
        printf("1. Add a new book\n");
        printf("2. Display all books\n");
        printf("3. Search for a book\n");
        printf("4. Borrow a book\n");
        printf("5. Return a book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                borrowBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                printf("Exiting the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to add a new book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book newBook;
    newBook.id = bookCount + 1;

    printf("Enter book title: ");
    getchar(); // to clear newline character in input buffer
    fgets(newBook.title, MAX_TITLE_LENGTH, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // Remove newline character

    printf("Enter book author: ");
    fgets(newBook.author, MAX_AUTHOR_LENGTH, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0'; // Remove newline character

    newBook.isAvailable = 1;
    library[bookCount] = newBook;
    bookCount++;

    printf("Book added successfully! Book ID: %d\n", newBook.id);
}

// Function to display all books
void displayBooks() {
    if (bookCount == 0) {
        printf("No books available in the library.\n");
        return;
    }

    printf("\nAvailable books:\n");
    printf("ID\tTitle\t\tAuthor\t\tAvailability\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%d\t%s\t\t%s\t\t%s\n", library[i].id, library[i].title, library[i].author,
               library[i].isAvailable ? "Available" : "Not Available");
    }
}

// Function to search for a book by title
void searchBook() {
    char title[MAX_TITLE_LENGTH];
    printf("Enter the title of the book to search: ");
    getchar(); // to clear newline character in input buffer
    fgets(title, MAX_TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = '\0'; // Remove newline character

    for (int i = 0; i < bookCount; i++) {
        if (strcasecmp(library[i].title, title) == 0) {
            printf("Book found! ID: %d, Title: %s, Author: %s, Availability: %s\n",
                   library[i].id, library[i].title, library[i].author,
                   library[i].isAvailable ? "Available" : "Not Available");
            return;
        }
    }
    printf("Book not found.\n");
}

// Function to borrow a book
void borrowBook() {
    int id;
    printf("Enter the ID of the book to borrow: ");
    scanf("%d", &id);

    if (id > 0 && id <= bookCount) {
        if (library[id - 1].isAvailable) {
            library[id - 1].isAvailable = 0;
            printf("You have successfully borrowed the book: %s\n", library[id - 1].title);
        } else {
            printf("Sorry, the book is currently not available.\n");
        }
    } else {
        printf("Invalid book ID.\n");
    }
}

// Function to return a book
void returnBook() {
    int id;
    printf("Enter the ID of the book to return: ");
    scanf("%d", &id);

    if (id > 0 && id <= bookCount) {
        if (!library[id - 1].isAvailable) {
            library[id - 1].isAvailable = 1;
            printf("You have successfully returned the book: %s\n", library[id - 1].title);
        } else {
            printf("The book was not borrowed.\n");
        }
    } else {
        printf("Invalid book ID.\n");
    }
}

