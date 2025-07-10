#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "producao.h"

int main() {
    Nodo *lista = NULL;
    int opcao, sucesso;
    Producao prod;
    Data dataConsulta;
    char cultivarConsulta[CULTIVAR_TAM];
    int codigoBusca;

    do {
        printf("\n--- Sistema de Produção de Feno ---\n");
        printf("1. Incluir Produção\n");
        printf("2. Consultar por Data\n");
        printf("3. Consultar por Cultivar\n");
        printf("4. Alterar Produção\n");
        printf("5. Excluir Produção\n");
        printf("6. Listar Todos\n");
        printf("7. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                printf("Código: ");
                scanf("%d", &prod.codigo);
                limparBuffer();

                lerData(&prod.dataProducao);
                limparBuffer();

                printf("Cultivar: ");
                fgets(prod.tipoDeFardo.cultivar, CULTIVAR_TAM, stdin);
                prod.tipoDeFardo.cultivar[strcspn(prod.tipoDeFardo.cultivar, "\n")] = 0;

                printf("Tipo de feno (A, B ou C): ");
                prod.tipoDeFardo.tipoDeFeno = getchar();
                limparBuffer();

                printf("Diâmetro do fardo (80 a 160 cm): ");
                scanf("%d", &prod.tipoDeFardo.diametro);
                limparBuffer();

                printf("Quantidade de fardos: ");
                scanf("%d", &prod.qtDeFardos);
                limparBuffer();

                printf("Tempo em minutos: ");
                scanf("%d", &prod.tempoEmMin);
                limparBuffer();

                lista = inserirOrdenado(lista, prod, &sucesso);
                if (sucesso) printf("Produção incluída com sucesso.\n");
                break;

            case 2:
                lerData(&dataConsulta);
                limparBuffer();
                consultarPorData(lista, dataConsulta);
                break;

            case 3:
                printf("Informe cultivar para consulta: ");
                fgets(cultivarConsulta, CULTIVAR_TAM, stdin);
                cultivarConsulta[strcspn(cultivarConsulta, "\n")] = 0;
                consultarPorCultivar(lista, cultivarConsulta);
                break;

            case 4:
                printf("Informe o código da produção para alterar: ");
                scanf("%d", &codigoBusca);
                limparBuffer();
                lista = alterarPorCodigo(lista, codigoBusca, &sucesso);
                break;

            case 5:
                printf("Informe o código da produção para excluir: ");
                scanf("%d", &codigoBusca);
                limparBuffer();
                lista = excluirPorCodigo(lista, codigoBusca, &sucesso);
                if (sucesso) printf("Produção excluída com sucesso.\n");
                break;

            case 6:
                listarTodos(lista);
                break;

            case 7:
                liberarLista(lista);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
