//
// Created by onerain233 on 2022/3/1.
//
#include "book_management.h"
#include "datastructure.h"
#include "user.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>

/* Check if the username is existed */
int check_exist(UserList *userlist, char *username) {
    User *cur = userlist->list;
    if (cur == NULL) {
        return 0;
    } else {
        while(cur != NULL) {
            if(strcmp(cur->username, username) == 0) {
                return 1;
            }
            cur = cur->next;
        }
    }
    return 0;
}

/* Create a User */
User *createUser(unsigned int id, char *username, char *password, int borrowNum, int borrowMax) {
    User *new_user = (User *) malloc(sizeof(User));
    new_user->username = username;
    new_user->password = password;
    new_user->borrowNum = borrowNum;
    new_user->borrowMax = borrowMax;
    new_user->id = id;
    new_user->next = NULL;;
    return new_user;

}

/* Insert User to the linked list */
User *insertUser(UserList *userlist, unsigned int id, char *username, char *password, int borrowNum, int borrowMax) {
    User *user = createUser(id, username, password, borrowNum, borrowMax);
    User *cur = userlist->list;
    if (cur == NULL) {
        userlist->list = user;
        return user;
    }
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = user;
    return user;
}

/* Read users from file */
void read_user(BookList *booklist, UserList *userlist) {
    FILE *fp;
    fp = fopen("user.txt", "r");
    if (fp == NULL) {
        printf("Open file error！\n");
        exit(0);
    }
    char *username = (char *) malloc(sizeof(char) * 20);
    char *password = (char *) malloc(sizeof(char) * 20);
    int borrowNum;
    int maxBorrowNum;
    int user_cnt = 0;

    while (fscanf(fp, "%s\t%s\t%d\t%d\n", username, password, &borrowNum, &maxBorrowNum) != EOF) {
        char *buf = (char *) malloc(sizeof(char) * 20);
        char *tmp_username = (char *) malloc(20 * sizeof(char));
        char *tmp_password = (char *) malloc(20 * sizeof(char));
        int tmp_borrowNum;
        int tmp_maxBorrowNum;
        strcpy(tmp_username, username);
        strcpy(tmp_password, password);
        tmp_borrowNum = borrowNum;
        tmp_maxBorrowNum = maxBorrowNum;
        User *user = insertUser(userlist,
                                user_cnt,
                                tmp_username,
                                tmp_password,
                                tmp_borrowNum,
                                tmp_maxBorrowNum);
        user_cnt++;
        for (int i = 0; i < user->borrowNum; i++) {
            fscanf(fp, "%s\n", buf);
        }

    }
    userlist->userNum = user_cnt;
    fclose(fp);

}

/* Check if the username is valid */
int check_valid(char *username){
    char invalid_char[] = "!@#$%^&*()_+-=[]{}|;':\",./<>?`~";
    for (int i = 0; i < strlen(username); i++) {
        for (int j = 0; j < strlen(invalid_char); j++) {
            if (username[i] == invalid_char[j]) {
                printf("Username cannot contain special char！\n");
                return 0;
            }
        }
    }

    if (strlen(username) < 6 || strlen(username) > 20) {
        printf("Username length should be between 6 and 20！\n");
        return 0;
    }
    return 1;
}

/* Register menu */
void register_user(UserList *userlist) {

    char username[20];
    char password[20];
    char password_confirm[20];

    printf("Please enter your username: ");
    scanf("%s", username);

    while(check_exist(userlist, username) == 1) {
        printf("The username has been registered!\n");
        printf("Please enter your username: ");
        scanf("%s", username);
    }

    while(check_valid(username) == 0) {
        printf("Please enter your username: ");
        scanf("%s", username);
    }
    printf("Please enter your password: ");
    scanf("%s", password);
    printf("Please enter your password again: ");
    scanf("%s", password_confirm);

    while(strcmp(password, password_confirm) != 0) {
        printf("The password is not the same!\n");
        printf("Please enter your password: ");
        scanf("%s", password);
        printf("Please enter your password again: ");
        scanf("%s", password_confirm);
    }

    User *new_user;
    new_user = (User *) malloc(sizeof(User));
    new_user->username = (char *) malloc(sizeof(char) * 20);
    new_user->password = (char *) malloc(sizeof(char) * 20);

    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    new_user->borrowMax = 10;
    new_user->borrowNum = 0;

    new_user->id = userlist->userNum;
    insertUser(userlist, new_user->id,
               new_user->username,
               new_user->password,
               new_user->borrowNum,
               new_user->borrowMax);
    fflush(stdin);
    printf("Register successfully!\n");
}
