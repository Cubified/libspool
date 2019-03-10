all: test

CC=gcc

LIBS=
CFLAGS=-Wno-int-to-pointer-cast -Wno-pointer-to-int-cast

FLAGS=-O3 -pipe -s -ansi -pedantic
DEBUGFLAGS=-Og -pipe -g -ansi -pedantic

INPUT=test.c
OUTPUT=libspool_test

RM=/bin/rm

test:
	$(CC) $(INPUT) -o $(OUTPUT) $(LIBS) $(CFLAGS) $(FLAGS)

debug:
	$(CC) $(INPUT) -o $(OUTPUT) $(LIBS) $(CFLAGS) $(DEBUGFLAGS)

clean:
	if [ -e $(OUTPUT) ]; then $(RM) $(OUTPUT); fi
