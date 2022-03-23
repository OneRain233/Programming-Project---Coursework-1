EXE = ./library
SRC = main.c login.c register.c user.c utils.c interface.c admin.c book_management.c

# generic build details

CC = gcc
CFLAGS= -std=c99 -Wall
CLINK=

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE)


clean:
	rm -f $(OBJ) $(EXE)

# dependencies

#main.o: main.c Register.h Login.h book_management.h
#Register.o: Register.c Register.h book_management.h Login.h
#user.o: user.c book_management.h user.h Librarian.h Register.h
#Login.o: Login.c Login.h Register.h book_management.h Librarian.h user.h
#Librarian.o: Librarian.c Login.h book_management.h Register.h
#book_management.o: book_management.c book_management.h Librarian.h Login.h
