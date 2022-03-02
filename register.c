//
// Created by onerain233 on 2022/3/1.
//
#include "book_management.h"
#include "user.h"
#include <string.h>
#include <stdlib.h>




void read_user(UserList *userlist){
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

    while(fscanf(fp, "%s", username) != EOF){
        User *user;
//        strcpy(user->username, username);
        fscanf(fp, "%s", password);
//        strcpy(user->password, password);

        user = (User *)malloc(sizeof(User));
        user->username = (char *)malloc(sizeof(char) * 20);
        user->password = (char *)malloc(sizeof(char) * 20);
        strcpy(user->username, username);
        strcpy(user->password, password);

        userlist->user[user_cnt] = user;
        user_cnt++;

    }

    userlist->userNum = user_cnt;
    fclose(fp);

    return;
}


void write2file(User *user){
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


void register_user(UserList *userlist){

    char username[20];
    char password[20];
    char password_confirm[20];

    printf("Please enter your username: ");
    scanf("%s", username);
    printf("Please enter your password: ");
    scanf("%s", password);
    printf("Please enter your password again: ");
    scanf("%s", password_confirm);

    if (strcmp(password, password_confirm) != 0) {
        printf("Password not match!\n");
        return;
    }

    User *new_user;
    new_user = (User *)malloc(sizeof(User));
    new_user -> username = (char *)malloc(sizeof(char) * 20);
    new_user -> password = (char *)malloc(sizeof(char) * 20);

    strcpy(new_user -> username, username);
    strcpy(new_user -> password, password);

    write2file(new_user);
    free(new_user);
//    userlist->user[userlist->userNum] = new_user;
//    free(new_user);
//    userlist->userNum++;


}
