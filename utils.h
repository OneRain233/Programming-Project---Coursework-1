//
// Created by onerain233 on 2022/3/2.
//

#ifndef PROJECT1_UTILS_H
#define PROJECT1_UTILS_H

#include "datastructure.h"

int optionChoice(void);

void listBook(BookList *booklist);

Book *createBook(unsigned int id, char *authors, char *title, unsigned int year, unsigned int copies);

void deleteBook(BookList *booklist, unsigned int id);

void insertBookByPointer(BookList *booklist, Book *book);

Book *findBookByID(BookList *booklist, unsigned int id);

BookList *createBooklist(void);

void store_user(FILE *fp, UserList *userList);

#endif //PROJECT1_UTILS_H
