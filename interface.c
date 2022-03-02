//
// Created by onerain233 on 2022/3/1.
//

#include <stdio.h>
#include "interface.h"
#include "utils.h"
#include "register.h"

void menu(){
    printf("Welcome to Book Management System!\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");

}


void run_interface(){
    menu();
    int choice;
    choice = optionChoice();

    switch (choice) {
        case 1:
            register_user();
            read_user();
            break;
        case 2:
            puts("Login");
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}
