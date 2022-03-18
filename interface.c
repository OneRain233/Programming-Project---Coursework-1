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
#include "library.h"
#include "admin.h"
#include "book_management.h"

void menu() {
    printf("Welcome to Book Management System!\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("999. Test\n");
    printf("3. Find books by name\n");
    printf("4. Find books by author\n");
    printf("5. Find books by year\n");
    printf("0. Exit\n");
    printf("Please input your choice: ");
}
//
//void init(BookList *booklist, UserList *userlist) {
//    puts("Initializing...");
//    booklist = malloc(sizeof(BookList));
//    booklist->list = NULL;
//    read_books("books.txt", booklist);
//    read_user(userlist);
//    puts("Initialization finished.");
//}

void run_interface() {

    UserList userlist;
    BookList *wholebooklist;
//    init(&booklist, &userlist);

    wholebooklist = malloc(sizeof(BookList));
//    read_books("books.txt", wholebooklist);

    FILE *fp = fopen("books.txt", "r");
    load_books(fp, wholebooklist);
    fclose(fp);
    BookList *recBookList = malloc(sizeof(BookList));
    memcpy(recBookList, wholebooklist, sizeof(BookList));

    read_user(&userlist);
//    listBook(wholebooklist);
    menu();


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
//                    read_borrow_books(user);
//                    user->borrowMax = 10;
//                    printf("%d", user->borrowNum);
//                    borrow_book(user, 1, wholebooklist);
//                    listBook(wholebooklist);
//                    return_book(user, 1, wholebooklist);
//                    listBook(wholebooklist);
                    user_menu(user, wholebooklist);

                } else {
                    puts("Login Failed!");
                }
                break;
            case 999:
                puts("test");
                add_book_interface(wholebooklist);
                break;
            case 3:
                puts("Find books by name");
                char name[100];
                printf("Please input the name: ");
                getc(stdin);
                fgets(name, 100, stdin);
                name[strlen(name) - 1] = '\0';

                BookList booklist = find_book_by_title(name);
                listBook(&booklist);

                break;
            case 4:
                puts("Find books by author\n");
                char author[100];
                printf("Please input the author: ");
                getc(stdin);
                fgets(author, 100, stdin);

                author[strlen(author) - 1] = '\0';
                BookList res2 = find_book_by_author(author);
                listBook(&res2);
                printf("\n");
                break;
            case 5:
                puts("Find books by year");
                unsigned int year;
                printf("Please input the year: ");
                scanf("%u", &year);
                BookList res3 = find_book_by_year(year);
                listBook(&res3);
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
        menu();
        printf("\n");
        choice = optionChoice();


    }
//    FILE *fp1 = fopen("books.txt", "w");
//    store_books(fp1, recBookList);
//    fclose(fp1);


}
