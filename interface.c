//
// Created by onerain233 on 2022/3/1.
//

#include <stdio.h>
#include "interface.h"
#include "utils.h"
#include "register.h"
#include "login.h"
#include "user.h"
#include "library.h"

void menu() {
    printf("Welcome to Book Management System!\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("4. test");
    printf("Please input your choice: ");
}


void run_interface() {
    menu();
    UserList userlist;
//    init_userlist(&userlist);
    int choice;
    read_user(&userlist);
    choice = optionChoice();

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
                read_borrow_books(user);
                user_menu(user);
            } else {
                puts("Login Failed!");
            }
            break;
        case 4:
            puts("test");
            read_books("books.txt");
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}
