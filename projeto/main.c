#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main() {

    int  input, cod;
    ListaClientes lista;

    cod = carregaListaClientes(&lista, "arquivo");

    if (cod != 0) {
        lista.qtd = 0;
    }

    do {
        imprimeMenu();

        scanf("%d", &input);

        if (input == 0);
        else if (input == 1) {
            cod = cadastraCliente(&lista);

            if (cod != 0) {
                printf("Erro ao cadastrar cliente! Tente novamente em instantes..\n\n");
            } else {
                cod = salvaListaClientes(&lista, "arquivo");

                if (cod == 0) {
                    printf("Cliente cadastrado com sucesso!\n\n");
                } else {
                    printf("Erro na abertura do arquivo de destino.\n\n");
                }
            }

            system("pause");

        } else if(input == 2) {
            cod = deletaCliente(&lista);

            if (cod == 1) {
                printf("Cliente nao encontrado!\n\n");
            } else if (cod != 0) {
                printf("Nao foi possivel deletar o cliente! Tente novamente em instantes..\n\n");
            } else {
                printf("Cliente deletado com sucesso!\n\n");
                salvaListaClientes(&lista, "arquivo");
            }

            system("pause");

        } else if(input == 3) {
            cod = listaClientes(&lista);

            if (cod == 0) {
            } else if (cod == 1) {
                printf("Lista de clientes vazia.\n\n");
            } else {
                printf("Nao foi possivel exibir a lista de clientes! Tente novamente em instantes..\n\n");
            }

            system("pause");

        } else if(input == 4) {
            cod = debitaValor(&lista);

            if (cod == -1) {
                printf("CPF invalido!\n\n");
            } else if (cod == 0) {
                printf("Valor debitado com sucesso!\n\n");
                salvaListaClientes(&lista, "arquivo");
            } else if (cod == -2) {
                printf("Senha incorreta!\n\n");
            }

            system("pause");

        } else if(input == 5) {
            cod = depositaValor(&lista);

            if (cod == -1) {
                printf("CPF invalido!\n\n");
            } else if (cod == 0) {
                printf("Valor depositado com sucesso!\n\n");
                salvaListaClientes(&lista, "arquivo");
            }

            system("pause");

        } else if(input == 6) {
            //extrato
        } else if(input == 7) {
            //transf
        } else {
            printf("Opcao invalida!\n\n");
        }
    } while (input != 0);
}
