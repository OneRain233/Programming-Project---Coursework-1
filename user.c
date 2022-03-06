//
// Created by onerain233 on 2022/3/3.
//

#include "user.h"
#include "utils.h"
#include <string.h>


void user_menu_hint(){
    puts("Welcome to user menu!");
    puts("1. View user info");
    puts("2. View user's book list");
    puts("3. Borrow a book");
    puts("4. Return a book");
    puts("5. Exit");
}


void user_menu(User *user, BookList *wholebooklist) {

    user_menu_hint();
    int choice = optionChoice();
    while (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
        puts("Please input a choice!");
        choice = optionChoice();
    }
    while (choice != 5) {
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
    if (pUser->borrowNum == 0) {
        puts("You have not borrowed any book!\n");
        return;
    }
    puts("User borrowed book list:");
    listBook(pUser->bookList);

}

void user_info(User *pUser) {
    puts("-----User info-----");
    printf("Name: %s\n", pUser->username);
    printf("Max borrow num: %d\n", pUser->borrowMax);
    printf("Borrowed num: %d\n", pUser->borrowNum);
    printf("\n");
}


void read_borrow_books(User *user) {

    FILE *fp = fopen("borrow.txt", "r");
    if (fp == NULL) {
        puts("File open error!");
        return;
    }

    char line[1024];
    while (fgets(line, 1024, fp) != NULL) {
        char *p = strtok(line, "-");
//        puts(p);
        if (strcmp(p, user->username) == 0) {
//            puts(p);
            p = strtok(NULL, "-");
            int size = (int) *p - '0';
            printf("%d\n", size);
            for (int i = 0; i < size; i++) {
                p = strtok(NULL, "-");
                printf("%s\n", p);
            }
        }
    }

}

void borrow_book(User *user, unsigned int id, BookList *wholeBookList) {
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


    if(user->bookList == NULL){
        user->bookList = createBooklist();
    }

//    book->next = NULL;
    deleteBook(wholeBookList, id);
    insertBookByPointer(user->bookList, book);
    puts("Borrow success!");
}

void return_book(User *user, unsigned int id, BookList *wholeBookList){
    Book *book = findBookByID(user->bookList, id);
    if (book == NULL) {
        puts("Book not found!");
        return;
    }


    deleteBook(user->bookList, id);
    insertBookByPointer(wholeBookList, book);
    user->borrowNum--;
    puts("Return success!");
}

void borrow_book_interface(BookList *wholetBookList, User *user) {
    puts("-----Borrow book interface-----");
    listBook(wholetBookList);
    puts("Please input the book id:");
    unsigned int id = optionChoice();
    borrow_book(user, id, wholetBookList);

}

void return_book_interface(BookList *wholetBookList, User *user) {
    puts("-----Return book interface-----");
    listBook(user->bookList);
    puts("Please input the book id:");
    unsigned int id = optionChoice();
    return_book(user, id, wholetBookList);
}