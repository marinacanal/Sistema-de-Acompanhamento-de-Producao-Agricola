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
    struct listaProducao *prox;
} ListaProducao;

int existeCodigo(ListaProducao *listaProducao, int codigo);
ListaProducao* inserirOrdenadoPorData(ListaProducao *listaProducao, Producao prod);
ListaProducao* excluirPorCodigo(ListaProducao *listaProducao, int codigo);
ListaProducao* alterarPorCodigo(ListaProducao *listaProducao, int codigo);
void consultarPorData(ListaProducao *listaProducao, Data data);
void consultarPorCultivar(ListaProducao *listaProducao, const char *cultivar);
void listarTodos(ListaProducao *listaProducao);
void liberarLista(ListaProducao *listaProducao);