//
// Created by onerain233 on 2022/3/2.
//

#include "login.h"
#include <stdio.h>
#include "user.h"
#include <string.h>

void login(UserList *userlist)
{
    char username[20];
    char password[20];
    printf("username: ");
    scanf("%s", username);
    printf("password: ");
    scanf("%s", password);

    int size = userlist->userNum;
    for(int i = 0; i < size; i++){
        if(strcmp(username, userlist->user[i]->username) == 0 && strcmp(password, userlist->user[i]->password) == 0){
            printf("login success\n");
            return;
        }
    }
    printf("login failed\n");


}
