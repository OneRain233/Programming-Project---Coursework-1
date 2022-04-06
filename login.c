//
// Created by onerain233 on 2022/3/2.
//

#include "login.h"
#include <stdio.h>
#include "datastructure.h"
#include <string.h>
#include <malloc.h>
#include "utils.h"

/* Login interface */
User *login(UserList *userlist) {
    char *username = malloc(sizeof(char) * 20);
    char *password = malloc(sizeof(char) * 20);
    fprintf(stdout, "username: ");
    fgets(username, 20, stdin);
    username[strlen(username) - 1] = '\0';
    fprintf(stdout, "password: ");
    fgets(password, 20, stdin);
    password[strlen(password) - 1] = '\0';


    User *cur = userlist->list;
    while (cur != NULL) {
        if (strcmp(username, cur->username) == 0) {
            if (strcmp(password, cur->password) == 0) {
                return cur;
            } else {
                printf_red("Invalid username or password!\n");
                return NULL;
            }
        }


        cur = cur->next;
    }
    return NULL;
}
