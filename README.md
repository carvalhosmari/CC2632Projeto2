# CC2632Projeto2
Repositório destinado a alocação do segundo projeto da disciplina CC2632 - Desenvolvimento de algoritmos, ministrada no segundo semestre do curso de ciência da computação do Centro Universitário FEI.
<hr>

## Trabalho prático - Banco QuemPoupaTem

O novo banco QuemPoupaTem vai iniciar a sua operação em breve, mas não tem um sistema bancário estabelecido. Para desenvolver o sistema que controla os clientes, o banco decidiu contratar você.

O seu programa deve ser todo desenvolvido em C.

### Requisitos

- O banco trabalha com dois tipos de conta:
  -  Comum: 
      - Cobra taxa de 5% a cada débito realizado
      - Permite um saldo negativo de até (R$ 1.000,00)

  - Plus:
    - Cobra taxa de 3% a cada débito realizado
    - Permite um saldo negativo de até (R$ 5.000,00)

- O sistema criado por você deve funcionar em loop infinito até que se deseje sair;
- Um menu de opções deve ser sempre apresentado ao operador, contendo as seguintes operações:

		1 - Novo cliente
		2 - Apaga cliente
		3 - Listar clientes
		4 - Débito
		5 - Depósito
		6 - Extrato
		7 - Transferência Entre Contas
		0 - Sair

- Cada opção deve ser implementada como uma função;
- O seu programa deve conseguir armazenar até 1000 clientes e as informações das últimas 100 operações (depósito, saque, transferência) realizada pelo cliente
- **IMPORTANTE:** Não se esqueça de que o banco não pode perder as informações se o programa terminar, fechar, parar de funcionar, ou o computador desligar. Todos os dados devem ser salvos de maneira permanente utilizando arquivos binários.


### Funções

- Opção 1 - Usada para criar novos clientes.
	- Dados solicitados:
		- Nome
		- CPF
		- Tipo de conta (são dois: comum e plus)
		- Valor inicial da conta
		- Senha do usuário

- Opção 2 - Apaga o cliente pelo CPF

- Opção 3 - Listar todos os clientes

- Opção 4 - Serve para debitar um valor da conta do cliente
	- Dados solicitados:
		- CPF
		- Senha
		- Valor
	- **O débito somente pode ser feito se o CPF e a senha estiverem corretos.**

- Opção 5 - Deposita um valor na conta do cliente
	- Dados solicitados:
		- CPF
		- Valor

- Opção 6 - Extrato - gera um arquivo com o histórico de todas as operações realizadas na conta, com datas e valores, incluindo as tarifas.
	- Dados solicitados:
		- CPF
		- Senha
	- O formato do extrato é livre, porém o arquivo de saída deve ser em formato txt e que possa ser aberto em qualquer editor de texto.
	- Não é necessário armazenar as datas das transações
	- **O extrato só pode ser exibido se o CPF e senha estiverem corretos**

- Opção 7 - Transferência - realiza a transferência de uma valor determinado de uma conta (Origem) para outra conta (Destino)
	- Dados solicitados:
		- CPF (Origem)
		- Senha (Origem)
		- CPF (Destino)
		- Valor
	- **A transferência só pode ser realizada se o CPF e a senha da conta de origem estiverem corretos.**
