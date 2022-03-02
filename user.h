//
// Created by onerain233 on 2022/3/1.
//

#ifndef PROJECT1_USER_H
#define PROJECT1_USER_H
#include <stdio.h>
#include "book_management.h"

typedef struct _User {
    char *username;
    char *password;
    BookList *bookList;
    int borrowNum;
    int borrowMax;
} User;

typedef struct _UserList {
    User *user;
    struct _UserList *next;
} UserList;

//UserList *userList;


#endif //PROJECT1_USER_H
