//
// Created by onerain233 on 2022/3/1.
//

#ifndef PROJECT1_DATASTRUCTURE_H
#define PROJECT1_DATASTRUCTURE_H

#include <stdio.h>
#include "book_management.h"

typedef struct _User {
    unsigned int id;
    char *username;
    char *password;
//    unsigned int bookList[10];
    BookList *bookList;
    int borrowNum;
    int borrowMax;
    struct _User *next;
} User;

typedef struct _UserList {
    User *list;
    int userNum;
//    struct _UserList *next;
} UserList;

//UserList *userList;


#endif //PROJECT1_DATASTRUCTURE_H
