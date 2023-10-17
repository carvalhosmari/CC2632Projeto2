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

int cadastraCliente(ListaClientes *lc) {
    Cliente *cl = &lc->carteira[lc->qtd];
    Transacoes *tr = &cl->extrato;

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

    printf("Digite uma senha de 4 digitos: ");
    scanf("%d", &cl->senha);

    tr->qtd = 0;
    lc->qtd++;

    return 0;
}

int listaClientes(ListaClientes *lc) {
    if (lc->qtd == 0) {
        return 1;
    }

    for (int i = 0; i < lc->qtd; i++) {
        printf("Cliente [%d]: \n", (i + 1));
        printf("\tNome: %s\n\tCPF: %d\n\tTipo de conta: %d\n\tSaldo: R$ %.2lf\n", lc->carteira[i].nome, lc->carteira[i].cpf, lc->carteira[i].tipo, lc->carteira[i].saldo);
    }

    return 0;
}

int deletaCliente(ListaClientes *lc) {
    int indiceCliente, cpf;

    printf("Digite o CPF do cliente que sera excluido: ");
    scanf("%d", &cpf);

    indiceCliente = retornaIndiceCliente(lc, cpf);

    for (int i = 0; i < lc->qtd; i++) {
        if (indiceCliente != -1 && indiceCliente <= i) {
            lc->carteira[i] = lc->carteira[(i + 1)];
        }
    }

    if (indiceCliente == -1) {
        return 1;
    }

    lc->qtd--;

    return 0;
}

int salvaListaClientes(ListaClientes *lc, char *arquivo) {
    FILE *f = fopen(arquivo, "wb");

    if (f == NULL) {
        return 1;
    }

    fwrite(lc, sizeof(ListaClientes), 1, f);

    fclose(f);

    return 0;
}

int carregaListaClientes(ListaClientes *lc, char *arquivo) {
    FILE  *f = fopen(arquivo, "rb");

    if (f == NULL) {
        return 1;
    }

    fread(lc, sizeof(ListaClientes), 1, f);

    fclose(f);

    return 0;
}

int depositaValor(ListaClientes *lc) {
    int cpfDestino, indiceCliente;
    double valorDeposito;

    printf("Digite o CPF da conta de destino: ");
    scanf("%d", &cpfDestino);

    indiceCliente = retornaIndiceCliente(lc, cpfDestino);

    if (indiceCliente == -1) {
        return -1;
    } else if (indiceCliente >= 0) {
        printf("Digite o valor a ser depositado: ");
        scanf("%lf", &valorDeposito);

        lc->carteira[indiceCliente].saldo += valorDeposito;
        registraTransacao(&lc->carteira[indiceCliente], 2, valorDeposito);
    }

    return  0;
}

int retornaIndiceCliente(ListaClientes *lc, int cpf) {
    int indiceCliente = -1;

    for (int i = 0; i < lc->qtd; i++) {
        if (cpf == lc->carteira[i].cpf) {
            indiceCliente = i;
            break;
        }
    }

    return indiceCliente;
}

int debitaValor(ListaClientes *lc) {
    int indiceCliente, cpf, senha;
    double valor, taxa;

    printf("CPF do cliente: ");
    scanf("%d", &cpf);

    indiceCliente = retornaIndiceCliente(lc, cpf);

    if (indiceCliente == -1) {
        return -1;
    } else {
        printf("Senha: ");
        scanf("%d", &senha);

        if (senha != lc->carteira[indiceCliente].senha) {
            return -2;
        } else {
            printf("Valor a ser debitado: ");
            scanf("%lf", &valor);

            if (lc->carteira[indiceCliente].tipo == 1) {
                taxa = 1.05;
            } else {
                taxa = 1.03;
            }

            lc->carteira[indiceCliente].saldo -= (valor * taxa);
            registraTransacao(&lc->carteira[indiceCliente], 1, (valor * -1));
        }
    }

    return 0;
}

