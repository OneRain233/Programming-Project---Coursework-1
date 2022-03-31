//
// Created by onerain233 on 2022/3/3.
//

#include "user.h"
#include "utils.h"
#include <string.h>
#include <malloc.h>

/* User menu */
void user_menu_hint(){
    printf("Welcome to user menu!\n");
    printf("1. View user info\n");
    printf("2. View user's book list\n");
    printf("3. Borrow a book\n");
    printf("4. Return a book\n");
    printf("0. Exit\n");
}

/* Run user menu */
void user_menu(User *user, BookList *wholebooklist) {

    user_menu_hint();
    getc(stdin);
    int choice = getOptions();

    while (choice != 0) {
        switch (choice) {
            case 1:
                user_info(user);
                break;
            case 2:
                user_borrowed_book_list(wholebooklist, user);
                break;
            case 3:
                borrow_book_interface(wholebooklist, user);
                break;
            case 4:
                return_book_interface(wholebooklist, user);
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
        user_menu_hint();
        choice = getOptions();
        while(choice == -1){
            choice = getOptions();
        }
    }
}

/* List the user borrowed books */
void user_borrowed_book_list(BookList *booklist, User *pUser) {
    if (pUser->borrowNum == 0) {
        printf("You have not borrowed any book!\n");
        return;
    }
    printf("User borrowed book list: ");
    for (int i = 0; i < pUser->borrowNum; i++) {
        unsigned int bookId = pUser->bookList[i];
        if (bookId == 99999) {
            continue;
        }
        Book *pBook = findBookByID(booklist, bookId);
        printf("%d. %s\n", bookId, pBook->title);

    }
}

/* List the user info */
void user_info(User *pUser) {
    printf("ID: %d\n", pUser->id);
    printf("Name: %s\n", pUser->username);
    printf("Max borrow num: %d\n", pUser->borrowMax);
    printf("Borrowed num: %d\n", pUser->borrowNum);
    printf("\n");
}

/* Find user by username */
User *findUserByUsername(UserList *userlist, char *username) {
    User *pUser = userlist->list;
    while (pUser != NULL) {
        if (strcmp(pUser->username, username) == 0) {
            return pUser;
        }
        pUser = pUser->next;
    }
    return NULL;
}

/* Read borrowed books for users */
void read_borrow_books(FILE *fp, UserList *userlist, BookList *wholebooklist) {

    if (fp == NULL) {
        fprintf(stderr,"File open error!\n");
        return;
    }

    char *username = (char *) malloc(sizeof(char) * 20);
    char *password = (char *) malloc(sizeof(char) * 20);
    int borrowNum;
    int maxBorrowNum;

    while (fscanf(fp,
                  "%s\t%s\t%d\t%d\n",
                  username,
                  password,
                  &borrowNum,
                  &maxBorrowNum) != EOF) {
        for (int i = 0; i < borrowNum; i++) {
            unsigned int bookId;

            fscanf(fp, "%d\n", &bookId);
            User *pUser = findUserByUsername(userlist, username);
            if (pUser == NULL) {
                puts("User not found!");
                return;
            }

            pUser->bookList[i] = bookId;
        }
    }

}

/* Borrow book Logic */
void borrow_book(User *user, unsigned int id, BookList *wholeBookList) {
    if (user->borrowNum >= user->borrowMax) {
        printf("You have borrowed the max num of books!\n");
        return;
    }
    for(int i = 0; i < user->borrowNum; i++){
        if(user->bookList[i] == id){
            printf("You have already borrowed this book!\n");
            return;
        }
    }


    user->bookList[user->borrowNum] = id;
    Book *book = findBookByID(wholeBookList, id);
    if(book == NULL){
        printf("Book not found!\n");
        return;
    }
    if(book->copies == 0){
        printf("Book is not available!\n");
        return;
    }
    book->copies--;
    book->borrowed ++;
    user->borrowNum++;
    printf("Borrow success!\n");
}

/* Return book Logic */
void return_book(User *user, unsigned int id, BookList *wholeBookList) {
    if (user->borrowNum == 0) {
        printf("You have not borrowed any book!\n");
        return;
    }

    for (int i = 0; i < user->borrowNum; i++) {
        if (user->bookList[i] == id) {
            user->bookList[i] = 9999;
            user->borrowNum--;
            break;
        }
    }

    for (int i = 0; i < user->borrowNum; i++) {
        if (user->bookList[i] == 9999) {
            for (int j = i; j < user->borrowNum; j++) {
                user->bookList[j] = user->bookList[j + 1];
            }
        }

    }


    Book *book = findBookByID(wholeBookList, id);
    book->copies++;
    book->borrowed --;
    printf("Return success!\n");
}

/* Borrow book interface */
void borrow_book_interface(BookList *wholetBookList, User *user) {
    listBook(wholetBookList);
    printf("Please input the book id: ");
    unsigned int id = getOptions();
    if(id == -1){
        printf("Please input a valid id!\n");
        return;
    }
    borrow_book(user, id, wholetBookList);

}

/* Return Book interface */
void return_book_interface(BookList *wholetBookList, User *user) {
    user_borrowed_book_list(wholetBookList, user);
    printf("Please input the book id:");
    unsigned int id = getOptions();
    if(id == -1){
        printf("Please input a valid id!\n");
        return;
    }
    return_book(user, id, wholetBookList);
}