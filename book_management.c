//
// Created by onerain233 on 2022/3/6.
//
#include "book_management.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "library.h"

BookList find_book_by_title(const char *title) {
    BookList *book_list = malloc(sizeof(BookList));
    read_books("books.txt", book_list);
    BookList *result = createBooklist();

    Book *dummyhead = book_list -> list;
    Book *cur = dummyhead -> next;

    while(cur != NULL) {
        if(strcmp(cur -> title, title) == 0) {
            Book *new_book = malloc(sizeof(Book));
            memccpy(new_book, cur, sizeof(Book), sizeof(Book));

            insertBookByPointer(result, new_book);
        }
        cur = cur -> next;
    }

    return *result;
}

BookList find_book_by_author(const char *author) {
    BookList *book_list = malloc(sizeof(BookList));
    read_books("books.txt", book_list);
    BookList *result = createBooklist();

    Book *dummyhead = book_list -> list;
    Book *cur = dummyhead -> next;

    while(cur != NULL) {
        if(strcmp(cur -> authors, author) == 0) {
            Book *new_book = malloc(sizeof(Book));
            memccpy(new_book, cur, sizeof(Book), sizeof(Book));

            insertBookByPointer(result, new_book);
        }
        cur = cur -> next;
    }

    return *result;
}


BookList find_book_by_year(unsigned int year) {
    BookList *book_list = malloc(sizeof(BookList));
    read_books("books.txt", book_list);
    BookList *result = createBooklist();

    Book *dummyhead = book_list -> list;
    Book *cur = dummyhead -> next;

    while(cur != NULL) {
        if(cur -> year == year) {
            Book *new_book = malloc(sizeof(Book));
            memccpy(new_book, cur, sizeof(Book), sizeof(Book));

            insertBookByPointer(result, new_book);
        }
        cur = cur -> next;
    }

    return *result;
}