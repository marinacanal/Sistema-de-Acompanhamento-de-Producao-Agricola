#ifndef PRODUCAO_H
#define PRODUCAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CULTIVAR_TAM 20

// Structs principais
typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct fardo {
    char cultivar[CULTIVAR_TAM];
    char tipoDeFeno; // A, B ou C
    int diametro;    // em cm
} Fardo;

typedef struct producao {
    int codigo;
    Data dataProducao;
    Fardo tipoDeFardo;
    int qtDeFardos;
    int tempoEmMin;
} Producao;

// Nó da lista encadeada
typedef struct nodo {
    Producao dado;
    struct nodo *prox;
} Nodo;

// Funções principais do sistema
Nodo* inserirOrdenado(Nodo *lista, Producao prod, int *sucesso);
Nodo* excluirPorCodigo(Nodo *lista, int codigo, int *sucesso);
Nodo* alterarPorCodigo(Nodo *lista, int codigo, int *sucesso);
void consultarPorData(Nodo *lista, Data data);
void consultarPorCultivar(Nodo *lista, const char *cultivar);
void listarTodos(Nodo *lista);
void liberarLista(Nodo *lista);

// Auxiliares
int compararData(Data d1, Data d2);
int existeCodigo(Nodo *lista, int codigo);
float calcularAreaMinima(int diametro, int qtFardos);
void lerData(Data *d);
void limparBuffer();

#endif
