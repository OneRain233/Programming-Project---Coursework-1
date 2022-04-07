//
// Created by onerain233 on 2022/3/1.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include "utils.h"
#include "register.h"
#include "login.h"
#include "user.h"
#include "admin.h"
#include "book_management.h"


/* menu()
 * -----------
 * Show the menu of the interface
 *
 * return: No return
 *
*/
void menu() {
    printf_green("\n====Welcome to Book Management System!====\n");
    fprintf(stdout, "1. Register\n");
    fprintf(stdout, "2. Login\n");
    fprintf(stdout, "3. Find books by name\n");
    fprintf(stdout, "4. Find books by author\n");
    fprintf(stdout, "5. Find books by year\n");
    fprintf(stdout, "6. Admin manage\n");
    fprintf(stdout, "0. Exit\n");
    fprintf(stdout, "Please input your choice: ");

}

/* run_interface()
 * ------------------
 *
 * Run the main interface
 * book_file: the file of books
 * user_file: the file of users
 *
 * return: No return
 */
void run_interface(char *book_file, char *user_file) {

    UserList *userlist = (UserList *) malloc(sizeof(userlist));
    BookList *wholebooklist = (BookList *) malloc(sizeof(BookList));

    FILE *fp = fopen(book_file, "r");
    if (fp == NULL) {
        fprintf(stderr,"Error: Can't open file %s\n", book_file);
        exit(1);
    }
    load_books(fp, wholebooklist);
    fclose(fp);
    BookList *recBookList = (BookList *) malloc(sizeof(BookList));
    memcpy(recBookList, wholebooklist, sizeof(BookList));

    read_user(user_file, userlist);
    FILE *user = fopen(user_file, "r");
    if (user == NULL) {
        fprintf(stderr,"Error: Can't open file %s\n", user_file);
        exit(1);
    }
    read_borrow_books(user, userlist, wholebooklist);
    menu();
    fclose(user);
    int choice = getOptions();

    while (choice != 0) {

        switch (choice) {
            case 1:
                register_user(userlist);
                break;
            case 2:
                printf_red("\nLogin\n");
                User *User = login(userlist);
                if (User != NULL) {
                    user_menu(User, wholebooklist);

                } else {
                    printf_red("Login Failed!\n");
                }
                break;
            case 3:
                printf_green("Find books by name\n");
                char name[100];
                fprintf(stdout, "Please input the name: ");
                fgets(name, 100, stdin);
                name[strlen(name) - 1] = '\0';

                BookList booklist = find_book_by_title(name, wholebooklist);
                if(booklist.length == 0) {
                    fprintf(stderr, "!!!No books found!!!\n");
                } else {
//                    fprintf(stderr, "%d\n", booklist.length);
                    listBook(&booklist);
                }
                break;
            case 4:
                printf_green("Find books by author\n");
                char author[100];
                fprintf(stdout, "Please input the author: ");
                fgets(author, 100, stdin);

                author[strlen(author) - 1] = '\0';
                puts(author);
                BookList res2 = find_book_by_author(author, wholebooklist);
                if(res2.length == 0) {
                    fprintf(stderr, "!!!No books found!!!\n");
                } else {
                    listBook(&res2);
                }
                break;
            case 5:
                fprintf(stdout, "Find books by year\n");
                unsigned int year;
                fprintf(stdout, "Please input the year: ");
                scanf("%d", &year);
                BookList res3 = find_book_by_year(year, wholebooklist);
                if(res3.length == 0) {
                    fprintf(stderr, "!!!No books found!!!\n");
                } else {
//                    fprintf(stdout, "%d\n", res3.length);
                    listBook(&res3);
                }
                break;
            case 6:

                printf_green("Admin\n");
                auth(userlist, wholebooklist, book_file);
                break;
            default:
//                printf("Your choice is %d!\n", choice);
                fprintf(stderr, "Invalid choice!\n");
                break;
        }

        menu();
        choice = getOptions();
        while (choice == -1) {
            menu();
            fprintf(stderr, "Invalid choice!\n");
            choice = getOptions();
        }
    }
    FILE *fp1 = fopen(book_file, "w");
    store_books(fp1, recBookList);
    FILE *fp2 = fopen(user_file, "w");
    store_user(fp2, userlist);
    fclose(fp1);
    fclose(fp2);
    free(userlist);
    free(wholebooklist);
    free(recBookList);

}
