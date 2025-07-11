#include <stdio.h>
#include "../estruturas/fardo.h"

float calcularAreaMinima(int diametro, int qtFardos) {
    float raio = (diametro / 100.0) / 2.0; 
    int colunas = (qtFardos + 2) / 3;
    float areaBase = 3.141592653589793 * raio * raio;
    float areaComPerda = areaBase * 1.2;
    return colunas * areaComPerda;
}