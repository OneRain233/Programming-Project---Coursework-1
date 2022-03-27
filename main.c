#include "book_management.h"

#include "interface.h"

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: %s <book_file> <user_file>\n", argv[0]);
        return 1;
    }
    char *book_file = argv[1];
    char *user_file = argv[2];
    run_interface(book_file, user_file);
    return 0;
}