#include "book_management.h"

#include "interface.h"

/* main()
 * --------------
 * main login
 *
*/
int main(int argc, char *argv[]){
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <book_file> <user_file>\n", argv[0]);
        return 1;
    }
    char *book_file = argv[1];
    char *user_file = argv[2];
    fprintf(stdout, "__        _______ _     ____ ___  __  __ _____ \n"
                    "\\ \\      / / ____| |   / ___/ _ \\|  \\/  | ____|\n"
                    " \\ \\ /\\ / /|  _| | |  | |  | | | | |\\/| |  _|  \n"
                    "  \\ V  V / | |___| |__| |__| |_| | |  | | |___ \n"
                    "   \\_/\\_/  |_____|_____\\____\\___/|_|  |_|_____|\n"
                    "                                                \n"
    );
    run_interface(book_file, user_file);
    return 0;
}