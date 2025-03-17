// bitset.h
// Řešení IJC-DU1, příklad a), 25.3.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "error.h"

// Typ bitového pole (pro předávání parametru do funkce odkazem).
typedef unsigned long bitset_t[];

// Typ indexu bitového pole.
typedef unsigned long bitset_index_t;
// Num of ULs to store all bits
#define bit_size(size) size / (sizeof(unsigned long) * CHAR_BIT) + (size / sizeof(unsigned long) == 0 ? 0 : 1)

//num of ULs to store all bits and one element for bitset_size
#define bitset_create(arr_name, size) \
    static_assert(size > 0 && size < ULONG_MAX, "bitset_create: Spatna velikost pole!\n"); \
    bitset_index_t arr_name[bit_size(size) + 1] = {0}; \
    arr_name[0] = size;


#define bitset_alloc(arr_name, size) \
    assert(size > 0 && size < ULONG_MAX, "bitset_alloc: Chyba alokace paměti\n"); \
    bitset_t *arr_name = calloc(bit_size(size) + 1, sizeof(unsigned long)); \
    if (arr_name == NULL) { \
        error_exit("%s: bitset_alloc: Chyba alokace paměti\n"); \
    } \
    arr_name[0] = size; 

#define bitset_free(arr_name) free(arr_name)

#define bitset_size(arr_name) arr_name[0]

#define bitset_fill(arr_name, bool_expr) \
    unsigned long val = (bool_expr) ? ULONG_MAX : 0UL; \
    for (unsigned long index = 1; index < (arr_name[0] \ (sizeof(unsigned long) * CHAR_BIT) + 1); index++ ) { \
        if (bool_expr) { \
            arr_name[index] = val; \
        } \
    }
