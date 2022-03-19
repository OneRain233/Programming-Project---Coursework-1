//
// Created by onerain233 on 2022/3/16.
//

#ifndef PROJECT1_ADMIN_H
#define PROJECT1_ADMIN_H

#include "book_management.h"
#include "datastructure.h"

void add_books();
void add_book_interface(BookList *list);
void admin_menu(BookList *booklist, UserList *userlist);
void auth(BookList *booklist, UserList *userlist);
#endif //PROJECT1_ADMIN_H
