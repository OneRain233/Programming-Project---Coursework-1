//
// Created by onerain233 on 2022/3/2.
//

#ifndef PROJECT1_REGISTER_H
#define PROJECT1_REGISTER_H
void register_user(UserList *userlist);
void read_user(BookList *booklist, UserList *userlist);
int check_exist(UserList *userlist, char *username);
int check_valid(char *username);
#endif //PROJECT1_REGISTER_H
