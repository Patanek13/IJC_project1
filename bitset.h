// bitset.h
// Řešení IJC-DU1, příklad a), 25.3.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3

#ifndef BITSET_H
#define BITSET_H
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "error.h"

// Typ bitového pole (pro předávání parametru do funkce odkazem).
typedef unsigned long bitset_t[];

// Typ indexu bitového pole.
typedef unsigned long bitset_index_t;

#ifndef USE_INLINE

// Num of ULs to store all bits
#define bit_size(size) ((size + (sizeof(bitset_index_t) * CHAR_BIT - 1)) / (sizeof(bitset_index_t) * CHAR_BIT))

//num of ULs to store all bits and one element for bitset_size
#define bitset_create(arr_name, size) \
    static_assert(size > 0 && size < ULONG_MAX, "bitset_create: Spatna velikost pole!\n"); \
    bitset_index_t arr_name[bit_size(size) + 1] = {0}; \
    arr_name[0] = size;


#define bitset_alloc(arr_name, size) \
    assert(size > 0 && size < ULONG_MAX); \
    bitset_t *arr_name = calloc(bit_size(size) + 1, sizeof(bitset_index_t)); \
    if (arr_name == NULL) { \
        error_exit("%s: bitset_alloc: Chyba alokace paměti\n"); \
    } \
    arr_name[0] = size;

#define bitset_free(arr_name) free(arr_name)

#define bitset_size(arr_name) arr_name[0]

#define bitset_fill(arr_name, bool_expr) \
    for (bitset_index_t index = 1; index <= bit_size(arr_name); index++ ) { \
        if (bool_expr) { \
            arr_name[index] = ULLONG_MAX; \
        } else { \
            arr_name[index] = 0UL; \
        } \
    }

#define bitset_setbit(arr_name, index, bool_expr) \
    bitset_index_t bit_arr_idx = index / (sizeof(bitset_index_t) * CHAR_BIT) + 1; \
    bitset_index_t bit_index = index % (sizeof(bitset_index_t) * CHAR_BIT); \
    if (index >= arr_name[0]) { \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", index, arr_name[0]); \
    } else { \
        bitset_index_t value = 1UL << bit_index; \
        if (bool_expr) { \
            arr_name[bit_arr_idx] |= value; \
        } else { \
            arr_name[bit_arr_idx] &= ~value; \
        } \
    }

#define bitset_getbit(arr_name, index) \
    ( \
        (index >= arr_name[0]) ? \
        (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", index, arr_name[0]), 0) : \
        ((arr_name[(index / (sizeof(bitset_index_t) * CHAR_BIT)) + 1] >> (index % (sizeof(bitset_index_t) * CHAR_BIT))) & 1) \
    )

#else

static inline void bitset_free(bitset_t arr_name) {
    free(arr_name);
}

static inline bitset_index_t bitset_size(bitset_t arr_name) {
    return arr_name[0];
}

static inline void bitset_fill(bitset_t arr_name, int bool_expr) {
    for (bitset_index_t index = 1; index < (arr_name[0] / (sizeof(bitset_index_t) * CHAR_BIT) + 1); index++ ) {
        if (bool_expr) {
            arr_name[index] = ULONG_MAX;
        } else {
            arr_name[index] = 0UL;
        }
    }
}

static inline void bitset_setbit(bitset_t arr_name, bitset_index_t index, int bool_expr) {
    bitset_index_t bit_arr_idx = index / (sizeof(bitset_index_t) * CHAR_BIT) + 1;
    bitset_index_t bit_index = index % (sizeof(bitset_index_t) * CHAR_BIT);
    if (index >= arr_name[0]) {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", index, arr_name[0]);
    } else {
        bitset_index_t value = 1UL << bit_index;
        if (bool_expr) {
            arr_name[bit_arr_idx] |= value;
        } else {
            arr_name[bit_arr_idx] &= ~value;
        }
    }
}

static inline bitset_index_t bitset_getbit(bitset_t arr_name, bitset_index_t index) {
    return (index >= arr_name[0]) ? 
        (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", index, arr_name[0]), 0) :
        ((arr_name[(index / (sizeof(bitset_index_t) * CHAR_BIT)) + 1] >> (index % (sizeof(bitset_index_t) * CHAR_BIT))) & 1);
}

#endif // USE_INLINE
#endif // BITSET_H


