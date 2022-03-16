//
// Created by onerain233 on 2022/3/16.
//

#include <malloc.h>
#include "admin.h"
#include "utils.h"
#include "library.h"

void save_books(BookList *booklist){
    FILE *fp = fopen("books.txt", "w+");
    if (fp == NULL) {
        printf("Open books.txt failed\n");
        return;
    }
    //0-Author-BookName-1999-2019
    Book *p = booklist->list;
    while (p != NULL) {
        fprintf(fp, "%d-%s-%s-%d-%d\n", p->id, p->authors, p->title, p->year, p->copies);
        p = p->next;
    }
    fclose(fp);
}


void add_books(){
    BookList *booklist = createBooklist();
    read_books("books.txt", booklist);

    char title[100];
    char author[100];
    unsigned int year;
    unsigned int copies;


    printf("Please input the book title：");
    scanf("%s", &title);
    printf("Please input the book author：");
    scanf("%s", &author);
    printf("Please input the year of publication：");
    scanf("%d", &year);
    printf("Please input the copies：");
    scanf("%d", &copies);

    Book *book = createBook(booklist->length,author, title, year, copies);
    book->id = booklist->length;
    booklist->length++;
    insertBookByPointer(booklist, book);
    listBook(booklist);
    save_books(booklist);
}

