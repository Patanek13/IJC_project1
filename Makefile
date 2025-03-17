# Makefile
# Řešení IJC-DU1, příklad a) b), 25.3.2025
# Autor: Patrik Lošťák, FIT

# Compiler
CC = gcc
# Flags/parametres for compiler
CFLAGS = -std=c11 -pedantic -Wall -Wextra 
# Library flags
LDFLAGS = -lm 
# Debugger flags
DBFLAGS = -g
# Source code files
SRC = primes.c eratosthenes.c
HEADERS = bitset.h eratosthenes.h
OBJECTS = $(SRC:.c=.o)

CFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address

.PHONY: all run clean zip

all: primes primes-i steg-decode

clean:
	rm -f *.o *.elf primes primes-i steg-decode

run: primes primes-i 
	ulimit -s 33333 && ./primes && ./primes-i

zip:
	zip xlostap00.zip *.c *.h Makefile

# Linikng
primes: $(OBJECTS)
	$(CC) $(CFLAGS) $(DBFLAGS) -o $@ $^ $(LDFLAGS) 

primes-i: primes-i.o bitset.o eratosthenes.o
	$(CC) $(CFLAGS) $(DBFLAGS) -DUSE_INLINE -o $@ $^ $(LDFLAGS)

# Compile
primes.o: primes.c $(HEADERS)
	$(CC) $(CFLAGS) $(DBFLAGS) -c -o $@ primes.c

primes-i.o: primes.c $(HEADERS)
	$(CC) $(CFLAGS) $(DBFLAGS) -c -o $@ -DUSE_INLINE primes.c

eratosthenes.o: eratosthenes.c $(HEADERS)
	$(CC) $(CFLAGS) $(DBFLAGS) -c -o $@ eratosthenes.c



