#include "producao_anterior.h"


int compararData(Data d1, Data d2) {
    if (d1.ano != d2.ano)
        return d1.ano - d2.ano;
    if (d1.mes != d2.mes)
        return d1.mes - d2.mes;
    return d1.dia - d2.dia;
}

int existeCodigo(Nodo *lista, int codigo) {
    while (lista != NULL) {
        if (lista->dado.codigo == codigo)
            return 1;
        lista = lista->prox;
    }
    return 0;
}

// Insere produção na lista ordenada por data, sem repetir código
Nodo* inserirOrdenado(Nodo *lista, Producao prod, int *sucesso) {
    *sucesso = 0;

    if (existeCodigo(lista, prod.codigo)) {
        printf("Já existe uma produção com o código %d.\n", prod.codigo);
        return lista;
    }

    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        return lista;
    }

    novo->dado = prod;
    novo->prox = NULL;

    if (lista == NULL || compararData(prod.dataProducao, lista->dado.dataProducao) < 0) {
        novo->prox = lista;
        *sucesso = 1;
        return novo;
    }

    Nodo *atual = lista;
    while (atual->prox != NULL && compararData(prod.dataProducao, atual->prox->dado.dataProducao) >= 0) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
    *sucesso = 1;

    return lista;
}

// Lista todas as produções cadastradas
void listarTodos(Nodo *lista) {
    if (lista == NULL) {
        printf("Nenhuma produção registrada.\n");
        return;
    }

    printf("Lista de produções:\n");

    Nodo *atual = lista;
    while (atual != NULL) {
        Producao p = atual->dado;
        printf("Código: %d | Data: %02d/%02d/%04d | Cultivar: %s | Tipo: %c\n",
               p.codigo,
               p.dataProducao.dia, p.dataProducao.mes, p.dataProducao.ano,
               p.tipoDeFardo.cultivar,
               p.tipoDeFardo.tipoDeFeno);
        printf("Diâmetro: %d cm | Qtde de Fardos: %d | Tempo: %d min\n\n",
               p.tipoDeFardo.diametro,
               p.qtDeFardos,
               p.tempoEmMin);
        atual = atual->prox;
    }
}

// Calcula área mínima para armazenar os fardos (com 20% de perda)
float calcularAreaMinima(int diametro, int qtFardos) {
    float raio = (diametro / 100.0) / 2.0; // converte cm pra metro e divide por 2
    int colunas = (qtFardos + 2) / 3;      // 3 fardos por coluna
    float areaBase = 3.141592653589793 * raio * raio;
    float areaComPerda = areaBase * 1.2;  // 20% de espaço vazio
    return colunas * areaComPerda;
}

// Lê uma data do teclado (formato dd mm aaaa)
void lerData(Data *d) {
    printf("Informe a data (dd mm aaaa): ");
    scanf("%d %d %d", &d->dia, &d->mes, &d->ano);
}

// Limpa buffer do teclado para evitar erro em scanf
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Consulta produções por data exata
void consultarPorData(Nodo *lista, Data data) {
    int achou = 0;
    Nodo *atual = lista;

    while (atual != NULL) {
        if (compararData(atual->dado.dataProducao, data) == 0) {
            Producao p = atual->dado;
            printf("%02d/%02d/%04d: %s - %c - %d fardos\n",
                   p.dataProducao.dia, p.dataProducao.mes, p.dataProducao.ano,
                   p.tipoDeFardo.cultivar,
                   p.tipoDeFardo.tipoDeFeno,
                   p.qtDeFardos);
            achou = 1;
        }
        atual = atual->prox;
    }

    if (!achou) {
        printf("Nenhuma produção encontrada para essa data.\n");
    }
}
void consultarPorCultivar(Nodo *lista, const char *cultivarBuscado) {
    if (lista == NULL) {
        printf("Nenhum registro disponível.\n");
        return;
    }

    // Para armazenar a soma de fardos por tipo de feno
    int somaA = 0, somaB = 0, somaC = 0;
    int diamA = 0, diamB = 0, diamC = 0;  // pra calcular a área, guardamos o último diâmetro encontrado

    Nodo *atual = lista;
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
        printf("Nenhum registro encontrado para a cultivar '%s'.\n", cultivarBuscado);
        return;
    }

    printf("Resultados para cultivar '%s':\n", cultivarBuscado);

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

Nodo* excluirPorCodigo(Nodo *lista, int codigo, int *sucesso) {
    *sucesso = 0;
    if (lista == NULL) return NULL;

    Nodo *atual = lista;
    Nodo *ant = NULL;

    while (atual != NULL && atual->dado.codigo != codigo) {
        ant = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Código %d não encontrado.\n", codigo);
        return lista;
    }

    if (ant == NULL) {
        // Excluir o primeiro da lista
        Nodo *novo_inicio = atual->prox;
        free(atual);
        *sucesso = 1;
        return novo_inicio;
    } else {
        ant->prox = atual->prox;
        free(atual);
        *sucesso = 1;
        return lista;
    }
}

Nodo* alterarPorCodigo(Nodo *lista, int codigo, int *sucesso) {
    *sucesso = 0;
    Nodo *atual = lista;

    while (atual != NULL && atual->dado.codigo != codigo) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Código %d não encontrado.\n", codigo);
        return lista;
    }

    printf("Alterando produção com código %d\n", codigo);

    printf("Informe nova data:\n");
    lerData(&atual->dado.dataProducao);
    limparBuffer();

    printf("Informe cultivar: ");
    fgets(atual->dado.tipoDeFardo.cultivar, CULTIVAR_TAM, stdin);
    atual->dado.tipoDeFardo.cultivar[strcspn(atual->dado.tipoDeFardo.cultivar, "\n")] = 0;

    printf("Informe tipo de feno (A, B ou C): ");
    atual->dado.tipoDeFardo.tipoDeFeno = getchar();
    limparBuffer();

    printf("Informe diâmetro do fardo (80 a 160 cm): ");
    scanf("%d", &atual->dado.tipoDeFardo.diametro);
    limparBuffer();

    printf("Informe quantidade de fardos: ");
    scanf("%d", &atual->dado.qtDeFardos);
    limparBuffer();

    printf("Informe tempo em minutos: ");
    scanf("%d", &atual->dado.tempoEmMin);
    limparBuffer();

    *sucesso = 1;
    printf("Registro alterado com sucesso.\n");
    return lista;
}

void liberarLista(Nodo *lista) {
    Nodo *atual = lista;
    while (atual != NULL) {
        Nodo *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}