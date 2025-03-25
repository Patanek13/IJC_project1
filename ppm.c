// ppm.c
// Řešení IJC-DU1, příklad b), 25.3.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ppm.h"
#include "error.h"

#define MaxColorValue 255
#define TwoSizes 2
#define RGB 3 
// Load PPM file into dynamically allocated structure.
// In case of format error, use the warning function and return NULL.
struct ppm *ppm_read(const char *filename) {
    FILE *ppm_file = fopen(filename, "r");

    if (ppm_file == NULL) {
        warning("ppm_read: Nelze otevřít soubor %s\n", filename);
        return NULL;
    }

    unsigned xsize, ysize;
    char MagicNumber[] = "P6";
    char buffer[3];
    unsigned ColorVal;
// Read MagicNumber, xsize, ysize, ColorValue and check if they are correct
    if ((fscanf(ppm_file, "%2s", buffer) != 1) || (strcmp(buffer, MagicNumber) != 0)) {
        warning("ppm_read: Chybný formát souboru (MagicNumber) %s\n", filename);
        fclose(ppm_file);
        return NULL;
    };

    if (fscanf(ppm_file,"%u %u", &xsize, &ysize) != TwoSizes || xsize < 1 || ysize < 1) {
        warning("ppm_read: Nesprávné rozměry obrázku %s\n", filename);
        fclose(ppm_file);
        return NULL;
    }

    if (fscanf(ppm_file, "%u", &ColorVal) != 1 || ColorVal != MaxColorValue) {
        warning("ppm_read: Chybný formát souboru (ColorValue) %s\n", filename);
        fclose(ppm_file);
        return NULL;
    }
// Check if there is a whitespace after ColorValue
   char c = fgetc(ppm_file);
    if (c == EOF || !isspace(c)) {
        warning("ppm_read: Chybný formát souboru %s\n", filename);
        fclose(ppm_file);
        return NULL;
    }
// Allocate memory for ppm structure
    struct ppm *ppm = malloc(sizeof(struct ppm) + RGB * xsize * ysize);

    if (ppm == NULL) {
        warning("ppm_read: Chyba alokace paměti %s\n");
        fclose(ppm_file);
        return NULL;
    }
// Fill ppm structure with data
    ppm->xsize = xsize;
    ppm->ysize = ysize;
// Read bit data from file
    if (fread(ppm->data, 1, RGB * xsize * ysize, ppm_file) != RGB * xsize * ysize) {
        warning("ppm_read: Chybný formát dat (BitData) %s\n", filename);
        free(ppm);
        fclose(ppm_file);
        return NULL;
    }

    fclose(ppm_file);
    return ppm;
}
// Free memory allocated in ppm_read.
void ppm_free (struct ppm *p) {
    free(p);
}

