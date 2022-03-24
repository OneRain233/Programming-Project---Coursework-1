//
// Created by onerain233 on 2022/3/6.
//
#include "book_management.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

BookList find_book_by_title(const char *title, BookList *booklist) {
    BookList res;
    res.length = 0;
    Book *dummyhead = (Book *) malloc(sizeof(Book));

    res.list = dummyhead;
    Book *cur = booklist->list;
    while(cur != NULL){
        if(strcmp(cur->title, title) == 0){
            Book *new_book = (Book *) malloc(sizeof(Book));
            memccpy(new_book, cur, sizeof(Book), sizeof(Book));
            insertBookByPointer(&res, new_book);
        }
        cur = cur->next;
    }
//    listBook(&res);

    return res;
}

BookList find_book_by_author(const char *author, BookList *booklist) {
    BookList res;
    res.length = 0;
    Book *dummyhead = (Book *) malloc(sizeof(Book));

    res.list = dummyhead;
    Book *cur = booklist->list;
    while(cur != NULL){
        if(strcmp(cur->authors, author) == 0){
            Book *new_book = (Book *) malloc(sizeof(Book));
            memccpy(new_book, cur, sizeof(Book), sizeof(Book));
            insertBookByPointer(&res, new_book);
        }
        cur = cur->next;
    }
//    listBook(&res);

    return res;
}


BookList find_book_by_year(unsigned int year, BookList *booklist) {
    BookList res;
    res.length = 0;
    Book *dummyhead = (Book *) malloc(sizeof(Book));

    res.list = dummyhead;
    Book *cur = booklist->list;
    while(cur != NULL){
        if(cur->year == year){
            Book *new_book = (Book *) malloc(sizeof(Book));
            memccpy(new_book, cur, sizeof(Book), sizeof(Book));
            insertBookByPointer(&res, new_book);
        }
        cur = cur->next;
    }
//    listBook(&res);

    return res;
}


int load_books(FILE *file, BookList* list){
    if(file == NULL ) {
        return -1;
    }
    Book *dummyhead = createBook(99999999, " ", " ", 0, 0);
    list->list = dummyhead;
    int cnt = 0;

    char line[1024];
    while (fgets(line, 1024, file) != NULL) {
//        Book *newbook;
//        newbook = (Book *) malloc(sizeof(Book));
        char *p = strtok(line, "-");
        unsigned id = atoi(p);

        p = strtok(NULL, "-");
        char *authors = (char *) malloc(sizeof(p));
        strcpy(authors, p);

        p = strtok(NULL, "-");
        char *title = (char *) malloc(sizeof(p));
        strcpy(title, p);

        p = strtok(NULL, "-");
        unsigned int year = atoi(p);

        p = strtok(NULL, "-");
        unsigned int copies = atoi(p);

        Book *newbook = createBook(id, authors, title, year, copies);
        insertBookByPointer(list, newbook);
        cnt++;
        list -> length = cnt;

    }
    return 0;
}


int store_books(FILE *file, BookList *list){
    if(file == NULL || list == NULL) {
        puts("file or list is NULL");
        return -1;
    }
    Book *dummyhead = list -> list;
    Book *cur = dummyhead -> next;

    while(cur != NULL) {
        fprintf(file, "%d-%s-%s-%d-%d\n", cur -> id, cur -> authors, cur -> title, cur -> year, cur -> copies);
        cur = cur -> next;
    }
    return 0;
}


int add_book(Book *book, BookList *list){
    if(list == NULL) {
        return -1;
    }
    Book *newbook = (Book *) malloc(sizeof(Book));
    memccpy(newbook, book, sizeof(Book), sizeof(Book));
    insertBookByPointer(list, newbook);
//    list -> length++;
    return 0;
}

int remove_book(Book *book, BookList *list){
    if(list == NULL) {
        return -1;
    }
    Book *dummyhead = list -> list;
    Book *cur = dummyhead -> next;

    while(cur != NULL) {
        if(cur -> id == book->id) {
            deleteBook(list, cur->id);
            return 0;
        }
        cur = cur -> next;
    }
    return -1;
}

