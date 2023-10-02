#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main() {

    int  input, cod;
    ListaClientes lista;
    lista.qtd = 0;

    do {
        imprimeMenu();

        scanf("%d", &input);

        if (input == 0);
        else if (input == 1) {
            cod = cadastraCliente(&lista);

            if (cod != 0) {
                printf("Erro ao cadastrar cliente! Tente novamente em instantes..\n");
            }

            system("pause");
        } else if(input == 2) {
            //deleta
        } else if(input == 3) {
            cod = listaClientes(&lista);

            if (cod != 0) {
                printf("Nao foi possivel exibir a lista de clientes! Tente novamente em instantes..\n");
            }
            system("pause");
        } else if(input == 4) {
            //debito
        } else if(input == 5) {
            //deposito
        } else if(input == 6) {
            //extrato
        } else if(input == 7) {
            //transf
        } else {
            printf("Opcao invalida!\n\n");
        }
    } while (input != 0);
}
