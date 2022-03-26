//
// Created by onerain233 on 2022/3/3.
//

#include "user.h"
#include "utils.h"
#include <string.h>
#include <malloc.h>


void user_menu_hint(){
//    printf("====================================================\n");
    puts("Welcome to user menu!");
    puts("1. View user info");
    puts("2. View user's book list");
    puts("3. Borrow a book");
    puts("4. Return a book");
    puts("0. Exit");
//    printf("====================================================\n");
}


void user_menu(User *user, BookList *wholebooklist) {

    user_menu_hint();
    getc(stdin);
    int choice = getOptions();

    while (choice != 0) {
        switch (choice) {
            case 1:
                user_info(user);
//                choice = optionChoice();
                break;
            case 2:
//            user_book_list(user);
                user_borrowed_book_list(wholebooklist, user);
//                choice = optionChoice();
                break;
            case 3:
                borrow_book_interface(wholebooklist, user);
//                choice = optionChoice();
                break;
            case 4:
                return_book_interface(wholebooklist, user);
//                choice = optionChoice();
                break;
            default:
                puts("Invalid choice!");
                break;
        }
        user_menu_hint();
        choice = getOptions();
    }
//    getc(stdin);
}

void user_borrowed_book_list(BookList *booklist, User *pUser) {
//    printf("====================================================\n");
    if (pUser->borrowNum == 0) {
        puts("You have not borrowed any book!\n");
        return;
    }
    puts("User borrowed book list:");
    for (int i = 0; i < pUser->borrowNum; i++) {
        unsigned int bookId = pUser->bookList[i];
        if (bookId == 99999) {
            continue;
        }
        Book *pBook = findBookByID(booklist, bookId);
        printf("%d. %s\n", bookId, pBook->title);

    }

//    printf("====================================================\n");
}

void user_info(User *pUser) {
//    printf("====================================================\n");
    printf("ID: %d\n", pUser->id);
    printf("Name: %s\n", pUser->username);
    printf("Max borrow num: %d\n", pUser->borrowMax);
    printf("Borrowed num: %d\n", pUser->borrowNum);
    printf("\n");
//    printf("====================================================\n");
}

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

void read_borrow_books(FILE *fp, UserList *userlist, BookList *wholebooklist) {

    if (fp == NULL) {
        puts("File open error!");
        return;
    }

    char *username = (char *) malloc(sizeof(char) * 20);
    char *password = (char *) malloc(sizeof(char) * 20);
    int borrowNum;
    int maxBorrowNum;

    while (fscanf(fp, "%s\t%s\t%d\t%d\n", username, password, &borrowNum, &maxBorrowNum) != EOF) {
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


void borrow_book(User *user, unsigned int id, BookList *wholeBookList) {
//    printf("====================================================\n");
    if (user->borrowNum >= user->borrowMax) {
        puts("You have borrowed the max num of books!");
        return;
    }
    for(int i = 0; i < user->borrowNum; i++){
        if(user->bookList[i] == id){
            puts("You have already borrowed this book!");
            return;
        }
    }


    user->bookList[user->borrowNum] = id;
    Book *book = findBookByID(wholeBookList, id);
    if(book == NULL){
        puts("Book not found!");
        return;
    }
    if(book->copies == 0){
        puts("Book is not available!");
        return;
    }
    book->copies--;
    user->borrowNum++;
    puts("Borrow success!");
//    printf("====================================================\n");
}

void return_book(User *user, unsigned int id, BookList *wholeBookList) {
//    printf("====================================================\n");
    if (user->borrowNum == 0) {
        puts("You have not borrowed any book!");
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

}

void borrow_book_interface(BookList *wholetBookList, User *user) {
//    printf("====================================================\n");
    listBook(wholetBookList);
    puts("Please input the book id:");
    unsigned int id = getOptions();
    printf("%d\n", id);
    if(id == -1){
        printf("Please input a valid id!\n");
        return;
    }
    borrow_book(user, id, wholetBookList);
//    printf("====================================================\n");

}

void return_book_interface(BookList *wholetBookList, User *user) {
//    printf("====================================================\n");
    user_borrowed_book_list(wholetBookList, user);
    puts("Please input the book id:");
    unsigned int id = getOptions();
    if(id == -1){
        printf("Please input a valid id!\n");
        return;
    }
    return_book(user, id, wholetBookList);
//    printf("====================================================\n");
}