int transfereValor(ListaClientes *lc) {
    int indiceCliente1, indiceCliente2, cpf1, cpf2;
    int senha;
    double valor;

    printf("CPF do titular da conta de origem: ");
    scanf("%d", &cpf1);

    indiceCliente1 = retornaIndiceCliente(lc, cpf1);

    if (indiceCliente1 == -1) {
        return -1;
    } else {
        printf("Senha: ");
        scanf("%d", &senha);

        if (senha != lc->carteira[indiceCliente1].senha) {
            return -2;
        } else {
            printf("CPF do titular da conta de destino: ");
            scanf("%d", &cpf2);

            indiceCliente2 = retornaIndiceCliente(lc, cpf2);

            if (indiceCliente2 == -1) {
                return -1;
            } else {
                printf("Valor a ser transferido: ");
                scanf("%lf", &valor);

                lc->carteira[indiceCliente1].saldo -= valor;
                registraTransacao(&lc->carteira[indiceCliente1], 3, (valor * -1));

                lc->carteira[indiceCliente2].saldo += valor;
                registraTransacao(&lc->carteira[indiceCliente2], 3, valor);
            }
        }
    }
    return 0;
}

int registraTransacao(Cliente *c, TipoOperacao tipoOperacao, double valor) {
    Transacoes *tr = &c->extrato;
    Operacao *op = &tr->lista[tr->qtd];

    op->valor = valor;
    op->tipo = tipoOperacao;

    tr->qtd++;

    return 0;
}

int listaTransacoes(ListaClientes *lc) {
    int cpf, senha, indiceCliente;

    printf("CPF do cliente: ");
    scanf("%d", &cpf);

    indiceCliente = retornaIndiceCliente(lc, cpf);

    Transacoes *tr = &lc->carteira[indiceCliente].extrato;

    if (indiceCliente == -1) {
        return -1;
    } else {
        printf("Senha: ");
        scanf("%d", &senha);

        if (senha != lc->carteira[indiceCliente].senha) {
            return -2;
        } else {
            for (int i = 0; i < tr->qtd; i++) {
                char *tipo;
                double tarifa = 0;
                double valorTransacao = tr->lista[i].valor / (1 + tarifa);

                if (tr->lista[i].tipo == 1) {
                    tipo = "debito";

                    if (lc->carteira[indiceCliente].tipo == 1) {
                        tarifa = 0.05;
                    } else if (lc->carteira[indiceCliente].tipo == 2) {
                        tarifa = 0.03;
                    }
                } else if (tr->lista[i].tipo == 2) {
                    tipo = "deposito";
                } else {
                    if (tr->lista[i].valor < 0) {
                        tipo = "transferencia enviada";
                    } else {
                        tipo = "transferencia recebida";
                    }
                }
                printf("--------------------------------------------------\n");
                printf("tipo: %s\n", tipo);
                printf("valor: R$\t%.2lf\ntarifa: %12.0lf%%\ntotal: R$\t%.2lf\n", valorTransacao, (tarifa * 100),  tr->lista[i].valor + (valorTransacao * tarifa));
            }
            geraExtrato(&lc->carteira[indiceCliente]);
            return 0;
        }
    }
}

int geraExtrato(Cliente *c) {
    Transacoes *tr = &c->extrato;
    FILE *f = fopen("extrato.txt", "w");

    for (int i = 0; i < tr->qtd; i++) {
        char *tipo;
        double tarifa = 0;
        double valorTransacao = tr->lista[i].valor / (1 + tarifa);

        if (tr->lista[i].tipo == 1) {
            tipo = "debito";

            if (c->tipo == 1) {
                tarifa = 0.05;
            } else if (c->tipo == 2) {
                tarifa = 0.03;
            }
        } else if (tr->lista[i].tipo == 2) {
            tipo = "deposito";
        } else {
            if (tr->lista[i].valor < 0) {
                tipo = "transferencia enviada";
            } else {
                tipo = "transferencia recebida";
            }
        }

        fprintf(f, "tipo: %s\n", tipo);
        fprintf(f, "valor: R$ %.2lf\n", valorTransacao);
        fprintf(f, "tarifa: %.0lf%%\n", (tarifa * 100));
        fprintf(f, "total: R$ %.2lf\n", tr->lista[i].valor + (valorTransacao * tarifa));
        fprintf(f, "-------------------------------\n");
    }

    fclose(f);

    return 0;
}

