# Projeto SUS
O projeto faz parte da disciplina de Algoritmos e Estruturas de Dados I, e consiste na elaboração de um sistema simples de atendimento médico por meio de tipos abstratos de dados (TADs).

## Requisitos do Sistema
O sistema consiste em dois armazenamentos principais: uma Lista com todos os pacientes que deram entrada no hospital e um Fila com os pacientes que entraram e ainda não foram atendidos. Para implementar isso, construímos um TAD de registro, que pode representar tanto um item da Lista quanto um item da Fila. Esse registro, por sua vez, contém o TAD Paciente (composto por id único e nome) e o seu histórico de procedimentos, implementado como uma Pilha de strings.  
Além disso, são requisitadas as seguintes funcionalidades, que são acessíveis por meio do menu de main.c e ordenadas pelos mesmos índices deste documento:  
1. Registrar um novo paciente  
    - Entradas: id único e nome  
    - Saídas: mensagem avisando se o resgistro teve sucesso
  
2. Dar alta ao paciente;  
    /O que significa dar alta ao paciente? Adicionar descrição/
   
4. Adicionar procedimento ao histórico médico;
    - Entradas: id do paciente que receberá o procedimento e o procedimento
    - Saída: mensagem avisando se a inserção teve sucesso ou se o histórico está cheio

6. Desfazer procedimento do histórico médico;
    - Adicionar descrição

8. Chamar paciente para atendimento;
    - Adicionar descrição

10. Mostrar fila de espera;
    - Adicionar descrição

12. Mostrar histórico do paciente;
    - Adicionar descrição

14. Sair do menu;
