CC = gcc
CFLAGS = -c -Wall

all: prog

prog: main.o leitura.o tad.o
	$(CC) main.o leitura.o tad.o -o prog

main.o: main.c
	$(CC) $(CFLAGS) main.c

leitura.o: leitura.c
	$(CC) $(CFLAGS) leitura.c

tad.o: tad.c
	$(CC) $(CFLAGS) tad.c

clean:
	rm -rf *o prog
