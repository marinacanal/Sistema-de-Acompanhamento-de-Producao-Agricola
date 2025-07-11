#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas/producao.h"

int existeCodigo(ListaProducao *listaProducao, int codigo) {
    while (listaProducao != NULL) {
        if (listaProducao->dado.codigo == codigo)
            return 1;
            listaProducao = listaProducao->prox;
    }
    return 0;
}

ListaProducao* inserirOrdenadoPorData(ListaProducao *listaProducao, Producao prod) {
    if (existeCodigo(listaProducao, prod.codigo)) {
        printf("já existe uma produção com o código %d.\n", prod.codigo);
        return listaProducao;
    }

    ListaProducao *novaProducao = (ListaProducao*) malloc(sizeof(ListaProducao));
    ListaProducao *atual = listaProducao;

    novaProducao->dado = prod;
    novaProducao->prox = NULL;
    
    if (listaProducao == NULL || compararData(prod.dataProducao, listaProducao->dado.dataProducao) < 0) {
        novaProducao->prox = listaProducao;
        return novaProducao;
        printf("produção incluída com sucesso!\n");
    }

    while (atual->prox != NULL && compararData(prod.dataProducao, listaProducao->dado.dataProducao) >= 0) {
        atual = atual->prox;
    }
    
    novaProducao->prox = listaProducao;
    atual->prox = novaProducao;
    printf("produção incluída com sucesso!\n");

    return listaProducao;
}

void listarTodos(ListaProducao *listaProducao) {
    if (listaProducao == NULL) {
        printf("nenhuma produção registrada.\n");
        return;
    }

    printf("lista de produções:\n");

    ListaProducao *atual = listaProducao;

    while (atual != NULL) {
        printf("\nCódigo: %d | Data: %02d/%02d/%04d | Cultivar: %s | Tipo: %c\n",
            atual->dado.codigo,
            atual->dado.dataProducao.dia, atual->dado.dataProducao.mes, atual->dado.dataProducao.ano,
            atual->dado.tipoDeFardo.cultivar,
            atual->dado.tipoDeFardo.tipoDeFeno);
        printf("Diâmetro: %d cm | Qtde de Fardos: %d | Tempo: %d min\n\n",
            atual->dado.tipoDeFardo.diametro,
            atual->dado.qtDeFardos,
            atual->dado.tempoEmMin);
        atual = atual->prox;
    }
}

void consultarPorData(ListaProducao *listaProducao, Data data) {
    int achou = 0;
    ListaProducao *atual = listaProducao;

    while (atual != NULL) {
        if (compararData(atual->dado.dataProducao, data) == 0) {
  
            printf("%02d/%02d/%04d: %s - %c - %d fardos\n",
                atual->dado.dataProducao.dia, atual->dado.dataProducao.mes, atual->dado.dataProducao.ano,
                atual->dado.tipoDeFardo.cultivar,
                atual->dado.tipoDeFardo.tipoDeFeno,
                atual->dado.qtDeFardos);
            achou = 1;
        }
        atual = atual->prox;
    }

    if (!achou) {
        printf("nenhuma produção encontrada para essa data.\n");
    }
}

void consultarPorCultivar(ListaProducao *listaProducao, const char *cultivarBuscado) {
    if (listaProducao == NULL) {
        printf("nenhum registro disponível.\n");
        return;
    }

    int somaA = 0, somaB = 0, somaC = 0;
    int diamA = 0, diamB = 0, diamC = 0;

    ListaProducao *atual = listaProducao;
    while (atual != NULL) {
        Producao p = atual->dado;
        if (strcmp(p.tipoDeFardo.cultivar, cultivarBuscado) == 0) {
            switch (p.tipoDeFardo.tipoDeFeno) {
                case 'A':
                    somaA += p.qtDeFardos;
                    diamA = p.tipoDeFardo.diametro;
                    break;
                case 'B':
                    somaB += p.qtDeFardos;
                    diamB = p.tipoDeFardo.diametro;
                    break;
                case 'C':
                    somaC += p.qtDeFardos;
                    diamC = p.tipoDeFardo.diametro;
                    break;
            }
        }
        atual = atual->prox;
    }

    if (somaA == 0 && somaB == 0 && somaC == 0) {
        printf("nenhum registro encontrado para a cultivar '%s'.\n", cultivarBuscado);
        return;
    }

    printf("resultados para cultivar '%s':\n", cultivarBuscado);

    if (somaA > 0) {
        float area = calcularAreaMinima(diamA, somaA);
        printf("A: %d fardos - área mínima: %.2f m²\n", somaA, area);
    }
    if (somaB > 0) {
        float area = calcularAreaMinima(diamB, somaB);
        printf("B: %d fardos - área mínima: %.2f m²\n", somaB, area);
    }
    if (somaC > 0) {
        float area = calcularAreaMinima(diamC, somaC);
        printf("C: %d fardos - área mínima: %.2f m²\n", somaC, area);
    }
}

ListaProducao* excluirPorCodigo(ListaProducao *listaProducao, int codigo) {
    if (listaProducao == NULL) return NULL;

    ListaProducao *atual = listaProducao;
    ListaProducao *anterior = NULL;

    while (atual != NULL && atual->dado.codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("código %d não encontrado.\n", codigo);
        return listaProducao;
    }

    if (anterior == NULL) {
        ListaProducao *novoInicio = atual->prox;
        free(atual);
        return novoInicio;

    } else {
        anterior->prox = atual->prox;
        return listaProducao;
    }
}

ListaProducao* alterarPorCodigo(ListaProducao *listaProducao, int codigo) {
    ListaProducao *atual = listaProducao;

    while (atual != NULL && atual->dado.codigo != codigo) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("código %d não encontrado.\n", codigo);
        return listaProducao;
    }

    printf("\nalterando produção com código %d\n", codigo);

    printf("informe nova data (dd mm aaaa):\n");
    scanf("%d %d %d", &atual->dado.dataProducao.dia , &atual->dado.dataProducao.mes, &atual->dado.dataProducao.ano);

    printf("informe cultivar: ");
    fgets(atual->dado.tipoDeFardo.cultivar, CULTIVAR_TAM, stdin);
    atual->dado.tipoDeFardo.cultivar[strcspn(atual->dado.tipoDeFardo.cultivar, "\n")] = 0;

    printf("informe tipo de feno (A, B ou C): ");
    atual->dado.tipoDeFardo.tipoDeFeno = getchar();

    printf("informe diâmetro do fardo (80 a 160 cm): ");
    scanf("%d", &atual->dado.tipoDeFardo.diametro);

    printf("informe quantidade de fardos: ");
    scanf("%d", &atual->dado.qtDeFardos);

    printf("informe tempo em minutos: ");
    scanf("%d", &atual->dado.tempoEmMin);

    printf("registro alterado com sucesso.\n");
    return listaProducao;
}

void liberarLista(ListaProducao *listaProducao) {
    ListaProducao *atual = listaProducao;
    while (atual != NULL) {
        ListaProducao *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}