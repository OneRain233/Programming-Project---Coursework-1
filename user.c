//
// Created by onerain233 on 2022/3/3.
//

#include "user.h"
#include "utils.h"


void user_info(User *pUser);

void user_book_list(User *pUser);

void user_borrowed_book_list(User *pUser);

void user_menu(User *user) {
    puts("Welcome to user menu!");
    puts("1. View user info");
    puts("2. View user's book list");
    puts("3. View user's borrowed book list");

    int choice = optionChoice();
    while(choice != 1 && choice !=2 && choice !=3) {
        puts("Please input a valid choice!");
        choice = optionChoice();
    }
    switch (choice) {
        case 1:
            user_info(user);
            break;
        case 2:
            user_book_list(user);
            break;
        case 3:
            user_borrowed_book_list(user);
            break;
        default:
            puts("Invalid choice!");
            break;
    }
}

void user_borrowed_book_list(User *pUser) {

}

void user_book_list(User *pUser) {

}

void user_info(User *pUser) {
    puts("User info:");
    printf("Name: %s\n", pUser->username);
//    printf("ID: %d\n", pUser->id);
//    printf("Email: %s\n", pUser->email);
//    printf("Phone: %s\n", pUser->phone);
//    printf("Address: %s\n", pUser->address);
//    printf("
}
