//
// Created by onerain233 on 2022/3/1.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "interface.h"
#include "utils.h"
#include "register.h"
#include "login.h"
#include "user.h"
#include "admin.h"
#include "book_management.h"

/* Show the menu */
void menu() {
    printf_green("## Welcome to Book Management System! ##\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Find books by name\n");
    printf("4. Find books by author\n");
    printf("5. Find books by year\n");
    printf("6. Admin manage\n");
    printf("0. Exit\n");
    printf("Please input your choice: ");
}

/* Show the interface */
void run_interface(char *book_file, char *user_file) {

    UserList *userlist = (UserList *) malloc(sizeof(userlist));
    BookList *wholebooklist = (BookList *) malloc(sizeof(BookList));

    FILE *fp = fopen(book_file, "r");
    load_books(fp, wholebooklist);
    fclose(fp);
    BookList *recBookList = (BookList *) malloc(sizeof(BookList));
    memcpy(recBookList, wholebooklist, sizeof(BookList));

    read_user(wholebooklist, userlist);
    FILE *user = fopen(user_file, "r");
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
                printf_red("Login\n");
                User *user = login(userlist);
                if (user != NULL) {
                    printf("Welcome %s!\n", user->username);
                    user_menu(user, wholebooklist);

                } else {
                    printf_red("Login Failed!\n");
                }
                break;
            case 3:
                puts("Find books by name");
                char name[100];
                printf("Please input the name: ");
                getc(stdin);
                fgets(name, 100, stdin);
                name[strlen(name) - 1] = '\0';

                BookList booklist = find_book_by_title(name, wholebooklist);
                if(booklist.length == 0) {
                    printf("!!!No books found!!!\n");
                } else {
                    printf("%d\n", booklist.length);
                    listBook(&booklist);
                }
                break;
            case 4:
                puts("Find books by author\n");
                char author[100];
                printf("Please input the author: ");
                getc(stdin);
                fgets(author, 100, stdin);

                author[strlen(author) - 1] = '\0';
                puts(author);
                BookList res2 = find_book_by_author(author, wholebooklist);
                if(res2.length == 0) {
                    printf("!!!No books found!!!\n");
                } else {
                    printf("%d\n", res2.length);
                    listBook(&res2);
                }
                break;
            case 5:
                printf("Find books by year\n");
                unsigned int year;
                printf("Please input the year: ");
                scanf("%u", &year);
                BookList res3 = find_book_by_year(year, wholebooklist);
                if(res3.length == 0) {
                    printf("!!!No books found!!!\n");
                } else {
                    printf("%d\n", res3.length);
                    listBook(&res3);
                }
                break;
            case 6:
                printf("Admin\n");
                auth(wholebooklist, userlist, book_file);
                break;
            default:
                printf("Your choice is %d!\n", choice);
                printf("Invalid choice!\n");
                break;
        }

        menu();
        choice = getOptions();
        while(choice == -1) {
            choice = getOptions();
        }
    }
    FILE *fp1 = fopen(book_file, "w");
    store_books(fp1, recBookList);
    FILE *fp2 = fopen(user_file, "w");
    store_user(fp2, userlist);
    fclose(fp1);
    fclose(fp2);

}
