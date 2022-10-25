SHELL=/bin/sh
CC=gcc
CFLAGS=-Wall -O3

default: build

clean:
	rm -f main C.zip stack.o hanoi.o utils.o *.o core a.out *.*~ Makefile~ build/*

queue.o: src/queue/queue.c src/queue/queue.h src/queue/private_queue.h
	$(CC) $(CFLAGS) -c src/queue/queue.c -o build/queue.o

app.o: src/app.c src/app.h
	$(CC) $(CFLAGS) -c src/app.c -o build/app.o

utils.o: src/utils/utils.c src/utils/utils.h
	$(CC) $(CFLAGS) -c src/utils/utils.c -o build/utils.o

build: ./src/main.c utils.o app.o queue.o
	$(CC) $(CFLAGS) ./src/main.c build/utils.o build/queue.o build/app.o -o main

boca: clean
	zip -r D.zip build/ src/ D Makefile

valgrind:
	cat $(ENTRADA) | valgrind ./$(MAIN)

all: build
