//
// Created by onerain233 on 2022/3/1.
//
#include "book_management.h"
#include "datastructure.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>

/* check_exist()
 * --------------
 * Check if the username is existed
 *
 * userlist: User list
 * username: the username of user
 *
 * return: 1 if existed, 0 if not
 */
int check_exist(UserList *userlist, char *username) {
    User *cur = userlist->list;
    if (cur == NULL) {
        return 0;
    } else {
        while(cur != NULL) {
            if(strcmp(cur->username, username) == 0) {
                return 1;
            }
            cur = cur->next;
        }
    }
    return 0;
}

/* createUser()
 * ----------------
 * create a user
 *
 * id: user id
 * username: the username
 * password: the password
 * borrowNum: the borrowNum
 * borrowMax: max number of borrowed books
 *
 * return: User
 *
*/
User *createUser(unsigned int id, char *username, char *password, int borrowNum, int borrowMax) {
    User *new_user = (User *) malloc(sizeof(User));
    new_user->username = username;
    new_user->password = password;
    new_user->borrowNum = borrowNum;
    new_user->borrowMax = borrowMax;
    new_user->id = id;
    new_user->next = NULL;;
    new_user->bookList = (BookList *) malloc(sizeof(BookList));
    new_user->bookList->list = createBook(99999999, " ", " ", 0, 10, 0);
    new_user->bookList->length = 0;
    return new_user;

}


/* insertUser()
 * ----------------
 * insert a user
 *
 * userlist: UserList
 * id: user id
 * username: the username
 * password: the password
 * borrowNum: the borrowNum
 * borrowMax: max number of borrowed books
 *
 * return: User
 *
*/
User *insertUser(UserList *userlist, unsigned int id, char *username, char *password, int borrowNum, int borrowMax) {
    User *user = createUser(id, username, password, borrowNum, borrowMax);
    User *cur = userlist->list;
    if (cur == NULL) {
        userlist->list = user;
        return user;
    }
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = user;
    return user;
}

/* read_user()
 * ----------------
 * read users from file
 *
 * user_file: filename
 * userlist: the user list
 *
 * return: No return
 *
*/
void read_user(char *user_file, UserList *userlist) {
    FILE *fp;
    fp = fopen(user_file, "r");
    if (fp == NULL) {
        fprintf(stderr, "Open User file error！\n");
        exit(1);
    }
    char *username = (char *) malloc(sizeof(char) * 20);
    char *password = (char *) malloc(sizeof(char) * 20);
    int borrowNum = -1;
    int maxBorrowNum = -1;
    int user_cnt = 0;

    while (fscanf(fp, "%s\t%s\t%d\t%d\n", username, password, &borrowNum, &maxBorrowNum) != EOF) {
        if (borrowNum == -1 || maxBorrowNum == -1) {
            fprintf(stderr, "Error: User file format error!\n");
            exit(1);
        }
        char *buf = (char *) malloc(sizeof(char) * 20);
        char *tmp_username = (char *) malloc(20 * sizeof(char));
        char *tmp_password = (char *) malloc(20 * sizeof(char));
        int tmp_borrowNum;
        int tmp_maxBorrowNum;
        strcpy(tmp_username, username);
        strcpy(tmp_password, password);
        tmp_borrowNum = borrowNum;
        tmp_maxBorrowNum = maxBorrowNum;

        User *user = insertUser(userlist,
                                user_cnt,
                                tmp_username,
                                tmp_password,
                                tmp_borrowNum,
                                tmp_maxBorrowNum);
        user_cnt++;
        for (int i = 0; i < user->borrowNum; i++) {
            fscanf(fp, "%s\n", buf);
        }

    }
    userlist->userNum = user_cnt;
    fclose(fp);

}

/* check_valid()
 * ------------------
 * check if the username is valid
 *
 * username: username
 *
 * return 1 if not 0
*/
int check_valid(char *username){
    char invalid_char[] = "!@#$%^&*()_+-=[]{}|;':\",./<>?`~ ";
    for (int i = 0; i < strlen(username); i++) {
        for (int j = 0; j < strlen(invalid_char); j++) {
            if (username[i] == invalid_char[j]) {
                fprintf(stderr, "Username cannot contain special char！\n");
                return 0;
            }
        }
    }

    if (strlen(username) < 6 || strlen(username) > 20) {
        fprintf(stderr, "Username length should be between 6 and 20！\n");
        return 0;
    }
    return 1;
}

/* register_user()
 * -------------------
 * the logic of registering
 *
 * userlist: the linked list of users
 *
 * return: No return
 *
*/
void register_user(UserList *userlist) {

    char *username = malloc(sizeof(char) * 64);
    char *password = malloc(sizeof(char) * 64);
    char *password_confirm = malloc(sizeof(char) * 64);

    fprintf(stdout, "Please enter your username: \n");
    fgets(username, 64, stdin);
    username[strlen(username) - 1] = '\0';
    while (check_exist(userlist, username) == 1) {
        fprintf(stderr, "The username has been registered!\n");
        fprintf(stdout, "Please enter your username: \n");
        fgets(username, 64, stdin);
        username[strlen(username) - 1] = '\0';
    }

    while (check_valid(username) == 0) {
        fprintf(stdout, "Please enter your username: \n");
        fgets(username, 64, stdin);
        username[strlen(username) - 1] = '\0';
    }

    fprintf(stdout, "Please enter your password: \n");
    fgets(password, 64, stdin);
    password[strlen(password) - 1] = '\0';
    fprintf(stdout, "Please enter your password again: \n");
    scanf("%s", password_confirm);

    while (strcmp(password, password_confirm) != 0) {
        fprintf(stderr, "The password is not the same!\n");
        fprintf(stdout, "Please enter your password: \n");
        fgets(password, 64, stdin);
        password[strlen(password) - 1] = '\0';
        fprintf(stdout, "Please enter your password again: \n");
        fgets(password_confirm, 64, stdin);
        password_confirm[strlen(password_confirm) - 1] = '\0';
        fflush(stdin);
    }

    User *new_user;
    new_user = (User *) malloc(sizeof(User));
    new_user->username = (char *) malloc(sizeof(char) * 64);
    new_user->password = (char *) malloc(sizeof(char) * 64);

    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    new_user->borrowMax = 10;
    new_user->borrowNum = 0;
    new_user->bookList = malloc(sizeof(Book));
    new_user->bookList->list = createBook(99999999, " ", " ", 0, 10, 0);
    new_user->id = userlist->userNum;
    insertUser(userlist, new_user->id,
               new_user->username,
               new_user->password,
               new_user->borrowNum,
               new_user->borrowMax);
    fprintf(stdout, "Register successfully!");
}
