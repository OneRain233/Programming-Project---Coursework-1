//
// Created by onerain233 on 2022/3/2.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* listBook()
 * --------------
 * booklist: the linked list of book list
 *
 * return: No return
 */
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

/* createBook()
 * --------------
 * create a book
 *
 * id: book id
 * authors: book authors
 * title: book title
 * year: the publication year
 * copies: how many copies
 * borrowed: how many users have borrowed
 *
 * return: Book
 */
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

/* insertBookByPointer()
 * -------------------------
 * Insert a book by a point to the linked list
 *
 * booklist: the list should be inserted into
 * book: the inserted book
 *
 * return: No return
 */
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


/* findBookByID()
 * -----------------
 * Find book by ID
 *
 * booklist: the linkded list of book
 * id: the book id
 *
 * return: Book
 */
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

/* store_user()
 * ----------------
 * store users to file
 *
 * fp: the file pointer
 * userList: the userList
 *
 * return: No return
 */
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

/* isNum()
 * -----------------
 * Check a string if it is a number
 *
 * string: the string will be checked
 *
 * return: 1 or 0
*/
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

/* getOptions()
 * --------------
 * Get user input options
 *
 * return: int
*/
int getOptions() {
    int option;
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

/* print_red()
 * --------------
 * print in red color
 *
 * return: No return
 *
 */
void printf_red(const char *string) {
    fprintf(stdout,"\033[0;31m%s\033[0m", string);
}

/* print_green()
 * --------------
 * print in green color
 *
 * return: No return
 */
void printf_green(const char *string) {
    fprintf(stdout,"\033[0;32m%s\033[0m", string);
}

/* getLastID()
 * --------------
 * Get the last id of bookList
 *
 * bookList: the bookList
 *
 * return: unsigned int
 */
unsigned int getLastID(BookList *booklist) {
    Book *cur = booklist->list->next;
    unsigned int id = 0;
    while (cur != NULL) {
        id = cur->id;
        cur = cur->next;
    }
    return id;
}

/* isExist()
 * -----------------
 * Check a book is existed
 *
 * pList: the book list
 * title: the title
 * authors: the authors of books
 * year: the publication year
 *
 * return Book
*/
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
