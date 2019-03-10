all: test

CC=gcc

LIBS=
CFLAGS=

FLAGS=-O3 -pipe -s
DEBUGFLAGS=-Og -pipe -g

INPUT=test.c
OUTPUT=libspool_test

RM=/bin/rm

test:
	$(CC) $(INPUT) -o $(OUTPUT) $(LIBS) $(CFLAGS) $(FLAGS)

debug:
	$(CC) $(INPUT) -o $(OUTPUT) $(LIBS) $(CFLAGS) $(DEBUGFLAGS)

clean:
	if [ -e $(OUTPUT) ]; then $(RM) $(OUTPUT); fi
