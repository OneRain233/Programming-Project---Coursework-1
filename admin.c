//
// Created by onerain233 on 2022/3/16.
//

#include <malloc.h>
#include "admin.h"
#include "utils.h"
#include "book_management.h"
#include <string.h>
#include <stdlib.h>

const char *username = "admin";
const char *password = "admin";

/* Authentication */
void auth(BookList *booklist, UserList *userlist, char *book_file) {
    char *input_username = (char *) malloc(sizeof(char) * 20);
    char *input_password = (char *) malloc(sizeof(char) * 20);
    printf("Please input your username: ");
    fgets(input_username, 20, stdin);
    input_username[strlen(input_username) - 1] = '\0';
    printf("Please input your password: ");
    fgets(input_password, 20, stdin);
    input_password[strlen(input_password) - 1] = '\0';
    if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
        admin_menu(booklist, book_file);
    } else {
        printf("Wrong username or password!\n");
        return;
    }
}

/* Show admin menu */
void admin_menu_hint(){
    printf("Welcome to the admin menu!\n");
    printf("Please choose the operation you want to do:\n");
    printf("1. Add a book\n");
    printf("2. Delete a book\n");
    printf("3. List all books\n");

    printf("0. exit\n");
}


/* Show the interface of adding books */
void add_book_interface(char *book_file, BookList *list) {
    char *title = (char *) malloc(sizeof(char) * 100);
    char *author = (char *) malloc(sizeof(char) * 100);
    char *tmp_year = (char *) malloc(sizeof(char) * 100);
    char *tmp_copies = (char *) malloc(sizeof(char) * 100);

    unsigned int year;
    unsigned int copies;

    printf("Please input the book title：");
    fgets(title, 100, stdin);
    title[strlen(title) - 1] = '\0';
    printf("Please input the book author：");
    fgets(author, 100, stdin);
    author[strlen(author) - 1] = '\0';
    printf("Please input the year of publication：");
    scanf("%s", tmp_year);
    printf("Please input the copies：");
    scanf("%s", tmp_copies);

    if (isNum(tmp_year) && isNum(tmp_copies)) {
        char *buf;
        year = strtol(tmp_year, &buf, 10);
        copies = strtol(tmp_copies, &buf, 10);
    } else {
        printf("Invalid input!\n");
        return;
    }
    unsigned int id = getLastID(list) + 1;

    //check if exist
    Book *pBook = isExist(list, title, author, year);
    if (pBook != NULL) {
        pBook->copies += copies;
        return;
    }
    Book *book = createBook(id, author, title, year, copies, 0);

    add_book(book, list);
    listBook(list);
    FILE *fp = fopen(book_file, "w");
    store_books(fp, list);
    fclose(fp);
    printf("Add book successfully!\n");
}


/* Show the interface of delete books */
void delete_book_interface(char *book_file, BookList *list) {
    listBook(list);
    int id;
    printf("Please input the book id：");

    id = getOptions();
    if (id == -1) {
        printf("Invalid input!\n");
        return;
    }
    Book *book = findBookByID(list, id);
    remove_book(book, list);

    listBook(list);
    FILE *fp = fopen(book_file, "w");
    store_books(fp, list);
    fclose(fp);
}

/* Show the admin menu */
void admin_menu(BookList *booklist, char *book_file){

    admin_menu_hint();
    int choice = getOptions();

    while(choice != 0){
        switch (choice) {
            case 1:
                add_book_interface(book_file,booklist);
                break;
            case 2:
                delete_book_interface(book_file,booklist);
                break;
            case 3:
                listBook(booklist);
                break;
            default:
                puts("Invalid choice!");
                break;
        }
        admin_menu_hint();
        choice = getOptions();
        while(choice == -1){

            choice = getOptions();
        }
    }

}


