//
// Created by onerain233 on 2022/3/2.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int optionChoice(void) {
//    fflush(stdin);
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
    if(booklist->list == NULL) return;
    Book *cur = booklist->list->next;
    printf("%s\t%s\t%s\t%s\t%s\n", "ID", "Authors", "Title", "Year", "Copies");
    while (cur != NULL) {

        printf("%d\t%s\t%s\t%d\t%d\n", cur->id, cur->authors, cur->title, cur->year, cur->copies);
        cur = cur->next;

    }
}


void insertBook(BookList *booklist, int id, char *authors, char *title, int year, int copies) {
    Book *dummyhead = booklist->list;
    Book *newbook = createBook(id, authors, title, year, copies);
//    newbook->next = NULL;
    if (dummyhead->next == NULL) {
        dummyhead->next = newbook;
    } else {
        Book *cur = dummyhead;
        while (cur->next != NULL) {
//            puts(cur->authors);
            cur = cur->next;
        }
        cur->next = newbook;
    }

}

Book *createBook(unsigned int id, char *authors, char *title, unsigned int year, unsigned int copies) {
    Book *book = (Book *) malloc(sizeof(Book));
    book->id = id;
    book->authors = authors;
    book->title = title;
    book->year = year;
    book->copies = copies;
    book->next = NULL;
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
    if(booklist == NULL) {
        booklist->list = createBooklist();
    }
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
        book->next = NULL;
    }
    booklist->length++;


}

Book *findBookByID(BookList *booklist, unsigned int id){
//    puts("findBookByID");
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
    Book *dummyhead = createBook(999, "", "", 0, 0);
    booklist->list = dummyhead;
    booklist->length = 0;
    return booklist;
}

void store_user(FILE *fp, UserList *userList){
    User *cur = userList->list;
    while( cur != NULL){
        fprintf(fp, "%s\t%s\t%d\t%d\n", cur->username, cur->password, cur->borrowNum, cur->borrowMax);
        for(int i = 0; i < cur->borrowNum; i++){
            fprintf(fp, "%d\n", cur->bookList[i]);
        }
        cur = cur->next;

    }
}