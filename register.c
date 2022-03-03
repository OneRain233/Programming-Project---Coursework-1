//
// Created by onerain233 on 2022/3/1.
//
#include "book_management.h"
#include "datastructure.h"
#include <string.h>
#include <stdlib.h>


int check_exist(UserList *userlist, char *username) {
    int size = userlist->userNum;
    for (int i = 0; i < size; i++) {
        if (strcmp(userlist->user[i]->username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void read_user(UserList *userlist) {
    FILE *fp;
    fp = fopen("user.txt", "rb");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        exit(0);
    }

    char username[20];
    char password[20];
    int user_cnt = 0;
//    User *user;

    while (fscanf(fp, "%s", username) != EOF) {
        User *user;
//        strcpy(user->username, username);
        fscanf(fp, "%s", password);
//        strcpy(user->password, password);

        user = (User *) malloc(sizeof(User));
        user->username = (char *) malloc(sizeof(char) * 20);
        user->password = (char *) malloc(sizeof(char) * 20);
        strcpy(user->username, username);
        strcpy(user->password, password);

        userlist->user[user_cnt] = user;
        user_cnt++;

    }

    userlist->userNum = user_cnt;
    fclose(fp);
}


void write2file(User *user) {
    FILE *fp;
    fp = fopen("user.txt", "a");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        exit(0);
    }
    fprintf(fp, "%s\t", user->username);
    fprintf(fp, "%s\n", user->password);

    fclose(fp);
}

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

void register_user(UserList *userlist) {

    char username[20];
    char password[20];
    char password_confirm[20];

    printf("Please enter your username: ");
    scanf("%s", username);

    if (check_exist(userlist, username)) {
        printf("The username has been registered!\n");
        return;
    }
    if(check_valid(username) == 0){
        return;
    }
    printf("Please enter your password: ");
    scanf("%s", password);
    printf("Please enter your password again: ");
    scanf("%s", password_confirm);

    if (strcmp(password, password_confirm) != 0) {
        printf("Password not match!\n");
        return;
    }

    User *new_user;
    new_user = (User *) malloc(sizeof(User));
    new_user->username = (char *) malloc(sizeof(char) * 20);
    new_user->password = (char *) malloc(sizeof(char) * 20);

    strcpy(new_user->username, username);
    strcpy(new_user->password, password);

    write2file(new_user);
    free(new_user);
//    userlist->user[userlist->userNum] = new_user;
//    free(new_user);
//    userlist->userNum++;


}
