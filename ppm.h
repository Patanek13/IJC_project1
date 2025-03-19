// ppm.h
// Řešení IJC-DU1, příklad b), 25.3.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3

#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[]; // RGB bajty, celkem 3*xsize*ysize
};

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);

#endif // PPM_H
