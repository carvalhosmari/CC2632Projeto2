#include <stdio.h>
#include "lib.h"

int main() {

    int  input;

    do {
        imprimeMenu();

        scanf("%d", &input);

        if (input == 0);
        else if (input == 1) {
            //cadastrar novo cliente
        } else if(input == 2) {
            //apagar cliente
        } else if(input == 3) {
            //listar clientes
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
