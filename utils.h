//
// Created by onerain233 on 2022/3/2.
//

#ifndef PROJECT1_UTILS_H
#define PROJECT1_UTILS_H

#include "datastructure.h"

int optionChoice( void );
void removeNewLine(char* string);
void formatUser(User *user, char *result);
void listBook(BookList *booklist);
void insertBook(Book *dummyhead, int id, char *authors, char *title, int year, int copies);
Book *createBook(int id, char *authors, char *title, int year, int copies);
#endif //PROJECT1_UTILS_H
