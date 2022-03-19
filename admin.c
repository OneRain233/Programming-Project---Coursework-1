//
// Created by onerain233 on 2022/3/16.
//

#include <malloc.h>
#include "admin.h"
#include "utils.h"
#include "library.h"
#include "book_management.h"
#include <string.h>

const char *username = "admin";
const char *password = "admin";


void auth(BookList *booklist, UserList *userlist){
    printf("====================================================\n");
    char *input_username = (char *)malloc(sizeof(char) * 20);
    char *input_password = (char *)malloc(sizeof(char) * 20);
    printf("Please input your username: ");
    scanf("%s", input_username);
    printf("Please input your password: ");
    scanf("%s", input_password);
    if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
        admin_menu(booklist, userlist);
    } else {
        printf("Wrong username or password!\n");
        return;
    }
}

void admin_menu_hint(){
    printf("====================================================\n");
    puts("Welcome to the admin menu!");
    puts("Please choose the operation you want to do:");
    puts("1. Add a book");
    puts("2. Delete a book");
    puts("3. List all books");

    puts("0. exit");
    printf("====================================================\n");
}


void add_book_interface(BookList *list){
    printf("====================================================\n");
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
    printf("Add book successfully!\n");
    printf("====================================================\n");
}


void delete_book_interface(BookList *list) {
    printf("====================================================\n");
    listBook(list);
    unsigned int id;
    printf("Please input the book id：");
    scanf("%d", &id);
    deleteBook(list, id);

    listBook(list);
    FILE *fp = fopen("books.txt", "w");
    store_books(fp, list);
    fclose(fp);
    printf("====================================================\n");
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
                delete_book_interface(booklist);
                break;
            case 3:
                listBook(booklist);
                break;

            default:
                puts("Invalid choice!");
                break;
        }
        admin_menu_hint();
        choice = optionChoice();
    }
}


