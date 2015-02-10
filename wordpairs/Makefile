LIBDIR = -L$(GET_WORD)/lib
INCLUDEDIR = -I$(GET_WORD)/include

WordPair: hashtable.c main.c
	gcc -Wall -g -std=c99 $(INCLUDEDIR) $(LIBDIR) hashtable.c main.c -o WordPairs -lget