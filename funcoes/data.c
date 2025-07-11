#include <stdio.h>
#include "estruturas/data.h"

void lerData(Data *data) {
    printf("informe a data (dd mm aaaa): ");
    scanf("%d %d %d", &data->dia, &data->mes, &data->ano);
}

int compararData(Data d1, Data d2) {
    if (d1.ano != d2.ano)
        return d1.ano - d2.ano;
    if (d1.mes != d2.mes)
        return d1.mes - d2.mes;
    return d1.dia - d2.dia;
}