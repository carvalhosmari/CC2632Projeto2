//
// Created by Mariane on 01/10/2023.
//

#include "lib.h"
#include <stdio.h>

void imprimeMenu() {
    printf("\n********************************************\n");
    printf("********   BANCO QUEM POUPA TEM!!   ********\n");
    printf("********************************************\n\n");
    printf("O que voce gostaria de fazer?\n\n");
    printf("\t1 - Novo cliente\n\t2 - Apagar cliente\n\t3 - Listar clientes\n\t4 - Debito\n\t5 - Deposito\n\t6 - Extrato\n\t7 - Transferencia entre contas\n\t0 - Sair\n\n");
    printf("digite sua opcao: ");
}

int cadastraCliente(ListaClientes *lt) {
    Cliente *cl = &lt->carteira[lt->qtd];

    fgetc(stdin);
    printf("Digite o nome do cliente: ");
    scanf("%[^\n]", cl->nome);

    fgetc(stdin);
    printf("Digite o cpf (somente numeros): ");
    scanf("%d", &cl->cpf);

    printf("Digite o tipo da conta: \n\t1 - Comum\n\t2 - Plus\n");
    scanf("%d", &cl->tipo);

    printf("Digite o saldo inicial da conta: ");
    scanf("%lf", &cl->saldo);

    printf("Digite uma senha de ate 15 caracteres: ");
    scanf("%s", cl->senha);

    lt->qtd++;

    return 0;
}

int listaClientes(ListaClientes *lt) {
    for (int i = 0; i < lt->qtd; i++) {
        printf("Cliente [%d]: \n", (i + 1));
        printf("\tNome: %s\n\tCPF: %d\n\tTipo de conta: %d\n\tSaldo: R$ %.2lf\n", lt->carteira[i].nome, lt->carteira[i].cpf, lt->carteira[i].tipo, lt->carteira[i].saldo);
    }

    return 0;
}

int deletaCliente(ListaClientes *lt, int cpf) {
    int indiceCliente = -1;

    for (int i = 0; i < lt->qtd; i++) {
        if (cpf == lt->carteira[i].cpf) {
            indiceCliente = i;
            break;
        }
    }

    for (int i = 0; i < lt->qtd; i++) {
        if (indiceCliente != -1 && indiceCliente <= i) {
            lt->carteira[i] = lt->carteira[(i + 1)];
        }
    }

    if (indiceCliente == -1) {
        return 1;
    }

    lt->qtd--;

    return 0;
}