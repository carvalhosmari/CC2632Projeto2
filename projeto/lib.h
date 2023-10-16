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
    int cpf;
    TipoConta tipo;
    double saldo;
    int senha;
    Transacoes extrato;
} Cliente;
typedef struct {
    Cliente carteira[1000];
    int qtd;
} ListaClientes;
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
#endif //PROJETO_LIB_H
