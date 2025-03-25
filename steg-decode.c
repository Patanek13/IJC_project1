// primes.c
// Řešení IJC-DU1, příklad b), 25.3.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "eratosthenes.h"
#include "ppm.h"
#include "bitset.h"
#include "error.h"
#include "utf8_check.h"

#define RGB 3
#define START_PRIME 101
// Write secret message from ppm_data to stdout
void write_secret_msg (struct ppm *ppm_struct, bitset_index_t *ppm_data) {
    char c = 0;
    bitset_index_t bit_count = 0;
    bitset_index_t msg_idx = 0;
// Allocate memory for message
   unsigned char *message = malloc(ppm_data[0]);
    if (message == NULL) {
        free(ppm_data);
        ppm_free(ppm_struct);
        error_exit("Chyba alokace paměti %s\n", write_secret_msg);
    }
// Iterate through ppm_data and ppm_struct
    for (bitset_index_t bit_idx = START_PRIME; bit_idx < ppm_data[0]; bit_idx++) {
        int bit = 0;
        if (bitset_getbit(ppm_data, bit_idx) == 1) {
            bit = ppm_struct->data[bit_idx] & 1;
// Shift bit to the left and add it to c if bit_count is less than CHAR_BIT
            c |= bit << bit_count;
            bit_count++;
// If bit_count is equal to byte(char), add c to message and reset c and bit_count
        if (bit_count == CHAR_BIT) {
            if (c == '\0') {
// If message is correctly terminated, break the loop
                message[msg_idx] = '\0';
                break;
            }
// If c is not null, add it to message
            message[msg_idx] = c;
            msg_idx++;
            c = 0;
            bit_count = 0;
        }

    }
}
// Check if message is in UTF-8 format
    if (utf8_check(message) != NULL) {
        free(ppm_data);
        free(message);
        ppm_free(ppm_struct);
        error_exit("Zpráva nebyla řádně ukončena %s\0", utf8_check);
    } else {
        printf("%s\n", message);
        free(message);
    }
}
// Read bitset from ppm_struct and use Eratosthenes algorithm to find prime numbers
// Return bitset with prime numbers
bitset_index_t *read_secret_msg (struct ppm *ppm_struct){
    bitset_index_t *ppm_data = calloc(ppm_struct->xsize * ppm_struct->ysize * RGB, sizeof(bitset_index_t));

    if (ppm_data == NULL) {
        ppm_free(ppm_struct);
        error_exit("read_secret_msg: Chyba alokace paměti %s\n", read_secret_msg);
    }

    ppm_data[0] = ppm_struct->xsize * ppm_struct->ysize * RGB;
    Eratosthenes(ppm_data);
    
    return ppm_data;
}

int main (int argc, char *argv[]) {
// Check if there is correct number of arguments
    if (argc > 2) {
        fprintf(stderr, "steg-decode: Nesprávný počet argumentů\n");
        exit(1);
    }
// Read ppm file
    struct ppm *p_img = ppm_read(argv[1]);
    if (p_img == NULL) {
        error_exit("Nepodařilo se načíst obrázek %s\n", argv[1]);
    }

    bitset_index_t *ppm_data = read_secret_msg(p_img);
    write_secret_msg(p_img, ppm_data);
    free(ppm_data);
    ppm_free(p_img);
}