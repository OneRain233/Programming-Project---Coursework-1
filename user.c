//
// Created by onerain233 on 2022/3/3.
//

#include "user.h"
#include "utils.h"
#include <string.h>
#include <malloc.h>


void user_menu_hint(){
    printf("====================================================\n");
    puts("Welcome to user menu!");
    puts("1. View user info");
    puts("2. View user's book list");
    puts("3. Borrow a book");
    puts("4. Return a book");
    puts("0. Exit");
    printf("====================================================\n");
}


void user_menu(User *user, BookList *wholebooklist) {

    user_menu_hint();
    int choice = optionChoice();
    while (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
        puts("Please input a choice!");
        choice = optionChoice();
    }
    while (choice != 0) {
        switch (choice) {
            case 1:
                user_info(user);
                break;
            case 2:
//            user_book_list(user);
                user_borrowed_book_list(user);
                break;
            case 3:
                borrow_book_interface(wholebooklist, user);
                break;
            case 4:
                return_book_interface(wholebooklist, user);
                break;
            default:
                puts("Invalid choice!");
                break;
        }
        user_menu_hint();
        choice = optionChoice();
    }

}

void user_borrowed_book_list(User *pUser) {
    printf("====================================================\n");
    if (pUser->borrowNum == 0) {
        puts("You have not borrowed any book!\n");
        return;
    }
    puts("User borrowed book list:");
    listBook(pUser->bookList);
    printf("====================================================\n");
}

void user_info(User *pUser) {
    printf("====================================================\n");
    printf("ID: %d\n", pUser->id);
    printf("Name: %s\n", pUser->username);
    printf("Max borrow num: %d\n", pUser->borrowMax);
    printf("Borrowed num: %d\n", pUser->borrowNum);
    printf("\n");
    printf("====================================================\n");
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

    char *username = malloc(sizeof(char) * 20);
    char *password = malloc(sizeof(char) * 20);
    int borrowNum;
    int maxBorrowNum;

    while (fscanf(fp, "%s\t%s\t%d\t%d\n", username, password, &borrowNum, &maxBorrowNum) != EOF) {
        for (int i = 0; i < borrowNum; i++) {
            unsigned int bookId;

            fscanf(fp, "%d\n", &bookId);
            printf("%d\n", bookId);
//            listBook(wholebooklist);
            Book *book = findBookByID(wholebooklist, bookId);
            if (book == NULL) {
                puts("Book not found!");
                continue;
            }

            User *user = findUserByUsername(userlisnzx m                                                         t, username);
            user->bookList = createBooklist();
            insertBook(user->bookList, book->id, book->authors, book->title, book->year, book->copies);
        }
    }

}



void borrow_book(User *user, unsigned int id, BookList *wholeBookList) {
    printf("====================================================\n");
    if (user->borrowNum >= user->borrowMax) {
        puts("You have borrowed the max num of books!");
        return;
    }

    user->borrowNum++;
    Book *book = findBookByID(wholeBookList, id);
    if (book == NULL) {
        puts("Book not found!");
        return;
    }
    if(book->copies == 0){
        puts("This book is not available");
        return;
    }


    if (user->bookList == NULL) {
        user->bookList = createBooklist();
    }

//    book->next = NULL;
//    deleteBook(wholeBookList, id);
    book->copies--;
    Book *borrowed_book = createBook(book->id, book->authors, book->title, book->year, book->copies);

    insertBookByPointer(user->bookList, borrowed_book);
    rec2db(book, user);
    puts("Borrow success!");
    printf("====================================================\n");
}

void return_book(User *user, unsigned int id, BookList *wholeBookList){
    printf("====================================================\n");
    Book *book = findBookByID(user->bookList, id);
    if (book == NULL) {
        puts("Book not found!");
        return;
    }

    deleteBook(user->bookList, id);
//    insertBookByPointer(wholeBookList, book);

    Book *originalBook = findBookByID(wholeBookList, id);
    originalBook->copies++;
    user->borrowNum--;
    delFromDB(id);
    puts("Return success!");
}

void borrow_book_interface(BookList *wholetBookList, User *user) {
    printf("====================================================\n");
    listBook(wholetBookList);
    puts("Please input the book id:");
    unsigned int id = optionChoice();
    borrow_book(user, id, wholetBookList);
    printf("====================================================\n");

}

void return_book_interface(BookList *wholetBookList, User *user) {
    printf("====================================================\n");
    listBook(user->bookList);
    puts("Please input the book id:");
    unsigned int id = optionChoice();
    return_book(user, id, wholetBookList);
    printf("====================================================\n");
}