//
// Created by onerain233 on 2022/3/16.
//

#ifndef PROJECT1_ADMIN_H
#define PROJECT1_ADMIN_H

#include "book_management.h"
#include "datastructure.h"

void admin_menu_hint();

void delete_book_interface(char *book_file, BookList *list);

void admin_menu(UserList *userlist, BookList *booklist, char *book_file);

void add_book_interface(char *book_file, BookList *list);

void auth(UserList *userlist, BookList *booklist, char *book_file);

void show_users_booklist(UserList *userlist);

#endif //PROJECT1_ADMIN_H
