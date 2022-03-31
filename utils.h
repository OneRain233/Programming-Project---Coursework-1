//
// Created by onerain233 on 2022/3/2.
//

#ifndef PROJECT1_UTILS_H
#define PROJECT1_UTILS_H

#include "datastructure.h"

int optionChoice(void);

void listBook(BookList *booklist);

Book *createBook(unsigned int id, char *authors, char *title, unsigned int year, unsigned int copies, int borrowed);

void deleteBook(BookList *booklist, unsigned int id);

void insertBookByPointer(BookList *booklist, Book *book);

Book *findBookByID(BookList *booklist, unsigned int id);

BookList *createBooklist(void);

void store_user(FILE *fp, UserList *userList);

int getOptions();

void printf_red(const char *string);

void printf_green(const char *string);

void printf_yellow(const char *string);

void printf_blue(const char *string);

int isNum(const char *string);

void stdinClear();

Book *isExist(BookList *pList, char *title, char *author, unsigned int year);
unsigned int getLastID(BookList *booklist);
#endif //PROJECT1_UTILS_H
