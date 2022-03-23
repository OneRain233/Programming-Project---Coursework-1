//
// Created by onerain233 on 2022/3/2.
//

#include "login.h"
#include <stdio.h>
#include "datastructure.h"
#include <string.h>

User *login(UserList *userlist) {
    char username[20];
    char password[20];
    printf("username: ");
    scanf("%s", username);
    printf("password: ");
    scanf("%s", password);

    User *cur = userlist->list;
    while(cur != NULL) {
        if(strcmp(username, cur->username) == 0){
            if(strcmp(password, cur->password) == 0){
                return cur;
            }
            else{
                printf("Invalid username or password!");
                return NULL;
            }
        }


        cur = cur->next;
    }
    return NULL;
}
