// ppm.h
// Řešení IJC-DU1, příklad b), 25.3.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3

#ifndef PPM_H
#define PPM_H

struct ppm {
    unsigned xsize; // Šířka obrázku zapsaná v ASCII v desítkové soustavě.
    unsigned ysize; // Obdobně výška obrázku.
    char data[]; // RGB bajty, celkem 3*xsize*ysize
};

// Načte obsah PPM souboru do touto funkcí dynamicky alokované struktury. 
// Při chybě formátu použije funkci warning a vrátí NULL.
struct ppm * ppm_read(const char * filename);

// Uvolní paměť dynamicky alokovanou v ppm_read.
void ppm_free(struct ppm *p);

#endif // PPM_H
