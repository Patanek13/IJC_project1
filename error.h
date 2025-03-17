// error.h
// Řešení IJC-DU1, příklad b), 25.3.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3

// Tisknou text "Warning: " nebo "Error: " a potom chybové hlášení podle formátu fmt na stderr (standardní funkcí vfprintf).
void warning(const char* fmt, ...);
// Ukončí program voláním funkce exit(1)
void error_exit(const char* fmt, ...);