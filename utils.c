//
// Created by onerain233 on 2022/3/2.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int optionChoice(void) {
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

