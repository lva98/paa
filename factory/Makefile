SHELL=/bin/sh
CC=gcc
CFLAGS=-Wall -O3

default: build

clean:
	rm -f main C.zip stack.o hanoi.o utils.o *.o core a.out *.*~ Makefile~ build/*

queue.o: src/queue/queue.c src/queue/queue.h src/queue/private_queue.h
	$(CC) $(CFLAGS) -c src/queue/queue.c -o build/queue.o

build: ./src/main.c queue.o
	$(CC) $(CFLAGS) ./src/main.c build/queue.o -o main

boca: clean
	zip -r C.zip build/ src/ C Makefile

valgrind:
	cat $(ENTRADA) | valgrind ./$(MAIN)

all: build
