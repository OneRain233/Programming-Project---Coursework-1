//
// Created by onerain233 on 2022/3/3.
//

#include "library.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

Book *createBook(int id, char *authors, char *title, int year, int copies) {
    Book *book = (Book *) malloc(sizeof(Book));
    book->id = id;
    book->authors = authors;
    book->title = title;
    book->year = year;
    book->copies = copies;
    return book;
}

void insertBook(Book *dummyhead, int id, char *authors, char *title, int year, int copies) {
    Book *newbook = createBook(id, authors, title, year, copies);
    newbook->next = NULL;
    if (dummyhead->next == NULL) {
        dummyhead->next = newbook;
    } else {
        Book *cur = dummyhead;
        while (cur->next != NULL) {

            cur = cur->next;
        }
        cur->next = newbook;
    }

}


void read_books(char *filename, BookList *booklist) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Book *dummyhead = createBook(999, " ", " ", 0, 0);

    int cnt = 0;

    char line[1024];
    while (fgets(line, 1024, fp) != NULL) {
        Book *newbook;
        newbook = (Book *) malloc(sizeof(Book));
        char *p = strtok(line, "-");
        unsigned id = atoi(p);

        p = strtok(NULL, "-");
        char *authors = malloc(sizeof(p));
        strcpy(authors, p);

        p = strtok(NULL, "-");
        char *title = malloc(sizeof(p));
        strcpy(title, p);

        p = strtok(NULL, "-");
        unsigned int year = atoi(p);

        p = strtok(NULL, "-");
        unsigned int copies = atoi(p);

        insertBook(dummyhead, id, authors, title, year, copies);
//        printf("%d, %s, %s, %d, %d\n\n", id, authors, title, year, copies);
        cnt++;
    }
    booklist->list = dummyhead;
    booklist->length = cnt;
    listBook(booklist);
}