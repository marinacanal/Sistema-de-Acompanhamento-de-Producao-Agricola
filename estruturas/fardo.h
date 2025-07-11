#include <stdio.h>

#define CULTIVAR_TAM 20

typedef struct fardo {
    char cultivar[CULTIVAR_TAM];
    char tipoDeFeno; // A, B ou C
    int diametro; // em cm
} Fardo;

float calcularAreaMinima(int diametro, int qtFardos);