//
// Created by Mariane on 01/10/2023.
//

#ifndef PROJETO_LIB_H
#define PROJETO_LIB_H
typedef enum {
    comum = 1,
    plus
} TipoConta;
typedef enum {
    debito = 1,
    deposito,
    saque,
    transferencia
} TipoOperacao;
typedef struct {
    TipoOperacao tipo;
    double valor;
} Operacao;
typedef struct {
    Operacao lista[100];
    int qtd;
} Transacoes;
typedef struct {
    char nome[150];
    char cpf[11];
    TipoConta tipo;
    double saldo;
    char senha[15];
    Transacoes extrato;
} Cliente;
typedef struct {
    Cliente carteira[1000];
    int qtd;
} ListaClientes;
void imprimeMenu();
int cadastraCliente(ListaClientes *lt);
#endif //PROJETO_LIB_H
