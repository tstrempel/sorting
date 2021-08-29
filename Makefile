.PHONY: clean

CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -g
LDFLAGS=-lm -lc

all: sorting sorting-O2 sorting-O3

sorting:
	$(CC) $(CFLAGS) -O0 main.c sort_functions.h -o sorting $(LDFLAGS)

sorting-O2:
	$(CC) $(CFLAGS) -O2 main.c sort_functions.h -o sorting-O2 $(LDFLAGS)

sorting-O3:
	$(CC) $(CFLAGS) -O3 main.c sort_functions.h -o sorting-O3 $(LDFLAGS)

clean:
	rm -rf *.o *.gch
