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

    if ((fscanf(ppm_file, "%2s", buffer) != 1) || (strcmp(buffer, MagicNumber) != 0)) {
        warning("ppm_read: Chybný formát souboru %s\n", filename);
        fclose(ppm_file);
        return NULL;
    };

    if (fscanf(ppm_file,"%u %u", xsize, ysize) != TwoSizes || xsize < 1 || ysize < 1) {
        warning("ppm_read: Nesprávné rozměry obrázku %s\n", filename);
        fclose(ppm_file);
        return NULL;
    }

    if (fscanf(ppm_file, "%u", &ColorVal) != 1 || ColorVal == MaxColorValue) {
        warning("ppm_read: Chybný formát souboru %s\n", filename);
        fclose(ppm_file);
        return NULL;
    }

    char c = fgetc(ppm_file);
    if (c == EOF || !isspace(c)) {
        warning("ppm_read: Chybný formát souboru %s\n", filename);
        fclose(ppm_file);
        return NULL;
    }

    struct ppm *ppm = malloc(sizeof(struct ppm) + RGB * xsize * ysize);

    if (ppm == NULL) {
        warning("ppm_read: Chyba alokace paměti %s\n");
        fclose(ppm_file);
        return NULL;
    }

    ppm->xsize = xsize;
    ppm->ysize = ysize;

    if (fread(ppm->data, RGB, xsize * ysize, ppm_file) != xsize * ysize) {
        warning("ppm_read: Chybný formát dat %s\n");
        free(ppm);
        fclose(ppm_file);
        return NULL;
    }

    fclose(ppm_file);
    return ppm;
}

void ppm_free (struct ppm *p) {
    free(p);
}

