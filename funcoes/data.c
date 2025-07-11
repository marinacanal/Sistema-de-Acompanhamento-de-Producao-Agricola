#include <stdio.h>
#include "../estruturas/data.h"

void lerData(Data *data) {
    printf("informe a data (dd mm aaaa): ");
    scanf("%d %d %d", &data->dia, &data->mes, &data->ano);
}

int compararData(Data data1, Data data2) { // retorna diferenca
    if (data1.ano != data2.ano) 
        return data1.ano - data2.ano;

    if (data1.mes != data2.mes)
        return data1.mes - data2.mes;

    return data1.dia - data2.dia;
}