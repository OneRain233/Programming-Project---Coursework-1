//
// Created by onerain233 on 2022/3/16.
//

#ifndef PROJECT1_ADMIN_H
#define PROJECT1_ADMIN_H

#include "book_management.h"
#include "datastructure.h"
void admin_menu_hint();
void delete_book_interface(BookList *list);
void admin_menu(BookList *booklist);
void add_book_interface(BookList *list);

void auth(BookList *booklist, UserList *userlist);
#endif //PROJECT1_ADMIN_H
