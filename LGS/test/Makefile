CC=gcc
CFLAGS=-I/usr/include/gsl -ansi -Wall -pedantic -g
LDFLAGS=-lgsl -lgslcblas

%: %.c
		$(CC) $(CFLAGS) $(LDFLAGS) $<
		#$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
		rm -f *~ ~.o core a.out