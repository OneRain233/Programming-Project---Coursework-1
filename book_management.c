//
// Created by onerain233 on 2022/3/6.
//
#include "book_management.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* find_book_by_title()
 * -------------------------
 * Find book by title
 *
 * title: book title
 * bookList: the bookList
 *
 * return: BookList
*/
BookList find_book_by_title(const char *title, BookList *booklist) {
    BookList res;
    res.length = 0;
    Book *dummyhead = createBook(99999999, " ", " ", 0, 10, 0);

    res.list = dummyhead;
    Book *cur = booklist->list;
    while(cur != NULL){
        if(strcmp(cur->title, title) == 0){
            Book *new_book = (Book *) malloc(sizeof(Book));
            memcpy(new_book, cur, sizeof(Book));
            insertBookByPointer(&res, new_book);
            res.length++;
        }
        cur = cur->next;
    }
    return res;
}

/* find_book_by_author()
 * -------------------------
 * Find book by authors
 *
 * authors: book authors
 * bookList: the bookList
 *
 * return: BookList
*/
BookList find_book_by_author(const char *author, BookList *booklist) {
    BookList res;
    res.length = 0;
    Book *dummyhead = createBook(99999999, " ", " ", 0, 10, 0);

    res.list = dummyhead;
    Book *cur = booklist->list;
    while(cur != NULL){
        if(strcmp(cur->authors, author) == 0){
            Book *new_book = (Book *) malloc(sizeof(Book));
            memcpy(new_book, cur, sizeof(Book));
            insertBookByPointer(&res, new_book);
            res.length++;
        }
        cur = cur->next;
    }
    return res;
}

/* find_book_by_year()
 * -------------------------
 * Find book by year
 *
 * year: book year
 * bookList: the bookList
 *
 * return: BookList
*/
BookList find_book_by_year(unsigned int year, BookList *booklist) {
    BookList res;
    res.length = 0;
    Book *dummyhead = createBook(99999999, " ", " ", 0, 10, 0);

    res.list = dummyhead;
    Book *cur = booklist->list;
    while (cur != NULL) {
        if (cur->year == year) {
            Book *new_book = (Book *) malloc(sizeof(Book));
            memcpy(new_book, cur, sizeof(Book));
            insertBookByPointer(&res, new_book);
            res.length++;
        }
        cur = cur->next;
    }
    return res;
}

/* check_format
 * -------------------
 * check the data format
 *
 * str: string
 *
 * return: No return
*/
void check_format(const char *str) {
    if (str == NULL) {
        fprintf(stderr, "Error: Book file format error\n");
        exit(1);

    }
}

/* load_books()
 * -------------------------
 * Load books from file
 *
 * file: file pointer
 * list: book list
 *
 * return: 0 if success, -1 if fail
*/
int load_books(FILE *file, BookList* list){
    if(file == NULL ) {
        return -1;
    }
    Book *dummyhead = createBook(99999999, " ", " ", 0, 0,0);
    list->list = dummyhead;
    int cnt = 0;

    char line[1024];
    while (fgets(line, 1024, file) != NULL) {
        char *p = strtok(line, "-");
        unsigned id = atoi(p);

        p = strtok(NULL, "-");
        check_format(p);
        char *authors = (char *) malloc(sizeof(p));
        strcpy(authors, p);

        p = strtok(NULL, "-");
        check_format(p);
        char *title = (char *) malloc(sizeof(p));
        strcpy(title, p);

        p = strtok(NULL, "-");
        check_format(p);
        unsigned int year = atoi(p);

        p = strtok(NULL, "-");
        check_format(p);
        unsigned int copies = atoi(p);

        p = strtok(NULL, "-");
        check_format(p);
        int borrowed = atoi(p);
        Book *newbook = createBook(id, authors, title, year, copies,borrowed);
        insertBookByPointer(list, newbook);
        cnt++;
        list -> length = cnt;

    }
    return 0;
}

/* store_books()
 * -------------------------
 * store books to file
 *
 * file: file pointer
 * list: book list
 *
 * return: 0 if success, -1 if fail
*/
int store_books(FILE *file, BookList *list){
    if(file == NULL || list == NULL) {
        puts("file or list is NULL");
        return -1;
    }
    Book *dummyhead = list -> list;
    Book *cur = dummyhead -> next;

    while(cur != NULL) {
        fprintf(file, "%d-%s-%s-%d-%d-%d\n",
                cur->id, cur->authors, cur->title, cur->year, cur->copies, cur->borrowed);
        cur = cur->next;
    }
    return 0;
}

/* add_book()
 * -------------------------
 * add books to list
 *
 * list: book list
 * book: book
 *
 * return: 0 if success, -1 if fail
*/
int add_book(Book *book, BookList *list){
    if(list == NULL) {
        return -1;
    }
    Book *newbook = (Book *) malloc(sizeof(Book));
    memccpy(newbook, book, sizeof(Book), sizeof(Book));
    insertBookByPointer(list, newbook);
    return 0;
}

/* remove_book()
 * -------------------------
 * remove books from list
 *
 * list: book list
 * book: book
 *
 * return: 0 if success, -1 if fail
*/
int remove_book(Book *book, BookList *list) {
    if (list == NULL) {
        return -1;
    }
    Book *cur = list->list;
    Book *prev = cur;
    while (cur != NULL) {
        if (cur->id == book->id) {
            prev->next = cur->next;
            free(cur);
            return 0;
        }
        prev = cur;
        cur = cur->next;
    }
    return -1;

}

void delete_book(unsigned int id, BookList *list) {
    Book *cur = list->list;
    Book *prev = cur;
    while (cur != NULL) {
        if (cur->id == id) {
            prev->next = cur->next;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}