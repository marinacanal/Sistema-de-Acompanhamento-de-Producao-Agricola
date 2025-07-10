#include <stdio.h>
#include "data.h"
#include "fardo.h"

typedef struct producao {
    int codigo;
    Data dataProducao;
    Fardo tipoDeFardo;
    int qtDeFardos;
    int tempoEmMin;
} Producao;

typedef struct listaProducao {
    Producao dado;
    struct producao *prox;
} ListaProducao;

ListaProducao* inserir(ListaProducao *lista, Producao prod, int *sucesso);
ListaProducao* excluirPorCodigo(ListaProducao *lista, int codigo, int *sucesso);
ListaProducao* alterarPorCodigo(ListaProducao *lista, int codigo, int *sucesso);
void consultarPorData(ListaProducao *lista, Data data);
void consultarPorCultivar(ListaProducao *lista, const char *cultivar);
void listarTodos(ListaProducao *lista);