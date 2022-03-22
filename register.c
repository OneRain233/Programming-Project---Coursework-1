//
// Created by onerain233 on 2022/3/1.
//
#include "book_management.h"
#include "datastructure.h"
#include <string.h>
#include <stdlib.h>


int check_exist(UserList *userlist, char *username) {
    User *cur = userlist->list;
    if(cur == NULL) {
        return 0;
    }
    else{
        while(cur != NULL) {
            if(strcmp(cur->username, username) == 0) {
                return 1;
            }
            cur = cur->next;
        }
    }
    return 0;
}

void insertUser(UserList *userlist, User *user) {
    User *cur = userlist->list;
    if (cur == NULL) {
        userlist->list = user;
        userlist->userNum++;
        return;
    }
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = user;
    userlist->userNum++;
}

void listUser(UserList *userlist) {
    User *cur = userlist->list;
    if (cur == NULL) {
        printf("No user\n");
        return;
    }
    printf("User list:\n");
    printf("%s\t%s", "ID", "Username\n");
    while (cur != NULL) {
        printf("%d\t%s\n", cur->id, cur->username);
        cur = cur->next;
    }
}
User *createUser(unsigned int id, char *username, char *password, int borrowNum, int borrowMax){
    User *new_user = malloc(sizeof(User));
    new_user -> username = username;
    new_user -> password = password;
    new_user -> borrowNum = borrowNum;
    new_user -> borrowMax = borrowMax;
    new_user -> id = id;
    return new_user;

}

void read_user(UserList *userlist) {
    FILE *fp;
    fp = fopen("user.txt", "r");
    if (fp == NULL) {
        printf("Open file error！\n");
        exit(0);
    }
    char *username = malloc(sizeof(char) * 20);
    char *password = malloc(sizeof(char) * 20);
    int borrowNum;
    int maxBorrowNum;
    int user_cnt = 0;

    while (fscanf(fp, "%s\t%s\t%d\t%d\n", username, password, &borrowNum, &maxBorrowNum) != EOF) {
        User *user = malloc(sizeof(User));
        user->username = username;
        user->password = password;
        user->borrowNum = borrowNum;
        user->borrowMax = maxBorrowNum;
        user->next = NULL;
        user->id = user_cnt;
        insertUser(userlist, user);
        user_cnt++;
    }
    userlist->userNum = user_cnt;
    fclose(fp);
//    listUser(userlist);
}


void write2file(User *user) {
    FILE *fp;
    fp = fopen("user.txt", "a");
    if (fp == NULL) {
        printf("Failed to open file！\n");
        exit(0);
    }
    fprintf(fp, "%s\t", user->username);
    fprintf(fp, "%s\t", user->password);
    fprintf(fp, "%d\t", user->borrowNum);
    fprintf(fp, "%d\n", user->borrowMax);
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
    new_user->borrowMax = 10;
    new_user->borrowNum = 0;

    new_user->id = userlist->userNum;

    write2file(new_user);
    free(new_user);


}
