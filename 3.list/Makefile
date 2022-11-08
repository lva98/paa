SHELL=/bin/sh
CC=gcc
CFLAGS=-Wall -O3

default: build

clean:
	rm -f main C.zip list.o app.o utils.o *.o core a.out *.*~ Makefile~ build/*

list.o: src/list/list.c src/list/list.h src/list/private_list.h
	$(CC) $(CFLAGS) -c src/list/list.c -o build/list.o

app.o: src/app.c src/app.h
	$(CC) $(CFLAGS) -c src/app.c -o build/app.o

utils.o: src/utils/utils.c src/utils/utils.h
	$(CC) $(CFLAGS) -c src/utils/utils.c -o build/utils.o

build: ./src/main.c utils.o app.o list.o
	$(CC) $(CFLAGS) ./src/main.c build/utils.o build/list.o build/app.o -o main

boca: clean
	zip -r E.zip build/ src/ E Makefile

valgrind:
	cat $(ENTRADA) | valgrind ./$(MAIN)

all: build
