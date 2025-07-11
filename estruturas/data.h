#include <stdio.h>

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

int compararData(Data data1, Data data2);
void lerData(Data *data);