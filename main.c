/* 
Desenvolvido por: Marina Canal e Luiz Izycki
Matéria: Estrutura de Dados
UFFS - Chapecó 
*/

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


    printf("\n---------------------------------------------------------------------\n");
    printf("\n       |                                                              ");
    printf("\n     \\|/|/                                                            ");
    printf("\n   \\|\\\\|//|/              ███████╗    █████╗    ██████╗  █████╗       ");
    printf("\n    \\|\\|/|/               ██╔════╝   ██╔══██╗   ██╔══██╗██╔══██╗      ");
    printf("\n      \\|/                 ███████╗   ███████║   ██████╔╝███████║      ");
    printf("\n      \\|/                 ╚════██║   ██╔══██║   ██╔═══╝ ██╔══██║      ");
    printf("\n       |                  ███████║██╗██║  ██║██╗██║██╗  ██║  ██║██╗   ");
    printf("\n_ \\|/__|_\\|/____\\|/_      ╚══════╝╚═╝╚═╝  ╚═╝╚═╝╚═╝╚═╝  ╚═╝  ╚═╝╚═╝   \n\n");

    printf("----------- SISTEMA DE ACOMPANHAMENTO DE PRODUÇÃO AGRÍCOLA ----------\n");

    do {
        printf("\n1. incluir produção\n");
        printf("2. consultar por data\n");
        printf("3. consultar por cultivar\n");
        printf("4. alterar produção\n");
        printf("5. excluir produção\n");
        printf("6. listar todos\n");
        printf("7. sair\n");

        printf("\n");
        printf("---> escolha: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\ncódigo: ");
                scanf("%d", &prod.codigo);
                getchar();

                lerData(&prod.dataProducao);
                getchar();

                printf("cultivar: ");
                fgets(prod.tipoDeFardo.cultivar, CULTIVAR_TAM, stdin);

                printf("tipo de feno (A, B ou C): ");
                scanf("%c", &prod.tipoDeFardo.tipoDeFeno);

                printf("diâmetro do fardo (80 a 160 cm): ");
                scanf("%d", &prod.tipoDeFardo.diametro);

                printf("quantidade de fardos: ");
                scanf("%d", &prod.qtDeFardos);

                printf("tempo em minutos: ");
                scanf("%d", &prod.tempoEmMin);

                listaProducao = inserirOrdenadoPorData(listaProducao, prod);
                break;

            case 2:
                lerData(&dataConsulta);
                consultarPorData(listaProducao, dataConsulta);
                break;

            case 3:
                printf("\ninforme cultivar para consulta: ");
                fgets(cultivarConsulta, CULTIVAR_TAM, stdin);
                
                consultarPorCultivar(listaProducao, cultivarConsulta);
                break;

            case 4:
                printf("\ninforme o código da produção para alterar: ");
                scanf("%d", &codigoBusca);
                listaProducao = alterarPorCodigo(listaProducao, codigoBusca);
                break;

            case 5:
                printf("\ninforme o código da produção para excluir: ");
                scanf("%d", &codigoBusca);
                listaProducao = excluirPorCodigo(listaProducao, codigoBusca);
                break;

            case 6:
                listarTodos(listaProducao);
                break;

            case 7:
                liberarLista(listaProducao);
                printf("\nsaindo...\n");
                break;

            default:
                printf("opção inválida. Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
