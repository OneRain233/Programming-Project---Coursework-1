//
// Created by onerain233 on 2022/3/16.
//

#include <malloc.h>
#include "admin.h"
#include "utils.h"
#include "library.h"
#include "book_management.h"


void admin_menu_hint(){

    puts("Welcome to the admin menu!");
    puts("Please choose the operation you want to do:");
    puts("1. Add a book");
    puts("2. Delete a book");
    puts("3. List all books");

    puts("4. Add a user");
    puts("5. Delete a user");
    puts("6. List all users");

    puts("0. exit");
}


void add_book_interface(BookList *list){
    char *title = malloc(sizeof(char) * 100);
    char *author = malloc(sizeof(char) * 100);
    unsigned int year;
    unsigned int copies;

    printf("Please input the book title：");
    scanf("%s", title);
    printf("Please input the book author：");
    scanf("%s", author);
    printf("Please input the year of publication：");
    scanf("%d", &year);
    printf("Please input the copies：");
    scanf("%d", &copies);

    Book *book = createBook(list->length,author, title, year, copies);
    book->id = list->length + 1;

    add_book(book, list);
    listBook(list);
    FILE *fp = fopen("books.txt", "w");
    store_books(fp,list);
    fclose(fp);
}



void admin_menu(BookList *booklist, UserList *userlist){

    admin_menu_hint();

    int choice = optionChoice();
    while(choice != 0){
        switch (choice) {
            case 1:
                add_book_interface(booklist);
                break;
            case 2:
//                delete_book_interface(booklist);
                break;
            case 3:
                listBook(booklist);
                break;
            case 4:
//                add_user();
                puts("Not implemented yet!");
                break;

            case 5:
//                delete_user();
                puts("Not implemented yet!");
                break;

            case 6:
                puts("Not implemented yet!");
                break;
            default:
                puts("Invalid choice!");
                break;
        }
        choice = optionChoice();
    }
}


