# Makefile
# Řešení IJC-DU1, příklad a) b), 25.3.2025
# Autor: Patrik Lošťák, FIT

# Compiler
CC = gcc
# Flags/parametres for compiler
CFLAGS = -std=c11 -pedantic -Wall -Wextra -O2
# Library flags
LDFLAGS = -lm
# Debugger flags
DBFLAGS = -g
# Source code files
SRC = primes.c eratosthenes.c error.c
HEADERS = bitset.h eratosthenes.h
OBJECTS = $(SRC:.c=.o)

# Add sanitizer flags to the CFLAGS
#CFLAGS += -fsanitize=address

.PHONY: all run clean zip

all: primes primes-i steg-decode

clean:
	rm -f *.o *.elf primes primes-i steg-decode xlostap00.zip

run: all
	ulimit -v unlimited && ./primes && ./primes-i

zip:
	zip xlostap00.zip *.c *.h Makefile

# Linking
primes: $(OBJECTS)
	$(CC) $(CFLAGS) $(DBFLAGS) -o $@ $^ $(LDFLAGS) 

primes-i: primes-i.o eratosthenes.o error.o
	$(CC) $(CFLAGS) $(DBFLAGS) -DUSE_INLINE -o $@ $^ $(LDFLAGS)

steg-decode: steg-decode.o ppm.o error.o eratosthenes.o utf8_check.o
	$(CC) $(CFLAGS) $(DBFLAGS) -o $@ $^ $(LDFLAGS)

# Compile
primes.o: primes.c $(HEADERS)
	$(CC) $(CFLAGS) $(DBFLAGS) -c -o $@ primes.c

primes-i.o: primes.c $(HEADERS)
	$(CC) $(CFLAGS) $(DBFLAGS) -c -o $@ -DUSE_INLINE primes.c

eratosthenes.o: eratosthenes.c $(HEADERS)
	$(CC) $(CFLAGS) $(DBFLAGS) -c -o $@ eratosthenes.c

error.o: error.h error.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c -o $@ error.c

steg-decode.o: steg-decode.c ppm.h error.h eratosthenes.h utf8_check.h bitset.h 
	$(CC) $(CFLAGS) $(DBFLAGS) -c -o $@ steg-decode.c

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) $(DBFLAGS) -c -o $@ ppm.c

utf8_check.o: utf8_check.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c -o $@ utf8_check.c
