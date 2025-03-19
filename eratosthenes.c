// eratosthenes.c
// Řešení IJC-DU1, příklad b), 25.3.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3

#include <math.h>
#include <stdbool.h>
#include "eratosthenes.h"


void Eratosthenes(bitset_t array){
    bitset_fill(array, 1);
    bitset_setbit(array, 0, 0);
    bitset_setbit(array, 1, 0);

    for (bitset_index_t i = 2; i <= sqrt(bitset_size(array)); i++) {
        if (bitset_getbit(array, i)) {
            for (bitset_index_t j = i * i; j < bitset_size(array); j += i) {
                bitset_setbit(array, j, 0);
            }
        }
    }
}