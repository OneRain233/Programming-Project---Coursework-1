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

/* auth()
 * -------------------------
 * authenticate the admin
 *
 * userlist: the user list
 * booklist: the book list
 * book_file: the filename of book file
 *
 * return: No return
*/
void auth(UserList *userlist, BookList *booklist, char *book_file) {
    char *input_username = (char *) malloc(sizeof(char) * 20);
    char *input_password = (char *) malloc(sizeof(char) * 20);
    printf("Please input your username: ");
    fgets(input_username, 20, stdin);
    input_username[strlen(input_username) - 1] = '\0';
    printf("Please input your password: ");
    fgets(input_password, 20, stdin);
    input_password[strlen(input_password) - 1] = '\0';
    if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
        admin_menu(userlist, booklist, book_file);
    } else {
        printf("Wrong username or password!\n");
        return;
    }
}

/* admin_menu_hint()
 * ------------------------
 * show the menu of admin
 *
 * return: No return
*/
void admin_menu_hint() {
    printf_green("\n====Welcome to the admin menu!====\n");
    fprintf(stdout, "Please choose the operation you want to do:\n");
    fprintf(stdout, "1. Add a book\n");
    fprintf(stdout, "2. Delete a book\n");
    fprintf(stdout, "3. List all books\n");
    fprintf(stdout, "4. Edit a book\n");
    fprintf(stdout, "5. Show user borrowed books\n");
    fprintf(stdout, "0. exit\n");
    fprintf(stdout, "Please input your choice: ");
}

/* show_users_booklist()
 * ------------------------
 * show the users borrowed books
 *
 * userlist: the user list
 *
 *
 * return: No return
*/
void show_users_booklist(UserList *userlist) {
    User *cur_user = userlist->list;
    while (cur_user != NULL) {
        printf_green("\n=====User borrowed books=====\n");
        fprintf(stdout, "User name: %s\n", cur_user->username);
        listBook(cur_user->bookList);
        cur_user = cur_user->next;
    }
}


/* add_book_interface()
 * ------------------------
 * add book interface
 *
 * book_file: the filename of book file
 * list: the book list
 *
 * return: No return
*/
void add_book_interface(char *book_file, BookList *list) {
    char *title = (char *) malloc(sizeof(char) * 100);
    char *author = (char *) malloc(sizeof(char) * 100);
    char *tmp_year = (char *) malloc(sizeof(char) * 100);
    char *tmp_copies = (char *) malloc(sizeof(char) * 100);

    unsigned int year;
    unsigned int copies;

    fprintf(stdout, "Please input the book title：");
    fgets(title, 100, stdin);
    title[strlen(title) - 1] = '\0';
    fprintf(stdout, "Please input the book author：");
    fgets(author, 100, stdin);
    author[strlen(author) - 1] = '\0';
    fprintf(stdout, "Please input the year of publication：");
    scanf("%s", tmp_year);
    fprintf(stdout, "Please input the copies：");
    scanf("%s", tmp_copies);

    if (isNum(tmp_year) && isNum(tmp_copies)) {
        char *buf;
        year = strtol(tmp_year, &buf, 10);
        copies = strtol(tmp_copies, &buf, 10);
    } else {
        fprintf(stderr, "Invalid input!\n");
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

    insertBookByPointer(list, book);
    listBook(list);
    FILE *fp = fopen(book_file, "w");
    store_books(fp, list);
    fclose(fp);
    fprintf(stdout, "Add book successfully!\n");
}


/* delete_book_interface()
 * ------------------------
 * delete book interface
 *
 * book_file: the filename of book file
 * list: the book list
 *
 * return: No return
*/
void delete_book_interface(char *book_file, BookList *list) {
    listBook(list);
    int id;
    fprintf(stdout, "Please input the book id：");
    id = getOptions();
    if (id == -1) {
        fprintf(stderr, "Invalid input!\n");
        return;
    }

    Book *book = findBookByID(list, id);
    if (book == NULL) {
        fprintf(stderr, "No such book!\n");
        return;
    }
//    if (book->borrowed != 0) {
//        fprintf(stderr, "The book is borrowed, can't delete!\n");
//        return;
//    }
    remove_book(book, list);

    listBook(list);
    FILE *fp = fopen(book_file, "w");
    store_books(fp, list);
    fclose(fp);
}

/* admin_menu()
 * ------------------------
 * show admin menu
 *
 * userlist: the user list
 * booklist: the book list
 * book_file: the filename of book file
 *
 * return: No return
*/
void admin_menu(UserList *userlist, BookList *booklist, char *book_file) {

    admin_menu_hint();
    int choice = getOptions();

    while (choice != 0) {
        switch (choice) {
            case 1:
                add_book_interface(book_file, booklist);
                break;
            case 2:
                delete_book_interface(book_file, booklist);
                break;
            case 3:
                listBook(booklist);
                break;
            case 4:
                puts("Edit a book");
                break;
            case 5:
                show_users_booklist(userlist);
                break;
            default:
                fprintf(stderr, "Invalid choice!\n");
                break;
        }
        admin_menu_hint();
        choice = getOptions();
        while (choice == -1) {
            admin_menu_hint();
            fprintf(stderr, "Invalid choice!\n");
            choice = getOptions();
        }
    }

}



