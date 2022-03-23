//
// Created by onerain233 on 2022/3/3.
//

#ifndef PROJECT1_USER_H
#define PROJECT1_USER_H

#include "datastructure.h"


void user_info(User *pUser);

void user_book_list(User *pUser);

void user_borrowed_book_list(BookList *booklist, User *pUser);

void user_menu(User *user, BookList *wholebooklist);

void read_borrow_books(FILE *fp, UserList *userlist, BookList *wholebooklist);

void borrow_book(User *user, unsigned int id, BookList *wholeBookList);

void return_book(User *user, unsigned int id, BookList *wholeBookList);

void return_book_interface(BookList *wholetBookList, User *user);

void borrow_book_interface(BookList *wholetBookList, User *user);
#endif //PROJECT1_USER_H
