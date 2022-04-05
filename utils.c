//
// Created by onerain233 on 2022/3/2.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* List books from the linked list */
void listBook(BookList *booklist) {
    if(booklist->list == NULL) return;
    Book *cur = booklist->list;
    printf("%s\t%s\t%s\t%s\t%s\n", "ID", "Authors", "Title", "Year", "Copies");
    while (cur != NULL) {
        if(cur->id == 99999999) {
            cur = cur->next;
            continue;
        }
        printf("%d\t%s\t%s\t%d\t%d\n", cur->id, cur->authors, cur->title, cur->year, cur->copies);
        cur = cur->next;

    }
}

/* Create a book */
Book *createBook(unsigned int id, char *authors, char *title, unsigned int year, unsigned int copies, int borrowed) {
    Book *book = (Book *) malloc(sizeof(Book));
    book->id = id;
    book->authors = authors;
    book->title = title;
    book->year = year;
    book->copies = copies;
    book->next = NULL;
    book->borrowed = borrowed;
    return book;
}

/* Insert a book by a point to the linked list */
void insertBookByPointer(BookList *booklist, Book *book) {
    if (booklist->list == NULL) {
        booklist->list = book;
        return;
    }
    Book *cur = booklist->list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = book;
}


/* Find book by id */
Book *findBookByID(BookList *booklist, unsigned int id){
    Book *dummyhead = booklist -> list;
    Book *cur = dummyhead;
    while (cur != NULL){
        if (cur -> id == id){
            return cur;
        }
        cur = cur -> next;
    }
    return NULL;
}

/* Store users to file */
void store_user(FILE *fp, UserList *userList){
    User *cur = userList->list;
    while (cur != NULL) {
        fprintf(fp, "%s\t%s\t%d\t%d\n", cur->username, cur->password, cur->borrowNum, cur->borrowMax);
        BookList *bookList = cur->bookList;
        Book *book = bookList->list;
        while (book != NULL) {
            fprintf(fp, "%d\n", book->id);
            book = book->next;
        }

        cur = cur->next;

    }
}

/* Check a string if it is a number */
int isNum(const char *string) {
    int i = 0;
    while (string[i] != '\0') {
        if (string[i] < '0' || string[i] > '9') {
            return 0;
        }
        i++;
    }
    return 1;
}

/* Get user input options */
int getOptions() {
    int option = -1;
    char line[80];
    fflush(stdin);
    rewind(stdin);
    fgets(line, 80, stdin);
    line[strlen(line) - 1] = '\0';
    if(line[0] == '\n' || line[0] == '\0') return -1;
    if(isNum(line)) {
        option = (int) atoi(line);
    }
    else{

        option = -1;
    }

    return option;
}

/* Print in red */
void printf_red(const char *string) {
    printf("\033[0;31m%s\033[0m", string);
}

/* Print in green */
void printf_green(const char *string) {
    printf("\033[0;32m%s\033[0m", string);
}

/* Get the last ID of the booklist */
unsigned int getLastID(BookList *booklist) {
    Book *cur = booklist->list->next;
    unsigned int id = 0;
    while (cur != NULL) {
        id = cur->id;
        cur = cur->next;
    }
    return id;
}

/* Check a book is existed */
Book *isExist(BookList *pList, char *title, char *author, unsigned int year) {
    Book *cur = pList->list;
    while (cur != NULL) {
        if (strcmp(cur->title, title) == 0
            && strcmp(cur->authors, author) == 0
            && cur->year == year) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;

}
