//
// Created by Mariane on 01/10/2023.
//

#include "lib.h"
#include <stdio.h>
#include <time.h>

// Função para exibir o menu de opções
void imprimeMenu() {
    // Exibe um menu de opções para o usuário
    printf("\n********************************************\n");
    printf("********   BANCO QUEM POUPA TEM!!   ********\n");
    printf("********************************************\n\n");
    printf("O que voce gostaria de fazer?\n\n");
    printf("\t1 - Novo cliente\n\t2 - Apagar cliente\n\t3 - Listar clientes\n\t4 - Debito\n\t5 - Deposito\n\t6 - Extrato\n\t7 - Transferencia entre contas\n\t0 - Sair\n\n");
    printf("digite sua opcao: ");
}

// Função para cadastrar um novo cliente
int cadastraCliente(ListaClientes *lc) {
    Cliente *cl = &lc->carteira[lc->qtd];
    Transacoes *tr = &cl->extrato;

    // Solicita informações do cliente, como nome, CPF, tipo de conta, saldo inicial e senha
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

    printf("Digite uma senha de 4 digitos numericos: ");
    scanf("%d", &cl->senha);

    // Inicializa o extrato do cliente e registra como deposito a transação de abertura da conta (saldo inicial)
    tr->qtd = 0;
    registraTransacao(cl, 2, cl->saldo);

    //incrementa a lista de clientes
    lc->qtd++;

    return 0;
}

// Função para listar todos os clientes
int listaClientes(ListaClientes *lc) {
    if (lc->qtd == 0) {
        // Se não houver clientes, retorna um código de erro
        return 1;
    }

    // Lista informações de todos os clientes, incluindo nome, CPF, tipo de conta e saldo
    for (int i = 0; i < lc->qtd; i++) {
        char *tipo;

        if (lc->carteira[i].tipo == 1) {
            tipo = "comum";
        } else {
            tipo = "plus";
        }
        printf("Cliente [%d]: \n", (i + 1));
        printf("\tNome: %s\n\tCPF: %d\n\tTipo de conta: %s\n\tSaldo: R$ %.2lf\n", lc->carteira[i].nome, lc->carteira[i].cpf, tipo, lc->carteira[i].saldo);
    }

    printf("\n");

    return 0;
}

// Função para excluir um cliente
int deletaCliente(ListaClientes *lc) {
    int indiceCliente, cpf;

    // Solicita o CPF do cliente que será excluído
    printf("Digite o CPF do cliente que sera excluido: ");
    scanf("%d", &cpf);

    // Encontra o índice do cliente na lista com base no CPF
    indiceCliente = retornaIndiceCliente(lc, cpf);

    // Move os clientes à direita do cliente excluído para ocupar seu lugar
    for (int i = 0; i < lc->qtd; i++) {
        if (indiceCliente != -1 && indiceCliente <= i) {
            lc->carteira[i] = lc->carteira[(i + 1)];
        }
    }

    // Decrementa a quantidade de clientes na lista
    lc->qtd--;

    // Retorna um código de erro se o cliente não foi encontrado
    if (indiceCliente == -1) {
        return 1;
    }

    return 0;
}

// Função para salvar a lista de clientes em um arquivo binário
int salvaListaClientes(ListaClientes *lc, char *arquivo) {
    FILE *f = fopen(arquivo, "wb");

    // Verifica se o arquivo foi aberto com sucesso
    if (f == NULL) {
        // Se o arquivo não pode ser aberto, retorna um código de erro
        return 1;
    }

    // Escreve a lista de clientes no arquivo binário
    fwrite(lc, sizeof(ListaClientes), 1, f);

    // Fecha o arquivo
    fclose(f);

    return 0;
}

