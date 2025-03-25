// error.c
// Řešení IJC-DU1, příklad b), 25.3.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
// Print warning message to stderr
void warning (const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}
// Print error message to stderr and exit program
void error_exit (const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
