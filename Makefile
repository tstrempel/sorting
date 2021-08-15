.PHONY: clean

CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -g
LDFLAGS=-lm -lc

all: sort

sort:
	$(CC) $(CFLAGS) main.c sort_functions.h -o sorting $(LDFLAGS)

clean:
	rm -rf *.o *.gch
