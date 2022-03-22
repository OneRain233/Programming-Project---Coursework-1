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

void menu() {
    printf("====================================================\n");
    printf("Welcome to Book Management System!\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Find books by name\n");
    printf("4. Find books by author\n");
    printf("5. Find books by year\n");
    printf("6. Admin manage\n");
    printf("0. Exit\n");
    printf("====================================================\n");
    printf("Please input your choice: ");
}

void run_interface() {

    UserList userlist;
    BookList *wholebooklist;

    wholebooklist = malloc(sizeof(BookList));

    FILE *fp = fopen("books.txt", "r");
    load_books(fp, wholebooklist);
    fclose(fp);
    BookList *recBookList = malloc(sizeof(BookList));
    memcpy(recBookList, wholebooklist, sizeof(BookList));

    read_user(&userlist);
    menu();
    listUser(&userlist);
    int choice;
    choice = optionChoice();
    while (choice != 0) {
//        printf("%d\n", choice);
        switch (choice) {
            case 1:
                register_user(&userlist);
                read_user(&userlist);
                break;
            case 2:
                puts("Login");
                User *user = login(&userlist);
                if (user != NULL) {
                    printf("Welcome %s!\n", user->username);
                    printf("%d\n", user->borrowMax);
                    user_menu(user, wholebooklist);

                } else {
                    puts("Login Failed!");
                }
                break;
            case 3:
                printf("====================================================\n");
                puts("Find books by name");
                char name[100];
                printf("Please input the name: ");
                getc(stdin);
                fgets(name, 100, stdin);
                name[strlen(name) - 1] = '\0';

                BookList booklist = find_book_by_title(name);
                if(booklist.length == 0) {
                    puts("!!!No books found!!!");
                } else {
                    printf("%d\n", booklist.length);
                    listBook(&booklist);
                }
//                listBook(&booklist);

                break;
            case 4:
                printf("====================================================\n");
                puts("Find books by author\n");
                char author[100];
                printf("Please input the author: ");
                getc(stdin);
                fgets(author, 100, stdin);

                author[strlen(author) - 1] = '\0';
                BookList res2 = find_book_by_author(author);
                if(booklist.length == 0) {
                    puts("!!!No books found!!!");
                } else {
                    printf("%d\n", res2.length);
                    listBook(&booklist);
                }

                break;
            case 5:
                printf("====================================================\n");
                puts("Find books by year");
                unsigned int year;
                printf("Please input the year: ");
                scanf("%u", &year);
                BookList res3 = find_book_by_year(year);
                if(booklist.length == 1) {
                    puts("!!!No books found!!!");
                } else {
                    printf("%d\n", res3.length);
                    listBook(&booklist);
                }
                break;
            default:
                printf("Invalid choice!\n");
                break;
            case 6:
                puts("Admin");
                auth(wholebooklist, &userlist);
        }
        menu();
        printf("\n");
        choice = optionChoice();


    }
//    FILE *fp1 = fopen("books.txt", "w");
//    store_books(fp1, recBookList);
//    fclose(fp1);


}
