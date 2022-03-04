//
// Created by onerain233 on 2022/3/2.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int optionChoice(void) {
    int option = -1;
    char line[80];

    fgets(line, 80, stdin);

    option = (int) atoi(line);

    return option;
}


void removeNewLine(char *string) {

    size_t length = strlen(string);

    if ((length > 0) && (string[length - 1] == '\n')) {
        string[length - 1] = '\0';
    }
}

void listBook(BookList *booklist) {
    Book *cur = booklist->list->next;
    while (cur != NULL) {

        printf("%d %s %s %d %d\n", cur->id, cur->authors, cur->title, cur->year, cur->copies);
        cur = cur->next;

    }
}

void insertBook(BookList *booklist, int id, char *authors, char *title, int year, int copies) {
    Book *dummyhead = booklist->list;
    Book *newbook = createBook(id, authors, title, year, copies);
    newbook->next = NULL;
    if (dummyhead->next == NULL) {
        dummyhead->next = newbook;
    } else {
        Book *cur = dummyhead;
        while (cur->next != NULL) {
            puts(cur->authors);
            cur = cur->next;
        }
        cur->next = newbook;
    }

}

Book *createBook(int id, char *authors, char *title, int year, int copies) {
    Book *book = (Book *) malloc(sizeof(Book));
    book->id = id;
    book->authors = authors;
    book->title = title;
    book->year = year;
    book->copies = copies;
    return book;
}

void deleteBook(BookList *booklist, unsigned int id) {
    Book *cur = booklist->list->next;
    Book *prev = booklist->list;
    while (cur != NULL) {
        if (cur->id == id) {
            prev->next = cur->next;
//            free(cur);
            break;
        }
        prev = cur;
        cur = cur->next;
    }
}

void insertBookByPointer(BookList *booklist, Book *book) {
    Book *dummyhead = booklist->list;
    book->next = NULL;
    if (dummyhead->next == NULL) {
        dummyhead->next = book;
    } else {
        Book *cur = dummyhead;
        while (cur->next != NULL) {

            cur = cur->next;
        }
        cur->next = book;
    }

}

Book *findBookByID(BookList *booklist, unsigned int id){
    puts("findBookByID");
    Book *dummyhead = booklist -> list;
//    Book *cur = dummyhead -> next;
    Book *cur = dummyhead;
    while (cur != NULL){
//        puts("finding");
//        printf("%d", cur -> id);
        if (cur -> id == id){
            return cur;
        }
        cur = cur -> next;
    }
    return NULL;
}


BookList *createBooklist(void) {
    BookList *booklist = (BookList *) malloc(sizeof(BookList));
    booklist->list = (Book *) malloc(sizeof(Book));
    Book *dummyhead = createBook(0, "", "", 0, 0);
    booklist->list = dummyhead;
    return booklist;
}