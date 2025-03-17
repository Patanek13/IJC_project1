# Makefile
# Řešení IJC-DU1, příklad a) b), 25.3.2025
# Autor: Patrik Lošťák, FIT

# Compiler
CC = gcc
# Flags/parametres for compiler
CFLAGS = -std=c11 -pedantic -Wall -Wextra
# Library flags
LDFLAGS = -lm -m32
# Debugger flags
DBFLAGS = -g
# Source code files
SRC = primes.c bitset.c eratosthenes.c
HEADERS = bitset.h eratosthenes.h
OBJECTS = $(SRC: .c = .o)

CFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address
LC_ALL = cs_CZ.utf8

.PHONY: all run clean zip


# A)
primes: $(OBJECTS)
	$(CC) $(CFLAGS) $(DBFLAGS) -o $@ $^ $(LDFLAGS) 

primes-i: $(OBJECTS)
	$(CC) $(CFLAGS) $(DBFLAGS) -DUSE_INLINE -o $@ $^ $(LDFLAGS)