// Função para carregar a lista de clientes de um arquivo binário
int carregaListaClientes(ListaClientes *lc, char *arquivo) {
    FILE  *f = fopen(arquivo, "rb");

    // Verifica se o arquivo foi aberto com sucesso
    if (f == NULL) {
        // Se o arquivo não pode ser aberto, retorna um código de erro
        return 1;
    }

    // Lê a lista de clientes do arquivo binário
    fread(lc, sizeof(ListaClientes), 1, f);

    // Fecha o arquivo
    fclose(f);

    return 0;
}

// Função para fazer um depósito em uma conta
int depositaValor(ListaClientes *lc) {
    int cpfDestino, indiceCliente;
    double valorDeposito;

    // Solicita o CPF da conta de destino para o depósito
    printf("Digite o CPF da conta de destino: ");
    scanf("%d", &cpfDestino);

    // Encontra o cliente na lista com base no CPF
    indiceCliente = retornaIndiceCliente(lc, cpfDestino);

    // Se o cliente de destino não for encontrado, retorna um código de erro
    if (indiceCliente == -1) {
        return -1;
    } else if (indiceCliente >= 0) {
        // Solicita o valor a ser depositado
        printf("Digite o valor a ser depositado: ");
        scanf("%lf", &valorDeposito);

        // Atualiza o saldo da conta de destino e registra a transação no extrato
        lc->carteira[indiceCliente].saldo += valorDeposito;
        registraTransacao(&lc->carteira[indiceCliente], 2, valorDeposito);
    }

    return 0;
}

// Função para retornar o índice de um cliente com base no CPF
int retornaIndiceCliente(ListaClientes *lc, int cpf) {
    int indiceCliente = -1;

    // Procura o índice do cliente na lista com base no CPF fornecido
    for (int i = 0; i < lc->qtd; i++) {
        if (cpf == lc->carteira[i].cpf) {
            indiceCliente = i;
            break;
        }
    }

    //retorna a posicao do cliente na lista e caso o mesmo nao esteja cadastrado, retorna -1
    return indiceCliente;
}

// Função para fazer um débito em uma conta
int debitaValor(ListaClientes *lc) {
    int indiceCliente, cpf, senha;
    double valor, valorFinal;

    // Solicita o CPF do cliente para o débito
    printf("CPF do cliente: ");
    scanf("%d", &cpf);

    // Encontra o índice do cliente com base no CPF
    indiceCliente = retornaIndiceCliente(lc, cpf);

    // Se o cliente não for encontrado, retorna um código de erro
    if (indiceCliente == -1) {
        return -1;
    } else {
        // Solicita a senha para autorizar o débito
        printf("Senha: ");
        scanf("%d", &senha);

        // Verifica se a senha é válida
        if (senha != lc->carteira[indiceCliente].senha) {
            return -2; //caso a senha esteja incorreta, retorna codigo de erro
        } else {
            // Solicita o valor a ser debitado
            printf("Valor a ser debitado: ");
            scanf("%lf", &valor);

            // Calcula o valor final com base no tipo de conta
            if (lc->carteira[indiceCliente].tipo == 1) {
                valorFinal = valor * 1.05; //caso cliente tenha conta tipo comum, uma taxa de 5% e cobrada a cada debito
            } else {
                valorFinal = valor * 1.03; //caso cliente tenha conta tipo plus, uma taxa de 3% e cobrada a cada debito
            }

            // Verifica se o saldo é suficiente e registra a transação no extrato
            if (verificaSaldo(&lc->carteira[indiceCliente], valorFinal) == -3) {
                return -3; //caso não haja saldo disponivel, contando com cheque especial, retorna codigo de erro
            }

            // Atualiza o saldo da conta e registra a transação
            lc->carteira[indiceCliente].saldo -= valorFinal;
            registraTransacao(&lc->carteira[indiceCliente], 1, (valor * -1));
        }
    }

    return 0;
}

