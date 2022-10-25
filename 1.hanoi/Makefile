SHELL=/bin/sh
CC=gcc
CFLAGS=-Wall -O3

default: build

clean:
	rm -f main C.zip stack.o hanoi.o utils.o *.o core a.out *.*~ Makefile~ build/*

stack.o: src/stack/stack.c src/stack/stack.h src/stack/private_stack.h
	$(CC) $(CFLAGS) -c src/stack/stack.c -o build/stack.o

hanoi.o: src/hanoi/hanoi.c src/hanoi/hanoi.h src/hanoi/private_hanoi.h
	$(CC) $(CFLAGS) -c src/hanoi/hanoi.c -o build/hanoi.o

utils.o: src/utils/utils.c src/utils/utils.h
	$(CC) $(CFLAGS) -c src/utils/utils.c -o build/utils.o

io.o: src/io.c src/io.h
	$(CC) $(CFLAGS) -c src/io.c -o build/io.o

build: ./src/main.c stack.o hanoi.o utils.o io.o
	$(CC) $(CFLAGS) ./src/main.c build/stack.o build/hanoi.o build/utils.o build/io.o -o main

boca: clean
	zip -r C.zip build/ src/ C Makefile

valgrind:
	cat $(ENTRADA) | valgrind ./$(MAIN)

all: build
