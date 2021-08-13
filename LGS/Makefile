# Alle auführbaren Dateien sind statisch gelinkt!
# Um dynamisch zu linken die Option -static entfernen
# pkg-config --libs gsl
# CC CFLAGS CPPFLAGS __ LDFLAGS
.PHONY: clean

CC=gcc
CFLAGS=-static -Wall -ansi -pedantic -g
LDFLAGS=-lgsl -lgslcblas -lm -lc

all: common_methods.o jacobi.bin gauss_seidel.bin sor.bin

common_methods.o: common_methods.c common_methods.h
	$(CC) $(CFLAGS) -c common_methods.c common_methods.h $(LDFLAGS)

jacobi.bin:	jacobi.c common_methods.o
	$(CC) $(CFLAGS) common_methods.o jacobi.c -o jacobi.bin $(LDFLAGS)

gauss_seidel.bin: gauss_seidel.c common_methods.o
	$(CC) $(CFLAGS) common_methods.o gauss_seidel.c -o gauss_seidel.bin $(LDFLAGS)

sor.bin: sor.c common_methods.o
	$(CC) $(CFLAGS) common_methods.o sor.c -o sor.bin $(LDFLAGS)

clean:
	rm -rf *.o *.gch