//
// Created by onerain233 on 2022/3/3.
//

#include "library.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"


void read_books(char *filename, BookList *booklist) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Book *dummyhead = createBook(999, " ", " ", 0, 0);
    booklist->list = dummyhead;
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

        insertBook(booklist, id, authors, title, year, copies);
//        printf("%d, %s, %s, %d, %d\n\n", id, authors, title, year, copies);
        cnt++;
//        booklist -> list = dummyhead;
        booklist -> length = cnt;

    }
    fclose(fp);

//    booklist->list = dummyhead;
//    booklist->length = cnt;
//    printf("%d books read from file %s\n\n", cnt, filename);
//    listBook(booklist);
}