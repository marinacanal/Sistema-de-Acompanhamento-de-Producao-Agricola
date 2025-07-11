#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas/producao.h"

int main() {
    ListaProducao *listaProducao = NULL;
    Producao prod;
    Data dataConsulta;
    int opcao, sucesso, codigoBusca;
    char cultivarConsulta[CULTIVAR_TAM];

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

        switch (opcao) {
            case 1:
                printf("Código: ");
                scanf("%d", &prod.codigo);

                lerData(&prod.dataProducao);

                printf("Cultivar: ");
                fgets(prod.tipoDeFardo.cultivar, CULTIVAR_TAM, stdin);
                prod.tipoDeFardo.cultivar[strcspn(prod.tipoDeFardo.cultivar, "\n")] = 0;

                printf("Tipo de feno (A, B ou C): ");
                prod.tipoDeFardo.tipoDeFeno = getchar();

                printf("Diâmetro do fardo (80 a 160 cm): ");
                scanf("%d", &prod.tipoDeFardo.diametro);

                printf("Quantidade de fardos: ");
                scanf("%d", &prod.qtDeFardos);

                printf("Tempo em minutos: ");
                scanf("%d", &prod.tempoEmMin);

                listaProducao = inserir(listaProducao, prod, &sucesso);
                if (sucesso) printf("Produção incluída com sucesso.\n");
                break;

            case 2:
                lerData(&dataConsulta);
                consultarPorData(listaProducao, dataConsulta);
                break;

            case 3:
                printf("Informe cultivar para consulta: ");
                fgets(cultivarConsulta, CULTIVAR_TAM, stdin);
                cultivarConsulta[strcspn(cultivarConsulta, "\n")] = 0;
                consultarPorCultivar(listaProducao, cultivarConsulta);
                break;

            case 4:
                printf("Informe o código da produção para alterar: ");
                scanf("%d", &codigoBusca);
                listaProducao = alterarPorCodigo(listaProducao, codigoBusca, &sucesso);
                break;

            case 5:
                printf("Informe o código da produção para excluir: ");
                scanf("%d", &codigoBusca);
                listaProducao = excluirPorCodigo(listaProducao, codigoBusca, &sucesso);
                if (sucesso) printf("Produção excluída com sucesso.\n");
                break;

            case 6:
                listarTodos(listaProducao);
                break;

            case 7:
                liberarLista(listaProducao);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