// Função para realizar uma transferência entre contas
int transfereValor(ListaClientes *lc) {
    int indiceCliente1, indiceCliente2, cpf1, cpf2;
    int senha;
    double valor;

    // Solicita o CPF do titular da conta de origem
    printf("CPF do titular da conta de origem: ");
    scanf("%d", &cpf1);

    // Encontra o índice do cliente de origem com base no CPF
    indiceCliente1 = retornaIndiceCliente(lc, cpf1);

    // Se o cliente de origem não for encontrado, retorna um código de erro
    if (indiceCliente1 == -1) {
        return -1;
    } else {
        // Solicita a senha para autorizar a transferência
        printf("Senha: ");
        scanf("%d", &senha);

        // Verifica se a senha é válida
        if (senha != lc->carteira[indiceCliente1].senha) {
            return -2; //caso a senha esteja incorreta, retorna codigo de erro
        } else {
            // Solicita o CPF do titular da conta de destino
            printf("CPF do titular da conta de destino: ");
            scanf("%d", &cpf2);

            // Encontra o índice do cliente de destino com base no CPF
            indiceCliente2 = retornaIndiceCliente(lc, cpf2);

            // Se o cliente de destino não for encontrado, retorna um código de erro
            if (indiceCliente2 == -1) {
                return -1;
            } else {
                // Solicita o valor a ser transferido
                printf("Valor a ser transferido: ");
                scanf("%lf", &valor);

                // Verifica se o saldo é suficiente na conta de origem
                if (verificaSaldo(&lc->carteira[indiceCliente1], valor) == -3) {
                    return -3; //caso não haja saldo disponivel, contando com cheque especial, retorna codigo de erro
                }

                // Atualiza o saldo das contas envolvidas e registra as transações
                lc->carteira[indiceCliente1].saldo -= valor;
                registraTransacao(&lc->carteira[indiceCliente1], 3, (valor * -1));

                lc->carteira[indiceCliente2].saldo += valor;
                registraTransacao(&lc->carteira[indiceCliente2], 3, valor);
            }
        }
    }
    return 0;
}

// Função para registrar uma transação no extrato de um cliente
int registraTransacao(Cliente *c, TipoOperacao tipoOperacao, double valor) {
    Transacoes *tr = &c->extrato;
    Operacao *op = &tr->lista[tr->qtd];

    // Preenche os detalhes da transação, como valor, tipo de operação e saldo atualizado
    op->valor = valor;
    op->tipo = tipoOperacao;
    op->saldoAtualizado = c->saldo;

    // Registra a data e hora da transação
    registraData(&op->dataTransacao);

    // Atualiza o contador de transações no extrato do cliente
    tr->qtd++;

    return 0;
}

// Função para listar as transações de um cliente
int listaTransacoes(ListaClientes *lc) {
    int cpf, senha, indiceCliente;

    // Solicita o CPF do cliente cujas transações serão listadas
    printf("CPF do cliente: ");
    scanf("%d", &cpf);

    // Encontra o índice do cliente com base no CPF
    indiceCliente = retornaIndiceCliente(lc, cpf);

    Transacoes *tr = &lc->carteira[indiceCliente].extrato;

    // Se o cliente não for encontrado, retorna um código de erro
    if (indiceCliente == -1) {
        return -1;
    } else {
        // Solicita a senha para acesso às transações
        printf("Senha: ");
        scanf("%d", &senha);

        // Verifica se a senha é válida
        if (senha != lc->carteira[indiceCliente].senha) {
            return -2;
        } else {
            // Exibe informações detalhadas das transações do cliente
            printf("\nNome: %s\n", lc->carteira[indiceCliente].nome);
            printf("CPF: %d\n", lc->carteira[indiceCliente].cpf);

            // Determina o tipo de conta do cliente
            if (lc->carteira[indiceCliente].tipo == 1) {
                printf("Tipo de conta: comum\n");
            } else {
                printf("Tipo de conta: plus\n");
            }

            // Itera sobre as transações e exibe os detalhes
            for (int i = 0; i < tr->qtd; i++) {
                double tarifa = 0;
                double valorTransacao = tr->lista[i].valor / (1 + tarifa);
                char *tipo;

                // Determina o tipo de transação e, se for débito, calcula a tarifa
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

                // Exibe detalhes da transação, incluindo data, tipo, valor, tarifa e saldo atualizado apos a transacao
                printf("--------------------------------------------------------\n");
                printf("%0d/%0d/%0d %0dh%0dm%0ds\t%s\n", tr->lista[i].dataTransacao.dia, tr->lista[i].dataTransacao.mes, tr->lista[i].dataTransacao.ano, tr->lista[i].dataTransacao.hora, tr->lista[i].dataTransacao.min, tr->lista[i].dataTransacao.seg, tipo);
                printf("\t R$ %.2lf\t tarifa: %.0lf%%\t saldo: %.2lf\n", valorTransacao, (tarifa * 100), tr->lista[i].saldoAtualizado);
            }
            printf("\n");

            // Em paralelo, gera um extrato em um arquivo txt
            geraExtrato(&lc->carteira[indiceCliente]);

            return 0;
        }
    }
}

