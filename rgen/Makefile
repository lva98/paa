SHELL=/bin/sh
CC=gcc
CFLAGS=-Wall -O3
NOME=rgen
ENTRADA=entry.txt
MAIN=main

default: build

clean:
	rm -f $(MAIN) $(NOME) *.o core a.out *.*~ Makefile~

$(NOME).o: src/tda/$(NOME).c src/tda/pub_$(NOME).h src/tda/pri_$(NOME).h
	$(CC) $(CFLAGS) -c src/tda/$(NOME).c -o $(NOME).o

build: ./src/$(MAIN).c ./src/$(MAIN).h $(NOME).o
	$(CC) $(CFLAGS) ./src/$(MAIN).c $(NOME).o -o $(MAIN)

valgrind:
	cat $(ENTRADA) | valgrind ./$(MAIN)

all: build
