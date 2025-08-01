// primes.c
// Řešení IJC-DU1, příklad a), 25.3.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "eratosthenes.h"
#include "bitset.h"

#define MAX 333000000
#define PRINT 10
// Print last 10 primes from bitset array to stdout separated by newline in ascending order
void print_primes(bitset_t array) {
    unsigned long count = 0;
    unsigned long primes[PRINT];
    for (bitset_index_t idx = bitset_size(array) - 1; idx > 0; idx--) {
        if (bitset_getbit(array, idx) == 1) {
            primes[count] = idx;
            count++;
        }
        if (count == PRINT) {
            break;
        }
    }

    for (int idx = PRINT - 1; idx >= 0; idx--) {
        printf("%lu\n", primes[idx]);
    }
}

int main() {
    // Create bitset array on stack, find primes and print them
    clock_t start = clock();
    bitset_create(array, MAX);
    Eratosthenes(array);
    print_primes(array);
    // Print time of execution
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}