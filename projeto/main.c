#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main() {

    int  input, cod;
    ListaClientes lista;

    //verifica se ha clientes cadastrados, caso haja, os mesmos sao carregados na lista declarada anteriormente
    cod = carregaListaClientes(&lista, "arquivo");

    if (cod != 0) {
        //caso nao haja clientes cadastrados, a lista e inicializada com quantidade = 0
        lista.qtd = 0;
    }

    //programa funcionando em looping ate que o usuario digite 0 (opcao de sair do programa)
    do {
        //funcao que imprime o menu principal
        imprimeMenu();

        //capta o input do usuario de acordo com a escolha do mesmo e redireciona fluxo do programa
        scanf("%d", &input);

        if (input == 0) {
            //se input for 0, o programa e encerrado
        } else if (input == 1) {
            //caso o input seja 1, a funcao que cadastra cliente e chamada, e a mesma retorna um codigo para tratamento de erros
            cod = cadastraCliente(&lista);

            if (cod != 0) {
                //caso retorne diferente de 0, indica que o programa nao concluiu o cadastro do cliente
                printf("\nErro ao cadastrar cliente! Tente novamente em instantes..\n\n");
            } else {
                //salvando o cliente no arquivo binario
                cod = salvaListaClientes(&lista, "arquivo");

                if (cod == 0) {
                    //caso retorne 0, indica que o cliente foi cadastrado e salvo com sucesso
                    printf("\nCliente cadastrado com sucesso!\n\n");
                } else {
                    //caso contrario (1), indica erro na abertura do arquivo binario onde sera salvo
                    printf("\nErro na abertura do arquivo de destino.\n\n");
                }
            }

            system("pause");

        } else if(input == 2) {
            //caso o input seja 2, a funcao que deleta cliente e chamada, e a mesma retorna um codigo para tratamento de erros
            cod = deletaCliente(&lista);

            if (cod == 1) {
                //caso retorne 1, indica que o cpf digitado nao corresponde ao cpf de qualquer cliente cadastrado
                printf("\nCliente nao encontrado!\n\n");
            } else {
                //caso retorne 0, indica que o cliente foi deletado com sucesso
                printf("\nCliente deletado com sucesso!\n\n");
                salvaListaClientes(&lista, "arquivo"); //a lista de clientes atualizada e salva no arquivo binario
            }

            system("pause");

        } else if(input == 3) {
            //caso o input seja 3, a funcao que lista os clientes e chamada, e a mesma retorna um codigo para tratamento de erros
            cod = listaClientes(&lista);

            if (cod == 0) {
                //a lista de clientes e exibida
            } else if (cod == 1) {
                //indica que nao ha clientes cadastrados
                printf("\nLista de clientes vazia.\n\n");
            } else {
                //indica erro na abertura do arquivo binario onde os clientes estao salvos
                printf("\nNao foi possivel exibir a lista de clientes! Tente novamente em instantes..\n\n");
            }

            system("pause");

        } else if(input == 4) {
            //caso o input seja 4, a funcao que debita um valor da conta do cliente e chamada, e a mesma retorna um codigo para tratamento de erros
            cod = debitaValor(&lista);

            if (cod == -1) {
                //se -1, indica que cpf digitado nao corresponde
                printf("\nCPF invalido!\n\n");
            } else if (cod == 0) {
                //se 0, confirma o sucesso da transacao
                printf("\nValor debitado com sucesso!\n\n");
                salvaListaClientes(&lista, "arquivo");
            } else if (cod == -2) {
                //se -2, indica senha incorreta
                printf("\nSenha incorreta!\n\n");
            } else if (cod == -3) {
                //se -3, indica saldo insuficiente
                printf("\nSaldo insuficiente!\n\n");
            }

            system("pause");

        } else if(input == 5) {
            //caso o input seja 5, a funcao que deposita um valor na conta do cliente e chamada, e a mesma retorna um codigo para tratamento de erros
            cod = depositaValor(&lista);

            if (cod == -1) {
                //se -1, indica que cpf digitado nao corresponde
                printf("\nCPF invalido!\n\n");
            } else if (cod == 0) {
                //se 0, indica o sucesso da transacao
                printf("\nValor depositado com sucesso!\n\n");
                salvaListaClientes(&lista, "arquivo");
            }

            system("pause");

        } else if(input == 6) {
            //caso o input seja 6, a funcao que exibe e gera o extrato do cliente e chamada, e a mesma retorna um codigo para tratamento de erros
            cod = listaTransacoes(&lista);

            if (cod == 0) {
                //se 0, exibe na tela o extrato do cliente e tambem gera arquivo txt com as informacoes
                printf("\nArquivo txt com informacoes de extrato gerado com sucesso!\n\n");
            } else if (cod == -1) {
                //se -1, indica que cpf digitado nao corresponde
                printf("\nCPF invalido!\n\n");
            } else if (cod == -2) {
                //se -2, indica que senha digitada nao corresponde
                printf("\nSenha incorreta!\n\n");
            }

            system("pause");
        } else if(input == 7) {
            //caso o input seja 7, a funcao que transfere um valor da conta de um cliente para o outro e chamada, e a mesma retorna um codigo para tratamento de erros
            cod = transfereValor(&lista);

            if (cod == -1) {
                //se -1, indica que cpf digitado nao corresponde
                printf("\nCPF invalido!\n\n");
            } else if (cod == 0) {
                //se 0, indica o sucesso da transacao
                printf("\nValor transferido com sucesso!\n\n");
                salvaListaClientes(&lista, "arquivo");
            } else if (cod == -2) {
                //se -2, indica que senha digitada nao corresponde
                printf("\nSenha incorreta!\n\n");
            } else if (cod == -3) {
                //se -3, indica que nao ha saldo suficiente
                printf("\nSaldo insuficiente!\n\n");
            }

            system("pause");

        } else {
            //caso digite algum input diferente de 1, 2, 3, 4, 5, 6, 7 ou 0
            printf("\nOpcao invalida!\n\n");
        }
    } while (input != 0);
}
