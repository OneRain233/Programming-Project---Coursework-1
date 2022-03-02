//
// Created by onerain233 on 2022/3/1.
//

#include <stdio.h>
#include "interface.h"
#include "utils.h"
#include "register.h"
#include "login.h"

void menu(){
    printf("Welcome to Book Management System!\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");

}



void run_interface(){
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
            login(&userlist);
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}
