//
// Created by onerain233 on 2022/3/3.
//

#ifndef PROJECT1_USER_H
#define PROJECT1_USER_H

#include "datastructure.h"


void user_info(User *pUser);

void user_book_list(User *pUser);

void user_borrowed_book_list(User *pUser);

void user_menu(User *user);
void read_borrow_books(User *user);

void borrow_book(User *user, unsigned int id, BookList *wholeBookList);

void return_book(User *user, unsigned int id, BookList *wholeBookList);
#endif //PROJECT1_USER_H
