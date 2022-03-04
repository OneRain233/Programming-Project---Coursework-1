//
// Created by onerain233 on 2022/3/3.
//

#include "user.h"
#include "utils.h"
#include <string.h>

void user_menu(User *user) {
    puts("Welcome to user menu!");
    puts("1. View user info");
    puts("2. View user's book list");
//    puts("3. View user's borrowed book list");
    puts("4. Exit");

    int choice = optionChoice();
    while (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
        puts("Please input a choice!");
        choice = optionChoice();
    }
    while (choice != 4) {
        switch (choice) {
            case 1:
                user_info(user);
                break;
            case 2:
//            user_book_list(user);
                user_borrowed_book_list(user);
                break;
            case 3:
                user_borrowed_book_list(user);
                break;
            default:
                puts("Invalid choice!");
                break;
        }
        user_menu(user);
        choice = optionChoice();
    }

}

void user_borrowed_book_list(User *pUser) {
    if (pUser->borrowNum == 0) {
        puts("You have not borrowed any book!\n");
        return;
    }
    puts("User borrowed book list:");
    listBook(pUser->bookList);

}

void user_info(User *pUser) {
    puts("-----User info-----");
    printf("Name: %s\n", pUser->username);
    printf("Max borrow num: %d\n", pUser->borrowMax);
    printf("Borrowed num: %d\n", pUser->borrowNum);
    printf("\n");
}


void read_borrow_books(User *user) {

    FILE *fp = fopen("borrow.txt", "r");
    if (fp == NULL) {
        puts("File open error!");
        return;
    }

    char line[1024];
    while (fgets(line, 1024, fp) != NULL) {
        char *p = strtok(line, "-");
//        puts(p);
        if (strcmp(p, user->username) == 0) {
//            puts(p);
            p = strtok(NULL, "-");
            int size = (int) *p - '0';
            printf("%d\n", size);
            for (int i = 0; i < size; i++) {
                p = strtok(NULL, "-");
                printf("%s\n", p);
            }
        }
    }

}