//
// Created by onerain233 on 2022/3/3.
//

#include "user.h"
#include "utils.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

/* user_menu_hint()
 * --------------------
 * print the menu
 *
 * return: No return
*/
void user_menu_hint(){
    printf_green("\n====Welcome to user menu!====\n");
    fprintf(stdout, "1. View user info\n");
    fprintf(stdout, "2. View user's book list\n");
    fprintf(stdout, "3. Borrow a book\n");
    fprintf(stdout, "4. Return a book\n");
    fprintf(stdout, "0. Exit\n");
    fprintf(stdout, "Please input your choice: ");
}

/* user_menu
 * --------------
 * run the user menu
 *
 * return: No return
*/
void user_menu(User *user, BookList *wholebooklist) {

    user_menu_hint();
    int choice = getOptions();

    while (choice != 0) {
        switch (choice) {
            case 1:
                user_info(user);
                break;
            case 2:
                user_borrowed_book_list(user);
                break;
            case 3:
                borrow_book_interface(wholebooklist, user);
                break;
            case 4:
                return_book_interface(wholebooklist, user);
                break;
            default:
                fprintf(stderr, "Invalid choice!\n");
                break;
        }
        user_menu_hint();
        choice = getOptions();
        while(choice == -1){
            printf_red("Invalid choice!\n");
            choice = getOptions();
        }
    }
}

/* user_borrowed_book_list()
 * --------------------------------
 * List the user borrowed books
 * pUser: User
 *
 * return: No return
 */
void user_borrowed_book_list(User *pUser) {
    printf_green("\n====User's borrowed books====\n");
    if (pUser->borrowNum == 0) {
        fprintf(stderr, "You have not borrowed any book!\n");
        return;
    }
    fprintf(stdout, "User borrowed book list: \n");
    listBook(pUser->bookList);
}

/* check_borrowed()
 * --------------------
 * booklist: Book List
 * id: the book id
 *
 * return: 1 if borrowed 0 not
*/
int check_borrowed(BookList *booklist, unsigned int id) {
    Book *book = booklist->list;
    while (book != NULL) {
        if (book->id == id) {
            return 1;
        }
        book = book->next;
    }
    return 0;
}

/* user_info()
 * -------------
 * List the user info
 * pUser: User
 *
 * return: No return
 *
 * */
void user_info(User *pUser) {
    printf_green("\n====User info====\n");
    fprintf(stdout, "ID: %d\n", pUser->id);
    fprintf(stdout, "Name: %s\n", pUser->username);
    fprintf(stdout, "Max borrow num: %d\n", pUser->borrowMax);
    fprintf(stdout, "Borrowed num: %d\n", pUser->borrowNum);
}

/* findUserByUsername()
 * --------------------------
 * Find user by username
 * userlist: the user list
 * username: the username should be found
 *
 * return: User
 */
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

/* read_borrow_books()
 * ---------------------
 * Read borrowed books for users
 *
 * fp: file pointer
 * userlist: the user list
 * wholebooklist: the book list
 *
 * return: No return
 *
 */
void read_borrow_books(FILE *fp, UserList *userlist, BookList *wholebooklist) {

    if (fp == NULL) {
        fprintf(stderr, "File open error!\n");
        exit(1);
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
        User *pUser = findUserByUsername(userlist, username);
        pUser->bookList->list = createBook(99999999, " ", " ", 0, 10, 0);
        for (int i = 0; i < borrowNum; i++) {
            unsigned int bookId;

            fscanf(fp, "%d\n", &bookId);


            Book *pBook = findBookByID(wholebooklist, bookId);
            if (pBook == NULL) {
                fprintf(stderr, "Book not found!");
                return;
            }
            Book *newBook = (Book *) malloc(sizeof(Book));
            newBook->id = pBook->id;
            newBook->title = pBook->title;
            newBook->authors = pBook->authors;
            newBook->year = pBook->year;
            newBook->copies = pBook->copies;
            newBook->borrowed = pBook->borrowed;
            newBook->next = NULL;

            pUser->borrowNum = borrowNum;
            pUser->borrowMax = maxBorrowNum;
            insertBookByPointer(pUser->bookList, newBook);
        }
    }

}

/* borrow_book
 * --------------
 * borrow books
 *
 * user: User
 * id: the book id
 * wholeBookList: the book list
 *
 * return: No return
 * */
void borrow_book(User *user, unsigned int id, BookList *wholeBookList) {
    if (user->borrowNum >= user->borrowMax) {
        printf_red("You have borrowed the max num of books!\n");
        return;
    }

    BookList *dummyHead = user->bookList;

    Book *book = findBookByID(wholeBookList, id);
    if (book == NULL) {
        printf_red("Book not found!\n");
        return;
    }
    if (book->copies == 0) {
        printf_red("Book is not available!\n");
        return;
    }
    if (check_borrowed(dummyHead, id)) {
        printf_red("You have borrowed this book!\n");
        return;
    }
    Book *newBook = (Book *) malloc(sizeof(Book));
    newBook->id = book->id;
    newBook->title = book->title;
    newBook->authors = book->authors;
    newBook->year = book->year;
    newBook->copies = 1;
    newBook->borrowed = book->borrowed;
    newBook->next = NULL;

    insertBookByPointer1(user->bookList, newBook);

    book->copies--;
    book->borrowed++;
    user->borrowNum++;
    printf_green("Borrow success!\n");
}

/* return_book()
 * --------------
 * return books
 *
 * user: User
 * id: the book id
 * wholeBookList: the book list
 *
 * return: No return
 * */
void return_book(User *user, unsigned int id, BookList *wholeBookList) {
    if (user->borrowNum == 0) {
        printf_red("You have not borrowed any book!\n");
        return;
    }

    BookList *dummyHead = user->bookList;
    Book *delBook = findBookByID(dummyHead, id);
    if (delBook == NULL) {
        printf_red("Book not found!\n");
        return;
    }
    remove_book(delBook, user->bookList);
//    Book *cur = user->bookList->list;
////    Book *prev = user->bookList->list;
//    while (cur ->next!= NULL) {
//        if (cur->next->id == id) {
//            cur->next = cur->next->next;
//            break;
//        }
////        prev = cur;
//        cur = cur->next;
//    }

    Book *book = findBookByID(wholeBookList, id);
    book->copies++;
    book->borrowed--;
    user->borrowNum--;
    printf_green("Return success!\n");
}

/* borrow_book_interface()
 * --------------
 * borrow books interface
 *
 * user: User
 * wholeBookList: the book list
 *
 * return: No return
 * */
void borrow_book_interface(BookList *wholetBookList, User *user) {
    listBook(wholetBookList);
    printf("Please input the book id: ");
    unsigned int id = getOptions();
    if(id == -1){
        printf_red("Please input a valid id!\n");
        return;
    }
    borrow_book(user, id, wholetBookList);

}

/* return_book_interface()
 * --------------
 * return books interface
 *
 * user: User
 * wholeBookList: the book list
 *
 * return: No return
 * */
void return_book_interface(BookList *wholetBookList, User *user) {
    if (user->borrowNum == 0) {
        printf_red("You have not borrowed any book!\n");
        return;
    }
//    printf("%d", user->bookList->length);
//    printf("Please input the book id:");
    listBook(user->bookList);
    unsigned int id = getOptions();
    if(id == -1){
        printf_red("Please input a valid id!\n");
        return;
    }
    return_book(user, id, wholetBookList);
}