// Função para gerar um extrato e salvá-lo em um arquivo txt
int geraExtrato(Cliente *c) {
    char *tipo;
    Transacoes *tr = &c->extrato;
    FILE *f = fopen("extrato.txt", "w");

    // Escreve informações gerais no arquivo do extrato
    fprintf(f, "nome: %s\n", c->nome);
    fprintf(f, "CPF: %d\n", c->cpf);

    // Determina o tipo de conta do cliente
    if (c->tipo == 1) {
        fprintf(f, "Tipo de conta: comum\n");
    } else {
        fprintf(f, "Tipo de conta: plus\n");
    }

    // Itera sobre as transações e escreve detalhes no arquivo
    for (int i = 0; i < tr->qtd; i++) {
        double tarifa = 0;
        double valorTransacao = tr->lista[i].valor / (1 + tarifa);

        // Determina o tipo de transação e, se for débito, calcula a tarifa
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

        // Escreve detalhes da transação no arquivo, incluindo data, tipo, valor, tarifa e saldo atualizado
        fprintf(f, "-----------------------------------------------------------\n");
        fprintf(f,"%0d/%0d/%0d %0dh%0dm%0ds\t", tr->lista[i].dataTransacao.dia, tr->lista[i].dataTransacao.mes, tr->lista[i].dataTransacao.ano, tr->lista[i].dataTransacao.hora, tr->lista[i].dataTransacao.min, tr->lista[i].dataTransacao.seg);
        fprintf(f, "%s\n", tipo);
        fprintf(f, "\t R$ %.2lf\t ", valorTransacao);
        fprintf(f, "tarifa: %.0lf%%\t ", (tarifa * 100));
        fprintf(f, "saldo: R$ %.2lf\t ", tr->lista[i].saldoAtualizado);
        fprintf(f, "\n");
    }

    // Fecha o arquivo do extrato
    fclose(f);

    return 0;
}

// Função para verificar se o saldo da conta é suficiente, considerando o cheque especial disponivel para cada tipo de conta (comum ou plus)
int verificaSaldo(Cliente *c, double valor) {

    //Se a conta for tipo comum, o limite e de 1000 reais negativos
    if (c->tipo == 1) {
        if (c->saldo - valor < -1000) {
            return -3;
        }
    } else if (c->tipo == 2) { //Se a conta for tipo plus, o limite e de 5000 reais negativos
        if (c->saldo - valor < -5000) {
            return -3;
        }
    }

    return 0;
}

// Função para registrar a data e hora da transação
int registraData(Data *dt) {
    struct tm *data;
    time_t timer;

    // Obtém a data e hora atual do sistema
    time(&timer);
    data = localtime(&timer); //retorna a data e hora atual do sistema no tipo struct tm

    // Preenche a estrutura Data com os detalhes da data e hora
    dt->dia = data->tm_mday;
    dt->mes = data->tm_mon + 1;
    dt->ano = data->tm_year + 1900;
    dt->hora = data->tm_hour;
    dt->min = data->tm_min;
    dt->seg = data->tm_sec;

    return 0;
}


