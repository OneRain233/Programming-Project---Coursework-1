//
// Created by onerain233 on 2022/3/1.
//

#ifndef PROJECT1_DATASTRUCTURE_H
#define PROJECT1_DATASTRUCTURE_H

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
    User *user[100];
    int userNum;
//    struct _UserList *next;
} UserList;

//UserList *userList;


#endif //PROJECT1_DATASTRUCTURE_H