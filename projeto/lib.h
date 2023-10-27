//
// Created by Mariane on 01/10/2023.
//

#ifndef PROJETO_LIB_H
#define PROJETO_LIB_H
// Enumeração que define os tipos de conta: comum ou plus
typedef enum {
    comum = 1,
    plus
} TipoConta;

// Enumeração que define os tipos de operação: débito, depósito ou transferência
typedef enum {
    debito = 1,
    deposito,
    transferencia
} TipoOperacao;

// Estrutura que representa uma data e hora
typedef struct {
    int dia;
    int mes;
    int ano;
    int hora;
    int min;
    int seg;
} Data;

// Estrutura que representa uma operação (transação)
typedef struct {
    TipoOperacao tipo;
    double valor;
    double saldoAtualizado;
    Data dataTransacao;
} Operacao;

// Estrutura que mantém uma lista de transações de um cliente
typedef struct {
    Operacao lista[100];
    int qtd;
} Transacoes;

// Estrutura que representa um cliente
typedef struct {
    char nome[150];
    int cpf;
    TipoConta tipo;
    double saldo;
    int senha;
    Transacoes extrato;
} Cliente;

// Estrutura que mantém uma lista de clientes
typedef struct {
    Cliente carteira[10];
    int qtd;
} ListaClientes;

// Declarações de funções utilizadas no sistema bancário
void imprimeMenu();
int cadastraCliente(ListaClientes *lc);
int listaClientes(ListaClientes *lc);
int deletaCliente(ListaClientes *lc);
int salvaListaClientes(ListaClientes *lc, char *arquivo);
int carregaListaClientes(ListaClientes *lc, char *arquivo);
int depositaValor(ListaClientes *lc);
int retornaIndiceCliente(ListaClientes *lc, int cpf);
int debitaValor(ListaClientes *lc);
int transfereValor(ListaClientes *lc);
int registraTransacao(Cliente *c, TipoOperacao tipoOperacao, double valor);
int listaTransacoes(ListaClientes *lc);
int geraExtrato(Cliente *c);
int verificaSaldo(Cliente *c, double valor);
int registraData(Data *dt);
#endif //PROJETO_LIB_H
