SHELL=/bin/sh
CC=gcc
CFLAGS=-Wall -O3

default: build

clean:
	rm -f main C.zip web_tree.o utils.o *.o core a.out *.*~ Makefile~ build/*

web_tree.o: src/web_tree/web_tree.c src/web_tree/web_tree.h src/web_tree/private_web_tree.h
	$(CC) $(CFLAGS) -c src/web_tree/web_tree.c -o build/web_tree.o

utils.o: src/utils/utils.c src/utils/utils.h
	$(CC) $(CFLAGS) -c src/utils/utils.c -o build/utils.o

build: ./src/main.c utils.o web_tree.o
	$(CC) $(CFLAGS) ./src/main.c build/utils.o build/web_tree.o -o main

boca: clean
	zip -r E.zip build/ src/ E Makefile

valgrind:
	cat $(ENTRADA) | valgrind ./$(MAIN)

all: build
